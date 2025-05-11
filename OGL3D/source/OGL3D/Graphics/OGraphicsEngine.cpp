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
	glClearColor(color.x, color.y, color.z, color.w);                                    //glClearColor �Ω�]�m OpenGL �e�����M���C��]�I���C��^�C
	glClear(GL_COLOR_BUFFER_BIT);													     //glClear �M�����w���w�İϤ��e, GL_COLOR_BUFFER_BIT�G�M���C��w�İϡA���m�e���I����C
}

void OGraphicsEngine::setFaceCulling(const OCullType& type)
{
	auto cullType = GL_BACK;

	if (type == OCullType::FrontFace) cullType = GL_FRONT;                     //GL_FRONT�G�簣�����T���ΡC
	else if (type == OCullType::BackFace) cullType = GL_BACK;                      //GL_FRONT_AND_BACK�G�簣�I���T���ΡC
	else if (type == OCullType::Both) cullType = GL_FRONT_AND_BACK;                     //GL_BACK�G�簣�����M�I���T���ΡC

	glEnable(GL_CULL_FACE);                                                        //glEnable �ҥέ��簣�\��C
	glCullFace(cullType);                                                         //glCullFace �]�m�n�簣���������C
}

void OGraphicsEngine::setWindingOrder(const OWindingOrder& order)
{
	auto orderType = GL_CW;
	
	if (order == OWindingOrder::ClockWise) orderType = GL_CW;
	else if (order == OWindingOrder::CounterClockWise) orderType = GL_CCW;            //GL_CCW�G�f�ɰw��V�C

	glFrontFace(orderType);                                                        //glFrontFace �]�m���I��¶�涶�ǡC
}

void OGraphicsEngine::setViewport(const ORect& size)
{
	glViewport(size.left, size.top, size.width, size.height);                            //glViewport �]�mViewport�j�p�A�Y�]�m OpenGL �e������ܰϰ�C
}

void OGraphicsEngine::setVertexArrayObject(const OVertexArrayObjectPtr& vao)
{
	glBindVertexArray(vao->getId());                                                     //glBindVertexArray �j�w�@�ӳ��I�}�C����]VAO�^�C
}

void OGraphicsEngine::setUniformBuffer(const OUniformBufferPtr& buffer, ui32 slot)
{
	glBindBufferBase(GL_UNIFORM_BUFFER, slot, buffer->getId());					         //glBindBufferBase �j�w�@�� Uniform Buffer Object�]UBO�^����w���Ѧ�C
}

void OGraphicsEngine::setShaderProgram(const OShaderProgramPtr& program)
{
	glUseProgram(program->getId());                                                      //glUseProgram �]�m��e�� Shader Program�C
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
