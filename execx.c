#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>


int main(int argc, char* argv[]){
	
	int numberOfTimes = atoi(argv[0]); //string olarak gelen argumani int'e ceviriyorum.
	int x;
	int f;
	char * argv_list[] = {argv[1],NULL}; 
	for(int i = 0; i<numberOfTimes;i++){
		if(fork()==0){
			x = execvp("./w", argv_list);
			perror("hata");
			exit(0);
		}
	}
	for(int i = 0;i<numberOfTimes;i++){
		wait(NULL);
	}
}
