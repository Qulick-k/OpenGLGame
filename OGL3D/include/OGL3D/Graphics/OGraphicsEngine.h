#pragma once
#include <OGL3D/OPrerequisites.h>
#include <OGL3D/Math/OVec4.h>
#include <OGL3D/Math/ORect.h>

class OGraphicsEngine
{
public:
	OGraphicsEngine();
	~OGraphicsEngine();
public:
	OVertexArrayObjectPtr createVertexArrayObject(const OVertexBufferDesc& data);   // 宣告函數，創建一個 Vertex Array Object，並返回一個指向它的智慧指標
	OShaderProgramPtr createShaderProgram(const OShaderProgramDesc& desc);          // 宣告函數，創建一個 ShaderProgram，並返回一個指向它的智慧指標
public:
	void clear(const OVec4& color);         //宣告一個成員函數 clear,用於接收一個 OVec4 型別的常量引用參數,通常用於清除某種狀態或設置背景顏色的函數
	void setViewport(const ORect& size);    //宣告一個成員函數 setViewport,用於接收一個 ORect 型別的常量引用參數,通常用於設置Viewport大小的函數
	void setVertexArrayObject(const OVertexArrayObjectPtr& vao);  // 設定某個 Vertex Array Object 作為當前的 VAO 或儲存到某個成員變數中, 用於管理 VAO 的狀態或切換。
	void setShaderProgram(const OShaderProgramPtr& program);	  // 設定某個 Shader Program 作為當前的 Program 或儲存到某個成員變數中, 用於管理 Shader Program 的狀態或切換。
	void drawTriangles(ui32 vertexCount, ui32 offset);         // 繪製三角形 vertexCount頂點數量 offset頂點的起始位置,從哪個頂點開始繪製
};