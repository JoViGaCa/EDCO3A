#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*
inicia(s) v
inserir(s,k) v
remover(s,k) v
topo(s)
estaVazia(s) v
destruir(s)
tamanho(s) v
*/

typedef struct NoPilha* PtrNoPilha;

//nódepilha
// chave + ponteiro para o próximo objeto
typedef struct NoPilha{
  int x; //chave
  PtrNoPilha proximo; //ptr do proximo
} NoPilha;


//pilha dinamica
//ptr topo + qtd elem
typedef struct{
  PtrNoPilha topo;
  int qtdElem;
} PilhaDin;

void iniciaPilhaDin(PilhaDin *p){
  //inicia ptr topo nulo e contador = 0
  p->topo = NULL;
  p->qtdElem = 0;
}

int tamanhoPilhaDin(PilhaDin *p){
  return p->qtdElem;
}

bool estaVaziaPilhaDin(PilhaDin *p){
  // ou qtdElem = 0 ou topo = NULL
  return (p->qtdElem == 0);
  //return (p->topo == NULL);
}

void empilhaPilhaDin(PilhaDin *p, int x){
  // ou a pilha está vazia ou não
  // pilha vazia: cria um novo nó e passa os dados certos (topo -> novo nó -> nulo) contador incrementa
  //pilha não vazia: topo -> novo -> antigo(s) - > nulo --- contador + 1
  // como é o mesmo esquema é possível fazer sem seleção
  PtrNoPilha aux = (PtrNoPilha) malloc(sizeof(PtrNoPilha));
  aux->x = x;
  aux->proximo = p->topo;
  p->topo = aux;
  p->qtdElem++;
}

void imprimePilhaDin(PilhaDin *p){
  //começa no topo e vai indo
  PtrNoPilha temp;
  for(temp = p->topo; temp != NULL; temp = temp->proximo){
    printf("%d ", temp->x);
  }
}

int desempilhaPillhaDin(PilhaDin *pd){
  //valor de controle
  int v = -99;
  if(!estaVazia(pd)){
    //ponteiro auxiiar
    PtrNoPilha aux = (PtrNoPilha) malloc(sizeof(PtrNoPilha));
    //ptr recebe o valor do topo
    aux = pd->topo;
    //copia o dado para ser retornado
    v = aux->x;
    //atualiza ponteiros
    pd->topo = pd->topo->proximo;
    //desaloca memoria
    free(aux);
    //decrementa contador
    pd->qtdElem--;
  } else {
    printf("Warning!! Pilha vazia\n");
  }
  return (v);
}

//topo
int topoPilhaDin(PilhaDin *pd){
  int x = -99;

  //verifica se esta vazia
  if(!estaVazia(pd)){
    x = pd->topo->x;
  } else {
    printf("Erro: pilha vazia\n");
  }
  return x;
}

//destruir
void destruirPilhaDin(PilhaDin *pd){
  if(!estaVazia(pd)){
    //auxiliar para ajudar
    PtrNoPilha des;
    //estrutura de repetição para destruir
    for(des = pd->topo; des != NULL; des = pd->topo){
      pd->topo = des->proximo;
      free(des);
      pd->qtdElem--;
    }
  } else{
    printf("Erro: pilha vazia\n");
  }
}

int main(int argc, const char * argv[]){
  PilhaDin pilha;

  iniciaPilhaDin(&pilha);

  printf("%i\n", tamanhoPilhaDin(&pilha));

  if(estaVazia(&pilha)){
    printf("Está vazia\n");
  } else {
    printf("Não está vazia\n");
  }

  empilhaPilhaDin(&pilha, 3);
  empilhaPilhaDin(&pilha, 4);
  empilhaPilhaDin(&pilha, 5);
  empilhaPilhaDin(&pilha, 6);
  empilhaPilhaDin(&pilha, 7);
  empilhaPilhaDin(&pilha, 8);

  imprimePilhaDin(&pilha);

  printf("\n%i\n", tamanhoPilhaDin(&pilha));

  printf("Valor do topo: %i\n", topoPilhaDin(&pilha));

  printf("Elemento do topo = %i\n", desempilhaPillhaDin(&pilha));
  printf("Valor do topo: %i\n", topoPilhaDin(&pilha));

  printf("Elemento do topo = %i\n", desempilhaPillhaDin(&pilha));
  printf("Valor do topo: %i\n", topoPilhaDin(&pilha));

  printf("Elemento do topo = %i\n", desempilhaPillhaDin(&pilha));
  printf("Valor do topo: %i\n", topoPilhaDin(&pilha));

  printf("Elemento do topo = %i\n", desempilhaPillhaDin(&pilha));
  printf("Valor do topo: %i\n", topoPilhaDin(&pilha));

  destruirPilhaDin(&pilha);
  printf("Tamanho da pilha = %i\n", tamanhoPilhaDin(&pilha));
  printf("%p\n", pilha.topo);

  return 0;
}
