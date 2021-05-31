#include "element_or.h"
#include "abstract_element.h"

element_or::element_or(abstract_element*first_input,abstract_element*second_input): abstract_element(first_input,second_input)
{

}
bool element_or:: get_value(){
    bool first_value=false;
    bool second_value=false;
    if(first!=nullptr){
        first_value=first->get_value();
    }
    if(second){
        second_value=second->get_value();
    }
    return first_value || second_value;
}

void element_or::print_element(QPainter* painter,int x, int y){
   // painter->drawRect(QRect(x,y, 20, 20));
   // painter->drawText(x,y,QString(1, '|'));
    painter->drawArc(x,y,30,20,270*16,180*16);
     painter->drawArc(x-5,y,50,20,270*16,180*16);
     painter->drawLine(x+27,y+5,x+17,y+5);
     painter->drawLine(x+27,y+15,x+17,y+15);
     painter->drawLine(x+45,y+10,x+55,y+10);
     one_input.x=x+17;
     one_input.y=y+5;
     two_input.x=x+17;
     two_input.y=y+15;
     exit.x=x+55;
     exit.y=y+10;
}
