#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>


int inputControl(char input[]);
char* toLowerCase(char input[]);
void helpMessage();

//islem kolayligi icin fonksiyonlarin parametrelerini global'de tutuyorum
char* execxParameters[] = {NULL,NULL,NULL};
char* catParameters[] = {"/bin/cat",NULL,NULL};
char* lsParameters[] = {"/bin/ls",NULL,NULL};

int main(){
	
	printf("-----------------------------------------\n");
	printf("Welcome to myshell!\n");
	printf("Say 'help' to see the available commands.\n");
	printf("-----------------------------------------\n");
	char input[30];
	
	while(1){
		
		printf("myshell>> ");
		fgets(input,30,stdin);
		//switch case yapisiyle shell simulasyonu yapiyorum.
		
		switch(inputControl(input)){
			
			case 1:
			helpMessage();
			break;
			
			case 2:
			execx(execxParameters);
			break;
			
			case 3:
			callCatOrLs(catParameters);
			break;

			case 4:
			callClear();
			break;
			
			case 5:
			callCatOrLs(lsParameters);
			break;
			
			case 6:
			callBash();
			break;
			
			case 0:
			exit(1);
			break;
			
			default:
			printf("Wrong command! Say 'help' to see available commands.\n");
			break;
		}
		
	}
}

void execx(char* parameters[]){
	//execx fonksiyonum execx file'ini aciyor
	int i;
	int f;
	f = fork();
	if(f==0){
		i = execvp("./e", parameters);
		perror("error");
	}
	else{
		wait(&i);
	}
}

void callBash(){
	//bash programini cagiriyorum
	int i;
	int f;
	char * argv_list[] = {"/bin/bash",NULL};
	f=fork();
	if(f==0){
		
		i = execvp(argv_list[0], argv_list);
		perror("hata");
	}
	else{
		wait(&i);		
	}
}

void callCatOrLs(char* parameters[]){
	//ikisinin de islemi ayni ve sadece parametreleri farkli oldugu icin
	//cat ve ls'i ayni fonksiyonda yapiyorum
	int i;
	int f;
	f=fork();
	if(f==0){
		
		i = execvp(parameters[0], parameters);
		perror("hata");
	}
	else{
		wait(&i);		
	}	
}

void callClear(){
	int i;
	int f;
	char * argv_list[] = {"clear",NULL};
	f=fork();
	if(f==0){
		
		i = execvp(argv_list[0], argv_list);
		perror("hata");
	}
	else{
		wait(&i);		
	}	
}


int inputControl(char input[]){

	//token arrayi olusturup input stringini bosluk yerlerine gore boluyorum.

	char tokens [20][20] = {{NULL}};
	
	int j = 0;
	int ctr = 0;
	for(int i = 0; i<=(strlen(input));i++){
		if(input[i]==' '||input[i]=='\0'){
			tokens[ctr][j] = '\0';
			ctr++;
			j=0;
		}
		else{
			tokens[ctr][j]=input[i];
			j++;
		}
	}
	
	//komutlari karsilastirmak icin hazirladigim stringler
	char StrHelp[] = "help\n";
	char StrExit[] = "exit\n";
	char StrBash[] = "bash\n";
	char StrCat[] = "cat";
	char StrClear[] = "clear\n";
	char StrLs[] = "ls";
	char StrExecx1[] = "execx";
	char StrExecx2[] = "-t";
	char StrWritef1[] = "writef";
	char StrWritef2[] = "-f";
	
	if((strcmp(toLowerCase(tokens[0]),StrHelp)) == 0){
		return 1;
	}
	else if((strcmp(toLowerCase(tokens[0]),StrExecx1))==0){ //exec fonksiyonunun input kontrolleri
		if((strcmp(toLowerCase(tokens[1]),StrExecx2))==0){
			if(isInteger(tokens[2])==1){
				if((strcmp(toLowerCase(tokens[3]),StrWritef1))==0){
					if((strcmp(toLowerCase(tokens[4]), StrWritef2)) == 0 && tokens[5][0] != NULL && tokens[6][0] == NULL){
						execxParameters[0]=tokens[2];
						execxParameters[1]=tokens[5];
						return 2;
					}
				}
			}
		}
	}
	else if((strcmp(toLowerCase(tokens[0]),StrCat)) == 0 && tokens[1] != NULL){
		catParameters[1] = tokens[1];
		return 3;
	}
	else if((strcmp(toLowerCase(tokens[0]),StrClear)) == 0){
		return 4;
	}
	else if((strcmp(toLowerCase(tokens[0]),StrLs)) == 0 && tokens[1] != NULL){
		char * token = tokens[1];
		token[strcspn(token,"\n")] = 0;
		lsParameters[1] = token;
		return 5;
	}
	else if((strcmp(toLowerCase(tokens[0]),StrBash))==0){
		return 6;
	}
	else if((strcmp(toLowerCase(tokens[0]),StrExit))==0){
		return 0;
	}else{
		return -1;
	}
	

	

}

char* toLowerCase(char input[]){ //girilen input case sensitive olmasin diye kullaniyorum.
	int len = strlen(input);
	for(int i = 0; i<len;i++){
		input[i]=tolower(input[i]);	
	}
	return input;
}

int isInteger(char input[]){ //isdigit kullanarak string integer mi diye kontrol ediyorum.
	printf("%s",input);
	int length = strlen(input);
	for(int i = 0;i<length-1;i++){
		if(!isdigit(input[i])){
			return 0;
		}
	}
	return 1;
}

void helpMessage(){ //help komutunda bastirdigim mesaj
	
	printf("*********************************\n");
	printf("execx -t (x) writef -f (y) --> Run the writef program (x) times, append to (y) file\n");
	printf("cat x --> Outputs (x) file\n");
	printf("clear --> Clears the terminal\n");
	printf("ls x --> Shows the files inside of (x)\n");
	printf("bash --> Calls the bash program\n");
	printf("exit --> Exits myshell\n");
	printf("*********************************\n");
	
}
