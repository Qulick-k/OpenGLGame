#pragma once
#include <memory>                                                     // 引入標頭檔，提供 std::shared_ptr 智慧指標的功能
#include <sstream>												      // 引入標頭檔，提供 std::stringstream 的功能
#include <iostream>													  // 引入標頭檔，提供 std::cout 的功能
#include <stdexcept>												  // 引入標頭檔，提供 std::runtime_error 的功能

class OVertexArrayObject; 										      // 前置宣告 (Forward Declaration)，告訴編譯器 OVertexArrayObject 類別會在後面定義
class OUniformBuffer; 										          // 前置宣告 (Forward Declaration)，告訴編譯器 OUniformBuffer 類別會在後面定義
class OShaderProgram;                                                 // 前置宣告 (Forward Declaration)，告訴編譯器 OVertexArrayObject 類別會在後面定義，定義一個shared pointer for the shader
/*
定義一個型別別名 OVertexArrayObjectPtr：
使用 std::shared_ptr 封裝類別 OVertexArrayObject 的智慧指標。
std::shared_ptr 是 C++11 引入的一種智慧指標，用於自動管理物件的記憶體生命週期。
當最後一個 std::shared_ptr 指向的物件被銷毀時，物件會自動釋放。
*/
typedef std::shared_ptr<OVertexArrayObject> OVertexArrayObjectPtr;
typedef std::shared_ptr<OUniformBuffer> OUniformBufferPtr;            //定義一個shared pointer for the uniform buffer
typedef std::shared_ptr<OShaderProgram> OShaderProgramPtr;            //定義一個shared pointer for the shader

typedef float f32;          // 別名 f32 讓其他開發者明確知道這是 32 位的浮點數
typedef int i32;            // 別名 i32 讓其他開發者明確知道這是 32 位的整數
typedef unsigned int ui32;  // 別名 ui32 讓其他開發者明確知道這是 32 位的無符號整數


struct OVertexAttribute
{
	ui32 numElements = 0;  //元素數量
};

struct  OVertexBufferDesc
{
	void* verticesList = nullptr;		  //指向頂點資料的指標,void* 泛型指標可以指向任意類型的資料, nullptr 初始時沒有指向任何資料
	ui32 vertexSize = 0;                  //每個頂點的大小（以位元組為單位）
	ui32 listSize = 0; 				      //頂點列表中的元素數量

	OVertexAttribute* attributesList = nullptr;  //指向頂點屬性的指標
	ui32 attributesListSize = 0;                      //頂點屬性的數量
};

struct  OIndexBufferDesc
{
	void* indicesList = nullptr;		  //指向頂點資料的指標,void* 泛型指標可以指向任意類型的資料, nullptr 初始時沒有指向任何資料
	ui32 listSize = 0; 				      //頂點列表中的元素數量
};

struct OShaderProgramDesc
{
	const wchar_t* vertexShaderFilePath;		 //頂點著色器
	const wchar_t* fragmentShaderFilePath;       //片段著色器
};

struct OUniformBufferDesc
{
	ui32 size = 0;
};

enum class OTriangleType
{
	TriangleList = 0,	//三角形列表
	TriangleStrip 		//三角形帶
};

enum class OCullType
{
	BackFace = 0,    //背面剔除
	FrontFace,     //正面剔除
	Both      //雙面剔除
};

enum class OWindingOrder
{
	ClockWise = 0, //順時針
	CounterClockWise //逆時針
};

enum class OShaderType
{
	VertexShader =0,
	FragmentShader
};

#define OGL3D_ERROR(message)\
{\
std::stringstream m;\
m << "OGL3D Error: " << message << std::endl;\
throw std::runtime_error(m.str());\
}

#define OGL3D_WARNING(message)\
std::wclog << "OGL3D Warning: " << message << std::endl;

#define OGL3D_INFO(message)\
std::wclog << "OGL3D Info: " << message << std::endl;