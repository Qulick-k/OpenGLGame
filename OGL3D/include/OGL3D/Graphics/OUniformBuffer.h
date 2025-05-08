#pragma once
#include <OGL3D/OPrerequisites.h>

class OUniformBuffer
{
public:
	OUniformBuffer(const OUniformBufferDesc& desc);
	~OUniformBuffer();

	void setData(void* data);

	ui32 getId();
private:
	ui32 m_id = 0; // �Ω��x�s uniform buffer �� ID
	ui32 m_size = 0; // �Ω��x�s uniform buffer ���j�p
};

