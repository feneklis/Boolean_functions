#ifndef PLUS_MINUS_H
#define PLUS_MINUS_H

#include <QWidget>

namespace Ui {
class Plus_minus_window;
}

class Plus_minus_window : public QWidget
{
    Q_OBJECT

public:
    explicit Plus_minus_window(QWidget *parent = nullptr);
    ~Plus_minus_window();
    void Chang_Text(int);

private:
    Ui::Plus_minus_window *ui;
};

#endif // PLUS_MINUS_H
