#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "kurs.cpp"
#include "helpwindow.h"
#include "theory_window.h"
#include "plus_minus_window.h"
#include "karnaugh_map.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    for (unsigned int i = 0; i < helpwindows.size(); i++) {
        delete helpwindows[i];
    }
    for (unsigned int i = 0; i < theorywindows.size(); i++) {
        delete theorywindows[i];
    }
    for (unsigned int i = 0; i < plusminuswindows.size(); i++) {
        delete plusminuswindows[i];
    }
    for (unsigned int i = 0; i < karnowindows.size(); i++) {
        delete karnowindows[i];
    }
    for (unsigned int i = 0; i < bddwindows.size(); i++) {
        delete bddwindows[i];
    }
    for (unsigned int i = 0; i < schem.size(); i++) {
        delete schem[i];
    }
    delete ui;
}

bool MainWindow::Parsing(const char* DNF)//разбор текста на составляющие. проверка строки на корректность
{
    int lenght;
    int i;
    lenght = strlen(DNF);

    if (lenght == 0) {
        return 0;
    }

    if(ui->Input_type->isChecked()){
        if (DNF[0] >= 65 && DNF[0] <= 90 || DNF[0] >= 97 && DNF[0] <= 122 || DNF[0] == '-') {
        }
        else {
            return 0;
        }
        if (DNF[lenght-1] >= 65 && DNF[lenght - 1] <= 90 || DNF[lenght - 1] >= 97 && DNF[lenght - 1] <= 122 ) {
        }
        else {
            return 0;
        }

        for (i = 0;i < lenght - 1;i++) {
            if (DNF[i] >= 65 && DNF[i] <= 90 || DNF[i] >= 97 && DNF[i] <= 122){
                if (DNF[i + 1] >= 65 && DNF[i + 1] <= 90 || DNF[i + 1] >= 97 && DNF[i + 1] <= 122|| DNF[i+1]=='-')
                    return 0;
            }
            else {
                if(DNF[i]!='|' && DNF[i]!='&' && DNF[i]!='-')
                    return 0;
            }
            if (DNF[i] == '&' || DNF[i] == ' | ')
                if (DNF[i + 1] == '&' || DNF[i + 1] == '|')
                    return 0;
            if (DNF[i] == '-')
                if (DNF[i+1] == '&' || DNF[i + 1] == '|' || DNF[i + 1] == '-')
                    return 0;
        }
    }
    else {
        int open_close=0;
        for (i = 0; i < lenght;i++) {
            if(DNF[i]=='('){
                open_close++;
            }
            else if(DNF[i]==')'){
                open_close--;
            }
            if (DNF[i] >= 65 && DNF[i] <= 90 || DNF[i] >= 97 && DNF[i] <= 122 || DNF[i] == '-' || DNF[i] == '&' || DNF[i] == '|' ) {
                continue;
            }
        }
        if (i < lenght || open_close) {
            return 0;
        }

        if (DNF[0] >= 65 && DNF[0] <= 90 || DNF[0] >= 97 && DNF[0] <= 122 || DNF[0] == '-' || DNF[0]=='(') {
        }
        else {
            return 0;
        }
        if (DNF[lenght-1] >= 65 && DNF[lenght - 1] <= 90 || DNF[lenght - 1] >= 97 && DNF[lenght - 1] <= 122 || DNF[lenght-1]==')') {
        }
        else {
            return 0;
        }

        for (i = 0;i < lenght - 1;i++) {
            if (DNF[i] >= 65 && DNF[i] <= 90 || DNF[i] >= 97 && DNF[i] <= 122){
                if (DNF[i + 1] >= 65 && DNF[i + 1] <= 90 || DNF[i + 1] >= 97 && DNF[i + 1] <= 122 || DNF[i+1]=='-')
                    return 0;}
            else{
                if(DNF[i]!='|' && DNF[i]!='&'  && DNF[i]!='-' && DNF[i]!=')' && DNF[i]!='(')
                    return 0;
            }
            if (DNF[i] == '&' || DNF[i] == ' | ')
                if (DNF[i + 1] == '&' || DNF[i + 1] == '|' ||DNF[i+1]==')')
                    return 0;
            if (DNF[i] == '-')
                if (DNF[i+1] == '&' || DNF[i + 1] == '|' || DNF[i + 1] == '-' || DNF[i+1]=='(' || DNF[i+1]==')')
                    return 0;
            if (DNF[i] == '(' || DNF[i]==')')
                if (DNF[i+1]=='(' || DNF[i+1]==')')
                    return 0;
            if (DNF[i] == '(')
                if (DNF[i+1] == '&' || DNF[i + 1] == '|')
                    return 0;
        }
    }
    return 1;
}

