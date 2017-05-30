#ifndef ELEMENT_H
#define ELEMENT_H

#include <QTableWidget>
#include <QComboBox>
#include <QDebug>

class Element : public QTableWidget
{
    Q_OBJECT

public:
    Element(int type);

    int getNumber() const;
    void setNumber(int value);
    double getResultSum();
    void setElement(int x, int y, double value);

private:
    int number;
    int type;

    void makeCap();
    void makeRows();

private slots:
    void slotUpdateComposition(int x, int y);
};

#endif // ELEMENT_H
