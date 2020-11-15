#include "pch.h"
#include "Material.h"
#include "Texture.h"

SpaRcle::Graph::Material::Material(Texture* diffuse, Texture* normal, Texture* specular, Texture* glossiness, bool isTransparent, bool isDefault) :
	m_diffuse(diffuse), m_normal(normal), m_specular(specular), m_glossiness(glossiness), m_isTransparent(isTransparent), m_isDefault(isDefault)
{
	if (m_diffuse)		m_diffuse->AddUsePoint();
	if (m_normal)		m_normal->AddUsePoint();
	if (m_specular)		m_specular->AddUsePoint();
	if (m_glossiness)	m_glossiness->AddUsePoint();
}

SpaRcle::Graph::Material::~Material() {
	if (m_diffuse)		m_diffuse->RemoveUsePoint();
	if (m_normal)		m_normal->RemoveUsePoint();
	if (m_specular)		m_specular->RemoveUsePoint();
	if (m_glossiness)	m_glossiness->RemoveUsePoint();

	this->m_diffuse		= nullptr;
	this->m_normal		= nullptr;
	this->m_specular	= nullptr;
	this->m_glossiness	= nullptr;
}

bool SpaRcle::Graph::Material::SetMesh(Mesh* mesh) {
	if (m_isDefault)
		return false;
	if (m_mesh)
		return false;

	m_mesh = mesh;

	return true;
}

SpaRcle::Graph::Material* SpaRcle::Graph::Material::Copy() {
	Material* mat = new Material(m_diffuse, m_normal, m_specular, m_glossiness, m_isDefault, m_isTransparent);

	mat->m_mesh = m_mesh;

	return mat;
}
