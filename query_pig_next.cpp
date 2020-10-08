#include "query_pig_next.h"
#include "ui_query_pig_next.h"

query_pig_next::query_pig_next(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::query_pig_next)
{
    ui->setupUi(this);
}

query_pig_next::~query_pig_next()
{
    delete ui;
}
