#include <iostream>
#include <list>
#include <vector>
#include <cstdint>
#include <queue>
#include <stack>
#include <utility>

using namespace std;

class Graph {
    struct Vertice {
        list<Vertice*> edges;
        uint16_t value;
    };

    public:
    vector<Vertice> all_vertices;
    
    Graph(uint16_t n_vert);
    //void addVertices(uint8_t quant);
    //void rmvVertice()
    void addUndirEdge(uint16_t vert_a, uint16_t vert_b);
    //void addDirEdge(uint16_t from_vert, uint16_t to_vert);
    //void rmvDirEdge(uint16_t vert_a, uint16_t vert_b);
    //void rmvUndirEdge(uint16_t from_vert, uint16_t to_vert);
    void printEdges(uint16_t vert);
    void bfsPrint(uint16_t start_vert);
    void dfsPrint(uint16_t start_vert);
    //bool isConnected();
};

Graph::Graph(uint16_t n_vert) {
    all_vertices = vector<Vertice>(n_vert);

    cout << "Grafo criado: { ";

    uint16_t i;
    for(i = 0; i < n_vert - 1; i++) {
        all_vertices[i].value = i;
        cout << i << ", ";
    }

    all_vertices[i].value = i;
    cout << i << " }\n";
}

void Graph::addUndirEdge(uint16_t vert_a, uint16_t vert_b) {
    all_vertices[vert_a].edges.push_back(&all_vertices[vert_b]);
    all_vertices[vert_b].edges.push_back(&all_vertices[vert_a]);

    cout << "Aresta não direcionada criada: " << all_vertices[vert_a].value << " <-> " << all_vertices[vert_b].value << '\n'; 
}

void Graph::printEdges(uint16_t vert) {
    cout << "Do vertice " << all_vertices[vert].value << '\n';

    for(Vertice* v : all_vertices[vert].edges) {
        cout << "vai para: " << v->value << '\n';
    }
}

void Graph::bfsPrint(uint16_t start_vert) {
    queue<Vertice*> q;
    vector<bool> visited(all_vertices.size());

    q.push(&all_vertices[start_vert]);
    visited[start_vert] = true;

    cout << "DFS:\nInício: "; 

    while(!q.empty()) {
        Vertice* front = q.front();
        q.pop();

        cout << front->value << '\n';

        for(Vertice* v : front->edges) {
            if(!visited[v->value]) {
                visited[v->value] = true;
                q.push(v);
            }
        }
    }
}

void Graph::dfsPrint(uint16_t start_vert) {
    stack<pair<Vertice*, >> s;
    vector<bool> visited(all_vertices.size());
    
    s.push(&all_vertices[start_vert]);
    visited[start_vert] = true;

    while(!s.empty()) {
        
    }
}

int main() {
    Graph a(11);

    a.addUndirEdge(0, 1);
    a.addUndirEdge(1, 2);
    a.addUndirEdge(1, 3);
    a.addUndirEdge(1, 4);
    a.addUndirEdge(3, 4);
    a.addUndirEdge(3, 5);
    a.addUndirEdge(4, 5);
    a.addUndirEdge(5, 6);
    a.addUndirEdge(2, 6);
    a.addUndirEdge(2, 10);
    a.addUndirEdge(9, 10);
    a.addUndirEdge(3, 9);
    a.addUndirEdge(0, 7);
    a.addUndirEdge(3, 7);
    a.addUndirEdge(7, 8);

    a.bfsPrint(10);
}
