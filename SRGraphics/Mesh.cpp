#include "pch.h"
#include "Mesh.h"
#include "ResourceManager.h"
#include "Material.h"

SpaRcle::Graph::Mesh::Mesh(Shader* shader, Material* material, std::string name) 
	: IResource("Mesh", 0)
{

}

SpaRcle::Graph::Mesh::~Mesh() {

}

SpaRcle::Graph::Mesh* SpaRcle::Graph::Mesh::Copy() {
	Mesh* copy = new Mesh(m_shader, nullptr, "");
	copy->m_res_id = m_res_id;
	return copy;
}

void SpaRcle::Graph::Mesh::SetVertexArray(const std::vector<Vertex>& vertices) {
	this->m_vertices		= vertices;
	this->m_count_vertices	= m_vertices.size();
}

bool SpaRcle::Graph::Mesh::Destroy() {
	if (m_isDestroy)
		return false;

	if (Debug::GetLevel() >= Debug::Level::Hight)
		Debug::Log("Mesh::Destroy() : destroying \"" + std::string(m_res_name) + "\" mesh...");

	m_isDestroy = true;

	ResourceManager::Destroy(this);

	return true;
}
