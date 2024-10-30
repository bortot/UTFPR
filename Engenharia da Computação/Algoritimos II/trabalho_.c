#include <stdio.h>
#include <stdlib.h>
#define false 0
#define true 1
#define branco 2    //branco=nao visitado
#define cinza 3     //cinza=visitado pela primeira vez
#define preto 4     //preto=vizinhos visitados
#define infi -1

typedef struct aresta_st{
  int id;
  int peso;
  struct aresta_st *prox;
  struct aresta_st *ant;
}aresta_st;

typedef struct vertice_st{
  int id;
  struct vertice_st *prox;
  struct vertice_st *ant;
  aresta_st *inicio;
  aresta_st *fim;
  int cor;
  int dist;
  int final;
  int pai;
}vertice_st;

typedef struct head_st{
  vertice_st *inicio;
  vertice_st *fim;
  int elementos;
}head_st;

typedef struct fila_st{
  int *v;
  int ini;
  int fim;
}fila_st;

typedef struct pilha_st{
  int *v;
  int ele;
}pilha_st;

void menu(void);
vertice_st* verificaVertice(head_st *h, int id);
aresta_st* verificaAresta(vertice_st *vert, int  id);
int insere_Vertice(head_st *h, int id, int peso);
int insere_aresta(int v1, int v2, int peso, head_st *h);
void print_grafo(head_st *h);
int remove_vertice(head_st *h, int vertice);
int removeAresta_aux(head_st *h, int are1, int are2);
int remove_aresta(head_st *h, vertice_st *vert1, vertice_st *vert2);
int grafo_conexo(head_st *h);
int grau_vertice(head_st *h, int id);
int busca_largura(head_st *h, int id);
void print_amplitude(head_st *h, int id);
void matriz(head_st *h);
void print_profundidade(head_st *h);
int print_dijkstra(head_st *h, int id);
int print_prim(head_st *h, int id);
void free_grafo(head_st *h);

int main(void){
  int op;
  int v1,v2,v3;
  head_st *head;

  head = (head_st*)malloc(sizeof(head_st));
  head->inicio=NULL, head->fim=NULL, head->elementos=0;

  menu();

  do{
    printf("OPCAO: ");
    while(scanf("%d",&op)!=1){
      scanf(" %*[^\n]");
      printf("Opcao Invalida!\n\n");
      menu();
      printf("OPCAO: ");
    }
    if(op>12 || op<0) printf("Opcao Invalida!\n");

    if(op==1){
      printf("Nome do vertice: ");
      if(scanf("%d",&v1)==1){
        if(insere_Vertice(head,v1,v2)==true)
          printf("Adicionado vertice.\n");
        else
          printf("Vertice ja existe.\n");
        }
      else{
        scanf(" %*[^\n]");
        printf("Nome invalido.\n");
      }
    }
    else if(op==2){
      printf("Vertices a serem ligados:\nVertice 1: ");
      if(scanf("%d",&v1)==1){
        printf("Vertice 2: ");
        if(scanf("%d",&v2)==1){
          printf("Peso da aresta: ");
          if(scanf("%d",&v3)==1){
            if(insere_aresta(v1,v2,v3,head)==false)
              printf("Erro ao inserir aresta.\n");
            else
              printf("Adicionada aresta.\n");
            }
          else{
            scanf(" %*[^\n]");
            printf("Peso invalido.\n");
          }
        }
        else{
          scanf(" %*[^\n]");
          printf("Vertice invalido.\n");
        }
      }
      else{
        scanf(" %*[^\n]");
        printf("Vertice invalido.\n");
      }
    }
    else if(op==3){
      print_grafo(head);
      //printf("\nPressione 'enter'\n");
      //getchar(); getchar();
    }
    else if(op==4){
      printf("Vertice a ser removido: ");
      if(scanf("%d",&v1)!=1){
        scanf(" %*[^\n]");
        printf("Vertice invalido.\n");
      }
      else{
        if(remove_vertice(head, v1)==true)
          printf("Vertice removido.\n");
        else
          printf("Falha ao remover vertice.\n");
      }
    }
    else if(op==5){
      printf("Vertices da aresta a ser removida:\nVertice 1: ");
      if(scanf("%d",&v1)==1){
        printf("Vertice 2: ");
        if(scanf("%d",&v2)==1){
          if(removeAresta_aux(head,v1,v2)==true)
            printf("Aresta removida.\n");
          else
            printf("Erro ao remover aresta.\n");
          }
        else{
          scanf(" %*[^\n]");
          printf("Vertice invalido.\n");
        }
      }
      else{
        scanf(" %*[^\n]");
        printf("Vertice invalido.\n");
      }
    }
    else if(op==6){
      printf("Informe o vertice: ");
      if(scanf("%d",&v1)!=1){
        scanf(" %*[^\n]");
        printf("Vertice invalido.\n");
      }
      else{
        v2=grau_vertice(head, v1);
        if(v2==-1)
          printf("Esse vertice não existe.\n");
        else
          printf("\nGrau do vertice %d: %d\n",v1,v2);
      }
    }
    else if(op==7){
      v1=grafo_conexo(head);
      if(v1==true)
        printf("Grafo conexo\n");
      else if(v1==false)
        printf("Grafo desconexo\n");
      else
        printf("Grafo Vazio!\n");
    }
    else if(op==8){
      matriz(head);
      //printf("\nPressione 'enter'\n");
      //getchar(); getchar();
    }
    else if(op==9){
      printf("Escolha um vertice para começar: ");
      if(scanf("%d",&v1)==1)
        print_amplitude(head,v1);
      else{
        scanf(" %*[^\n]");
        printf("Vertice invalido.\n");
      }
    }
    else if(op==10){
      print_profundidade(head);
    }
    else if(op==11){
      printf("Vertice para comecar: ");
      if(scanf("%d",&v1)==1)
        print_dijkstra(head,v1);
      else
        printf("Vertice invalido\n");
    }
    else if(op==12){
      printf("Vertice para comecar: ");
      if(scanf("%d",&v1)==1)
        print_prim(head,v1);
      else
        printf("Vertice invalido\n");
    }
    //if(op!=0 && op!=3) system("sleep 1");
    printf("\n");
  }while(op!=0);

  free_grafo(head);
  return 0;
}

