// kurs.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <vector>
#include <math.h>
#include <QString>

/*class Node
{
    char* arguments;
    int* coordinates;
    Node *parent;
    std::vector<Node*> childs;

public:
    Node() { parent = NULL, arguments = NULL; coordinates = NULL; };
    ~Node() {};
    Node(char*);
    Node(char*, Node*, int*);
    friend class Logic_schema_tree; //подготвка для построения дерева
    void Treegrowing(char**, int, Node*); //Строит дерево
    void Get_truth_table(char**,int&); // возвращает таблицу истинности
};



Node::Node(char* arguments_) 
{
    parent = NULL;
    coordinates = NULL;
    int i;
    for (i = 0; arguments_[i] != '\0'; i++);
    i++;
    arguments = new char[i];
    for (int j = 0; j < i; j++) arguments[j] = arguments_[j];
}

Node::Node(char* arguments_, Node*P, int*Cor)
{
    parent = P;
    coordinates = Cor;
    int i;
    for (i = 0; arguments_[i] != '\0'; i++);
    i++;
    arguments = new char[i];
    for (int j = 0; j < i; j++) arguments[j] = arguments_[j];
}

void Node::Treegrowing(char** temp, int n, Node* P) {
    char actual, next;
    int *exists = new int[n];
    int l = 0;
    for (actual = arguments[0] + 1; actual < 255; actual = next) {
        exists[0] = -1;
        l = 0;
        next = 255;
        for (int k = coordinates[0]; k != -1; k++) {
            int s = 0;
            while ((temp[k][s] < actual) && (temp[k][s] != '\0'))
                s++;
            if (temp[k][s] == actual) {
                exists[l] = k;
                exists[l + 1] = -1;
                l++;
                if ((temp[k][s + 1] != '\0') && (temp[k][s + 1] < next)) {
                    next = temp[k][s + 1];
                }
            }
            else {
                if ((temp[k][s] != '\0') && (temp[k][s] < next)) {
                }
            }

        }
        if (exists[0] != -1) {
            Node* Result = new Node;
            Result->arguments = new char[2];
            Result->arguments[0] = actual;
            Result->coordinates = new int[l + 1];
            for (int i = 0; i <= l; i++) {
                Result->coordinates[i] = exists[i];
            }
            Result->parent = P;
            P->childs.push_back(Result);
        }
    }
    delete[]exists;
    for (int i = 0; i < P->childs.size(); i++) {
        Treegrowing(temp, n, P->childs[i]);
    }
}
*/
/*void Node::Get_truth_table(char** table, int& n) {
 *
    if (childs.size() > 0) {
        char***temp = new char**[childs.size()];
        int* n_table = new int[childs.size()];
        for (int i = 0; i < childs.size(); i++) {
            Get_truth_table(temp[i], n_table[i]);
        }
        std::vector <char*> Resultate;
        char* ptr;
        bool smotr_diapozon, smotr_nayden;//2 случая с помощью одной какая то область уже входит в результат, а другая что область обхватывает из результата
        for (int i = 0; i < childs.size(); i++) {
            for (int j = 0; j < n_table[i]; j++) {
                smotr_diapozon = false;
                smotr_nayden = false;
                for (int k = 0; k < Resultate.size(); k++) {
                    int z;
                    for (z = 0; z < 256; z++) {
                        if (Resultate[k][z] != temp[i][j][z]) {//если результат не совпадает с нашей областью темп-набор таблиц истинности
                            if (temp[i][j][z] == '-') {
                                smotr_diapozon = true;//если ---- резльтат а 1--- ребенок то надо доопределить
                            }
                            else if (Resultate[k][z] == '-') {//наоборот
                                smotr_nayden = true;
                                if (smotr_diapozon) {//два разных интервала смотри дальше
                                    smotr_diapozon = false;
                                    smotr_nayden = false;
                                    break;
                                }
                            }
                            else {//если просто отлиаются то два разных интервала 1100 1111
                                smotr_diapozon = false;
                                smotr_nayden = false;
                                break;
                            }
                        }
                    }
                    if (z == 256) {
                        smotr_nayden = true;
                    }
                    if (smotr_nayden) {
                        break;
                    }
                    if (!smotr_nayden) {//если интервал не содержится польностью в интервале результата то смотрим
                        if (smotr_diapozon) {//если наш интервал получился больше чем какой то из результата
                            for (z = 0; z < 256; z++) {
                                if (Resultate[k][z] != temp[i][j][z]) {//если символы не совпадают заполнить
                                    Resultate[k][z] = temp[i][j][z];
                                }
                            }
                            break;
                        }
                    }
                }
                if (!smotr_nayden) {//если интервал не нашли внутри результата и интервал не покрывает никакй интервал то мы его добавляем как новый интервал
                    if (!smotr_diapozon) {
                        ptr = new char[256];
                        for (int z = 0; z < 256; z++) {
                            ptr[z] = temp[i][j][z];
                        }
                        Resultate.push_back(ptr);
                        ptr = NULL;
                    }
                }
            }
        }
        n = Resultate.size();//до обработки не знаем скоько выйдет
        table = new char*[n];//формируем интревалы
        for (int i = 0; i < n; i++) {
            table[i] = new char[256];
        }
        for (int i = 0; i < n; i++) {//заполняем интервалы
            for (int j = 0; j < 256; j++) {
                table[i][j] = Resultate[i][j];
            }
        }
        for (int i = 0; i < childs.size(); i++) {
            for (int j = 0; j < n_table[i]; j++) {
                delete []temp[i][j];
            }
        }
        for (int i = 0; i < childs.size(); i++) {
            delete[]temp[i];
        }
        for (int i = 0; i < Resultate.size(); i++) {
            delete[]Resultate[i];
        }
        delete[]temp;
        delete[]n_table;
        return;
        /* Надо из кучи таблиц истинности полученных с детей сформировать общую таблицу истинности
        и вернуть

    }
    table = new char*[1];// обработка листов
    table[0] = new char[256];
    n = 1;
    for (int i = 0; i < 256; i++) {
        table[0][i] = '-';
    }
    table[0][arguments[0]] = '1';
}


class Logic_schema_tree
{
    Node *root;

public:
    Logic_schema_tree();
    Logic_schema_tree(char*);
    ~Logic_schema_tree();
    bool Output(bool*);
    void Delete_tree(Node *);
    void Linking(char**,int);
    void Truth_table(char**,int&);
};

Logic_schema_tree::Logic_schema_tree()
{
    Node *root_;
    root_ = new Node;
    this->root = root_;
};

Logic_schema_tree::Logic_schema_tree(char *DNF)//достаем все коньюнкции и отправляем для формирования дерева  
{
    int len,i,j=0,k,p;
    bool flag=0;
    char **Dis = new char*[10];
    for (int z = 0; z < 10; z++) {
        Dis[z] = new char[10];
    }

    Node *temp = NULL;
    int Q_of_dis=0;
    int Q_of_con=0;
    len = strlen(DNF);
    for (int i = 0; i < len; i++) {
        if (DNF[i] == '|')
            Q_of_dis++;
    }
    temp = new Node;
    root = temp;
    while (!flag) {
        for (i = len-1; i >= 0; i--) {
            if (DNF[i] == '|')
                break;
        }
        if (i <= 0)
            flag = 1;
        i++;
        for (k = i, p = 0; k < len; p++) {
            if (DNF[i + p] != '&') {
                Dis[j][k - i] = DNF[i + p];
                k++;
            }
        }
        Dis[j][k - i] = 0;
        //std::cout << Dis[j] << std::endl;
        j++;
        if (i != 0) {
            DNF[i - 1] = 0;
            len = strlen(DNF);
        }
    }
    Linking(Dis, j);//дерево строит
    for (int z = 0; z < 10; z++) {
        delete[]Dis[z];
    }
    delete[]Dis;
};

Logic_schema_tree::~Logic_schema_tree()
{
    Delete_tree(root);
};

void Logic_schema_tree::Delete_tree(Node *p)
{

    for (int i = 0; i < p->childs.size(); i++) {
        Delete_tree(p->childs[i]);
    }
    delete p;
};

void Logic_schema_tree::Linking(char** temp, int n)
{
    int len = 0;
    for (int i = 0; i < n; i++) {
        len = 0;
        while (temp[i][len] != 0)
            len++;
        //сортировка символов
        for (int j = 0; j < len; j++) {
            for (int k = 0; k < len - j - 1; k++) {
                if (temp[i][k] > temp[i][k + 1]) {
                    char t = temp[i][k + 1];
                    temp[i][k + 1] = temp[i][k];
                    temp[i][k] = t;
                }
            }
        }
    }
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n - j - 1; k++) {
                int s=0;
                while ((temp[k + 1][s] == temp[k][s]) && (temp[k][s]!='\0'))
                    s++;
                if ((temp[k][s] > temp[k + 1][s]) /*||(temp[k+1][s]==0)) {
                    char *t = temp[k+1];
                    temp[k + 1] = temp[k];
                    temp[k] = t;
                }
            }
        }
        //---выше стортировка строк
        char actual = 65, next=255;//пытаемся пройтись по всем аргументам и пытаемся разбить нашу функцию на подмножество коньюнкций по какому то аргументу
        int *exists = new int[n + 1];
        exists[0] = -1;
        int l = 0;
        for (actual = 65; actual < 255; actual = next) {
            next = 255;
            exists[0] = -1;
            for (int k = 0; k < n; k++) {
                int s = 0;
                while ((temp[k][s] < actual) && (temp[k][s] != '\0'))
                    s++;
                if (temp[k][s] == actual) {
                    exists[l] = k;
                    exists[l + 1] = -1;
                    l++;
                    if ((temp[k][s + 1] != '\0') && (temp[k][s + 1] < next)) {
                        next = temp[k][s + 1];
                    }
                }
                else {
                    if ((temp[k][s] != '\0') && (temp[k][s] < next)) {
                        next = temp[k][s];
                    }
                }

            }
            if (exists[0] != -1) {
                Node* Result = new Node;
                Result->arguments = new char[2];
                Result->arguments[0] = actual;
                Result->coordinates = new int[l + 1];
                for (int i = 0; i <= l; i++) {
                    Result->coordinates[i] = exists[i];
                }
                Result->parent = root;
                root->childs.push_back(Result);
            }
        }
        delete[]exists;
        for (int i = 0; i < root->childs.size(); i++) {
            root->childs[i]->Treegrowing(temp, n, root->childs[i]);
        }
            /*Нам известены номер строк в которых есть нужные аргументы
             нужно создать узел Node который содержит все этистрочки
             написать как разбивать массив строк по аргументам
             Разбиваем по арументам
             будет рекурентная функция которая идет по npde пок не кончатся аргументы
             ?сжатия возможно ли, если да, то как?

}

void Logic_schema_tree::Truth_table(char**table, int&n) {
    root->Get_truth_table(table, n);
}
*/

