#ifndef ELEMENT_H
#define ELEMENT_H

#include <QTableWidget>
#include <QComboBox>
#include <QDebug>

class Element : public QTableWidget
{
    Q_OBJECT

public:
    Element();

    int getNumber() const;
    void setNumber(int value);
    int getResultSum();

private:
    int number;

    void makeCap();
    void makeRows();

private slots:
    void slotUpdateComposition(int x, int y);
};

#endif // ELEMENT_H
