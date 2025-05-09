#include <OGL3D/Game/OGame.h>
#include <OGL3D/Window/OWindow.h>
#include <OGL3D/Graphics/OVertexArrayObject.h>
#include <OGL3D/Graphics/OShaderProgram.h>
#include <OGL3D/Graphics/OUniformBuffer.h>
#include <OGL3D/Math/OMat4.h>
//#include <OGL3D/Graphics/OGraphicsEngine.h> 
/*  #include ���O
#include ���O
�@�ΡG
�N���w�����Y�ɮפ��e���J���e�ɮפ��A�H�K�ϥμ��Y�ɮפ��w�q�����B��ƩΨ�L�{���X�C
�y�k�G
#include <���Y�ɮ�>�G��ܱq�зǩΥ������|���j�M�ɮסC
#include "���Y�ɮ�"�G��ܱq��e�ɮשҦb�ؿ��Ϋ��w�����|���j�M�ɮסC
*/
//#include <Windows.h>

struct UniformData
{
	OMat4 world;
};

OGame::OGame()
{
	m_graphicsEngine = std::make_unique<OGraphicsEngine>(); //��l��OGraphicsEngine,  || std::make_unique�Ыؤ@��GraphicsEngine���������z���С]std::unique_ptr�^,�ñN��������ܼ�m_graphicsEngine
	m_display = std::make_unique<OWindow>();                //�ϥδ��z���wstd::unique_ptr�޲z�@�ӰʺA���t��OWindow��H�A�N����t�������ܼ�m_display //�ϥ�make_unique<OWindow>()���Nunique_ptr<OWindow>(new OWindow())

	m_display->makeCurrentContext();                        //�ե�OWindow����makeCurrentContext()���
	
	m_graphicsEngine->setViewport(m_display->getInnerSize()); //�ե�OGraphicsEngine����setViewport��ơA�]�mViewport�j�p
}

OGame::~OGame()
{
}

void OGame::onCreate()
{
	const f32 polygonVertices[] = { //�|�����Ϊ�4�ӳ��I����
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
		});   // �I�s��� createVertexArrayObject�A�Ψӫإߤ@�� Vertex Array Object (VAO)


	m_uniform = m_graphicsEngine->createUniformBuffer({
		sizeof(UniformData)
		}); // �I�s��� createUniformBuffer�A�Ψӫإߤ@�� Uniform Buffer Object (UBO)

	m_shader = m_graphicsEngine->createShaderProgram(
		{
			L"Assets/Shaders/BasicShader.vert",
			L"Assets/Shaders/BasicShader.frag"
		}); // �I�s��� createShaderProgram�A�Ψӫإߤ@�� Shader Program

	m_shader->setUniformBufferSlot("UniformData", 0); // �]�m Uniform Buffer ���Ѧ�A�N Uniform Buffer �j�w�� Shader Program �������w�Ѧ�
}

void OGame::onUpdate()
{
	//computing delta time
	auto currentTime = std::chrono::system_clock::now(); //�����e�ɶ�
	auto elapsedSeconds = std::chrono::duration<double>();
	if (m_previousTime.time_since_epoch().count())
	{
		elapsedSeconds = currentTime - m_previousTime; //�p���e�ɶ��P�W���ɶ����t��
	}
	m_previousTime = currentTime; //��s�W���ɶ�����e�ɶ�


	auto deltaTime = (f32)elapsedSeconds.count(); //�N�ɶ��t�ഫ���B�I�����������



	m_scale += 1.14f * deltaTime; //�N�ɶ��t���H3.14f�A�ò֥[��m_scale�ܼƤ�, �o�˥i�H�ϱom_scale�H�ۮɶ��������ӼW�[�A�q�ӹ�{�ʵe�ĪG
	auto curreentScale = abs(sin(m_scale)); //�p���e���Y���ҡA�ϥ�sin��ƨ�����@�Ӧb-1��1�������ȡA�M�������ȡA�Ϩ�b0��1�����ܤ�


	OMat4 world, temp; //�Ыؤ@��OMat4������Hworld

	temp.setIdentity(); //�զ^�w�]�x�}
	temp.setScale(OVec4(1, 1, 1, 1)); //�]�m�Y��x�}�A�N��e���Y�������Ψ�world�x�}�W, �o�˥i�H��{���骺�Y��ĪG
	world *= temp; 

	temp.setIdentity();
	temp.setRotationZ(m_scale); //�]�mZ�b����x�}�A�N��e�����ਤ�����Ψ�world�x�}�W
	world *= temp;

	temp.setIdentity();
	temp.setRotationY(m_scale); //�]�mY�b����x�}�A�N��e�����ਤ�����Ψ�world�x�}�W
	world *= temp;

	temp.setIdentity();
	temp.setRotationX(m_scale); //�]�mX�b����x�}�A�N��e�����ਤ�����Ψ�world�x�}�W
	world *= temp;

	temp.setIdentity(); 
	temp.setTranslation(OVec4(0, 0, 0, 1)); //�]�m�����x�}�A�N��e������������Ψ�world�x�}�W, �o�˥i�H��{���骺�����ĪG
	world *= temp; 

	UniformData data = { world };
	m_uniform->setData(&data); //�ե�OUniformBuffer����setData��ơA�]�mUniform Buffer���ƾ�  




	m_graphicsEngine->clear(OVec4(0, 0, 0, 1));              //�ե�OGraphicsEngine����clear��ơA�M���e��OVec4(1, 0, 0, 1) ���ӥN�� RGBA �榡������]����Ȭ� 1�A���M�Ŧ⬰ 0�A�z���׬� 1 �Y�������z���^

	m_graphicsEngine->setVertexArrayObject(m_polygonVAO);   //�ե�OGraphicsEngine����setVertexArrayObject��ơA�]�m��e��VAO
	m_graphicsEngine->setUniformBuffer(m_uniform, 0);       //�ե�OGraphicsEngine����setUniformBuffer��ơA�]�m��e��UBO
	m_graphicsEngine->setShaderProgram(m_shader);            //�ե�OGraphicsEngine����setShaderProgram��ơA�]�m��e��Shader Program
	m_graphicsEngine->drawTriangles(TriangleStrip, m_polygonVAO->getVertexBufferSize(), 0);                   //�ե�OGraphicsEngine����drawTriangles��ơAø�s�T����

	m_display->present(false);							     //�ե�OWindow����present��ơA������P�B
}

void OGame::onQuit()
{
}



void OGame::quit()
{
	m_isRunning = false;
}
