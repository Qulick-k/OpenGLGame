#include <OGL3D/Game/OGame.h>
#include <OGL3D/Window/OWindow.h>
#include <OGL3D/Graphics/OVertexArrayObject.h>
#include <OGL3D/Graphics/OShaderProgram.h>
#include <OGL3D/Graphics/OUniformBuffer.h>
#include <OGL3D/Math/OMat4.h>
//#include <OGL3D/Graphics/OGraphicsEngine.h> 
/*  #include 指令
#include 指令
作用：
將指定的標頭檔案內容插入到當前檔案中，以便使用標頭檔案中定義的類、函數或其他程式碼。
語法：
#include <標頭檔案>：表示從標準或全局路徑中搜尋檔案。
#include "標頭檔案"：表示從當前檔案所在目錄或指定的路徑中搜尋檔案。
*/
//#include <Windows.h>

struct UniformData
{
	OMat4 world;
};

OGame::OGame()
{
	m_graphicsEngine = std::make_unique<OGraphicsEngine>(); //初始化OGraphicsEngine,  || std::make_unique創建一個GraphicsEngine類型的智慧指標（std::unique_ptr）,並將其指派給變數m_graphicsEngine
	m_display = std::make_unique<OWindow>();                //使用智慧指針std::unique_ptr管理一個動態分配的OWindow對象，將其分配給成員變數m_display //使用make_unique<OWindow>()取代unique_ptr<OWindow>(new OWindow())

	m_display->makeCurrentContext();                        //調用OWindow類的makeCurrentContext()函數
	
	m_graphicsEngine->setViewport(m_display->getInnerSize()); //調用OGraphicsEngine類的setViewport函數，設置Viewport大小
}

OGame::~OGame()
{
}

void OGame::onCreate()
{
	const f32 polygonVertices[] = { //四角角形的4個頂點坐標
		-0.5f, -0.5f, 0.0f,
		1    ,0     ,0    ,

		-0.5f, 0.5f, 0.0f,
		0    ,1     ,0    ,

		0.5f, -0.5f, 0.0f,
		0    ,0     ,1	,

		0.5f, 0.5f, 0.0f,
		1    ,1     ,0
	};


	OVertexAttribute attribsList[] = {
		3,  //position
		3   //color
	};

	m_polygonVAO = m_graphicsEngine->createVertexArrayObject({
		(void*)polygonVertices,
		sizeof(f32)*(3+3), 
		4,

		attribsList,
		2
		});   // 呼叫函數 createVertexArrayObject，用來建立一個 Vertex Array Object (VAO)


	m_uniform = m_graphicsEngine->createUniformBuffer({
		sizeof(UniformData)
		}); // 呼叫函數 createUniformBuffer，用來建立一個 Uniform Buffer Object (UBO)

	m_shader = m_graphicsEngine->createShaderProgram(
		{
			L"Assets/Shaders/BasicShader.vert",
			L"Assets/Shaders/BasicShader.frag"
		}); // 呼叫函數 createShaderProgram，用來建立一個 Shader Program

	m_shader->setUniformBufferSlot("UniformData", 0); // 設置 Uniform Buffer 的槽位，將 Uniform Buffer 綁定到 Shader Program 中的指定槽位
}

void OGame::onUpdate()
{
	//computing delta time
	auto currentTime = std::chrono::system_clock::now(); //獲取當前時間
	auto elapsedSeconds = std::chrono::duration<double>();
	if (m_previousTime.time_since_epoch().count())
	{
		elapsedSeconds = currentTime - m_previousTime; //計算當前時間與上次時間的差值
	}
	m_previousTime = currentTime; //更新上次時間為當前時間


	auto deltaTime = (f32)elapsedSeconds.count(); //將時間差轉換為浮點數類型的秒數



	m_scale += 1.14f * deltaTime; //將時間差乘以3.14f，並累加到m_scale變數中, 這樣可以使得m_scale隨著時間的推移而增加，從而實現動畫效果
	auto curreentScale = abs(sin(m_scale)); //計算當前的縮放比例，使用sin函數來獲取一個在-1到1之間的值，然後取絕對值，使其在0到1之間變化


	OMat4 world, temp; //創建一個OMat4類的對象world

	temp.setIdentity(); //調回預設矩陣
	temp.setScale(OVec4(1, 1, 1, 1)); //設置縮放矩陣，將當前的縮放比例應用到world矩陣上, 這樣可以實現物體的縮放效果
	world *= temp; 

	temp.setIdentity();
	temp.setRotationZ(m_scale); //設置Z軸旋轉矩陣，將當前的旋轉角度應用到world矩陣上
	world *= temp;

	temp.setIdentity();
	temp.setRotationY(m_scale); //設置Y軸旋轉矩陣，將當前的旋轉角度應用到world矩陣上
	world *= temp;

	temp.setIdentity();
	temp.setRotationX(m_scale); //設置X軸旋轉矩陣，將當前的旋轉角度應用到world矩陣上
	world *= temp;

	temp.setIdentity(); 
	temp.setTranslation(OVec4(0, 0, 0, 1)); //設置平移矩陣，將當前的平移比例應用到world矩陣上, 這樣可以實現物體的平移效果
	world *= temp; 

	UniformData data = { world };
	m_uniform->setData(&data); //調用OUniformBuffer類的setData函數，設置Uniform Buffer的數據  




	m_graphicsEngine->clear(OVec4(0, 0, 0, 1));              //調用OGraphicsEngine類的clear函數，清除畫面OVec4(1, 0, 0, 1) 應該代表 RGBA 格式的紅色（紅色值為 1，綠色和藍色為 0，透明度為 1 即完全不透明）

	m_graphicsEngine->setVertexArrayObject(m_polygonVAO);   //調用OGraphicsEngine類的setVertexArrayObject函數，設置當前的VAO
	m_graphicsEngine->setUniformBuffer(m_uniform, 0);       //調用OGraphicsEngine類的setUniformBuffer函數，設置當前的UBO
	m_graphicsEngine->setShaderProgram(m_shader);            //調用OGraphicsEngine類的setShaderProgram函數，設置當前的Shader Program
	m_graphicsEngine->drawTriangles(TriangleStrip, m_polygonVAO->getVertexBufferSize(), 0);                   //調用OGraphicsEngine類的drawTriangles函數，繪製三角形

	m_display->present(false);							     //調用OWindow類的present函數，控制垂直同步
}

void OGame::onQuit()
{
}



void OGame::quit()
{
	m_isRunning = false;
}
