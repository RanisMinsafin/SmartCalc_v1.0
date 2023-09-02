#ifndef DEPOSITWINDOW_H
#define DEPOSITWINDOW_H

#include <QDate>
#include <QDialog>
#include <QLineEdit>

#include "ui_depositwindow.h"

extern "C" {
#include "../../s21_deposit.h"
}

namespace Ui {
class depositwindow;
}

class depositwindow : public QDialog {
  Q_OBJECT

 public:
  explicit depositwindow(QWidget* parent = nullptr);
  ~depositwindow();

 private slots:
  void edit_date();
  void start_numbers();
  void set_validators();
  int input_check();
  int null_check(QString str);
  void output_null();
  void frequency_return(s21_term* info);
  void double_return(s21_term* info);
  void days_return(s21_term* info);
  s21_term data_return();
  void data_show(s21_result* res);
  void str_clear();
  void on_pushButton_calculate_clicked();

 private:
  Ui::depositwindow* ui;
  QDate current;
  QString income;
  QString tax;
  QString total_sum;
  QString clone_total_sum;
};

#endif  // DEPOSITWINDOW_H
