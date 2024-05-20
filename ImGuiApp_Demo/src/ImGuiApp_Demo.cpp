#include "EntryPoint.h"
#include "App.h" 

#include "DemoApp.h"
#include "SampleLayers.h"
#include "OpenGLSampleLayer.h"

#include <string> 

ImGuiApp::App* ImGuiApp::CreateApp(int argc, char** argv)
{
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