#include "file_saved.h"
#include "ui_file_saved.h"

File_Saved::File_Saved(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::File_Saved)
{
    ui->setupUi(this);
}

File_Saved::~File_Saved()
{
    delete ui;
}
