#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//Feita com encadeamento Separado
typedef struct pet{
    char nome[1000];
    int idade;
    int id;
    struct pet *prox;
}tp_pet;

void pausaTudo(){
  system("pause");
  system("cls");
}

void inicializaVetor(tp_pet vet[], int tam){
    for(int i = 0; i < tam; i++){
      vet[i].prox = NULL;
      vet[i].id = -1;
    }
}

int funcaoInsana(int id, int tam){ //Funcao que faz o Hashing
  float A = 0.6180339887;
  float val = id * A;
  val -= (int)val;
  return (int)(val * tam);
}

int procuraSeExiste(tp_pet vetPet[], int pos){ //Retornar 0 se não existir, 1 se existir
  if(vetPet[pos].id != -1){
    return 1;
  }
  return 0; 
}

void inserePets(tp_pet vetPet[], int tam){
  int pos;
  tp_pet *aux, *novo, *ant;

  for(int i = 0; i<tam; i++){
    novo = (tp_pet*)malloc(sizeof(tp_pet));
    novo->prox = NULL;
    printf("=-=-=-=-=-=-=-=-=-=-= Pet %d =-=-=-=-=-=-=-=-=-=-=\n", i+1);
    printf("Nome do pet %d:\n", i+1);
    scanf("%s", novo->nome);
    printf("Idade do pet:\n");
    scanf("%d", &novo->idade);
    printf("ID do pet:\n");
    scanf("%d", &novo->id);
    
    pos = funcaoInsana(novo->id, tam);
    if(procuraSeExiste(vetPet, pos)){
      aux = &vetPet[pos];
      while(aux->prox != NULL){
        aux = aux->prox;
      }
      aux->prox = novo;
    } else{
      strcpy(vetPet[pos].nome, novo->nome);
      vetPet[pos].idade = novo->idade;
      vetPet[pos].id = novo->id;
    }   
  }
}

void mostraPets(tp_pet vet[], int tam){
    tp_pet *aux;
    printf("=-=-=-=-=-=-=-=-=-=-= Pets =-=-=-=-=-=-=-=-=-=-=\n");
    for(int i = 0, j; i<tam; i++){
      j=1;
      if(vet[i].id != -1){
        aux = &vet[i];
        while(aux != NULL){
          printf("=-=-=-= Pet =-=-=-=\n", i+1, j);
          printf("Nome: %s\n", aux->nome);
          printf("Idade: %d\n", aux->idade);
          printf("ID: %d\n", aux->id);
          aux = aux->prox;
          j++;
        }
      }
    }  
  }

int buscaPet(tp_pet vet[], int id, int tam){
  int pos = funcaoInsana(id, tam);
  tp_pet *aux = &vet[pos];
  if(aux->id == -1){
    return 0;
  }
  while(aux->id != id && aux != NULL){
    aux = aux->prox;
  }
  if(aux->id == id){
    printf("=-=-=-= Pet Buscado =-=-=-=\n");
    printf("Nome: %s\n", aux->nome);
    printf("Idade: %d\n", aux->idade);
    printf("ID: %d\n", aux->id);
    return 1;
  }
  return 0;
}

int main(){
  int tam, resp = 1, id, vez=0;
  printf("Quantidade de Pets a inserir:\n");
  scanf("%d", &tam);
  tp_pet *vetorPets = (tp_pet*)malloc(tam*sizeof(tp_pet));
  inicializaVetor(vetorPets, tam);
  inserePets(vetorPets, tam);
  while(resp != 0){
    printf("=-=-=-=-=-=-=-=-=-=-= Menu =-=-=-=-=-=-=-=-=-=-=\n");
    printf("1 - Mostrar Pets\n");
    printf("2 - Buscar Pet\n");
    printf("3 - Inserir Mais Pets\n");
    printf("0 - Sair\n");
    scanf("%d", &resp);
    switch(resp){
      case 1:
        mostraPets(vetorPets, tam);
        pausaTudo();
        break;
      case 2:
        printf("ID do Pet:\n");
        scanf("%d", &id);
        if(!buscaPet(vetorPets, id, tam)){
          printf("Pet nao encontrado\n"); 
        }
        pausaTudo();
        break;
      case 3:
        inserePets(vetorPets, tam);
        pausaTudo();
        break;
      case 0:
        printf("Saindo...\n");
        break;
      default:
        printf("Opção inválida\n");
        pausaTudo();
        break;
    }
  }
  return 0;
}