void menu(void){
  //system("clear");
  printf("       MENU\n");
  printf("1.  Inserir vertices\n");
  printf("2.  Inserir arestas\n");
  printf("3.  Visualizar grafo\n");
  printf("4.  Remover vertices\n");
  printf("5.  Remover arestas\n");
  printf("6.  Grau de um vertice\n");
  printf("7.  Grafo conexo\n");
  printf("8.  Matriz de adjacencias\n");
  printf("9.  Busca em largura\n");
  printf("10. Busca em profundidade\n");
  printf("11. Algoritimo de Dijkstra\n");
  printf("12. Algoritimo de Prim\n");
  printf("\n0. Sair\n\n");
}

vertice_st* verificaVertice(head_st *h, int id){
  vertice_st *aux;

  aux=h->inicio;
  while(aux!=NULL){
    if(id==aux->id) return aux;
    aux=aux->prox;
  }
  return NULL;
}

aresta_st* verificaAresta(vertice_st *vert, int id){
  aresta_st *aux;

  aux=vert->inicio;
  while(aux!=NULL){
    if(id==aux->id) return aux;
    aux=aux->prox;
  }
  return NULL;
}

int insere_Vertice(head_st *h, int id, int peso){
  if(verificaVertice(h,id)!=NULL) return false;

  vertice_st *aux,*novo;
  novo = (vertice_st*)malloc(sizeof(vertice_st));

  novo->id=id, novo->prox=NULL, novo->inicio=NULL, novo->fim=NULL;
  h->elementos++;

  if(h->inicio!=NULL){
    aux=h->fim;
    aux->prox=novo;
    novo->ant=aux;
    h->fim=novo;
  }
  else{
    h->inicio=novo;
    h->fim=novo;
    novo->ant=NULL;
  }
  return true;
}

int insere_aresta(int v1, int v2, int peso, head_st *h){
  aresta_st *novo1, *novo2, *are_aux;
  vertice_st *aux, *aux2;

  if(v1==v2) return false;

  aux=verificaVertice(h, v1);
  if(aux==NULL) return false;
  aux2=verificaVertice(h, v2);
  if(aux2==NULL) return false;

  if(verificaAresta(aux, v2)!=NULL) return false;
  if(verificaAresta(aux2, v1)!=NULL) return false;

  novo1 = (aresta_st*)malloc(sizeof(aresta_st));
  novo1->id=v2;
  novo1->peso=peso;
  novo1->prox=NULL;
  novo2 = (aresta_st*)malloc(sizeof(aresta_st));
  novo2->id=v1;
  novo2->prox=NULL;
  novo2->peso=peso;

  if(aux->inicio!=NULL){
    are_aux=aux->fim;
    are_aux->prox=novo1;
    novo1->ant=are_aux;
    aux->fim=novo1;
  }
  else{
    aux->inicio=novo1;
    aux->fim=novo1;
    novo1->ant=NULL;
  }
  if(aux2->inicio!=NULL){
    are_aux=aux2->fim;
    are_aux->prox=novo2;
    novo2->ant=are_aux;
    aux2->fim=novo2;
  }
  else{
    aux2->inicio=novo2;
    aux2->fim=novo2;
    novo2->ant=NULL;
  }

  return true;
}

