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
	std::unique_ptr<OGraphicsEngine> m_graphicsEngine; //定義名為 m_graphicsEngine 指向 OGraphicsEngine 類型的智慧指針
	std::unique_ptr<OWindow> m_display;                //定義名為 m_display 指向 OWindow 類型的智慧指針, 來取代OWindow* m_display = nullptr



	OVertexArrayObjectPtr m_polygonVAO;                 //定義名為 m_polygonVAO 指向 OVertexArrayObject 類型的智慧指針
	OUniformBufferPtr m_uniform;                        //定義名為 m_uniform 指向 OUniformBuffer 類型的智慧指針
	OShaderProgramPtr m_shader; 					    //定義名為 m_shader 指向 OShaderProgram 類型的智慧指針

	std::chrono::system_clock::time_point m_previousTime; //定義名為 m_previousTime 的變數，類型為 std::chrono::system_clock::time_point
	f32 m_scale = 0;
};

