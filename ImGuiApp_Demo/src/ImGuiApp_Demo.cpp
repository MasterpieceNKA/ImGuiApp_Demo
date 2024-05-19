#include "EntryPoint.h"
#include "App.h"  

class ExampleLayer : public ImGuiApp::Layer
{
public: 
	virtual void OnUIRender() override
	{
		ImGui::Begin("Hello");
		ImGui::Button("Button");
		ImGui::End();

		ImGui::ShowDemoWindow();
	}
};

ImGuiApp::App* ImGuiApp::CreateApp(int argc, char** argv)
{
	///*
	IGA_CORE_INFO("Info");
	IGA_CORE_WARN("Warn");
	IGA_CORE_ERROR("Error");

	IGA_INFO("Info");
	IGA_WARN("Warn");
	IGA_ERROR("Error");

	IGA_ASSERT(true, "Client assertion");
	IGA_CORE_ASSERT(false, "Core assertion"); 
	//*/

	ImGuiApp::AppSpecification spec;
	spec.Name = "ImGui App Example";

	ImGuiApp::App* app = new ImGuiApp::App(spec);
    app->PushLayer<ExampleLayer>(); 
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