//Функция которая сокращает интервалы (Подается набор интервалов)
std::vector<char*> table_compressor(std::vector<char*> Result) {
    bool different_intervals, same_intrevals, smaller, is_compressible;
    int coordinate = 256, coordinate_star = 256, coordinate_minus = 256;
    for (int i = 0; i < Result.size(); i++) {//по всем строчкам
        for (int k = i + 1; k < Result.size(); k++) {//по последующим
            different_intervals = false;
            same_intrevals = true;
            smaller = false;
            is_compressible = false;
            coordinate = 256;
            coordinate_star = 256;
            coordinate_minus = 256;
            for (int p = 0; p < 256; p++) {//по всем символам
                if (Result[i][p] != Result[k][p]) {
                    if (Result[i][p] == '*' || Result[k][p] == '*') {//разные интервалы *10
                        if (Result[i][p] == '-' || Result[k][p] == '-') {//-10
                            smaller = true;
                            if (coordinate_star == 256) {
                                coordinate_star = p;
                            }
                            else if (Result[i][coordinate_star] != Result[i][p]) {
                                different_intervals = true;
                                same_intrevals = false;
                                smaller = false;
                                break;
                            }
                        }
                        else {
                            different_intervals = true;
                            same_intrevals = false;
                            smaller = false;
                            break;
                        }
                    }
                    else if (Result[i][p] == '-' || Result[k][p] == '-') {//-10
                        smaller = true;
                        if (coordinate_minus == 256) {
                            coordinate_minus = p;
                        }
                        else if (Result[i][coordinate_minus] != Result[i][p]) {
                            different_intervals = true;
                            same_intrevals = false;
                            smaller = false;
                            break;
                        }
                        if(is_compressible){
                            different_intervals = true;
                            same_intrevals = false;
                            smaller = false;
                            break;
                        }
                    }
                    else {
                        if (smaller) {
                            different_intervals = true;
                            same_intrevals = false;
                            smaller = false;
                            break;
                        }
                        if (coordinate != 256) {
                            different_intervals = true;
                            same_intrevals = false;
                            smaller = false;
                            is_compressible = false;
                            break;
                        }
                        coordinate = p;
                        is_compressible = true;
                    }
                }
            }
            if (different_intervals) {
                continue;
            }
            if (smaller) {
                if (coordinate_star == 256) {
                    if (Result[i][coordinate_minus] != '-') {
                        delete[]Result[i];
                        Result.erase(Result.begin() + i);
                        i--;
                        break;
                    }
                    else {
                        delete[]Result[k];
                        Result.erase(Result.begin() + k);
                        k--;
                        continue;
                    }
                }
                else {
                    if (Result[i][coordinate_star] != '-') {
                        delete[]Result[i];
                        Result.erase(Result.begin() + i);
                        i--;
                        break;
                    }
                    else {
                        delete[]Result[k];
                        Result.erase(Result.begin() + k);
                        k--;
                    }
                }
            }
            if (is_compressible) {
                delete[]Result[k];
                Result.erase(Result.begin() + k);
                Result[i][coordinate] = '-';
                Result.push_back(Result[i]);
                Result.erase(Result.begin() + i);
                i--;
                break;
            }
            else {
                delete[]Result[k];
                Result.erase(Result.begin() + k);
                k--;
            }
        }
    }
    return Result;
};
// функция которая удаляется повторяющие элементы
std::vector<char*> table_of_unique(std::vector<char*> Result) {
    bool same_intrevals;
    int coordinate = 256, coordinate_star = 256, coordinate_minus = 256;
    for (int i = 0; i < Result.size(); i++) {//по всем строчкам
        for (int k = i + 1; k < Result.size(); k++) {//по последующим
            same_intrevals = true;
            coordinate = 256;
            coordinate_star = 256;
            coordinate_minus = 256;
            for (int p = 0; p < 256; p++) {//по всем символам
                if (Result[i][p] != Result[k][p]) {
                    if (Result[i][p] == '*' || Result[k][p] == '*') {//разные интервалы *10
                        if (Result[i][p] == '-' || Result[k][p] == '-') {//-10
                            if (coordinate_star == 256) {//запомнили координату *- и дальше смотрим не меняются  они местами
                                coordinate_star = p;
                            }
                            else if (Result[i][coordinate_star] != Result[i][p]) {
                                //same_intrevals = false;
                                //break;
                            }
                        }
                        else {
                            same_intrevals = false;
                            break;
                        }
                    }
                    else if (Result[i][p] == '-' || Result[k][p] == '-') {//-10
                        same_intrevals = false;
                        break;
                    }
                    else {
                        same_intrevals = false;
                        break;
                    }
                }
            }
            if (same_intrevals){
                delete[]Result[k];
                Result.erase(Result.begin() + k);
                k--;
            }
        }
    }
    return Result;
};
// функция получения таблицы истинности из днф
std::vector<char*> table_true(const char* DNF_input, bool compress = true) {
    {
        int len, i, j = 0, k, p;
        bool flag = 0;
        char **Dis = new char*[10];
        std::string DNF(DNF_input);
        for (int z = 0; z < 10; z++) {
            Dis[z] = new char[10];
        }

        int Q_of_dis = 0;
        int Q_of_con = 0;
        len = DNF.size();
        for (int i = 0; i < len; i++) {
            if (DNF[i] == '|')
                Q_of_dis++;
        }

        while (!flag) {
            for (i = len - 1; i >= 0; i--) {
                if (DNF[i] == '|')
                    break;
            }
            if (i <= 0)
                flag = 1;
            i++;
            for (k = i, p = 0; i+p<len && k < len; p++) {
                if (DNF[i + p] != '&') {
                    Dis[j][k - i] = DNF[i + p];
                    k++;
                }
            }
            Dis[j][k - i] = 0;
            j++;
            if (i != 0) {
                //DNF[i - 1] = 0;
                DNF.resize(i-1);
                len = DNF.size();
            }
        }
        std::vector<char*> Result;
        for (int i = 0; i < j; i++) {
            char* interval = new char[257];
            for (int k = 0; k < 256; k++) {
                interval[k] = '-';
            }
            interval[256] = '\0';
            for (int k = 0; Dis[i][k] != '\0'; k++) {
                if (Dis[i][k] == '-') {
                    if (interval[Dis[i][k + 1]] == '-') {
                        interval[Dis[i][k + 1]] = '0';
                    }
                    else {
                        delete[] interval;
                        interval = NULL;
                        break;
                    }
                    k++;
                    continue;
                }
                if (interval[Dis[i][k]] == '-') {
                    interval[Dis[i][k]] = '1';
                }
                else {
                    delete[] interval;
                    interval = NULL;
                    break;
                }
            }
            if (interval == NULL) {
                continue;
            }
            Result.push_back(interval);
        }
        for (int z = 0; z < 10; z++) {
            delete[]Dis[z];
        }
        delete[]Dis;
        if(compress){
            return table_compressor(Result);
        }
        return table_of_unique(Result);
    };

}
//функция таблица ложности для построения кнф
std::vector<char*>table_false(std::vector<char*>table_true, bool compress = true) {
    std::vector<char*>table_false;
    char* ptr = new char[257], *stars=new char[256];
    ptr[256] = '\0';
    for (int i = 0; i < 256; i++) {
        ptr[i] = '-';
        stars[i] = '*';
    }
    table_false.push_back(ptr);
    bool different;
    std::vector<unsigned char> coordinate_same, coordinate_minus;
    for (int i = 0; i < table_true.size(); i++) {
        for (int j = 0; j < table_false.size(); j++) {
            different = false;
            coordinate_same.clear();
            coordinate_minus.clear();
            for (int z = 0; z < 256; z++) {
                if (table_true[i][z] != '*') {
                    stars[z] = '_';
                    if (table_true[i][z]!='-') {
                        if (table_false[j][z] != '-') {
                            if (table_true[i][z] != table_false[j][z]) {
                                different = true;
                                break;
                            }
                            else {
                                coordinate_same.push_back(z);
                            }
                        }
                        else {
                            coordinate_minus.push_back(z);
                        }

                    }
                }
            }
            if (different) {
                continue;
            }
            if (coordinate_minus.size() > 1) {
                for (int k = 0; k < coordinate_minus.size(); k++) {
                    int pereborA2 = 0;
                    int count=2<<(coordinate_minus.size()-2);
                    for (int m = 0; m < count; m++) {
                        ptr = new char[257];
                        ptr[256] = '\0';
                        for (int k = 0; k < 256; k++) {
                            ptr[k] = table_false[j][k];
                        }
                        for (int k = 0; k < coordinate_same.size(); k++) {
                            ptr[coordinate_same[k]] = table_true[i][coordinate_same[k]];
                        }

                        if (table_true[i][coordinate_minus[k]] == '1') {
                            ptr[coordinate_minus[k]] = '0';
                        }
                        else {
                            ptr[coordinate_minus[k]] = '1';
                        }

                        int needed_bit = 1;
                        for (int n = 0; n < k; n++) {
                            if (needed_bit & pereborA2) {
                                ptr[coordinate_minus[n]] = '1';
                            }
                            else {
                                ptr[coordinate_minus[n]] = '0';
                            }
                            needed_bit <<= 1;
                        }
                        for (int n = k + 1; n < coordinate_minus.size(); n++) {
                            if (needed_bit & pereborA2) {
                                ptr[coordinate_minus[n]] = '1';
                            }
                            else {
                                ptr[coordinate_minus[n]] = '0';
                            }
                            needed_bit <<= 1;
                        }
                        pereborA2++;
                        table_false.insert(table_false.begin(),ptr);
                        j++;
                    }
                }
                delete[]table_false[j];
                table_false.erase(table_false.begin() + j);
                j-=coordinate_minus.size()*2;
            }
            else if(coordinate_minus.size()==1) {
                ptr = new char[257];
                ptr[256] = '\0';
                for (int k = 0; k < 256; k++) {
                    ptr[k] = table_false[j][k];
                }
                for (int k = 0; k < coordinate_same.size(); k++) {
                    ptr[coordinate_same[k]] = table_true[i][coordinate_same[k]];
                }
                if (table_true[i][coordinate_minus[0]] == '1') {
                    ptr[coordinate_minus[0]] = '0';
                }
                else {
                    ptr[coordinate_minus[0]] = '1';
                }
                delete[]table_false[j];
                table_false.erase(table_false.begin() + j);
                table_false.insert(table_false.begin(), ptr);
            }
            else {
                delete[]table_false[j];
                table_false.erase(table_false.begin() + j);
                j--;
            }
        }
    }
    for (int i = 0; i < table_false.size(); i++) {
        for (int j = 0; j < 256; j++) {
            if (stars[j] == '*') {
                table_false[i][j] = '*';
            }
        }
    }
    if (compress) {
        return table_compressor(table_false);
    }
    return table_of_unique(table_false);
};
//функция построения кнф
char * KNF_maker(std::vector<char*>table_true) {
    std::vector<char*>table_false1=table_false(table_true);
    if (table_false1.size() == 0) {
        return NULL;
    }
    char* KNF_Result = new char[250];
    KNF_Result[0] = '(';
    int a = 1;
    bool first_time = true;
    for (int i = 0; i < 256; i++) {
        if (table_false1[0][i] != '*' && table_false1[0][i] != '-') {
            if (!first_time) {
                KNF_Result[a] = '|';
                a++;
            }
            else {
                first_time = false;
            }
            if (table_false1[0][i] == '1') {
                KNF_Result[a] = '-';
                KNF_Result[a + 1] = i;
                a += 2;
            }
            else {
                KNF_Result[a] = i;
                a++;
            }
        }
    }
    KNF_Result[a] = ')';
    a++;
    for (int q = 1; q < table_false1.size(); q++) {
        KNF_Result[a] = '&';
        KNF_Result[a + 1] = '(';
        a += 2;
        bool first_time = true;
        for (int i = 0; i < 256; i++) {
            if (table_false1[q][i] != '*' && table_false1[q][i] != '-') {
                if (!first_time) {
                    KNF_Result[a] = '|';
                    a++;
                }
                else {
                    first_time = false;
                }
                if (table_false1[q][i] == '1') {
                    KNF_Result[a] = '-';
                    KNF_Result[a + 1] = i;
                    a += 2;
                }
                else {
                    KNF_Result[a] = i;
                    a++;
                }
            }
        }
        KNF_Result[a] = ')';
        a++;
    }
    KNF_Result[a] = 0;
    return KNF_Result;
};
//функция построения днф
char * DNF_maker(std::vector<char*>table_true) {

    if (table_true.size() == 0) {
        return NULL;
    }
    char* DNF_Result = new char[250];
    //DNF_Result[0] = '(';
    int a = 0;
    bool first_time = true;
    for (int i = 0; i < 256; i++) {
        if (table_true[0][i] != '*' && table_true[0][i] != '-') {
            if (!first_time) {
                DNF_Result[a] = '&';
                a++;
            }
            else {
                first_time = false;
            }
            if (table_true[0][i] == '0') {
                DNF_Result[a] = '-';
                DNF_Result[a + 1] = i;
                a += 2;
            }
            else {
                DNF_Result[a] = i;
                a++;
            }
        }
    }
    //DNF_Result[a] = ')';
    //a++;
    for (int q = 1; q < table_true.size(); q++) {
        DNF_Result[a] = '|';
        //DNF_Result[a + 1] = '(';
        a += 1;
        bool first_time = true;
        for (int i = 0; i < 256; i++) {
            if (table_true[q][i] != '*' && table_true[q][i] != '-') {
                if (!first_time) {
                    DNF_Result[a] = '&';
                    a++;
                }
                else {
                    first_time = false;
                }
                if (table_true[q][i] == '0') {
                    DNF_Result[a] = '-';
                    DNF_Result[a + 1] = i;
                    a += 2;
                }
                else {
                    DNF_Result[a] = i;
                    a++;
                }
            }
        }
        //DNF_Result[a] = ')';
        //a++;
    }
    DNF_Result[a] = 0;
    return DNF_Result;
}

