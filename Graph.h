//jcarlosr@ufmg.br  -   Precisa de bolsista (sem bolsa).
#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <list>
#include "Edge.h"

class Graph
{
    private:
        int Edge_;  //Numero de arestas do grafo.
        int Vertex_;    //Numero de vertices do grafo.
        int **adjMatrix_; //Ponteiro para matriz de adjacencias.
        Edge *edgeArray_;   //Ponteiro para vetor de arestas.
	    std::list<int> *adjList;
    public:
        Graph(const int);   //Construtor da classe Graph.
        bool insert(const Edge&);   //Insere arestas no grafo.
        bool remove(const Edge&);   //Remove arestas do grafo.
        int quantEdge();    //Retorna a quantidade de arestas.
        int quantVertex();  //Retorna a quantidade de vertices.
        bool isComplete();  //Verifica se o grafo eh completo.
        bool edge(const Edge&) const; //Verifica a existencia de uma aresta no grafo.
        void complete();    //Completa o grafo.
        void BFS(const int);    //Imprime os indices dos vertices na ordem do caminhamento em largura.
        void DFS(const int, int& counter);    //Imprime os indices dos vertices na ordem do caminhamento em profundidade.
       	int quantConnected();    //Retorna a quantidade de componentes conectados do grafo - por meio de DFS.
        int getMin(const int*, const bool*);
        int* shortestPath(const int, const int, int&);    //Encontra o menor caminho, atraves do Algoritmo de Dijkstra, entre dois vertices do grafo, e retorna um ponteiro para um vetor contendo os vertices desse caminho e o comprimento desse caminho (ultimo valor do vetor).
        ~Graph();   //Destrutor da classe Graph.
};

#endif /* GRAPH_H */
