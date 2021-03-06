#include "mainwindow.h"

MainWindow::MainWindow() : QMainWindow()
{
    parent();

    // We initialize the mainMenu's widget and controller
    mainMenuController.setMainMenuWidget(&mainMenuWidget);
    mainMenuController.setMainWindowPointer(this);
    mainMenuWidget.setMainMenuController(&mainMenuController);


    // We initialize the game's widget and controller
    gamecontroller.setGameView(&gameview);
    gamecontroller.setSettingsPointer(&settings);
    gamecontroller.setMainWindowPointer(this);
    gameview.setGameController(&gamecontroller);


    // We initialize the levelEditor's widget and controller
    levelEditorWidget.setLevelEditorEngine(&levelEditorEngine);
    levelEditorWidget.setLevelEditorView(&levelEditorView);
    levelEditorView.setLevelEditorEngine(&levelEditorEngine);
    levelEditorEngine.setLevelEditorWidget(&levelEditorWidget);
    levelEditorEngine.setLevelEditorView(&levelEditorView);
    levelEditorEngine.setMainWindowPointer(this);

    // We initialize the pauseMenu's widget and controller
    pauseMenuController.setPauseMenuWidget(&pauseMenuWidget);
    pauseMenuController.setMainWindowPointer(this);
    pauseMenuWidget.setPauseMenuController(&pauseMenuController);

    // We initialize the optionsMenu's widget and controller
    optionsMenuController.setOptionsMenuWidget(&optionsMenuWidget);
    optionsMenuController.setMainWindowPointer(this);
    optionsMenuController.setSettingsPointer(&settings);
    optionsMenuWidget.setOptionsMenuController(&optionsMenuController);

    // We fill the stackedWidget with the menu, the game and the levelEditor
    stackedWidget.addWidget(&mainMenuWidget);
    stackedWidget.addWidget(&gameview);
    stackedWidget.addWidget(&levelEditorWidget);
    stackedWidget.addWidget(&pauseMenuWidget);
    stackedWidget.addWidget(&optionsMenuWidget);

    //Display the menu to the application start
    goBackToMainMenu();

    setCentralWidget(&stackedWidget);
}

void MainWindow::startGameOnMap(QString filePath)
{
    stackedWidget.setCurrentIndex(1);
    gamecontroller.setMapFilepath(filePath);
    gamecontroller.start();

    resize(1280, 720);
    centerOnScreen();
}

void MainWindow::displayPauseMenu()
{
    stackedWidget.setCurrentIndex(3);
}

void MainWindow::goBackToMainMenu()
{
    gamecontroller.stop();
    stackedWidget.setCurrentIndex(0);
    resize(500,500);
    centerOnScreen();
}

void MainWindow::launchLevelEditor()
{
    stackedWidget.setCurrentIndex(2);
    levelEditorEngine.start();
    resize(1280, 850);
    centerOnScreen();
}

void MainWindow::displayOptionsMenu()
{
    stackedWidget.setCurrentIndex(4);
}

void MainWindow::goBackToGame(){
    stackedWidget.setCurrentIndex(1);
    gamecontroller.playMusic();
}

void MainWindow::retryGame(){
    stackedWidget.setCurrentIndex(1);
    gamecontroller.reset();
}

void MainWindow::centerOnScreen()
{
    QDesktopWidget wid;
    int width = frameGeometry().width();
    int height = frameGeometry().height();
    int screenWidth = wid.screen()->width();
    int screenHeight = wid.screen()->height();

    move((screenWidth/2)-(width/2),(screenHeight/2)-(height/2));
}
