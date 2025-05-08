#pragma once
#include <memory>
#include <OGL3D/Graphics/OGraphicsEngine.h>
#include <chrono>

//class OGraphicsEngine;
class OWindow;
class OGame
{
public:
	OGame();
	~OGame();

	virtual void onCreate();
	virtual void onUpdate();
	virtual void onQuit();

	void run();
	void quit();
protected:
	bool m_isRunning = true;
	std::unique_ptr<OGraphicsEngine> m_graphicsEngine; //�w�q�W�� m_graphicsEngine ���V OGraphicsEngine ���������z���w
	std::unique_ptr<OWindow> m_display;                //�w�q�W�� m_display ���V OWindow ���������z���w, �Ө��NOWindow* m_display = nullptr



	OVertexArrayObjectPtr m_polygonVAO;                 //�w�q�W�� m_polygonVAO ���V OVertexArrayObject ���������z���w
	OUniformBufferPtr m_uniform;                        //�w�q�W�� m_uniform ���V OUniformBuffer ���������z���w
	OShaderProgramPtr m_shader; 					    //�w�q�W�� m_shader ���V OShaderProgram ���������z���w

	std::chrono::system_clock::time_point m_previousTime; //�w�q�W�� m_previousTime ���ܼơA������ std::chrono::system_clock::time_point
	f32 m_scale = 0;
};

