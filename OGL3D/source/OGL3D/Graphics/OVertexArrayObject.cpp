#include <OGL3D/Graphics/OVertexArrayObject.h>
#include <glad/glad.h>

OVertexArrayObject::OVertexArrayObject(const OVertexBufferData& data)
{
	glGenBuffers(1, &m_vertexBufferId); //	�Ω�ͦ��@�ӽw�İϡ]Buffer Object�^�C�Ĥ@�ӰѼ� 1 ��ܭn�ͦ����w�İϼƶq�C�ĤG�ӰѼ� & m_vertexBufferId �O�s��ͦ����w�İ� ID �����СA�� ID �O�� OpenGL ���t���C


	glGenVertexArrays(1, &m_vertexArrayObjectId); //	�Ω�ͦ��@�ӳ��I�}�C����]Vertex Array Object, VAO�^�C�Ĥ@�ӰѼ� 1 ��ܭn�ͦ������I�}�C����ƶq�C�ĤG�ӰѼ� & m_vertexArrayObjectId �O�s��ͦ��� VAO ID �����СC
	glBindVertexArray(m_vertexArrayObjectId); //�j�w���e�ͦ������I�}�C����A�Ϩ䦨����e�� VAO�C�Ҧ����U�Ӫ����I�ݩʳ]�m�N���Ω�o�Ӹj�w�� VAO�C


	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferId); //	�\��G�j�w���w���w�İϡA�ϫ��򪺽w�İϾާ@���Ψ�o�Ӹj�w���w�İϡC�ѼơGGL_ARRAY_BUFFER�G���w�w�İ����������I�ƾڪ��w�İϡCm_vertexBufferId�G���e�ͦ����w�İ� ID�]�Ҧp�q�L glGenBuffers �ͦ��^�C
	glBufferData(GL_ARRAY_BUFFER, data.vertexSize * data.listSize, data.verticesList, GL_STATIC_DRAW); //	�\��G���j�w���w�İϤ��t�O����ô��ѼƾڡC	�ѼơGGL_ARRAY_BUFFER�G���w�ާ@���w�İ������]�P glBindBuffer �@�P�^�C		data.vertexSize* data.listSize�G���t���w�İϤj�p�A�q�`�O���I�j�p���H���I�ƶq�C		data.verticesList�G���V���I�ƾڪ����СCGL_STATIC_DRAW�G���w�ƾڪ��γ~�C		GL_STATIC_DRAW ��ܼƾڴX�G���|�Q���ܡA�D�n�Ω��R�A��V�C

	/*glVertexAttribPointer�\��
	�\��G�w�q���I�ƾڪ��榡�M�s�x���c�A�i�D OpenGL �p������j�w�����I�w�İϤ����ƾڡC
	�ѼơG
	0�G���w���I�ݩʪ����ޡ]location�^�C
	3�G�C�ӳ��I�ݩʥ� 3 �ӭȲզ��]�Ҧp x, y, z ���С^�C
	GL_FLOAT�G���I�ƾ������� float�C
	GL_FALSE�G���ݭn��ƾڶi���k�@�ơ]�ƾڤ��|�Q���Y�� [0,1] �� [-1,1] �d�򤺡^�C
	data.vertexSize�G�C�ӳ��I���r�`�j�p�A�Ω���w�U�@�ӳ��I�ƾڪ������q�]stride�^�C
	0�G���I�ƾڪ��_�l�����q�]offset�^�A��ܱq���I�ƾڪ��_�I�}�lŪ���C
	*/
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, data.vertexSize, 0);
	glEnableVertexAttribArray(0);  //�ҥι������ޡ]0�^�����I�ݩʼƾڡA�Ϩ�i�Ω����ø�s�ާ@


	glBindVertexArray(0); //�Ѱ��j�w���I�}�C����]VAO, Vertex Array Object�^

	m_vertexBufferData = data;
}

OVertexArrayObject::~OVertexArrayObject()
{
	/*
	�R���@�өΦh�ӽw�İϪ���C
	�Ĥ@�ӰѼ� 1 ��ܧR�����w�İϼƶq�C
	�ĤG�ӰѼƬO���V�n�R�����w�İ� ID �����СA�o�̬O m_vertexBufferId�C
	*/
	glDeleteBuffers(1, &m_vertexBufferId);
	/*
	�R���@�өΦh�ӳ��I�}�C���� (VAO)�C
	�Ĥ@�ӰѼ� 1 ��ܧR���� VAO �ƶq�C
	�ĤG�ӰѼƬO���V�n�R���� VAO ID �����СA�o�̬O m_vertexArrayObjectId�C
	*/
	glDeleteVertexArrays(1, &m_vertexArrayObjectId);
}

ui32 OVertexArrayObject::getId()
{
	return m_vertexArrayObjectId;
}

ui32 OVertexArrayObject::getVertexBufferSize()
{
	return m_vertexBufferData.listSize;
}

ui32 OVertexArrayObject::getVertexSize()
{
	return m_vertexBufferData.vertexSize;
}
