#pragma once
#include <Debug.h>
#include <thread>

#include "Mesh.h"
#include <SafeArray.h>

namespace SpaRcle {
	using namespace Helper;
	namespace Graph {
		class ResourceManager {
		private:
			inline static size_t						m_count_meshes					= 0;
			inline static SafeArray<Mesh*>				m_meshes						= SafeArray<Mesh*>();

			inline static SafeArray<IResource*>			m_resources_to_destroy			= SafeArray<IResource*>();
		private:
			inline static volatile bool					m_isInit						= false;
			inline static volatile bool					m_isStop						= false;
			inline static std::thread					m_thread						= std::thread();
		private:
			static bool RemoveMesh(Mesh* mesh);

			static bool FreeResource(IResource* res);
			static void GC();
			static void Thread();
		public:
			static void Destroy(IResource* res);
		public:
			static std::vector<Mesh*> LoadObj(std::string name);
		public:
			static bool Init(std::string resource_folder);
			static bool Stop();
		};
	}
}

