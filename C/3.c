	#include <sys/types.h>
	#include <sys/stat.h>
	#include <fcntl.h>
	#include <stdio.h>
	#include <signal.h>
	int INPUT_END=1;

	void setInput(){
		INPUT_END=0;
	}

	int main(int argc, char const *argv[], char *envp[])
	{
		FILE *file;
		file=fopen(argv[1], "w");

		signal(SIGINT, setInput);

		if (file==NULL) {
			fprintf(stderr, "\nCan't open file\n");
			return -1;
		}
		int ch;

		while ((ch=getc(stdin))!=EOF && INPUT_END)
			fputc(ch, file);

		if (fclose(file)!=0){
			fprintf(stderr, "\nCan't close file\n");
		}

		return 0;
	}