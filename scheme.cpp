#include "scheme.h"
#include <iostream>
#include <sstream>
#include <stack>
#include "ui_schem.h"
#include <QVector>


//преобразование в ПОЛИЗ
std::string infixToPostfix(const std::string& infix) {
    const std::string ops = "|&-";
    std::stringstream ss;
    std::stack<int> s;

    unsigned int infix_index=0;
    while (infix_index<infix.size()) {
        char c = infix[infix_index];
        size_t idx = ops.find(c);

        // check for operator
        if (idx != std::string::npos) {
            while (!s.empty()) {
                int prec2 = s.top() ;
                int prec1 = idx;
                if (prec2 > prec1 || (prec2 == prec1 && c != '^')) {
                    ss << ops[s.top()];
                    s.pop();
                } else break;
            }
            s.push(idx);
        } else if (c == '(') {
            s.push(-2); // -2 stands for '('
        } else if (c == ')') {
            // until '(' on stack, pop operators.
            while (s.top() != -2) {
                ss << ops[s.top()];
                s.pop();
            }
            s.pop();
        } else {
            ss << c;
        }
        infix_index++;
    }

    while (!s.empty()) {
        ss << ops[s.top()];
        s.pop();
    }

    return ss.str();
}


char*DNF_maker(std::vector<char*>);//создание ДНФ по таблице истинности оно тут чтоб в текстовом виде представить
void scheme:: set_table_truth(std::vector<char*> table_truth)//функция все что мы писали перемещено чтоб вызвать
{
    char *DNF=DNF_maker(table_truth);
    std::string Poliz=infixToPostfix(DNF);//строится плиз по ЛНФ
    abstract_element* first = nullptr;
    abstract_element* second = nullptr;
    std::stack<abstract_element*> stack;//создается стек для элементов
    for(int i=0; i<Poliz.size();i++){
        if(Poliz[i]>='a'&& Poliz[i]<='z' || Poliz[i]>='A'&& Poliz[i]<='Z' ){
            int j=0;
            for(j=0;j<array_litera.size();j++){
                if(array_litera[j]->get_litera()==Poliz[i]){//есть ли такая буква
                    second=first;
                    first=array_litera[j];
                    stack.push(array_litera[j]);//отправляем в стек
                    break;
                }
            }
            if(j==array_litera.size()){
                array_litera.push_back(new element_litera(Poliz[i],false));//создаем букву
                stack.push(array_litera[j]);
            }
        }
        if(Poliz[i]=='|'){//если элемент или то два элемента из стека и создаем вентиль
            first=stack.top();
            stack.pop();
            second=stack.top();
            stack.pop();
            array_abstcact_element.push_back(new element_or(first,second));
            stack.push(array_abstcact_element[array_abstcact_element.size()-1]);
        }
        if(Poliz[i]=='&'){
            first=stack.top();
            stack.pop();
            second=stack.top();
            stack.pop();
            array_abstcact_element.push_back(new element_and(first,second));
            stack.push(array_abstcact_element[array_abstcact_element.size()-1]);
        }
        if(Poliz[i]=='-'){
            first=stack.top();
            stack.pop();
            array_abstcact_element.push_back(new element_not(first));
            stack.push(array_abstcact_element[array_abstcact_element.size()-1]);
        }
    }

    //ui->setupUi(this);
    //setMinimumSize(QSize(600, 600));
    repaint();
}


