#include "element.h"

Element::Element() : QTableWidget()
{
    //this->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
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
            QTableWidgetItem *item = new QTableWidgetItem();
            item->setText("0");
            this->setItem(i,j,item);
        }
    }
    connect(this, SIGNAL(cellChanged(int,int)), this, SLOT(slotUpdateComposition(int, int)));
}

void Element::makeCap()
{
    this->setColumnCount(3);
    QStringList LowerTableHeaders;
    LowerTableHeaders << "интенсивность" << "количество" << "произведение";
    this->setHorizontalHeaderLabels(LowerTableHeaders);
}

void Element::slotUpdateComposition(int x, int y)
{
    QTableWidgetItem *item = new QTableWidgetItem();
    qDebug() << this->item(x,0)->text().toInt(NULL,10);
    qDebug() << this->item(x,1)->text().toInt(NULL,10);
    int a = this->item(x,0)->text().toInt(NULL,10)*this->item(x,1)->text().toInt(NULL,10);
    item->setText(QString::number(a));
    disconnect(this, SIGNAL(cellChanged(int,int)), this, SLOT(slotUpdateComposition(int, int)));
    this->setItem(x,2,item);
    connect(this, SIGNAL(cellChanged(int,int)), this, SLOT(slotUpdateComposition(int, int)));
}
