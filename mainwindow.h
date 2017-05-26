#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <systempart.h>
#include <reportframe.h>
#include <QTextDocumentWriter>
#include <QTextDocument>

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
    void on_controlButUpdate_clicked();
    void on_gidravlButUpdate_clicked();
    void on_gidravlButShow_clicked();
    void on_controlButShow_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();

private:
    Ui::MainWindow *ui;
    SystemPart *control;
    SystemPart *gidravl;
    QWidget *factorWidget;
    double cycleTime;
    bool cMark;
    bool gMark;
};

#endif // MAINWINDOW_H
