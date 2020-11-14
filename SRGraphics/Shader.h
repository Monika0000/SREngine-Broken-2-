#pragma once
#include <iostream>
#include <string>
#include <vector>

namespace SpaRcle {
	namespace Graph {
		class Render;

		class Shader {
		public:
			Shader(Render* render, std::string name);
			~Shader();
		public:
			Render* GetRender() const noexcept { return m_render; };
		private:
			Render*			m_render	= nullptr;
			std::string		m_name		= "Unnamed";
		};
	}
}

