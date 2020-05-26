#include "pausemenuwidget.h"

#include "pausemenucontroller.h"
#include "QDebug"

PauseMenuWidget::PauseMenuWidget()
{
    setFixedSize(300, 300);
    QVBoxLayout * layout = new QVBoxLayout(this);
    continueButton.setText("CONTINUE");
    menuButton.setText("GO BACK TO MENU");
    optionsButton.setText("OPTIONS");
    quitButton.setText("QUIT");

    //listWidget style
    applyStyleSheet();

    //Add element in layout
    layout->addWidget(&continueButton);
    layout->addWidget(&menuButton);
    layout->addWidget(&optionsButton);
    layout->addWidget(&quitButton);

    //Connect the buttons to their slots
    connect(&continueButton, SIGNAL (clicked()), this, SLOT (handleContinueButton()));
    connect(&menuButton, SIGNAL (clicked()), this, SLOT (handleMenuButton()));
    connect(&optionsButton, SIGNAL (clicked()), this, SLOT (handleOptionsButton()));
    connect(&quitButton, SIGNAL (clicked()), this, SLOT (handleQuitButton()));
}

void PauseMenuWidget::applyStyleSheet()
{

}

void PauseMenuWidget::handleContinueButton()
{

}

void PauseMenuWidget::handleMenuButton()
{
    pauseMenuController->launchMainMenu();
}

void PauseMenuWidget::handleOptionsButton()
{

}

void PauseMenuWidget::handleQuitButton()
{

}
