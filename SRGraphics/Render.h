#pragma once
#include "Mesh.h"
#include "Texture.h"
#include "ResourceManager.h"

#include "IFramework.h"

#include "Shader.h"

namespace SpaRcle {
	namespace Graph {
		class Window;
		class Camera;

		class Render : private IFramework {
		public:
			Render();
			~Render();
		private:
			Shader*			m_geometryShader			= nullptr;
			Shader*			m_postProcessingShader		= nullptr;
			Shader*			m_SkyboxShader				= nullptr;
		private:
			Window*			m_window					= nullptr;
			Camera*			m_camera					= nullptr;
		public:
			bool Create(Window* window, Camera* camera);
			bool Init();
			bool Run();
			
			/* Call only from OpenGL context */
			bool Close();
		public:
			void DrawGeometry();
			void DrawTransparentGeometry();
			void DrawSkybox();
			void DrawGUI();
		};
	}
}

