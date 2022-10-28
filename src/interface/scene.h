#ifndef S21_SCENE_H
#define S21_SCENE_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsSceneMouseEvent>
#include <QTimer>

namespace s21 {

class Scene : public QGraphicsScene {
   Q_OBJECT
 public:
    explicit Scene(QObject *parent = nullptr);
    ~Scene();
 private:
    QPointF previousPoint;
 private:
    // Для рисования используем события мыши
    void mousePressEvent(QGraphicsSceneMouseEvent * event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

};

} // namespace s21

#endif // S21_SCENE_H
