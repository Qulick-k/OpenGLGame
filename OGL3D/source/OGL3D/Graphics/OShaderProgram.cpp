#include <OGL3D/Graphics/OShaderProgram.h>
#include <glad/glad.h>
#include <fstream>    //�ޥ�fstream�A���F�ե�Input File Stream
#include <sstream>    //in order to extract the file, include sstream
#include <string>     //�x�sshader code�bstring��
#include <vector>     //�ʺA�}�C�]Dynamic Array�^
#include <filesystem>

OShaderProgram::OShaderProgram(const OShaderProgramDesc& desc)
{
	m_programId = glCreateProgram();	// �Ы� Shader Program
	attach(desc.vertexShaderFilePath, VertexShader);          //call attach�sĶvertex shader
	attach(desc.fragmentShaderFilePath, FragmentShader);      //call attach�sĶfragment shader
	link();	// �s�� Shader Program
}

OShaderProgram::~OShaderProgram()
{
	for (ui32 i = 0; i < 2; i++)
	{
		glDetachShader(m_programId, m_attachedShaders[i]);  // �N Shader �q Shader Program ������
		glDeleteShader(m_attachedShaders[i]);              	// �R�� Shader
	}
	glDeleteProgram(m_programId);	    // �R�� Shader Program
}

ui32 OShaderProgram::getId()
{
	return m_programId;
}

void OShaderProgram::attach(const wchar_t* shaderFilePath, const OShaderType& type)
{
	std::string shaderCode;	                    // �x�s Shader Code
	
	auto path = std::filesystem::path(shaderFilePath);

	std::ifstream shaderStream(path);	// Ū�� Shader �ɮ�
	if (shaderStream.is_open())
	{		
		std::stringstream sstr;
		sstr << shaderStream.rdbuf();	// sstr �N�]�t shaderStream �Ҧ����ƾ�
		shaderCode = sstr.str();		// �N sstr �ഫ�� string
		shaderStream.close();			// �x�s��string��A�����ɮ�
	}
	else
	{
		OGL3D_WARNING("OShaderProgram | " << shaderFilePath << "not found");	// �p�G�ɮפ��s�b�A��Xĵ�i
		return;
	}

	ui32 shaderId = 0;                  //�x�sShader ID

	//�ھ� type ���ȡA�M�w�Ыح����������ۦ⾹
	if (type == VertexShader)
		shaderId = glCreateShader(GL_VERTEX_SHADER);
	else if (type == FragmentShader)
		shaderId = glCreateShader(GL_FRAGMENT_SHADER);

	auto sourcePointer = shaderCode.c_str();	                //�N shader code �ഫ�� const char* ����
	glShaderSource(shaderId, 1, &sourcePointer, NULL);	        //�N shader code �]�m�� shader ����
	glCompileShader(shaderId);	                                //�sĶ shader ����


	//get compile errors
	i32 logLength = 0;
	glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &logLength);
	if (logLength > 0)
	{
		std::vector<char> errorMessage(logLength + 1);
		glGetShaderInfoLog(shaderId, logLength, NULL, &errorMessage[0]);
		OGL3D_WARNING("OShaderProgram | " << &errorMessage[0] << " compiled with errors:" << std::endl << &errorMessage[0]);
		return;
	}


	glAttachShader(m_programId, shaderId);	                    //�N shader ������[�� Shader Program �� .AKA �N�@�ӵۦ⾹ (Shader) ���[����w���{����H (Program Object)
	m_attachedShaders[type] = shaderId;	                        //�N shader ID �x�s�� m_attachedShader ��

	OGL3D_INFO("OShaderProgram | " << shaderFilePath << "compiled successfully");	//��X�sĶ���\���T��
}

void OShaderProgram::link()
{
	glLinkProgram(m_programId);	                                // �s�� Shader Program

	//get compile errors
	i32 logLength = 0;
	glGetShaderiv(m_programId, GL_INFO_LOG_LENGTH, &logLength);
	if (logLength > 0)
	{
		std::vector<char> errorMessage(logLength + 1);
		glGetShaderInfoLog(m_programId, logLength, NULL, &errorMessage[0]);
		OGL3D_WARNING("OShaderProgram | " << &errorMessage[0]);
		return;
	}
}
