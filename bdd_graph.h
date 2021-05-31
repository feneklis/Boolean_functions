#ifndef BDD_GRAPH_H
#define BDD_GRAPH_H

#include <QMainWindow>
#include <QtGui/QWindow>
#include <QtGui/QPainter>
#include <QtGui/QResizeEvent>
#include <QtGui/QExposeEvent>
#include <QtGui/QBackingStore>
#include "graph.h"

namespace Ui {
class BDD_graph;
}

class BDD_graph : public QWindow
{
    Q_OBJECT

public:
    explicit BDD_graph(QWindow *parent, std::vector<char*> table, const char* arguments, int count, int type_input=0);
    ~BDD_graph();

protected: // Начало секции полей и методов, доступных только в наследниках этого класса

    // Ниже перегружены полиморфные методы родительского класса QWindow
    // Библиотека Qt рассылает различные события по этим методам
    //  - метод event вызывается перед обработкой любых событий, включая resizeEvent и exposeEvent
    //  - метод resizeEvent вызывается при изменении размера окна
    //  - метод exposeEvent вызывается при показе окна
    bool event(QEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void exposeEvent(QExposeEvent *event) override;

private: // Начало секции полей и методов, доступных только в наследниках этого класса

    void renderLater();
    void renderNow();
    void render(QPainter *painter);
    void tree_print(QPainter *painter, Vertex *p, int left_border, int right_border, int y);
    int type;

    // Класс QBackingStore предоставляет окну буфер рисования кадра.
    // Грубо говоря, этот буфер содержит будущие пиксели окна и позволяет
    //  рисовать векторную графику (фигуры, изображения, текст), заполняя
    //  этот буфер пикселей.
    QBackingStore *m_backingStore = nullptr;
    Ui::BDD_graph *ui;
    Graph bdd;
};

#endif // BDD_GRAPH_H

