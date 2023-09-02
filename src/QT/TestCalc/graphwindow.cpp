#include "graphwindow.h"

GraphWindow::GraphWindow(QWidget* parent)
    : QDialog(parent), ui(new Ui::GraphWindow) {
  ui->setupUi(this);
  setFixedSize(549, 366);
}

GraphWindow::~GraphWindow() { delete ui; }

void GraphWindow::y_calculate(char* str_clone, char* x_clone, double* result) {
  list = s21_smartcalc_manager(str_clone, x_clone);
  Y = atof(x_clone);
  Y += step;
  sprintf(x_clone, "%lf", Y);
  *result = list->value;
  if (list) s21_pop_from(&list);
}

void GraphWindow::widget_edit() {
  ui->widget->addGraph();
  ui->widget->graph(0)->addData(x, y);
  ui->widget->replot();
  ui->widget->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
  x.clear();
  y.clear();
}

void GraphWindow::draw_result(double result, double x_max, double x_min,
                              const char* str, const char* x_char) {
  ui->widget->clearGraphs();

  char str_clone[260] = {'0'};
  strncpy(str_clone, str, strlen(str));
  char x_clone[60] = {'0'};
  strncpy(x_clone, x_char, strlen(x_char));
  xBegin = x_min;
  xEnd = x_max;
  y_min = x_min;
  y_max = -x_max;
  step = (abs(x_min) + abs(x_max)) / (2 * 100000);

  ui->widget->xAxis->setRange(x_min - step, x_max + step);
  ui->widget->yAxis->setRange(x_min - step, x_max + step);

  for (X = xBegin; X <= xEnd; X += step) {
    x.push_back(X);
    y.push_back(result);
    y_calculate(str_clone, x_clone, &result);
  }

  widget_edit();
  if (list) free(list);
}
