#include "pch.h"
#include <iostream>
#include "ResourceManager.h"

using namespace SpaRcle::Helper;
using namespace SpaRcle::Graph;

bool SpaRcle::Graph::ResourceManager::RemoveMesh(Mesh* mesh) {
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

bool SpaRcle::Graph::ResourceManager::FreeResource(IResource* res) {
	if (res->Name() == "Mesh")
		RemoveMesh(static_cast<Mesh*>(res));
	else
		return false;

	return true;
}

void SpaRcle::Graph::ResourceManager::GC() {
	for (size_t t = 0; t < m_resources_to_destroy.Size(); t++) {
		if (m_resources_to_destroy[t]->m_CountPossibleUses == 0) {
			FreeResource(m_resources_to_destroy[t]);
		}
	}

	m_resources_to_destroy.Clear();
}

void SpaRcle::Graph::ResourceManager::Thread() {
	while (m_isInit) {
		GC();
	}
}

void SpaRcle::Graph::ResourceManager::Destroy(IResource* res) {
	m_resources_to_destroy.Add(res);
}

std::vector<Mesh*> SpaRcle::Graph::ResourceManager::LoadObj(std::string name) {
	std::vector<Mesh*> meshes = std::vector<Mesh*>();

	meshes.push_back(new Mesh());

	for (size_t t = 0; t < meshes.size(); t++) {
		m_meshes.Add(meshes[t]);
		m_count_meshes++;
	}

	return meshes;
}

bool SpaRcle::Graph::ResourceManager::Init(std::string resource_folder) {
	if (m_isInit) {
		Debug::Info("ResourceManager::Init() : Resource manager already initialized!");
		return false;
	}else
		Debug::Info("Initializing resource manager...");

	m_isInit = true;
	m_isStop = false;
	m_thread = std::thread(ResourceManager::Thread);

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

	Debug::Info("ResourceManager::Stop() : free application memory:\n\tMeshes: " 
		+ std::to_string(m_meshes.Size()) + "\n\tWait free: "+std::to_string(m_resources_to_destroy.Size()));

	if (m_thread.joinable()) m_thread.join();

	Sleep(10);

	{
		//for (Mesh* mesh : m_meshes)
		//	delete mesh;
		//for (IResource* res : m_resources_to_destroy) {
		//	FreeResource(res);
		//}
	}

	return true;
}
