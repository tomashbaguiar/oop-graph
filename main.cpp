#include <iostream>
#include <fstream>
#include <cstdlib>
#include "Graph.h"
#include "Edge.h"
#include <string> 

using namespace std;

int main(int argc, char *argv[])
{

    ifstream inFile("Input.txt");

    if(inFile.is_open() == 0)
        cout << "Erro ao abrir o arquivo Input.txt." << endl;

    string quant;
    getline(inFile, quant);

    int quantity = atoi(quant.c_str());

    Graph grafo(quantity);
    
    while(inFile)
    {
	    int vert1, vert2;
	    inFile >> vert1;
	    inFile >> vert2;
	
	    Edge aux(vert1, vert2);
	    grafo.insert(aux);
    }

    /*	MENU de opçoes	*/

	unsigned short int choice = 0;

	do 
	{

        cout << "Digite: " << endl << " 0 - Sair do programa." << endl
            	                << " 1 - Inserir uma aresta no grafo." << endl
            	                << " 2 - Remover uma aresta no grafo." << endl
            	                << " 3 - Verificar a quantidade de arestas." << endl
            	                << " 4 - Verificar a quantidade de vertices." << endl
            	                << " 5 - Verificar se o grafo eh completo." << endl
            	                << " 6 - Completar o grafo." << endl
            	                << " 7 - Imprime os vertices utilizando busca em largura" << endl
            	                << " 8 - Imprime os vertices utilizando busca em profundidade" << endl
            	                << " 9 - Imprimir a quantidade de componentes conectados do grafo." << endl
            	                << " 10 - Verificar se uma aresta estah presente no grafo." << endl
                    	        << " 11 - Descobrir o menor caminho entre dois vertices do grafo." << endl;
        cout << "Escolha: ";
    	cin >> choice;
	
	    int number, number2;

        if((choice == 1) || (choice == 2) || (choice == 10))
        {
				cout << "Aresta do vertice: ";
				cin >> number;
				cout << " ao vertice: ";
				cin >> number2;
        }

        Edge aux(number, number2);
        int counter = 0;
        int *path = NULL;

		switch(choice)
		{
			case 1:
				grafo.insert(aux);
				break;
			case 2:
				grafo.remove(aux);
				break;
			case 3:
				cout << "Quantidade de arestas no grafo: " << grafo.quantEdge() << endl;
				break;
			case 4:
				cout << "Quantidade de vertices no grafo: " << grafo.quantVertex() << endl;
				break;
			case 5:
                if(grafo.isComplete())
                    cout << "Grafo eh completo." << endl;
                else
                    cout << "Grafo nao eh completo." << endl;
				break;
            case 6:
                grafo.complete();
                break;
            case 7:
                cout << "A partir de qual vertice?";
                cin >> number;
                grafo.BFS(number);
                break;
            case 8:
                cout << "A partir de qual vertice?";
                cin >> number;
                grafo.DFS(number, counter);
                break;
            case 9:
                cout << "Quantidade de vertices conectados: " << grafo.quantConnected() << endl;
                break;
            case 10:
				if(grafo.edge(aux))
                    cout << "Estah presente." << endl;
                else
                    cout << "Nao estah presente." << endl;
				break;
            case 11:
				cout << "Vertice de destino: ";
				cin >> number;
				cout << "Vertice de origem: ";
				cin >> number2;
                counter = 0;
				path = grafo.shortestPath(number, number2, counter);
                cout << "O caminho passa por " << counter << " vertices." << endl;
                for(int i = 0; i < counter; i++)
                    cout << " - " << path[i];
                cout << endl;
                delete [] path;
                break;
			default:
				cout << endl << "Saindo..." << endl;
				choice = 0;
		}
	}
	while(choice != 0);

    return EXIT_SUCCESS;
}
