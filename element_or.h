#ifndef ELEMENT_OR_H
#define ELEMENT_OR_H

#include "abstract_element.h"

class element_or : public abstract_element
{
public:
    element_or(abstract_element*first_input=nullptr, abstract_element*second_input=nullptr);
    bool get_value();
    void print_element(QPainter* painter,int x,int y);
};

#endif // ELEMENT_OR_H