//Функия для построения  тблицы истинности из КНФ
std::vector<char*> table_true_from_KNF(const char*KNF_input, bool compress = true) {
    int len, i, j = 0, k, p;
    bool flag = 0;
   std::string con[10];
    for (int z = 0; z < 10; z++) {
        con[z].resize(10);
    }
    std::string KNF(KNF_input);

    int Q_of_dis = 0;
    int Q_of_con = 0;
    len = KNF.size();
    for (int i = 0; i < len; i++) {
        if (KNF[i] == '|')
            Q_of_con++;
    }

    while (!flag) {
        for (i = len - 1; i >= 0; i--) {
            if (KNF[i] == '&')
                break;
        }
        if (i <= 0)
            flag = 1;
        i++;
        for (k = i, p = 0;i+p<len; p++) {
            if (KNF[i + p] != '|' && KNF[i + p] != '(' &&KNF[i + p] != ')') {
                con[j][k - i] = KNF[i + p];
                k++;
            }
        }
        con[j].resize(k-i);
        j++;
        if (i != 0) {
            KNF.resize(i - 1);
            len = KNF.size();
        }
    }
    std::vector<char*> Result;
    for (int i = 0; i < j; i++) {
        char* interval = new char[257];
        for (int k = 0; k < 256; k++) {
            interval[k] = '*';
        }
        interval[256] = '\0';
        for (int k = 0; con[i][k] != '\0'; k++) {
            if (con[i][k] == '-') {
                if (interval[con[i][k + 1]] == '*') {
                    interval[con[i][k + 1]] = '1';
                }
                else {
                    delete[] interval;
                    interval = NULL;
                    break;
                }
                k++;
                continue;
            }
            if (interval[con[i][k]] == '*') {
                interval[con[i][k]] = '0';
            }
            else {
                delete[] interval;
                interval = NULL;
                break;
            }
        }
        if (interval == NULL) {
            continue;
        }
        Result.push_back(interval);
    }
   // for (int z = 0; z < 10; z++) {
     //   delete[]con[z];
    //}
    //delete[]con;
    return table_false(table_compressor(Result), compress);
};

