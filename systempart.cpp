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

int SystemPart::getSumIntensity()
{
    int answer = 0;
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

void SystemPart::on_pushButton_clicked()
{
    createElementWidget(ui->toolBox->count());
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
    int x = ui->toolBox->currentIndex();
    int p = ui->lineChanges->text().toInt(NULL,10);
    elementList.at(x)->setNumber(p);
}

void SystemPart::on_buttonChanges_2_clicked()
{
    int x = ui->toolBox->currentIndex();
    int p = ui->lineChanges_2->text().toInt(NULL,10);
    resistorList.at(x)->setNumber(p);
}

void SystemPart::on_buttonChanges_3_clicked()
{
    int x = ui->toolBox->currentIndex();
    int p = ui->lineChanges_3->text().toInt(NULL,10);
    condensatorList.at(x)->setNumber(p);
}

void SystemPart::on_buttonChanges_4_clicked()
{
    int x = ui->toolBox->currentIndex();
    int p = ui->lineChanges_4->text().toInt(NULL,10);
    microList.at(x)->setNumber(p);
}

void SystemPart::on_buttonChanges_5_clicked()
{
    int x = ui->toolBox->currentIndex();
    int p = ui->lineChanges_5->text().toInt(NULL,10);
    connectorList.at(x)->setNumber(p);
}

void SystemPart::on_buttonChanges_6_clicked()
{
    int x = ui->toolBox->currentIndex();
    int p = ui->lineChanges_6->text().toInt(NULL,10);
    polupList.at(x)->setNumber(p);
}
