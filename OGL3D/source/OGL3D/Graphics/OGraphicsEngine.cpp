#include <OGL3D/Graphics/OGraphicsEngine.h>
#include <OGL3D/Graphics/OVertexArrayObject.h>
#include <OGL3D/Graphics/OShaderProgram.h>
#include <glad/glad.h>


OVertexArrayObjectPtr OGraphicsEngine::createVertexArrayObject(const OVertexBufferDesc& data)
{
	return std::make_shared<OVertexArrayObject>(data);
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

void OGraphicsEngine::setViewport(const ORect& size)
{
	glViewport(size.left, size.top, size.width, size.height);                            //glViewport 設置Viewport大小，即設置 OpenGL 畫面的顯示區域。
}

void OGraphicsEngine::setVertexArrayObject(const OVertexArrayObjectPtr& vao)
{
	glBindVertexArray(vao->getId());                                                     //glBindVertexArray 綁定一個頂點陣列物件（VAO）。
}

void OGraphicsEngine::setShaderProgram(const OShaderProgramPtr& program)
{
	glUseProgram(program->getId());                                                      //glUseProgram 設置當前的 Shader Program。
}

void OGraphicsEngine::drawTriangles(ui32 vertexCount, ui32 offset)
{
	glDrawArrays(GL_TRIANGLES, offset, vertexCount);
}