//представления бинарной функции
bool Binary_function(char function, bool first_argument, bool second_argument = 0)
{
    if (function = '-')
        return first_argument ^ 1;
    if (function=='|')
        return first_argument || second_argument;
    return first_argument && second_argument;
};
//функция проверки принадлежит ли вектор како-нибудь интервалу из таблицы истинности
bool vector_check(int vector, const char* arguments, std::vector<char*> table_true, int count)
{
    bool be_interval=false;
    int count_rang=1<<(count-1);
    for (int i=0; i<table_true.size(); i++){
        count_rang=1<<(count-1);
        be_interval=true;
        for(int j=0; j<256; j++){
            if(arguments[j]=='*'){
                if(table_true[i][j]=='-'){
                    count_rang>>=1;
                    continue;
                }
                if((bool)(vector&count_rang)==(bool)(table_true[i][j]=='1')){
                    count_rang>>=1;
                    continue;
                }
                else {
                    be_interval=false;
                    break;
                }
            }
        }
        if(be_interval){
            return  true;
        }
    }
    return false;
};
//Таблица истинности для вектора
std::vector<char*> table_true_from_vector(const char* vector, bool compress = true) {
    {
        int len, lenning, count=0;
        len = strlen(vector);
        lenning= 1;
        while(!(lenning&len)){
            lenning<<=1;
            count++;
        }
        std::vector<char*> Result;
        for (int i = 0; i < len; i++) {
            if(vector[i]=='1') {
                char* interval = new char[257];
                for (int k = 0; k < 256; k++) {
                    interval[k] = '-';
                }
                interval[256] = '\0';
                int ptr=len/2;
                for(int j=0; j<count; j++){
                    if(ptr&i){
                        interval[97+j]='1';

                    }
                    else{
                        interval[97+j]='0';
                    }
                    ptr>>=1;
                }
                Result.push_back(interval);
            }
        }
        if(compress){
            return table_compressor(Result);
        }
        return table_of_unique(Result);
    };
}
//Для  построения полинома Жегалкина
char* Polinom_maker(std::vector <char*> table, const char* arguments, int count){
    std::vector <bool*> pascal_triangle;
    pascal_triangle.resize(pow(2,count));
    pascal_triangle[0]=new bool[int (pow(2,count))];
    for(int i=0; i<pow(2,count);i++){
        pascal_triangle[0][i]=vector_check(i,arguments,table,count);
    }
    for(int i=1; i<pow(2,count); i++){
        pascal_triangle[i]=new bool[int (pow(2,count)-i)];
        for(int j=0; j<(pow(2,count)-i); j++){
            pascal_triangle[i][j]=pascal_triangle[i-1][j]^pascal_triangle[i-1][j+1];
        }
    }
    char* polinom=new char[256];
    int pol=0;
    if(pascal_triangle[0][0]){
        polinom[pol]='1';
        polinom[pol+1]='+';
        pol+=2;
    }
    for(int i=1; i<pow(2,count); i++){
        unsigned char shag=0;
        int ptr=1<<(count-1);
        if(pascal_triangle[i][0]){
            for(int j=0; j<count; j++){
                while(arguments[shag]!='*'){
                    shag++;
                }
                if(i&ptr){
                    polinom[pol]=shag;
                    polinom[pol+1]='&';
                    pol+=2;
                }
                shag++;
                ptr>>=1;
            }
            polinom[pol-1]='+';
        }
    }
    polinom[pol-1]='\0';
    return polinom;
}
// Теоремы поста
char* Table_post(std::vector <char*> table_true, const char* arguments, int count){
    char* array_simbol=new char [6];
    array_simbol[5]='\0';
    if(vector_check(0, arguments, table_true, count)){
        array_simbol[0]='-';//функция не принадлежит Т0
    }
    else {
        array_simbol[0]='+';
    }
    if(vector_check(~0, arguments, table_true, count)){
        array_simbol[1]='+';//функция принадлежит Т1
    }
    else {
        array_simbol[1]='-';
    }
    bool previous=vector_check(0, arguments, table_true, count);
    array_simbol[2]='+';//функция принадлежит М
    for(int i=1; i<pow(2,count); i++){
        bool current=vector_check(i, arguments, table_true, count);
        if(previous==true & current==false){
            array_simbol[2]='-';
            break;
        }
    }
    std::vector <bool*> pascal_triangle;
    pascal_triangle.resize(pow(2,count));
    pascal_triangle[0]=new bool[int (pow(2,count))];
    for(int i=0; i<pow(2,count);i++){
        pascal_triangle[0][i]=vector_check(i,arguments,table_true,count);
    }
    for(int i=1; i<pow(2,count); i++){
        pascal_triangle[i]=new bool[int (pow(2,count)-i)];
        for(int j=0; j<(pow(2,count)-i); j++){
            pascal_triangle[i][j]=pascal_triangle[i-1][j]^pascal_triangle[i-1][j+1];
        }
    }
    array_simbol[3]='+';//функция принадлежит L
    for(int i=0; i<pow(2,count); i++){
        if(pascal_triangle[0][i]==true){
            if(i&(i-1)!=0){
                array_simbol[3]='-';
                break;
            }
        }
    }
    array_simbol[4]='+';//функция принадлежит S
    for(int i=0; i<pow(2,count)/2; i++){
        bool from_start=vector_check(i, arguments, table_true, count);
        bool from_end=vector_check(pow(2,count)-1-i, arguments, table_true, count);
        if(from_start==from_end){
            array_simbol[4]='-';
            break;
        }
    }
    return array_simbol;
}

