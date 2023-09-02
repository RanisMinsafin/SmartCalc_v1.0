#ifndef CREDITWINDOW_H
#define CREDITWINDOW_H

#include <QDialog>

#include "ui_creditwindow.h"

extern "C" {
#include "../../s21_credit.h"
}

namespace Ui {
class CreditWindow;
}

class CreditWindow : public QDialog {
  Q_OBJECT

 public:
  explicit CreditWindow(QWidget* parent = nullptr);
  ~CreditWindow();

 private slots:
  void set_validators();
  void on_pushButton_calculate_clicked();
  s21_info double_assignment();
  int input_check();
  int null_check(QString str);
  void output_null();
  char* q_converter(QString q_str);
  void round_function(double* number);
  void min_pay_check(s21_res* res);
  void str_clear();
  void result_show();

 private:
  Ui::CreditWindow* ui;
  QString q_pay;
  QString q_overpay;
  QString q_sum;
  QString q_pay_clone;
};

#endif  // CREDITWINDOW_H
