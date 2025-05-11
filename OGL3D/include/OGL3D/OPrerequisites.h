#pragma once
#include <memory>                                                     // �ޤJ���Y�ɡA���� std::shared_ptr ���z���Ъ��\��
#include <sstream>												      // �ޤJ���Y�ɡA���� std::stringstream ���\��
#include <iostream>													  // �ޤJ���Y�ɡA���� std::cout ���\��
#include <stdexcept>												  // �ޤJ���Y�ɡA���� std::runtime_error ���\��

class OVertexArrayObject; 										      // �e�m�ŧi (Forward Declaration)�A�i�D�sĶ�� OVertexArrayObject ���O�|�b�᭱�w�q
class OUniformBuffer; 										          // �e�m�ŧi (Forward Declaration)�A�i�D�sĶ�� OUniformBuffer ���O�|�b�᭱�w�q
class OShaderProgram;                                                 // �e�m�ŧi (Forward Declaration)�A�i�D�sĶ�� OVertexArrayObject ���O�|�b�᭱�w�q�A�w�q�@��shared pointer for the shader
/*
�w�q�@�ӫ��O�O�W OVertexArrayObjectPtr�G
�ϥ� std::shared_ptr �ʸ����O OVertexArrayObject �����z���СC
std::shared_ptr �O C++11 �ޤJ���@�ش��z���СA�Ω�۰ʺ޲z���󪺰O����ͩR�g���C
��̫�@�� std::shared_ptr ���V������Q�P���ɡA����|�۰�����C
*/
typedef std::shared_ptr<OVertexArrayObject> OVertexArrayObjectPtr;
typedef std::shared_ptr<OUniformBuffer> OUniformBufferPtr;            //�w�q�@��shared pointer for the uniform buffer
typedef std::shared_ptr<OShaderProgram> OShaderProgramPtr;            //�w�q�@��shared pointer for the shader

typedef float f32;          // �O�W f32 ����L�}�o�̩��T���D�o�O 32 �쪺�B�I��
typedef int i32;            // �O�W i32 ����L�}�o�̩��T���D�o�O 32 �쪺���
typedef unsigned int ui32;  // �O�W ui32 ����L�}�o�̩��T���D�o�O 32 �쪺�L�Ÿ����


struct OVertexAttribute
{
	ui32 numElements = 0;  //�����ƶq
};

struct  OVertexBufferDesc
{
	void* verticesList = nullptr;		  //���V���I��ƪ�����,void* �x�����Хi�H���V���N���������, nullptr ��l�ɨS�����V������
	ui32 vertexSize = 0;                  //�C�ӳ��I���j�p�]�H�줸�լ����^
	ui32 listSize = 0; 				      //���I�C���������ƶq

	OVertexAttribute* attributesList = nullptr;  //���V���I�ݩʪ�����
	ui32 attributesListSize = 0;                      //���I�ݩʪ��ƶq
};

struct  OIndexBufferDesc
{
	void* indicesList = nullptr;		  //���V���I��ƪ�����,void* �x�����Хi�H���V���N���������, nullptr ��l�ɨS�����V������
	ui32 listSize = 0; 				      //���I�C���������ƶq
};

struct OShaderProgramDesc
{
	const wchar_t* vertexShaderFilePath;		 //���I�ۦ⾹
	const wchar_t* fragmentShaderFilePath;       //���q�ۦ⾹
};

struct OUniformBufferDesc
{
	ui32 size = 0;
};

enum class OTriangleType
{
	TriangleList = 0,	//�T���ΦC��
	TriangleStrip 		//�T���αa
};

enum class OCullType
{
	BackFace = 0,    //�I���簣
	FrontFace,     //�����簣
	Both      //�����簣
};

enum class OWindingOrder
{
	ClockWise = 0, //���ɰw
	CounterClockWise //�f�ɰw
};

enum class OShaderType
{
	VertexShader =0,
	FragmentShader
};

#define OGL3D_ERROR(message)\
{\
std::stringstream m;\
m << "OGL3D Error: " << message << std::endl;\
throw std::runtime_error(m.str());\
}

#define OGL3D_WARNING(message)\
std::wclog << "OGL3D Warning: " << message << std::endl;

#define OGL3D_INFO(message)\
std::wclog << "OGL3D Info: " << message << std::endl;