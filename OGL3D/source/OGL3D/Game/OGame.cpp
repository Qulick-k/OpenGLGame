#include <OGL3D/Game/OGame.h>
#include <OGL3D/Window/OWindow.h>
#include <Windows.h>

OGame::OGame()
{
	m_display = std::unique_ptr<OWindow>(new OWindow());
}

OGame::~OGame()
{
}

void OGame::run()
{
	MSG msg;
	while (m_isRunning && !m_display->isClosed())
	{
		//�ˬd���ε{�����T����C���O�_���T��(PeekMessage), (&msg)�ϥΦa�}�N�T���x�s�x���ܼƤ�, (hWnd)�ˬd�P�ثe��������p���������T��, 
		//(wMsgFilterMin),(wMsgFilterMax)�]�m�n�ˬd�T�������d��]��NULL����ˬd�Ҧ��������T��, (PM_REMOVE)�˯��T���Ჾ��
		if (PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE))  
		{
			TranslateMessage(&msg);     //�N��l��L�T���ഫ���r��T��
			DispatchMessage(&msg);	    //�N�T���o�e��X�A������
		}

		Sleep(1);                       //��CPU�𮧤@�U
	}
}

void OGame::quit()
{
	m_isRunning = false;
}
