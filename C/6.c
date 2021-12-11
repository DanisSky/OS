#include <dirent.h>
#include <unistd.h>
#include <limits.h>
#include <stdio.h>
//DONE
void my_print(char * path);
int main(int argc[], char * argv[], char * envp[]) {
  char PathName[PATH_MAX];
    my_print(getcwd(PathName, PATH_MAX));
    my_print(argv[1]);
}

void my_print(char * path) {
  DIR * dir;
  struct dirent * ent;
  if ((dir = opendir(path)) != NULL) {
    while ((ent = readdir(dir)) != NULL) {
      printf("%s\n ", ent -> d_name);
    }
    closedir(dir);
  } else {
    perror(" ");
  }
}