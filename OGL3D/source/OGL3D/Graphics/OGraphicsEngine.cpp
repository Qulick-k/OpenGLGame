#include <OGL3D/Graphics/OGraphicsEngine.h>
#include <glad/glad.h>
#include <assert.h>
#include <stdexcept>





void OGraphicsEngine::clear(const OVec4& color)
{
	glClearColor(color.x, color.y, color.z, color.w);                                    //glClearColor �Ω�]�m OpenGL �e�����M���C��]�I���C��^�C
	glClear(GL_COLOR_BUFFER_BIT);													     //glClear �M�����w���w�İϤ��e, GL_COLOR_BUFFER_BIT�G�M���C��w�İϡA���m�e���I����C
}
