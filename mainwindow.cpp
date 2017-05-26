#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    cMark = false;
    gMark = false;
    this->cycleTime = 0;
    ui->lineEdit->setText("0");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_controlButUpdate_clicked()
{
    ui->intensityLineC->setText(QString::number(control->getSumIntensity()));
    if (control->getSumIntensity()!=0) {
        ui->middleLineC->setText(QString::number((double)1/control->getSumIntensity(),'g',6));
        ui->lineEdit_4->setText(QString::number(((double)1/control->getSumIntensity())/cycleTime,'g',6));
    }
}

void MainWindow::on_gidravlButUpdate_clicked()
{
    ui->intensityLineG->setText(QString::number(gidravl->getSumIntensity()));
    if (gidravl->getSumIntensity()!=0) {
        ui->middleLineG->setText(QString::number((double)1/gidravl->getSumIntensity(),'g',6));
        ui->lineEdit_8->setText(QString::number(((double)1/gidravl->getSumIntensity())/cycleTime,'g',6));
    }
}

void MainWindow::on_gidravlButShow_clicked()
{
    if (!gMark) {
        gidravl = new SystemPart(ui->blockNumbLineG->text().toInt(NULL, 10));
        ui->blockNumbLineG->setReadOnly(true);
        ui->gidravlButUpdate->setEnabled(true);
        gMark = true;
    }
    factorWidget = new QWidget();
    QGridLayout *layout = new QGridLayout();
    layout->addWidget(gidravl);
    factorWidget->setLayout(layout);
    factorWidget->setFixedSize(1000, 600);
    factorWidget->setWindowTitle("гидравлическая система");
    factorWidget->show();
}

void MainWindow::on_controlButShow_clicked()
{
    if (!cMark) {
        control = new SystemPart(ui->blockNumbLineC->text().toInt(NULL, 10));
        ui->blockNumbLineC->setReadOnly(true);
        ui->controlButUpdate->setEnabled(true);
        cMark = true;
    }
    factorWidget = new QWidget();
    QGridLayout *layout = new QGridLayout();
    layout->addWidget(control);
    factorWidget->setLayout(layout);
    factorWidget->setFixedSize(1000, 600);
    factorWidget->setWindowTitle("система управления");
    factorWidget->show();
}

void MainWindow::on_pushButton_3_clicked()
{
    this->cycleTime = ui->lineEdit->text().toDouble(NULL);
}

void MainWindow::on_pushButton_4_clicked()
{
    QString s = "<HTML>";
    s=s+"<HEAD>"+
                    "<TITLE>Управление разрывом строк </Title>"+
            "</HEAD>"+
            "<BODY>"+
            "<H1 align=center>Отчет о надежности</H1>"+
            "<H2 align=left><FONT SIZE=7>Система управления</H2>"+
              "<FONT SIZE=4>"+
                "<B>Количество блоков: </B>"+ui->blockNumbLineC->text()+"<br>"+
                "<B>Интенсивность отказов: </B>"+ui->intensityLineC->text()+"<br>"+
                "<B>Средняя наработка на отказ: </B>"+ui->middleLineC->text()+"<br>"+
                "<B>Количество полных циклов работы по рассчитанным показателям надежности: </B>"+ui->lineEdit_4->text()+"<br>"+
            "<H3 align=left> <FONT SIZE=10>Гидравлическая система</H3>"+
              "<FONT SIZE=4>"+
                "<B>Количество блоков: </B>"+ui->blockNumbLineG->text()+"<br>"+
                "<B>Интенсивность отказов: </B>"+ui->intensityLineG->text()+"<br>"+
                "<B>Средняя наработка на отказ: </B>"+ui->middleLineG->text()+"<br>"+
                "<B>Количество полных циклов работы по рассчитанным показателям надежности: </B>"+ui->lineEdit_8->text()+"<br>"+
            "</BODY>"+
            "</HTML>";
    ReportFrame *frame = new ReportFrame(s);
    frame->show();
    QTextDocumentWriter writer("report.html", "plaintext");
    QTextDocument *doc = new QTextDocument(s);
    writer.write(doc);
}
