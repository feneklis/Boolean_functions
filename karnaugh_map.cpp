#include "karnaugh_map.h"
#include "ui_karnaugh_map.h"

Karnaugh_map::Karnaugh_map(QWidget *parent, QString str, int count) :
    QDialog(parent),
    ui(new Ui::Karnaugh_map)
{
    ui->setupUi(this);//установка того что мы наделали вдизайнерее
    if (count > 0) {
        int left = count / 2;//кол-во аргументов идущие влево и вправо
        int up = count - left;
        this->resize(((1 << up) + left + 1) * 24 + 46, ((1 << left) + up + 1) * 24 + 46);//задание окна чтоб без ползунков
    }
    ui->webView->setHtml(str);
    ui->webView->page()->setBackgroundColor(QColor(206, 210,255));
    ui->webView->page()->triggerAction(QWebEnginePage::AlignCenter, true);
}

Karnaugh_map::~Karnaugh_map()
{
    delete ui;
}
