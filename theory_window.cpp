#include "theory_window.h"
#include "ui_theory_window.h"

Theory_window::Theory_window(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Theory_window)
{
    ui->setupUi(this);
}

Theory_window::~Theory_window()
{
    delete ui;
}
