#include "painter.h"

Painter::Painter(QObject *parent) : QGraphicsScene{parent} {}

Painter::~Painter() {}

void Painter::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    addEllipse(event->scenePos().x() - 5,
               event->scenePos().y() - 5,
               10, 10,
               QPen(Qt::NoPen),
               QBrush(Qt::black));
    previousPoint = event->scenePos();
}

void Painter::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    draw(100, 15, event->scenePos());
    draw(150, 13, event->scenePos());
    draw(255, 10, event->scenePos());
    previousPoint = event->scenePos();
}

void Painter::draw(int alpha, int size, QPointF now) {
    addLine(previousPoint.x(),
            previousPoint.y(),
            now.x(),
            now.y(),
            QPen(QColor(0, 0, 0, alpha), size, Qt::SolidLine, Qt::RoundCap));
}

//  кладбище

/*
 Painter::Painter(QObject *parent) : QGraphicsScene{parent} {
//    painter = new QPainter;
//    QRadialGradient radial(0, 0, 10);
//    radial.setColorAt(0, Qt::black);
//    radial.setColorAt(0.5, Qt::gray);
//    radial.setColorAt(1, Qt::white);
//    painter->setPen(Qt::transparent);
//    painter->setBrush(radial);
}

Painter::~Painter() {
//    delete painter;
}

void Painter::paintEvent(QPaintEvent *) {
    painter = new QPainter();
    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->setPen(QPen(Qt::black, 5, Qt::DashDotLine, Qt::RoundCap));
    painter->drawLine(width()/2, 0, width()/2, height());

//        painter->drawLine(previousPoint.x(),
//                          previousPoint.y(),
//                          nowPoint.x(),
//                          nowPoint.y());
//    painter->drawEllipse(previousPoint.x() - 5,
//                         previousPoint.y() -5,
//                             10, 10);
}

void Painter::mousePressEvent(QGraphicsSceneMouseEvent *event) {
//    painter->drawEllipse(event->scenePos().x() - 5,
//                         event->scenePos().y() - 5,
//                         10, 10);
//    addEllipse(event->scenePos().x() - 5,
//               event->scenePos().y() - 5,
//               10, 10,
//               QPen(Qt::NoPen),
//               QBrush(Qt::black));
    previousPoint = event->scenePos();
    update();
}

void Painter::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    nowPoint = event->scenePos();
    update();
//    painter->drawLine(previousPoint.x(),
//                      previousPoint.y(),
//                      event->scenePos().x(),
//                      event->scenePos().y());
//    addLine(previousPoint.x(),
//            previousPoint.y(),
//            event->scenePos().x(),
//            event->scenePos().y(),
//            QPen(Qt::black, 10, Qt::SolidLine, Qt::RoundCap));
    previousPoint = event->scenePos();
}*/
