#include <iostream>
#include <map>
#include <list>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// Class Definitions
class Object {};

class Decorator {
private:
    map<string, Object*> attributes;
public:
    Object* get(const string& key) { return attributes[key]; }
    void set(const string& key, Object* value) { attributes[key] = value; }
};

class Vertex : public Decorator {
public:
    string element;
    list<class Edge*> incidentEdges; // Incident edges for undirected graph

    Vertex(string elem) : element(elem) {}

    string operator*() {
        return element;
    }
};

class Edge : public Decorator {
public:
    Vertex* u;
    Vertex* v;
    int weight;

    Edge(Vertex* u, Vertex* v, int weight) : u(u), v(v), weight(weight) {}

    Vertex* opposite(Vertex* vertex) {
        return (vertex == u) ? v : u;
    }

    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};

class UndirectedGraph {
public:
    list<Vertex*> vertices;
    list<Edge*> edges;

    Vertex* insertVertex(string element) {
        Vertex* vertex = new Vertex(element);
        vertices.push_back(vertex);
        return vertex;
    }

    void insertEdge(Vertex* u, Vertex* v, int weight) {
        Edge* edge = new Edge(u, v, weight);
        edges.push_back(edge);
        u->incidentEdges.push_back(edge);
        v->incidentEdges.push_back(edge);
    }
};

class UnionFind{
private:
    map<Vertex*, Vertex*> parent;
    map<Vertex*, int> rank;
public:
    void makeSet(Vertex* v){
        parent[v] = v;
        rank[v] = 0;
    }

    Vertex* find(Vertex* v) {
        if (parent[v] != v)
            parent[v] = find(parent[v]); // Path compression
        return parent[v];
    }

    void unionSet(Vertex* u, Vertex* v){
        Vertex* rootU = find(u);
        Vertex* rootV = find(v);

        if (rootU != rootV) {
            if (rank[rootU] < rank[rootV]) {
                parent[rootU] = rootV;
            } else if (rank[rootU] > rank[rootV]) {
                parent[rootV] = rootU;
            } else {
                parent[rootV] = rootU;
                rank[rootU]++;
            }
        }
    }
};

list<Edge*> krushallMST(UndirectedGraph graph){
    list<Edge*> mst;
    vector<Edge*> edgeList(graph.edges.begin(), graph.edges.end());
    UnionFind uf;

    for(Vertex* v : graph.vertices){
        uf.makeSet(v);
    }

    sort(edgeList.begin(), edgeList.end(), [](Edge* e1, Edge* e2) {
        return e1->weight < e2->weight;
    });

    for(Edge* edge: edgeList){
        Vertex* u = edge->u;
        Vertex* v = edge->v;

        if(uf.find(u) != uf.find(v)){
            mst.push_back(edge);
            uf.unionSet(u, v);
        }
    }

    return mst;
}

int main(){
    UndirectedGraph graph;
    Vertex* A = graph.insertVertex("A");
    Vertex* B = graph.insertVertex("B");
    Vertex* C = graph.insertVertex("C");
    Vertex* D = graph.insertVertex("D");
    Vertex* E = graph.insertVertex("E");

    graph.insertEdge(A, B, 4);
    graph.insertEdge(A, C, 2);
    graph.insertEdge(B, C, 5);
    graph.insertEdge(B, D, 10);
    graph.insertEdge(C, D, 8);
    graph.insertEdge(C, E, 3);
    graph.insertEdge(D, E, 6);

    list<Edge*> mst = krushallMST(graph);

    cout << "Edges in the Minimum Spanning Tree:" << endl;
    for (Edge* edge : mst) {
        cout << edge->u->element << " - " << edge->v->element << " (Weight: " << edge->weight << ")" << endl;
    }

    return 0;
}