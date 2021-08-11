#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct NoArvoreAvl * PtrNoArvoreAvl;
typedef struct NoArvoreAvl{
  int x;
  PtrNoArvoreAvl esquerda;
  PtrNoArvoreAvl direita;
  int altura;
}NoArvoreAvl;

//inicia
void iniciaArvoreAvl(PtrNoArvoreAvl *node){
  (*node) = NULL;
}

//esta vazia
bool estaVazia(PtrNoArvoreAvl *node){
  return(*node == NULL);
}

int alturaArvoreAVL(PtrNoArvoreAvl node) {
  if(node == NULL) {
    return (0);
  } else {
    return ((node)->altura);
  }
}

//imprimir:
//preOrdem
// imprime valor->recursivo esquerda->recursivo direita;
void imprimePreOrdemAvl(PtrNoArvoreAvl *node){
  //percorre recursivamente, imprime os da esquerda, dps da direita
  if((*node) == NULL) return;
  printf("%d ",(*node)->x);
  imprimePreOrdemAvl(&(*node)->esquerda);
  imprimePreOrdemAvl(&(*node)->direita);
}

//destruir
void destruirArvoreAvl(PtrNoArvoreAvl *node){
  if(*node == NULL) return;
  destruirArvoreAvl(&(*node)->esquerda);
  destruirArvoreAvl(&(*node)->direita);
  free(*node);
  *node = NULL;
  return;
}

//pesquisa
bool pesquisaArvoreAvl(PtrNoArvoreAvl *node, int valor){
  //caso falso
  if((*node) == NULL){
    return false;
  }
  //caso verdadeiro
  if((*node)->x == valor){
    return true;
  }
  //navegação recursiva
  if((*node)->x > valor){
    return(pesquisaArvoreAvl(&(*node)->esquerda, valor));
  } else {
    return(pesquisaArvoreAvl(&(*node)->direita, valor));
  }

}

int atualizaAlturaAvl(PtrNoArvoreAvl esq,PtrNoArvoreAvl dir){
  int ae = alturaArvoreAVL(esq);
  int ad = alturaArvoreAVL(dir);
  if(ae > ad){
    return (ae+1);
  } else {
    return (ad+1);
  }

}
void rotacaoSimplesEsquerda(PtrNoArvoreAvl* node){
  PtrNoArvoreAvl u = (*node)->direita;
  (*node)->direita = u->esquerda;
  u->esquerda = (*node);
  (*node)->altura = 0;

  (*node)->altura = atualizaAlturaAvl((*node)->esquerda, (*node)->direita);
  u->altura = atualizaAlturaAvl(u->esquerda, u->direita);

  (*node) = u;
}

void rotacaoSimplesDireita(PtrNoArvoreAvl* node){
  PtrNoArvoreAvl u = (*node)->esquerda;
  (*node)->esquerda = u->direita;
  u->direita = (*node);
  (*node)->altura = 0;

  (*node)->altura = atualizaAlturaAvl((*node)->esquerda, (*node)->direita);
  u->altura = atualizaAlturaAvl(u->esquerda, u->direita);

  (*node) = u;
}

void rotacaoDuplaEsquerda(PtrNoArvoreAvl* node){
  PtrNoArvoreAvl u, v;
  u = (*node)->direita;
  v = u->esquerda;
  (*node)->direita = v->esquerda;
  u->esquerda = v->direita;
  v->direita = u;
  v->esquerda = (*node);

  (*node)->altura = atualizaAlturaAvl((*node)->esquerda,(*node)->direita);
  u->altura = atualizaAlturaAvl(u->esquerda,u->direita);
  v->altura = atualizaAlturaAvl(v->esquerda,v->direita);

  (*node) = v;

}

void rotacaoDuplaDireita(PtrNoArvoreAvl* node){
  PtrNoArvoreAvl u, v;
  u = (*node)->esquerda;
  v = u->direita;
  (*node)->esquerda = v->direita;
  u->direita = v->esquerda;
  v->esquerda = u;
  v->direita = (*node);

  (*node)->altura = atualizaAlturaAvl((*node)->esquerda,(*node)->direita);
  u->altura = atualizaAlturaAvl(u->esquerda,u->direita);
  v->altura = atualizaAlturaAvl(v->esquerda,v->direita);

  (*node) = v;

}


void aplicarRotacoesAvl(PtrNoArvoreAvl* node){
  int ae = alturaArvoreAVL((*node)->esquerda);
  int ad = alturaArvoreAVL((*node)->direita);
  int diferenca = ad - ae;

  if(diferenca == 2){
   PtrNoArvoreAvl temp = (*node)->direita;
   int tempAE = alturaArvoreAVL(temp->esquerda);
   int tempAD = alturaArvoreAVL(temp->direita);

   if(tempAD > tempAE){
    rotacaoSimplesEsquerda(&(*node));
   } else {
    rotacaoDuplaEsquerda(&(*node));
   }
  } else {
    PtrNoArvoreAvl temp = (*node)->esquerda;
    int tempAE = alturaArvoreAVL(temp->esquerda);
    int tempAD = alturaArvoreAVL(temp->direita);

    if(tempAE > tempAD){
     rotacaoSimplesDireita(&(*node));
    } else {
     rotacaoDuplaDireita(&(*node));
    }

  }


}


bool inserirArvoreAvl(PtrNoArvoreAvl *node, int x){
   //criterio de parada (posiçaõ == NULL)
   if((*node) == NULL){
     (*node) = (PtrNoArvoreAvl) malloc (sizeof(NoArvoreAvl));
     (*node)->direita = (*node)->esquerda = NULL;
     (*node)->x = x;
     (*node)->altura = 1;
     return true;
   }
   //se já houver o elemento, não faz nada
   if((*node)->x == x){
     return false;
   }

   bool inseriu;
   if(x > (*node)->x){
     inseriu = inserirArvoreAvl(&(*node)->direita,x);
   } else {
     inseriu = inserirArvoreAvl(&(*node)->esquerda,x);
   }

   //se não inseriu, retorna falso
   if(inseriu == false) return false;

   //se inseriu, fazer o lance do indice
   int alturaesq, alturadir;
   alturadir = alturaArvoreAVL((*node)->direita);
   alturaesq = alturaArvoreAVL((*node)->esquerda);

   //identifica desbalanceamento
   if((alturadir-alturaesq) == 2 ||(alturadir-alturaesq) == -2){
     //aplicar rotações
     aplicarRotacoesAvl(&(*node));
   }

  (*node)->altura = atualizaAlturaAvl((*node)->direita, (*node)->esquerda);

  return true;
}



int main(){
  PtrNoArvoreAvl raiz;
  iniciaArvoreAvl(&raiz);

  inserirArvoreAvl(&raiz, 77);
  imprimePreOrdemAvl(&raiz);
  printf("\n");

  inserirArvoreAvl(&raiz, 12);
  imprimePreOrdemAvl(&raiz);
  printf("\n");

  inserirArvoreAvl(&raiz, 10);
  imprimePreOrdemAvl(&raiz);
  printf("\n");

  inserirArvoreAvl(&raiz, 5);
  imprimePreOrdemAvl(&raiz);
  printf("\n");

  inserirArvoreAvl(&raiz, 7);
  imprimePreOrdemAvl(&raiz);
  printf("\n");

  inserirArvoreAvl(&raiz, 80);
  imprimePreOrdemAvl(&raiz);
  printf("\n");

  inserirArvoreAvl(&raiz, 78);
  imprimePreOrdemAvl(&raiz);
  printf("\n");


  return 0;
}
