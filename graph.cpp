#include "graph.h"
#include <algorithm>

Vertex:: Vertex (Vertex* prev_input, Vertex* next_input , std::string data_input, std::vector<Connection> vertexes_input){
prev=prev_input;
next=next_input;
data=data_input;
vertexes=vertexes_input;
}

Graph::Graph(){
}

void Graph::Add_vertex(Vertex* vertex){
vertexes.push_back(vertex);
}

void Graph:: Remove_vertex(Vertex* vertex ){
    for(auto ptr=vertexes.begin(); ptr!=vertexes.end();ptr++){
        if(*ptr==vertex){
            ptr=vertexes.erase(ptr);
            ptr--;
        }
        else {
            for(int i=0; i<(*ptr)->vertexes.size();i++){
                if((*ptr)->vertexes[i].vertex==vertex){
                    (*ptr)->vertexes.erase( (*ptr)->vertexes.begin()+i);
                    i--;
                }
            }
        }
    }
    delete vertex;
}


void Graph:: Connect_vertex(Vertex* vertex1,Vertex* vertex2, int Direction, int Type){
    int i;

    for (i=0; i<vertex1->vertexes.size();i++){
        if(vertex1->vertexes[i].vertex==vertex2){
            break;
        }
    }
    if(i >=vertex1->vertexes.size()){
        vertex1->vertexes.push_back({Direction, Type, vertex2});
    }
    for (i=0; i<vertex2->vertexes.size();i++){
        if(vertex2->vertexes[i].vertex==vertex1){
            break;
        }
    }
    if(i >=vertex2->vertexes.size()){
        if(Direction==2){
            Direction=1;
        }
        else if(Direction==1){
            Direction=2;
        }
        vertex2->vertexes.push_back({Direction, Type, vertex1});
    }
}
Vertex*  Graph::Get_vertex(int index){
    auto ptr=vertexes.begin();
    for(int i=0;i<index;i++){
        ptr++;
    }
    return *ptr;
}

Graph:: Graph(std::vector <char*> table, const char *arguments, int count){
    Vertex* terminal0=new Vertex(), *terminal1=new Vertex();
    terminal0->data.push_back('0');
    terminal1->data.push_back('1');
    vertexes.push_back(terminal0);
    vertexes.push_back(terminal1);
    Vetka(table, arguments, count);
}

Vertex* Graph::Vetka(std::vector <char*> table, const char *arguments, int count){
    if(count==0){
        if(table.empty()){
            return *vertexes.begin();
        }
        else{
            return *(std::next(vertexes.begin(), 1));
        }
    }
    int index=0;
    while(arguments[index]!='*'){
        index++;
    }
    std::vector<char*> table1;
    std::vector<char*> table0;
    for(int i=0;i<table.size();i++){
        if(table[i][index]=='1'){
            table1.push_back(table[i]);
        }
        else if(table[i][index]=='0'){
            table0.push_back(table[i]);
        }
        else{
            table1.push_back(table[i]);
             table0.push_back(table[i]);
        }
    }
    char arguments2[256];
    for(int i=0;i<256;i++){
         arguments2[i]=arguments[i];
    }
    arguments2[index]='_';
    Vertex* vertex=new Vertex();
    vertex->data.push_back(index);
    vertexes.push_back(vertex);
    Connect_vertex(vertex,Vetka(table0, arguments2,count-1),1,1);
    Connect_vertex(vertex,Vetka(table1, arguments2,count-1),1);
    return vertex;
}

bool Graph:: Pervoe_Pravilo_Ydalenia(Vertex* ToDelete){
    Vertex* childs[2]={nullptr, nullptr};
    for(int i=0,j=0; i<ToDelete->vertexes.size(); i++){
        if(ToDelete->vertexes[i].direction==1){
            childs[j]=ToDelete->vertexes[i].vertex;
            j++;
        }
    }
    if(childs[1]!=nullptr && childs[0]!=childs[1]||childs[0]==nullptr){
        return false;
    }
    int k=0;
    for(int i=0;i<ToDelete->vertexes.size(); i++){
        if(ToDelete->vertexes[i].direction==2){
            Connection* ptr=&ToDelete->vertexes[i].vertex->vertexes[0];
            int j=1;
            while(ptr->vertex!=ToDelete){
                ptr=&ToDelete->vertexes[i].vertex->vertexes[j];
                j++;
            }
            ptr->vertex=childs[0];
        }
        else{

        }
    }
    int m=0;
    while(m<childs[0]->vertexes.size()&& childs[0]->vertexes[m].direction!=2){
        m++;
    }
    while(k<ToDelete->vertexes.size()&& ToDelete->vertexes[k].direction!=2){
        k++;
    }
    if(k<ToDelete->vertexes.size()){
        childs[0]->vertexes[m]=ToDelete->vertexes[k];
        k++;
         while(k<ToDelete->vertexes.size()){
             while(k<ToDelete->vertexes.size()&& ToDelete->vertexes[k].direction!=2){
                 k++;
             }
             if(k<ToDelete->vertexes.size()){
                 childs[0]->vertexes.push_back(ToDelete->vertexes[k]);
                 k++;
             }
         }
    }
    Remove_vertex(ToDelete);
    return true;
}

