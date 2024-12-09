#include <OGL3D/Graphics/OGraphicsEngine.h>
#include <OGL3D/Graphics/OVertexArrayObject.h>
#include <glad/glad.h>


OVertexArrayObjectPtr OGraphicsEngine::createVertexArrayObject(const OVertexBufferData& data)
{
	return std::make_shared<OVertexArrayObject>(data);
}

void OGraphicsEngine::clear(const OVec4& color)
{
	glClearColor(color.x, color.y, color.z, color.w);                                    //glClearColor �Ω�]�m OpenGL �e�����M���C��]�I���C��^�C
	glClear(GL_COLOR_BUFFER_BIT);													     //glClear �M�����w���w�İϤ��e, GL_COLOR_BUFFER_BIT�G�M���C��w�İϡA���m�e���I����C
}

void OGraphicsEngine::setViewport(const ORect& size)
{
	glViewport(size.left, size.top, size.width, size.height);                            //glViewport �]�mViewport�j�p�A�Y�]�m OpenGL �e������ܰϰ�C
}

void OGraphicsEngine::setVertexArrayObject(const OVertexArrayObjectPtr& vao)
{
	glBindVertexArray(vao->getId());                                                     //glBindVertexArray �j�w�@�ӳ��I�}�C����]VAO�^�C
}

void OGraphicsEngine::drawTriangles(ui32 vertexCount, ui32 offset)
{
	glDrawArrays(GL_TRIANGLES, offset, vertexCount);
}
