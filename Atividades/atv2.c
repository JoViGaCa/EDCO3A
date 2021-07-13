/**
* @file atv2.c
* @author João Carvalho
* @date 12 07 2021
* @brief Resoluçao da ativade prática 2
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

//no de lista: chave, ponteiro para proximo, anterior, id, nome, sexo, peso e altura
typedef struct NoLista *PtrNoLista;
typedef struct NoLista{
  int id;
  char nome[21];
  char sexo;
  float peso;
  int altura;
  PtrNoLista proximo;
  PtrNoLista anterior;
}NoLista;

//tipo lista: ponteiro inicio + qtdelem
typedef struct{
  PtrNoLista inicio;
  int qtdElem;
}ListaOrd;

//inicializar
void iniciaListaOrd(ListaOrd *l){
  l->inicio = NULL;
  l->qtdElem = 0;
}

//estaVazia
bool estaVazia(ListaOrd *l){
  return(l->inicio == NULL);
}

void inserirListaOrd(ListaOrd *l, int id, char* nome, char sexo, float peso, int altura){
  PtrNoLista novo = (PtrNoLista) malloc(sizeof(NoLista));
  //primeira inserção ou o elemento é menor que o primeiro elemento: cria novo nó, aloca,
  //    copia informação, inicio -> novo -> nulo, qtedelem++
  if(estaVazia(l)){
    novo->proximo = l->inicio;
    novo->anterior = l->inicio;
    l->inicio = novo;
    novo->id = id;
    strcpy(novo->nome,nome);
    novo->sexo = sexo;
    novo->peso = peso;
    novo->altura = altura;
  } else {
    //segunda inserção: acha a posição de inserção, salva o anterior no aux,
    //                  novo -> aux(prox), aux -> novo, qtdelem++
    PtrNoLista aux;
    for(aux = l->inicio; aux->proximo != NULL; aux = aux->proximo){
      if(id <= aux->proximo->id){
        break;
      }
    }
    novo->proximo = aux->proximo;
    aux->proximo = novo;
    novo->anterior = aux;
    novo->id = id;
    strcpy(novo->nome,nome);
    novo->sexo = sexo;
    novo->peso = peso;
    novo->altura = altura;
  }
  l->qtdElem++;
}


//tamanho
int tamanhoListOrd(ListaOrd *l){
  return l->qtdElem;
}

//imprimir crescente
void imprimeListaOrdC(ListaOrd *l, FILE *arqs){
  PtrNoLista aux;
  for(aux = l->inicio; aux != NULL; aux = aux->proximo){
    fprintf(arqs,"%i %s %c %f %i\n", aux->id, aux->nome, aux->sexo, aux->peso, aux->altura);
  }
}

//imprimir decrescente
//    percorrer até o último e ir do ultimo até o primeiro
void imprimeListaOrdD(ListaOrd *l, FILE *arqs){
  PtrNoLista aux;
  for(aux = l->inicio; aux->proximo != NULL; aux = aux->proximo){
  }
  //trabalhar com uma variavel i auxiliar
  for(int i = 0; i < l->qtdElem; i++){
    fprintf(arqs,"%i %s %c %f %i\n", aux->id, aux->nome, aux->sexo, aux->peso, aux->altura);
    aux = aux->anterior;
  }
}

//pesquisar
bool pesquisaListaOrd(ListaOrd *l, int x, FILE *arqs){
  if(estaVazia(l)){
    printf("Lista vazia\n");
    return 0;
  }
    //percorre a lista com auxiliar
    PtrNoLista aux;
    for(aux = l->inicio; aux->proximo != NULL; aux = aux->proximo){
      if(x == aux->id){
        fprintf(arqs,"%i %s %c %f %i\n", aux->id, aux->nome, aux->sexo, aux->peso, aux->altura);
        return 1;
      }
      if (x < aux->id){
        printf("Erro, id requisitado não achado\n");
        return 0;
      }
    }
  return 0;
}

//destruir
void destruirListaOrd(ListaOrd *l){
  if(!estaVazia(l)){
    PtrNoLista aux;
    for(aux = l->inicio; aux != NULL; aux = l->inicio){
      l->inicio = l->inicio->proximo;
      free(aux);
      l->qtdElem--;
    }
  } else{
    printf("Erro destruir lista vazia\n");
  }
}


int main(int argc, const char * argv[]){

  if(argc != 3){
    printf("Erro na sintaxe, argumentos não corretos\n");
    exit(1);
  }

  //receber os arquivos do argc
  FILE *arqe = fopen(argv[1], "r"); //ARQuivo de Entrada
  FILE *arqs = fopen(argv[2], "w"); //ARQuivo de Saida
  if(!arqe || !arqs){
    printf("Erro na abertura dos arquivos\n");
    exit(1);
  }

  //cria e inicia a lista
  ListaOrd lista;
  iniciaListaOrd(&lista);

  //cria as variáveis para copiar do arquivo
  int id;
  char nome[21];
  char sexo;
  float peso;
  int altura;
  //opção que quer
  int opcao;
  while (fscanf(arqe,"{%d,%s ,%c,%f,%d}\n", &id, nome, &sexo, &peso, &altura) == 5){
    inserirListaOrd(&lista, id, nome, sexo, peso, altura); //insere na lista

  }


  //reajusta o ponteiro do arquivo para ler a opção, caso der erro ele mostra
  fseek(arqe,-2,SEEK_CUR);
  if(fscanf(arqe,"%d\n", &opcao)!= 1){
    printf("Erro, não há opção\n");
  }


  //variavel auxiliar para opção 3
  int id_aux = 0;
  switch (opcao) {
    case 1:
      imprimeListaOrdC(&lista, arqs);
      break;
    case 2:
      imprimeListaOrdD(&lista, arqs);
      break;
    case 3:
      fscanf(arqe,"\n%i",&id_aux);
      pesquisaListaOrd(&lista, id_aux, arqs);
      break;
  }

  destruirListaOrd(&lista);

  fclose(arqe);
  fclose(arqs);
  return 0;
}
