#ifndef ELEMENT_AND_H
#define ELEMENT_AND_H

#include "abstract_element.h"

class element_and : public abstract_element
{
public:
    element_and(abstract_element*first_input=nullptr, abstract_element*second_input=nullptr);
    bool get_value();
    void print_element(QPainter* painter,int x,int y);
};

#endif // ELEMENT_AND_H
