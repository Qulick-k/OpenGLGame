#pragma once
#include <OGL3D/OPrerequisites.h>



class OShaderProgram
{
public:
	OShaderProgram(const OShaderProgramDesc& desc);
	~OShaderProgram();
	ui32 getId();
	void setUniformBufferSlot(const char* name, ui32 slot);
private:
	void attach(const wchar_t* shaderFilePath, const OShaderType& type);   // 用於附加 Shader，需要特定的type of the shader
	void link();                                                            // 用於連接 Shader Program
private:
	ui32 m_programId = 0;                         // 用於儲存 Shader Program 的 ID
	ui32 m_attachedShaders[2] = {};                //2個unsigned integer，vertex 和 fragment 
};

