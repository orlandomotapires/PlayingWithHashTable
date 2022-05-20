#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

//Code developed by: Orlando Mota and Pedro Martins

typedef struct NO* ArvAVL;

typedef struct pets{
	int idade, id;
	char nome[500];
}tp_pet;

struct NO{
   struct NO *esq;
   tp_pet info;
   int alt; //altura da sub- rvore (facilita o c lculo do fator de balanceamento!)??
   struct NO *dir;
};

ArvAVL* arvoreDePets[100];

ArvAVL* criarAVL();
void emOrd(ArvAVL* raiz);
int inserir(ArvAVL* raiz, tp_pet valor);
int consultarValorAVL(ArvAVL* raiz, tp_pet valor);
int maior(int x, int y);
int alt_NO(struct NO* no);
int fb_NO(struct NO* no);
void RotacaoLL(ArvAVL* raiz);
void RotacaoRR(ArvAVL* raiz);
void RotacaoRL(ArvAVL* raiz);
void RotacaoLR(ArvAVL* raiz);
int contPrint=0;

ArvAVL* criarAVL(){
  ArvAVL* raiz = (ArvAVL*)malloc(sizeof(ArvAVL));
  if(raiz!=NULL){
    *raiz = NULL;
  }
  return raiz;
}

void emOrd(ArvAVL* raiz){
   if(raiz==NULL) return;
   if(*raiz != NULL){
      //printf("Contador:%d", contPrint);
      emOrd(&((*raiz)->esq));
      if(contPrint!=0){
     printf(" ");  
  }
      printf("=-=-=-=-=-=-=-=-=-=-=  Pet  =-=-=-=-=-=-=-=-=-=-=\n");
      printf("Nome: %s\n", (*raiz)->info.nome);
      printf("Idade: %d\n", (*raiz)->info.idade);
      printf("ID: %d\n", (*raiz)->info.id);

      contPrint++;
      emOrd(&((*raiz)->dir));
   }
}

int inserir(ArvAVL* raiz, tp_pet pet){
	int res;
	if(*raiz==NULL){
		struct NO* novo;
		novo = (struct NO*)malloc(sizeof(struct NO));
		if(novo==NULL) return 0;
		novo->info = pet;
		novo->alt = 0;
		novo->dir = NULL;
		novo->esq = NULL;
		*raiz = novo;
		return 1;
	} else {
		struct NO* atual = *raiz;
		if(pet.id < atual->info.id){
			if((res=inserir(&(atual->esq), pet))==1){
				if(fb_NO(atual) >= 2){
					if(pet.id < (*raiz)->esq->info.id){
						RotacaoLL(raiz);
					}else{
						RotacaoLR(raiz);
					}
				}
			}
		}else{
			if(pet.id > atual->info.id){
				if((res = inserir(&(atual->dir), pet))==1){
					if(fb_NO(atual) >= 2){
						if(pet.id > (*raiz)->dir->info.id){
							RotacaoRR(raiz);
						}else{
							RotacaoRL(raiz);
						}
					}
				}
			}else{
				return 0; // Valor Duplicado
			}
		}
		atual->alt = maior(alt_NO(atual->esq), alt_NO(atual->dir)) + 1;
		return res;
	} 
}

tp_pet consultarValorAVL(ArvAVL* raiz, int id){
	tp_pet petRetorno;
  petRetorno.id = -1;
  struct NO* atual = *raiz;
	while(atual != NULL){
		if(atual->info.id == id){
			return atual->info;
		}else{
			if(atual->info.id >  id){
				atual = atual->esq;
			}else{
				atual = atual->dir;
			}
		}
	}
  return petRetorno;
}

int alt_NO(struct NO* no){
   if(no == NULL) return -1;
   else return no->alt;
}

int fb_NO(struct NO* no){
int esq = alt_NO(no->esq);
int dir = alt_NO(no->dir);
return labs(esq - dir);
}

int maior(int x, int y){
return (x>y)?x:y;
}

void RotacaoLL(ArvAVL* raiz){
   struct NO* no;
   no = (*raiz)->esq;
   (*raiz)->esq = no->dir;
   no->dir = *raiz;
   (*raiz)->alt = maior(alt_NO((*raiz)->esq), alt_NO((*raiz)->dir)) + 1;
   no->alt = maior(alt_NO(no->esq), (*raiz)->alt) + 1;
   *raiz = no;
}

