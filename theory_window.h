#ifndef THEORY_WINDOW_H
#define THEORY_WINDOW_H

#include <QWidget>

namespace Ui {
class Theory_window;
}

class Theory_window : public QWidget
{
    Q_OBJECT

public:
    explicit Theory_window(QWidget *parent = nullptr);
    ~Theory_window();

private:
    Ui::Theory_window *ui;
};

#endif // THEORY_WINDOW_H
