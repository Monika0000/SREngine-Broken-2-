#include <Debug.h>
#include <SRGraphics.h>
#include <SRFile.h>
#include <Window.h>
#include <ResourceManager.h>

using namespace SpaRcle::Helper;
using namespace SpaRcle::Graph;

#pragma comment(lib, "SRHelper.lib")
#pragma comment(lib, "SRGraphics.lib")

int main(int argcp, char* argv) {
    Debug::Get()->Init(SRFile::GetPathToExe() + "\\log.txt", true);
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
        for (int i = 0; i < 1000; i++) {
            std::vector<Mesh*> meshes = ResourceManager::LoadObj("example");
            meshes[0]->Destroy();
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
    return Debug::Get()->Stop();
}
