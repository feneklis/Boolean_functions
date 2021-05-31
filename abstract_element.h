#ifndef ABSTRACT_ELEMENT_H
#define ABSTRACT_ELEMENT_H
#include <QPainter>

struct coordinates {
    int x;
    int y;
};
class abstract_element
{
public:
    abstract_element(abstract_element*first_input=nullptr, abstract_element*second_input=nullptr);
    virtual bool get_value()=0;
    virtual void print_element(QPainter*, int,int)=0;
    abstract_element* get_first_parent();
    abstract_element* get_second_parent();
    coordinates get_first_coordinates();
    coordinates get_second_coordinates();
    coordinates get_exit_coordinates();
protected:
    abstract_element *first;
   abstract_element *second;
   coordinates one_input;
   coordinates two_input;
   coordinates exit;
};

#endif // ABSTRACT_ELEMENT_H
