#pragma once
#include "Render.h"
#include <WindowFormat.h>
#include "Camera.h"

#include "IFramework.h"

using namespace SpaRcle::Helper;

namespace SpaRcle {
	namespace Graph {
		class Window : private IFramework {
		private:
			FormatType				m_format					= FormatType::Unknown;
			Render*					m_render					= nullptr;
			Camera*					m_camera					= nullptr;
			bool					m_fullscreen				= false;
			bool					m_smooth_samples			= false;
			bool					m_vsync						= false;
			const char*				m_win_name					= "Unnamed";
			int						m_argcp						= 0;
			char*					m_argv						= nullptr;
		public:
			Window(
				const char*		win_name,
				int				argcp,
				char*			argv,
				Render*			render, 
				Camera*			camera,
				FormatType		format, 
				bool			vsync, 
				bool			fullscreen,
				unsigned char	smooth_samples = 4
			);
			~Window() { };
		public:
			bool Create();
			bool Init();
			bool Run();
			bool Close();
		};
	}
}

