#ifndef S21_PAINTER_H
#define S21_PAINTER_H

#include <QWidget>
#include <QTimer>
#include <QResizeEvent>
#include <iostream>

#include "../includes/network.h"
#include "scene.h"

namespace s21 {

namespace Ui { class painter; }

class painter : public QWidget
{
    Q_OBJECT

public:
    painter(QWidget *parent = nullptr);
    ~painter();

private:
    Ui::painter *ui;
    Scene *scene;
    s21::Network *net_;
private slots:
    void onPredictButtonClicked_();
};

} // namespace s21
#endif // S21_PAINTER_H
