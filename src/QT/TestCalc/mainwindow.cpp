#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  setFixedSize(549, 366);
  set_validators();
  connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(convertation()));
  connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(convertation()));
  connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(convertation()));
  connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(convertation()));
  connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(convertation()));
  connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(convertation()));
  connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(convertation()));
  connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(convertation()));
  connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(convertation()));
  connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(convertation()));
  connect(ui->pushButton_dot, SIGNAL(clicked()), this, SLOT(operators()));
  connect(ui->pushButton_br_open, SIGNAL(clicked()), this,
          SLOT(open_brackets()));
  connect(ui->pushButton_br_close, SIGNAL(clicked()), this,
          SLOT(close_brackets()));
  connect(ui->pushButton_minus, SIGNAL(clicked()), this, SLOT(operators()));
  connect(ui->pushButton_plus, SIGNAL(clicked()), this, SLOT(operators()));
  connect(ui->pushButton_multiply, SIGNAL(clicked()), this, SLOT(operators()));
  connect(ui->pushButton_divide, SIGNAL(clicked()), this, SLOT(operators()));
  connect(ui->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->pushButton_sin, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->pushButton_cos, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->pushButton_asin, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->pushButton_acos, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->pushButton_ln, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->pushButton_log, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->pushButton_tan, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->pushButton_atan, SIGNAL(clicked()), this, SLOT(functions()));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::set_validators() {
  ui->result_show->setAlignment(Qt::AlignCenter | Qt::AlignRight);
  ui->x_show->setValidator(new QDoubleValidator(-1000000, 1000000, 7, this));
  ui->x_max->setValidator(new QDoubleValidator(-1000000, 1000000, 7, this));
  ui->x_min->setValidator(new QDoubleValidator(-1000000, 1000000, 7, this));

  ui->x_show->setMaxLength(6);
  ui->x_max->setMaxLength(6);
  ui->x_min->setMaxLength(6);
  on_pushButton_clear_clicked();
}

void MainWindow::null_flags() {
  unar_flag = 0;
  graph_flag = 0;
  operands_flag = 0;
  brackets_flag = 0;
  result_flag = 0;
  x_flag = 0;
  counter = 0;
}

void MainWindow::convertation() {
  if (counter < 256) {
    QPushButton *button = (QPushButton *)sender();
    if (button->text() >= '0' && button->text() <= '9') {
      operands_flag = 0;
      x_flag = 1;
      result_check();
      counter++;
    }
    str.append(button->text());
    ui->result_show->setText(str);
  }
}

void MainWindow::on_pushButton_x_clicked() {
  if (counter < 256 && x_flag != 1) {
    operands_flag = 0;
    result_check();
    counter++;
    x_flag = 1;
    graph_flag = 1;
    str.append('x');
  }
  ui->result_show->setText(str);
}

void MainWindow::result_check() {
  if (result_flag == 1) {
    str.clear();
    result_flag = 0;
  }
}

void MainWindow::operators() {
  QPushButton *button = (QPushButton *)sender();
  if (str.isEmpty() && button->text() != '-') str.append('0');
  if ((operands_flag == 0 || (unar_flag && button->text() == '-')) &&
      counter < 256) {
    str.append(button->text());
    ui->result_show->setText(str);
    operands_flag = 1;
    result_flag = 0;
    not_null = 0;
    x_flag = 0;
    unar_check();
    counter++;
  }
}

void MainWindow::unar_check() {
  if (str.endsWith('*') || str.endsWith('/'))
    unar_flag = 1;
  else if (str.endsWith('-') && unar_flag)
    unar_flag = 0;
}

void MainWindow::on_pushButton_mod_clicked() {
  QPushButton *button = (QPushButton *)sender();
  if (str.isEmpty() && button->text() != '-') str.append('0');
  if (operands_flag == 0 && counter < 256) {
    str.append(" mod ");
    ui->result_show->setText(str);
    operands_flag = 1;
    result_flag = 0;
    x_flag = 0;
    counter += 3;
  }
}

void MainWindow::open_brackets() {
  if ((operands_flag == 1 || str.isEmpty()) && counter < 256) {
    QPushButton *button = (QPushButton *)sender();
    str.append(button->text());
    ui->result_show->setText(str);
    brackets_flag++;
    unar_flag = 1;
    operands_flag = 1;
    x_flag = 0;
    counter++;
  }
}

