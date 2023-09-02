#include "creditwindow.h"

CreditWindow::CreditWindow(QWidget* parent)
    : QDialog(parent), ui(new Ui::CreditWindow) {
  ui->setupUi(this);
  setFixedSize(515, 350);
  set_validators();
}

CreditWindow::~CreditWindow() { delete ui; }

void CreditWindow::set_validators() {
  ui->credit_show->setValidator(new QDoubleValidator(1, 1.7E-308, 7, this));
  ui->term_show->setValidator(new QIntValidator(1, 50, this));
  ui->interest_show->setValidator(new QDoubleValidator(1, 999, 7, this));
}

int CreditWindow::input_check() {
  return null_check(ui->credit_show->text()) ||
         null_check(ui->term_show->text()) ||
         null_check(ui->interest_show->text());
}

int CreditWindow::null_check(QString str) {
  return str == '0' || str == "00" || str.isEmpty();
}

s21_info CreditWindow::double_assignment() {
  s21_info info;
  info.sum = ui->credit_show->text().toDouble();
  info.months = ui->term_show->text().toDouble();
  info.interest = ui->interest_show->text().toDouble();
  return info;
}

void CreditWindow::round_function(double* number) {
  *number = round(*number * 100) / 100;
}

char* CreditWindow::q_converter(QString q_str) {
  char* str = new char(q_str.size());
  ;
  QByteArray str_byte = q_str.toUtf8();
  strlcpy(str, str_byte, q_str.size() + 1);
  return str;
}

void CreditWindow::min_pay_check(s21_res* res) {
  if (res->min_pay != 0) {
    q_pay.append(" ... ");
    round_function(&res->min_pay);
    QString q_min_pay = QString::number(res->min_pay, 'g', 14);
    q_pay.append(q_min_pay);
  }
}

void CreditWindow::result_show() {
  if (q_pay_clone != q_pay) {
    q_pay_clone = q_pay;
    ui->payment_show->setText(q_pay);
    ui->clean_int_show->setText(q_overpay);
    ui->debt_plus_int_show->setText(q_sum);
  }
}

void CreditWindow::str_clear() {
  q_pay.clear();
  q_overpay.clear();
  q_sum.clear();
}

void CreditWindow::output_null() {
  ui->payment_show->setText("0");
  ui->clean_int_show->setText("0");
  ui->debt_plus_int_show->setText("0");
}

void CreditWindow::on_pushButton_calculate_clicked() {
  if (!input_check()) {
    s21_info info = double_assignment();
    QString q_period = ui->period_term->currentText();
    char* period = q_converter(q_period);
    QString q_payment = ui->type_show->currentText();
    char* payment = q_converter(q_payment);
    s21_res* res = s21_credit_manager(&info, period, payment);
    q_overpay = QString::number(res->overpay, 'g', 14);
    q_sum = QString::number(res->sum_total, 'g', 14);
    round_function(&res->max_pay);
    q_pay = QString::number(res->max_pay, 'g', 14);
    min_pay_check(res);
    result_show();
    str_clear();
    delete period;
    delete payment;
    if (res) free(res);
  } else {
    output_null();
    str_clear();
  }
}
