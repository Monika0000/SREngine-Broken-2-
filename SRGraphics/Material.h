#pragma once
#include "IResource.h"
#include "Texture.h"

namespace SpaRcle {
	namespace Graph {
		class Mesh;
		
		class Material {
		public:
			Material(Texture* diffuse, Texture* normal, Texture* specular, Texture* glossiness, bool isTransparent, bool isDefault);
			~Material();
		public:
			bool SetMesh(Mesh* mesh);
			Material* Copy();
		private:
			const bool		m_isDefault			= false;
			const bool		m_isTransparent		= false;
			Mesh*			m_mesh				= nullptr;
		private:
			Texture*		m_diffuse			= nullptr;
			Texture*		m_normal			= nullptr;
			Texture*		m_specular			= nullptr;
			Texture*		m_glossiness		= nullptr;
		};
	}
}
