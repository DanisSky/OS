#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
 // DONE
char * fget_line(char * buffer, int max, FILE * fp);
void write_line(char * buffer, int max, FILE * fp);

int main(int argc[], char * argv[], char * envp[]) {
  FILE * file;
  FILE * file2;
  char * filename = argv[1];
  char * filename2 = argv[2];
  char buff[256];

  file = fopen(filename, "r");
  file2 = fopen(filename2, "w");
  if (file == NULL) {
    printf("Error: could not open file %s", filename);
    return 1;
  }

  struct stat st;
  stat(filename, & st);
  chmod(filename2, st.st_mode);

  while (fget_line(buff, sizeof(buff), file)) {
    write_line(buff, sizeof(buff), file2);
  }
  write_line(buff, sizeof(buff), file2);
  if (fclose(file)!=0){
      fprintf(stderr, "Can't close file\n");
    }
  if (fclose(file2)!=0){
      fprintf(stderr, "Can't close file2\n");
    }

  return 0;
}

char * fget_line(char * buffer, int max, FILE * fp) {
  int c;
  char * p;
  for (p = buffer, max--; max > 0; max--) {
    if ((c = fgetc(fp)) == EOF)
      break;
    * p++ = c;
    if (c == '\n')
      break;
  }
  * p = 0;
  if (p == buffer || c == EOF)
    return NULL;
  return (p);
}

void write_line(char * buffer, int max, FILE * fp) {
  int c;
  char * p;
  for (p = buffer, max; max > 0; max--) {
    c = * p++;
    if (c == 0)
      break;
    fputc(c, fp);
  }
}