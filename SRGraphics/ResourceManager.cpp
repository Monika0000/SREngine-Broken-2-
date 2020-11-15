#include "pch.h"
#include <iostream>
#include "ResourceManager.h"
#include "ObjLoader.h"
#include "Image.h"

using namespace SpaRcle::Helper;
using namespace SpaRcle::Graph;

bool SpaRcle::Graph::ResourceManager::Remove(Mesh* mesh) {
	for (size_t t = 0; t < m_count_meshes; t++) {
		if (m_meshes[t] == mesh) {
			m_meshes.Remove(t);
			m_count_meshes--;
			delete mesh;
			return true;
		} 
	}

	return false;
}
bool SpaRcle::Graph::ResourceManager::Remove(Texture* texture) {
	for (size_t t = 0; t < m_count_textures; t++) {
		if (m_textures[t] == texture) {
			m_textures.Remove(t);
			m_count_textures--;
			delete texture;
			return true;
		}
	}

	return false;
}

bool SpaRcle::Graph::ResourceManager::FreeResource(IResource* res) {
	if (res->GetResourceName() == "Mesh") {
		if (!Remove(static_cast<Mesh*>(res))) {
			Debug::Error("ResourceManager::FreeResource() : failed remove \"" + res->m_res_id + "\" mesh!");
			Sleep(1);
			return false;
		}
	} else 
	if (res->GetResourceName() == "Texture") {
		if (!Remove(static_cast<Texture*>(res))) {
			Debug::Error("ResourceManager::FreeResource() : failed remove \"" + res->m_res_id + "\" texture!");

			PrintTexturesDump();

			Sleep(1);
			return false;
		}
	}
	else
		return false;

	return true;
}

void SpaRcle::Graph::ResourceManager::GC() {
	for (size_t t = 0; t < m_resources_to_destroy.Size(); t++) {
		if (m_resources_to_destroy[t]->m_CountUses == 0) {
			if (Debug::GetLevel() >= Debug::Level::High)
				Debug::Log("ResourceManager::GC() : free \"" + std::string(m_resources_to_destroy[t]->m_res_name) + "\" resource...");

			if (!FreeResource(m_resources_to_destroy[t])) {
				Debug::Error("ResourceManager::GC() : failed free \"" + std::string(m_resources_to_destroy[t]->m_res_name) + "\" resource!");
				Sleep(1);
			} 

			m_resources_to_destroy.Remove(t);
		}
	}
}

void SpaRcle::Graph::ResourceManager::Thread() {
	while (m_isInit) {
		m_mutex.lock();
		GC();
		m_mutex.unlock();
	}
}

void SpaRcle::Graph::ResourceManager::Destroy(IResource* res) {
	if (Debug::GetLevel() >= Debug::Level::High)
		Debug::Log("ResourceManager::Destroy() : add resource to destroy...");

	m_resources_to_destroy.Add(res);
}

void SpaRcle::Graph::ResourceManager::SetDefaultGeometryShader(Shader* shader) noexcept { m_default_geometry_shader = shader; }
Shader* SpaRcle::Graph::ResourceManager::GetDefaultGeometryShader() noexcept { return m_default_geometry_shader; }

std::string SpaRcle::Graph::ResourceManager::GetResourceFolder() noexcept { return m_resource_folder; }


