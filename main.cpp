#include "mainwindow.h"
#include "bdd_graph.h"
#include <QApplication>
#include "scheme.h"

std::vector<char*> table_true(const char* DNF_input, bool compress = true);
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    //BDD_graph proverka;
    //proverka.show();
    //scheme sch(nullptr,table_true("a&c|b|-c&-b"),"abc",3);
  //sch.show();
    return a.exec();
}
