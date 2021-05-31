#ifndef KARNAUGH_MAP_H
#define KARNAUGH_MAP_H

#include <QDialog>

namespace Ui {
class Karnaugh_map;
}

class Karnaugh_map : public QDialog
{
    Q_OBJECT

public:
    explicit Karnaugh_map(QWidget *parent = nullptr, QString str = "", int count = 0);
    ~Karnaugh_map();

private:
    Ui::Karnaugh_map *ui;
};

#endif // KARNAUGH_MAP_H
