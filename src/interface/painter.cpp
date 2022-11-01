#include "painter.h"
#include "ui_painter.h"

s21::painter::painter(QWidget *parent)
    : QWidget(parent)
    , ui(new s21::Ui::painter)
{
    net_ = new s21::Network({50, 30}, 784, 26, 0.05);
    net_->UploadWeightsToNet(net_->LoadWeights("/Users/ritapryanik/Desktop/mlp/src/weights26640x100x005.txt"));  // загрузить выгруженные веса
    ui->setupUi(this);
    ui->predict_button->setEnabled(false);
    ui->choose_image->setEnabled(false);
    connect(ui->picture, SIGNAL(toggled(bool)), this, SLOT(enableUploading_()));
    connect(ui->choose_image, SIGNAL(clicked()), this, SLOT(uploadImage_()));
    connect(ui->paint, SIGNAL(toggled(bool)), this, SLOT(paintLetter_()));
    connect(ui->predict_button, SIGNAL(clicked()), this, SLOT(onPredictButtonClicked_()));
    fillAlphabet_();
    connect(ui->delete_nah, SIGNAL(clicked()), this, SLOT(clearScene_()));

    picture_place_ = new QLabel(this);
    picture_place_->setGeometry(28, 28, 420, 420);
}

s21::painter::~painter()
{
    delete ui;
}

void s21::painter::paintLetter_() {
    ui->choose_image->setEnabled(false);
    picture_place_->hide();
    scene = new Scene();
    ui->painter_obj->setScene(scene);
    ui->painter_obj->setFixedSize(420, 420);
    ui->painter_obj->setSceneRect(0, 0, 420, 420);
    ui->painter_obj->setStyleSheet("background-color:white;");
    ui->predict_button->setEnabled(true);
}

void s21::painter::enableUploading_() {
    ui->choose_image->setEnabled(true);
}

void s21::painter::uploadImage_() {
    QString file_path = QFileDialog::getOpenFileName(this, tr("Upload image"), QDir::homePath());
    QPixmap letter = QPixmap(file_path);
    picture_place_->setPixmap(letter);
    picture_place_->show();
    letter_ = letter;
    ui->predict_button->setEnabled(true);
}

void s21::painter::fillAlphabet_() {
    for (int i = 1; i <= 26; ++i)
       alphabet_.insert(std::make_pair(i, static_cast<char>('A' + i - 1)));
}

void s21::painter::clearScene_() {
    picture_place_->hide();
    scene->clear();
}

QImage s21::painter::applyEffectToImage(QImage src, QGraphicsEffect *effect, int extent) {
    if (src.isNull()) return QImage();
    if (!effect) return src;
    QGraphicsScene scene;
    QGraphicsPixmapItem item;
    item.setPixmap(QPixmap::fromImage(src));
    item.setGraphicsEffect(effect);
    scene.addItem(&item);
    QImage res(src.size()+QSize(extent * 2, extent * 2), QImage::Format_ARGB32);
    res.fill(Qt::transparent);
    QPainter ptr(&res);
    scene.render(&ptr, QRectF(), QRectF( -extent, -extent, src.width() + extent * 2, src.height() + extent * 2 ) );
    return res;
}

void writeLetterToFile(std::vector <double> input_data, std::string answer) {
    std::ofstream test_file;
    test_file.open("/Users/ritapryanik/Desktop/mlp/dataset/interface-letters.txt", std::ios::app);
    test_file << answer << ",";
    for (size_t i = 0; i < input_data.size(); i++)
    {
      test_file << input_data[i] << ",";
    }
    test_file << "\n";

}

void s21::painter::addBlur_() {
    if (ui->paint->isChecked()) {
        letter_ = ui->painter_obj->grab();
    }
    QGraphicsBlurEffect *blur = new QGraphicsBlurEffect;
    blur->setBlurRadius(8);
    QImage image = letter_.toImage();

    QImage result = applyEffectToImage(image, blur);
    letter_ = QPixmap::fromImage(result).scaled(28, 28, Qt::KeepAspectRatio, Qt::FastTransformation);
}

void s21::painter::noBlur_() {
    if (ui->paint->isChecked()) {
        letter_ = ui->painter_obj->grab();
    }
    letter_ = letter_.scaled(28, 28, Qt::KeepAspectRatio, Qt::FastTransformation);
}

void s21::painter::onPredictButtonClicked_() {
//  addBlur_();
  noBlur_();
  QImage result = letter_.toImage();
  QColor pixel_;
  std::vector<double> input_data;
  int red, green, blue;
  double max = -1.0;
  for (int i = 0; i < result.height(); ++i) {
    for (int j = 0; j < result.width(); ++j) {
      pixel_ = result.pixel(i, j);
      pixel_.getRgb(&red, &green, &blue);
      std::cout << red << " " << green << " " << blue << std::endl;
      red = 255 - red;
      green = 255 - green;
      blue = 255 - blue;
      double colour = (red + green + blue) / 3.0;
      if (colour > max) max = colour;
      input_data.push_back(double(red + green + blue) / 3.0);
    }
  }

  for (auto it = input_data.begin(); it != input_data.end(); ++it) {
      if (*it != 0) *it = *it / max;
  }
  writeLetterToFile(input_data, ui->answer->text().toStdString());
  auto letter = alphabet_.find(net_->Predict(input_data));
  if (letter != alphabet_.end()) {
    ui->label->setText(QString((*letter).second));
  } else {
      ui->label->setText("Я ничего не понимаю(((");
  }

//  auto res_vec = net_->Predict_test(input_data);
//  for (auto it = res_vec.begin(); it != res_vec.end(); ++it) {
//    qDebug() << *it << " ";
//  }

}


