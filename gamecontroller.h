#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <QObject>
#include <QTimer>
#include "snake.h"
#include "food.h"

class Snake;
class Food;
class QGraphicsScene;


class GameController : public QObject
{
    Q_OBJECT
public:
    explicit GameController(QGraphicsScene &scene, QObject *parent = nullptr);

    void snakeAteFood(Snake *, Food *food);
    void snakeAteItself(Snake *);

//signals:

public slots:
    void resume();
    void gameOver();

private:
    QTimer timer;
    QGraphicsScene &scene;
    Snake *snake;

    void addNewFood();
    void handleKeyPress(QKeyEvent *evt);

protected:
    bool eventFilter(QObject *obj, QEvent *evt);

};

#endif // GAMECONTROLLER_H
