#include <OGL3D/Graphics/OGraphicsEngine.h>
#include <glad/glad.h>
#include <assert.h>
#include <stdexcept>





void OGraphicsEngine::clear(const OVec4& color)
{
	glClearColor(color.x, color.y, color.z, color.w);                                    //glClearColor 用於設置 OpenGL 畫面的清除顏色（背景顏色）。
	glClear(GL_COLOR_BUFFER_BIT);													     //glClear 清除指定的緩衝區內容, GL_COLOR_BUFFER_BIT：清除顏色緩衝區，重置畫面背景色。
}
