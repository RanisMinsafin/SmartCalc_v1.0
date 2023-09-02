#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDoubleValidator>
#include <QIntValidator>
#include <QMainWindow>
#include <cstring>
#include <iostream>

#include "creditwindow.h"
#include "depositwindow.h"
#include "graphwindow.h"
#include "ui_mainwindow.h"

extern "C" {
#include "../../s21_smartcalc.h"
}

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget* parent = nullptr);
  ~MainWindow();

 private:
  Ui::MainWindow* ui;
  QString str;
  QString clone;
  QString x_value;
  QString x_max_value;
  QString x_min_value;
  int x_flag;
  int unar_flag;
  int not_null;
  int operands_flag;
  int brackets_flag;
  int result_flag;
  int graph_flag;
  int counter;
  char x_char[30];
  char string[300];
  s21_list_t* list;

 private slots:
  void set_validators();
  void null_flags();
  void str_check();
  void unar_check();
  void result_check();
  void x_converter();
  void convertation();
  void functions();
  void operators();
  void open_graph();
  void open_brackets();
  void func_brackets();
  void close_brackets();
  void str_converter();
  void equal_operations();
  void on_pushButton_pow_clicked();
  void on_pushButton_clear_clicked();
  void on_pushButton_equal_sign_clicked();
  void on_pushButton_mod_clicked();
  void on_pushButton_x_clicked();
  void is_empty();
  void x_check(double* result, double* x_max, double* x_min);
  void on_pushButton_credit_clicked();
  void on_pushButton_deposit_clicked();
};

#endif  // MAINWINDOW_H
