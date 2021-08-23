#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

typedef struct NoArvoreAvl * PtrNoArvoreAvl;
typedef struct NoArvoreAvl{
  int x;
  PtrNoArvoreAvl esquerda;
  PtrNoArvoreAvl direita;
  int altura;
  int tamanho;
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

//salva a arvore no arquivo de saida
void imprimeArqAvl(PtrNoArvoreAvl *node, FILE * arq_s, int tamanho){
  if((*node) == NULL) return;
  if((*node)->tamanho == tamanho){
    //salva apenas aqueles com o tamanho indicado
    int alt_dir = alturaArvoreAVL((*node)->direita);
    int alt_esq = alturaArvoreAVL((*node)->esquerda);
    //percorre recursivamente, imprime os da esquerda, dps da direita
    if((*node) == NULL) return;
    fprintf(arq_s, "%d (%i) ",(*node)->x, (alt_dir - alt_esq));
  }
  imprimeArqAvl(&(*node)->esquerda, arq_s, tamanho);
  imprimeArqAvl(&(*node)->direita, arq_s, tamanho);
}

void imprimePreOrdemAvl(PtrNoArvoreAvl *node){
  //percorre recursivamente, imprime os da esquerda, dps da direita
  if((*node) == NULL) return;
  printf("%d (%i)",(*node)->x, (*node)->tamanho);
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

// atualiza na inserção
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

  (*node)->altura = atualizaAlturaAvl((*node)->esquerda, (*node)->direita);
  u->altura = atualizaAlturaAvl(u->esquerda, u->direita);

  (*node) = u;
}

void rotacaoSimplesDireita(PtrNoArvoreAvl* node){
  PtrNoArvoreAvl u = (*node)->esquerda;
  (*node)->esquerda = u->direita;
  u->direita = (*node);

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

//aplica nas inserções
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

  (*node)->altura = atualizaAlturaAvl((*node)->esquerda, (*node)->direita);

  return true;
}

//menor elemento sub-arvore direita
PtrNoArvoreAvl menorElemDir(PtrNoArvoreAvl *node){
  PtrNoArvoreAvl menor;
  if ((*node)->esquerda != NULL){
    menor = menorElemDir(&(*node)->esquerda);
  } else {
    menor = (*node);
    (*node) = (*node)->direita;
  }
  return menor;
}

//maior elemento sub-arvore esquerda
PtrNoArvoreAvl maiorElemEsq(PtrNoArvoreAvl *node){
  PtrNoArvoreAvl maior;
  if ((*node)->direita != NULL){
    maior = maiorElemEsq(&(*node)->direita);
  } else {
    maior = (*node);
    (*node) = (*node)->esquerda;
  }
  return maior;
}


//remover
bool removeAvl(PtrNoArvoreAvl *node,int x, char estilo){
  if((*node) == NULL){
    printf("Erro, elemento não achado\n");
    return false;
  }

  if((*node)->x == x){
    //se é folha
    if((*node)->esquerda == NULL && (*node)->direita == NULL){
      PtrNoArvoreAvl temp = (*node);
      (*node) = NULL;
      free(temp);
      return true;
    }
    //se arvore esquerda é nula
    if((*node)->esquerda == NULL && (*node)->direita != NULL){
      PtrNoArvoreAvl temp = (*node);
      (*node) = (*node)->direita;
      free(temp);
      return true;
    }
    //se arvore da direita é nula
    if((*node)->direita == NULL && (*node)->esquerda != NULL){
      PtrNoArvoreAvl temp = (*node);
      (*node) = (*node)->esquerda;
      free(temp);
      return true;
    }
    //nenhum dos casos a cima
    if((*node)->direita != NULL && (*node)->esquerda != NULL){
      PtrNoArvoreAvl temp;
      if(estilo == 'd' || estilo == 'D'){
        temp = menorElemDir(&(*node)->direita);
      }
      if (estilo == 'e' || estilo == 'E'){
        temp = maiorElemEsq(&(*node)->esquerda);
      } else {
        printf ("Erro, não específicado estilo\n");
        exit(1);
      }
      (*node)->x = temp->x;
      free(temp);
      return true;
    }
  }

  bool remover;
  //chamadas recursivas
  if(x > (*node)->x){
    remover = removeAvl(&(*node)->direita, x, estilo);
  } else {
    remover = removeAvl(&(*node)->esquerda, x, estilo);
  }

  //ajustar arvore
  if(remover == false){
    return false;
  }

  int alt_esq = alturaArvoreAVL((*node)->esquerda);
  int alt_dir = alturaArvoreAVL((*node)->direita);

  if((alt_dir - alt_esq) == 2 || (alt_dir - alt_esq) == -2){
    aplicarRotacoesAvl(&(*node));
  }

  (*node)->altura = atualizaAlturaAvl((*node)->esquerda,(*node)->direita);

  return true;
}

//atualiza os tamanhos de cada node
int atualizaTamanhoAvl(PtrNoArvoreAvl *node){
  if((*node) == NULL){
    return 0;
  }
  int te = atualizaTamanhoAvl(&(*node)->esquerda);
  int td = atualizaTamanhoAvl(&(*node)->direita);
  if(td > te){
    (*node)->tamanho = td +1;
  } else {
    (*node)->tamanho = te + 1;
  }
  return ((*node)->tamanho);
}




int main(int argc, const char * argv[]){
  if(argc != 3){
    printf("Erro, argumentos inválidos\n");
    exit(1);
  }

  //abre os arquivos
  FILE *arq_e = fopen(argv[1],"r"); //arquivo de entrada
  FILE *arq_s = fopen(argv[2],"w"); // arquivo de saida

  if(!arq_e || !arq_s){
    printf("Erro na abertura dos arquivos\n");
    exit(1);
  }

  //cria a arvore
  PtrNoArvoreAvl raiz;
  iniciaArvoreAvl(&raiz);

  //string que armazena os numeros
  char numeros[50];
  fscanf(arq_e, "%s", numeros);
  //divide a string pela virgula, converte para inteiro e armazena na arvore
  char *num = strtok(numeros, ",");
  while (num){
    int x = atoi(num);
    inserirArvoreAvl(&raiz,x);
    num = strtok(NULL, ",");
  }





  //acha os numeros que devem ser removidos e coloca em um vetor
  int remover[15];
  int i = 0;
  fscanf(arq_e, "%s", numeros);
  num = strtok(numeros, ",");
  while (num){
    int x = atoi(num);
    remover[i] = x;
    i++;
    num = strtok(NULL, ",");
  }


  // acha o estilo de rotação
  char estilo; // qual forma será aplicada
  fscanf(arq_e, "\n%c", &estilo);

  if(estilo != 'e' && estilo != 'E'  && estilo != 'd' && estilo != 'D'){
    fprintf(arq_s, "Arquivo inválido\n");
    printf("Arquivo inválido\n");
    exit(1);
  }


  //salva no arquivo o formato de antes
  atualizaTamanhoAvl(&raiz);
  fprintf(arq_s,"*Antes:\n");
  //salva os nodes em ordem decrescente de tamanho
  for(int i = raiz->tamanho; i > 0; i--){
    imprimeArqAvl(&raiz,arq_s, i);
    fprintf(arq_s, "\n");
  }
  fprintf(arq_s,"\n\n");


  //remove os numeros
  for(int j = 0; j < i; j++){
    removeAvl(&raiz, remover[j], estilo);
  }



  //salva no arquivo o formato de depois
  atualizaTamanhoAvl(&raiz);
  fprintf(arq_s,"*Depois:\n");
  for(int i = raiz->tamanho; i > 0; i--){
    imprimeArqAvl(&raiz,arq_s, i);
    fprintf(arq_s, "\n");
  }
  fprintf(arq_s,"\n\n");

  return 0;
}
