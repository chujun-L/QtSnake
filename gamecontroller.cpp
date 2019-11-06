#include <QGraphicsScene>
#include <QEvent>
#include <QKeyEvent>
#include "gamecontroller.h"
#include "food.h"
#include "snake.h"

GameController::GameController(QGraphicsScene &scene, QObject *parent) :
    QObject(parent),
    scene(scene),
    snake(new Snake(*this))
{
    timer.start(1000 / 33);

    Food *food = new Food(0, -50);
    scene.addItem(food);

    scene.addItem(snake);
    scene.installEventFilter(this);

    resume();
}

void GameController::snakeAteFood(Snake *, Food *food)
{
    scene.removeItem(food);
    delete food;

    addNewFood();
}

void GameController::snakeAteItself(Snake *)
{
    QTimer::singleShot(0, this, SLOT(gameOver()));
}

void GameController::resume()
{
    connect(&timer, SIGNAL(timeout()), &scene, SLOT(advance()));
}

void GameController::gameOver()
{
    scene.clear();

    snake = new Snake(*this);
    scene.addItem(snake);
    addNewFood();
}

void GameController::addNewFood()
{
    int x, y;

    do {
        x = static_cast<int>(qrand() % 100 / 10);
        y = static_cast<int>(qrand() % 100 / 10);

        x *= 10;
        y *= 10;
    } while(snake->shape().contains(snake->mapFromScene(QPointF(x + 5, y + 5))));

    Food *food = new Food(x, y);
    scene.addItem(food);
}

void GameController::handleKeyPress(QKeyEvent *evt)
{
    switch (evt->key()) {
        case Qt::Key_Left:
            snake->setMoveDirction(Snake::MoveLeft);
            break;
        case Qt::Key_Right:
            snake->setMoveDirction(Snake::MoveRight);
            break;
        case Qt::Key_Up:
            snake->setMoveDirction(Snake::MoveUp);
            break;
        case Qt::Key_Down:
            snake->setMoveDirction(Snake::MoveDown);
            break;
    }
}

bool GameController::eventFilter(QObject *obj, QEvent *evt)
{
    if (evt->type() == QEvent::KeyPress) {
        handleKeyPress(reinterpret_cast<QKeyEvent *>(evt));
        return true;
    } else {
        return QObject::eventFilter(obj, evt);
    }
}
