#ifndef ELEMENT_NOT_H
#define ELEMENT_NOT_H

#include "abstract_element.h"

class element_not : public abstract_element
{
public:
    element_not(abstract_element*first_input=nullptr);
    bool get_value();
    void print_element(QPainter* painter,int x,int y);
};

#endif // ELEMENT_NOT_H
