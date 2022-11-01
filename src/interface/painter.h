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
    std::map<int, char> alphabet_;
    void fillAlphabet_();
    QColor inverseColors_(QColor pixel);
    void compressImage_();
    void normalizeData_(std::vector<double> &input_data, double max);

private slots:
    void onPredictButtonClicked_();
    void clearScene_();
    void uploadImage_();
    void paintLetter_();
    void enableUploading_();

};

} // namespace s21
#endif // S21_PAINTER_H
