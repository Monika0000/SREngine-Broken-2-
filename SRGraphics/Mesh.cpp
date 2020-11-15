#include "pch.h"
#include "Mesh.h"
#include "ResourceManager.h"
#include "Material.h"

SpaRcle::Graph::Mesh::Mesh(Shader* shader, Material* material, std::string name) 
	: IResource("Mesh", 0)
{
	this->m_shader		= shader;
	this->m_render		= m_shader->GetRender();
	this->m_material	= material;
	this->m_name		= name;
}

SpaRcle::Graph::Mesh::~Mesh() {
	if (m_material)
		delete m_material;
	m_material	= nullptr;
	m_shader	= nullptr;
	m_name.clear();
}

SpaRcle::Graph::Mesh* SpaRcle::Graph::Mesh::Copy() {
	Mesh* copy = new Mesh(m_shader, m_material, m_name);

	copy->m_res_id	= m_res_id;
	// m_res_name - setting automatic
	copy->m_count_vertices = m_count_vertices;

	return copy;
}

bool SpaRcle::Graph::Mesh::Draw()
{
	return false;
}

void SpaRcle::Graph::Mesh::SetVertexArray(const std::vector<Vertex>& vertices) {
	this->m_vertices		= vertices;
	this->m_count_vertices	= m_vertices.size();
}

bool SpaRcle::Graph::Mesh::Destroy() {
	if (m_isDestroy)
		return false;

	if (Debug::GetLevel() >= Debug::Level::High)
		Debug::Log("Mesh::Destroy() : destroying \"" + std::string(m_res_name) + "\" mesh...");

	m_isDestroy = true;

	ResourceManager::Destroy(this);

	return true;
}