void scheme:: show_window(QPainter* Painter){
  // array_litera[0].print_element(Painter,20,20);
   //for (int i=0; i<array_litera.size();i++){
    //   array_litera[i].print_element(Painter,20,20+i*50);
  // }
   QVector<QVector<abstract_element*>> array_level;//создаем массив уровней и создамем уровни
   array_level.push_back(QVector<abstract_element*>());
   for(int i=0;i<array_litera.size();i++){//создание нулевого уровня
       array_level[0].push_back(array_litera[i]);
   }
   std::vector<abstract_element*> Copy = array_abstcact_element;
   int shag_po_strokam=1;
   while(!Copy.empty()){//создание остальных уровней
       array_level.push_back(QVector<abstract_element*>());
       for (int i=0;i<Copy.size();i++){
           bool get_first=false;
           bool get_second=false;
           for(int j=0;j<array_level.size()-1;j++){
               for(int k=0; k<array_level[j].size();k++){
                   if(Copy[i]->get_first_parent()==array_level[j][k]){
                       get_first=true;
                       break;
                   }
               }
           }
           if(Copy[i]->get_second_parent()!=nullptr){
               for(int j=0;j<array_level.size()-1;j++){
                   for(int k=0; k<array_level[j].size();k++){
                       if(Copy[i]->get_second_parent()==array_level[j][k]){
                           get_second=true;
                           break;
                       }
                   }
               }
           }
           else{
               get_second=true;
           }
           if(get_first && get_second){
               array_level[shag_po_strokam].push_back(Copy[i]);
               Copy.erase(Copy.begin()+i);
               i--;
           }
       }
       shag_po_strokam++;

       //СДЕЛАТЬ ПРИДУМАТЬ И РЕАЛИЗОВАТЬ КАК СОЕДИГИТЬ ЭЛЕМНТЫ И РИСОВАТЬ ЭЛЕМЕНТЫ
   }

   int width = 55, height = 20;//длина и высота окна до 181 строки вычисление размера окна
   int input_count = 0;
   for (int i = 0; i < array_level.size() - 1; i++) {
       for(int j=0;j<array_level[i+1].size();j++){
          if(array_level[i+1][j]->get_second_parent()!=nullptr){
              input_count+=2;
          }
          else{
              input_count++;
          }
       }
   }
   width += input_count * 10;
   width += (array_level.size() - 1) * 55 + 50;
   int max1=0;
   for(int i=0;i<array_level.size();i++){
       if(max1<array_level[i].size()){
           max1=array_level[i].size();
       }
   }
   height += 50 * (max1 + 1);
   height += input_count * 5 + 5;
   setMinimumSize(QSize(width, height));

   int prev_count_imput=array_litera.size();//рисование схемы
   level_indent.resize(array_level.size(),0);
   for(int i=0;i<array_level.size();i++){//проодится по урвням
       int count_imput=0;
       if(i<array_level.size()-1){//высчитываем входы след уровня и ограничение что не выйдем за след
       for(int j=0;j<array_level[i+1].size();j++){
          if(array_level[i+1][j]->get_second_parent()!=nullptr){
              count_imput+=2;
          }
          else{
              count_imput+=1;
          }
       }
       }
       if(i!=0){//если не нулевой уровень, то формируем отступ и для каждого элемента вызываем функцию с такими то парметарами
           level_indent[i]=level_indent[i-1]+50+prev_count_imput*10+5;

            for(int j=0;j<array_level[i].size();j++){

                array_level[i][j]->print_element(Painter,level_indent[i-1]+prev_count_imput*10+5,40*(j+1));
            }


            prev_count_imput=count_imput;
       }
       else{//если нулевой уровень, то начальные данные заадем
           level_indent[i]=55;
           prev_count_imput=count_imput;
           count_imput=-7;
           for(int j=0;j<array_level[i].size();j++){

               array_level[i][j]->print_element(Painter,level_indent[i]+count_imput*5+5,40*(j+1));
           }

       }


   }
   int max=0;//максималбное число элементов на одном уровне и использем его чтоб отспут снизу сформировать
   for(int i=0;i<array_level.size();i++){
       if(max<array_level[i].size()){
           max=array_level[i].size();
       }
   }
   down_indent=50*(max+1);
   for(int i=1;i<array_level.size();i++){//рисование линий
       for(int j=0;j<array_level[i].size();j++){//определяем на каком уровнне вход
           int level=-1;
           for(int k=0;k<i;k++){
               for(int l=0;l<array_level[k].size();l++){
                   if(array_level[k][l]==array_level[i][j]->get_first_parent()){
                       level=k;
                       break;
                   }
               }
               if(level!=-1){
                   break;
               }
           }
           if(level==i-1){//соседние линии
               connect_neighboring(Painter,array_level[i][j]->get_first_parent(),array_level[i][j],1,level);
           }
           else{//если разные уровни соединение через низ
               connect_not_neighboring(Painter,array_level[i][j]->get_first_parent(),array_level[i][j],1,level,i-1);
           }
           if(array_level[i][j]->get_second_parent()!=nullptr){
               int level=-1;
               for(int k=0;k<i;k++){
                   for(int l=0;l<array_level[k].size();l++){
                       if(array_level[k][l]==array_level[i][j]->get_second_parent()){
                           level=k;
                           break;
                       }
                   }
                   if(level!=-1){
                       break;
                   }
               }
               if(level==i-1){
                   connect_neighboring(Painter,array_level[i][j]->get_second_parent(),array_level[i][j],2,level);
               }
               else{
                   connect_not_neighboring(Painter,array_level[i][j]->get_second_parent(),array_level[i][j],2,level,i-1);
               }
           }
       }

   }
}




