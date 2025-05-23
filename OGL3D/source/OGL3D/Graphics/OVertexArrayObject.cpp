#include <OGL3D/Graphics/OVertexArrayObject.h>
#include <glad/glad.h>

OVertexArrayObject::OVertexArrayObject(const OVertexBufferDesc& vbDesc)
{
	if (!vbDesc.listSize) OGL3D_ERROR("OVertexArrayObject | listSize is NULL");
	if (!vbDesc.vertexSize) OGL3D_ERROR("OVertexArrayObject | vertexSize is NULL");
	if (!vbDesc.verticesList) OGL3D_ERROR("OVertexArrayObject | verticesList is NULL");

	glGenVertexArrays(1, &m_vertexArrayObjectId); //	用於生成一個頂點陣列物件（Vertex Array Object, VAO）。第一個參數 1 表示要生成的頂點陣列物件數量。第二個參數 & m_vertexArrayObjectId 是存放生成的 VAO ID 的指標。
	glBindVertexArray(m_vertexArrayObjectId); //綁定先前生成的頂點陣列物件，使其成為當前的 VAO。所有接下來的頂點屬性設置將應用於這個綁定的 VAO。

	glGenBuffers(1, &m_vertexBufferId); //	用於生成一個緩衝區（Buffer Object）。第一個參數 1 表示要生成的緩衝區數量。第二個參數 & m_vertexBufferId 是存放生成的緩衝區 ID 的指標，該 ID 是由 OpenGL 分配的。
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferId); //	功能：綁定指定的緩衝區，使後續的緩衝區操作應用到這個綁定的緩衝區。參數：GL_ARRAY_BUFFER：指定緩衝區類型為頂點數據的緩衝區。m_vertexBufferId：先前生成的緩衝區 ID（例如通過 glGenBuffers 生成）。
	glBufferData(GL_ARRAY_BUFFER, vbDesc.vertexSize * vbDesc.listSize, vbDesc.verticesList, GL_STATIC_DRAW); //	功能：為綁定的緩衝區分配記憶體並提供數據。	參數：GL_ARRAY_BUFFER：指定操作的緩衝區類型（與 glBindBuffer 一致）。		data.vertexSize* data.listSize：分配的緩衝區大小，通常是頂點大小乘以頂點數量。		data.verticesList：指向頂點數據的指標。GL_STATIC_DRAW：指定數據的用途。		GL_STATIC_DRAW 表示數據幾乎不會被改變，主要用於靜態渲染。

	for (ui32 i = 0; i < vbDesc.attributesListSize; i++)
	{
		/*glVertexAttribPointer功能
	功能：定義頂點數據的格式和存儲結構，告訴 OpenGL 如何解釋綁定的頂點緩衝區中的數據。
	參數：
	0：指定頂點屬性的索引（location）。
	3：每個頂點屬性由 3 個值組成（例如 x, y, z 坐標）。
	GL_FLOAT：頂點數據類型為 float。
	GL_FALSE：不需要對數據進行歸一化（數據不會被壓縮到 [0,1] 或 [-1,1] 範圍內）。
	data.vertexSize：每個頂點的字節大小，用於指定下一個頂點數據的偏移量（stride）。
	0：頂點數據的起始偏移量（offset），表示從頂點數據的起點開始讀取。
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, data.vertexSize, 0);
	*/
		glVertexAttribPointer(
			i,
			vbDesc.attributesList[i].numElements,
			GL_FLOAT,
			GL_FALSE,
			vbDesc.vertexSize,
			(void*)((i==0)?0: vbDesc.attributesList[i-1].numElements*sizeof(f32))
		);
		glEnableVertexAttribArray(i);  //啟用對應索引（0）的頂點屬性數據，使其可用於後續的繪製操作
	}

	glBindVertexArray(0); //解除綁定頂點陣列物件（VAO, Vertex Array Object）

	m_vertexBufferData = vbDesc;
}

OVertexArrayObject::OVertexArrayObject(const OVertexBufferDesc& vbDesc, const OIndexBufferDesc& ibDesc):OVertexArrayObject(vbDesc)
{
	if (!ibDesc.listSize) OGL3D_ERROR("OVertexArrayObject | listSize is NULL");
	if (!ibDesc.indicesList) OGL3D_ERROR("OVertexArrayObject | indicesList is NULL");

	glBindVertexArray(m_vertexArrayObjectId); //綁定先前生成的頂點陣列物件，使其成為當前的 VAO。所有接下來的頂點屬性設置將應用於這個綁定的 VAO。

	glGenBuffers(1, &m_elementBufferId); //	用於生成一個緩衝區（Buffer Object）。第一個參數 1 表示要生成的緩衝區數量。第二個參數 & m_vertexBufferId 是存放生成的緩衝區 ID 的指標，該 ID 是由 OpenGL 分配的。
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_elementBufferId); //	功能：綁定指定的緩衝區，使後續的緩衝區操作應用到這個綁定的緩衝區。參數：GL_ARRAY_BUFFER：指定緩衝區類型為頂點數據的緩衝區。m_vertexBufferId：先前生成的緩衝區 ID（例如通過 glGenBuffers 生成）。
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, ibDesc.listSize, ibDesc.indicesList, GL_STATIC_DRAW); //	功能：為綁定的緩衝區分配記憶體並提供數據。	參數：GL_ARRAY_BUFFER：指定操作的緩衝區類型（與 glBindBuffer 一致）。		data.vertexSize* data.listSize：分配的緩衝區大小，通常是頂點大小乘以頂點數量。		data.verticesList：指向頂點數據的指標。GL_STATIC_DRAW：指定數據的用途。		GL_STATIC_DRAW 表示數據幾乎不會被改變，主要用於靜態渲染。

	glBindVertexArray(0); //解除綁定頂點陣列物件（VAO, Vertex Array Object）
}

OVertexArrayObject::~OVertexArrayObject()
{
	glDeleteBuffers(1, &m_elementBufferId);
	glDeleteBuffers(1, &m_vertexBufferId);
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
