#include <OGL3D/Graphics/OUniformBuffer.h>
#include <glad/glad.h>


OUniformBuffer::OUniformBuffer(const OUniformBufferDesc& desc)
{
    glGenBuffers(1, &m_id); // �ͦ��@�� buffer�A�ñN�� ID �x�s�� m_id ��
    glBindBuffer(GL_UNIFORM_BUFFER, m_id); // �j�w buffer�A�o�˫��򪺾ާ@���|�@�Ω�o�� buffer
    glBufferData(GL_UNIFORM_BUFFER, desc.size, nullptr, GL_STATIC_DRAW); // ���t buffer �����s�A�ó]�m���R�Aø�s
    glBindBuffer(GL_UNIFORM_BUFFER, 0); // �Ѱ��j�w buffer
    m_size = desc.size; // �x�s buffer ���j�p
}

OUniformBuffer::~OUniformBuffer()
{
    glDeleteBuffers(1, &m_id); // �R�� buffer
}

void OUniformBuffer::setData(void* data)
{
    glBindBuffer(GL_UNIFORM_BUFFER, m_id); // �j�w buffer
    glBufferSubData(GL_UNIFORM_BUFFER, 0, m_size, data); // ��s buffer ���ƾ�
    glBindBuffer(GL_UNIFORM_BUFFER, 0); // �Ѱ��j�w buffer
}

ui32 OUniformBuffer::getId()
{
    return m_id;
}
