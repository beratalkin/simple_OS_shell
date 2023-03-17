#include <stdio.h>
#include <stdlib.h>
#include <time.h>



int main(int argc, char* argv[]){

	//ppid ve pid degerlerini alip time.h library'sindeki time fonksiyonuyla şimdiki zamanla birlikte bastiriyorum.
	char strPid[10];
	sprintf(strPid, "%d", getpid());
	char strPpid[10];
	sprintf(strPpid, "%d", getppid());
	
	char str[50] = "Pid = ";
	time_t t;
	time(&t);
	
	strcat(str,strPid);
	strcat(str,", Ppid = ");
	strcat(str,strPpid);
	strcat(str,", ");
	strcat(str,ctime(&t));
	
	FILE *fp;
	fp = fopen(argv[0],"a+");
	fputs(str,fp);
	fclose(fp);
	
	return 0;

	
}
