#ifndef SNAKE_H
#define SNAKE_H

#include <QGraphicsItem>

class GameController;


class Snake : public QGraphicsItem
{
public:
    enum Direction {
        NoMove,
        MoveLeft,
        MoveRight,
        MoveUp,
        MoveDown
    };

    Snake(GameController &controller);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
    QPainterPath shape() const;

    void setMoveDirction(Direction dir);

private:
    QPointF head;
    QList<QPointF> tail;
    GameController &controller;
    int growing;
    int tickCounter;
    int speed;
    Direction moveDirection;

    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();

    void handleCollisions();

protected:
    void advance(int step);
};

#endif // SNAKE_H
