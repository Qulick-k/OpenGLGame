#pragma once
#include <memory>                                                     // �ޤJ���Y�ɡA���� std::shared_ptr ���z���Ъ��\��

class OVertexArrayObject; 										      // �e�m�ŧi (Forward Declaration)�A�i�D�sĶ�� OVertexArrayObject ���O�|�b�᭱�w�q

/*
�w�q�@�ӫ��O�O�W OVertexArrayObjectPtr�G
�ϥ� std::shared_ptr �ʸ����O OVertexArrayObject �����z���СC
std::shared_ptr �O C++11 �ޤJ���@�ش��z���СA�Ω�۰ʺ޲z���󪺰O����ͩR�g���C
��̫�@�� std::shared_ptr ���V������Q�P���ɡA����|�۰�����C
*/
typedef std::shared_ptr<OVertexArrayObject> OVertexArrayObjectPtr;

typedef float f32;          // �O�W f32 ����L�}�o�̩��T���D�o�O 32 �쪺�B�I��
typedef int i32;            // �O�W i32 ����L�}�o�̩��T���D�o�O 32 �쪺���
typedef unsigned int ui32;  // �O�W ui32 ����L�}�o�̩��T���D�o�O 32 �쪺�L�Ÿ����


struct  OVertexBufferData
{
	void* verticesList = nullptr;		  //���V���I��ƪ�����,void* �x�����Хi�H���V���N���������, nullptr ��l�ɨS�����V������
	ui32 vertexSize = 0;                  //�C�ӳ��I���j�p�]�H�줸�լ����^
	ui32 listSize = 0; 				      //���I�C���������ƶq
};