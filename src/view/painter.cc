#include "painter.h"

Painter::Painter(QObject *parent) : QGraphicsScene{parent} {}

Painter::~Painter() {}

void Painter::mousePressEvent(QGraphicsSceneMouseEvent *event) {
//    QRadialGradient radial(0, 0, 10);
//    radial.setColorAt(0, Qt::black);
//    radial.setColorAt(0.5, Qt::gray);
//    radial.setColorAt(1, Qt::white);
//    QBrush brush(radial);
    addEllipse(event->scenePos().x() - 5,
               event->scenePos().y() - 5,
               10, 10,
               QPen(Qt::NoPen),
               QBrush(Qt::black));
    previousPoint = event->scenePos();
}

void Painter::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    addLine(previousPoint.x(),
            previousPoint.y(),
            event->scenePos().x(),
            event->scenePos().y(),
            QPen(Qt::black,10,Qt::SolidLine,Qt::RoundCap));
    previousPoint = event->scenePos();
}
