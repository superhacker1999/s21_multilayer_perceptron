#include "painter.h"
#include "ui_painter.h"

s21::painter::painter(QWidget *parent)
    : QWidget(parent),
      ui(new s21::Ui::painter),
      controller_("../../../../../dataset/interface-letters.txt", "../../../../weights/weights26640x100x005.txt")

{
    net_ = new s21::Network({50, 30}, 784, 26, 0.05);
    ui->setupUi(this);
    fillAlphabet_();

    scene = new Scene();
    picture_place_ = new QLabel(this);  // label for displaying picture uploaded by user
    picture_place_->setGeometry(28, 28, 420, 420);

    ui->painter_obj->setStyleSheet("background-color:white;");

    ui->predict_button->setEnabled(false);
    ui->choose_image->setEnabled(false);

    connect(ui->picture, SIGNAL(toggled(bool)), this, SLOT(enableUploading_()));
    connect(ui->paint, SIGNAL(toggled(bool)), this, SLOT(paintLetter_()));
    connect(ui->choose_image, SIGNAL(clicked()), this, SLOT(uploadImage_()));
    connect(ui->predict_button, SIGNAL(clicked()), this, SLOT(onPredictButtonClicked_()));
    connect(ui->delete_nah, SIGNAL(clicked()), this, SLOT(clearScene_()));

}

s21::painter::~painter()
{
    delete ui;
}

void s21::painter::paintLetter_() {
    ui->choose_image->setEnabled(false);
    picture_place_->hide();
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
    QPixmap letter = QPixmap(file_path).scaled(420, 420, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
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
    ui->label->clear();
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

void s21::painter::compressImage_() {
    if (ui->paint->isChecked()) {
        letter_ = ui->painter_obj->grab();
    }
    letter_ = letter_.scaled(28, 28, Qt::KeepAspectRatio, Qt::SmoothTransformation);
}

void s21::painter::onPredictButtonClicked_() {
  compressImage_();
  QImage result = letter_.toImage();
  QColor pixel_;
  std::vector<double> input_data;
  int red, green, blue;
  double max = -1.0;
  for (int i = 0; i < result.height(); ++i) {
    for (int j = 0; j < result.width(); ++j) {
      pixel_ = result.pixel(i, j);
      pixel_.getRgb(&red, &green, &blue);
      double colour = ((255 - red) + (255 - green) + (255 - blue)) / 3.0;
      if (colour > max) max = colour;
      input_data.push_back(double(colour));
    }
  }

//  int i = 0;
//  for (auto it = input_data.begin(); it != input_data.end(); ++it) {
//      if (i % 28 == 0) std::cout << "\n";
//      i++;
//      printf("%5.2lf ", *it);
//  }
//  normalizeData_(input_data, max);
  writeLetterToFile(input_data, ui->answer->text().toStdString());
  auto letter = alphabet_.find(controller_.getPrediction());
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


