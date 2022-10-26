#include "view.h"
#include "ui_view.h"

namespace s21 {
view::view(QWidget *parent) : QMainWindow(parent), ui(new Ui::view) {
  ui->setupUi(this);
}

view::~view() {
  delete ui;
}
} // namespace s21
