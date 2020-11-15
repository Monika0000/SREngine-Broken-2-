#include "pch.h"
#include "Texture.h"
#include <Debug.h>
#include "ResourceManager.h"

using namespace SpaRcle::Helper;

SpaRcle::Graph::Texture::Texture(Image* image, Type type, Filter filter, CompressedLevel compress)
    : IResource("Texture", 0), m_type(type), m_filter(filter), m_compress(compress)
{
    this->AddUsePoint();
    this->m_image = image;
}

SpaRcle::Graph::Texture::~Texture() {
    if (m_image)
        delete m_image;

    m_image = nullptr;
    this->m_id = 0;
}

SpaRcle::Graph::Texture* SpaRcle::Graph::Texture::Copy() {
    this->AddUsePoint();
    return this;
}

bool SpaRcle::Graph::Texture::Calculate() {
    return false;
}

bool SpaRcle::Graph::Texture::Destroy() {
    this->RemoveUsePoint();

    if (m_isDestroy)
        return false;

    if (Debug::GetLevel() >= Debug::Level::High)
        Debug::Log("Texture::Destroy() : destroy texture...");
    
    m_isDestroy = true;

    ResourceManager::Destroy(this);

    return true;
}
