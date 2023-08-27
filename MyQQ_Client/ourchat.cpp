#include "ourchat.h"
#include "ui_ourchat.h"

ourchat::ourchat(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ourchat)
{
    ui->setupUi(this);
}

ourchat::~ourchat()
{
    delete ui;
}
