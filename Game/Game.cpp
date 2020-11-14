#define NOMINMAX
#define GLEW_STATIC 1
#define WINDOWLESS 1
#define _CRT_SECURE_NO_WARNINGS

#include <Debug.h>
#include <SRGraphics.h>
#include <SRFile.h>
#include <Window.h>
#include <ResourceManager.h>
#include <Input.h>
#include <SRString.h>

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

        while (true) {
            if (GetKey(KeyCode::F))
            {
                meshes = ResourceManager::LoadObj("Engine\\cube");
                for (size_t t = 0; t < meshes.size(); t++) {
                    Debug::Log(std::to_string(meshes[t]->GetCountVertices()));
                    meshes[t]->Destroy();
                }
            }
            if (GetKeyDown(KeyCode::D))
                ResourceManager::PrintMemoryDump();
        }
    });

    if (SRGraphics::Create(window)) {
        if (SRGraphics::Init()) {
            if (SRGraphics::Run()) {
                SRGraphics::Close();
            } 
            else
                Debug::Error("Failed running SRGraphics!");
        }
        else
            Debug::Error("Failed initializing SRGraphics!");
    }
    else
        Debug::Error("Failed creating SRGraphics!");
    
    if (task.joinable()) task.join();

    ResourceManager::Stop();
    return Debug::Stop();
}
