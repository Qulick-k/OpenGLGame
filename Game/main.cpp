#include <OGL3D/Game/OGame.h>
#include <iostream> //�ޤJC++�зǪ���J��X�y�w

int main()
{
	try
	{
		OGame game;
		game.run();
	}
	catch (const std::exception& e)
	{
		std::wclog << e.what() << std::endl;            //�ϥ�e.what()��X���`��������~�T��,��K�}�o�̩w����D�C
		return -1;
	}

	return 0;
}