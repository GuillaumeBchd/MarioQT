#ifndef PAUSEMENUCONTROLLER_H
#define PAUSEMENUCONTROLLER_H

#include "pausemenuwidget.h"

class MainMenuController;
class MainWindow;

class PauseMenuController
{
private:
    PauseMenuWidget * pauseMenuWidget;
    MainWindow * mainWindow;

public:
    PauseMenuController();
    void setPauseMenuWidget(PauseMenuWidget * pmw){ pauseMenuWidget = pmw; }
    void setMainWindowPointer(MainWindow * mw){ mainWindow = mw; }
    void launchMainMenu();
};

#endif // PAUSEMENUCONTROLLER_H