QString Karno (std::vector <char*> table, const char *arguments, int count){
    QString variable;
    int simbol_ptr=0;
    for(int i=0;i<256;i++){
        if(arguments[i]=='*'){
            variable+=(char)i;
        }
    }
    int up_count;
    int left_count;
    left_count=count/2;
    up_count=count-left_count;
    int table_itog_strok;
    int table_itog_stolb;
    table_itog_strok= up_count + pow (2, left_count)+1;
    table_itog_stolb= left_count + pow (2, up_count)+1;
    QString cell_size = "width = \"20\"";//размер ячейки
    QString cell_size_tr = "height = \"20\"";//размер ячейки
    std::vector<int> interval_chast_stolb((int)pow(2,up_count));
    std::vector<int> interval_chast_strok((int)pow(2,left_count));
    for(int i=0; i<pow(2,up_count);i++){
        interval_chast_stolb[i]=0;
    }
    for(int i=0;i<pow(2,left_count);i++){
        interval_chast_strok[i]=0;
    }
    QString Result= "<html><body><table style = \"table-layout: fixed;\" border = \"1\" width = \""+QString::number(table_itog_stolb*20)+"\" height = \""+QString::number(table_itog_strok*20)+"\" align = \"center\">";
    int save_stolb;
    save_stolb = pow(2,up_count);
    int partc_count=1;
    int kol_zakrachen;
    int bit_ptr=1<<(up_count+left_count);//указатель на нужный бит
    for(int i=0; i<up_count; i++){
        partc_count*=2;
        kol_zakrachen=save_stolb/partc_count;
        int flag=0;
        Result+="<tr "+cell_size_tr+">";
        for(int j=0;j<left_count;j++){
            Result+=" <td style = \"border:0;\" " + cell_size + "></td>";
        }
        bit_ptr>>=1;
        for(int j=0; j<partc_count; j++){
            QString granica;
            if(flag==1){
                granica = " style=\"border-color: black; border-bottom:0; border-left:0; border-right:0;\"";
            }
            else{
                granica= " style=\"border:0;\"";
            }
            for(int z=0;z<kol_zakrachen;z++){
                if (flag==1) {
                    interval_chast_stolb[j*kol_zakrachen+z]|=bit_ptr;
                }
                Result+="<td"+granica+' '+cell_size+"></td>";
            }
            flag=((flag+(j+1)%2)%2);
        }
        Result+=" <td style = \"border:0;\" "+cell_size+">"+variable[simbol_ptr]+"</td></tr>";
        simbol_ptr++;
    }
    std::vector<std::vector<bool>> Bul_matrix_linia(left_count);
    for (unsigned int i = 0; i < Bul_matrix_linia.size(); i++) {
        Bul_matrix_linia[i].resize((int)pow(2,left_count));
    }
    save_stolb = pow(2,left_count);
    partc_count=1;
    for(int i=0; i<left_count; i++){
        partc_count*=2;
        kol_zakrachen=save_stolb/partc_count;
        int flag=0;

        for(int j=0; j<partc_count; j++){
            for(int z=0;z<kol_zakrachen;z++){
                Bul_matrix_linia[i][j*kol_zakrachen+z]=flag;
            }
            flag=((flag+(j+1)%2)%2);//нужна для того чтоб понять где рисовать линию а нле нет
        }
    }
    for(int i=0; i<pow(2,left_count); i++){//цикл заполнение левой части и самой таблицы
        Result+="<tr "+cell_size_tr+">";
        bit_ptr=1<<(left_count-1);
        for(int j=0; j<left_count; j++){
            QString granica;
            if(Bul_matrix_linia[j][i]==true){
                granica = " style=\"border-color: black; border-bottom:0; border-top:0; border-right:0;\"";
                interval_chast_strok[i]|=bit_ptr;
            }
            else{
                granica= " style=\"border:0;\"";
            }
            Result+="<td"+granica+' '+cell_size+"></td>";
            bit_ptr>>=1;
        }
        for(int j=0;j<pow(2,up_count);j++){
            Result+="<td style=\"border-color: black; text-align: center; vertical-align: middle;\" "+cell_size+">";
            if(vector_check(interval_chast_stolb[j]|interval_chast_strok[i],arguments,table,count)){
                Result+=QString::fromUtf8(u8"♥");
            }
            Result+="</td>";
        }
        Result+="<td style=\"border:0;\" "+cell_size+"></td></tr>";
    }
    Result+="<tr "+cell_size_tr+">";
    for(int i=0;i<left_count;i++){
        Result+=" <td style = \"border:0;\" "+cell_size+" >"+variable[simbol_ptr]+"</td>";
        simbol_ptr++;
    }
    for(int j=0;j<pow(2,up_count);j++){
        Result+="<td style=\"border:0;\" "+cell_size+"></td>";
    }
    Result+="<td style=\"border:0;\" "+cell_size+"></td></tr></table></body></html>";
    //std::cout << Result.toStdString() << '\n';
    return Result;
}


