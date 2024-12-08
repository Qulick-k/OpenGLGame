#include <OGL3D/Game/OGame.h>
#include <OGL3D/Window/OWindow.h>
#include <OGL3D/Graphics/OGraphicsEngine.h> 
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
}

OGame::~OGame()
{
}

void OGame::onCreate()
{

}

void OGame::onUpdate()
{
	m_graphicsEngine->clear(OVec4(1, 0, 0, 1));             //�ե�OGraphicsEngine����clear��ơA�M���e��OVec4(1, 0, 0, 1) ���ӥN�� RGBA �榡������]����Ȭ� 1�A���M�Ŧ⬰ 0�A�z���׬� 1 �Y�������z���^


	m_display->present(false);							    //�ե�OWindow����present��ơA�N�e����ܥX��
}

void OGame::onQuit()
{
}



void OGame::quit()
{
	m_isRunning = false;
}
