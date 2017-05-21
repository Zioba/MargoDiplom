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
    Element *element = new Element();
    elementList << element;
    QVBoxLayout *vBoxLayoutMain = new QVBoxLayout();
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
