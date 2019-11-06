#include <QPainter>
#include "snake.h"
#include "gamecontroller.h"

static const qreal SNAKE_SIZE = 10;

Snake::Snake(GameController &controller) :
    head(0, 0),
    controller(controller),
    growing(7),
//    tickCounter(0),
    speed(3),
    moveDirection(NoMove)
{

}

QRectF Snake::boundingRect() const
{
    qreal minX = head.x();
    qreal minY = head.y();
    qreal maxX = head.x();
    qreal maxY = head.y();

    // 遍历蛇身的每一个方块，找出最大的x、y，最小的x、y。
    foreach (QPointF p, tail) {
        maxX = p.x() > maxX ? p.x() : maxX;
        maxY = p.y() > maxY ? p.y() : maxY;
        minX = p.x() < minX ? p.x() : minX;
        minY = p.y() < minY ? p.y() : minY;
    }

    QPointF tl = mapFromScene(QPointF(minX, minY));
    QPointF br = mapFromScene(QPointF(maxX, maxY));

    QRectF bound = QRectF(tl.x(),
                          tl.y(),
                          br.x() - tl.x() + SNAKE_SIZE,
                          br.y() - tl.y() + SNAKE_SIZE);

    return bound;
}

void Snake::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->save();
    painter->fillPath(shape(), Qt::yellow);
    painter->restore();
}

QPainterPath Snake::shape() const
{
    QPainterPath path;
    path.setFillRule(Qt::WindingFill);

    path.addRect(QRectF(0, 0, SNAKE_SIZE, SNAKE_SIZE));

    foreach (QPointF p, tail) {
        QPointF itemp = mapFromScene(p);
        path.addRect(QRectF(itemp.x(), itemp.y(), SNAKE_SIZE, SNAKE_SIZE));
    }

    return path;
}

void Snake::setMoveDirction(Snake::Direction dir)
{
    moveDirection = dir;
}

void Snake::moveLeft()
{
    head.rx() -= SNAKE_SIZE;
    if (head.rx() < -100)
        head.rx() = 100;
}

void Snake::moveRight()
{
    head.rx() += SNAKE_SIZE;
    if (head.rx() > 100)
        head.rx() = -100;
}

void Snake::moveUp()
{
    head.ry() -= SNAKE_SIZE;
    if (head.ry() < -100)
        head.ry() = 100;
}

void Snake::moveDown()
{
    head.ry() += SNAKE_SIZE;
    if (head.ry() > 100)
        head.ry() = -100;
}

void Snake::handleCollisions()
{
    QList<QGraphicsItem *> collisions = collidingItems();

    foreach (QGraphicsItem *collidingItem, collisions) {
        controller.snakeAteFood(this, static_cast<Food *>(collidingItem));
        growing += 1;
    }

    if (tail.contains(head)) {
        controller.snakeAteItself(this);
    }
}

void Snake::advance(int step)
{
    if (!step) return;

    if (tickCounter++ % speed != 0) return;

    if (moveDirection == NoMove) return;

    if (growing > 0) {
        QPointF tailPoint = head;
        tail << tailPoint;
        growing -= 1;
    } else {
        tail.takeFirst();
        tail << head;
    }


    switch (moveDirection) {
        case MoveLeft:
            moveLeft();
            break;
        case MoveRight:
            moveRight();
            break;
        case MoveUp:
            moveUp();
            break;
        case MoveDown:
            moveDown();
            break;
        case NoMove:
            break;
    }

    setPos(head);
    handleCollisions();
}
