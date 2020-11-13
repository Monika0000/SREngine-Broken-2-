#include "pch.h"
#include "SRGraphics.h"
#include <Debug.h>

#include "Window.h"

using namespace SpaRcle::Helper;

bool SpaRcle::Graph::SRGraphics::Create(Window* window) {
	if (!m_IsCreate)
		Debug::Info("Creating SpaRcle graphics...");
	else {
		Debug::Error("SpaRcle graphics already create!");
		return false;
	}

	//if (m_window->) 

	m_IsCreate = true;

	return true;
}

bool SpaRcle::Graph::SRGraphics::Init() {
	if (!m_IsInit)
		Debug::Info("Initializing SpaRcle graphics...");
	else {
		Debug::Error("SpaRcle graphics already initialize!");
		return false;
	}

	m_IsInit = true;

	return true;
}

bool SpaRcle::Graph::SRGraphics::Run() {
	if (!m_IsRun)
		Debug::Info("Running SpaRcle graphics...");
	else {
		Debug::Error("SpaRcle graphics already ran!");
		return false;
	}

	m_IsRun = true;

	return true;
}

bool SpaRcle::Graph::SRGraphics::Close() {
	if (!m_IsClose)
		Debug::Info("Close SpaRcle graphics...");
	else {
		Debug::Error("SpaRcle graphics already closed!");
		return false;
	}

	m_IsClose = true;

	return true;
}
