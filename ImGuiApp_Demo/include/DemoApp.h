#pragma once

#include "App.h"  

namespace ImGUIApp_Demo{
	class DemoApp : public ImGuiApp::App
	{
	public:
		DemoApp(const ImGuiApp::AppSpecification& appSpecification = ImGuiApp::AppSpecification()) 
		: ImGuiApp::App(appSpecification){
			m_Color = ImVec4(114.0f / 255.0f, 144.0f / 255.0f, 154.0f / 255.0f, 200.0f / 255.0f);
		};
    	~DemoApp() { };

		ImVec4 m_Color;

	};
};