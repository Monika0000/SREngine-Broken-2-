#include "pch.h"
#include "Mesh.h"
#include "ResourceManager.h"

SpaRcle::Graph::Mesh::Mesh() : IResource("Mesh", 0) {

}

bool SpaRcle::Graph::Mesh::Destroy() {
	if (m_isDestroy)
		return false;

	m_isDestroy = true;

	ResourceManager::Destroy(this);

	return true;
}
