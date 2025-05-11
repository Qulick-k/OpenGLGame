#include <OGL3D/Graphics/OGraphicsEngine.h>
#include <OGL3D/Graphics/OVertexArrayObject.h>
#include <OGL3D/Graphics/OUniformBuffer.h>
#include <OGL3D/Graphics/OShaderProgram.h>
#include <glad/glad.h>


OVertexArrayObjectPtr OGraphicsEngine::createVertexArrayObject(const OVertexBufferDesc& vbDesc)
{
	return std::make_shared<OVertexArrayObject>(vbDesc);
}

OVertexArrayObjectPtr OGraphicsEngine::createVertexArrayObject(const OVertexBufferDesc& vbDesc, const OIndexBufferDesc& ibDesc)
{
	return std::make_shared<OVertexArrayObject>(vbDesc, ibDesc);
}

OUniformBufferPtr OGraphicsEngine::createUniformBuffer(const OUniformBufferDesc& desc)
{
	return std::make_shared<OUniformBuffer>(desc);
}

OShaderProgramPtr OGraphicsEngine::createShaderProgram(const OShaderProgramDesc& desc)
{
	return std::make_shared<OShaderProgram>(desc);
}


void OGraphicsEngine::clear(const OVec4& color)
{
	glClearColor(color.x, color.y, color.z, color.w);                                    //glClearColor 用於設置 OpenGL 畫面的清除顏色（背景顏色）。
	glClear(GL_COLOR_BUFFER_BIT);													     //glClear 清除指定的緩衝區內容, GL_COLOR_BUFFER_BIT：清除顏色緩衝區，重置畫面背景色。
}

void OGraphicsEngine::setFaceCulling(const OCullType& type)
{
	auto cullType = GL_BACK;

	if (type == OCullType::FrontFace) cullType = GL_FRONT;                     //GL_FRONT：剔除正面三角形。
	else if (type == OCullType::BackFace) cullType = GL_BACK;                      //GL_FRONT_AND_BACK：剔除背面三角形。
	else if (type == OCullType::Both) cullType = GL_FRONT_AND_BACK;                     //GL_BACK：剔除正面和背面三角形。

	glEnable(GL_CULL_FACE);                                                        //glEnable 啟用面剔除功能。
	glCullFace(cullType);                                                         //glCullFace 設置要剔除的面類型。
}

void OGraphicsEngine::setWindingOrder(const OWindingOrder& order)
{
	auto orderType = GL_CW;
	
	if (order == OWindingOrder::ClockWise) orderType = GL_CW;
	else if (order == OWindingOrder::CounterClockWise) orderType = GL_CCW;            //GL_CCW：逆時針方向。

	glFrontFace(orderType);                                                        //glFrontFace 設置頂點的繞行順序。
}

void OGraphicsEngine::setViewport(const ORect& size)
{
	glViewport(size.left, size.top, size.width, size.height);                            //glViewport 設置Viewport大小，即設置 OpenGL 畫面的顯示區域。
}

void OGraphicsEngine::setVertexArrayObject(const OVertexArrayObjectPtr& vao)
{
	glBindVertexArray(vao->getId());                                                     //glBindVertexArray 綁定一個頂點陣列物件（VAO）。
}

void OGraphicsEngine::setUniformBuffer(const OUniformBufferPtr& buffer, ui32 slot)
{
	glBindBufferBase(GL_UNIFORM_BUFFER, slot, buffer->getId());					         //glBindBufferBase 綁定一個 Uniform Buffer Object（UBO）到指定的槽位。
}

void OGraphicsEngine::setShaderProgram(const OShaderProgramPtr& program)
{
	glUseProgram(program->getId());                                                      //glUseProgram 設置當前的 Shader Program。
}

void OGraphicsEngine::drawTriangles(const OTriangleType& triangleType, ui32 vertexCount, ui32 offset)
{
	auto glTriType = GL_TRIANGLES;

	switch (triangleType)
	{
		case OTriangleType::TriangleList: {glTriType = GL_TRIANGLES; break; }
		case OTriangleType::TriangleStrip: {glTriType = GL_TRIANGLE_STRIP; break; }
	}

	glDrawArrays(glTriType, offset, vertexCount);
}

void OGraphicsEngine::drawIndexedTriangles(const OTriangleType& triangleType, ui32 indicesCount)
{
	auto glTriType = GL_TRIANGLES;

	switch (triangleType)
	{
		case OTriangleType::TriangleList: {glTriType = GL_TRIANGLES; break; }
		case OTriangleType::TriangleStrip: {glTriType = GL_TRIANGLE_STRIP; break; }
	}

	glDrawElements(glTriType, indicesCount, GL_UNSIGNED_INT, nullptr);
}
