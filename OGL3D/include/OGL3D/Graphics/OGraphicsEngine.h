#pragma once
#include <OGL3D/OPrerequisites.h>
#include <OGL3D/Math/OVec4.h>
#include <OGL3D/Math/ORect.h>

class OGraphicsEngine
{
public:
	OGraphicsEngine();
	~OGraphicsEngine();
public:
	OVertexArrayObjectPtr createVertexArrayObject(const OVertexBufferDesc& data);   // �ŧi��ơA�Ыؤ@�� Vertex Array Object�A�ê�^�@�ӫ��V�������z����
	OShaderProgramPtr createShaderProgram(const OShaderProgramDesc& desc);          // �ŧi��ơA�Ыؤ@�� ShaderProgram�A�ê�^�@�ӫ��V�������z����
public:
	void clear(const OVec4& color);         //�ŧi�@�Ӧ������ clear,�Ω󱵦��@�� OVec4 ���O���`�q�ޥΰѼ�,�q�`�Ω�M���Y�ت��A�γ]�m�I���C�⪺���
	void setViewport(const ORect& size);    //�ŧi�@�Ӧ������ setViewport,�Ω󱵦��@�� ORect ���O���`�q�ޥΰѼ�,�q�`�Ω�]�mViewport�j�p�����
	void setVertexArrayObject(const OVertexArrayObjectPtr& vao);  // �]�w�Y�� Vertex Array Object �@����e�� VAO ���x�s��Y�Ӧ����ܼƤ�, �Ω�޲z VAO �����A�Τ����C
	void setShaderProgram(const OShaderProgramPtr& program);	  // �]�w�Y�� Shader Program �@����e�� Program ���x�s��Y�Ӧ����ܼƤ�, �Ω�޲z Shader Program �����A�Τ����C
	void drawTriangles(ui32 vertexCount, ui32 offset);         // ø�s�T���� vertexCount���I�ƶq offset���I���_�l��m,�q���ӳ��I�}�lø�s
};