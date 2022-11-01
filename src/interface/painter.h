#ifndef S21_PAINTER_H
#define S21_PAINTER_H

#include <QWidget>
#include <QTimer>
#include <QResizeEvent>
#include <iostream>

#include "../includes/network.h"
#include <QGraphicsBlurEffect>
#include "scene.h"
#include <QGraphicsPixmapItem>
#include <QDebug>
#include <map>
#include <fstream>
#include <QFileDialog>
#include <QLabel>

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
    QPixmap letter_;
    QLabel *picture_place_;
    s21::Network *net_;
    QImage applyEffectToImage(QImage src, QGraphicsEffect *effect, int extent = 0);
    std::map<int, char> alphabet_;
    void fillAlphabet_();
    void addBlur_();
    QColor inverseColors_(QColor pixel);
    void noBlur_();

private slots:
    void onPredictButtonClicked_();
    void clearScene_();
    void uploadImage_();
    void paintLetter_();
    void enableUploading_();

};

} // namespace s21
#endif // S21_PAINTER_H
