#include "element_and.h"
#include "abstract_element.h"

element_and::element_and(abstract_element*first_input,abstract_element*second_input): abstract_element(first_input,second_input)
{

}
bool element_and:: get_value(){
    bool first_value=false;
    bool second_value=false;
    if(first!=nullptr){
        first_value=first->get_value();
    }
    if(second){
        second_value=second->get_value();
    }
    return first_value && second_value;
}

void element_and::print_element(QPainter* painter,int x, int y){
    //painter->drawRect(QRect(x,y, 20, 20));
    //painter->drawText(x,y,QString(1, '&'));
    painter->drawPie(x,y,40,20,270*16,180*16);
    painter->drawLine(x+20,y+5,x+10,y+5);
    painter->drawLine(x+20,y+15,x+10,y+15);
    painter->drawLine(x+40,y+10,x+50,y+10);
    one_input.x=x+10;
    one_input.y=y+5;
    two_input.x=x+10;
    two_input.y=y+15;
    exit.x=x+50;
    exit.y=y+10;
}
