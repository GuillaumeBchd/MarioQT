#include "leveleditorengine.h"
#include "mainwindow.h"

LevelEditorEngine::LevelEditorEngine()
{
    mouseState = NOTPRESSED;
    selectedButton = NOBUTTON;
    objectToPaintOnMouse = nullptr;
    fakeMario = nullptr;
    levelEditorView = nullptr;
    levelEditorWidget = nullptr;
    tickrate = 1000/240;
}

void LevelEditorEngine::update(CameraVisitor & visitor){
    int X = getColumnFromMousePosition()*block_size;
    int Y = getLineFromMousePosition()*block_size;

    visitor.setPosition(levelEditorView->getCameraPosition());

    if(mouseState == LEFTCLICKPRESSED){
        addObjectOnMousePosition();
    }

    if(mouseState == RIGHTCLICKPRESSED){
        deleteObjectAtPosition(X, Y);
    }

    for(ObjectModel * object : objects){
        object->accept(visitor);
    }

    if(fakeMario != nullptr){
        fakeMario->accept(visitor);
    }

    if(objectToPaintOnMouse != nullptr){
        objectToPaintOnMouse->moveTo(X, Y);
        objectToPaintOnMouse->accept(visitor);
    }
}

void LevelEditorEngine::changeCameraPosition(int value)
{
     if(levelEditorView != nullptr){
         levelEditorView->setCameraPosition(value);
     }
}

void LevelEditorEngine::addObjectOnMousePosition()
{
    int X = getColumnFromMousePosition()*block_size;
    int Y = getLineFromMousePosition()*block_size;

    deleteObjectAtPosition(X, Y);

    switch(selectedButton){
        case BRICK: {
            Brick * newBrick = new Brick();
            newBrick->moveTo(X, Y);
            inerts.append(newBrick);
            objects.append(newBrick);
            break;
        }
        case COINBRICK: {
            Brick * newBrick = new Brick();
            newBrick->setCoinBrick(true);
            newBrick->moveTo(X, Y);
            inerts.append(newBrick);
            objects.append(newBrick);
            break;
        }
        case BLOCK: {
            Block * newBlock = new Block();
            newBlock->moveTo(X, Y);
            inerts.append(newBlock);
            objects.append(newBlock);
            break;
        }
        case WALL: {
            Wall * newWall = new Wall();
            newWall->moveTo(X, Y);
            inerts.append(newWall);
            objects.append(newWall);
            break;
        }
        case SECRETBOXFLOWER: {
            Box * newBox = new Box();
            newBox->setBoxContent(FLOWER);
            newBox->moveTo(X, Y);
            inerts.append(newBox);
            objects.append(newBox);
            break;
        }
        case SECRETBOXMUSHROOM: {
            Box * newBox = new Box();
            newBox->setBoxContent(MUSHROOM);
            newBox->moveTo(X, Y);
            inerts.append(newBox);
            objects.append(newBox);
            break;
        }
        case SECRETBOXSTAR: {
            Box * newBox = new Box();
            newBox->setBoxContent(STAR);
            newBox->moveTo(X, Y);
            inerts.append(newBox);
            objects.append(newBox);
            break;
        }
        case SECRETBOXCOIN: {
            Box * newBox = new Box();
            newBox->setBoxContent(COIN);
            newBox->moveTo(X, Y);
            inerts.append(newBox);
            objects.append(newBox);
            break;
        }
        case SMALLPIPE: {
            Inert * newBrick = new Inert();
            newBrick->setCurrentTexture(newBrick->loadTexture(":/resources/graphics/pipe-small.png").scaled(block_size, block_size));
            newBrick->moveTo(X, Y);
            inerts.append(newBrick);
            objects.append(newBrick);
            break;
        }
        case MEDPIPE: {
            Inert * newBrick = new Inert();
            newBrick->setCurrentTexture(newBrick->loadTexture(":/resources/graphics/pipe-med.png").scaled(block_size, block_size));
            newBrick->moveTo(X, Y);
            inerts.append(newBrick);
            objects.append(newBrick);
            break;
        }
        case BIGPIPE: {
            Inert * newBrick = new Inert();
            newBrick->setCurrentTexture(newBrick->loadTexture(":/resources/graphics/pipe-big.png").scaled(block_size, block_size));
            newBrick->moveTo(X, Y);
            inerts.append(newBrick);
            objects.append(newBrick);
            break;
        }
        case BULLETBLASTER: {
            Inert * newBrick = new Inert();
            newBrick->setCurrentTexture(newBrick->loadTexture(":/resources/graphics/bill-blaster.png").scaled(block_size, block_size*2));
            newBrick->moveTo(X, Y);
            inerts.append(newBrick);
            objects.append(newBrick);
            break;
        }
        case FLAGPOLE: {
            Inert * newBrick = new Inert();
            newBrick->setCurrentTexture(newBrick->loadTexture(":/resources/graphics/flagpole.png").scaled(block_size, block_size*11));
            newBrick->moveTo(X, Y);
            inerts.append(newBrick);
            objects.append(newBrick);
            break;
        }
        case CASTLE: {
            Inert * newBrick = new Inert();
            newBrick->setCurrentTexture(newBrick->loadTexture(":/resources/graphics/castle.png").scaled(block_size*4, block_size*4));
            newBrick->moveTo(X, Y);
            inerts.append(newBrick);
            objects.append(newBrick);
            break;
        }
        case GOOMBA: {
            Goomba * goomba = new Goomba();
            goomba->moveTo(X, Y);
            entities.append(goomba);
            objects.append(goomba);
            break;
        }
        case TURTLE: {
            Koopa * koopa = new Koopa();
            koopa->moveTo(X, Y);
            entities.append(koopa);
            objects.append(koopa);
            break;
        }
        case FLYINGTURTLE: {
            //TODO
            break;
        }
        case MARIO: {
            fakeMario = new Mario();
            fakeMario->moveTo(X, Y);
            break;
        }
        default: {
            break;
        }
    }
}

