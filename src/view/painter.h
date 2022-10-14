#ifndef PAINTER_H
#define PAINTER_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>


class Painter : public QGraphicsScene
{
public:
    explicit Painter(QObject *parent = nullptr);
    ~Painter();

private:
    QPointF previousPoint;

private:
    void mousePressEvent(QGraphicsSceneMouseEvent * event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
};

#endif // PAINTER_H
