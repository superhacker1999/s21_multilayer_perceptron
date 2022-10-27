#ifndef S21_PAINTER_H
#define S21_PAINTER_H

#include <QWidget>

namespace s21 {
class painter : public QWidget {
  Q_OBJECT
  public:
    explicit painter(QWidget *parent = nullptr);

  signals:

};  // class painter
} // namespace s21

#endif // S21_PAINTER_H
