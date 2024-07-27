/**
 * @file ImGuiApp_Demo.cpp
 * @author n.a (na@mail.com)
 * @brief Definition of the application to run in the main function defined in the EntryPoint (EntryPoint.h)
 * @version 0.0.0
 * @date 2024-05-20
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "EntryPoint.h"
#include "App.h" 

#include "DemoApp.h"
#include "SampleLayers.h"
#include "OpenGLSampleLayer.h"

#include "IGA_Logger.h"

#include <string> 

/**
 * @brief Implementation of the CreateApp function for creating the static App class instance to run.
 * 
 * @param argc 
 * @param argv 
 * @return ImGuiApp::App* 
 */
ImGuiApp::App* ImGuiApp::CreateApp(int argc, char** argv)
{
	IGA_INFO( "[ImGuiApp] Sample info log");
	IGA_WARN( "[ImGuiApp] Sample warning log");
	IGA_ERROR("[ImGuiApp] Sample error log");
	ImGuiApp::AppSpecification spec;
	spec.Name = "ImGui App Example";

	//ImGuiApp::App* app = new ImGuiApp::App(spec);
	ImGuiApp::App* app = new ImGUIApp_Demo::DemoApp(spec);
    //app->PushLayer<ImGUIApp_Demo::ExampleLayer>(); 
    app->PushLayer<ImGUIApp_Demo::DemoWindowLayer>(); 
    app->PushLayer<ImGUIApp_Demo::ColorPickerLayer>(); 
    app->PushLayer<ImGUIApp_Demo::OpenGLSampleLayer>(); 
	app->SetMenubarCallback([app]()
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Exit"))
			{
				app->Close();
			}
			ImGui::EndMenu();
		}
	}); 
	return app;
} 