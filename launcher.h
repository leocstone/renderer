#ifndef LAUNCHER_H
#define LAUNCHER_H
#include <gtk/gtk.h>
#include <string>
#include <iostream>

using std::cout;
using std::endl;
using std::string;

// A struct containing all the options in the GTK menu
struct Arguments
{
    Arguments() {}
    Arguments(const char* t, const char* m, bool f) : texturePath(t), modelPath(m), fullscreen(f) {}

    string texturePath;
    string modelPath;
    bool fullscreen;
};

/*

Launcher

Creates a GTK window and runs the renderer's main method with the user's arguments

*/
class Launcher
{
public:
    Launcher(const char* windowTitle, int (*gameMain)(const Arguments&));
    ~Launcher() {}

    void launchGame();

    GtkWidget* getWindow() { return m_window; }

private:
    // Gets the current values of all input fields and puts them into the struct
    void updateArguments();

    // Creates the launcher window
    void setupWindow(const char* title);

    // Static function passed to GTK to launch game
    static void _launchGame();

    Arguments m_arguments;

    // Pointer to the game's main method
    int (*m_gameMain)(const Arguments&);

    // UI elements
    GtkWidget* m_fullscreenToggle;
    GtkWidget* m_window;
    GtkWidget* m_texturePath;
    GtkWidget* m_modelPath;
};

#endif // LAUNCHER_H
