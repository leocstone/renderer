#include <iostream>
#include "launcher.h"
#include "game.h"
#include "meshrenderer.h"
#include "diffuseshader.h"
#include "objloader.h"
#include "timer.h"

using std::cin;

// Linux emulation of win32 API GetTickCount(), in unix epoch instead of time since system startup
static float getTickCount()
{
    timespec now;
    if(clock_gettime(CLOCK_MONOTONIC, &now))
    {
        return 0;
    }
    return (now.tv_sec * 1000.0f) + (now.tv_nsec / 1000000.0f);
}

// Launches renderer, taking arguments from GTK menu
int gameMain(const Arguments& args)
{
    cout << "Launched the game" << endl;
    cout << "Model: " << args.modelPath << endl;
    cout << "Texture: " << args.texturePath << endl;
    cout << "Fullscreen: " << args.fullscreen << endl;

    // Default to 1024x778
    SDL_VideoInit(NULL);
    SDL_DisplayMode dm;
    dm.w = 1024;
    dm.h = 768;

    if(SDL_GetDesktopDisplayMode(0, &dm))
    {
        cout << "ERROR: Could not get display mode" << endl;
        cout << SDL_GetError() << endl;
    }

    // Windowed size is 3/4 of entire screen
    if(!args.fullscreen)
    {
        dm.w = (dm.w * 3) / 4;
        dm.h = (dm.h * 3) / 4;
    }

    cout << "Resolution of primary monitor: " << dm.w << "x" << dm.h << endl;

    Game game(dm.w, dm.h, "Renderer", args.texturePath, args.fullscreen);

    // Create the objects needed for rendering, loading the OBJ model and texture from supplied paths
    DirectionalLight dl(vec3(-1, -1, -1), vec3(0.1, 0.1, 0.1), vec3(1.0, 1.0, 1.0), vec3(0.1, 0.1, 0.1));
    Material boxMat(vec3(1.0, 1.0, 1.0), vec3(1.0, 1.0, 1.0), vec3(1.0, 1.0, 1.0), 1.0f);
    DiffuseShader df("./res/diffuseShader", &game.player.camera, &dl, &boxMat);
    Texture demoTexture(args.texturePath);
    Mesh* demoMesh = new Mesh(OBJLoader::loadOBJ(args.modelPath));
    Transform dt;
    Transform rootTransform(vec3(0, 0, 0));
    MeshRenderer root(demoMesh, &rootTransform);
    game.createRenderer(&root, Diffuse);

    // Tracks FPS
    Timer frameTimer;
    // Used to keep the update rate constant
    float nextUpdate = getTickCount();
    unsigned timesUpdated = 0;
    unsigned totalUpdates = 0;
    unsigned totalDraws = 0;
    Timer gameTimer;
    gameTimer.start();

    // Main loop - attempts to maintain constant update rate defined in engine_constants.h
    while(!game.isClosed())
    {
        timesUpdated = 0;
        frameTimer.start();
        while(getTickCount() > nextUpdate && timesUpdated < max_frameskip)
        {
            game.update();
            nextUpdate += skip_ticks;
            timesUpdated++;
            totalUpdates++;
        }
        game.draw();
        totalDraws++;
        cout << 1.0f / frameTimer.secondsElapsed() << " fps" << endl;
    }
    double timeElapsed = gameTimer.secondsElapsed();
    cout << "Ran for " << timeElapsed << " seconds" << endl;
    cout << "Updated " << totalUpdates << " times ( " << double(totalUpdates) / timeElapsed << " updates/s )" << endl;
    cout << "Drew " << totalDraws << " times ( " << double(totalDraws) / timeElapsed << " fps )" << endl;

    delete demoMesh;
    return 0;
}

int main(int argc, char* argv[])
{
    // Disable vsync for accurate fps measurement
    setenv("vblank_mode", "0", 1);
    Launcher l("test", &gameMain);
    gtk_main();

    return 0;
}
