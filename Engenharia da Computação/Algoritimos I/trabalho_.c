/*Inicio do Trabalho 01 AED22CP*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define falso 0
#define verd 1
#define ordLim 12
#define AUTHKEY "c42eee84"

typedef struct tagKey{
	char *txt;
	char *txt2;
	int qt;
}tagKey;

typedef struct list{
	char *tag;
	int qt;
}list;

int reconheceComando(char *texto);
void faddKey(tagKey *aux);
void ftagHit(tagKey *aux);
void fShowTagcontent(tagKey *key, tagKey *tag, int k, int j);
void fDumpTags(list *l, int tam, tagKey *tag, int tamTag);
void fDumpKey(int indKey, tagKey *comKey);
void fListTop(int num, int tamList, list *l);
void fListBottom(int num, int tamList, list *l);
int newDay(tagKey *t, int indTag);
int tiraNum(void);
void quickChar(tagKey *t, int p, int r, int cont);
int buscaChar(tagKey *t, int p, int r, char *auxp);
int contLista(list *l, tagKey *t, int indTag);
void mergeaList(list *t, int p, int r);
void posKey(tagKey *k, tagKey *t, list *l, int indKey, int indTag, int tamLista);
void quickListLexi2(list *t, int p, int r);
void insertionchar(tagKey *t, int tam, int ultPos);

int main(void){
	char texto[5];
	int keyOrd=falso, tagOrd=falso, tamListOrd=falso, posKeyOrd = verd, listLexiOrd = verd;
	int tamLista, ultPosKey=0, ultPosTag=0;
	int tamT=50, tamK=50;
	int k,j,oldTag=0;
	char *txt;
	tagKey *comKey, *comTag;
	list *listTag;
	comKey = (tagKey*)malloc(tamK*sizeof(tagKey));
	comTag = (tagKey*)malloc(tamT*sizeof(tagKey));
	listTag = (list*)malloc(tamT*sizeof(list));
	int indKey=0, indTag=0;
	while(scanf(" %s", texto) == 1){
		int comando = reconheceComando(texto);
		if(comando == 1){
			//addKey
			faddKey(&comKey[indKey++]);
			keyOrd = falso;
			if(indKey==tamK){
				tamK+=100;
				comKey = (tagKey*)realloc(comKey, tamK*sizeof(tagKey));
			}
		}else if(comando == 2){
			//TagHit
			ftagHit(&comTag[indTag++]);
			tagOrd = falso, tamListOrd = falso, posKeyOrd = falso, listLexiOrd = falso;
			if(indTag==tamT){
				tamT+=100;
				comTag = (tagKey*)realloc(comTag, tamT*sizeof(tagKey));
				listTag = (list*)realloc(listTag, tamT*sizeof(list));
			}
		}else if(comando == 3){
			//Show
			scanf(" %*c%ms",&txt);
			if(tagOrd == falso){
				k = buscaChar(comTag, 0, ultPosTag - 1, txt);
				if(k == -1){
					if(indTag - ultPosTag > ordLim){
						quickChar(comTag, 0, indTag -1, 0);
						insertionchar(comTag, indTag, 1);
					}else
						insertionchar(comTag, indTag, ultPosTag);
					tagOrd = verd, ultPosTag = indTag;
					k = buscaChar(comTag, 0, indTag - 1, txt);
				}
			}
			else
				k = buscaChar(comTag, 0, indTag - 1, txt);
			if(keyOrd == falso){
				j = buscaChar(comKey, 0, ultPosKey - 1, comTag[k].txt2);
				if(j == -1){
					if(indKey - ultPosKey > ordLim){
						quickChar(comKey, 0, indKey - 1, 0);
						insertionchar(comKey, indKey, 1);
					}else
						insertionchar(comKey, indKey, ultPosKey);
					keyOrd = verd, ultPosKey = indKey;
					j = buscaChar(comKey, 0, indKey - 1, comTag[k].txt2);
				}
			}
			else
				j = buscaChar(comKey, 0, indKey - 1, comTag[k].txt2);
			fShowTagcontent(comKey, comTag, k, j);
		}else if(comando == 6){
			//Dump Tag
			if(tamListOrd==falso){
				if(tagOrd == falso){
					if(indTag - ultPosTag > ordLim){
						quickChar(comTag, 0, indTag -1, 0);
						insertionchar(comTag, indTag, 1);
					}else
						insertionchar(comTag, indTag, ultPosTag);
					tagOrd = verd, ultPosTag = indTag;
				}
				free(listTag);
				listTag = (list*)malloc(tamT*sizeof(list));
				tamLista = contLista(listTag, comTag, indTag);
				tamListOrd = verd, listLexiOrd = verd;
			}
			if(listLexiOrd == falso){
				quickListLexi2(listTag, 0, tamLista-1);
				listLexiOrd=verd;
			}
			fDumpTags(listTag, tamLista, comTag, indTag);
		}else if(comando == 7){
			//Dump Key
			if(keyOrd == falso){
				if(indKey - ultPosKey > ordLim){
					quickChar(comKey, 0, indKey - 1, 0);
					insertionchar(comKey, indKey, 1);
				}else
					insertionchar(comKey, indKey, ultPosKey);
				keyOrd = verd, ultPosKey = indKey;
			}
			if(tamListOrd==falso){
				if(tagOrd == falso){
					if(indTag - ultPosTag > ordLim){
						quickChar(comTag, 0, indTag -1, 0);
						insertionchar(comTag, indTag, 1);
					}else
						insertionchar(comTag, indTag, ultPosTag);
					tagOrd = verd, ultPosTag = indTag;
				}
				free(listTag);
				listTag = (list*)malloc(tamT*sizeof(list));
				tamLista = contLista(listTag, comTag, indTag);
				tamListOrd = verd;
			}
			if(posKeyOrd == falso)
				posKey(comKey, comTag, listTag, indKey, indTag, tamLista);
			posKeyOrd = verd;
			fDumpKey(indKey, comKey);
		}else if(comando == 4){
			//ListTop
			if(tamListOrd==falso){
				if(tagOrd == falso){
					if(indTag - ultPosTag > ordLim){
						quickChar(comTag, 0, indTag -1, 0);
						insertionchar(comTag, indTag, 1);
					}else
						insertionchar(comTag, indTag, ultPosTag);
					tagOrd = verd, ultPosTag = indTag;
				}
				free(listTag);
				listTag = (list*)malloc(tamT*sizeof(list));
				tamLista = contLista(listTag, comTag, indTag);
				tamListOrd = verd;
			}
			listLexiOrd = falso;
			mergeaList(listTag, 0, tamLista-1);
			int num = tiraNum();
			fListTop(num, tamLista, listTag);
		}else if(comando == 5){
			//ListBottom
			if(tamListOrd==falso){
				if(tagOrd == falso){
					if(indTag - ultPosTag > ordLim){
						quickChar(comTag, 0, indTag -1, 0);
						insertionchar(comTag, indTag, 1);
					}else
						insertionchar(comTag, indTag, ultPosTag);
					tagOrd = verd, ultPosTag = indTag;
				}
				free(listTag);
				listTag = (list*)malloc(tamT*sizeof(list));
				tamLista = contLista(listTag, comTag, indTag);
				tamListOrd = verd;
			}
			listLexiOrd = falso;
			mergeaList(listTag, 0, tamLista-1);
			int num = tiraNum();
			fListBottom(num, tamLista, listTag);
		}else if(comando == 8){
			if(oldTag==indTag)
				indTag=0;
			else{
				indTag = newDay(comTag, indTag);
				oldTag = indTag;
			}
			comTag = (tagKey*)realloc(comTag, indTag*sizeof(tagKey));
			tamT = indTag+50;
			comTag = (tagKey*)realloc(comTag, tamT*sizeof(tagKey));
			listTag = (list*)realloc(listTag, tamT*sizeof(list));
			tagOrd = falso, tamListOrd = falso, posKeyOrd = falso, listLexiOrd = falso, ultPosTag = 0;
		}
	}

	return 0;
}
/* Comandos a serem reconhecidos:
	add key -------------- 1
	tag hit -------------- 2
	show tagcontent ------ 3
	list trending top ---- 4
	list trending bottom - 5
	dump tags ------------ 6
	dump keys ------------ 7
	new day -------------- 8
*/
int reconheceComando(char *texto){
	char cmd;
	if(texto[0] == 'a'){
		scanf(" %*s");
		return 1;
	}else if(texto[0] == 't'){
		scanf(" %*s");
		return 2;
	}else if(texto[0] == 's'){
		scanf(" %*s");
		return 3;
	}else if(texto[0] == 'l'){
		scanf("%*s %c%*s",&cmd);
		if(cmd == 't')
			return 4;
		else
			return 5;
	}else if(texto[0] == 'd'){
		scanf(" %c%*s",&cmd);
		if(cmd == 't')
			return 6;
		else
			return 7;
	}else if(texto[0] == 'n'){
		scanf(" %*s");
		return 8;
	}
}