void print_grafo(head_st *h){
  vertice_st *aux;
  aresta_st *aux2;

  if(h->inicio==NULL)
    printf("Grafo Vazio!\n");
  else{
    for(aux=h->inicio; aux!=NULL; aux=aux->prox){
      printf("%-3d -> ",aux->id);
      for(aux2=aux->inicio; aux2!=NULL; aux2=aux2->prox)
        printf("%d - ",aux2->id);
      printf("|\n");
    }
  }
}

int remove_vertice(head_st *h, int vertice){
  vertice_st *aux, *aux2, *vert;
  aresta_st *aresta, *aresta2;

  vert=verificaVertice(h,vertice);
  if(vert==NULL) return false;

  h->elementos--;

  for(aux=h->inicio; aux!=NULL; aux=aux->prox)
    if(vert->id!=aux->id) remove_aresta(h,vert,aux);

  if(vert->ant==NULL){
    h->inicio=vert->prox;
    aresta=vert->inicio;
    while(aresta!=NULL){
      aresta2=aresta->prox;
      free(aresta);
      aresta=aresta2;
    }
    if(h->inicio==NULL)
      h->fim==NULL;
    else
      aux=h->inicio, aux->ant=NULL;
    free(vert);
  }
  else{
    aux=vert->ant, aux->prox=vert->prox;
    aresta=vert->inicio;
    while(aresta!=NULL){
      aresta2=aresta->prox;
      free(aresta);
      aresta=aresta2;
    }
    if(aux->prox==NULL)
      h->fim=aux;
    else
      aux2=aux->prox, aux2->ant=aux;
    free(vert);
  }
  return true;
}

int removeAresta_aux(head_st *h, int are1, int are2){
  vertice_st *vert1, *vert2;

  if(are1==are2) return false;

  vert1=verificaVertice(h, are1);
  if(vert1==NULL) return false;
  vert2=verificaVertice(h, are2);
  if(vert2==NULL) return false;

  return remove_aresta(h, vert1, vert2);
}

int remove_aresta(head_st *h, vertice_st *vert1, vertice_st *vert2){
  aresta_st *aux, *aux2, *aresta;

  aux=verificaAresta(vert1, vert2->id);
  if(aux==NULL) return false;
  aux2=verificaAresta(vert2, vert1->id);
  if(aux2==NULL) return false;

  if(aux->ant==NULL){
    aresta=aux->prox;
    vert1->inicio=aresta;
    if(vert1->inicio==NULL)
      vert1->fim=NULL;
    else
      aresta->ant=NULL;
    free(aux);
  }
  else{
    aresta=aux->ant, aresta->prox=aux->prox;
    if(aresta->prox==NULL)
      vert1->fim=aresta;
    else
      aresta=aux->prox, aresta->ant=aux->ant;
    free(aux);
  }

  if(aux2->ant==NULL){
    aresta=aux2->prox;
    vert2->inicio=aresta;
    if(vert2->inicio==NULL)
      vert2->fim=NULL;
    else
      aresta->ant=NULL;
    free(aux2);
  }
  else{
    aresta=aux2->ant, aresta->prox=aux2->prox;
    if(aresta->prox==NULL)
      vert2->fim=aresta;
    else
      aresta=aux2->prox, aresta->ant=aux2->ant;
    free(aux2);
  }
  return true;
}

int grau_vertice(head_st *h, int id){
  vertice_st *vert;
  aresta_st *are;
  int cont=0;

  vert=verificaVertice(h, id);
  if(vert==NULL) return -1;

  for(are=vert->inicio; are!=NULL; are=are->prox)
    cont++;

  return cont;
}

int grafo_conexo(head_st *h){
  vertice_st *v;

  if(h->inicio==NULL){
    return -1;
  }
  else{
    busca_largura(h, h->inicio->id);

    for(v=h->inicio; v!=NULL; v=v->prox)
      if(v->cor!=preto) return false;
    return true;
  }
}

