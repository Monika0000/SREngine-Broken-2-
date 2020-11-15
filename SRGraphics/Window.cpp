#include "pch.h"
#include "Window.h"

SpaRcle::Graph::Window::Window(
	const char* win_name, 
	int argcp, char* argv, 
	Render* render, 
	Camera* camera, 
	FormatType format, 
	bool vsync, 
	bool fullscreen, 
	unsigned char smooth_samples) 
{
	this->m_win_name			= win_name;
	this->m_argcp				= argcp;
	this->m_argv				= argv;
	this->m_render				= render;
	this->m_camera				= camera;
	this->m_format				= format;
	this->m_vsync				= vsync;
	this->m_fullscreen			= fullscreen;
	this->m_smooth_samples		= smooth_samples;
}

bool SpaRcle::Graph::Window::Create() {
	if (m_isCreate) {
		Debug::Error("Window::Create() : window already create!");
		return false;
	}

	Debug::Graph("Window::Create() : creating window...");

	if (!m_render->Create(this, m_camera)) {
		Debug::Error("Window::Create() : failed create render!");
		return false;
	}

	m_isCreate = true;

	return true;
}

bool SpaRcle::Graph::Window::Init() {
	if (m_isInit) {
		Debug::Error("Window::Init() : window already initialize!");
		return false;
	}

	Debug::Graph("Window::Init() : initializing window...");

	m_isInit = true;

	return true;
}

bool SpaRcle::Graph::Window::Run() {
	if (m_isRun) {
		Debug::Error("Window::Run() : window already ran!");
		return false;
	}

	Debug::Graph("Window::Run() : running window...");

	m_isRun = true;

	return true;
}

bool SpaRcle::Graph::Window::Close() {
	if (!m_isClose) {
		Debug::Error("Window::Close() : window is not ran!");
		return false;
	}

	Debug::Graph("Window::Close() : close window...");

	m_isRun = false;
	m_isClose = true;

	return true;
}
