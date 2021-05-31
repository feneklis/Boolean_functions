#ifndef GRAPH_H
#define GRAPH_H
#include <string>
#include <list>
#include <vector>

struct Vertex;
struct Connection{
  int direction;
  int type;
  Vertex* vertex;
};
struct Vertex{
Vertex* prev, *next;
std::vector<Connection> vertexes;
std::string data;
Vertex (Vertex* prev_input = NULL, Vertex* next_input = NULL, std::string data_input = "", std::vector<Connection> vertexes_input = std::vector<Connection> ());
};



class Graph{
private:
std:: list <Vertex*> vertexes;
public:
Graph();
Graph(std::vector <char*> table, const char *arguments, int count);
void Add_vertex(Vertex*);
void Remove_vertex(Vertex*);
void Connect_vertex(Vertex*,Vertex*, int Direction=0, int Type=0);
Vertex* Get_vertex(int);
Vertex* Vetka(std::vector <char*> table, const char *arguments, int count);
bool Pervoe_Pravilo_Ydalenia(Vertex*);
bool Vtoroe_Ptavilo_Obedinenie(Vertex*,Vertex*);
void Sokrachatel();
void Rekurs_1(std::vector<Vertex*>);
void Rekurs_2(std::vector<Vertex*>);
void Rekurs_2_temp(Vertex* vertex);
};


#endif
