#include "element_litera.h"

element_litera::element_litera(char litera,bool znach):abstract_element(nullptr,nullptr)
{
    litra=litera;
    znachenie=znach;

}

bool element_litera:: get_value(){
    return znachenie;
}

void element_litera::set_value(bool znach){
    znachenie=znach;
}

char element_litera::get_litera(){
    return litra;
}

void element_litera:: print_element(QPainter* painter,int x, int y){
    painter->drawText(x,y,QString(1, litra));
    //painter->drawLine(x,y+5,x-10,y+5);
    //painter->drawLine(x,y+15,x-10,y+15);
    painter->drawLine(x,y+20,x+30,y+20);
    one_input.x=x-10;
    one_input.y=y+5;
    two_input.x=x-10;
    two_input.y=y+15;
    exit.x=x+30;
    exit.y=y+20;
}
