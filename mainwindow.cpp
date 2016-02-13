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
//  QString _formula = "x";
//  _formula.append(0x2081);
//  _formula += " & x";
//  _formula.append(0x2082);
//  _formula += " | x";
//  _formula.append(0x2084);

  QString _formula = QString("%1%4 %2 %7(%1%5 %3 %7%1%6)").arg("x").arg("&").
      arg("|").arg((QChar)0x2081).arg((QChar)0x2082).arg((QChar)0x2083).
      arg((QChar)0x00AC);
  function->setFormula(_formula);

  //DEBUG
  showMessage("Function: ", true);
  showMessage(function->getFormula(), false);

  return function;
}
