#include "reportframe.h"
#include "ui_reportframe.h"

ReportFrame::ReportFrame(QString s, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ReportFrame)
{
    ui->setupUi(this);
    ui->label->setText(s);
}

ReportFrame::~ReportFrame()
{
    delete ui;
}
