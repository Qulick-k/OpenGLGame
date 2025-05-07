#include <OGL3D/Graphics/OShaderProgram.h>
#include <glad/glad.h>
#include <fstream>    //引用fstream，為了調用Input File Stream
#include <sstream>    //in order to extract the file, include sstream
#include <string>     //儲存shader code在string中
#include <vector>     //動態陣列（Dynamic Array）
#include <filesystem>

OShaderProgram::OShaderProgram(const OShaderProgramDesc& desc)
{
	m_programId = glCreateProgram();	// 創建 Shader Program
	attach(desc.vertexShaderFilePath, VertexShader);          //call attach編譯vertex shader
	attach(desc.fragmentShaderFilePath, FragmentShader);      //call attach編譯fragment shader
	link();	// 連接 Shader Program
}

OShaderProgram::~OShaderProgram()
{
	for (ui32 i = 0; i < 2; i++)
	{
		glDetachShader(m_programId, m_attachedShaders[i]);  // 將 Shader 從 Shader Program 中分離
		glDeleteShader(m_attachedShaders[i]);              	// 刪除 Shader
	}
	glDeleteProgram(m_programId);	    // 刪除 Shader Program
}

ui32 OShaderProgram::getId()
{
	return m_programId;
}

void OShaderProgram::attach(const wchar_t* shaderFilePath, const OShaderType& type)
{
	std::string shaderCode;	                    // 儲存 Shader Code
	
	auto path = std::filesystem::path(shaderFilePath);

	std::ifstream shaderStream(path);	// 讀取 Shader 檔案
	if (shaderStream.is_open())
	{		
		std::stringstream sstr;
		sstr << shaderStream.rdbuf();	// sstr 將包含 shaderStream 所有的數據
		shaderCode = sstr.str();		// 將 sstr 轉換為 string
		shaderStream.close();			// 儲存到string後，關閉檔案
	}
	else
	{
		OGL3D_WARNING("OShaderProgram | " << shaderFilePath << "not found");	// 如果檔案不存在，輸出警告
		return;
	}

	ui32 shaderId = 0;                  //儲存Shader ID

	//根據 type 的值，決定創建哪種類型的著色器
	if (type == VertexShader)
		shaderId = glCreateShader(GL_VERTEX_SHADER);
	else if (type == FragmentShader)
		shaderId = glCreateShader(GL_FRAGMENT_SHADER);

	auto sourcePointer = shaderCode.c_str();	                //將 shader code 轉換為 const char* 類型
	glShaderSource(shaderId, 1, &sourcePointer, NULL);	        //將 shader code 設置到 shader 物件中
	glCompileShader(shaderId);	                                //編譯 shader 物件


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


	glAttachShader(m_programId, shaderId);	                    //將 shader 物件附加到 Shader Program 中 .AKA 將一個著色器 (Shader) 附加到指定的程式對象 (Program Object)
	m_attachedShaders[type] = shaderId;	                        //將 shader ID 儲存到 m_attachedShader 中

	OGL3D_INFO("OShaderProgram | " << shaderFilePath << "compiled successfully");	//輸出編譯成功的訊息
}

void OShaderProgram::link()
{
	glLinkProgram(m_programId);	                                // 連接 Shader Program

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