void MainWindow::on_Table_true_button_clicked()
{
    bool t = true;
    bool need_compress = true;
    std::string input = ui->Input->toPlainText().toStdString();
    char arguments[256];
    int count=0;
    std::vector<char*> table;
    if(ui->Vector->isChecked()){
        if((input.size()&(input.size()-1))!=0){
            ui->Output->setText(QString::fromUtf8("Вектор должен состоять из 2<sup>n</sup> значений."));
            return;
        }
        int letter=0;
        while(input[letter]=='0' || input[letter]=='1'){
            letter++;
        }
        if(input[letter]!='\0'){
            ui->Output->setText(QString::fromUtf8("Некорректно введённая строка."));
            return;
        }
        for (int i = 0; i < 256; i++) {
            arguments[i] = '_';
        }
        int len, lenning;
        len = input.size();
        lenning= 1;
        while(!(lenning&len)){
            lenning<<=1;
            count++;
        }
        for (int i = 0; i < count; i++) {
            arguments[97+i] = '*';
        }
        table=table_true_from_vector(input.c_str());
    }
    else{
        for (int i = 0; i < 256; i++) {
            arguments[i] = '_';
        }
        for (int i = 0; i < input.size(); i++) {
            if (input[i] >= 65 && input[i] <= 90 || input[i] >= 97 && input[i] <= 122) {
                if(arguments[input[i]]=='_'){
                    count++;
                }
                arguments[input[i]] = '*';
            }
        }
        t = Parsing(input.c_str());
        if (t == 0) {
            ui->Output->setText(QString::fromUtf8("Некорректно введённая строка."));
            return;
        }
        if(ui->Output_type->isChecked()){
            need_compress=false;
        }

        if (ui->Input_type->isChecked()) {
            table = table_true(input.c_str(), need_compress);
        } else {
            table = table_true_from_KNF(input.c_str(), need_compress);
        }
    }
    ui->Output->setText("");
    if(ui->DNF->isChecked()){
        char *temp = DNF_maker(table);
        ui->Output->setText(temp);
        delete []temp;
        return;

    }


    if(ui->CDNF->isChecked()){
        QString table_str;
        for (int i = 0; i < pow(2,count); i++) {
            int vec = i, count_rang=1<<(count-1);
            int shag_argument=0;
            for (int j = 0; j < count; j++) {
                if((vector_check(vec,arguments,table,count))){
                    while (arguments[shag_argument]!='*') {
                        shag_argument++;
                    }
                    if(!(vec&count_rang)){
                        table_str += '-';
                    }
                    count_rang>>=1;
                    table_str += shag_argument ;
                    if(count_rang){
                        table_str+='&';
                    }
                    shag_argument++;
                }
            }
            if((vector_check(vec,arguments,table,count))){
                table_str+='|';
            }
        }
        table_str.remove(table_str.size()-1,1);
        ui->Output->setText(table_str);
        for (unsigned int i = 0; i < table.size(); i++) {
            delete []table[i];
        }
        return;
    }

    if(ui->CKNF->isChecked()){
        QString table_str;
        for (int i = 0; i < pow(2,count); i++) {
            int vec = i, count_rang=1<<(count-1);
            int shag_argument=0;
            if(!(vector_check(vec,arguments,table,count))){
                table_str+='(';
            }
            for (int j = 0; j < count; j++) {
                if(!(vector_check(vec,arguments,table,count))){
                    while (arguments[shag_argument]!='*') {
                        shag_argument++;
                    }
                    if((vec&count_rang)){
                        table_str += '-';
                    }
                    count_rang>>=1;
                    table_str += shag_argument ;
                    if(count_rang){
                        table_str+='|';
                    }
                    shag_argument++;
                }
            }
            if(!(vector_check(vec,arguments,table,count))){
                table_str+=")&";
            }
        }
        table_str.remove(table_str.size()-1,1);
        ui->Output->setText(table_str);
        for (unsigned int i = 0; i < table.size(); i++) {
            delete []table[i];
        }
        return;
    }
    if(ui->Polinom->isChecked()){
        char *temp = Polinom_maker(table,arguments,count);
        ui->Output->setText(temp);
        delete []temp;
        return;
    }

    if(ui->TablePost->isChecked()){
        char* temp= Table_post(table,arguments,count);
        QString table_str;
        table_str += QString::fromUtf8("<table class='table table-bordered table-center' border=\"1\"><tbody><tr>");
        table_str += QString::fromUtf8("<td align='center'>") + " T<sub>0</sub> " + QString::fromUtf8("</td>");
        table_str += QString::fromUtf8("<td align='center'>") + " T<sub>1</sub> " + QString::fromUtf8("</td>");
        table_str += QString::fromUtf8("<td align='center'>") + " M " + QString::fromUtf8("</td>");
        table_str += QString::fromUtf8("<td align='center'>") + " L " + QString::fromUtf8("</td>");
        table_str += QString::fromUtf8("<td align='center'>") + " S " + QString::fromUtf8("</td>");
        table_str += QString::fromUtf8("</tr>");
        table_str += QString::fromUtf8("<tr>");
        for (int j = 0; j < 5; j++) {
            table_str += QString::fromUtf8("<td align='center'>") + temp[j] + QString::fromUtf8("</td>");
        }
        table_str += QString::fromUtf8("</tr>");
        table_str += QString::fromUtf8("</tbody></table>");
        table_str += QString::fromUtf8("</h4><h4>T<sub>0</sub></h4><p>Функция принадлежит классу T<sub>0</sub>, если на нулевом наборе она <br> принимает значение 0.<br> </p><h4>T<sub>1</sub></h4><p>Функция принадлежит классу T<sub>1</sub>, если на единичном наборе она принимает<br> значение 1.</p><h4>L</h4><p>Функция принадлежит классу линейных функций (L), если её полином <br> Жегалкина не содержит произведений.</p><h4>M</h4><p>Функция принадлежит классу монотонных функций (M), если для любой <br> пары наборов α и β таких, что α ≤ β, выполняется условие f(α) ≤ f(β).</p><h4>S</h4><p>Функция принадлежит классу самодвойственных функций (S), если на <br> противоположных наборах она принимает противоположные значения.</p></div>");
        ui->Output->setText(table_str);
        delete []temp;
        return;
    }

    if(ui->KNF->isChecked()){
        char *temp = KNF_maker(table);
        ui->Output->setText(temp);
        delete []temp;
        return;
    }
    if(ui->Karno->isChecked()){
        //ui->webView->setHtml(Karno(table, arguments, count));
        karnowindows.push_back(new Karnaugh_map(this, Karno(table, arguments, count), count));
        karnowindows.back()->show();
        return;
    }
    if(ui->BDDGraph->isChecked()){
        bddwindows.push_back(new BDD_graph(nullptr, table, arguments, count));
        bddwindows.back()->show();
    }
    if(ui->SokrBDD->isChecked()){
        bddwindows.push_back(new BDD_graph(nullptr, table, arguments, count,1));
        bddwindows.back()->show();
    }
    if(ui->Schem->isChecked()){
        schem.push_back(new SchemeForm(nullptr,table,arguments,count));
        schem.back()->show();
    }
    QString table_str;
    /*table_str += QString::fromUtf8("<table class='table table-bordered table-center'><tbody><tr>");
    for (int j = 0; j < 256; j++) {
        if (arguments[j] == '*') {
            //ui->Output->setText(ui->Output->text() + (unsigned char)j);
            table_str += QString::fromUtf8("<td align='center'>") + (unsigned char)j + QString::fromUtf8("</td>");
        }
    }
    table_str += QString::fromUtf8("</tr>");
    //ui->Output->setText(ui->Output->text() + '\n');
    for (int i = 0; i < table.size(); i++) {
        table_str += QString::fromUtf8("<tr>");
        for (int j = 0; j < 256; j++) {
            if (arguments[j] == '*') {
                //ui->Output->setText(ui->Output->text() + table[i][j]);
                table_str += QString::fromUtf8("<td align='center'>") + table[i][j] + QString::fromUtf8("</td>");
            }
        }
        //ui->Output->setText(ui->Output->text() + '\n');
        table_str += QString::fromUtf8("</tr>");
    }
    table_str += QString::fromUtf8("</tbody></table>");
    ui->Output->setText(table_str);*/

    //ui->Output->setText(QString::fromUtf8("<table class='table table-bordered table-center'><tbody><tr><td align='center'>a</td><td align='center'>b</td><td align='center'>c</td><td align='center'>a&amp;b</td><td align='center'>(a&amp;b)&amp;c</td><td align='center'>⌐a</td><td align='center'>(⌐a)&amp;b</td><td align='center'>((a&amp;b)&amp;c)v((⌐a)&amp;b)</td></tr><tr><td align='center'>0</td><td align='center'>0</td><td align='center'>0</td><td align='center'>0</td><td align='center'>0</td><td align='center'>1</td><td align='center'>0</td><td align='center'>0</td></tr><tr><td align='center'>0</td><td align='center'>0</td><td align='center'>1</td><td align='center'>0</td><td align='center'>0</td><td align='center'>1</td><td align='center'>0</td><td align='center'>0</td></tr><tr><td align='center'>0</td><td align='center'>1</td><td align='center'>0</td><td align='center'>0</td><td align='center'>0</td><td align='center'>1</td><td align='center'>1</td><td align='center'>1</td></tr><tr><td align='center'>0</td><td align='center'>1</td><td align='center'>1</td><td align='center'>0</td><td align='center'>0</td><td align='center'>1</td><td align='center'>1</td><td align='center'>1</td></tr><tr><td align='center'>1</td><td align='center'>0</td><td align='center'>0</td><td align='center'>0</td><td align='center'>0</td><td align='center'>0</td><td align='center'>0</td><td align='center'>0</td></tr><tr><td align='center'>1</td><td align='center'>0</td><td align='center'>1</td><td align='center'>0</td><td align='center'>0</td><td align='center'>0</td><td align='center'>0</td><td align='center'>0</td></tr><tr><td align='center'>1</td><td align='center'>1</td><td align='center'>0</td><td align='center'>1</td><td align='center'>0</td><td align='center'>0</td><td align='center'>0</td><td align='center'>0</td></tr><tr><td align='center'>1</td><td align='center'>1</td><td align='center'>1</td><td align='center'>1</td><td align='center'>1</td><td align='center'>0</td><td align='center'>0</td><td align='center'>1</td></tr></tbody></table>"));
    table_str="";
    table_str += QString::fromUtf8("<table class='table table-bordered table-center'><tbody><tr>");
    for (int j = 0; j < 256; j++) {
        if (arguments[j] == '*') {
            //ui->Output->setText(ui->Output->text() + (unsigned char)j);
            table_str += QString::fromUtf8("<td align='center'>") + (unsigned char)j + QString::fromUtf8("</td>");
        }
    }
    QString func=ui->Input->toPlainText().toUtf8();
    if(ui->Vector->isChecked()){
        func='F';
    }
    table_str += QString::fromUtf8("<td align='center'>") + func + QString::fromUtf8("</td>");
    table_str += QString::fromUtf8("</tr>");
    //ui->Output->setText(ui->Output->text() + '\n');
    for (int i = 0; i < pow(2,count); i++) {
        table_str += QString::fromUtf8("<tr>");
        int vec = i, count_rang=1<<(count-1);
        for (int j = 0; j < count; j++) {
            char symbol='1';
            if(!(vec&count_rang)){
                symbol='0';
            }
            count_rang>>=1;
            table_str += QString::fromUtf8("<td align='center'>") + symbol + QString::fromUtf8("</td>");
        }
        char simvol='1';
        if(!(vector_check(vec,arguments,table,count))){
            simvol='0';
        }
        table_str += QString::fromUtf8("<td align='center'>") + simvol + QString::fromUtf8("</td>");
        table_str += QString::fromUtf8("</tr>");
    }
    table_str += QString::fromUtf8("</tbody></table>");
    ui->Output->setText(table_str);
    for (unsigned int i = 0; i < table.size(); i++) {
        delete []table[i];
    }

}



