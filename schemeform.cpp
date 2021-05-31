#include "schemeform.h"
#include "ui_schemeform.h"

SchemeForm::SchemeForm(QWidget *parent, std::vector<char*> table, const char* arguments, int count, int type_input) :
    QWidget(parent),
    ui(new Ui::SchemeForm)
{
    ui->setupUi(this);
    ui->scrollAreaWidgetContents->set_table_truth(table);
}

SchemeForm::~SchemeForm()
{
    delete ui;
}