void faddKey(tagKey *aux){
	scanf(" %m[^:] %*s",&aux->txt);
	scanf(" %m[^\n]",&aux->txt2);
	aux->qt = 0;
}

void ftagHit(tagKey *aux){
	scanf(" %*c%ms",&aux->txt);
	scanf("%ms",&aux->txt2);
	aux->qt=1;
}

void fShowTagcontent(tagKey *key, tagKey *tag, int k, int j){
	printf("#%s -> %s\n", tag[k].txt, tag[k].txt2);
	printf("%s :. %s\n", tag[k].txt2, key[j].txt2);
}
//Funcionando Falta Fazer a Order Alfabeitca
void fDumpTags(list *l, int tam, tagKey *tag, int tamTag){
	int i, j;
	printf("8<----------Begin Tag Dump----------\n");
	for(i=tam-1; i>=0; i--){
		j = buscaChar(tag, 0, tamTag, l[i].tag );
		printf("#%s -> %s :: hits=%d\n", l[i].tag, tag[j].txt2, l[i].qt);
	}
	printf("8<----------End   Tag Dump----------\n");
}
//Funcionando Falta Fazer a Order Alfabeitca
void fDumpKey(int indKey, tagKey *comKey){
	int i;
	printf("8<----------Begin Key Dump----------\n");
	for(i=0; i<indKey;i++)
		printf("%s content=\"%s\" refs=%d\n", comKey[i].txt, comKey[i].txt2, comKey[i].qt);
	printf("8<----------End   Key Dump----------\n");
}

