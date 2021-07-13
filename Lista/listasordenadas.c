#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
//dinamica ||||| single linkage

//no de lista: chave e ponteiro para proximo
typedef struct NoLista *PtrNoLista;
typedef struct NoLista{
  PtrNoLista proximo;
  int x;
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

//inserir
void inserirListaOrd(ListaOrd *l, int x){
  PtrNoLista novo = (PtrNoLista) malloc(sizeof(NoLista));
  novo->x = x;
  //primeira inserção ou o elemento é menor que o primeiro elemento: cria novo nó, aloca,
  //    copia informação, inicio -> novo -> nulo, qtedelem++
  if(estaVazia(l) || x < l->inicio->x){
    novo->proximo = l->inicio;
    l->inicio = novo;
  } else {
    //segunda inserção: acha a posição de inserção, salva o anterior no aux,
    //                  novo -> aux(prox), aux -> novo, qtdelem++
    PtrNoLista aux;
    for(aux = l->inicio; aux->proximo != NULL; aux = aux->proximo){
      if(x <= aux->proximo->x){
        break;
      }
    }
    novo->proximo = aux->proximo;
    aux->proximo = novo;
  }
  l->qtdElem++;
}
//pesquisar
bool pesquisaListaOrd(ListaOrd *l, int x){
  if(estaVazia(l)){
    printf("Lista vazia\n");
    return 0;
  }
    //percorre a lista com auxiliar
    PtrNoLista aux;
    for(aux = l->inicio; aux->proximo != NULL; aux = aux->proximo){
      if(x == aux->x){
        return 1;
      }
      if (x < aux->x){
        return 0;
      }
    }
  return 0;
}
//remover
//casos possíveis nos slides
int removeListaOrd(ListaOrd *l, int x){
  int a = -99;
  if(estaVazia(l) || x < l->inicio->x){ //A e B
    printf("Esta vazia\n");
    return a;
  }
  if(x == l->inicio->x){ // C
    printf("Retirando primeiro elemento\n");
    PtrNoLista aux;
    aux = l->inicio;
    a = l->inicio->x;
    l->inicio = aux->proximo;
    free(aux);
    l->qtdElem--;
    return a;
  }

  PtrNoLista aux;
  for(aux = l->inicio; aux->proximo != NULL; aux = aux->proximo){
    if(x == aux->x){
      break;
    }
    if(x < aux->x){
      printf("Elemento não achado 2\n");
      return a;
    }
  }
  if(aux->proximo == NULL){
    printf("Elemento não achado 1\n");
    return a;
  } else {
    printf("Elemento achado e removido\n");
    PtrNoLista ant;
    ant = aux->proximo;
    a = aux->x;
    aux->proximo = aux->proximo->proximo;
    l->qtdElem--;
    free(ant);
    return a;
  }
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


//maximo
int maximoListaOrd(ListaOrd *l){
  int a = -99;
  if(!estaVazia(l)){
    PtrNoLista aux;
    for(aux = l->inicio; aux != NULL; aux = aux->proximo){
      if(aux->proximo == NULL){
        a = aux->x;
        break;
      }
    }
  } else {
    printf("Erro maximo lista, lista vazia\n");
  }
  return a;
}

//minimo
int minimoListaOrd(ListaOrd *l){
  int a = -99;
  if(!estaVazia(l)){
    a = l->inicio->x;
  } else {
    printf("Erro minimo lista, lista vazia\n");
  }
  return a;
}

//tamanho
int tamanhoListOrd(ListaOrd *l){
  return l->qtdElem;
}

//proximo
int proximoListaOrd(ListaOrd *l, int x){
  int a = -99;
  if(!estaVazia(l)){
    PtrNoLista aux;
    for(aux = l->inicio; aux != NULL; aux = aux->proximo){
      if(aux->x == x){
        if(aux->proximo == NULL){
          printf("Erro proximo: ultimo elemento da lista\n");
          a = -99;
          break;
        }
        a = aux->proximo->x;
      }
    }
    if(a == -99){
      printf("Erro proximo :elemento não encontrado\n");
    }
  } else {
    printf("Erro proximo, lista vazia\n");
  }
  return a;
}

//anterior
int anteriorListaOrd(ListaOrd *l, int x){
  int a = -99;
  if(!estaVazia(l)){
    PtrNoLista aux;
    for(aux = l->inicio; aux->proximo != NULL; aux = aux->proximo){
      if(aux->x == x && aux == l->inicio){
        printf("Erro anterior, primeiro elemento da lista\n");
        a = -98;
        break;
      }
      if(aux->proximo->x == x){
      a = aux->x;
      }
    }
    if(a == -99){
      printf("Erro anterior :elemento não encontrado\n");
    }
  } else {
    printf("Erro anterior, lista vazia\n");
  }
  return a;
}

//imprimir
void imprimeListaOrd(ListaOrd *l){
  PtrNoLista aux;
  for(aux = l->inicio; aux != NULL; aux = aux->proximo){
    printf("%i\n", aux->x);
  }
}


int main(){
  ListaOrd lista;
  iniciaListaOrd(&lista);

  pesquisaListaOrd(&lista, 5);

  if(estaVazia(&lista)){
    printf("Está vazia\n");
  }
  inserirListaOrd(&lista, 5);
  inserirListaOrd(&lista, 4);
  inserirListaOrd(&lista, 7);
  inserirListaOrd(&lista, 2);
  inserirListaOrd(&lista, 7);

  if(pesquisaListaOrd(&lista, 8)){
    printf("Tem o número 8\n");
  } else {
    printf("Não tem o número 8\n");
  }

  if(pesquisaListaOrd(&lista, 5)){
    printf("Tem o número 5\n");
  } else {
    printf("Não tem o número 5\n");
  }

  printf("Tamanho: %i\n", tamanhoListOrd(&lista));
  imprimeListaOrd(&lista);

  int x = removeListaOrd(&lista, 3);
  printf("Elemento %i\n", x);
  printf("Tamanho: %i\n", tamanhoListOrd(&lista));
  imprimeListaOrd(&lista);

  x = removeListaOrd(&lista, 2);
  printf("Elemento %i\n", x);
  printf("Tamanho: %i\n", tamanhoListOrd(&lista));
  imprimeListaOrd(&lista);

  x = removeListaOrd(&lista, 5);
  printf("Elemento %i\n", x);
  printf("Tamanho: %i\n", tamanhoListOrd(&lista));
  imprimeListaOrd(&lista);

  x = removeListaOrd(&lista, 10);
  printf("Elemento %i\n", x);
  printf("Tamanho: %i\n", tamanhoListOrd(&lista));
  imprimeListaOrd(&lista);

  printf("Elemento minino %i\n", minimoListaOrd(&lista));
  printf("Elemento maximo %i\n", maximoListaOrd(&lista));
  printf("Proximo elemento %i\n", proximoListaOrd(&lista, 4));
  printf("Proximo elemento %i\n", proximoListaOrd(&lista, 7));
  printf("Anterior elemento %i\n", anteriorListaOrd(&lista, 7));
  printf("Anterior elemento %i\n", anteriorListaOrd(&lista, 4));

  destruirListaOrd(&lista);

  if(estaVazia(&lista)){
    printf("Está vazia\n");
  }

  return 0;
}
