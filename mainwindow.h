#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <systempart.h>

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
    void on_controlBut_clicked();

    void on_gidravlBut_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
