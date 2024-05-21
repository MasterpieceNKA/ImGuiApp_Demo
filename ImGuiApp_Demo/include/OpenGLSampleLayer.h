/**
 * @file OpenGLSampleLayer.h
 * @author n.a (na@MasterpieceTechVideos.com)
 * @brief Defines class for an OpenGL ImGui frame Layer
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

namespace ImGUIApp_Demo{
    /**
     * @brief Layer class definition of a simple ImGui frame that acts as an OpenGL window
     * 
     */
    class OpenGLSampleLayer : public ImGuiApp::Layer
    {
    public:  
        /**
         * @brief Called after object has been added to m_LayerStack 
         * of the App application instance. Creates triangle indices,
         * shaders and buffers needed to render the OpenGL window.
         * 
         */
        virtual void OnAttach() override
        {
            ImGUIApp_Demo::DemoApp& m_App = static_cast<ImGUIApp_Demo::DemoApp&> (ImGuiApp::App::Get());
            //ImGUIApp_Demo::DemoApp& m_App = (ImGUIApp_Demo::DemoApp&) ImGuiApp::App::Get();
            m_Color  = &m_App.m_Color;
            create_triangle();
	        create_shaders();
	        create_framebuffer();
        }
        /**
         * @brief Called when the App application instance is shutting down. 
         * Deletes the OpenGL buffers and textures being used.
         * 
         */
        virtual void OnDetach() override
        {
            glDeleteFramebuffers(1, &FBO);
            glDeleteTextures(1, &texture_id);
            glDeleteRenderbuffers(1, &RBO);
        } 
        /**
         * @brief Called in the render loop within the ImGui::NewFrame(); and ImGui::End(); lines
         * to render ImGui frame items. Draws texture on the ImGui frame Layer on which OpenGL shaders will render the 
         * image.
         * 
         */
        virtual void OnUIRender() override
        {
            ImGui::Begin("OpenGL"); 
            const float window_width = ImGui::GetContentRegionAvail().x;
		    const float window_height = ImGui::GetContentRegionAvail().y;
            
            rescale_framebuffer(window_width, window_height);
            glViewport(0, 0, window_width, window_height);

            ImVec2 pos = ImGui::GetCursorScreenPos();
            
            ImGui::GetWindowDrawList()->AddImage(
                (void *)texture_id, 
                ImVec2(pos.x, pos.y), 
                ImVec2(pos.x + window_width, pos.y + window_height), 
                ImVec2(0, 1), 
                ImVec2(1, 0)
            );

            ImGui::End();         
        }
        /**
         * @brief Called after rendering loop ImGui frame items i.e. after ImGui::Render(); line.
         * Binds buffers and uses defined shaders to render the OpenGL output.
         * 
         */
        virtual void OnPostUIRender() override
        {
            bind_framebuffer();
		
            glUseProgram(shader);

            int vertexColorLocation = glGetUniformLocation(shader, "vertexColor"); 
            glUniform4f(vertexColorLocation, m_Color->x, m_Color->y, m_Color->z, m_Color->w);

            glBindVertexArray(VAO);
            glDrawArrays(GL_TRIANGLES, 0, 3);
            glBindVertexArray(0);
            glUseProgram(0);
            
            unbind_framebuffer();	
        }
    public:
        /**
         * @brief Pointer to the DemoApp m_Color variable for updating the colour of the 
         * triangle to be rendered. Updated by ColorPickerLayer.
        */
        ImVec4* m_Color; 
    private: 
        const GLint WIDTH = 400;
        const GLint HEIGHT = 300;

        GLuint VAO;
        GLuint VBO;
        GLuint FBO;
        GLuint RBO;
        GLuint texture_id;
        GLuint shader;

        const char* vertex_shader_code = R"*(
        #version 330

        layout (location = 0) in vec3 pos; 

        void main()
        {
            gl_Position = vec4(0.9*pos.x, 0.9*pos.y, 0.5*pos.z, 1.0);
        }
        )*";

        const char* fragment_shader_code = R"*(
        #version 330

        uniform vec4 vertexColor;
        out vec4 color;

        void main()
        {
            color = vertexColor;
        }
        )*";

        void create_triangle()
        {
            GLfloat vertices[] = {
                -1.0f, -1.0f, 0.0f, // 1. vertex x, y, z
                1.0f, -1.0f, 0.0f, // 2. vertex ...
                0.0f, 1.0f, 0.0f // etc... 
            };

            glGenVertexArrays(1, &VAO);
            glBindVertexArray(VAO);

            glGenBuffers(1, &VBO);
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
            glEnableVertexAttribArray(0);

            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindVertexArray(0);
        }

        void add_shader(GLuint program, const char* shader_code, GLenum type) 
        {
            GLuint current_shader = glCreateShader(type);

            const GLchar* code[1];
            code[0] = shader_code;

            GLint code_length[1];
            code_length[0] = strlen(shader_code);

            glShaderSource(current_shader, 1, code, code_length);
            glCompileShader(current_shader);

            GLint result = 0;
            GLchar log[1024] = {0};

            glGetShaderiv(current_shader, GL_COMPILE_STATUS, &result);
            if (!result) {
                glGetShaderInfoLog(current_shader, sizeof(log), NULL, log);
                IGA_ERROR("Error compiling " + std::to_string(type) + " shader. ");//+std::to_string(log));
                return;
            }

            glAttachShader(program, current_shader);
        }

        void create_shaders()
        {
            shader = glCreateProgram();
            if(!shader) {
                IGA_ERROR("Error creating shader program!"); 
                exit(1);
            }

            add_shader(shader, vertex_shader_code, GL_VERTEX_SHADER);
            add_shader(shader, fragment_shader_code, GL_FRAGMENT_SHADER);

            GLint result = 0;
            GLchar log[1024] = {0};

            glLinkProgram(shader);
            glGetProgramiv(shader, GL_LINK_STATUS, &result);
            if (!result) {
                glGetProgramInfoLog(shader, sizeof(log), NULL, log);
                IGA_ERROR("Error linking program: ");// + std::to_string(log )+"");
                return;
            }

            glValidateProgram(shader);
            glGetProgramiv(shader, GL_VALIDATE_STATUS, &result);
            if (!result) {
                glGetProgramInfoLog(shader, sizeof(log), NULL, log);
                IGA_ERROR("Error validating program: ");// + std::to_string(log)+"");
                return;
            }
        }

        void create_framebuffer()
        {
            glGenFramebuffers(1, &FBO);
            glBindFramebuffer(GL_FRAMEBUFFER, FBO);

            glGenTextures(1, &texture_id);
            glBindTexture(GL_TEXTURE_2D, texture_id);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, WIDTH, HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture_id, 0);

            glGenRenderbuffers(1, &RBO);
            glBindRenderbuffer(GL_RENDERBUFFER, RBO);
            glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, WIDTH, HEIGHT);
            glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO);

            if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
                IGA_ERROR("ERROR::FRAMEBUFFER:: Framebuffer is not complete!");

            glBindFramebuffer(GL_FRAMEBUFFER, 0);
            glBindTexture(GL_TEXTURE_2D, 0);
            glBindRenderbuffer(GL_RENDERBUFFER, 0);
        }

        void bind_framebuffer()
        {
            glBindFramebuffer(GL_FRAMEBUFFER, FBO);
        }

        void unbind_framebuffer()
        {
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
        }

        void rescale_framebuffer(float width, float height)
        {
            glBindTexture(GL_TEXTURE_2D, texture_id);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture_id, 0);

            glBindRenderbuffer(GL_RENDERBUFFER, RBO);
            glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
            glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO);
        }

    };

   
}