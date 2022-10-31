#include "scene.h"

s21::Scene::Scene(QObject *parent) : QGraphicsScene(parent)
{

}

s21::Scene::~Scene()
{

}

void s21::Scene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    // При нажатии кнопки мыши отрисовываем эллипс
    addEllipse(event->scenePos().x() - 5,
               event->scenePos().y() - 5,
               10,
               10,
               QPen(Qt::NoPen),
               QBrush(Qt::white));
    // Сохраняем координаты точки нажатия
    previousPoint = event->scenePos();
}

void s21::Scene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    // Отрисовываем линии с использованием предыдущей координаты
    addLine(previousPoint.x(),
            previousPoint.y(),
            event->scenePos().x(),
            event->scenePos().y(),
            QPen(QColor::fromRgb(255, 255, 255), 30, Qt::SolidLine, Qt::RoundCap));
    // Обновляем данные о предыдущей координате
    previousPoint = event->scenePos();
}
