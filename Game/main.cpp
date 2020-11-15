#define NOMINMAX
#define GLEW_STATIC 1
#define WINDOWLESS 1
#define _CRT_SECURE_NO_WARNINGS

#include <SRGraphics.h>
#include <Debug.h>
#include <SRFile.h>
#include <Input.h>
#include <SRString.h>
#include <ResourceManager.h>
#include <EventsManager.h>

#include <GL\glew.h>

using namespace SpaRcle::Helper;
using namespace SpaRcle::Graph;

#pragma comment(lib, "SRHelper.lib")
#pragma comment(lib, "SRGraphics.lib")

#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "SOIL.lib")

int main(int argcp, char* argv) {
    Debug::Init(SRFile::GetPathToExe() + "\\log.txt", true);
    ResourceManager::Init(SRFile::GetPathToExe()+"../../Resources");

    Render* render = new Render();
    Camera* camera = new Camera();

    Window* window = new Window(
        "SpaRcle Engine",
        argcp, argv,
        render,
        camera,
        FormatType::_1280_720,
        false,
        false,
        4
    );
    std::thread task = std::thread([&]() {
        std::vector<Mesh*> meshes;

        //std::vector<Mesh*> load = ResourceManager::LoadObj("Engine\\cube");
        //ResourceManager::LoadTexture("engine\\default.png");

        while (true) {
            if (!SRGraphics::IsRun()) 
                continue;
            if (!SRGraphics::IsClose()) 
                break;

            if (GetKey(KeyCode::F))
            {
                //Texture* texture = ResourceManager::LoadTexture("engine\\default.png");
                //texture->Destroy();

                meshes = ResourceManager::LoadModel("Engine\\cube.obj");
                for (size_t t = 0; t < meshes.size(); t++) {
                    meshes[t]->Destroy();
                }
            }
            if (GetKeyDown(KeyCode::D))
                ResourceManager::PrintMemoryDump();
            if (GetKeyDown(KeyCode::T))
                ResourceManager::PrintTexturesDump();
        }
    });

    if (SRGraphics::Create(window)) {
        if (SRGraphics::Init()) {
            if (SRGraphics::Run()) {

            } 
            else {
                Debug::Error("Failed running SRGraphics!"); 
                EventsManager::PushEvent(EventsManager::Event::Error);
            }
        }
        else {
            Debug::Error("Failed initializing SRGraphics!");
            EventsManager::PushEvent(EventsManager::Event::Error);
        }
    }
    else {
        Debug::Error("Failed creating SRGraphics!");
        EventsManager::PushEvent(EventsManager::Event::Error);
    }

    Debug::System("All systems ran successfully!");
    
    while (true) {
        EventsManager::Event ev = EventsManager::PopEvent();
        if (ev == EventsManager::Event::Error) {
            break;
        }
        else if (ev == EventsManager::Event::Exit) {
            break;
        }
    }

    if (task.joinable()) task.join();

    ResourceManager::Stop();
    return Debug::Stop();
}
