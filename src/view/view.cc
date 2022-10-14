#include "view.h"
#include "ui_view.h"

view::view(QWidget *parent) : QMainWindow(parent), ui_(new Ui::view) {
    ui_->setupUi(this);

    scene_ = new Painter();
    ui_->graphicsView->setScene(scene_);
    scene_->setSceneRect(0, 0, 511, 511);
    scene_->setBackgroundBrush(QColor("#FFFFFF"));

    ui_->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui_->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);



}

view::~view() {
    delete scene_;
    delete ui_;
}

