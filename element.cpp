#include "element.h"

Element::Element() : QTableWidget()
{
    number = 0;
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
            if (j != 0) {
                QTableWidgetItem *item = new QTableWidgetItem();
                item->setText("0");
                this->setItem(i,j,item);
            }
            else {
                QComboBox *item = new QComboBox();
                item->addItem("контроллер");
                item->addItem("конденсатор");
                item->addItem("резистор");
                this->setCellWidget(i,j,item);
            }
        }
    }
    connect(this, SIGNAL(cellChanged(int,int)), this, SLOT(slotUpdateComposition(int, int)));
}

int Element::getResultSum()
{
    int answer = 0;
    for (int i = 0; i < this->rowCount(); i++) {
        answer+= this->item(i,3)->text().toInt(NULL,10);
    }
    return answer;
}

void Element::makeCap()
{
    this->setColumnCount(4);
    QStringList LowerTableHeaders;
    LowerTableHeaders << "тип элемента" << "интенсивность" << "количество" << "произведение";
    this->setHorizontalHeaderLabels(LowerTableHeaders);
}

void Element::slotUpdateComposition(int x, int y)
{
    if (y == 3) return;
    QTableWidgetItem *item = new QTableWidgetItem();
    int a = this->item(x,1)->text().toInt(NULL,10)*this->item(x,2)->text().toInt(NULL,10);
    item->setText(QString::number(a));
    this->setItem(x,3,item);
}
