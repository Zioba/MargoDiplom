#ifndef SYSTEMPART_H
#define SYSTEMPART_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
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

private slots:
    void on_pushButton_clicked();
    void slotChangeCurrentClass();

    void on_buttonChanges_clicked();

private:
    Ui::SystemPart *ui;

    QList<Element*> elementList;

    void createElementWidget(int x);
};

#endif // SYSTEMPART_H
