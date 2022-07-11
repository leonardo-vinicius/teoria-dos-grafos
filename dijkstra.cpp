#include <iostream>
#include <list>
#include <queue>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

// Algoritmo de Dijkstra feito por Leonardo Vinicius e João Pedro Castelo

// classe do grafo
class Grafo
{   private:
	    int N;// N é o n° de vertices(quantidade)
	    list<pair<int, int> > * vizinhos; //lista de pares que aponta para vizinhos

    public:
	    Grafo(int N){
		    this->N = N; // construtor
		    vizinhos = new list<pair<int, int> >[N]; //lista de pares vizinhos vai conter a aresta de destino e o peso
													// cada vertice tem sua lista de vizinhos
	}

	void adicionarAresta(int v1, int v2, int peso)
	{vizinhos[v1].push_back({v2, peso});} // funcao de adicionar aresta jogando vertice de destino e peso

	int dijkstra(int origem, int destino){ // funcao de dijkstra
		int pre[N]; 		//pre de cada vertice, muito importante para a saida final
		int distancia[N];   // distancia
		int visitados[N];	// visitados

		// heap, fila de prioridade
		priority_queue < pair<int, int>,vector<pair<int, int> >, greater<pair<int, int> > > H;// greater indica que vai pegar o menor
		
		for(int i = 0; i < N; i++){
			distancia[i] = 9999; //distancia de cada vertice recebe infinito
			visitados[i] = 0; // visitados é um booleano recebe 0 se nao foi visitado
			pre[i] = -1;      // pre recebe menos 1
		}

		distancia[origem] = 0;

		H.push({distancia[origem], origem});

		while(!H.empty()){
			int u = H.top().second;
			H.pop();

			if(visitados[u] == 0){
				visitados[u] = 1;

				// iterator i para percorrer a lista de vizinhos de um vertice u que nao foi visitado
				for(list<pair<int, int> >::iterator i = vizinhos[u].begin(); i != vizinhos[u].end(); i++){
    
					int v = i->first; 
					int peso_aresta = i->second;

					if(distancia[v] > (distancia[u] + peso_aresta))
					{
						distancia[v] = distancia[u] + peso_aresta;
						H.push({distancia[v], v});
						pre[v] = u;
					}
				}
			}
		}

		cout << "caminho minimo: ";
		int f=destino;
		while (f > origem) //um laco para printar o caminho de peso minimo
		{	int o = pre[destino];
			if(f == destino){}
			else{
				cout <<"(" << pre[o] << "," << pre[destino] << ")  ";
			}
			f=pre[f];
		}
		
		cout <<"(" << pre[destino] << "," << destino << ")  " << endl;
		cout << "e a menor distancia entre " << origem << " e " << destino << " eh: " << distancia[destino] << endl;
		return 0;
	}
};

int main(int argc, char *argv[]){

    string linha, linha2, aux, aux2;
    fstream arquivo;
    arquivo.open("exemplo.txt", fstream::in);
    vector<int> line_tam;
    vector<int> line_arestas;
    int contador=0;

    if(arquivo.is_open()){ // esse eh o metodo que uso para pegar o txt, primeiro adiciono no tamanho dos vertices e arestas
        getline(arquivo, linha);
        std::stringstream read(linha);
        while(getline(read, aux, ' ')){
            int num = stoi(aux); //essa funcao transforma uma linha(aux) em um vetor int
            line_tam.push_back(num);
        }
    }
    int n = line_tam[0]; // primeira linha é o n (tamanho dos vertices)
    int m = line_tam[1]; // segunda linha é o m (tamanho das arestas)
    
    Grafo g(n); //grafo declarado de tamanho n 
    
    while(arquivo){ // aqui eu vou adicionar as arestas
        getline(arquivo, linha2);
        std::stringstream read2(linha2); 
        while(getline(read2, aux2, ' ')){ 
            int num2 = stoi(aux2); //essa funcao transforma uma linha(aux2) em um vetor int
            line_arestas.push_back(num2);
        }

		// linha 1 desse vetor ignorando espaços é o vertice de origem, linha 2 vert de destino e linha 3 peso
        g.adicionarAresta(line_arestas[0], line_arestas[1], line_arestas[2]);
        line_arestas.clear(); //LIMPAR as variaveis
        contador++;

        if(contador == m){ //se o contador chegar no n° de arestas encerra o laço e fecha o txt
            arquivo.close();
            break;
        }
    }

	int vertice1, vertice2;
	cout << "//lembre-se que Dijkstra nao calcula arestas com pesos negativos!//" << endl;
	cout << "\n" <<"O programa vai calcular a distancia entre dois vertices digitados." << endl;
	cout << "\n" << "digite qual o vertice de origem: ";
	cin >> vertice1;
	cout << "digite qual o vertice de destino: ";
	cin >> vertice2;;
	g.dijkstra(vertice1, vertice2);

	return 0;
}