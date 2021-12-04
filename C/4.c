#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

char * fget_line(char * buffer, int max, FILE * fp);

int main(int argc[], char * argv[], char * envp[]) {
  FILE * file;
  char * filename = argv[1];
  int n = strtol(argv[2], NULL, 10);
  char buff[256];
  int flag = 1;

  file = fopen(filename, "r");

  if (n < 0) {
    printf("N >= 0 %d", n);
    return 1;
  }

  if (file == NULL) {
    printf("Error: could not open file %s", filename);
    return 1;
  }
  if (n == 0) {
    while (fget_line(buff, sizeof(buff), file)) {
      printf("%s", buff);
    }
    printf("%s", buff);
  } else {
    while (flag) {
      getc(stdin);
      for (int i = 0; i < n; i++) {
        if (!fget_line(buff, sizeof(buff), file)) {
          flag = 0;
          break;
        }
        printf("%s", buff);
      }
    }
    printf("%s", buff);
  }
  if (fclose(file) != 0) {
    fprintf(stderr, "Can't close file\n");
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