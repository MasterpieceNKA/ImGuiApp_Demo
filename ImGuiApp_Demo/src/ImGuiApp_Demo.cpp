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
	ImGuiApp::AppSpecification spec;
	spec.Name = "ImGui App Example";

	ImGuiApp::App* app = new ImGuiApp::App(spec);
    //ExampleLayer exampleLayer = ExampleLayer();
    //const std::shared_ptr<ExampleLayer> exampleLayer;
	///*
    app->PushLayer<ExampleLayer>();
    //app->PushLayer(exampleLayer);
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
    //*/
	return app;
} 