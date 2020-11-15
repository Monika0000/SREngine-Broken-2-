#pragma once
#include "Window.h"
#include "Render.h"

namespace SpaRcle {
	namespace Graph {
		class Window;

		class SRGraphics {
		private:
			inline static Window*				m_window		= nullptr;
		private:
			inline static volatile bool			m_IsCreate		= false;
			inline static volatile bool			m_IsInit		= false;
			inline static volatile bool			m_IsRun			= false;
			inline static volatile bool			m_IsClose		= false;
		public:
			static Window* GetMainWindow() noexcept { return m_window; }
		public:
			static bool Create(Window* window);
			static bool Init();
			static bool Run();
			static bool Close();
		};
	}
}

