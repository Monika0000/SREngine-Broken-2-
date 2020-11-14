#pragma once
#include "IResource.h"
#include "Component.h"
#include "Vertex.h"
#include "Shader.h"

namespace SpaRcle {
	namespace Graph {
		class ResourceManager;
		class Render;
		class Material;

		class Mesh : public IResource, public Component {
			friend class ResourceManager;
		public:
			Mesh(Shader* shader, Material* material, std::string name = "Unnamed");
			/* call only from GC */
			~Mesh();
			Mesh* Copy();
		private:
			Material*					m_material				= nullptr;
			Render*						m_render				= nullptr;
			Shader*						m_shader				= nullptr;
			std::vector<Vertex>			m_vertices				= std::vector<Vertex>();
			size_t						m_count_vertices		= 0;
		public:
			const size_t GetCountVertices() const noexcept { return m_count_vertices; }
			void SetVertexArray(const std::vector<Vertex>& vertices);
		public:
			bool Destroy() override;
		};
	}
}

