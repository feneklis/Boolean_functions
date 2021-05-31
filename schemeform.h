#ifndef SCHEMEFORM_H
#define SCHEMEFORM_H

#include <QWidget>

namespace Ui {
class SchemeForm;
}

class SchemeForm : public QWidget
{
    Q_OBJECT

public:
    explicit SchemeForm(QWidget *parent, std::vector<char*> table, const char* arguments, int count, int type_input=0);
    ~SchemeForm();

private:
    Ui::SchemeForm *ui;
};

#endif // SCHEMEFORM_H