void fListTop(int num, int tamList, list *l){
	int i,p, cont=1, n=0;
	p = tamList*num/100;
	printf("Begin %d%% top trending\n", num);
	for(i=tamList-1; n<p; i--){
		printf("%-3d #%s with %d hits\n",cont, l[i].tag,l[i].qt);
		if(i!=0 && l[i].qt != l[i - 1].qt) cont++;
		n++;
	}
	printf("End Trending\n");
}

void fListBottom(int num, int tamList, list *l){
	int i,p, cont=tamList, n=0;
	p = tamList*num/100;
	printf("Begin %d%% bottom trending\n", num);
	for(i=0; i<p; i++){
		if(i!=0 && l[i].qt != l[i - 1].qt) cont--;
		printf("%-3d #%s with %d hits\n",cont, l[i].tag,l[i].qt);
	}
	printf("End Trending\n");
}

int newDay(tagKey *t, int indTag){
	int i, j=0;
	for(i=0; i<indTag; i++)
		if(--t[i].qt == 0)
			t[j++]=t[i];
		else{
			free(t[i].txt);
			free(t[i].txt2);
		}
	return j;
}

//Funcao para os comandos List, apenas retira a % para ser mostrada e utilizada em funcoes futuras
int tiraNum(void){
	char txt_num[4];
	int i=0, num=0;
	scanf(" %s",txt_num);
	while(txt_num[i] != '\0'){
		num = num*10 + (txt_num[i] - 48);
		i++;
	}
	return num;
}

void insertionchar(tagKey *t, int tam, int ultPos){
	int i,j;
	tagKey x;

	for(i=ultPos; i<tam; i++){
		x = t[i];
		j = i-1;
		while((j>=0) && (strcmp(x.txt,t[j].txt)<0))
			t[j+1] = t[j--];
		if(j!=(i-1))
			t[j+1] = x;
	}
}

void colacaPivoChar(tagKey *t, int p, int r){
	int a, b, c, n;
	b = (p + r)/2;
	if(b>p){
		a = lrand48() % (b - p) + p;
		c = lrand48() % (r - b) + b;
		if( strcmp(t[a].txt, t[b].txt) > 0)
			n=a,a=b, b=n;
		if(strcmp(t[b].txt, t[c].txt) > 0)
			n=b, b=c, c=n;
		if(strcmp(t[a].txt, t[b].txt) > 0)
			n=a,a=b,b=n;
		tagKey aux;
		aux = t[p], t[p] = t[b], t[b] = aux;
	}
}

int separaChar(tagKey *t, int p, int r){
	colacaPivoChar(t,p,r);
    tagKey c = t[p], aux;
    int i=p + 1, j=r;
    while (i<=j){
        if(strcmp(t[i].txt, c.txt) < 0)
            i++;
        else if(strcmp(c.txt, t[j].txt) < 0)
            j--;
        else{
            aux = t[i], t[i]=t[j], t[j]=aux;
            j--, i++;
        }
    }
    t[p] = t[j];
    t[j] = c;
    return j;
}

void quickChar(tagKey *t, int p, int r, int cont){
   int j;
    if(r-p<20 || cont > 3)
			return;
	  j = separaChar(t, p, r);
		if(j == (p+r)/2)
			cont++;
	  quickChar(t, p, j-1, cont);
    quickChar(t, j+1, r, cont);
}

