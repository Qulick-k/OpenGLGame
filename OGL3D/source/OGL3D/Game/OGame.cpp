#include <OGL3D/Game/OGame.h>
#include <OGL3D/Window/OWindow.h>
#include <OGL3D/Graphics/OVertexArrayObject.h>
#include <OGL3D/Graphics/OShaderProgram.h>
#include <OGL3D/Graphics/OUniformBuffer.h>
#include <OGL3D/Math/OMat4.h>
#include <OGL3D/Math/OVec3.h>
#include <OGL3D/Math/OVec2.h>
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
	OMat4 projection;
};

struct Vertex
{
	OVec3 position;
	OVec2 texcoord;
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

	//const f32 polygonVertices[] = { //�|�����Ϊ�4�ӳ��I����
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
	// �إߤ@�� Vertex Array Object (VAO)
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


	OMat4 world,projection, temp; //�Ыؤ@��OMat4������Hworld

	temp.setIdentity(); //�զ^�w�]�x�}
	temp.setScale(OVec3(1, 1, 1)); //�]�m�Y��x�}�A�N��e���Y�������Ψ�world�x�}�W, �o�˥i�H��{���骺�Y��ĪG
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
	temp.setTranslation(OVec3(0, 0, 0)); //�]�m�����x�}�A�N��e������������Ψ�world�x�}�W, �o�˥i�H��{���骺�����ĪG
	world *= temp; 



	auto displaySize = m_display->getInnerSize(); //����������j�p
	projection.setOrthoLH(displaySize.width * 0.004f, displaySize.height * 0.004f, 0.01f, 100.0f); //�]�m�����v�x�}�A�o�˥i�H��{���骺��v�ĪG



	UniformData data = { world, projection };
	m_uniform->setData(&data); //�ե�OUniformBuffer����setData��ơA�]�mUniform Buffer���ƾ�  




	m_graphicsEngine->clear(OVec4(0, 0, 0, 1));              //�ե�OGraphicsEngine����clear��ơA�M���e��OVec4(1, 0, 0, 1) ���ӥN�� RGBA �榡������]����Ȭ� 1�A���M�Ŧ⬰ 0�A�z���׬� 1 �Y�������z���^

	m_graphicsEngine->setFaceCulling(OCullType::BackFace); //�ե�OGraphicsEngine����setFaceCulling��ơA�]�m���簣�������I���簣
	m_graphicsEngine->setWindingOrder(OWindingOrder::ClockWise);
	m_graphicsEngine->setVertexArrayObject(m_polygonVAO);   //�ե�OGraphicsEngine����setVertexArrayObject��ơA�]�m��e��VAO
	m_graphicsEngine->setUniformBuffer(m_uniform, 0);       //�ե�OGraphicsEngine����setUniformBuffer��ơA�]�m��e��UBO
	m_graphicsEngine->setShaderProgram(m_shader);            //�ե�OGraphicsEngine����setShaderProgram��ơA�]�m��e��Shader Program
	m_graphicsEngine->drawIndexedTriangles(OTriangleType::TriangleList,36);                   //�ե�OGraphicsEngine����drawTriangles��ơAø�s�T����

	m_display->present(false);							     //�ե�OWindow����present��ơA������P�B
}

void OGame::onQuit()
{
}



void OGame::quit()
{
	m_isRunning = false;
}
