#ifndef FOOD_H
#define FOOD_H

// 被添加到场景的元素
#include <QGraphicsItem>


class Food : public QGraphicsItem
{
public:
    Food(qreal x, qreal y);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
    QPainterPath shape() const;
};

#endif // FOOD_H
