#ifndef SCHEME_H
#define SCHEME_H
#include <vector>
#include "element_litera.h"
#include "element_and.h"
#include "element_not.h"
#include "element_or.h"

namespace Ui {
class schem;
}


struct logic_element{
    logic_element* first;
    logic_element* second;

};


class scheme: public QWidget
{
public:
    explicit scheme(QWidget *parent, std::vector<char*> table, const char* arguments, int count, int type_input=0);
    ~scheme();
    scheme(QWidget *parent = nullptr);
    void set_table_truth(std::vector<char*> table_truth);
    void show_window(QPainter* painter);
//НАРИСОВАТЬ ВХОДЫ ПРИ ЭТОМ РАЗБИТЬ ИХ НА УРОВНИ, ПО ХОРОШЕМУ СХЕМЫ ТОЖЕ РАСПРЕДЕЛИТЬ НА УРОВНИ И ПОТОМ ВСЕ УРОВНИ ПОСЛЕДОВАТЕЛЬНО ПРИРИСОВАТЬ

protected:
    /* Определяем виртуальный метод родительского класса
     * для отрисовки содержимого виджета
     * */
    void paintEvent(QPaintEvent *event);

private: // Начало секции полей и методов, доступных только в наследниках этого класса
    bool first_time=true;
    int type;
    int down_indent;
    Ui::schem *ui;
    std::vector<element_litera*>array_litera;
    std::vector<abstract_element*>array_abstcact_element;
    void connect_neighboring(QPainter*,abstract_element*,abstract_element*,int,int);
    void connect_not_neighboring(QPainter*,abstract_element*,abstract_element*,int,int,int);
    std::vector<int>level_indent;
};



#endif // SCHEME_H
