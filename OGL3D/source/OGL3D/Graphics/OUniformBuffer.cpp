#include <OGL3D/Graphics/OUniformBuffer.h>
#include <glad/glad.h>


OUniformBuffer::OUniformBuffer(const OUniformBufferDesc& desc)
{
    glGenBuffers(1, &m_id); // 生成一個 buffer，並將其 ID 儲存到 m_id 中
    glBindBuffer(GL_UNIFORM_BUFFER, m_id); // 綁定 buffer，這樣後續的操作都會作用於這個 buffer
    glBufferData(GL_UNIFORM_BUFFER, desc.size, nullptr, GL_STATIC_DRAW); // 分配 buffer 的內存，並設置為靜態繪製
    glBindBuffer(GL_UNIFORM_BUFFER, 0); // 解除綁定 buffer
    m_size = desc.size; // 儲存 buffer 的大小
}

OUniformBuffer::~OUniformBuffer()
{
    glDeleteBuffers(1, &m_id); // 刪除 buffer
}

void OUniformBuffer::setData(void* data)
{
    glBindBuffer(GL_UNIFORM_BUFFER, m_id); // 綁定 buffer
    glBufferSubData(GL_UNIFORM_BUFFER, 0, m_size, data); // 更新 buffer 的數據
    glBindBuffer(GL_UNIFORM_BUFFER, 0); // 解除綁定 buffer
}

ui32 OUniformBuffer::getId()
{
    return m_id;
}
