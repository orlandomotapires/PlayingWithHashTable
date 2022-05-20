//Codigo desenvivolvido puro e exclusivamente por Orlando Mota
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct pet{
    char nome[100];
    int idade;
    int id;
}tp_pet;

tp_pet matrizPets[100][2];

void pausaTudo(){
  system("pause");
  system("cls");
}

void inicializaMatriz(int tam){
  for(int i = 0; i < tam; i++){
    matrizPets[i][0].id = -1;
    matrizPets[i][1].id = -1;
  }
}

int funcaoInsana(int id, int tam){//Funcao que faz o Hashing
  float A = 0.6180339887;
  float val = id * A;
  val = val - (int)val;
  return (int) (val * tam);
}

int procuraSeExiste(int linha){ //Retornar 0 se não existir, 1 se existir
  return matrizPets[linha][0].id != -1;
}

void alocaSemColisao(tp_pet novoPet, int linha){
  matrizPets[linha][0] = novoPet;
}

int alocaComColisao(tp_pet novoPet, int linha, int tam){
  int proxSemPreencher, umaVez=0;
  for(int i = linha; i < tam; i++){
    if(matrizPets[i][1].id == -1 && umaVez==0){
      proxSemPreencher = i;
      umaVez++;
    }
    if(matrizPets[i][0].id == -1){
      matrizPets[i][0] = novoPet;
      matrizPets[proxSemPreencher][1].id = i;
      return 1;
    }
    if(i == tam-1) i = 0;
  }
  return 0;
}

int estaCheio(int tam){
  for(int i = 0; i<tam; i++){
    if(matrizPets[i][0].id == -1){
      return 0;
    }
  }
  return 1;
}

int checaSeIdExiste(int tam, int id){
  for(int i = 0; i<tam; i++){
    if(matrizPets[i][0].id == id){
      return 1;
    }
  }
  return 0;
}

tp_pet lerPet(int tam, int i){
  tp_pet novoPet;
  printf("=-=-=-=-=-=-=-=-=-=-= Pet %d =-=-=-=-=-=-=-=-=-=-=\n", i+1);
  printf("Nome do pet %d:\n", i+1);
  scanf("%s", novoPet.nome);
  printf("Idade do pet:\n");
  scanf("%d", &novoPet.idade);
  printf("ID do pet:\n");
  scanf("%d", &novoPet.id);
  while(checaSeIdExiste(tam, novoPet.id)){
    system("cls");
    printf("ID ja existe, digite outro ID:\n");
    scanf("%d", &novoPet.id);
  }
  return novoPet;
}

void inserePets(int tam){
  int linha;
  tp_pet novoPet;
  for(int i = 0; i<tam; i++){  
    novoPet = lerPet(tam, i);
    linha = funcaoInsana(novoPet.id, tam);
    if(procuraSeExiste(linha)){//Ve se ja tem alguem ali
      //printf("Colidiu/n"); //Ver se colidiu
      alocaComColisao(novoPet, linha, tam);//Insere com colisao
    }else{
      alocaSemColisao(novoPet, linha);//Insere sem colisao
    }
  }
}

void mostraPets(int tam){
  printf("=-=-=-=-=-=-=-=-=-=-= Pets =-=-=-=-=-=-=-=-=-=-=\n");
  for(int i = 0; i < tam; i++){   
    printf("=-=-=-= Pet %d =-=-=-=\n", i+1);
    printf("Nome: %s\n", matrizPets[i][0].nome);
    printf("Idade: %d\n", matrizPets[i][0].idade);
    printf("ID: %d\n", matrizPets[i][0].id); 
    //printf("Linha do coleguinha: %d\n", matrizPets[i][1].id);
  }  
}

int buscaPet(int id, int tam){
  
  if(!checaSeIdExiste(tam, id)){
    return 0;
  }
  
  int linha = funcaoInsana(id, tam);
  for(int i = 0; i < tam; i++){
    if(matrizPets[linha][0].id == id){
      printf("=-=-=-= Pet Buscado =-=-=-=\n");
      printf("Nome: %s\n", matrizPets[linha][0].nome);
      printf("Idade: %d\n", matrizPets[linha][0].idade);
      printf("ID: %d\n", matrizPets[linha][0].id);
      return 1;
    }else{
      linha = matrizPets[linha][1].id;
    } 
  }
  
}

void menu(int tam){
  int resp=1, id;
  while(resp != 0){
    printf("=-=-=-=-=-=-=-=-=-=-= Menu =-=-=-=-=-=-=-=-=-=-=\n");
    printf("1 - Mostrar Pets\n");
    printf("2 - Buscar Pet\n");
    printf("3 - Inserir Mais Pets\n");
    printf("0 - Sair\n");
    scanf("%d", &resp);
    switch(resp){
      case 1:
        mostraPets(tam);
        pausaTudo();
        break;
      case 2:
        printf("ID do Pet:\n");
        scanf("%d", &id);
        if(!buscaPet(id, tam)){
          printf("Pet nao encontrado\n"); 
        }
        pausaTudo();
        break;
      case 3:
        if(estaCheio(tam)){
        printf("Nao ha espaco para mais pets\n");
        }else inserePets(tam);
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
}

int main(){
  int tam;
  printf("Quantidade de Pets a inserir:\n");
  scanf("%d", &tam);
  inicializaMatriz(tam);
  inserePets(tam);
  menu(tam);
  return 0;
}