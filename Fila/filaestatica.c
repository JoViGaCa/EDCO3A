#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define TAMANHO 5

//Estrutura: tamanho fixo, array, inicio e fim, contador
typedef struct{
  int inicio;
  int fim;
  int array[TAMANHO];
  int qtdElem;
} FilaEst;

//incrementa indice
int incrementaIndice(int i){
  int x =   (i + 1) % TAMANHO;
  return x;
}

//inicia
void iniciaFilaEst(FilaEst *fl){
  fl->qtdElem = 0;
  fl->inicio = 0;
  fl->fim = -1;
}

//estaVazia
bool estaVazia(FilaEst *fl){
  return(fl->qtdElem == 0);
  //fim == -1
}

//estaCheia
bool estaCheia(FilaEst *fl){
  return(fl->qtdElem == TAMANHO);
  //fim == TAMANHO -1
}

//adiciona no começo
void adicionaFilaEst(FilaEst *fl, int x){
  //incrementa fim, adiciona elemento, incrementa qtdElem
  if(!estaCheia(fl)){
    fl->fim = incrementaIndice(fl->fim);
    fl->array[fl->fim] = x;
    fl->qtdElem++;

  } else {
    printf("Erro: fila cheia\n");
  }

}

//remove do final
int removeFilaEst(FilaEst *fl){
  int x; // variavel retorno
  if(!estaVazia(fl)){
    //armazena o valor do primeiro em x, incrementa inicio, decrementa qtdElem
    x = fl->array[fl->inicio];
    fl->inicio = incrementaIndice(fl->inicio);
    fl->qtdElem--;
  } else {
    printf("Erro: fila vazia\n");
  }

  return x;
}

//primeiro
int primeiroFilaEst(FilaEst *f){
  //variavel de retorno e controle
  int a = -99;
  if(!estaVazia(f)){
    a = f->array[f->inicio];
  } else{
    printf("Erro: fila vazia\n");
  }
  return a;
}
//ultimo
int ultimoFilaEst(FilaEst *f){
  //variavel de retorno e controle
  int a = -99;
  if(!estaVazia(f)){
    a = f->array[f->fim];
  } else {
    printf("Erro: fila vazia\n");
  }
  return a;
}

//tamanho
int tamanhoFilaEst(FilaEst * fl){
  return (fl->qtdElem);
}

void imprimeFilaEst(FilaEst *fl){
  printf("{ ");
  for(int i = 0; i < fl->qtdElem; i++){
    int indice = (fl->inicio + i) % TAMANHO;
    printf("%i ", fl->array[indice]);
  }
  printf("}\n");
}

int main(){
  FilaEst fila;

  iniciaFilaEst(&fila);

  if(estaVazia(&fila)){
    printf("Está vazia\n");
  }
  if(!estaCheia(&fila)){
    printf("Não está cheia\n");
  }
  adicionaFilaEst(&fila, 3);
  adicionaFilaEst(&fila, 54);
  int x = removeFilaEst(&fila);
  imprimeFilaEst(&fila);
  printf("Primeiro elemento: %i\n", primeiroFilaEst(&fila));
  printf("Último elemento: %i\n", ultimoFilaEst(&fila));
  printf("Tamnho: %i\n", tamanhoFilaEst(&fila));
  adicionaFilaEst(&fila, 345);
  adicionaFilaEst(&fila, 65);
  adicionaFilaEst(&fila, 75);
  imprimeFilaEst(&fila);
  printf("Tamnho: %i\n", tamanhoFilaEst(&fila));
  int y = removeFilaEst(&fila);
  printf("Primeiro elemento: %i\n", primeiroFilaEst(&fila));
  printf("Último elemento: %i\n", ultimoFilaEst(&fila));
  adicionaFilaEst(&fila, 754);
  adicionaFilaEst(&fila, 4);
  imprimeFilaEst(&fila);
  printf("Tamnho: %i\n", tamanhoFilaEst(&fila));


  imprimeFilaEst(&fila);
  printf("Tamnho: %i\n", tamanhoFilaEst(&fila));


  printf("X = %i\nY = %i\n", x, y);
  imprimeFilaEst(&fila);
  printf("Tamnho: %i\n", tamanhoFilaEst(&fila));

  printf("Primeiro elemento: %i\n", primeiroFilaEst(&fila));
  printf("Último elemento: %i\n", ultimoFilaEst(&fila));

  return 0;
}
