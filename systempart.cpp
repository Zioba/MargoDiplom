#include "systempart.h"
#include "ui_systempart.h"

SystemPart::SystemPart(int blockNumb, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SystemPart)
{
    ui->setupUi(this);

    ui->toolBox->removeItem(0);
    for (int i=0; i<blockNumb; i++) {
        createElementWidget(i);
    }
    connect(ui->toolBox, SIGNAL(currentChanged(int)), this, SLOT(slotChangeCurrentClass()));
}

SystemPart::~SystemPart()
{
    delete ui;
}

double SystemPart::getSumIntensity()
{
    double answer = 0;
    for (int i = 0; i < elementList.size(); i++) {
        answer+= elementList.at(i)->getResultSum();
        answer+= resistorList.at(i)->getResultSum();
        answer+= condensatorList.at(i)->getResultSum();
        answer+= microList.at(i)->getResultSum();
        answer+= connectorList.at(i)->getResultSum();
        answer+= polupList.at(i)->getResultSum();
    }
    return answer;
}

void SystemPart::setExcel1(int block, int x)
{
    elementList.at(block)->setNumber(x);
}

void SystemPart::setExcel2(int block, int x)
{
    resistorList.at(block)->setNumber(x);
}

void SystemPart::setExcel3(int block, int x)
{
    condensatorList.at(block)->setNumber(x);
}

void SystemPart::setExcel4(int block, int x)
{
    microList.at(block)->setNumber(x);
}

void SystemPart::setExcel5(int block, int x)
{
    connectorList.at(block)->setNumber(x);
}

void SystemPart::setExcel6(int block, int x)
{
    polupList.at(block)->setNumber(x);
}

void SystemPart::setCell1(int block, int x, int y, double value)
{
    elementList.at(block)->setElement(x,y,value);
}

void SystemPart::setCell2(int block, int x, int y, double value)
{
    resistorList.at(block)->setElement(x,y,value);
}

void SystemPart::setCell3(int block, int x, int y, double value)
{
    condensatorList.at(block)->setElement(x,y,value);
}

void SystemPart::setCell4(int block, int x, int y, double value)
{
    microList.at(block)->setElement(x,y,value);
}

void SystemPart::setCell5(int block, int x, int y, double value)
{
    connectorList.at(block)->setElement(x,y,value);
}

void SystemPart::setCell6(int block, int x, int y, double value)
{
    polupList.at(block)->setElement(x,y,value);
}

void SystemPart::on_pushButton_clicked()
{
    emit closeWindowSignal();
}

void SystemPart::createElementWidget(int x)
{
    QWidget *widget = new QWidget();
    QVBoxLayout *vBoxLayoutMain = new QVBoxLayout();
    //1
    QLabel *label = new QLabel();
    label->setText("Обычные элементы");
    vBoxLayoutMain->addWidget(label);
    Element *element = new Element(0);
    elementList << element;
    vBoxLayoutMain->addWidget(element);
    //2
    label = new QLabel();
    label->setText("Резисторы");
    vBoxLayoutMain->addWidget(label);
    element = new Element(1);
    resistorList << element;
    vBoxLayoutMain->addWidget(element);
    //3
    label = new QLabel();
    label->setText("конденсаторы");
    vBoxLayoutMain->addWidget(label);
    element = new Element(2);
    condensatorList << element;
    vBoxLayoutMain->addWidget(element);
    //4
    label = new QLabel();
    label->setText("Микросхемы");
    vBoxLayoutMain->addWidget(label);
    element = new Element(3);
    microList << element;
    vBoxLayoutMain->addWidget(element);
    //5
    label = new QLabel();
    label->setText("Соеденители");
    vBoxLayoutMain->addWidget(label);
    element = new Element(4);
    connectorList << element;
    vBoxLayoutMain->addWidget(element);
    //6
    label = new QLabel();
    label->setText("Полупроводниковые элементы");
    vBoxLayoutMain->addWidget(label);
    element = new Element(5);
    polupList << element;
    vBoxLayoutMain->addWidget(element);
    widget->setLayout(vBoxLayoutMain);
    ui->toolBox->addItem(widget, "блок" + QString::number(x+1));
}

void SystemPart::slotChangeCurrentClass()
{
    int x = ui->toolBox->currentIndex();
    int p = elementList.at(x)->getNumber();
    ui->lineChanges->setText(QString::number(p));
}

void SystemPart::on_buttonChanges_clicked()
{
    setExcel1(ui->toolBox->currentIndex(), ui->lineChanges->text().toInt(NULL,10));
}

void SystemPart::on_buttonChanges_2_clicked()
{
    setExcel2(ui->toolBox->currentIndex(), ui->lineChanges_2->text().toInt(NULL,10));
}

void SystemPart::on_buttonChanges_3_clicked()
{
    setExcel3(ui->toolBox->currentIndex(), ui->lineChanges_3->text().toInt(NULL,10));
}

void SystemPart::on_buttonChanges_4_clicked()
{
    setExcel4(ui->toolBox->currentIndex(), ui->lineChanges_4->text().toInt(NULL,10));
}

void SystemPart::on_buttonChanges_5_clicked()
{
    setExcel5(ui->toolBox->currentIndex(), ui->lineChanges_5->text().toInt(NULL,10));
}

void SystemPart::on_buttonChanges_6_clicked()
{
    setExcel6(ui->toolBox->currentIndex(), ui->lineChanges_6->text().toInt(NULL,10));
}
