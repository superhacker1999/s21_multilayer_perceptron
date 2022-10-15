#ifndef PAINTER_H
#define PAINTER_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QColor>
//#include <QPaintEvent>
//#include <QPainter>


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
    void draw(int alpha, int size, QPointF now);
};

#endif // PAINTER_H
