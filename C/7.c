#include <stdio.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <inttypes.h>
#include <stdlib.h>

void dirout(DIR * cdir, char * path, char * file_name);
void write_file_info(char *
  var, char * name);

int dir_cnt;
int file_cnt;

int main(int argc, char * argv[], char * envp[]) {
  dir_cnt = 0;
  file_cnt = 0;
  DIR * dir;
  char * file_name;
  if (argc < 3) {
    fprintf(stderr, "Too few arguments\n");
    return 1;
  }
  dir = opendir(argv[1]);
  file_name = argv[2];
  if (errno == ENOTDIR) {
    perror("Isn't dir");
    return 1;
  }
  dirout(dir, argv[1], file_name);
  closedir(dir);
  return 0;
}

void dirout(DIR * cdir, char * path, char * file_name) {
  DIR * hdir;
  char *var = (char*) malloc(1000);
  struct dirent * entry;
  int flag = 0;

  if (!strcmp(path, "/")) {
    path[0] = '\0';
  }
  while ((entry = readdir(cdir)) != NULL) {
      if(!strcmp(entry-> d_name, ".") | !strcmp(entry-> d_name, "..")){
          continue;
      }
    sprintf(var, "%s/%s", path, entry -> d_name);
    hdir = opendir(var);
    if (errno == ENOTDIR) {
      file_cnt++;
      if (!strcmp(entry -> d_name, file_name)) {
        printf("dirs - %d files - %d\n", dir_cnt, file_cnt);
        write_file_info(var, file_name);
        break;
      }
    } else {
      dir_cnt++;
      dirout(hdir, var, file_name);
      flag = 1;
    }
  }
  if (flag == 1)
    closedir(hdir);
}

void write_file_info(char * path, char * name) {
  struct stat st1;
  stat(path, & st1);
  printf("%s %s %lu %lu %d %lu\n", path, name, st1.st_size, st1.st_mtime, st1.st_mode, (uintmax_t) st1.st_ino);
}