#include <QGraphicsEllipseItem>


std::vector<char*>table_true(const char*,bool);

scheme::scheme(QWidget *parent) ://конструктор по умолчанию
    QWidget(parent),
    ui(new Ui::schem)
{
    ui->setupUi(this);//создание виджета
}

scheme::scheme(QWidget *parent, std::vector<char*> table, const char* arguments, int count, int type_input) ://конструктор который создает
    QWidget(parent),
    ui(new Ui::schem),
  type(type_input)
{
    ui->setupUi(this);
    if (table.size() > 0) {
        set_table_truth(table);
    }
}

void scheme:: paintEvent(QPaintEvent *event) {//слот которая вызывается тогдакогда мы рисуем окно
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.fillRect(0, 0, width(), height(), Qt::white);
    painter.setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::FlatCap));
    show_window(&painter);
    painter.end();
}

scheme::~scheme()
{
    delete ui;
}
//соединить соседние
void scheme:: connect_neighboring(QPainter* painter,abstract_element* prev,abstract_element* next,int number_input,int level){
    coordinates prev_=prev->get_exit_coordinates();
    coordinates next_;
    if(number_input==1){
        next_=next->get_first_coordinates();
    }
    else{
        next_=next->get_second_coordinates();
    }
    painter->drawLine(prev_.x,prev_.y,level_indent[level],prev_.y);
    painter->drawLine(level_indent[level],prev_.y,level_indent[level],next_.y);
    painter->drawLine(level_indent[level],next_.y,next_.x,next_.y);
    level_indent[level]+=5;
}
//соединить не соседние
void scheme:: connect_not_neighboring(QPainter* painter, abstract_element* prev, abstract_element* next, int number_input,int level_prev, int level_next){
    coordinates prev_=prev->get_exit_coordinates();
    coordinates next_;
    if(number_input==1){
        next_=next->get_first_coordinates();
    }
    else{
        next_=next->get_second_coordinates();
    }
    painter->drawLine(prev_.x,prev_.y,level_indent[level_prev],prev_.y);
    painter->drawLine(level_indent[level_prev],prev_.y,level_indent[level_prev],down_indent);
    painter->drawLine(level_indent[level_prev],down_indent,level_indent[level_next],down_indent);
    painter->drawLine(level_indent[level_next],down_indent,level_indent[level_next],next_.y);
    painter->drawLine(level_indent[level_next],next_.y,next_.x,next_.y);
    level_indent[level_prev]+=5;
    level_indent[level_next]+=5;
    down_indent+=5;

}

