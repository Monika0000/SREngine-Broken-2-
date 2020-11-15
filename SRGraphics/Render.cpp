#include "pch.h"
#include "Render.h"
#include "Window.h"
#include "Camera.h"

SpaRcle::Graph::Render::Render() {

}

SpaRcle::Graph::Render::~Render() {

}

bool SpaRcle::Graph::Render::Create(Window* window, Camera* camera) {
	if (m_isCreate) {
		Debug::Error("Render::Create() : render alreay create!");
		return false;
	}
	else
		Debug::Graph("Render::Create() : creating render...");

	m_window = window;
	m_camera = camera;

	this->m_geometryShader = new Shader(this, "geometry");

	m_isCreate = true;

	return true;
}

bool SpaRcle::Graph::Render::Init() {
	if (m_isInit) {
		Debug::Error("Render::Init() : render alreay initialized!");
		return false;
	}
	else
		Debug::Graph("Render::Init() : initializing render...");

	m_isInit = true;

	return true;
}

bool SpaRcle::Graph::Render::Run() {
	if (m_isRun) {
		Debug::Error("Render::Run() : render alreay ran!");
		return false;
	}
	else
		Debug::Graph("Render::Run() : running render...");

	m_isRun = true;

	return true;
}

bool SpaRcle::Graph::Render::Close() {
	if (!m_isRun) {
		Debug::Error("Render::Close() : render is not ran!");
		return false;
	}
	else
		Debug::Graph("Render::Close() : close render...");

	//m_isRun = true;

	return true;
}

void SpaRcle::Graph::Render::DrawGeometry()
{
}

void SpaRcle::Graph::Render::DrawTransparentGeometry()
{
}

void SpaRcle::Graph::Render::DrawSkybox()
{
}

void SpaRcle::Graph::Render::DrawGUI()
{
}
