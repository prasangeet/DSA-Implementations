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
    list<class Edge*> outgoingEdges;

    Vertex(string elem): element(elem) {}

    string operator*(){
        return element;
    }
};

class Edge: public Decorator{
public: 
    Vertex* u;
    Vertex* v;

    Edge(Vertex* u, Vertex* v): u(u), v(v) {}

    Vertex* opposite(Vertex* vertex){
        return (vertex == u) ? v : nullptr;;
    }
};

class Graph{
public: 
    list<Vertex*> vertices;
    list<Edge*> edges;

    Vertex* insertVertex(string x){
        Vertex* v = new Vertex(x);
        vertices.push_back(v);
        return v;
    }

    Edge* insertEdge(Vertex* u, Vertex* v){
        Edge* e = new Edge(u, v);
        edges.push_back(e);
        u->outgoingEdges.push_back(e);
        return e;
    }
};

void TopologicalSort(Graph& G){
    map<Vertex*, int> inDegree;
    queue<Vertex*> zeroInDegVetices;
    list<Vertex*> order;

    for(Vertex* v : G.vertices){
        inDegree[v] = 0;
    }

    for(Edge* e: G.edges){
        inDegree[e->v]++;
    }

    for(Vertex* v : G.vertices){
        if(inDegree[v] == 0){
            zeroInDegVetices.push(v);
        }
    }

    while(!zeroInDegVetices.empty()){
        Vertex* u = zeroInDegVetices.front();
        zeroInDegVetices.pop();
        order.push_back(u);

        for(Edge* e : u->outgoingEdges){
            Vertex* w = e->opposite(u);
            if(--inDegree[w] == 0){
                zeroInDegVetices.push(w);
            }
        }
    }

    if(order.size() != G.vertices.size()){
        cout << "Graph contains a cycle. Topological sorting is not possible." << endl;
        return;
    }
    cout << "Topological Order:" << endl;
    for (Vertex* v : order) {
        cout << v->element << " ";
    }
    cout << endl;
}

int main(){
    Graph G;

    Vertex* v1 = G.insertVertex("A");
    Vertex* v2 = G.insertVertex("B");
    Vertex* v3 = G.insertVertex("C");
    Vertex* v4 = G.insertVertex("D");
    Vertex* v5 = G.insertVertex("E");

    G.insertEdge(v1, v2); // A -> B
    G.insertEdge(v1, v3); // A -> C
    G.insertEdge(v3, v4); // C -> D
    G.insertEdge(v2, v4); // B -> D
    G.insertEdge(v4, v5); // D -> E

    TopologicalSort(G);

    return 0;
}