#ifndef S21_VIEW_H
#define S21_VIEW_H

#include <QMainWindow>

namespace s21 {
namespace Ui { class view; }
class view : public QMainWindow {
  Q_OBJECT

  public:
    view(QWidget *parent = nullptr);
    ~view();

  private:
    Ui::view *ui;
};  // class view
} // namespace s21
#endif // S21_VIEW_H
