/**
* @file atv1.c
* @author João Carvalho
* @date 05 07 2021
* @brief Resoluçao da ativade prática 1
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#define  TAMANHO 50

//definição da pilha dinâmica
typedef struct NoPilha *PtrNoPilha;
typedef struct NoPilha{
  int x;
  PtrNoPilha proximo;
} NoPilha;
typedef struct{
  PtrNoPilha topo;
  int qtdElem;
} PilhaDin;

//definição pilha estática
typedef struct{
  int array[TAMANHO];
  int topoest;
  int qtdElem;
}PilhaEst;

//implementações pilha estática
//inicializar a pilha
void iniciaPilhaEst(PilhaEst *p){
   //inicia topo em zero
   p->topoest = 0;
   //inicia a quantidade em 0
   p->qtdElem = 0;
}

//esta vazia
bool estaVaziaPilhaEst(PilhaEst *p){
  //esta vazia se topo igual a zero
  return (p->topoest == 0);
}

//esta cheia
bool estaCheiaPilhaEst(PilhaEst *p){
  //esta cheia se topo igual a TAMANHO
  return(p->topoest == TAMANHO);
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
  if(!estaCheiaPilhaEst(p)){
    p->array[p->topoest] = x;
    p->topoest++;
    p->qtdElem++;
  } else{
    printf("Erro: pilha está cheia, não é possível inserir\n");
  }
}

// visualiza pilha estatica
void imprimePilhaEst(PilhaEst *p){
  if(!estaVaziaPilhaEst(p)){
     for(int i = 0; i < p->topoest; i++){
       printf("%i ", p->array[i]);
     }
     printf("\n");
  } else{
    printf("Erro pilha vazia imprime pilha estatica\n");
  }
}

//desempilha
int desempilhaPilhaEst(PilhaEst *p){
  int x = -99; //valor de controle
  //verifica se a pilha não estiver vazia
  if(!estaVaziaPilhaEst(p)){
    //tira o último elemento e decrementa topo e qtdElem
    x = p->array[p->topoest-1];
    p->topoest--;
    p->qtdElem--;
  } else {
    printf("Erro: pilha vazia desempilha pilha estatica\n");
  }
  return (x);
}

//remove
void removerPilhaEst(PilhaEst *p, int x){
  if(!estaVaziaPilhaEst(p)){
    //estrutura de repetição para percorrer a pilha
    for(int i = 0; i < p->topoest; i++){
      //verifica se o elemento é igual ao que se quer
      if(p->array[i] == x){
        //estrutura de repetição para retirar o elemento e atualizar o array
        for(int j = i; j < p->topoest; j++){
          p->array[j] = p->array[j+1];
        }
        //decrementar topo e qtdelementos
        p->topoest--;
        p->qtdElem--;
      }
    }
  } else{
    printf("Erro: pilha vazia remover pilha estatica\n");
  }
}

//retorna topo
int topoPilhaEst(PilhaEst *p){
  //valor auxiliar
  int x = -99;
  //verifica se esta vazia
  if(!estaVaziaPilhaEst(p)){
    x = p->array[p->topoest - 1];
  } else{
    printf("Erro: pilha vazia topo pilha estatica\n");
  }
  return x;
}

//calcula o binário na pilha estatica
void calcBinPilhaEst(PilhaEst *p, int numero){
  if(numero == 0){
    empilhaPilhaEst(p, 0);
  } else if(numero == 1){
    empilhaPilhaEst(p, 1);
  } else if(numero%2 == 0){
    calcBinPilhaEst(p, numero/2);
    empilhaPilhaEst(p, 0);
  } else {
    calcBinPilhaEst(p, numero/2);
    empilhaPilhaEst(p, 1);
  }
}

//armazena os valores da pilha binaria, for do ultimo ao primeiro
void armazenaPilhaEst(PilhaEst *p, FILE* arqs){
  if(!estaVaziaPilhaEst(p)){
    for(int i = 0; i < p->qtdElem; i++){
      fprintf(arqs,"%i", p->array[i]);
    }
  } else {
    printf("Error: pilha vazia armazena pilha estatica\n");
  }

}


//implementações pilha dinamica
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
  if(!estaVaziaPilhaDin(p)){
    //começa no topo e vai indo
    PtrNoPilha temp;
    for(temp = p->topo; temp != NULL; temp = temp->proximo){
      printf("%d ", temp->x);
    }
  } else {
    printf("Erro pilha vazia imprime pilha dinamica\n");
  }
}


int desempilhaPilhaDin(PilhaDin *pd){
  //valor de controle
  int v = -99;
  if(!estaVaziaPilhaDin(pd)){
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
  if(!estaVaziaPilhaDin(pd)){
    x = pd->topo->x;
  } else {
    printf("Erro: pilha vazia topo pilha dinamica\n");
  }
  return x;
}

//destruir
void destruirPilhaDin(PilhaDin *pd){
  if(!estaVaziaPilhaDin(pd)){
    //auxiliar para ajudar
    PtrNoPilha des;
    //estrutura de repetição para destruir
    for(des = pd->topo; des != NULL; des = pd->topo){
      pd->topo = des->proximo;
      free(des);
      pd->qtdElem--;
    }
  } else{
    printf("Erro: pilha vazia destruit pilha dinamica\n");
  }
}

//calcula o binario na pilha dinamica
void calcBinPilhaDin(PilhaDin *p, int numero){
  if(numero == 0){
    empilhaPilhaDin(p, 0);
  } else if(numero == 1){
    empilhaPilhaDin(p, 1);
  } else if(numero%2 == 0){
    calcBinPilhaDin(p, numero/2);
    empilhaPilhaDin(p, 0);
  } else {
    calcBinPilhaDin(p, numero/2);
    empilhaPilhaDin(p, 1);
  }
}

//armazena os valores da pilha binaria, recursivamente do ultimo até o primeiro
void armazenaPilhaDin(PtrNoPilha p, FILE* arqs){
  if(p->proximo == NULL){
    fprintf(arqs,"%i", p->x);
  } else {
    armazenaPilhaDin(p->proximo, arqs);
    fprintf(arqs,"%i", p->x);
  }
}

int main(int argc, const char * argv[]){
  //abre o arquivo de entrada e saida
  FILE *arqe = fopen(argv[1],"r");
  FILE *arqs = fopen(argv[2], "w");
  if(!arqe || !arqs){
    printf("Erro: arquivo inexistente no diretório\n");
  } else {
    //le o primeiro caractere do arquivo e cria as pilhas para o mesmo
    char c = fgetc(arqe);
    if(c == 'd' || c == 'D'){
      PilhaDin pilhabi; //pilha binaria
      PilhaDin pilhaaux; // pilha auxiliar
      //inicia pilha
      iniciaPilhaDin(&pilhabi);
      iniciaPilhaDin(&pilhaaux);
      //recebe os valores do arquivo e coloca na pilha auxiliar
      int d;
      while(!feof(arqe)){
        fscanf(arqe,"%d", &d);
        empilhaPilhaDin(&pilhaaux, d);
      }

      //armazena o tamanho da pilha em uma variável para não dar erro
      int tam = tamanhoPilhaDin(&pilhaaux);

      for(int i = 0; i < tam; i++){
        //pega o elemento do topo da pilha calcula sua divisão por 2 e joga na pilha binaria
        d = desempilhaPilhaDin(&pilhaaux);
        calcBinPilhaDin(&pilhabi,d);

        //armazena o valor na pilha
        armazenaPilhaDin(pilhabi.topo, arqs);
        fprintf(arqs,"\n");

        //variaveis auxiliares para limpar a pilha, mas deixa um para poder destruir depois
        int a = pilhabi.qtdElem;
        int b;
        for(int i = 0; i < a; i++){
          b = desempilhaPilhaDin(&pilhabi);
        }
      }

   } else {
      if(c == 'e' || c == 'E'){
        PilhaEst pilhabi; // pilha binaria
        PilhaEst pilhaaux; // pilha auxiliar

        //inicia as pilhas
        iniciaPilhaEst(&pilhabi);
        iniciaPilhaEst(&pilhaaux);

        //recebe os valores do arquivo e coloca na pilha auxiliar
        int d;
        while(!feof(arqe)){
          fscanf(arqe,"\n%d", &d);
          empilhaPilhaEst(&pilhaaux, d);
        }


        //armazena o tamanho da pilha em uma variável para não dar erro
        int tam = tamanhoPilhaEst(&pilhaaux);

        for(int i = 0; i < tam; i++){
          //pega o elemento do topo da pilha calcula sua divisão por 2 e joga na pilha binaria
          d = desempilhaPilhaEst(&pilhaaux);
          calcBinPilhaEst(&pilhabi,d);

          //armazena o valor na pilha
          armazenaPilhaEst(&pilhabi, arqs);
          fprintf(arqs,"\n");

          //variaveis auxiliares para limpar a pilha
          int a = pilhabi.qtdElem;
          int b;
          for(int i = 0; i < a; i++){
            b = desempilhaPilhaEst(&pilhabi);
          }
        }

      } else{
        printf("Erro: Arquivo não define pilha\n");
      }
    }

  }
  fclose(arqs);
  fclose(arqe);

  return 0;
}
