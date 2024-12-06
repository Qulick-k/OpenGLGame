#pragma once
class OWindow
{
	//add constructor and destructor
public:
	OWindow();  // 構造函數聲明
	~OWindow(); // 析構函數聲明

	void onDestroy();  //新增onDestroy函數，用於銷毀視窗
	bool isClosed();   //新增isClosed函數，用於判斷視窗是否關閉
private:
	void* m_handle = nullptr;  //定義私有成員變數，儲存資源的通用指針
};

