#include <OGL3D/Game/OGame.h>
#include <OGL3D/Window/OWindow.h>
#include <OGL3D/Graphics/OVertexArrayObject.h>
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
	const f32 triangleVerices[] = { //�T���Ϊ��T�ӳ��I����
		-0.5f, -0.5f, 0.0f,
		1    ,0     ,0    ,

		0.5f, -0.5f, 0.0f,
		0    ,1     ,0    ,

		0.0f, 0.5f, 0.0f,
		0    ,0     ,1
	};


	OVertexAttribute attribsList[] = {
		3,  //position
		3   //color
	};

	m_triangleVAO = m_graphicsEngine->createVertexArrayObject({
		(void*)triangleVerices,
		sizeof(f32)*(3+3), 
		3,

		attribsList,
		2

		});   // �I�s��� createVertexArrayObject�A�Ψӫإߤ@�� Vertex Array Object (VAO)
	m_shader = m_graphicsEngine->createShaderProgram(
		{
			L"Assets/Shaders/BasicShader.vert",
			L"Assets/Shaders/BasicShader.frag"
		}); // �I�s��� createShaderProgram�A�Ψӫإߤ@�� Shader Program
}

void OGame::onUpdate()
{
	m_graphicsEngine->clear(OVec4(0, 0, 0, 1));              //�ե�OGraphicsEngine����clear��ơA�M���e��OVec4(1, 0, 0, 1) ���ӥN�� RGBA �榡������]����Ȭ� 1�A���M�Ŧ⬰ 0�A�z���׬� 1 �Y�������z���^

	m_graphicsEngine->setVertexArrayObject(m_triangleVAO);   //�ե�OGraphicsEngine����setVertexArrayObject��ơA�]�m��e��VAO
	m_graphicsEngine->setShaderProgram(m_shader);            //�ե�OGraphicsEngine����setShaderProgram��ơA�]�m��e��Shader Program
	m_graphicsEngine->drawTriangles(m_triangleVAO->getVertexBufferSize(), 0);                   //�ե�OGraphicsEngine����drawTriangles��ơAø�s�T����

	m_display->present(false);							     //�ե�OWindow����present��ơA������P�B
}

void OGame::onQuit()
{
}



void OGame::quit()
{
	m_isRunning = false;
}
