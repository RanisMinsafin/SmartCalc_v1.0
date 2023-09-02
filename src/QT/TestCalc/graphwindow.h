#ifndef GRAPHWINDOW_H
#define GRAPHWINDOW_H

#include <string.h>

#include <QDialog>
#include <QVector>
#include <iostream>

#include "ui_graphwindow.h"

namespace Ui {
class GraphWindow;
}

extern "C" {
#include "../../s21_smartcalc.h"
}

class GraphWindow : public QDialog {
  Q_OBJECT

 public:
  explicit GraphWindow(QWidget* parent = nullptr);
  ~GraphWindow();

 public slots:
  void widget_edit();
  void y_calculate(char* str_clone, char* x_clone, double* result);
  void draw_result(double result, double str_max, double str_min,
                   const char* str, const char* x_char);

 private:
  Ui::GraphWindow* ui;
  s21_list_t* list;
  double xBegin, xEnd, step, X, Y;
  double result, x_min, x_max, y_max, y_min;
  char str[200];
  QString text_str;
  QVector<double> x, y;
};
#endif  // GRAPHWINDOW_H
