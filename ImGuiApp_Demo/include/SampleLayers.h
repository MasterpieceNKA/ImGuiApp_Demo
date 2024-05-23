/**
 * @file SampleLayers.h
 * @author n.a (na@MasterpieceTechVideos.com)
 * @brief Defines sample ImGui frame Layer classes
 * @version 0.0.0
 * @date 2024-05-20
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#pragma once
#include <GL/glew.h> 
//#include <GLFW/glfw3.h>

#include "App.h"
#include "Layer.h"
#include "Logger.h"

#include "DemoApp.h"

#include <string>

#include "pbPlots.hpp"
#include "supportLib.hpp"

namespace ImGUIApp_Demo{
    /**
     * @brief Sample ImGui frame Layer object containing a Button
     * 
     */
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
    /**
     * @brief Sample ImGui frame Layer class for rendering the ImGui Demo Window
     * 
     */
    class DemoWindowLayer : public ImGuiApp::Layer
    {
    public: 
        virtual void OnUIRender() override
        {
            ImGui::ShowDemoWindow();
        }
    };
    /**
     * @brief Sample ImGui frame Layer class containing a colour picker for updating 
     * the m_Color variable of the DemoApp application instance.
     * 
     */
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
            ImGuiColorEditFlags flags = ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_AlphaBar;

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
    public:
        /// @brief Pointer to the DemoApp m_Color variable for updating the colour
        ImVec4* m_Color;
    };

}