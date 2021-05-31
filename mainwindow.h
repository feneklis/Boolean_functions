#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "helpwindow.h"
#include "theory_window.h"
#include "plus_minus_window.h"
#include "karnaugh_map.h"
#include "bdd_graph.h"
#include "schemeform.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_Table_true_button_clicked();

    void on_Helpbutton_clicked();

    void on_Input_type_2_clicked();

    void on_Input_type_clicked();

    void on_Clear_button_clicked();

    void on_Theory_button_clicked();

    void on_plus_minus_button_clicked();

    void on_Vector_clicked();

private:
    Ui::MainWindow *ui;
    bool Parsing(const char*);
    std::vector<HelpWindow*> helpwindows;
    std::vector<Theory_window*> theorywindows;
    std::vector<Plus_minus_window*> plusminuswindows;
    std::vector<Karnaugh_map*> karnowindows;
    std::vector<BDD_graph*> bddwindows;
    std::vector<SchemeForm*>schem;
};
#endif // MAINWINDOW_H
