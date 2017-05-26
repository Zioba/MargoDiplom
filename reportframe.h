#ifndef REPORTFRAME_H
#define REPORTFRAME_H

#include <QWidget>

namespace Ui {
class ReportFrame;
}

class ReportFrame : public QWidget
{
    Q_OBJECT

public:
    explicit ReportFrame(QString s, QWidget *parent = 0);
    ~ReportFrame();

private:
    Ui::ReportFrame *ui;
};

#endif // REPORTFRAME_H
