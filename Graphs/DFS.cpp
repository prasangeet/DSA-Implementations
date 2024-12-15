#include<iostream>
#include<map>
#include<list>
#include<string>

using namespace std;

class Object{};

class Decorator{
private: 
    map<string, Object*> attributes;

public:
    Object* get(const string& key) {return attributes[key];}
    void set(const string& key, Object* value) {attributes[key] = value;}
};

class Vertex: public Decorator {
public:
    string element;
    list<class Edge*> incidentEdges;
    Vertex(string elem): element(elem) {}
};

class Edge: public Decorator {
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

    Vertex* insertVertex(string x){
        Vertex* newVertex = new Vertex(x);
        vertices.push_back(newVertex);
        return newVertex;
    }

    Edge* insertEdge(Vertex* u, Vertex* v){
        Edge* e = new Edge(u, v);
        u->incidentEdges.push_back(e);
        v->incidentEdges.push_back(e);
        edges.push_back(e);
        return e;
    }
};

void DFS(Graph& G, Vertex* v, Object* visited, Object* discovery, Object* back, Object* unvisited) {
    v->set("status", visited);

    for (Edge* e : v->incidentEdges) {
       if (e->get("status") == unvisited) {  // If edge is unvisited
            Vertex* w = e->opposite(v);  // Get the opposite vertex
            if (w->get("status") == unvisited) {  // If opposite vertex is unvisited
                e->set("status", discovery);  // Mark edge as discovery
                DFS(G, w, visited, discovery, back, unvisited);  // Recursive DFS
            } else {
                e->set("status", back);  // Mark edge as back edge
            }
        }
    }
}

int main(){
    Object* unvisited = new Object();
    Object* visited = new Object();
    Object* discovery = new Object();
    Object* back = new Object();

    Graph G;
    Vertex* v1 = G.insertVertex("A");
    Vertex* v2 = G.insertVertex("B");
    Vertex* v3 = G.insertVertex("C");
    Edge* e1 = G.insertEdge(v1, v2);
    Edge* e2 = G.insertEdge(v2, v3);
    Edge* e3 = G.insertEdge(v3, v1);

    for (Vertex* v : G.vertices) {
        v->set("status", unvisited);
    }
    for (Edge* e : G.edges) {
        e->set("status", unvisited);
    }

    DFS(G, v1, visited, discovery, back, unvisited);

    for (Vertex* v : G.vertices) {
        cout << "Vertex " << v->element << " status: " 
             << (v->get("status") == visited ? "visited" : "unvisited") << endl;
    }
    for (Edge* e : G.edges) {
        cout << "Edge (" << e->u->element << ", " << e->v->element << ") status: ";
        if (e->get("status") == discovery) {
            cout << "discovery" << endl;
        } else if (e->get("status") == back) {
            cout << "back" << endl;
        }
    }
}