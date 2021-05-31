#ifndef ELEMENT_LITERA_H
#define ELEMENT_LITERA_H

#include "abstract_element.h"
#include <QMainWindow>
#include <QtGui/QWindow>
#include <QtGui/QPainter>
#include <QtGui/QResizeEvent>
#include <QtGui/QExposeEvent>
#include <QtGui/QBackingStore>

class element_litera : public abstract_element
{
public:
    element_litera(char,bool);
    bool get_value();
    void print_element(){

    };
    void print_element(QPainter*,int x, int y);
    void set_value(bool);
    char get_litera();
private:
    char litra;
    bool znachenie;


};

#endif // ELEMENT_LITERA_H
