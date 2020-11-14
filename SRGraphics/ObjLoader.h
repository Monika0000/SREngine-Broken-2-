#pragma once
#include "Mesh.h"
#include <SRString.h>
#include <mutex>

namespace SpaRcle {
	using namespace Helper;
	namespace Graph {
		class ObjLoader {
		private:
			ObjLoader()  { };
			~ObjLoader() { };
		private:
			inline static std::mutex					m_mutex					= std::mutex();

			inline static unsigned long long			m_line_number			= 0;
			inline static std::string					m_current_object		= "";
			inline static std::vector<Mesh*>			m_temp_meshes			= std::vector<Mesh*>();

			inline static std::vector<Vertex>			m_temp_vertexes			= std::vector<Vertex>();
			inline static std::vector<unsigned int>		m_temp_indices			= std::vector<unsigned int>();

			inline static std::vector<glm::vec3>		m_pos_vertex			= std::vector<glm::vec3>();
			inline static std::vector<glm::vec2>		m_pos_texture			= std::vector<glm::vec2>();
			inline static std::vector<glm::vec3>		m_pos_normal			= std::vector<glm::vec3>();
		private:
			inline static bool							m_is_used				= false;
			inline static std::string					m_file_name				= "";
		private:
			static void AddMesh();
			static void Clear();
			static void ProcessFace(char** elems);
			static bool ProcessLine(char* line);
			static void ProcessFile(const char* data);
		public:
			static std::vector<Mesh*> Load(std::string name);
		};
	}
}

