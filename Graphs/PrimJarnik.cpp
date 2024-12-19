#include <iostream>
#include <map>
#include <list>
#include <string>
#include <queue>
#include <limits>
#include <set>
using namespace std;

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
    list<class Edge*> incidentEdges;

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

    Edge* insertEdge(Vertex* u, Vertex* v, int weight) {
        Edge* edge = new Edge(u, v, weight);
        u->incidentEdges.push_back(edge);
        v->incidentEdges.push_back(edge);
        edges.push_back(edge);
        return edge;
    }
};

class PrimJarnikMST {
public:
    struct PQNode {
        Vertex* vertex;
        Edge* edge;
        int key;

        bool operator<(const PQNode& other) const {
            return key > other.key;
        }
    };

    list<Edge*> computeMST(UndirectedGraph& graph) {
        map<Vertex*, int> D; 
        map<Vertex*, Edge*> edgeMap; 
        priority_queue<PQNode> pq; 
        set<Vertex*> inMST; 
        list<Edge*> MST; 

        Vertex* start = graph.vertices.front();
        for (auto vertex : graph.vertices) {
            D[vertex] = numeric_limits<int>::max();
            edgeMap[vertex] = nullptr;
        }
        D[start] = 0;

        for (auto vertex : graph.vertices) {
            pq.push({ vertex, nullptr, D[vertex] });
        }

        while (!pq.empty()) {
            PQNode current = pq.top();
            pq.pop();

            Vertex* u = current.vertex;

            if (inMST.find(u) != inMST.end()) continue;

            inMST.insert(u);

            if (current.edge != nullptr) {
                MST.push_back(current.edge);
            }

            for (auto edge : u->incidentEdges) {
                Vertex* z = edge->opposite(u);
                if (inMST.find(z) == inMST.end() && edge->weight < D[z]) {
                    D[z] = edge->weight;
                    edgeMap[z] = edge;
                    pq.push({ z, edge, D[z] });
                }
            }
        }

        return MST;
    }
};

ostream& operator<<(ostream& os, const Vertex& vertex) {
    os << vertex.element;
    return os;
}

int main() {
    UndirectedGraph graph;

    Vertex* A = graph.insertVertex("A");
    Vertex* B = graph.insertVertex("B");
    Vertex* C = graph.insertVertex("C");
    Vertex* D = graph.insertVertex("D");
    Vertex* E = graph.insertVertex("E");

    graph.insertEdge(A, B, 4);
    graph.insertEdge(A, C, 2);
    graph.insertEdge(B, C, 1);
    graph.insertEdge(B, D, 7);
    graph.insertEdge(C, D, 3);
    graph.insertEdge(C, E, 5);
    graph.insertEdge(D, E, 6);

    PrimJarnikMST mstSolver;
    list<Edge*> MST = mstSolver.computeMST(graph);

    cout << "Edges in the Minimum Spanning Tree:" << endl;
    for (auto edge : MST) {
        cout << "(" << *(edge->u) << ", " << *(edge->v) << ") Weight: " << edge->weight << endl;
    }

    return 0;
}