#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define TAMANHO 5

/*
inicia(s) v
inserir(s,k) v
remover(s,k) v
topo(s) v
estaVazia(s) v
estaCheia(s) v
tamanho(s) v
*/

//tipo basico
typedef struct{
  int array[TAMANHO];
  int topo;
  int qtdElem;
}PilhaEst;

//inicializar a pilha
void iniciaPilhaEst(PilhaEst *p){
   //inicia topo em zero
   p->topo = 0;
   //inicia a quantidade em 0
   p->qtdElem = 0;
}

//esta vazia
bool estaVaziaPilhaEst(PilhaEst *p){
  //esta vazia se topo igual a zero
  return (p->topo == 0);
}

//esta cheia
bool estaCheiaPilhaEst(PilhaEst *p){
  //esta cheia se topo igual a TAMANHO
  return(p->topo == TAMANHO);
}

//verifica tamanho
int tamanhoPilhaEst(PilhaEst *p){
   //retorna a quantidade de elementos
  return p->qtdElem;
}

//inserir um elemento
void empilhaPilhaEst(PilhaEst *p, int x){
  //quando a pilha se estiver cheia
  //insere um elemento no topo e aumenta um no topo, e a quantidade de elemento
  if(!estaCheia(p)){
    p->array[p->topo] = x;
    p->topo++;
    p->qtdElem++;
  } else{
    printf("Erro: pilha está cheia, não é possível inserir\n");
  }
}

// visualiza pilha estatica
void imprimePilhaEst(PilhaEst *p){
   for(int i = 0; i < p->topo; i++){
     printf("%i ", p->array[i]);
   }
   printf("\n");
}

//desempilha
int desempilhaPilhaEst(PilhaEst *p){
  int x = -99; //valor de controle
  //verifica se a pilha não estiver vazia
  if(!estaVazia(p)){
    //tira o último elemento e decrementa topo e qtdElem
    x = p->array[p->topo-1];
    p->topo--;
    p->qtdElem--;
  } else {
    printf("Erro: pilha vazia\n");
  }
  return (x);
}

//remove
void removerPilhaEst(PilhaEst *p, int x){
  if(!estaVazia(p)){
    //estrutura de repetição para percorrer a pilha
    for(int i = 0; i < p->topo; i++){
      //verifica se o elemento é igual ao que se quer
      if(p->array[i] == x){
        //estrutura de repetição para retirar o elemento e atualizar o array
        for(int j = i; j < p->topo; j++){
          p->array[j] = p->array[j+1];
        }
        //decrementar topo e qtdelementos
        p->topo--;
        p->qtdElem--;
      }
    }
  } else{
    printf("Erro: pilha vazia\n");
  }
}

//retorna topo
int topoPilhaEst(PilhaEst *p){
  //valor auxiliar
  int x = -99;
  //verifica se esta vazia
  if(!estaVazia(p)){
    x = p->array[p->topo - 1];
  } else{
    printf("Erro: pilha vazia\n");
  }
  return x;
}

int main(){
  PilhaEst pilha;

  iniciaPilhaEst(&pilha);

  if(estaVazia(&pilha)){
    printf("Esta vazia\n");
  }

  if(estaCheia(&pilha)){
    printf("Esta cheia\n");
  }


  empilhaPilhaEst(&pilha, 4);
  empilhaPilhaEst(&pilha, 76);
  empilhaPilhaEst(&pilha, 34);
  empilhaPilhaEst(&pilha, 52);
  empilhaPilhaEst(&pilha, 35);

  imprimePilhaEst(&pilha);

  printf("Tamanho = %d\n", tamanhoPilhaEst(&pilha));

  printf("Retirar um elemento: %d\n", desempilhaPilhaEst(&pilha));

  imprimePilhaEst(&pilha);

  removerPilhaEst(&pilha, 76);

  imprimePilhaEst(&pilha);
  printf("Tamanho = %d\n", tamanhoPilhaEst(&pilha));

  printf("Valor do topo = %i\n", topoPilhaEst(&pilha));

  printf("Hello World!\n");

  return 0;
}
