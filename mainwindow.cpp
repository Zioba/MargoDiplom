#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_controlBut_clicked()
{
    SystemPart *w = new SystemPart(ui->blockNumbLine1->text().toInt(NULL, 10));
    w->show();
}

void MainWindow::on_gidravlBut_clicked()
{
    SystemPart *w = new SystemPart(ui->blockNumbLine2->text().toInt(NULL, 10));
    w->show();
}
