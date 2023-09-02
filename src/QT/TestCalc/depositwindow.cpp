#include "depositwindow.h"

depositwindow::depositwindow(QWidget* parent)
    : QDialog(parent), ui(new Ui::depositwindow) {
  ui->setupUi(this);
  setFixedSize(483, 390);
  edit_date();
  set_validators();
  start_numbers();
}

depositwindow::~depositwindow() { delete ui; }

void depositwindow::edit_date() {
  ui->input_date->setDisplayFormat("dd/MM/yyyy");
  current = QDate::currentDate();
  ui->input_date->setDate(current);
}

void depositwindow::start_numbers() {
  ui->sum_input->setText("120000");
  ui->period_input->setText("12");
  ui->interest_rate_input->setText("12.5");
  ui->tax_rate_input->setText("35");
}

void depositwindow::set_validators() {
  ui->sum_input->setValidator(new QDoubleValidator(1, 1.7E-308, 7, this));
  ui->period_input->setValidator(new QIntValidator(1, 600, this));
  ui->interest_rate_input->setValidator(new QDoubleValidator(1, 999, 7, this));
  ui->tax_rate_input->setValidator(new QIntValidator(1, 35, this));
}

int depositwindow::input_check() {
  return null_check(ui->sum_input->text()) ||
         null_check(ui->period_input->text()) ||
         null_check(ui->interest_rate_input->text()) ||
         null_check(ui->tax_rate_input->text());
}

int depositwindow::null_check(QString str) {
  return str == '0' || str == "00" || str.isEmpty();
}

void depositwindow::output_null() {
  ui->tax_show->setText("0");
  ui->income_show->setText("0");
  ui->total_deposit->setText("0");
}

void depositwindow::double_return(s21_term* info) {
  info->start_sum = ui->sum_input->text().toDouble();
  info->months = ui->period_input->text().toDouble();
  info->interest = ui->interest_rate_input->text().toDouble() / 100;
  info->tax = ui->tax_rate_input->text().toDouble() / 100;
}

void depositwindow::frequency_return(s21_term* info) {
  if (ui->caps_button->isChecked()) {
    if (ui->freq_of_pay->currentText() == "daily")
      info->frequency = DAILY;
    else if (ui->freq_of_pay->currentText() == "monthly")
      info->frequency = MONTHLY;
    else if (ui->freq_of_pay->currentText() == "quarterly")
      info->frequency = QUARTERLY;
    else if (ui->freq_of_pay->currentText() == "every six months")
      info->frequency = HALF_YEAR;
    else if (ui->freq_of_pay->currentText() == "yearly")
      info->frequency = YEARLY;
    else
      info->frequency = END;
  } else {
    info->frequency = END;
  }
}

void depositwindow::days_return(s21_term* info) {
  QDate futureDate = current.addMonths(info->months);
  info->days = current.daysTo(futureDate);
}

s21_term depositwindow::data_return() {
  s21_term info;
  double_return(&info);
  frequency_return(&info);
  days_return(&info);
  return info;
}

void depositwindow::data_show(s21_result* res) {
  income = QString::number(res->income, 'g', 14);
  tax = QString::number(res->tax, 'g', 14);
  total_sum = QString::number(res->end_sum, 'g', 14);
  if (clone_total_sum != total_sum) {
    clone_total_sum = total_sum;
    ui->income_show->setText(income);
    ui->tax_show->setText(tax);
    ui->total_deposit->setText(total_sum);
  }
}

void depositwindow::str_clear() {
  income.clear();
  tax.clear();
  total_sum.clear();
}

void depositwindow::on_pushButton_calculate_clicked() {
  if (!input_check()) {
    s21_term info = data_return();
    s21_result* res = s21_deposit_manager(&info);
    data_show(res);
    if (res) free(res);
  } else {
    output_null();
  }
  str_clear();
}
