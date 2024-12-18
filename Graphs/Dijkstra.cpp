#include<iostream>
#include<string>
#include<vector>
#include<list>
#include<map>
#include<queue>
#include<climits>

using namespace std;

class Object{};

class Decorator{
private:
    map<string, Object*> attributes;
public:
    Object* get(const string& key){
        return attributes[key];
    }

    void set(const string& key, Object* value){
        attributes[key] = value;
    }
};

class Vertex: public Decorator{
public:
    string element;
    list<class Edge*> outgoingEdges;

    Vertex(string elem): element(elem){}

    string operator*(){
        return element;
    }
};

class Edge: public Decorator{
public:
    Vertex* u;
    Vertex* v;
    int weight;

    Edge(Vertex* u, Vertex* v, int weight): u(u), v(v), weight(weight){}

    Vertex* opposite(Vertex* vertex){
        return (vertex == u)? v: nullptr;
    }
};

class DirectedGraph{
public:
    list<Vertex*> vertices;
    list<Edge*> edges;

    Vertex* insertVertex(string element){
        Vertex* newVertex = new Vertex(element);
        vertices.push_back(newVertex);
        return newVertex;
    }

    Edge* insertEdge(Vertex* u, Vertex* v, int weight){
        Edge* newEdge = new Edge(u, v, weight);
        u->outgoingEdges.push_back(newEdge);
        edges.push_back(newEdge);
        return newEdge;
    }
};

void DijkstraShortestPath(DirectedGraph& graph, Vertex* source){
    map<Vertex*, int> distance;

    auto compare = [&](Vertex* a, Vertex* b) { return distance[a] > distance[b];};
    priority_queue<Vertex*, vector<Vertex*>, decltype(compare)> priorityQueue(compare);

    for(auto vertex: graph.vertices){
        distance[vertex] = INT_MAX;
    }
    distance[source] = 0;
    priorityQueue.push(source);

    while (!priorityQueue.empty())
    {
        Vertex* u = priorityQueue.top();
        priorityQueue.pop();

        for(auto edge : u->outgoingEdges){
            Vertex* neighbor = edge->opposite(u);
            int edgeWeight = edge->weight;

            if(distance[u] + edgeWeight < distance[neighbor]){
                distance[neighbor] = distance[u] + edgeWeight;

                priorityQueue.push(neighbor);
            }
        }
    }

    cout<< "Shortest distance from source " << source->element << ":\n";
    for(auto& pair : distance){
        Vertex* vertex = pair.first;
        int dist = pair.second;
        cout<<"Vertex: "<<vertex->element<< ", Distance: ";
        if(dist == INT_MAX){
            cout<< "Infinity\n";
        }else{
            cout << dist << "\n";
        }
    }
}

int main() {
    DirectedGraph graph;

    Vertex* A = graph.insertVertex("A");
    Vertex* B = graph.insertVertex("B");
    Vertex* C = graph.insertVertex("C");
    Vertex* D = graph.insertVertex("D");
    Vertex* E = graph.insertVertex("E");

    graph.insertEdge(A, B, 4);
    graph.insertEdge(A, C, 1);
    graph.insertEdge(C, B, 2);
    graph.insertEdge(B, D, 1);
    graph.insertEdge(C, E, 5);
    graph.insertEdge(D, E, 3);

    DijkstraShortestPath(graph, A);

    return 0;
}