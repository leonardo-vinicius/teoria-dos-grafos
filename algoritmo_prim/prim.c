#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define true 1
#define false 0
typedef int bool;

// código simples do algoritmo de Prim feito por Leonardo Vinicius e João Pedro Castelo

void help()
{
    printf("--------------Algoritmo de Prim--------------\n");
    printf("Consideramos um vertice inicial na arvore e a cada interação ele pega a aresta mais barata que conecte a um vértice não pertencente a árvore\n");
    printf("Feito com matriz de Adjacencia\n");
}

void grafo(int nume_vertices, int nume_arestas, int ma_adj[][nume_vertices], FILE *texto) //criar grafo
{
    int origem, destino, peso;
    //iniciando grafo com 9999 nas arestas
    for ( int n = 0; n < nume_vertices; n++ )
    {
        for ( int l = 0; l < nume_vertices; l++)
        {
            ma_adj[n][l] = 9999;
        }
    }
    //colocando arestas com pesos
    for ( int i = 0; i < nume_arestas; i++)
    {   char pes;
        fscanf(texto, "%d %d %d", &origem, &destino);
        fscanf(texto, "%c", &pes);

        if (pes == '\n')
        {
            pes = 1;
        }
        
        else
        {
            fscanf(texto, "%d", &pes);
        }

        ma_adj[origem - 1][destino - 1]=pes;
        ma_adj[destino - 1][origem - 1]=pes;
    }
}

int Prim (int nume_vertices, int ma_adj[][nume_vertices], int pai[], int origem)
{ int men_peso, peso_total=0, dest;


    for (int i = 0; i < nume_vertices ; i++) //iniciando todo mundo tendo pai = -1
    {
        pai[i]=-1;
    }
    pai[origem]=origem; //colocando o vertice origem como pai dele mesmo
    while (1)
    {
        int primeiro=1;
        
        for(int i = 0; i < nume_vertices; i++) //percorrer os vertices
        { 

            if(pai[i] != -1) //achar vertices ja visitados
            {   
                for (int m = 0; m < nume_vertices; m++) //percorrer vizinhos
                {   
                    if(pai[m] == -1) //achar vertice náo visitado
                    {
                        if(ma_adj[i][m] != 9999) // achou vertice com caminho diferente de "infinito"
                        {   
                            if(primeiro == 1) 
                            {
                                men_peso = ma_adj[i][m]; // pegou a aresta com menor peso
                                origem=i;
                                dest=m;
                                primeiro = 0;
                            }
                        
                            else //checar se existe outra aresta com menor peso
                            {
                                if(men_peso > ma_adj[i][m])
                                {
                                men_peso = ma_adj[i][m];
                                origem=i;
                                dest=m;
                                }
                            }
                        }
                    }
                }
            }

        }
        
        if(primeiro==1)
        {   
            break;
        }

    pai[dest]=origem; //alocou vertice visitado como filho
    peso_total=peso_total+men_peso; //somou o peso da aresta
    }
    
return peso_total;
}


int main(int argc, char *argv[])
{
  int initV = 0, lastV = 0, in = 0, out = 0;
  bool solucao = false;

  for (int i = 0; i < argc; i++)
  {
    if (strcmp(argv[i], "-i") == 0)
      sscanf(argv[i + 1], "%d", &initV);
    if (strcmp(argv[i], "-l") == 0)
      sscanf(argv[i + 1], "%d", &lastV);
    if (strcmp(argv[i], "-s") == 0)
      solucao = 1;
    if (strcmp(argv[i], "-o") == 0)
      out = i + 1;
    if (strcmp(argv[i], "-f") == 0)
    {
      if (strcmp(argv[i + 1], "-s") == 0)
        in = i + 2;
      else
        in = i + 1;
    }

    if (strcmp(argv[i], "-h") == 0)
    {
      help();
      return 0;
    }
  }

  FILE *texto = fopen(argv[in], "r");
  if (texto == NULL)
  {
    printf("Entrada inválida");
    return 0;
  }

  int nmr_vertices, nmr_arestas;
  fscanf(texto, "%d %d", &nmr_vertices, &nmr_arestas);

  int pai[nmr_vertices];
  int matriz_adj[nmr_vertices][nmr_vertices];
  grafo(nmr_vertices, nmr_arestas, matriz_adj, texto);

  int TOTAL = Prim(nmr_vertices, matriz_adj, pai, initV - 1);

  if (out != 0)
  {
    FILE *saida = fopen(argv[out], "w");
    if (solucao == true)
    {
      for (int i = 0; i < nmr_vertices; i++)
      {
        fprintf(saida, "(%d,%d)\n", pai[i] + 1, i + 1);
      }
    } else{
    	fprintf(saida, "%d\n", TOTAL);
    }
  }
  else
  {
    if (solucao == true)
    {
      for (int i = 0; i < nmr_vertices; i++)
      {
        printf("(%d,%d)\n", pai[i] + 1, i + 1);
      }
    } else{
    	printf("%d\n", TOTAL);
    }
  }

  return 0;
}