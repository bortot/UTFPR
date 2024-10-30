/* 	este codigo tem como objetivo gerar um resumo
	da entrada de dados do trabalho de alg I
*/

#include <stdio.h>
#include <string.h>

int reconheceComando(char *texto);

int main(void){
  int indKey=0, indTag=0, cmd[8]={0,0,0,0,0,0,0,0}, cmdOld=0;
  int tamKey1=0, tamKey2=0, tamTag=0, cont=0, cont2=0, cont3=0;
  float medKey1=0, medKey2=0, medTag=0;
  char txt[1001];

  printf("#ENTRADA:\n\n");
	while(scanf(" %s", txt) == 1){
		int comando = reconheceComando(txt);

    if(cmdOld==1 && cmdOld!=comando){
      printf("|%-8d|Add Keys\t\t|\n",cont);
      cont=0;
    }
    else if(cmdOld==2 && cmdOld!=comando){
      printf("|%-8d|Tag Hits\t\t|\n",cont2);
      cont2=0;
    }
    else if(cmdOld==3 && cmdOld!=comando){
      printf("|%-8d|Show Tagcontent\t|\n",cont3);
      cont3=0;
    }
    cmdOld = comando;

		if(comando == 1){
      //Add Key
      scanf(" %[^:] %*s",txt);
      tamKey1 += strlen(txt);
    	scanf(" %[^\n]",txt);
      tamKey2 += strlen(txt);
      cont++, cmd[0]++;
		}else if(comando == 2){
			//TagHit
      scanf(" %*c%s %*s",txt);
      tamTag += strlen(txt);
      cont2++, cmd[1]++;
		}else if(comando == 3){
			//Show
      scanf(" %*s");
      cont3++, cmd[2]++;
		}else if(comando == 4){
			//List Top
      scanf(" %*s");
      printf("|        |List Top\t\t|\n");
      cmd[3]++;
		}else if(comando == 5){
			//List Bottom
      scanf(" %*s");
      printf("|        |List Bottom\t\t|\n");
      cmd[4]++;
		}else if(comando == 6){
      //Dump Tag
      printf("|        |Dump Tag\t\t|\n");
      cmd[5]++;
		}else if(comando == 7){
			//Dump Key
      printf("|        |Dump Key\t\t|\n");
      cmd[6]++;
    }else if(comando == 8){
      //New Day
      printf("|        |New Day\t\t|\n");
      cmd[7]++;
    }
  }

  if(cmd[0]!=0){
    medKey1 = (float)tamKey1/cmd[0];
    medKey2 = (float)tamKey2/cmd[0];
  }
  if(cmd[1]!=0)
    medTag = tamTag/cmd[1];

  printf("\n#RESUMO:\n\n");
  printf("%-6d Add Keys\n",cmd[0]);
  printf("%-6d Tag Hits\n",cmd[1]);
  printf("%-6d Show\n",cmd[2]);
  printf("%-6d List Top\n",cmd[3]);
  printf("%-6d List Bottom\n",cmd[4]);
  printf("%-6d Dump Tag\n",cmd[5]);
  printf("%-6d Dump Keys\n",cmd[6]);
  printf("%-6d New Day\n",cmd[7]);
  printf("Tamanho medio das keys: %.2f\n",medKey1);
  printf("Tamanho medio do conteudo das keys: %.2f\n",medKey2);
  printf("Tamanho medio das tags: %.2f\n",medTag);

	return 0;
}

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