void matriz(head_st *h){
  vertice_st *vert, *vert2;
  aresta_st *are;
  int i,cont=0;

  if(h->inicio==NULL) printf("Grafo Vazio!\n");
  else{
    printf("\n");
    for(i=0; i<h->elementos/2+1; i++)
      printf("   ");
    printf("MATRIZ DE ADJACENCIAS\n\n");
    printf("\n    |");
    for(vert=h->inicio; vert!=NULL; vert=vert->prox){
      printf("%4d ",vert->id);
      cont++;
    }
    printf("\n____|_");

    for(i=0; i<cont; i++)
      printf("_____");
    printf("\n");

    for(vert=h->inicio; vert!=NULL; vert=vert->prox){
      printf("%-4d|",vert->id);
      for(vert2=h->inicio; vert2!=NULL; vert2=vert2->prox){
        if(vert->id!=vert2->id){
          are=verificaAresta(vert, vert2->id);
          if(are==NULL)
            printf("%4d ",0);
          else
            printf("%4d ",are->peso);
        }
        else
          printf("%4d ",0);
      }
      printf("\n");
    }
  }
}

//FILA: inicializa, enfila, desenfila, filavazia
void inicializa(fila_st *f, head_st *h){
  f->v=(int*)malloc(h->elementos*sizeof(int));
  f->ini=0, f->fim=-1;
}

int filavazia(fila_st *f){
  if(f->fim==-1) return true;
  else return false;
}

int enfila(fila_st *f, int vert, head_st *h){
  f->fim=(f->fim+1)%h->elementos;
  f->v[f->fim]=vert;
}

int desenfila(fila_st *f, head_st *h){
  int ret=f->v[f->ini];
  if(f->ini!=f->fim)
    f->ini=(f->ini+1)%h->elementos;
  else
    inicializa(f,h);
  return ret;
}
//FIM_FILA

int busca_largura(head_st *h, int id){
  fila_st busca;
  vertice_st *v,*aux,*vert;
  aresta_st *are;

  vert=verificaVertice(h,id);
  if(vert==NULL){
    printf("Vertice nao existe!\n");
    return false;
  }

  inicializa(&busca, h);

  for(v=h->inicio; v!=NULL; v=v->prox){
    v->cor=branco;
    v->dist=infi;
    v->pai=-1;
  }
  vert->cor=cinza, vert->dist=0;
  enfila(&busca, vert->id, h);

  while(filavazia(&busca)==false){
    v=verificaVertice(h,desenfila(&busca, h));
    for(are=v->inicio; are!=NULL; are=are->prox){
      aux=verificaVertice(h, are->id);
      if(aux->cor==branco){
        aux->cor=cinza;
        aux->dist=v->dist+1;
        aux->pai=v->id;
        enfila(&busca, aux->id, h);
      }
    }
    v->cor=preto;
  }
  free(busca.v);
  return true;
}

void print_amplitude(head_st *h, int id){
  vertice_st *v;

  if(h->inicio==NULL) printf("Grafo Vazio!\n");
  else if(busca_largura(h,id)==true){
    printf("\n     BUSCA EM LARGURA\n\n");
    printf("Vertice |  Pai  | Distancia\n");
    printf("________|_______|__________\n");
    for(v=h->inicio; v!=NULL; v=v->prox)
      printf("%-7d | %-5d | %-9d\n",v->id,v->pai,v->dist);
  }
}

void profundidade_aux(head_st *h, int id, int *tempo){
  vertice_st *vert,*v;
  aresta_st *aux;

  vert=verificaVertice(h,id);
  vert->cor=cinza;
  vert->dist=++(*tempo);
  for(aux=vert->inicio; aux!=NULL; aux=aux->prox){
    v=verificaVertice(h,aux->id);
    if(v->cor==branco){
      v->pai=vert->id;
      profundidade_aux(h,v->id,tempo);
    }
  }
  vert->cor=preto;
  vert->final=++(*tempo);
}

int busca_profundidade(head_st *h){
  vertice_st *v;

  for(v=h->inicio; v!=NULL; v=v->prox){
    v->cor=branco;
    v->pai=-1;
  }
  int tempo=0;
  for(v=h->inicio; v!=NULL; v=v->prox)
    if(v->cor==branco) profundidade_aux(h,v->id,&tempo);
}

void print_profundidade(head_st *h){
  vertice_st *v;

  if(h->inicio==NULL){
    printf("Grafo Vazio!\n");
    return;
  }
  busca_profundidade(h);
  printf("\n         BUSCA EM PROFUNDIDADE\n\n");
  printf("Vertice | Descoberta | Finalizacao | Pai\n");
  printf("________|____________|_____________|_____\n");
  for(v=h->inicio; v!=NULL; v=v->prox){
    printf("%-7d | %-10d | %-11d | %d\n",v->id,v->dist,v->final,v->pai);
  }
}

