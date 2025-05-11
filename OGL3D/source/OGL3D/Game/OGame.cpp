#include <OGL3D/Game/OGame.h>
#include <OGL3D/Window/OWindow.h>
#include <OGL3D/Graphics/OVertexArrayObject.h>
#include <OGL3D/Graphics/OShaderProgram.h>
#include <OGL3D/Graphics/OUniformBuffer.h>
#include <OGL3D/Math/OMat4.h>
#include <OGL3D/Math/OVec3.h>
#include <OGL3D/Math/OVec2.h>
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
	OMat4 projection;
};

struct Vertex
{
	OVec3 position;
	OVec2 texcoord;
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
	OVec3 positionsList[] =
	{
		//front face
		OVec3(-0.5f, -0.5f, -0.5f),
		OVec3(-0.5f, 0.5f, -0.5f),
		OVec3(0.5f, 0.5f, -0.5f),
		OVec3(0.5f, -0.5f, -0.5f),

		//back face
		OVec3(0.5f, -0.5f, 0.5f),
		OVec3(0.5f, 0.5f, 0.5f),
		OVec3(-0.5f, 0.5f, 0.5f),
		OVec3(-0.5f, -0.5f, 0.5f),
	};


	OVec2 texcoordsList[] =
	{
		OVec2(0,0),
		OVec2(0,1),
		OVec2(1,0),
		OVec2(1,1),
	};


	Vertex verticesList[] =
	{
		//front face
		{ positionsList[0], texcoordsList[1] },
		{ positionsList[1], texcoordsList[0] },
		{ positionsList[2], texcoordsList[2] },
		{ positionsList[3], texcoordsList[3] },

		//back face
		{ positionsList[4], texcoordsList[1] },
		{ positionsList[5], texcoordsList[0] },
		{ positionsList[6], texcoordsList[2] },
		{ positionsList[7], texcoordsList[3] },

		//top face
		{ positionsList[1], texcoordsList[1] },
		{ positionsList[6], texcoordsList[0] },
		{ positionsList[5], texcoordsList[2] },
		{ positionsList[2], texcoordsList[3] },

		//buttom face
		{ positionsList[7], texcoordsList[1] },
		{ positionsList[0], texcoordsList[0] },
		{ positionsList[3], texcoordsList[2] },
		{ positionsList[4], texcoordsList[3] },

		//right face
		{ positionsList[3], texcoordsList[1]},
		{ positionsList[2], texcoordsList[0]},
		{ positionsList[5], texcoordsList[2]},
		{ positionsList[4], texcoordsList[3]},

		//left face
		{ positionsList[7], texcoordsList[1]},
		{ positionsList[6], texcoordsList[0]},
		{ positionsList[1], texcoordsList[2]},
		{ positionsList[0], texcoordsList[3]}
	};

	ui32 indicesList[] =
	{
		//front
		0,1,2,
		2,3,0,

		//back
		4,5,6,
		6,7,4,

		//top
		8,9,10,
		10,11,8,

		//bottom
		12,13,14,
		14,15,12,

		//right
		16,17,18,
		18,19,16,

		//left
		20,21,22,
		22,23,20
	};

	//const f32 polygonVertices[] = { //四角角形的4個頂點坐標
	//	-0.5f, -0.5f, 0.0f,
	//	1    ,0     ,0    ,

	//	-0.5f, 0.5f, 0.0f,
	//	0    ,1     ,0    ,

	//	0.5f, -0.5f, 0.0f,
	//	0    ,0     ,1	,

	//	0.5f, 0.5f, 0.0f,
	//	1    ,1     ,0
	//};


	OVertexAttribute attribsList[] = {
		sizeof(OVec3)/sizeof(f32),  //position
		sizeof(OVec2)/sizeof(f32)   //texcoord
	};
	// 建立一個 Vertex Array Object (VAO)
	m_polygonVAO = m_graphicsEngine->createVertexArrayObject(
		{
			(void*)verticesList,
			sizeof(Vertex),
			sizeof(verticesList)/sizeof(Vertex),

			attribsList,
			sizeof(attribsList)/sizeof(OVertexAttribute)
		},

		{
			(void*) indicesList,
			sizeof(indicesList)
		}
	);   


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


	OMat4 world,projection, temp; //創建一個OMat4類的對象world

	temp.setIdentity(); //調回預設矩陣
	temp.setScale(OVec3(1, 1, 1)); //設置縮放矩陣，將當前的縮放比例應用到world矩陣上, 這樣可以實現物體的縮放效果
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
	temp.setTranslation(OVec3(0, 0, 0)); //設置平移矩陣，將當前的平移比例應用到world矩陣上, 這樣可以實現物體的平移效果
	world *= temp; 



	auto displaySize = m_display->getInnerSize(); //獲取視窗的大小
	projection.setOrthoLH(displaySize.width * 0.004f, displaySize.height * 0.004f, 0.01f, 100.0f); //設置正交投影矩陣，這樣可以實現物體的投影效果



	UniformData data = { world, projection };
	m_uniform->setData(&data); //調用OUniformBuffer類的setData函數，設置Uniform Buffer的數據  




	m_graphicsEngine->clear(OVec4(0, 0, 0, 1));              //調用OGraphicsEngine類的clear函數，清除畫面OVec4(1, 0, 0, 1) 應該代表 RGBA 格式的紅色（紅色值為 1，綠色和藍色為 0，透明度為 1 即完全不透明）

	m_graphicsEngine->setFaceCulling(OCullType::BackFace); //調用OGraphicsEngine類的setFaceCulling函數，設置面剔除類型為背面剔除
	m_graphicsEngine->setWindingOrder(OWindingOrder::ClockWise);
	m_graphicsEngine->setVertexArrayObject(m_polygonVAO);   //調用OGraphicsEngine類的setVertexArrayObject函數，設置當前的VAO
	m_graphicsEngine->setUniformBuffer(m_uniform, 0);       //調用OGraphicsEngine類的setUniformBuffer函數，設置當前的UBO
	m_graphicsEngine->setShaderProgram(m_shader);            //調用OGraphicsEngine類的setShaderProgram函數，設置當前的Shader Program
	m_graphicsEngine->drawIndexedTriangles(OTriangleType::TriangleList,36);                   //調用OGraphicsEngine類的drawTriangles函數，繪製三角形

	m_display->present(false);							     //調用OWindow類的present函數，控制垂直同步
}

void OGame::onQuit()
{
}



void OGame::quit()
{
	m_isRunning = false;
}
