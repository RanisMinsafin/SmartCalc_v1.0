#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private:
  Ui::MainWindow *ui;
  QString str;
  int unar_flag;
  int operands_flag;
  int brackets_flag;
  int first_flag;
  int second_flag

      private slots : void void
                      null_flags();
  void convertation();
  void functions();
  void operators();
  void open_brackets();
  void close_brackets();
  void on_pushButton_pow_clicked();
  void on_pushButton_clear_clicked();

  void on_pushButton_equal_sign_clicked();
};

#endif  // MAINWINDOW_H
