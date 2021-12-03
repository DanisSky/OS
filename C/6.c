#include <dirent.h>
#include <unistd.h>
#include <limits.h>
#include <stdio.h>
//DONE
int main(int argc[], char * argv[], char * envp[]) {
  DIR * dir;
  struct dirent * ent;

  char PathName[PATH_MAX];
  if ((dir = opendir(getcwd(PathName, PATH_MAX))) != NULL) {
    while ((ent = readdir(dir)) != NULL) {
      printf("%s\n ", ent -> d_name);
    }
    closedir(dir);
  } else {

    perror(" ");
    return -1;

  }

  if ((dir = opendir(argv[1])) != NULL) {
    while ((ent = readdir(dir)) != NULL) {
      printf("%s\n ", ent -> d_name);
    }
    closedir(dir);
  } else {
    perror(" ");
    return -1;

  }
}