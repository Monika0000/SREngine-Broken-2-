#pragma once
#define GLEW_STATIC
#define NOMINMAX
#define _CRT_SECURE_NO_WARNINGS

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <Windows.h>
#include <thread>
#include <string>

#include <glm/matrix.hpp>
#include <glm\ext\matrix_transform.hpp>

namespace SpaRcle {
	namespace Graph {
		class Render;

		/* All functions need call from OpenGL context */
		class Shader {
		public:
			Shader(Render* render, std::string name);
			~Shader();
		public:
			Render* GetRender() const noexcept { return m_render; };
			GLuint GetID() const noexcept { return m_ID; };
		private:
			Render*			m_render		= nullptr;
			std::string		m_name			= "Unnamed";

			GLuint			m_ID			= 0;

			bool			m_isLink		= false;
			bool			m_isCompile		= false;
			bool			m_isDestroy		= false;
		public:
			bool Link();
			bool Compile();

			bool Use();
			bool Destroy();
		};
	}
}

