#include "bdd_graph.h"
#include "ui_bdd_graph.h"
#include <QGraphicsEllipseItem>


std::vector<char*>table_true(const char*,bool);

BDD_graph::BDD_graph(QWindow *parent, std::vector<char*> table, const char* arguments, int count, int type_input) :
    QWindow(parent),
    ui(new Ui::BDD_graph), m_backingStore(new QBackingStore(this)), bdd(table,arguments,count),
  type(type_input)
{
    //ui->setupUi(this);
    setMinimumSize(QSize(600, 600));
}


bool BDD_graph::event(QEvent *event)
{
    if (event->type() == QEvent::UpdateRequest) {
        renderNow();
        return true;
    }
    return QWindow::event(event);
}

void BDD_graph::exposeEvent(QExposeEvent*){
    if(isExposed()){
        renderNow();
    }
}

void BDD_graph::resizeEvent(QResizeEvent *resizeEvent)
{
    // Изменяем размер буфера кадра, чтобы он совпадал с размером окна
    m_backingStore->resize(resizeEvent->size());
    if (isExposed())
    {
        renderNow();
    }
}

void BDD_graph::renderLater()
{
    requestUpdate();
}

void BDD_graph::renderNow()
{
    if (!isExposed())
    {
        return;
    }

    QRect rect(0, 0, width(), height());
    m_backingStore->beginPaint(rect);

    QPaintDevice *device = m_backingStore->paintDevice();
    QPainter painter(device);

    painter.fillRect(0, 0, width(), height(), Qt::white);
    render(&painter);
    painter.end();

    m_backingStore->endPaint();
    m_backingStore->flush(rect);
}


void BDD_graph::render(QPainter *painter)
{
    // Устанавливаем режим устранения ступенчатости фигур (anti-aliasing mode)
    painter->setRenderHint(QPainter::Antialiasing);

    // Устанавливаем кисть ГОЛУБОГО цвета (цвет задан в RGB)
    painter->setBrush(QBrush(Qt::blue));
    Vertex* ptr= nullptr;
    if(type==1){
    bdd.Sokrachatel();
    }
    int i=0;
    Vertex* iterator;
    while(ptr==nullptr){
        iterator=bdd.Get_vertex(i);
        int j=0;
        for(j=0;j<iterator->vertexes.size();j++){
            if(iterator->vertexes[j].direction==2){
                break;
            }
        }
        if(j==iterator->vertexes.size()){
            ptr=iterator;
        }
        else{
            i++;
        }
    }
    tree_print(painter, ptr, 0, width(), 20);
}


void BDD_graph::tree_print(QPainter *painter, Vertex *p, int left_border, int right_border, int y) {
    if (p == nullptr) return;
   // System::Drawing::Brush ^black2 = gcnew System::Drawing::SolidBrush(System::Drawing::Color::Black);
   // System::Drawing::Font ^font = gcnew System::Drawing::Font("Arial", (float)12);
    int offset = 10;
    if(p->data=="0" ||p->data=="1" ){
        painter->drawRect(QRect(left_border + (right_border - left_border) / 2 - offset, y - offset, 20, 20));
    }
    else {
    painter->drawEllipse(QRect(left_border + (right_border - left_border) / 2 - offset, y - offset, 20, 20));
    }
    painter->setPen(Qt::white);
    painter->drawText((left_border + (right_border - left_border) / 2) - 4, y + 3, QString::fromStdString(p->data));
     painter->setPen(Qt::blue);
    Vertex* left = nullptr;
    Vertex* right = nullptr;
    for(int i=0;i<p->vertexes.size();i++){
     if(p->vertexes[i].direction==1){
         if(p->vertexes[i].type==1){
             left=p->vertexes[i].vertex;
         }
         else{
             right=p->vertexes[i].vertex;
         }
     }
    }
    if (right == nullptr) {
        right = left;
    }
    if (left) {
        painter->setPen(Qt::DashLine);
        painter->drawLine(10 + left_border + (right_border - left_border) / 2 - offset, y + 20 - offset, 10 + left_border + (((left_border + (right_border - left_border) / 2) - left_border) / 2) - offset, y + 50 - offset);
        painter->setPen(Qt::SolidLine);
    }
    if (right) {
        painter->drawLine(10 + left_border + (right_border - left_border) / 2 - offset, y + 20 - offset, 10 + (left_border + (right_border - left_border) / 2) + ((right_border - (left_border + (right_border - left_border) / 2)) / 2) - offset, y + 50 - offset);
    }
    tree_print(painter, left, left_border, left_border + (right_border - left_border) / 2, y + 50);
    tree_print(painter, right, left_border + (right_border - left_border) / 2, right_border, y + 50);
};

BDD_graph::~BDD_graph()
{
    delete ui;
}
