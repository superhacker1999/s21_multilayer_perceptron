#ifndef VIEW_H
#define VIEW_H

#include <QGraphicsScene>
#include <QMainWindow>
#include <QPainter>
#include <QColor>

#include <QResizeEvent>

#include "painter.h"

QT_BEGIN_NAMESPACE
namespace Ui { class view; }
QT_END_NAMESPACE

class view : public QMainWindow {
    Q_OBJECT

public:
    view(QWidget *parent = nullptr);
    ~view();

private:
    Ui::view *ui_;
    QGraphicsScene *scene_;
};
#endif // VIEW_H
