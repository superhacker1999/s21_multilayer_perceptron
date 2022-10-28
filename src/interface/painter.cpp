#include "painter.h"
#include "ui_painter.h"

s21::painter::painter(QWidget *parent)
    : QWidget(parent)
    , ui(new s21::Ui::painter)
{
    ui->setupUi(this);

    scene = new Scene();
//    ui->graphicsView->setScene(scene);
//    ui->graphicsView->;
}

s21::painter::~painter()
{
    delete ui;
}

