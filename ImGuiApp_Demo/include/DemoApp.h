/**
 * @file DemoApp.h
 * @author n.a (na@MasterpieceTechVideos.com)
 * @brief Defines the DemoApp class which extends the ImGuiApp::App for defining the application to run
 * @version 0.0.0
 * @date 2024-05-20
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#pragma once

#include "App.h"  

namespace ImGUIApp_Demo{
	/**
	 * @brief Class definition for DemoApp which extends the ImGuiApp::App for defining the application to run
	 * 
	 */
	class DemoApp : public ImGuiApp::App
	{
	public:
		/**
		 * @brief Construct a new Demo App object which calls the App super class and initialises the m_Color variable
		 * 
		 * @param appSpecification 
		 */
		DemoApp(const ImGuiApp::AppSpecification& appSpecification = ImGuiApp::AppSpecification()) 
		: ImGuiApp::App(appSpecification){
			m_Color = ImVec4(94.0f / 255.0f, 193.0f / 255.0f, 22.0f / 255.0f, 255.0f / 255.0f);
		};
		/**
		 * @brief Destroy the Demo App object
		 * 
		 */
    	~DemoApp() { };
		
		/**
		 * @brief variable to store color set by the ColorPickerLayer color picker ImGui frame 
		 * and used by the OpenGLSampleLayer ImGui frame. Demonstrates sharing of variables.
		*/
		ImVec4 m_Color;

	};
};