int buscaChar(tagKey *t, int p, int r, char *auxp){
	if (p>r) return -1;
	int meio =(p+r)/2;
	if (strcmp(t[meio].txt, auxp) > 0) return buscaChar(t, p, meio-1, auxp);
	else if(strcmp(t[meio].txt, auxp) < 0) return buscaChar(t,meio+1, r, auxp);
	else if(strcmp(t[meio].txt, auxp) == 0) return meio;
}

int contLista(list *l, tagKey *t, int indTag){
	int i, j=0;
	for(i=indTag-1; i>=0; i--){
		l[j].tag = (char*)malloc(strlen(t[i].txt)+1);
		strcpy(l[j].tag, t[i].txt);
		l[j].qt = t[i].qt;
		while(i-1>=0 && strcmp(t[i].txt, t[i-1].txt) == 0)
			l[j].qt += t[--i].qt;
		j++;
	}
	return j;
}

void colacaPivoList(list *t, int p, int r){
	int a, b, c, n;
	b = (p + r)/2;
	if(b>p){
		a = lrand48() % (b - p) + p;
		c = lrand48() % (r - b) + b;
		if( t[a].qt > t[b].qt)
			n=a,a=b, b=n;
		if(t[b].qt> t[c].qt)
			n=b, b=c, c=n;
		if(t[a].qt > t[b].qt)
			n=a,a=b,b=n;
		list aux;
		aux = t[p], t[p] = t[b], t[b] = aux;
	}
}

int separaList(list *t, int p, int r){
	colacaPivoList(t, p, r);
    list c = t[p], aux;
    int i= p + 1, j=r;
    while (i<=j) {
        if(t[i].qt < c.qt)
            i++;
        else if(t[j].qt > c.qt)
            j--;
        else{
            aux = t[i], t[i]=t[j], t[j]=aux;
            j--, i++;
        }
    }
    t[p] = t[j];
    t[j] = c;
    return j;
}

void posKey(tagKey *k, tagKey *t, list *l, int indKey, int indTag, int tamLista){
	int i;
	for(i=0;i<indKey; i++) k[i].qt=0;
	for(i=0; i<tamLista; i++){
		int j=buscaChar(t, 0, indTag-1, l[i].tag);
		int a=buscaChar(k, 0, indKey-1, t[j].txt2);
		k[a].qt++;
	}
}

list* mergeab(list *a, list *b, int tamA, int tamB){
  list *c=(list*)malloc(sizeof(list)*(tamA+tamB));
  int ia=0, ib=0, ic;
  for(ic = 0; ic<tamA+tamB && ia<tamA && ib<tamB; ic++){
    if(a[ia].qt<=b[ib].qt)
    	c[ic]=a[ia++];
    else
    	c[ic]=b[ib++];
  }
  while (ia<tamA)
    c[ic++]=a[ia++];
  while (ib<tamB)
    c[ic++]=b[ib++];
  return c;
}

void intercala(list *t, int l, int m, int r){
  list *novo=mergeab(&t[l], &t[m+1], m-l+1, r-m);
  int i, k=r-l;
  for(i=0; i<=k; i++)
    t[l++]=novo[i];
  free(novo);
}

void mergeaList(list *t, int p, int r){
  if(p>=r) return;
  int m=(p+r)/2;
  mergeaList(t, p, m);
  mergeaList(t, m+1, r);
  intercala(t, p, m, r);
}
void colacaPivoLexi(list *t, int p, int r){
	int a, b, c, n;
	b = (p + r)/2;
	if(b>p){
		a = lrand48() % (b - p) + p;
		c = lrand48() % (r - b) + b;
	if(strcmp(t[a].tag, t[b].tag) > 0)
		n=a,a=b, b=n;
	if(strcmp(t[b].tag, t[c].tag) > 0)
		n=b, b=c, c=n;
	if(strcmp(t[a].tag, t[b].tag) > 0)
		n=a,a=b,b=n;
	list aux;
	aux = t[p], t[p] = t[b], t[b] = aux;
	}
}

int separaListLexi2(list *t, int p, int r){
	colacaPivoLexi(t, p ,r);
    list c = t[p], aux;
    int i= p + 1, j=r;

    while (i<=j) {
        if(strcmp(t[i].tag, c.tag) > 0)
            i++;
        else if(strcmp(c.tag, t[j].tag) > 0)
        	j--;
        else{
            aux = t[i], t[i]=t[j], t[j]=aux;
            j--, i++;
        }
    }
    t[p] = t[j];
    t[j] = c;
    return j;
}

void quickListLexi2(list *t, int p, int r){
   int j;
    if(p<r){
        j = separaListLexi2(t, p, r);
        quickListLexi2(t, p, j-1);
        quickListLexi2(t, j+1, r);
    }
}