void MainWindow::func_brackets() {
  str.append('(');
  ui->result_show->setText(str);
  brackets_flag++;
  unar_flag = 1;
  operands_flag = 1;
  x_flag = 0;
  counter++;
}

void MainWindow::close_brackets() {
  QPushButton *button = (QPushButton *)sender();
  if (brackets_flag > 0 && counter < 256) {
    str.append(button->text());
    ui->result_show->setText(str);
    brackets_flag--;
    x_flag = 1;
    counter++;
  }
}

void MainWindow::functions() {
  result_check();
  if ((operands_flag == 1 || str.isEmpty()) && counter < 256) {
    QPushButton *button = (QPushButton *)sender();
    str.append(button->text());
    func_brackets();
    ui->result_show->setText(str);
    counter += 3;
  }
}

void MainWindow::on_pushButton_pow_clicked() {
  if (str.isEmpty()) str.append('0');
  if (operands_flag == 0 && counter < 256) {
    str.append('^');
    ui->result_show->setText(str);
    operands_flag = 1;
    result_flag = 0;
    x_flag = 0;
    counter++;
  }
}

void MainWindow::on_pushButton_clear_clicked() {
  null_flags();
  str = "0";
  ui->result_show->setText(str);
  ui->x_show->clear();
  ui->x_max->clear();
  ui->x_min->clear();
  str.clear();
}

void MainWindow::open_graph() {
  double result = str.toDouble();
  double x_max = x_max_value.toDouble();
  double x_min = x_min_value.toDouble();
  x_check(&result, &x_max, &x_min);
  if (graph_flag) {
    ui->result_show->setText(str);
    GraphWindow graph_window;
    graph_window.draw_result(result, x_max, x_min, string, x_char);
    graph_window.setModal(true);
    graph_window.exec();
  }
}

void MainWindow::is_empty() {
  if (x_max_value.isEmpty() && x_min_value.isEmpty()) graph_flag = 0;
  if (x_max_value.isEmpty() && !x_min_value.isEmpty()) graph_flag = 0;
  if (!x_max_value.isEmpty() && x_min_value.isEmpty()) graph_flag = 0;
}

void MainWindow::x_check(double *result, double *x_max, double *x_min) {
  if (*result > *x_max) *x_max = *result;
  if (*x_min > *result) *x_min = *result;
  if (*x_min >= *x_max) {
    double tmp = *x_min;
    *x_min = *x_max;
    *x_max = tmp;
  }
  is_empty();
}

void MainWindow::str_check() {
  if (str == "inf" || str == "nan" || str == "Error") {
    str.clear();
  } else {
    open_graph();
  }
}

void MainWindow::x_converter() {
  x_value = ui->x_show->text();
  x_min_value = ui->x_min->text();
  x_max_value = ui->x_max->text();
  if (x_value.isEmpty()) x_value = "0";
}

void MainWindow::str_converter() {
  QByteArray x_byte = x_value.toUtf8();
  QByteArray str_byte = str.toUtf8();
  strlcpy(string, str_byte, str.size() + 1);
  strlcpy(x_char, x_byte, x_value.size() + 1);
  list = s21_smartcalc_manager(string, x_char);
}

void MainWindow::equal_operations() {
  if (list->type == ERROR) {
    str = "Error";
  } else {
    str = QString::number(list->value, 'g', 14);
  }
  ui->result_show->setText(str);
  str_check();
  null_flags();
  result_flag = 1;
  clone = str;
  s21_pop_from(&list);
}

void MainWindow::on_pushButton_equal_sign_clicked() {
  if (operands_flag == 0 && str != clone) {
    x_converter();
    str_converter();
    equal_operations();
  } else if (operands_flag && counter == 256) {
    on_pushButton_clear_clicked();
  }
}

void MainWindow::on_pushButton_credit_clicked() {
  CreditWindow credit_window;
  credit_window.setModal(true);
  credit_window.exec();
}

void MainWindow::on_pushButton_deposit_clicked() {
  depositwindow deposit_window;
  deposit_window.setModal(true);
  deposit_window.exec();
}