std::vector<Mesh*> SpaRcle::Graph::ResourceManager::LoadModel(std::string name) {
	m_mutex.lock();

	std::string path = SRString::MakePath(m_resource_folder + "\\Models\\" + name);
	std::vector<Mesh*> result_meshes = std::vector<Mesh*>();

	bool is_exists = false;
	int counter = 0;

ret:
	Mesh** find_mesh = m_meshes.Find<std::string>(
		[](Mesh* mesh, const std::string& v) -> bool
		{
			return mesh->GetResourceID() == v;
		},
		path + " - " +std::to_string(counter));

	if (find_mesh != nullptr)  {
		if (!is_exists) {
			if (Debug::GetLevel() >= Debug::Level::High)
				Debug::Log("ResourceManager::LoadModel() : copy \"" + name + "\" model...");
			is_exists = true;
		}

		Mesh* copy = (*find_mesh)->Copy();

		m_meshes.Add(copy);
		m_count_meshes++;
		result_meshes.push_back(copy);

		counter++;
		goto ret;
	}

	if (!is_exists) {
		if (Debug::GetLevel() >= Debug::Level::High)
			Debug::Log("ResourceManager::LoadModel() : loading \"" + name + "\" model...");

		std::string ext = SRString::GetExtensionFromFilePath(path);
		if (ext == "obj")
			result_meshes = ObjLoader::Load(path);
		else
		{
			path.clear();
			Debug::Error("ResourceManager::LoadModel() : failed load \"" + name + "\" obj model! Unknown extension!");
			m_mutex.unlock();
			return {};
		}

		if (result_meshes.size() == 0) {
			Debug::Error("ResourceManager::LoadModel() : failed load \"" + name + "\" obj model!");
			m_mutex.unlock();
			return {};
		}

		for (size_t t = 0; t < result_meshes.size(); t++) {
			result_meshes[t]->m_res_id = (path + " - " + std::to_string(t));
			m_meshes.Add(result_meshes[t]);
			m_count_meshes++;
		}
	}

	path.clear();
	m_mutex.unlock();
	return result_meshes;
}
Texture* SpaRcle::Graph::ResourceManager::LoadTexture(std::string name, Texture::Type type, Texture::Filter filter, Texture::CompressedLevel compress) {
	m_mutex.lock();

	std::string path = SRString::MakePath(ResourceManager::GetResourceFolder() + "\\Textures\\" + name);
	
	Texture* find = nullptr;
	size_t count = m_count_textures;
	for (size_t t = 0; t < count; t++) {
		if (m_textures[t]->GetResourceID() == path)
		{
			find = m_textures[t];
			break;
		}
	}

	Texture* texture = nullptr;

	if (find) {
		if (Debug::GetLevel() >= Debug::Level::High)
			Debug::Log("ResourceManager::LoadTexture() : copying \"" + name + "\" texture...");
		texture = find->Copy();
	}
	else {
		if (Debug::GetLevel() >= Debug::Level::High)
			Debug::Log("ResourceManager::LoadTexture() : loading \""+path+"\" texture...");

		std::string ext = SRString::GetExtensionFromFilePath(path);
		Image* image = nullptr;
		/*if (ext == "png")
			image = Image::LoadPNG(path.c_str());
		else {
			Debug::Error("ResourceManager::LoadTexture() : failed load \""+path+"\" texture! Unknown extension!");
			m_mutex.unlock();
			return nullptr;
		}*/

		texture = new Texture(image, type, filter, compress);

		texture->m_res_id = path;

		m_textures.Add(texture);
		m_count_textures++;

		ext.clear();
	}

	m_mutex.unlock();
	return texture;
}

bool SpaRcle::Graph::ResourceManager::Init(std::string resource_folder) {
	if (m_isInit) {
		Debug::Info("ResourceManager::Init() : Resource manager already initialized!");
		return false;
	} else
		Debug::Info("Initializing resource manager...");

	m_resource_folder	= resource_folder;
	m_isInit			= true;
	m_isStop			= false;
	m_thread			= std::thread(ResourceManager::Thread);

	return true;
}
bool SpaRcle::Graph::ResourceManager::Stop() {
	if (!m_isInit) {
		Debug::Info("ResourceManager::Stop() : Resource manager is not initialized!");
		return false;
	}
	else
		Debug::Info("Stopping resource manager...");

	m_isInit = false;
	m_isStop = true;

	Debug::Info("ResourceManager::Stop() : free application memory...");

	PrintMemoryDump();

	if (m_thread.joinable()) m_thread.join();


	for (size_t t = 0; t < m_resources_to_destroy.Size(); t++)
		FreeResource(m_resources_to_destroy[t]);
	for (size_t t = 0; t < m_meshes.Size(); t++)
		delete m_meshes[t];

	return true;
}

void SpaRcle::Graph::ResourceManager::PrintMemoryDump() {
	Debug::System(
		"\n======================================= MEMORY DUMP ======================================="
		"\n\tMeshes		: " + std::to_string(m_meshes.Size()) +
		"\n\tTextures	: " + std::to_string(m_textures.Size()) +
		"\n\tWait free	: " + std::to_string(m_resources_to_destroy.Size()) +
		"\n===========================================================================================");
}
void SpaRcle::Graph::ResourceManager::PrintTexturesDump() {
	std::string dump = "";

	for (size_t t = 0; t < m_count_textures; t++) {
		dump += "\n\t\"" + m_textures[t]->GetResourceID() + " | " + std::to_string(m_textures[t]->GetCountUses()) + "\"";
	}

	Debug::System(
		"\n===================================== TEXTURE DUMP ====================================="
		+ dump + 
		"\n========================================================================================"
	);
}