void LevelEditorEngine::deleteObjectAtPosition(int x, int y)
{
    for(ObjectModel * object : objects){
        if(object->getPosition().x() == x && object->getPosition().y() == y){
            Mario * mario = dynamic_cast<Mario*>(object);
            if(mario){
                if(mario != nullptr){
                    objects.removeOne(mario);
                    entities.removeOne(mario);
                    delete mario;
                    mario = nullptr;
                }
            }
            else{
                Entity * entity = dynamic_cast<Entity*>(object);
                if(entity){
                    objects.removeOne(entity);
                    entities.removeOne(entity);
                    delete entity;
                }
                else{
                    Inert * inert = dynamic_cast<Inert*>(object);
                    if(inert){
                        objects.removeOne(inert);
                        inerts.removeOne(inert);
                        delete inert;
                    }
                }
            }
        }
    }
}

void LevelEditorEngine::setMouseState(MouseState ms)
{
    mouseState = ms;
}

void LevelEditorEngine::setSelectedButton(SelectedButton sb){
    selectedButton = sb;

    if(objectToPaintOnMouse != nullptr){
        delete  objectToPaintOnMouse;
        objectToPaintOnMouse = nullptr;
    }

    switch(selectedButton){
        case BRICK:
        case COINBRICK: {
            objectToPaintOnMouse = new Brick();
            objectToPaintOnMouse->setOpacity(0.5);
            break;
        }
        case BLOCK: {
            objectToPaintOnMouse = new Block();
            objectToPaintOnMouse->setOpacity(0.5);
            break;
        }
        case WALL: {
            objectToPaintOnMouse = new Wall();
            objectToPaintOnMouse->setOpacity(0.5);
            break;
        }
        case SECRETBOXMUSHROOM:
        case SECRETBOXFLOWER:
        case SECRETBOXSTAR:
        case SECRETBOXCOIN: {
            objectToPaintOnMouse = new Inert();
            objectToPaintOnMouse->setCurrentTexture(QPixmap(objectToPaintOnMouse->loadTexture(":/resources/graphics/blocs/secret-box.png").scaled(block_size, block_size)));
            objectToPaintOnMouse->setOpacity(0.5);
            break;
        }
        case SMALLPIPE: {
                objectToPaintOnMouse = new Inert();
                objectToPaintOnMouse->setCurrentTexture(QPixmap(objectToPaintOnMouse->loadTexture(":/resources/graphics/pipe-small.png").scaled(block_size, block_size)));
                objectToPaintOnMouse->setOpacity(0.5);
                break;
        }
        case MEDPIPE: {
                objectToPaintOnMouse = new Inert();
                objectToPaintOnMouse->setCurrentTexture(QPixmap(objectToPaintOnMouse->loadTexture(":/resources/graphics/pipe-med.png").scaled(block_size, block_size)));
                objectToPaintOnMouse->setOpacity(0.5);
                break;
        }
        case BIGPIPE: {
                objectToPaintOnMouse = new Inert();
                objectToPaintOnMouse->setCurrentTexture(QPixmap(objectToPaintOnMouse->loadTexture(":/resources/graphics/pipe-big.png").scaled(block_size, block_size)));
                objectToPaintOnMouse->setOpacity(0.5);
                break;
        }
        case BULLETBLASTER: {
                objectToPaintOnMouse = new Inert();
                objectToPaintOnMouse->setCurrentTexture(QPixmap(objectToPaintOnMouse->loadTexture(":/resources/graphics/bill-blaster.png").scaled(block_size, block_size*2)));
                objectToPaintOnMouse->setOpacity(0.5);
                break;
        }
        case FLAGPOLE: {
                objectToPaintOnMouse = new Inert();
                objectToPaintOnMouse->setCurrentTexture(QPixmap(objectToPaintOnMouse->loadTexture(":/resources/graphics/flagpole.png").scaled(block_size, block_size*11)));
                objectToPaintOnMouse->setOpacity(0.5);
                break;
        }
        case CASTLE: {
                objectToPaintOnMouse = new Inert();
                objectToPaintOnMouse->setCurrentTexture(QPixmap(objectToPaintOnMouse->loadTexture(":/resources/graphics/castle.png").scaled(block_size*4, block_size*4)));
                objectToPaintOnMouse->setOpacity(0.5);
                break;
        }
        case GOOMBA: {
            objectToPaintOnMouse = new Goomba();
            objectToPaintOnMouse->setOpacity(0.5);
            break;
        }
        case TURTLE: {
            objectToPaintOnMouse = new Koopa();
            objectToPaintOnMouse->setOpacity(0.5);
            break;
        }
        case MARIO: {
            objectToPaintOnMouse = new Mario();
            objectToPaintOnMouse->setOpacity(0.5);
            break;
        }
        default: {
            break;
        }
    }
}