void RotacaoRR(ArvAVL* raiz){
   struct NO* no;
   no = (*raiz)->dir;
   (*raiz)->dir = no->esq;
   no->esq = *raiz;
   (*raiz)->alt = maior(alt_NO((*raiz)->esq), alt_NO((*raiz)->dir)) + 1;
   no->alt = maior(alt_NO(no->dir), (*raiz)->alt) + 1;
   *raiz = no;
}

void RotacaoLR(ArvAVL* raiz){
RotacaoRR(&(*raiz)->esq);
RotacaoLL(raiz);
}

void RotacaoRL(ArvAVL* raiz){
RotacaoLL(&(*raiz)->dir);
RotacaoRR(raiz);
}

//Funcoes proprias
void pausaTudo(){
  system("pause");
  system("cls");
}

void mostraTudo(int tam){
  for(int i=0; i<tam; i++){
    emOrd(arvoreDePets[i]);
  }
  printf("\n");
}

int hashing(float id, int tam){
	float a = 0.912519251;
	float val = id * a;
	val = val - (int)val;
	return (int) (tam*val);
} 

int idExistente(ArvAVL* raiz, int id){
	struct NO* atual = *raiz;
	while(atual != NULL){
		if(atual->info.id == id){
			return 1;
		}else{
			if(atual->info.id >  id){
				atual = atual->esq;
			}else{
				atual = atual->dir;
			}
		}
	}
	return 0;
}

void inserePets(int tam){
	int pos;
	tp_pet petAux;
	for(int i = 0; i < tam; i++){
		printf("=-=-=-=-=-=-=-=-=-=-= Pet %d =-=-=-=-=-=-=-=-=-=-=\n", i+1);
		printf("Nome do pet: ");
		scanf(" %s", petAux.nome);
		printf("Idade do pet: ");
		scanf("%d", &petAux.idade);
		printf("Id do pet: ");
		scanf("%d", &petAux.id);
    
		pos = hashing(petAux.id, tam);
		while(idExistente(arvoreDePets[pos], petAux.id)){
			printf("ID ja inserido!\n");
			scanf("%d", &petAux.id);
      pos = hashing(petAux.id, tam);
		}
		
		pos = hashing(petAux.id, tam);
		inserir(arvoreDePets[pos], petAux);
    printf("Pet cadastrado com sucesso!\n");
	}
}

void menu(int tam){
	int op, id, pos;
	tp_pet petAux2;
	while(1){
    printf("=-=-=-=-=-=-=-=-=-=-= Menu =-=-=-=-=-=-=-=-=-=-=\n");
		printf("O que deseja fazer: \n");
		printf("1 - Buscar pet\n");
		printf("2 - Inserir pet\n");
    printf("3 - Mostrar Todos Pets cadastrados\n");
		printf("0 - Sair\n");
		scanf("%d", &op);
		switch(op){
			case 1:
				printf("ID do pet que deseja buscar: ");
				scanf("%d", &id);
				pos = hashing(id, tam);
				petAux2 = consultarValorAVL(arvoreDePets[pos], id);
        if(petAux2.id != -1){
          printf("=-=-=-=-=-=-= Pet buscado =-=-=-=-=-=-= \n");
          printf("Nome: %s\n", petAux2.nome);
          printf("Idade: %d\n", petAux2.idade);
          printf("ID: %d\n", petAux2.id);
        }else{
          printf("Pet nao encontrado!\n");
        }
        pausaTudo();
				break;
			case 2:
				printf("Quantos Pets deseja inserir: ");
				scanf("%d", &tam);
				inserePets(tam);
        pausaTudo();
				break;
      case 3:
        mostraTudo(tam);
        pausaTudo();
        break;
			case 0:
				return;
		}
	}
}

void inicializaArvorePets(int tam){
	for(int i = 0; i < tam; i++){
		arvoreDePets[i] = criarAVL();
	}
}

int main(){
	int tam;
	tp_pet petAux;
	printf("Insira a quantidade de pets total: ");
	scanf("%d", &tam);	
	inicializaArvorePets(tam);
	inserePets(tam);
  pausaTudo();
	menu(tam);
	return 0;
}