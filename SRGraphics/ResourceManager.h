#pragma once
#include <Debug.h>
#include <thread>

#include "Mesh.h"
#include <SafeArray.h>
#include <SafeDictionary.h>
#include <WindowFormat.h>
#include "Shader.h"
#include "Texture.h"

namespace SpaRcle {
	using namespace Helper;
	namespace Graph {
		class ResourceManager {
		private:
			inline static size_t									m_count_meshes					= 0;
			inline static SafeArray<Mesh*>							m_meshes						= SafeArray<Mesh*>();

			inline static size_t									m_count_textures				= 0;
			inline static SafeArray<Texture*>						m_textures						= SafeArray<Texture*>();

			inline static SafeArray<IResource*>						m_resources_to_destroy			= SafeArray<IResource*>();

			inline static Shader*									m_default_geometry_shader		= nullptr;
			inline static std::string								m_resource_folder				= "DirNotSelected";
		private:
			inline static volatile bool								m_isInit						= false;
			inline static volatile bool								m_isStop						= false;
			inline static std::thread								m_thread						= std::thread();
			inline static std::mutex								m_mutex							= std::mutex();
		private:
			static bool Remove(Mesh* mesh);
			static bool Remove(Texture* texture);

			static bool FreeResource(IResource* res);
			static void GC();
			static void Thread();
		public:
			static void Destroy(IResource* res);
		public:
			static void SetDefaultGeometryShader(Shader* shader) noexcept;
			static Shader* GetDefaultGeometryShader() noexcept;

			static std::string GetResourceFolder() noexcept;
		public:
			static std::vector<Mesh*> LoadModel(std::string name);
			static Texture* LoadTexture(std::string name, 
				Texture::Type type					= Texture::Type::Diffuse, 
				Texture::Filter filter				= Texture::Filter::NEAREST,
				Texture::CompressedLevel compress	= Texture::CompressedLevel::None
			);
		public:
			static bool Init(std::string resource_folder);
			static bool Stop();

			static void PrintMemoryDump();
			static void PrintTexturesDump();
		};
	}
}

