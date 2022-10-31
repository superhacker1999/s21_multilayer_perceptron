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
    fillAlphabet_();

    scene = new Scene();
    ui->painter_obj->setScene(scene);
    ui->painter_obj->setFixedSize(420, 420);
    ui->painter_obj->setSceneRect(0, 0, 420, 420);
    ui->painter_obj->setStyleSheet("background-color:black;");
    connect(ui->delete_nah, SIGNAL(clicked()), this, SLOT(clearScene_()));
}

s21::painter::~painter()
{
    delete ui;
}

void s21::painter::fillAlphabet_() {
    for (int i = 1; i <= 26; ++i)
       alphabet_.insert(std::make_pair(i, static_cast<char>('A' + i - 1)));
}

void s21::painter::clearScene_() {
    scene->clear();
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
  QPixmap pixmap = ui->painter_obj->grab();
  QGraphicsBlurEffect *blur = new QGraphicsBlurEffect;
  blur->setBlurRadius(8);
  QImage image = pixmap.toImage();

  QImage result = applyEffectToImage(image, blur);
  pixmap = QPixmap::fromImage(result).scaled(28, 28, Qt::KeepAspectRatio, Qt::FastTransformation);
//  pixmap = pixmap.scaled(28, 28, Qt::KeepAspectRatio, Qt::FastTransformation);

  result = pixmap.toImage();
//  QImage image = pixmap.toImage();
  QColor pixel_;
  int red, green, blue;
  double max = -1.0;
  for (int i = 0; i < result.height(); ++i) {
    for (int j = 0; j < result.width(); ++j) {
      pixel_ = result.pixel(i, j);
      pixel_.getRgb(&red, &green, &blue);
      double colour = (red + green + blue) / 3.0;
      if (colour > max) max = colour;
      input_data.push_back(double(red + green + blue) / 3.0);
    }
  }

  for (auto it = input_data.begin(); it != input_data.end(); ++it) {
      *it = *it / max;
  }
  auto letter = alphabet_.find(net_->Predict(input_data));
  qDebug() << (*letter).second << " ";
  if (letter != alphabet_.end()) {
    ui->label->setText(QString((*letter).second));
  } else {
      ui->label->setText("Я ничего не понимаю(((");
  }

//  auto res_vec = net_->Predict_test(input_data);
//  for (auto it = res_vec.begin(); it != res_vec.end(); ++it) {
//    qDebug() << *it << " ";
//  }


//  int i = 0;
//  for (auto it = input_data.begin(); it != input_data.end(); ++it) {
//      if (i % 28 == 0) std::cout << "\n";
//      i++;
//      printf("%3.2lf ", *it);
//  }
}
