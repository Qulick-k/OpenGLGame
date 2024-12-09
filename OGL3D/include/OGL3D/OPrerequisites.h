#pragma once
#include <memory>                                                     // 引入標頭檔，提供 std::shared_ptr 智慧指標的功能

class OVertexArrayObject; 										      // 前置宣告 (Forward Declaration)，告訴編譯器 OVertexArrayObject 類別會在後面定義

/*
定義一個型別別名 OVertexArrayObjectPtr：
使用 std::shared_ptr 封裝類別 OVertexArrayObject 的智慧指標。
std::shared_ptr 是 C++11 引入的一種智慧指標，用於自動管理物件的記憶體生命週期。
當最後一個 std::shared_ptr 指向的物件被銷毀時，物件會自動釋放。
*/
typedef std::shared_ptr<OVertexArrayObject> OVertexArrayObjectPtr;

typedef float f32;          // 別名 f32 讓其他開發者明確知道這是 32 位的浮點數
typedef int i32;            // 別名 i32 讓其他開發者明確知道這是 32 位的整數
typedef unsigned int ui32;  // 別名 ui32 讓其他開發者明確知道這是 32 位的無符號整數


struct  OVertexBufferData
{
	void* verticesList = nullptr;		  //指向頂點資料的指標,void* 泛型指標可以指向任意類型的資料, nullptr 初始時沒有指向任何資料
	ui32 vertexSize = 0;                  //每個頂點的大小（以位元組為單位）
	ui32 listSize = 0; 				      //頂點列表中的元素數量
};