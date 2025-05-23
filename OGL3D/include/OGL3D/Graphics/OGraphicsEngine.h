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
	OVertexArrayObjectPtr createVertexArrayObject(const OVertexBufferDesc& vbDesc);   // 宣告函數，創建一個 Vertex Array Object，並返回一個指向它的智慧指標
	OVertexArrayObjectPtr createVertexArrayObject(const OVertexBufferDesc& vbDesc, const OIndexBufferDesc& ibDesc);
	OUniformBufferPtr createUniformBuffer(const OUniformBufferDesc& desc);          // 宣告函數，創建一個 Uniform Buffer，並返回一個指向它的智慧指標
	OShaderProgramPtr createShaderProgram(const OShaderProgramDesc& desc);          // 宣告函數，創建一個 ShaderProgram，並返回一個指向它的智慧指標
public:
	void clear(const OVec4& color);         //宣告一個成員函數 clear,用於接收一個 OVec4 型別的常量引用參數,通常用於清除某種狀態或設置背景顏色的函數
	void setFaceCulling(const OCullType& type); // 設定面剔除的類型,用於設置 OpenGL 的面剔除狀態
	void setWindingOrder(const OWindingOrder& order); // 設定頂點的繞行順序,用於設置 OpenGL 的頂點繞行順序
	void setViewport(const ORect& size);    //宣告一個成員函數 setViewport,用於接收一個 ORect 型別的常量引用參數,通常用於設置Viewport大小的函數
	void setVertexArrayObject(const OVertexArrayObjectPtr& vao);  // 設定某個 Vertex Array Object 作為當前的 VAO 或儲存到某個成員變數中, 用於管理 VAO 的狀態或切換。
	void setUniformBuffer(const OUniformBufferPtr& buffer, ui32 slot); // 設定某個 Uniform Buffer 作為當前的 UBO 或儲存到某個成員變數中, 用於管理 UBO 的狀態或切換。
	void setShaderProgram(const OShaderProgramPtr& program);	  // 設定某個 Shader Program 作為當前的 Program 或儲存到某個成員變數中, 用於管理 Shader Program 的狀態或切換。
	void drawTriangles(const OTriangleType& triangleType, ui32 vertexCount, ui32 offset);         // 繪製三角形 vertexCount頂點數量 offset頂點的起始位置,從哪個頂點開始繪製
	void drawIndexedTriangles(const OTriangleType& triangleType, ui32 indicesCount);
};