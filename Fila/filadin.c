#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct NoFila *PtrNoFila;

//No fila: informação + ptr
typedef struct NoFila{
  int x;  //informação
  PtrNoFila proximo; // ptr proximo
} NoFila;

//fila dinamica: inicio _ fim + qtd elementos
typedef struct{
  PtrNoFila inicio; // ptr 1° elemento
  PtrNoFila fim; // ptr ultimo elemento
  int qtdElem;
} FilaDin;


//inicia
void iniciaFilaDin(FilaDin *fl){
  fl->inicio = NULL;
  fl->fim = NULL;
  fl->qtdElem = 0;
}

//estaVazia
bool estaVazia(FilaDin *fl){
  return(fl->qtdElem == 0);
  // fl->inicio == 0;
}

//inserir
void insereFilaDin(FilaDin *fl, int x){
  //primeira inserção: cria variavel auxiliar, aloca memória, copia informação
  PtrNoFila aux;
  aux = (PtrNoFila) malloc(sizeof(NoFila));
  aux->x = x;
  if(estaVazia(fl)){
  //   inicio e fim apuntam para novo, novo aponta para num, qtd++;
  fl->fim = aux;
  fl->inicio = aux;
  aux->proximo = NULL;
} else {
  //   proximo do novo aponta para null, prox fim aponta para novo elemento, fim recebe proximo fim, qtd++
  aux->proximo = fl->fim->proximo; //NULL
  fl->fim->proximo = aux;
  fl->fim = fl->fim->proximo;
  }
  fl->qtdElem++;
}


//Retirar
int removeFilaDin(FilaDin *fl){
  int x = -999;
  //ptr auxiliar, copia informação, atualiza inicio, desaloca mem aux, decrementa qtd
  if(!estaVazia(fl)){
    PtrNoFila aux;
    aux = fl->inicio;
    x = aux->x;
    fl->inicio = fl->inicio->proximo;
    free(aux);
    fl->qtdElem--;
  } else {
    printf("Erro: fila vazia, não pode retirar\n");
  }

  return x;
}

//tamanho
int tamanhoFilaDin(FilaDin* fl){
  return(fl->qtdElem);
}

//imprime
void imprimeFilaDin(FilaDin *fl){
  //começa no topo e vai indo
  PtrNoFila temp;
  for(temp = fl->inicio; temp != NULL; temp = temp->proximo){
    printf("%d ", temp->x);
  }
  printf("\n");
}

//primeiro
int primeiroFilaDin(FilaDin *f){
  int a = -99;
  if(!estaVazia(f)){
    a = f->inicio->x;
  } else {
    printf("Erro no primeiro elemento, fila vazia\n");
  }
  return a;
}
//ultimo
int ultimoFilaFin(FilaDin *f){
  int a = -99;
  if(!estaVazia(f)){
    a = f->fim->x;
  } else {
    printf("Erro no ultimo elemento: fila vazia\n");
  }
  return a;
}

//destruir
void destruirFilaDin(FilaDin *f){
  PtrNoFila aux;
  if(!estaVazia(f)){
    for(aux = f->inicio; aux != NULL; aux = f->inicio){
      f->inicio = f->inicio->proximo;
      free(aux);
      f->qtdElem--;
    }
  } else {
    printf("Erro o destruir: fila vazia\n");
  }
}



int main(){
  FilaDin fila;

  iniciaFilaDin(&fila);

  insereFilaDin(&fila, 5);
  insereFilaDin(&fila, 6);
  insereFilaDin(&fila, 4);


  if(estaVazia(&fila)){
    printf("Esta vazia\n");
  } else {
    printf("Não esta vazia\n");
  }
  imprimeFilaDin(&fila);
  printf("Tamanho = %i\n", tamanhoFilaDin(&fila));

  int x = removeFilaDin(&fila);
  imprimeFilaDin(&fila);
  printf("Tamanho = %i\n", tamanhoFilaDin(&fila));
  int y = removeFilaDin(&fila);
  imprimeFilaDin(&fila);
  printf("Tamanho = %i\n", tamanhoFilaDin(&fila));
  int z = removeFilaDin(&fila);
  imprimeFilaDin(&fila);
  printf("Tamanho = %i\n", tamanhoFilaDin(&fila));
  int a = removeFilaDin(&fila);

  insereFilaDin(&fila, 5);
  insereFilaDin(&fila, 6);
  insereFilaDin(&fila, 4);
  printf("Primeiro elemento: %i\n", primeiroFilaDin(&fila));
  printf("Último elemento: %i\n", ultimoFilaFin(&fila));

  destruirFilaDin(&fila);

  if(estaVazia(&fila)){
    printf("Esta vazia\n");
  } else {
    printf("Não esta vazia\n");
  }

  return 0;
}
