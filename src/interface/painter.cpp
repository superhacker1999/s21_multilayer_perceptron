#include "painter.h"
#include "ui_painter.h"

s21::painter::painter(QWidget *parent)
    : QWidget(parent)
    , ui(new s21::Ui::painter)
{
    ui->setupUi(this);
    connect(ui->predict_button, SIGNAL(clicked()), this, SLOT(onPredictButtonClicked_()));

    scene = new Scene();
    ui->painter_obj->setScene(scene);
}

s21::painter::~painter()
{
    delete ui;
}


void s21::painter::onPredictButtonClicked_() {
  std::vector<double> input_data;
  QSize new_size(28, 28);
  QPixmap pixmap = ui->painter_obj->grab();
  pixmap = pixmap.scaled(new_size, Qt::KeepAspectRatio);
  QImage image = pixmap.toImage().convertToFormat(QImage::Format_Mono);
  QColor pixel_;
  int red, green, blue;
  for (int i = 0; i < image.width(); ++i) {
    for (int j = 0; j < image.height(); ++j) {
      pixel_ = image.pixel(i, j);
      pixel_.getRgb(&red, &green, &blue);
      input_data.push_back(((red + green + blue) / 3.0) / 255.0);
    }
  }
  for (auto it = input_data.begin(); it != input_data.end(); ++it)
    std::cout << *it << " ";
}
