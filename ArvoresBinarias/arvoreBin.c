#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct NoArvore * PtrNoArvore;
typedef struct NoArvore{
  int x;
  PtrNoArvore esquerda;
  PtrNoArvore direita;
}NoArvore;

//inicia
void iniciaArvore(PtrNoArvore *node){
  (*node) = NULL;
}

//esta vazia
bool estaVazia(PtrNoArvore *node){
  return(*node == NULL);
}

//insere
bool inserirArvore(PtrNoArvore *node, int x){
  //acha o ponto de inserção
  // cria o nó, aloca memória, copia informação, filhos == NULL
  // retorna true or false (consegue ou não)
  if((*node) == NULL){
    (*node) = (PtrNoArvore) malloc(sizeof(NoArvore));
    (*node)->x = x;
    (*node)->esquerda = NULL;
    (*node)->direita = NULL;
    return (true);
  }

  // se x == node.x , return false
  if((*node)->x == x){
    printf("Erro: elemento já existente\n");
    return (false);
  }

  // achar o percurso com recursão
  if(x > (*node)->x){
    return (inserirArvore(&(*node)->direita,x));
  }
  if(x < (*node)->x){
    return (inserirArvore(&(*node)->esquerda,x));
  }
}

//maximo
PtrNoArvore maximoArvoreBin(PtrNoArvore *node){
  PtrNoArvore aux;
  for(aux = *node; aux->direita != NULL; aux = aux->direita){
  }
  (*node) = (*node)->esquerda;
  return (aux);
}

//minimo
PtrNoArvore minimoArvoreBin(PtrNoArvore *node){
  PtrNoArvore aux;
  for(aux = *node; aux->esquerda != NULL; aux = aux->esquerda){
  }
  (*node) = (*node)->direita;
  return (aux);
}


//remove
bool removeArvore(PtrNoArvore *node, int x){
  if(!estaVazia(node)){
    if(x == (*node)->x){
      PtrNoArvore aux = *node;
      //caso 1: é uma folha
      if((*node)-> direita == NULL && (*node)->esquerda == NULL){
        *node = NULL;
        free(aux);
        return true;
      }
     //caso 2: sub-arvore esquerda nula e direita não
     if((*node)-> direita != NULL && (*node)->esquerda == NULL){
       *node = (*node)->direita;
       free(aux);
       return true;
     }
     //caso 3: o contrário do 2
     if((*node)-> direita == NULL && (*node)->esquerda != NULL){
       *node = (*node)->esquerda;
       free(aux);
       return true;
     }
     //caso 4: nenhuma é nula, vai para a direita
     if((*node)-> direita != NULL && (*node)->esquerda != NULL){
       aux = minimoArvoreBin(&(*node)->direita);
       (*node)->x = aux->x;
       free(aux);
       return true;
     }

    }
    if(x < (*node)->x){
      if((*node)->esquerda == NULL){
        printf("Erro: elemento não achado.\n");
        return false;
      }
      removeArvore(&(*node)->esquerda, x);
    }
    if(x > (*node)->x){
      if((*node)->direita == NULL){
        printf("Erro: elemento não achado\n");
        return false;
      }
      removeArvore(&(*node)->direita, x);
    }
  } else {
    printf("Erro: arvore vazia\n");
    return false;
  }

}

//pesquisa
bool pesquisaArvore(PtrNoArvore * node, int x){
  //pesquisa i item
  if(x == (*node)->x){
    return true;
  }
  if(x < (*node)->x){
    if((*node)->esquerda == NULL){
      printf("Erro: elemento não achado.\n");
      return false;
    }
    pesquisaArvore(&(*node)->esquerda, x);
  }
  if(x > (*node)->x){
    if((*node)->direita == NULL){
      printf("Erro: elemento não achado\n");
      return false;
    }
    pesquisaArvore(&(*node)->direita, x);
  }
}

//destruir
void destruirArvore(PtrNoArvore *node){
  if(*node == NULL) return;
  destruirArvore(&(*node)->esquerda);
  destruirArvore(&(*node)->direita);
  free(*node);
  *node = NULL;
  return;
}

//tamanho
int tamanhoArvoreBin(PtrNoArvore *node){
  if ((*node) == NULL){
    return 0;
  }
  int x = 1;
  if((*node)->esquerda != NULL){
    x += tamanhoArvoreBin(&(*node)->esquerda);
  }
  if((*node)->direita != NULL){
    x += tamanhoArvoreBin(&(*node)->direita);
  }
  return x;
}



//imprimir:
//preOrdem
// imprime valor->recursivo esquerda->recursivo direita;
void imprimePreOrdem(PtrNoArvore *node){
  //percorre recursivamente, imprime os da esquerda, dps da direita
  if((*node) == NULL) return;
  printf("%d ",(*node)->x);
  imprimePreOrdem(&(*node)->esquerda);
  imprimePreOrdem(&(*node)->direita);
}

//posOrdem
// recursivo esquerda -> recursivo direita -> imprime valor
void imprimePosOrdem(PtrNoArvore *node){
  // chama recursiva esquerda, chama recursiva direita, imprime
  if((*node) == NULL) return;
  imprimePosOrdem(&(*node)->esquerda);
  imprimePosOrdem(&(*node)->direita);
  printf("%d ",(*node)->x);
}

//emOrdem
// recursiva esquerda -> imprime -> recursivo direita
void imprimeEmOrdem(PtrNoArvore *node){
  // chama recursiva esquerda, imprime, recursiva direita
  if((*node) == NULL) return;
  imprimeEmOrdem(&(*node)->esquerda);
  printf("%d ",(*node)->x);
  imprimeEmOrdem(&(*node)->direita);
}


int main(){
  //arvore == referencia
  PtrNoArvore raiz;

  iniciaArvore(&raiz);

  if(estaVazia(&raiz)){
    printf("Arvore vazia\n");
  }

  inserirArvore(&raiz, 5);
  inserirArvore(&raiz, 6);
  inserirArvore(&raiz, 7);
  inserirArvore(&raiz, 4);
  inserirArvore(&raiz, 2);
  inserirArvore(&raiz, 3);
  inserirArvore(&raiz, 1);

  printf("Tamanho: %i\n", tamanhoArvoreBin(&raiz));


  if(estaVazia(&raiz)){
    printf("Arvore vazia\n");
  } else {
    printf("Não está vazia\n");
  }

  imprimePreOrdem(&raiz);
  printf("\n");

  imprimePosOrdem(&raiz);
  printf("\n");

  imprimeEmOrdem(&raiz);
  printf("\n");

  if(pesquisaArvore(&raiz, 7)){
    printf("Tem o elemento 7\n");
  } else {
    printf("Não tem o elemento 7\n");
  }

  if(pesquisaArvore(&raiz, 9)){
    printf("Tem o elemento 9\n");
  } else {
    printf("Não tem o elemento 9\n");
  }


  removeArvore(&raiz, 2);
  imprimeEmOrdem(&raiz);
  printf("\n");
  imprimePreOrdem(&raiz);
  printf("\n");

  destruirArvore(&raiz);

  if(estaVazia(&raiz)){
    printf("Arvore vazia\n");
  } else {
    printf("Não está vazia\n");
  }



  imprimeEmOrdem(&raiz);
  printf("\n");


  return 0;
}
