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
	void attach(const wchar_t* shaderFilePath, const OShaderType& type);   // �Ω���[ Shader�A�ݭn�S�w��type of the shader
	void link();                                                            // �Ω�s�� Shader Program
private:
	ui32 m_programId = 0;                         // �Ω��x�s Shader Program �� ID
	ui32 m_attachedShaders[2] = {};                //2��unsigned integer�Avertex �M fragment 
};

