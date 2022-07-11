#include <iostream>
#include <vector>
#include <algorithm>
#include <string.h>
#include <list>
#include <queue>
#include <fstream>
#include <sstream>

using namespace std;

// este é um algoritmo simples de kruskal feito por Leonardo Vinicius e João Pedro Castelo para a disciplina de teoria dos grafos

class Aresta{

	int u, v, custo;

public:

	Aresta(int v1, int v2, int custo){
		u = v1;
		v = v2;
		this->custo = custo;
	}

	int printar(int index){
		switch (index){
			case 1: return u; break;
			case 2: return v; break;
			case 3: return custo; break;
		}
	}

	bool operator < (const Aresta& aresta2) const{return (custo < aresta2.custo);}

};

class Grafo{
	int N;
	vector<Aresta> arestas;

public:

	Grafo(int N){
		this->N = N;
	}

	void adicionarAresta(int v1, int v2, int custo){
		Aresta aresta(v1, v2, custo);
		arestas.push_back(aresta);
	}

	int buscar(int subset[], int i){
		if(subset[i] == -1)
			return i;
		return buscar(subset, subset[i]);
	}

	void unir(int subset[], int v1, int v2){
		int v1_set = buscar(subset, v1);
		int v2_set = buscar(subset, v2);
		subset[v1_set] = v2_set;
	}

	void kruskal(){
		vector<Aresta> arvore;
		int tamanho_aresta = arestas.size();
		sort(arestas.begin(), arestas.end());
		int * subset = new int[N];
		memset(subset, -1, sizeof(int) * N);
		int cont1 = 0;
		while(cont1 < tamanho_aresta){
			//cout << "1";
			int v1 = buscar(subset, arestas[cont1].printar(1));
			int v2 = buscar(subset, arestas[cont1].printar(2));

			if(v1 != v2){
				//cout << "2";
				arvore.push_back(arestas[cont1]);
				unir(subset, v1, v2);
			}
			cont1++;
		}

		int tamanho_arvore = arvore.size();

		int cont2=0;
		while(cont2 < tamanho_arvore)
		{   //cout << "3";
			int v1 = arvore[cont2].printar(1);
			int v2 = arvore[cont2].printar(2);
			cout << "(" << v1 << ", " << v2 << ") custo: " << arvore[cont2].printar(3) << endl;
			cont2++;
		}
	}
};

int main(int argc, char *argv[])
{
	string linha, linha2, aux, aux2;
    fstream arquivo;
    arquivo.open("exemplok-novo.txt", fstream::in);
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
        // cout << ".";
        g.adicionarAresta(line_arestas[0], line_arestas[1], line_arestas[2]);
        line_arestas.clear(); //LIMPAR as variaveis
        contador++;

        if(contador == m){ //se o contador chegar no n° de arestas encerra o laço e fecha o txt
            arquivo.close();
            break;
        }
    }

    g.kruskal();
	
	return 0;
}