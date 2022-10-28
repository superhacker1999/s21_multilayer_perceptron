#include "painter.h"
#include "ui_painter.h"

s21::painter::painter(QWidget *parent)
    : QWidget(parent)
    , ui(new s21::Ui::painter)
{
    net_ = new s21::Network({50, 30}, 784, 26, 0.05);
    net_->UploadWeightsToNet(net_->LoadWeights("/Users/ritapryanik/Desktop/mlp/src/weights26640x100x005.txt"));  // загрузить выгруженные веса
    ui->setupUi(this);
    connect(ui->predict_button, SIGNAL(clicked()), this, SLOT(onPredictButtonClicked_()));

    scene = new Scene();
    ui->painter_obj->setScene(scene);
}

s21::painter::~painter()
{
    delete ui;
}

QImage s21::painter::applyEffectToImage(QImage src, QGraphicsEffect *effect, int extent)
{
    if (src.isNull()) return QImage();   //No need to do anything else!
    if (!effect) return src;             //No need to do anything else!
    QGraphicsScene scene;
    QGraphicsPixmapItem item;
    item.setPixmap(QPixmap::fromImage(src));
    item.setGraphicsEffect(effect);
    scene.addItem(&item);
    QImage res(src.size()+QSize(extent*2, extent*2), QImage::Format_ARGB32);
    res.fill(Qt::transparent);
    QPainter ptr(&res);
    scene.render(&ptr, QRectF(), QRectF( -extent, -extent, src.width()+extent*2, src.height()+extent*2 ) );
    return res;
}


void s21::painter::onPredictButtonClicked_() {
  std::vector<double> input_data;
//  QSize new_size(28, 28);
  QPixmap pixmap = ui->painter_obj->grab();
  pixmap = pixmap.scaled(28, 28, Qt::KeepAspectRatio, Qt::SmoothTransformation);

//  QGraphicsBlurEffect *blur = new QGraphicsBlurEffect;
//  blur->setBlurRadius(1);
  QImage image = pixmap.toImage();
//  QImage result = applyEffectToImage(image, blur);
  QColor pixel_;
  int red, green, blue;
  for (int i = 0; i < image.height(); ++i) {
    for (int j = 0; j < image.width(); ++j) {
      pixel_ = image.pixel(j, i);
      pixel_.getRgb(&red, &green, &blue);
      input_data.push_back((299 * red + 587 * green + 114 * blue) / 1000 );
    }
  }
  int i = 0;
  for (auto it = input_data.begin(); it != input_data.end(); ++it) {
      if (i % 28 == 0) std::cout << "\n";
      i++;
      printf("%.0lf ", *it);
  }
}
