#pragma once
#include <OGL3D/Math/ORect.h>


class OWindow
{
	//add constructor and destructor
public:
	OWindow();  // 篶硑ㄧ计羘
	~OWindow(); // 猂篶ㄧ计羘

	ORect getInnerSize();       //穝糤getInnerSizeㄧ计ノ莉Viewportず场

	void makeCurrentContext();  //穝糤makeCurrentContextㄧ计ノ砞竚讽玡ゅ
	void present(bool vsync);   //穝糤presentㄧ计ノ瞷礶
	//void onDestroy();  //穝糤onDestroyㄧ计ノ綪反跌怠
	//bool isClosed();   //穝糤isClosedㄧ计ノ耞跌怠琌闽超
private:
	void* m_handle = nullptr;  //﹚竡╬ΤΘ跑计纗戈方硄ノ皐
	void* m_context = nullptr; //﹚竡╬ΤΘ跑计纗ゅ硄ノ皐
};

