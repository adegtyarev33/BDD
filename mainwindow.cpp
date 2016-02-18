#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QSplitter"
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  QPalette p = ui->plainTextEdit->palette();
  p.setColor(QPalette::Base, Qt::black);
  p.setColor(QPalette::Text, Qt::green);
  ui->plainTextEdit->setPalette(p);
  showMessage("BDD educational module v0.2", false);
  Function *function = generateFunction(3);
  function->calculateValues();

  //DEBUG
  showMessage("Calculating values...", true);
  showMessage("Number of variables: ", true);
  showMessage(function->getNumberOfVariables(), false);
  showMessage("Vector of values: ", true);
  showMessage(function->getValues(), false);
  Graph *graph = new Graph();
  int _values = function->getValues().toInt();
  int _variables = function->getNumberOfVariables().unicode() - 48;
  graph->buildBdd(_values, _variables, graph->getRoot());
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::showMessage(QString message, bool newLine)
{
  if (newLine)
    ui->plainTextEdit->textCursor().insertBlock();
//  QTextCharFormat format;
//  format.setForeground(Qt::white);
//  ui->plainTextEdit->textCursor().setBlockCharFormat(format);
  ui->plainTextEdit->textCursor().insertText(message);
}


Function* MainWindow::generateFunction(unsigned size)
{
  Function* function = new Function();

  QString x1 = QString("x%1").arg((QChar)0x2081);
  QString x2 = QString("x%1").arg((QChar)0x2082);
  QString x3 = QString("x%1").arg((QChar)0x2083);
  QString s_not = QString("%1").arg((QChar)0x00AC);
  QString _formula = s_not + x1 + "&" + s_not + x2 + "&" + s_not + x3 + "|" + s_not + x1 + "&" +
      s_not + x2 + "&" + x3 + "|" + s_not + x1 + "&" + x2 + "&" + x3;

  function->setFormula(_formula);

  //DEBUG
  showMessage("Function: ", true);
  showMessage(function->getFormula(), false);

  return function;
}
