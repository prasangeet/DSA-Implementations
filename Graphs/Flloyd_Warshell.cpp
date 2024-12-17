#include<iostream>
#include<list>
#include<vector>
#include<string>
#include<stdexcept>
#include<unordered_map>

using namespace std;

class Edge;

class Vertex{
public: 
    string element;
    list<Edge*> incidentEdges;

    Vertex(string elem): element(elem){}

    string operator*() {return element; }
};

class Edge{
public:
    string element;
    Vertex* u;
    Vertex* v;

    Edge(string elem, Vertex* u, Vertex* v): element(elem), u(u), v(v){}

    string operator*(){ return element;}

    pair<Vertex*, Vertex*> endVertices() { return {u, v}; }
};

ostream& operator<<(ostream& os, const Vertex& v) {
    os << v.element;  // Print the element (e.g., name of the vertex)
    return os;
}

ostream& operator<<(ostream& os, const Edge& e) {
    os << e.element;  // Print the element (e.g., name of the vertex)
    return os;
}

class GraphAdjList{
private:
    list<Vertex*> vertices;
    list <Edge*> edges;
    unordered_map<string, Vertex*> vertexMap;
public:
    list<Vertex*> getVertices(){return vertices;}

    list<Edge*> getEdges(){return edges;}

    Vertex* insertVertex(string x){
        Vertex* v = new Vertex(x);
        vertices.push_back(v);
        vertexMap[x] = v;
        return v;
    }

    Edge* insertDirectedEdge(Vertex* v, Vertex* w, string x){
        Edge* e = new Edge(x, v, w);
        edges.push_back(e);
        v->incidentEdges.push_back(e);
        return e;
    }

    bool hasEdge(Vertex* u, Vertex* v){
        for(Edge* e : u->incidentEdges){
            if (e->u == u && e->v == v)
            {
                return true;
            }
        }
        return false;
    }

    void addEdgeIfNotPresent(Vertex* u, Vertex* v){
        if(!hasEdge(u, v)){
            insertDirectedEdge(u, v, "TransitiveEdge");
        }
    }

    void computeTransitiveClosure(){
        vector<Vertex*> vertexList(vertices.begin(), vertices.end());
        int n = vertexList.size();

        for (int k = 0; k < n; k++)
        {
            Vertex* intermediate = vertexList[k];
            for (int i = 0; i < n; i++)
            {
                Vertex* source = vertexList[i];
                for (int j = 0; j < n; j++)
                {
                    Vertex* target = vertexList[j];
                    if(hasEdge(source, intermediate) && hasEdge(intermediate, target)){
                        addEdgeIfNotPresent(source, target);
                    }
                }
                
            }
            
        }
        
    }

    void printGraph() {
        for (auto v : vertices) {
            cout << "Vertex: " << *v << " -> ";
            for (auto e : v->incidentEdges) {
                cout << "(" << *(e->u) << "->" << *(e->v) << ") ";
            }
            cout << endl;
        }
    }
};

void testFloydWarshall() {
    GraphAdjList graph;

    // Insert vertices
    Vertex* vA = graph.insertVertex("A");
    Vertex* vB = graph.insertVertex("B");
    Vertex* vC = graph.insertVertex("C");
    Vertex* vD = graph.insertVertex("D");

    // Insert directed edges
    graph.insertDirectedEdge(vA, vB, "Edge1");
    graph.insertDirectedEdge(vB, vC, "Edge2");
    graph.insertDirectedEdge(vC, vD, "Edge3");

    cout << "Original Graph:" << endl;
    graph.printGraph();

    // Compute transitive closure
    graph.computeTransitiveClosure();

    cout << "\nTransitive Closure:" << endl;
    graph.printGraph();
}

int main(){
    testFloydWarshall();

    return 0;
}