bool Graph:: Vtoroe_Ptavilo_Obedinenie(Vertex* first,Vertex* second){
    if(first==second){
        return false;
    }
    if(first->data!=second->data){
        return false;
    }
    Vertex* firstchilds[2]={nullptr, nullptr};
    Vertex* secondchilds[2]={nullptr, nullptr};
    for(int i=0; i<first->vertexes.size(); i++){
        if(first->vertexes[i].direction==1){
            if(first->vertexes[i].type==0){
            firstchilds[0]=first->vertexes[i].vertex;
        }
            else {
                firstchilds[1]=first->vertexes[i].vertex;
            }
        }
    }
    for(int i=0; i<second->vertexes.size(); i++){
        if(second->vertexes[i].direction==1){
            if(second->vertexes[i].type==0){
            secondchilds[0]=second->vertexes[i].vertex;
        } else {
                secondchilds[1]=second->vertexes[i].vertex;
            }
        }
    }
    if(firstchilds[0]!=secondchilds[0] || firstchilds[1]!=secondchilds[1]){
        if(firstchilds[1]!=secondchilds[0] || firstchilds[0]!=secondchilds[1])
        return false;
    }
    for(int i=0;i<second->vertexes.size(); i++){
        if(second->vertexes[i].direction==2){
            Connection* ptr=&second->vertexes[i].vertex->vertexes[0];
            int j=1;
            while(ptr->vertex!=second){
                ptr=&second->vertexes[i].vertex->vertexes[j];
                j++;
            }
            ptr->vertex=first;
            for( j=0;j<first->vertexes.size(); j++){
                if(first->vertexes[j].vertex==second->vertexes[i].vertex){
                    break;
                }
            }
            if(j<first->vertexes.size()){
                continue;
            }
            else{
                first->vertexes.push_back(second->vertexes[i]);
            }
        }
        else{

        }
    }
    Remove_vertex(second);
    return true;
}
//сам сокращает BDD граф
void Graph:: Sokrachatel(){
    std::vector<Vertex*> start;
    std::list<Vertex*>::iterator ptr = vertexes.begin();
    start.push_back(*ptr);
    ptr++;
    start.push_back(*ptr);
    Rekurs_1(start);
   // Rekurs_2(start);
    Vertex* ptr_2= nullptr;
    int i=0;
    Vertex* iterator;
    while(ptr_2==nullptr){
        iterator=Get_vertex(i);
        int j=0;
        for(j=0;j<iterator->vertexes.size();j++){
            if(iterator->vertexes[j].direction==2){
                break;
            }
        }
        if(j==iterator->vertexes.size()){
            ptr_2=iterator;
        }
        else{
            i++;
        }
    }
    Rekurs_2_temp(ptr_2);
     Rekurs_1(start);
}
//пименение правило 1
void Graph:: Rekurs_1(std::vector<Vertex*> vertexes){
    std::vector<Vertex*> parents;
    for(int i=0; i<vertexes.size();i++){
        for(int j=0;j<vertexes[i]->vertexes.size();j++){
            if(vertexes[i]->vertexes[j].direction==2){
                if (std::find(parents.begin(), parents.end(), vertexes[i]->vertexes[j].vertex) == parents.end()) {
                    parents.push_back(vertexes[i]->vertexes[j].vertex);
                }
            }
        }
    }
    for(int i=0; i<vertexes.size();i++){
                if( Pervoe_Pravilo_Ydalenia(vertexes[i])){
                    vertexes.erase(vertexes.begin()+i);
                    i--;
                }
    }
    if(!parents.empty()){
        Rekurs_1(parents);
    }
}
//применение правило обьединения
void Graph:: Rekurs_2(std::vector<Vertex*>vertexes){
    for(int i=0; i<vertexes.size()-1;i++){
               if( Vtoroe_Ptavilo_Obedinenie(vertexes[i],vertexes[i+1])){
                   vertexes.erase(vertexes.begin()+i+1);
                   if(i>0){
                       i--;
                   }
                   for(int j=0; j<vertexes[i]->vertexes.size();j++){
                       if(vertexes[i]->vertexes[j].direction==2){
                           if(Pervoe_Pravilo_Ydalenia (vertexes[i]->vertexes[j].vertex)){
                               j--;
                           }
                       }
                   }
               }
    }
    std::vector<Vertex*> parents;
    for(int i=0; i<vertexes.size();i++){
        for(int j=0;j<vertexes[i]->vertexes.size();j++){
            if(vertexes[i]->vertexes[j].direction==2 && std::find(parents.begin(), parents.end(), vertexes[i]->vertexes[j].vertex)==parents.end()) {
                parents.push_back(vertexes[i]->vertexes[j].vertex);
            }

        }
    }
    if(!parents.empty()){
        Rekurs_2(parents);
    }

}
//тоже правило обьединения
void Graph:: Rekurs_2_temp(Vertex* vertex){
    Vertex* childs[2];
    if(vertex->data=="0" || vertex->data=="1"){
        return;
    }
    int j=0;
    for(int i=0; i<vertex->vertexes.size();i++){
        if(vertex->vertexes[i].direction==1){
            childs[j]=vertex->vertexes[i].vertex;
            j++;
        }
    }
    Rekurs_2_temp(childs[0]);
    Rekurs_2_temp(childs[1]);
    Vtoroe_Ptavilo_Obedinenie(childs[0],childs[1]);

}
