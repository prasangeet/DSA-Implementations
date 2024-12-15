#include <iostream>
#include <map>
#include <list>
#include <string>
#include <queue>

using namespace std;

class Object{};

class Decorator{
private: 
    map<string, Object*> attributes;
public:
    Object* get(const string& key){return attributes[key];}
    void set(const string& key, Object* value){attributes[key] = value;}
};

class Vertex: public Decorator{
public: 
    string element;
    list<class Edge*> incidentEdges;

    Vertex(string elem): element(elem){}

    string operator*(){
        return element;
    }
};

class Edge: public Decorator{
public:
    Vertex* u;
    Vertex* v;
    Edge(Vertex* u, Vertex* v): u(u), v(v){}
    Vertex* opposite(Vertex* vertex){
        return (vertex == u) ? v : u;
    }
};

class Graph{
public:
    list<Vertex*> vertices;
    list<Edge*> edges;

    Vertex* insertVertex(string element){
        Vertex* vertex = new Vertex(element);
        vertices.push_back(vertex);
        return vertex;
    }

    Edge* insertEdge(Vertex* u, Vertex* v){
        Edge* edge = new Edge(u, v);
        u->incidentEdges.push_back(edge);
        v->incidentEdges.push_back(edge);
        edges.push_back(edge);
        return edge;
    }
};

void BFS(Graph& G, Vertex* startVertex, Object* visited, Object* discovery, Object* cross, Object* unvisited){
    map<int, list<Vertex*>> levels;
    int level = 0;

    levels[level].push_back(startVertex);
    startVertex->set("status", visited);
    
    while (!levels[level].empty())
    {   
        levels[level + 1] = list<Vertex*> ();
        for(Vertex* v: levels[level]){
            cout<<"Visited "<<v->element<<"\n";
            for(Edge* e: v->incidentEdges){
                if(e->get("status") == unvisited){
                    Vertex* w = e->opposite(v);
                    if(w->get("status") == unvisited){
                        e->set("status", discovery);
                        w->set("status", visited);
                        levels[level + 1].push_back(w);
                    }
                    else{
                        e->set("status", cross);
                    }
                }
            }
        }
        ++level;
    }
}

int main(){
    Object* unvisited = new Object();
    Object* visited = new Object();
    Object* discovery = new Object();
    Object* cross = new Object();

    Graph G;
    Vertex* v1 = G.insertVertex("A");
    Vertex* v2 = G.insertVertex("B");
    Vertex* v3 = G.insertVertex("C");
    Vertex* v4 = G.insertVertex("D");

    G.insertEdge(v1, v2);
    G.insertEdge(v2, v3);
    G.insertEdge(v3, v4);
    G.insertEdge(v4, v1);

    for(Vertex* v : G.vertices){
        v->set("status", unvisited);
    }
    for(Edge* e: G.edges){
        e->set("status", unvisited);
    }

    BFS(G, v1, visited, discovery, cross, unvisited);

    for(Edge* e : G.edges){
        cout<<"Edge ("<<e->u->element <<", " <<e->v->element<<"): ";
        if (e->get("status") == discovery) {
            cout << "discovery" << endl;
        } else if (e->get("status") == cross) {
            cout << "cross" << endl;
        }
    }
    return 0;
}