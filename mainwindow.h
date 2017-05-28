#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <systempart.h>
#include <reportframe.h>
#include <QTextDocumentWriter>
#include <QTextDocument>
#include <QAxObject>

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
    void closeSystemPart();
    void on_excelButton_clicked();

private:
    Ui::MainWindow *ui;
    SystemPart *control;
    SystemPart *gidravl;
    QWidget *factorWidget;
    double cycleTime;
    bool cMark;
    bool gMark;

    void setTableSize(SystemPart *s, int block, int size, int n);
    void fillCell(SystemPart *s, int block, int x, int y, int value, int n);
    int getTableSize(int x);
};

#endif // MAINWINDOW_H