/*int main()
{
    bool t;
    char *DNF;
    DNF = new char[50];
    std::cout << "Input DNF:" << std::endl;
    std::cin >> DNF;
    char arguments[256];
    for (int i = 0; i < 256; i++) {
        arguments[i] = '_';
    }
    for (int i = 0; i < strlen(DNF); i++) {
        if (DNF[i] >= 65 && DNF[i] <= 90 || DNF[i] >= 97 && DNF[i] <= 122) {
            arguments[DNF[i]] = '*';
        }
    }
    std::cout << std::endl;
    t = Parsing(DNF);
    if (t == 0) {
        std::cout << "Incorrect inputed string" << std::endl;
        system("pause");
        return 0;
    }
    //Logic_schema_tree Tree(DNF);
    std::vector<char*>table = table_true(DNF);
    std::cout << '\n';
    for (int j = 0; j < 256; j++) {
        if (arguments[j] == '*') {
            std::cout << (unsigned char)j;
        }
    }
    std::cout << '\n';
    for (int i = 0; i < table.size(); i++) {
        for (int j = 0; j < 256; j++) {
            if (arguments[j] == '*') {
                std::cout << table[i][j];
            }
        }
        std::cout << '\n';
    }

    std::vector<char*>table_2 = table_false(table);
    std::cout << '\n';
    for (int j = 0; j < 256; j++) {
        if (arguments[j] == '*') {
            std::cout << (unsigned char)j;
        }
    }
    std::cout << '\n';
    for (int i = 0; i < table_2.size(); i++) {
        for (int j = 0; j < 256; j++) {
            if (arguments[j] == '*') {
                std::cout << table_2[i][j];
            }
        }
        std::cout << '\n';
    }
    std::cout << '\n';
    std::cout << KNF_maker(table) << '\n';
    table = table_true_from_KNF(KNF_maker(table));
    std::cout << '\n';
    for (int j = 0; j < 256; j++) {
        if (arguments[j] == '*') {
            std::cout << (unsigned char)j;
        }
    }
    std::cout << '\n';
    for (int i = 0; i < table.size(); i++) {
        for (int j = 0; j < 256; j++) {
            if (arguments[j] == '*') {
                std::cout << table[i][j];
            }
        }
        std::cout << '\n';
    }
    delete[] DNF;
    system("pause");
    return 0;
}*/


