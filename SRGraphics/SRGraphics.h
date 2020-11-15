#pragma once
#include "Window.h"
#include "Render.h"
#include "IFramework.h"

namespace SpaRcle {
	namespace Graph {
		class Window;

		class SRGraphics : private IFramework {
		private:
			SRGraphics() { };
			~SRGraphics() { };
		private:
			inline static Window*	m_window	= nullptr;
		public:
			static Window* GetMainWindow() noexcept { return m_window; }

			static bool IsRun() noexcept { return m_isRun; }
			static bool IsClose() noexcept { return m_isClose; }
		public:
			static bool Create(Window* window);
			static bool Init();
			static bool Run();
			static bool Close();
		};
	}
}

