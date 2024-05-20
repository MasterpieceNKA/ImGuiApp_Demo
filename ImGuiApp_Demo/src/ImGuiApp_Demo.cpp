#include "EntryPoint.h"
#include "App.h" 
#include "OpenGLSampleLayer.h"

#include <string> 

class ExampleLayer : public ImGuiApp::Layer
{
public: 
	virtual void OnUIRender() override
	{
		//ImGui::Begin("Hello"); 
		//ImGui::Button("Button");
		//ImGui::End();

		ImGui::ShowDemoWindow();
	}
};

namespace ImGUIApp_Demo{
	class DemoApp : public ImGuiApp::App
	{
	public:
		DemoApp(const ImGuiApp::AppSpecification& appSpecification = ImGuiApp::AppSpecification()) 
		: ImGuiApp::App(appSpecification){};
    	~DemoApp() { };

	};
};

ImGuiApp::App* ImGuiApp::CreateApp(int argc, char** argv)
{
	//IGA_CORE_INFO("Info");
	//IGA_CORE_WARN("Warn");
	//IGA_CORE_ERROR("Error");

	//IGA_INFO("Info");
	//IGA_WARN("Warn");
	//IGA_ERROR("Error");

	//IGA_CORE_ASSERT(false); 
	//IGA_ASSERT(false);   

	ImGuiApp::AppSpecification spec;
	spec.Name = "ImGui App Example";

	//ImGuiApp::App* app = new ImGuiApp::App(spec);
	ImGuiApp::App* app = new ImGUIApp_Demo::DemoApp(spec);
    app->PushLayer<ExampleLayer>(); 
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