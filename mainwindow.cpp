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
        ui->excelButton->setEnabled(false);
        connect(gidravl, SIGNAL(helloBitch()), this, SLOT(closeSystemPart()));
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
        ui->excelButton->setEnabled(false);
        connect(control, SIGNAL(helloBitch()), this, SLOT(closeSystemPart()));
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
    QString s = "<!DOCTYPE html>";
    int x1 = control->getSumIntensity();
    int x2 = gidravl->getSumIntensity();
    s = s + "<html>"+
      "<head>"+
        "<meta charset=\"UTF-8\">"+
        "<meta name=\"description\" content=\"Free Web content\">"+
        "<meta name=\"keywords\" content=\"HTML,CSS,XML,JavaScript\">"+
        "<meta name=\"author\" content=\"Yurkov Aleksandr\">"+
        "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">"+
      "</head>"+
      "<body>"+
        "<title>Отчет о надежности </title>"+
        "<h1 align=center>Отчет о надежности</h1>"+
        "<h2 align=left><FONT size=7>Система управления </FONT></h2>"+
          "<FONT size=4>"+
            "<b>Количество блоков: </b>"+ui->blockNumbLineC->text()+"<br>"+
            "<b>Интенсивность отказов: </b>"+ui->intensityLineC->text()+"<br>"+
            "<b>Средняя наработка на отказ: </b>"+ui->middleLineC->text()+"<br>"+
            "<b>Количество полных циклов работы по рассчитанным показателям надежности: </b>"+ui->lineEdit_4->text()+"<br>"+
          "</FONT>"+
        "<h3 align=left> <FONT size=10>Гидравлическая система</FONT><h3>"+
          "<FONT size=4>"+
            "<b>Количество блоков: </b>"+ui->blockNumbLineG->text()+"<br>"+
            "<b>Интенсивность отказов: </b>"+ui->intensityLineG->text()+"<br>"+
            "<b>Средняя наработка на отказ: </b>"+ui->middleLineC->text()+"<br>"+
            "<b>Количество полных циклов работы по рассчитанным показателям надежности: </b>"+ui->lineEdit_4->text()+"<br>"+
          "</FONT>"+
        "<h4 align=left> <FONT size=10>Общие параметры системы</FONT><h4>"+
          "<FONT size=4>"+
            "<b>Интенсивность отказов: </b>"+QString::number((x1+x2)*1.5)+"<br>"+
            "<b>Средняя наработка на отказ: </b>"+QString::number(((double)1/((x1+x2)*1.5)),'g',6)+"<br>"+
            "<b>Количество полных циклов работы: </b>"+QString::number(((double)1/((x1+x2)*1.5))/cycleTime,'g',6)+"<br>"+
          "</FONT>"+
      "</body>"+
    "</html>";
    ReportFrame *frame = new ReportFrame(s);
    frame->show();
    QTextDocumentWriter writer("report.html", "plaintext");
    QTextDocument *doc = new QTextDocument(s);
    writer.write(doc);
}

void MainWindow::closeSystemPart()
{
    factorWidget->hide();
}

void MainWindow::on_excelButton_clicked()
{
    QAxObject* excel = new QAxObject("Excel.Application", 0);
    QAxObject* workbooks = excel->querySubObject("Workbooks");
    QAxObject* workbook = workbooks->querySubObject("Open(const QString&)", "D:\\margo.xlsx");
    QAxObject* sheets = workbook->querySubObject("Worksheets");
    QAxObject* sheet = sheets->querySubObject("Item(int)", 1);
    QAxObject* cell = sheet->querySubObject("Cells(int,int)", 2, 2);
    QVariant value = cell->property("Value");
    int blockN = value.toInt();
//создаем систему управления
    control = new SystemPart(blockN);
    ui->blockNumbLineC->setText(QString::number(blockN));
    ui->blockNumbLineC->setReadOnly(true);
    ui->controlButUpdate->setEnabled(true);
    cMark = true;
    connect(control, SIGNAL(helloBitch()), this, SLOT(closeSystemPart()));
//===
    int i = 3;
    for (int blockI = 0; blockI < blockN; blockI++) {
        for (int j = 0; j < 6; j++) {
            cell = sheet->querySubObject("Cells(int,int)", i, 2);
            value = cell->property("Value");
            int tableN = value.toInt();
            setTableSize(control,blockI,tableN,j);
            i++;
            i++;
            for (int tableI = 0; tableI < tableN; tableI++) {
                for (int q = 0; q < getTableSize(j); q++) {
                    cell = sheet->querySubObject("Cells(int,int)", i, q+2);
                    value = cell->property("Value");
                    double r = value.toDouble();
                    qDebug() << r;
                    fillCell(control, blockI, tableI, q, value.toDouble(), j);
                }
                i++;
            }
        }
    }
    i++;
    cell = sheet->querySubObject("Cells(int,int)", i, 2);
    value = cell->property("Value");
    blockN = value.toInt();
//создаем гидравлическую систему
    gidravl = new SystemPart(blockN);
    ui->blockNumbLineG->setText(QString::number(blockN));
    ui->blockNumbLineG->setReadOnly(true);
    ui->gidravlButUpdate->setEnabled(true);
    gMark = true;
    ui->excelButton->setEnabled(false);
    connect(gidravl, SIGNAL(helloBitch()), this, SLOT(closeSystemPart()));
//===
    i++;
    for (int blockI = 0; blockI < blockN; blockI++) {
        for (int j = 0; j < 6; j++) {
            cell = sheet->querySubObject("Cells(int,int)", i, 2);
            value = cell->property("Value");
            int tableN = value.toInt();
            setTableSize(gidravl,blockI,tableN,j);
            i++;
            i++;
            for (int tableI = 0; tableI < tableN; tableI++) {
                for (int q = 0; q < getTableSize(j); q++) {
                    cell = sheet->querySubObject("Cells(int,int)", i, q+2);
                    value = cell->property("Value");
                    fillCell(gidravl, blockI, tableI, q, value.toDouble(), j);
                }
                i++;
            }
        }
    }
    workbook->dynamicCall("Close()");
    excel->dynamicCall("Quit()");
}

void MainWindow::setTableSize(SystemPart *s, int block, int size, int n)
{
    switch (n) {
    case 0:
        s->setExcel1(block, size);
        break;
    case 1:
        s->setExcel2(block, size);
        break;
    case 2:
        s->setExcel3(block, size);
        break;
    case 3:
        s->setExcel4(block, size);
        break;
    case 4:
        s->setExcel5(block, size);
        break;
    default:
        s->setExcel6(block, size);
        break;
    }
}

void MainWindow::fillCell(SystemPart *s, int block, int x, int y, double value, int n)
{
    switch (n) {
    case 0:
        s->setCell1(block, x, y, value);
        break;
    case 1:
        s->setCell2(block, x, y, value);
        break;
    case 2:
        s->setCell3(block, x, y, value);
        break;
    case 3:
        s->setCell4(block, x, y, value);
        break;
    case 4:
        s->setCell5(block, x, y, value);
        break;
    default:
        s->setCell6(block, x, y, value);
        break;
    }
}

int MainWindow::getTableSize(int x)
{
    switch (x) {
    case 0:
        return 2;
    case 1:
        return 5;
    case 2:
        return 5;
    case 3:
        return 4;
    case 4:
        return 5;
    default:
        return 3;
    }
}
