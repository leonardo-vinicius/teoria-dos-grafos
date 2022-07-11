#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

// este é um algoritmo simples de bellman-ford feito por Leonardo Vinicius para a disciplina de teoria dos grafos

int main(){
	
	vector<vector<int>> vertices;

	string linha, linha2, aux, aux2;
    fstream arquivo;
    arquivo.open("exemplo-ford.txt", fstream::in);
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
    
    while(arquivo){ // aqui eu vou adicionar as arestas
        getline(arquivo, linha2);
        std::stringstream read2(linha2); 
        while(getline(read2, aux2, ' ')){ 
            int num2 = stoi(aux2); //essa funcao transforma uma linha(aux2) em um vetor int
            line_arestas.push_back(num2);
        }

        vertices.push_back({line_arestas[0], line_arestas[1], line_arestas[2]});
        line_arestas.clear(); //LIMPAR as variaveis
        contador++;

        if(contador == m){ //se o contador chegar no n° de arestas encerra o laço e fecha o txt
            arquivo.close();
            break;
        }
    }   
	
	int v0=0; //vertice inicial v0
    cout << "digite o vertice inicial: ";
	cin >> v0;
	vector<int> distancia(n, 9999);
	distancia [v0] = 0;
	//int soma_pesos = 0;
	for(int iteracoes=0; iteracoes<n-1; iteracoes++){

	    for(auto e:vertices){
	        int u = e[0];
	        int v = e[1];
	        int w = e[2];
            
	        if(distancia[v] > w + distancia[u])
	        distancia[v] = min(distancia[v], w + distancia[u]);
            //soma_pesos =+ distancia[v];
	    }
    }

    for(int i=0; i<m; i++){
	    for(auto e:vertices){
	        int u = e[0];
	        int v = e[1];
	        int w = e[2];
	        if(distancia[v] > w + distancia[u]){
                // se houver ciclos negativos encerra o programa e exibe essa mensagem
                cout << "ERRO" << endl;
                cout << "Grafo tem ciclo ou ciclos de peso negativo"; 
                exit(0);
            }
	    }
    }

    int j=0;
    cout << "menor distancia entre:" << endl;
	for(auto i : distancia){
        cout << "(" << v0 << "," << j << ")  ";
		cout << i << " " << endl;
        j++;
	}

    cout << "se apareceu '9999' significa infinito" << endl << "diz respeito a distancia '->' que nao existe" << endl;
    /*lembrando que se voce digitou um numero e uma coordenada printada"
     for infinito(9999), significa que nao existe uma aresta que vai do v0 indo"
     provavelmente so tem saindo do outro vertice e nao o contrario" */

    return 0;
}