void LevelEditorEngine::advance() {
    //for(Entity * entity : entities){
    // The level editor doesn't have animations
    //}
    levelEditorView->repaint();
}

void LevelEditorEngine::start(){
    //We setup the game engine : A timer that calls advance every 10ms
    QObject::connect(&engine, SIGNAL(timeout()), this, SLOT(advance()));

    engine.setTimerType(Qt::PreciseTimer);
    engine.setInterval(tickrate); // possible de le passer en dynamique

    engine.start();
}

int LevelEditorEngine::getLineFromMousePosition()
{
     return floor(levelEditorView->mapFromGlobal(QCursor::pos()).y()/block_size);
}

int LevelEditorEngine::getColumnFromMousePosition()
{
     return floor( (levelEditorView->mapFromGlobal(QCursor::pos()).x() + levelEditorView->getCameraPosition() - levelEditorView->getWindowSize().width()/2) / block_size);
}

void LevelEditorEngine::saveLevel()
{

}

void LevelEditorEngine::clearMap()
{
    for(Entity * entity : entities){
        objects.removeOne(entity);
        entities.removeOne(entity);
        delete entity;
    }
    for(Inert * inert : inerts){
        objects.removeOne(inert);
        inerts.removeOne(inert);
        delete inert;
    }
    if(fakeMario != nullptr){
        objects.removeOne(fakeMario);
        delete fakeMario;
        fakeMario = nullptr;
    }
}

void LevelEditorEngine::goBackToMainMenu()
{
    mainWindow->goBackToMainMenu();
}
