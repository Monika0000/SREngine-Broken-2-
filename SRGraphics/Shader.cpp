#include "pch.h"
#include "Shader.h"
#include "Render.h"

SpaRcle::Graph::Shader::Shader(Render* render, std::string name) :
	m_render(render), m_name(name) 
{

}

SpaRcle::Graph::Shader::~Shader()
{
}

bool SpaRcle::Graph::Shader::Link()
{
	return false;
}

bool SpaRcle::Graph::Shader::Compile()
{
	return false;
}

bool SpaRcle::Graph::Shader::Use()
{
	return false;
}

bool SpaRcle::Graph::Shader::Destroy()
{
	return false;
}
