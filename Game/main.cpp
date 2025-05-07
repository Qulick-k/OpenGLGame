#include <OGL3D/Game/OGame.h>
#include <iostream> //引入C++標準的輸入輸出流庫

int main()
{
	try
	{
		OGame game;
		game.run();
	}
	catch (const std::exception& e)
	{
		std::wclog << e.what() << std::endl;            //使用e.what()輸出異常的具體錯誤訊息,方便開發者定位問題。
		return -1;
	}

	return 0;
}