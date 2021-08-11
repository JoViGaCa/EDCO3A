/**
* @file ED2021-1-AT03-IndiceRemissivo-JoãoCarvalho.c
* @author João Carvalho
* @date 02 08 2021
* @brief Resoluçao da ativade prática 3
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <string.h>
#include <ctype.h>



typedef struct NoArvore * PtrNoArvore;
typedef struct NoArvore{
  char palavra[16];
  int pagina[15];
  int qtdpag; // quantidade de páginas que aparece
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
bool inserirArvore(PtrNoArvore *node, char palavra[]){
  //acha o ponto de inserção
  // cria o nó, aloca memória, copia informação, filhos == NULL
  // retorna true or false (consegue ou não)
  if((*node) == NULL){
    (*node) = (PtrNoArvore) malloc(sizeof(NoArvore));
    strcpy((*node)->palavra, palavra);
    (*node)->qtdpag = 0;
    for(int i = 0; i< 15; i++){
      (*node)->pagina[i] = 0;
    }
    (*node)->esquerda = NULL;
    (*node)->direita = NULL;
    return (true);
  }

  // se as palavras forem iguais , return false
  if((strcmp((*node)->palavra, palavra)) == 0){
    printf("Erro: elemento já existente\n");
    return (false);
  }

  // achar o percurso com recursão
  if((strcmp((*node)->palavra,palavra)) < 0){
    return (inserirArvore(&(*node)->direita,palavra));
  }
  if((strcmp((*node)->palavra,palavra)) > 0){
    return (inserirArvore(&(*node)->esquerda,palavra));
  }
}

//emOrdem
// recursiva esquerda -> imprime -> recursivo direita
void imprimeEmOrdem(PtrNoArvore *node, FILE* arq_s){
  // chama recursiva esquerda, imprime, recursiva direita
  if((*node) == NULL) return;
  imprimeEmOrdem(&(*node)->esquerda, arq_s);
  fprintf(arq_s,"%s ",(*node)->palavra);
  for(int i = 0; i < (*node)->qtdpag; i++){
    fprintf(arq_s,",%i", (*node)->pagina[i]);
  }
  fprintf(arq_s,"\n");
  imprimeEmOrdem(&(*node)->direita, arq_s);
}


void inserirTermos(FILE* arq_e, PtrNoArvore *node){
  char string[65]; // auxiliar
  fseek(arq_e,1,SEEK_CUR); // reajuste por causa dos ':'
  fscanf(arq_e,"%[^>]", string);// pega todas as palavras
  //separa as palavras da string e adiciona uma a uma na arvore
  char *palavra;
  palavra = strtok(string, ",");
  while(palavra){
    for(int i = 0; i< strlen(palavra); i++){
      palavra[i] = tolower(palavra[i]);
    }
    inserirArvore(&(*node), palavra);
    palavra = strtok(NULL, ",");
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

//pesquisa
bool pesquisaArvore(PtrNoArvore * node, char palavra[], int pagina){
  //pesquisa i item
  if((strcmp((*node)->palavra,palavra)) == 0){
    //adiciona a pagina se não for igual às outras já existentes
    for(int i = 0; i < (*node)->qtdpag; i++){
      if(pagina == (*node)->pagina[i]){
        return true;
      }
    }
    (*node)->pagina[(*node)->qtdpag] = pagina;
    (*node)->qtdpag++;
    return true;
  }
  if((strcmp((*node)->palavra,palavra)) > 0){
    if((*node)->esquerda == NULL){
      return false;
    }
    pesquisaArvore(&(*node)->esquerda, palavra, pagina);
  }
  if((strcmp((*node)->palavra,palavra)) < 0){
    if((*node)->direita == NULL){
      return false;
    }
    pesquisaArvore(&(*node)->direita, palavra, pagina);
  }
}

int main(int argc, const char *argv[]){
  if(argc != 3){
    printf("Erro nos argumentos\n");
    exit(1);
  }

  FILE* arq_e = fopen(argv[1],"r"); // arquivo de entrada
  FILE* arq_s = fopen(argv[2],"w"); // arquivo de saida
  if(!arq_e || !arq_s){
    printf("Erro ao abrir os arquivos\n");
    exit(1);
  }
  PtrNoArvore raiz;
  iniciaArvore(&raiz);

  int pagina = 0; // defina a página em específico
  char palavra[16]; // string para auxiliar a manipular o arquivo
  char c;

  //primeira parte são os termos, se o arquivo não estiver vazio ele adiciona os termos
  if((fscanf(arq_e,"%[^:]", palavra)) != 1){
    printf("Erro: arquivo vazio\n");
    exit(1);
  }
  if((strcmp(palavra, "<termos")) == 0){
    inserirTermos(arq_e, &raiz);
  } else {
    printf("Erro na formatação do arquivo\n");
    exit(1);
  }

  //loop para as páginas
  while(true){
   fscanf(arq_e,"%s", palavra);
   char *aux; // variavel auxiliar
   //verifica se é uma tag
   if(palavra[0] == '<'){
     //se for ele pega o número da página e salva;
     aux = strtok(palavra, ":>");
     aux = strtok(NULL, ":>");
     pagina = atoi(aux);
   }

   for(int i = 0; i < strlen(palavra); i++){
     palavra[i] = tolower(palavra[i]);
   }

   //separa a palavra de pontos ou espaços
   aux = strtok(palavra, ",.) (");
   //verifica se tem a palavra na Arvore e se tiver já adiciona a página
   pesquisaArvore(&raiz,aux,pagina);

   //se houver uma segunda parte, ele verifica se está na Arvore.
   if((aux = strtok(NULL, ",.) ("))){
     pesquisaArvore(&raiz, aux, pagina);
   }


    if(feof(arq_e)){
      break;
    }
  }

  imprimeEmOrdem(&raiz, arq_s);


  destruirArvore(&raiz);
  fclose(arq_s);
  fclose(arq_e);
  return 0;
}
