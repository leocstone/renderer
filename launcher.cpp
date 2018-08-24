#include "launcher.h"

static Launcher* singleton = NULL;
Launcher::Launcher(const char* windowTitle, int (*gameMain)(const Arguments&))
{
    m_gameMain = gameMain;
    setupWindow(windowTitle);
    m_arguments.modelPath = "uninitialized";
    m_arguments.texturePath = "uninitialized";
    m_arguments.fullscreen = false;
    if(singleton == NULL)
    {
        singleton = this;
    }
    else
    {
        cout << "Error: tried to create two launchers" << endl;
        exit(1);
    }
}

void Launcher::_launchGame()
{
    singleton->updateArguments();
    gtk_widget_destroy(singleton->getWindow());
    gtk_main_quit();
    singleton->launchGame();
}

void Launcher::launchGame()
{
    m_gameMain(m_arguments);
}

void Launcher::setupWindow(const char* title)
{
    GtkWidget* widget = NULL;
    GtkWidget* vbox = NULL;
    const char* defaultModel = "./res/surface.obj";
    const char* defaultTexture = "./res/grid.png";

    // Init GTK
    g_log_set_handler("Gtk", G_LOG_LEVEL_WARNING, (GLogFunc)gtk_false, NULL);
    gtk_init(NULL, NULL);
    g_log_set_handler("Gtk", G_LOG_LEVEL_WARNING, g_log_default_handler, NULL);

    // Create the window
    m_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_container_set_border_width(GTK_CONTAINER(m_window), 8);
    gtk_window_set_title(GTK_WINDOW(m_window), title);
    gtk_window_set_position(GTK_WINDOW(m_window), GTK_WIN_POS_CENTER);
    gtk_widget_realize(m_window);
    g_signal_connect(m_window, "destroy", gtk_main_quit, NULL);

    // Create the vbox
    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 6);
    gtk_container_add(GTK_CONTAINER(m_window), vbox);

    widget = gtk_label_new("Path to texture:");
    gtk_box_pack_start(GTK_BOX(vbox), widget, TRUE, TRUE, 0);

    m_texturePath = gtk_entry_new();
    gtk_entry_set_text(GTK_ENTRY(m_texturePath), defaultTexture);
    gtk_box_pack_start(GTK_BOX(vbox), m_texturePath, TRUE, TRUE, 0);

    widget = gtk_label_new("Path to model (OBJ):");
    gtk_box_pack_start(GTK_BOX(vbox), widget, TRUE, TRUE, 0);

    m_modelPath = gtk_entry_new();
    gtk_entry_set_text(GTK_ENTRY(m_modelPath), defaultModel);
    gtk_box_pack_start(GTK_BOX(vbox), m_modelPath, TRUE, TRUE, 0);

    m_fullscreenToggle = gtk_check_button_new_with_label("Fullscreen");
    gtk_box_pack_start(GTK_BOX(vbox), m_fullscreenToggle, TRUE, TRUE, 0);

    widget = gtk_button_new_with_label("Launch");
    g_signal_connect(widget, "clicked", G_CALLBACK(_launchGame), NULL);
    gtk_box_pack_start(GTK_BOX(vbox), widget, TRUE, TRUE, 0);

    widget = gtk_button_new_with_label("Close");
    g_signal_connect(widget, "clicked", gtk_main_quit, NULL);
    gtk_box_pack_start(GTK_BOX(vbox), widget, TRUE, TRUE, 0);
    gtk_widget_show_all(m_window);
}

void Launcher::updateArguments()
{
    m_arguments = Arguments(gtk_entry_get_text(GTK_ENTRY(m_texturePath)),
                            gtk_entry_get_text(GTK_ENTRY(m_modelPath)),
                            gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(m_fullscreenToggle)));
}
