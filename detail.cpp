#include "detail.h"
#include "ui_detail.h"

detail::detail(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::detail)
{
    ui->setupUi(this);
}

detail::~detail()
{
    delete ui;
}
