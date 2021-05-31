#include "abstract_element.h"

abstract_element:: abstract_element(abstract_element*first_input, abstract_element*second_input)
{
first=first_input;
second=second_input;
}

abstract_element* abstract_element:: get_first_parent(){
    return first;
}

abstract_element* abstract_element:: get_second_parent(){
    return second;
}

coordinates abstract_element:: get_first_coordinates(){
    return one_input;
}
coordinates abstract_element:: get_second_coordinates(){
    return two_input;
}
coordinates abstract_element:: get_exit_coordinates(){
    return exit;
}
