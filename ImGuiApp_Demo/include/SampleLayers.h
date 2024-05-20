#pragma once
#include <GL/glew.h> 
//#include <GLFW/glfw3.h>

#include "App.h"
#include "Layer.h"
#include "Logger.h"

#include "DemoApp.h"

#include <string>

namespace ImGUIApp_Demo{
    class ExampleLayer : public ImGuiApp::Layer
    {
    public: 
        virtual void OnUIRender() override
        {
            ImGui::Begin("Hello"); 
            ImGui::Button("Button");
            ImGui::End(); 
        }
    };
    
    class DemoWindowLayer : public ImGuiApp::Layer
    {
    public: 
        virtual void OnUIRender() override
        {
            ImGui::ShowDemoWindow();
        }
    };
    class ColorPickerLayer : public ImGuiApp::Layer
    {
    public: 
        virtual void OnAttach() {
            ImGUIApp_Demo::DemoApp& m_App = static_cast<ImGUIApp_Demo::DemoApp&> (ImGuiApp::App::Get());
            //ImGUIApp_Demo::DemoApp& m_App = (ImGUIApp_Demo::DemoApp&) ImGuiApp::App::Get();
            m_Color  = &m_App.m_Color;
        }

        virtual void OnUIRender() override
        {
            ImGui::Begin("ImGuiApp Color Picker"); 
            /*
            ImGuiColorEditFlags flags = ImGuiColorEditFlags_PickerHueWheel | 
                                        ImGuiColorEditFlags_NoSidePreview | 
                                        ImGuiColorEditFlags_NoInputs | 
                                        ImGuiColorEditFlags_NoAlpha;
            //*/
            ///*
            ImGuiColorEditFlags flags = ImGuiColorEditFlags_PickerHueWheel;

            ImGui::ColorPicker3("##MyColor##6", (float*)m_Color, flags);
            //*/

            /*
            float w = (ImGui::GetContentRegionAvail().x - ImGui::GetStyle().ItemSpacing.y) * 0.40f;
            ImGui::SetNextItemWidth(w);
            ImGui::ColorPicker3("##MyColor##5", (float*)m_Color, ImGuiColorEditFlags_PickerHueBar | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoAlpha);
            ImGui::SameLine();
            ImGui::SetNextItemWidth(w);
            ImGui::ColorPicker3("##MyColor##6", (float*)m_Color, ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoAlpha);
            //*/

            ImGui::End(); 
        }
    private:
        ImVec4* m_Color;// = ImVec4(114.0f / 255.0f, 144.0f / 255.0f, 154.0f / 255.0f, 200.0f / 255.0f);
        //ImGUIApp_Demo::DemoApp& m_App;
    };

}