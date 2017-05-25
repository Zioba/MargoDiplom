#include "element.h"

Element::Element(int type) : QTableWidget()
{
    number = 0;
    this->type = type;
    makeCap();
}

int Element::getNumber() const
{
    return number;
}

void Element::setNumber(int value)
{
    disconnect(this, SIGNAL(cellChanged(int,int)), this, SLOT(slotUpdateComposition(int, int)));
    number = value;
    this->clear();
    makeCap();
    this->setRowCount(number);
    for (int i=0; i<this->rowCount(); i++) {
        for (int j=0; j<this->columnCount(); j++) {
            QTableWidgetItem *item = new QTableWidgetItem();
            item->setText("0");
            this->setItem(i,j,item);
        }
    }
    connect(this, SIGNAL(cellChanged(int,int)), this, SLOT(slotUpdateComposition(int, int)));
}

int Element::getResultSum()
{
    int answer = 0;
    int x = this->columnCount()-1;
    for (int i = 0; i < this->rowCount(); i++) {
        answer+= this->item(i,x)->text().toInt(NULL,10);
    }
    return answer;
}

void Element::makeCap()
{
    QStringList LowerTableHeaders;
    switch (this->type) {
    case 0:
        this->setColumnCount(3);
        LowerTableHeaders << "интенсивность" << "количество" << "произведение";
        this->setHorizontalHeaderLabels(LowerTableHeaders);
        break;
    case 1:
        this->setColumnCount(6);
        LowerTableHeaders << "интенсивность" << "Кр" << "Кэ" << "Км" << "количество" << "произведение";
        this->setHorizontalHeaderLabels(LowerTableHeaders);
        break;
    case 2:
        this->setColumnCount(6);
        LowerTableHeaders << "интенсивность" << "Кс" << "Кр" << "Кэ" << "количество" << "произведение";
        this->setHorizontalHeaderLabels(LowerTableHeaders);
        break;
    case 3:
        this->setColumnCount(5);
        LowerTableHeaders << "интенсивность" << "К(с.т)" << "Кэ" << "количество" << "произведение";
        this->setHorizontalHeaderLabels(LowerTableHeaders);
        break;
    case 4:
        this->setColumnCount(6);
        LowerTableHeaders << "интенсивность" << "Кc" << "Кk" << "Кэ" << "количество" << "произведение";
        this->setHorizontalHeaderLabels(LowerTableHeaders);
        break;
    default:
        this->setColumnCount(4);
        LowerTableHeaders << "интенсивность" << "Коб" << "количество" << "произведение";
        this->setHorizontalHeaderLabels(LowerTableHeaders);
        break;
    }
}

void Element::slotUpdateComposition(int x, int y)
{
    if (y == this->columnCount()-1) return;
    QTableWidgetItem *item = new QTableWidgetItem();
    int a = this->item(x,0)->text().toInt(NULL,10);
    for (int i = 1; i < this->columnCount()-1; i++) {
        a*= this->item(x,i)->text().toInt(NULL,10);
    }
    item->setText(QString::number(a));
    this->setItem(x, this->columnCount()-1, item);
}
