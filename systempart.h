#ifndef SYSTEMPART_H
#define SYSTEMPART_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <element.h>

namespace Ui {
class SystemPart;
}

class SystemPart : public QWidget
{
    Q_OBJECT

public:
    explicit SystemPart(int blockNumb, QWidget *parent = 0);
    ~SystemPart();
    int getSumIntensity();
    void setExcel1(int block, int x);
    void setExcel2(int block, int x);
    void setExcel3(int block, int x);
    void setExcel4(int block, int x);
    void setExcel5(int block, int x);
    void setExcel6(int block, int x);

    void setCell1(int block, int x, int y, int value);
    void setCell2(int block, int x, int y, int value);
    void setCell3(int block, int x, int y, int value);
    void setCell4(int block, int x, int y, int value);
    void setCell5(int block, int x, int y, int value);
    void setCell6(int block, int x, int y, int value);

signals:
    void helloBitch();

private slots:
    void on_pushButton_clicked();
    void slotChangeCurrentClass();
    void on_buttonChanges_clicked();
    void on_buttonChanges_2_clicked();
    void on_buttonChanges_3_clicked();
    void on_buttonChanges_4_clicked();
    void on_buttonChanges_5_clicked();
    void on_buttonChanges_6_clicked();

private:
    Ui::SystemPart *ui;

    QList<Element*> elementList;
    QList<Element*> resistorList;
    QList<Element*> condensatorList;
    QList<Element*> microList;
    QList<Element*> connectorList;
    QList<Element*> polupList;

    void createElementWidget(int x);
};

#endif // SYSTEMPART_H