//HEAP
void corrige_descendo(vertice_st **a, int *n, int i){
  int j=i, f;
  vertice_st *aux;

  while((2*j)<=(*n)){
    f=2*j;
    if((f<(*n)) && (a[f]->dist>a[f+1]->dist))
      f++;
    if(a[j]->dist<=a[f]->dist)
      j=(*n);
    else{
      aux=a[j], a[j]=a[f], a[f]=aux;
      j=f;
    }
  }
}

void corrige_subindo(vertice_st **a, int m){
  vertice_st *aux;
  int i=m;
  while(i>=2 && a[i/2]->dist>a[i]->dist){
    aux=a[i/2], a[i/2]=a[i], a[i]=aux;
    i=i/2;
  }
}

void min_heap(vertice_st **a, int *n){
  int i;

  for(i=(*n)/2; i>0; i--){
    corrige_descendo(a, n, i);
  }
}

vertice_st* extrai_min(vertice_st **a, int *n){
  vertice_st *max=a[1];
  a[1]=a[(*n)];
  (*n)--;
  //corrige_descendo(a,n,1);
  return max;
}

void insere_heap(vertice_st **a, int *n, vertice_st *c){
  a[(*n)+1]=c;
  corrige_subindo(a,(*n)+1);
}
//FIM_HEAP

void relaxa(vertice_st *v, vertice_st *u, int w){
  if(u->dist>(v->dist+w)){
    u->dist=v->dist+w;
    u->pai=v->id;
  }
}

int dijkstra(head_st *h, int id){
  vertice_st *v, *vert, *heap[h->elementos+1];
  aresta_st *are;
  int pos=0,i;

  vert=verificaVertice(h,id);
  if(vert==NULL) return -1;
  if(grafo_conexo(h)==false) return false;

  for(v=h->inicio; v!=NULL; v=v->prox){
    v->dist=999999;
    v->pai=-1;
    heap[++pos]=v;
  }
  vert->dist=0;
  min_heap(heap,&pos);

  while(pos>0){
    v=extrai_min(heap,&pos);
    for(are=v->inicio; are!=NULL; are=are->prox){
      vert=verificaVertice(h,are->id);
      relaxa(v,vert,are->peso);
    }
    min_heap(heap,&pos);
  }
}

int print_dijkstra(head_st *h, int id){
  int erro;
  vertice_st *v;

  erro=dijkstra(h,id);
  if(erro==false)
    printf("Grafo desconexo\n");
  else if(erro==-1)
    printf("Vertice não existe\n");
  else{
    printf("\n  ALGORITIMO DE DIJKSTRA\n\n");
    printf("Vertice |  Pai  | Distancia\n");
    printf("________|_______|__________\n");
    for(v=h->inicio; v!=NULL; v=v->prox)
      printf("%-7d | %-5d | %-9d\n",v->id,v->pai,v->dist);
  }
}

int prim(head_st *h, int id){
  vertice_st *v, *u, *heap[h->elementos+1];
  aresta_st *are;
  int pos=0,i;

  u=verificaVertice(h,id);
  if(u==NULL) return -1;
  if(grafo_conexo(h)==false) return false;

  for(v=h->inicio; v!=NULL; v=v->prox){
    v->dist=999999;
    v->pai=-1;
    heap[++pos]=v;
  }
  u->dist=0;
  min_heap(heap,&pos);

  while(pos>0){
    u=extrai_min(heap,&pos);
    for(are=u->inicio; are!=NULL; are=are->prox){
      v=verificaVertice(h,are->id);
      if(are->peso<v->dist){
        for(i=1; i<pos+1 && heap[i]->id!=v->id; i++);
        if(heap[i]->id==v->id){
          v->pai=u->id;
          v->dist=are->peso;
        }
      }
    }
    min_heap(heap,&pos);
  }
}

int print_prim(head_st *h, int id){
  int erro;
  vertice_st *v;

  erro=prim(h,id);
  if(erro==false)
    printf("Grafo desconexo\n");
  else if(erro==-1)
    printf("Vertice não existe\n");
  else{
    printf("\n    ALGORITIMO DE PRIM\n\n");
    printf("Vertice |  Pai  | Distancia\n");
    printf("________|_______|__________\n");
    for(v=h->inicio; v!=NULL; v=v->prox)
      printf("%-7d | %-5d | %-9d\n",v->id,v->pai,v->dist);
  }
}

void free_grafo(head_st *h){
  vertice_st *vert1, *vert2;
  aresta_st *are1, *are2;

  vert1=h->inicio;
  while(vert1!=NULL){
    vert2=vert1->prox;
    are1=vert1->inicio;
    while(are1!=NULL){
      are2=are1->prox;
      free(are1);
      are1=are2;
    }
    free(vert1);
    vert1=vert2;
  }
  free(h);
}
