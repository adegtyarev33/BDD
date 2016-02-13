#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "function.h"
#include "graph.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

private:
    Ui::MainWindow *ui;

    void showMessage(QString message, bool newLine);
    Function* generateFunction(unsigned size);
};

#endif // MAINWINDOW_H
