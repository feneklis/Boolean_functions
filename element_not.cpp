#include "element_not.h"
#include "abstract_element.h"

element_not::element_not(abstract_element*first_input): abstract_element(first_input)
{

}
bool element_not:: get_value(){
    bool first_value=false;
    if(first!=nullptr){
        first_value=first->get_value();
    }
    return !first_value;
}

void element_not::print_element(QPainter* painter,int x, int y){
  //  painter->drawRect(QRect(x,y, 20, 20));
    //painter->drawText(x+5,y+10,QString(1, '-'));
    QPointF *array=new QPointF[3];
    array[0]=QPointF(x,y);
    array[1]=QPointF(x,y+20);
    array[2]=QPointF(x+35,y+10);
    //{QPointF(x,y),QPointF(x,y+30),QPointF(x+40,y+15)};
    painter->drawPolygon(array,3);
    painter->drawEllipse(x+35,y+8,4,4);
    painter->drawLine(x,y+10,x-10,y+10);
    //painter->drawLine(x,y+15,x-10,y+15);
    painter->drawLine(x+39,y+10,x+49,y+10);
    one_input.x=x-10;
    one_input.y=y+10;
    two_input.x=x-10;
    two_input.y=y+15;
    exit.x=x+49;
    exit.y=y+10;
}
