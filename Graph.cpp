#include "Graph.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <list>
#include <stack>

Graph::Graph(const int quantity)
{
    adjMatrix_ = new int*[quantity]; //Alocando vetor de ponteiros.
    
    for(int i = 0; i < quantity; i++)
        adjMatrix_[i] = new int[quantity];  //Alocando vetor de inteiros (matriz).

    for(int i = 0; i < quantity; i++)
    {
	for(int j = 0; j < quantity; j++)
           adjMatrix_[i][j] = 0;
    }

    Vertex_ = quantity;
    
    adjList = new std::list<int>[Vertex_];

    Edge_ = 0;
}

bool Graph::insert(const Edge& edgei)
{
    if(edge(edgei) || (edgei.after == edgei.before))
        return false;

    adjMatrix_[edgei.after][edgei.before] = 1;
    adjMatrix_[edgei.before][edgei.after] = 1;

    adjList[edgei.before].push_back(edgei.after);
    adjList[edgei.after].push_back(edgei.before);
    
    Edge_++;

    return true;
}

bool Graph::remove(const Edge &edger)
{
    if(!edge(edger) || (edger.after == edger.before))
        return false;

    int rem;
    int count = 0;

    do
    {
    	rem = adjList[edger.before].front();
	    if(rem != edger.after)
		    adjList[edger.before].push_back(rem);
        count++;
        if(count > Vertex_)
            return false;
    }
    while(rem != edger.after);
    
    do
    {
    	rem = adjList[edger.after].front();
	    if(rem != edger.before)
		    adjList[edger.after].push_back(rem);
        count++;
        if(count > Vertex_)
            return false;
    }
    while(rem != edger.before);

    adjMatrix_[edger.after][edger.before] = 0;
    adjMatrix_[edger.before][edger.after] = 0;
    Edge_--;

    return true;
}

int Graph::quantEdge()
{
    return Edge_;   
}

int Graph::quantVertex() 
{   
    return Vertex_; 
}

bool Graph::isComplete()
{
    for(int i = 0; i < Vertex_; i++)
    {
        for(int j = 0; j < Vertex_; j++)
        {
            if(!adjMatrix_[i][j])
                return false;
        }
    }

    return true;
}

bool Graph::edge(const Edge &edgei) const
{
	if(adjMatrix_[edgei.after][edgei.before] &&
		adjMatrix_[edgei.before][edgei.after])
		return true;
    
	return false;
}

void Graph::complete()
{
    if(!isComplete())
    {
        for(int i = 0; i < Vertex_; i++)
        {
            for(int j = 0; j < Vertex_; j++)
            {
                if((!adjMatrix_[i][j]) && (i != j))
                {
                    Edge aux(i, j);
		    insert(aux);
                }
            }
        }
    }
}

void Graph::BFS(const int vertex)
{
	bool *visited = new bool[Vertex_];
	for(int i = 0; i < Vertex_; i++)
		visited[i] = false;

	std::list<int> queue;

	visited[vertex] = true;

	queue.push_back(vertex);
	
	int v = vertex;

	std::list<int>::iterator i;
	
	while(!queue.empty())
	{
		v = queue.front();
		std::cout << " -> " << v;
		queue.pop_front();

		for(i = adjList[v].begin(); i != adjList[v].end(); ++i)
		{
			if(!visited[*i])
			{
				visited[*i] = true;
				queue.push_back(*i);
			}
		}
	}
	std::cout << std::endl;
}

void Graph::DFS(const int vertex, int &counter)
{
	bool *visited = new bool[vertex];
	for(int i = 0; i < Vertex_; i++)
		visited[i] = false;

	std::stack<int> stack;

	visited[vertex] = true;
	stack.push(vertex);

	int v = vertex;

	std::list<int>::iterator i;

	while(!stack.empty())
	{
		v = stack.top();
		std::cout << " -> " << v;
		counter++;
		stack.pop();

		for(i = adjList[v].begin(); i != adjList[v].end(); ++i)
		{
			if(!visited[*i])
			{
				visited[*i] = true;
				stack.push(*i);
			}
		}
	}
	
	std::cout << std::endl;
}

int Graph::quantConnected()
{
	int counter = 0;
	DFS(0, counter);

	return counter;
}

int Graph::getMin(const int *distance, const bool *visited)
{
    int vMin, least;
    bool flag = false;

    for(int i = 0; (i < Vertex_) && (flag == false); i++)
    {
        if(visited[i] == false)
        {
            least = distance[i];
            vMin = i;
            flag = true;
        }
    }

    for(int i = 0; i < Vertex_; i++)
    {
        if((visited[i] == false) && (distance[i] < least))
        {
            least = distance[i];
            vMin = i;
        }
    }

    return vMin;
}

int* Graph::shortestPath(const int vertex1, const int vertex2, int &counter)
{
    unsigned int infinite = 99999999;
	bool *visited = new bool[Vertex_];
    int *distance = new int[Vertex_];
    int *pred = new int[Vertex_];

    for(int i = 0; i < Vertex_; i++)
    {
        distance[i] = infinite;
        pred[i] = -1;
        visited[i] = false;
    }

    distance[vertex1] = 0;
    int length = 0;

    while(visited[vertex2] == false)
    {
        int vMin = getMin(distance, visited);

        for(int i = 0; i < Vertex_; i++)
        {
            if((adjMatrix_[vMin][i] != 0) && (visited[i] == false))
            {
                if(distance[i] > (distance[vMin] + adjMatrix_[vMin][i]))
                {
                    distance[i] = distance[vMin] + adjMatrix_[vMin][i];
                    pred[i] = vMin;
                }
            }
        }
    
        visited[vMin] = true;
    }

    counter = 0;
    length = distance[vertex2];
    counter++;
    int aux = vertex2;

    while(aux != vertex1)
    {
        length += distance[pred[aux]];
        aux = pred[aux];
        counter++;
    }

    int *path = new int[counter];

    counter = 0;
    path[counter] = vertex2;
    aux = vertex2;
    counter++;

    while(aux != vertex1)
    {
        path[counter] = pred[aux];
        aux = pred[aux];
        counter++;
    }
    
    return path;
}


Graph::~Graph()
{
    for(int i = 0; i < Vertex_; i++)
        delete [] adjMatrix_[i];
    delete [] adjMatrix_;
    //Destrutor.
}