void MainWindow::on_Helpbutton_clicked()
{
    helpwindows.push_back(new HelpWindow());
    helpwindows.back()->show();
}

void MainWindow::on_Input_type_2_clicked()
{
    ui->Input->setPlaceholderText(QString::fromUtf8("Введите КНФ"));
}

void MainWindow::on_Input_type_clicked()
{
    ui->Input->setPlaceholderText(QString::fromUtf8("Введите ДНФ"));
}

void MainWindow::on_Clear_button_clicked()
{
    ui->Input->setText("");
    ui->Output->setText("");
}

void MainWindow::on_Theory_button_clicked()
{
    Theory_window theory ;
    theorywindows.push_back(new Theory_window());
    theorywindows.back()->show();
}


void MainWindow::on_plus_minus_button_clicked()
{
    plusminuswindows.push_back(new Plus_minus_window());
    if(ui->Output_type->isChecked()){plusminuswindows.back()->Chang_Text(0);}
    if(ui->DNF->isChecked()){plusminuswindows.back()->Chang_Text(2);}
    if(ui->KNF->isChecked()){plusminuswindows.back()->Chang_Text(1);}
    if(ui->CDNF->isChecked()){plusminuswindows.back()->Chang_Text(3);}
    if(ui->CKNF->isChecked()){plusminuswindows.back()->Chang_Text(4);}
    if(ui->Polinom->isChecked()){plusminuswindows.back()->Chang_Text(5);}
    if(ui->TablePost->isChecked()){plusminuswindows.back()->Chang_Text(6);}
    if(ui->Karno->isChecked()){plusminuswindows.back()->Chang_Text(7);}
    if(ui->BDDGraph->isChecked()){plusminuswindows.back()->Chang_Text(8);}
    if(ui->SokrBDD->isChecked()){plusminuswindows.back()->Chang_Text(9);}
    if(ui->Schem->isChecked()){plusminuswindows.back()->Chang_Text(10);}
    plusminuswindows.back()->show();
}


void MainWindow::on_Vector_clicked()
{
    ui->Input->setPlaceholderText(QString::fromUtf8("Введите вектор"));
}

