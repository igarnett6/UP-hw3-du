//unix programming hw3
//du.c
//isaiah garnett
//ig907
#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>
#include <string.h>
#include <limits.h>


//prototypes
void listDirs(char dirname[], char *knownInodes[], char *allPaths[]);
long getSize(char dirname[]);



int main(int argc, char *argv[]){
  char **allPaths;
  char *initAP = (char*)malloc(4096);
  initAP[0] = '\0';
  allPaths = &initAP;
  char **knownInodes;
  char *initKINO = malloc(2048);
  initKINO[0] = '\0';
  knownInodes = &initKINO;
  if(argc == 1){
    listDirs(".", knownInodes, allPaths);
  }
  else if(argc == 2){
    listDirs(argv[1], knownInodes, allPaths);
  }
  else{
    perror("Invalid input. Use format: du [directory name]\n");
    exit(1);
  }
  // printf("KNOWNINODES:\n%s\n\n", *knownInodes);

  // printf("ALLPATHS:\n%s\n\n", *allPaths);
  char *token = strtok(*allPaths, "\n");
  DIR *dirp;
  char realPath[4096];
  while(token != NULL){
    realpath(token, realPath);
    if((dirp = opendir(realPath)) != NULL){
      printf("%ld\t\t%s\n", getSize(token), token);
    }
    token = strtok(NULL, "\n");
  }

  // free(*allPaths);
  // free(allPaths);
  free(initKINO);
  // free(knownInodes);
  free(initAP);
  // free(ld);
  return 0;
}





void listDirs(char dirname[], char *knownInodes[], char *allPaths[]){ //change to void function which passes allPaths from main modifying it directly
  //allPaths should be passed the same way as knownInodes to manage memory

//allPaths should be passed the same way as knownInodes to manage memory
    DIR *dirp;
    struct dirent *direntp;
    struct stat info;
    if((dirp = opendir(dirname)) != NULL){
      // printf("DIRNAME: %s\n", dirname);
      while((direntp = readdir(dirp)) != NULL){
        // printf("DIRENTP->D_NAME: %s\n", direntp->d_name);
        lstat(direntp->d_name, &info);
        if((strcmp(direntp->d_name, ".") != 0) && (strcmp(direntp->d_name, "..") != 0)){
          char newPath[4096];
          realpath(dirname, newPath);
          strcat(newPath, "/");
          strcat(newPath, direntp->d_name);
          char newIno[1024];
          sprintf(newIno, "%ld", info.st_ino);
          if((strstr(*knownInodes, newIno)) == NULL){
          //   // lstat(direntp->d_name, &info);
            // printf("RETURNED:\t%s\n", listDirs(newPath, knownInodes));
            listDirs(newPath, knownInodes, allPaths); //the addr of allPaths is changing within the recursive call
          }
          // char **temp = realloc(allPaths, (2 * sizeof(*allPaths)));
          // if(temp){
          //   allPaths = temp;
          // }
          // strcat(*allPaths, listDirs(newPath, knownInodes, allPaths));
          // strcat(*allPaths, "\n");  //so by the time it reaches here it's an invalid pointer
          //   // printf("KNOWNINODES: \n%s\n", *knownInodes);
          // printf("REALPATH:\t%s\n", realPath);
          // free(newPath);
        }
      }
      char newIno[2048];
      lstat(dirname, &info);
      sprintf(newIno, "%ld", info.st_ino);
      //increase size of knownInodes
      *knownInodes = realloc(*knownInodes, (4096 + strlen(*knownInodes)));
      strcat(*knownInodes, newIno);
      strcat(*knownInodes, "\n");
      //increase size of allPaths before strcat-ing
      *allPaths = realloc(*allPaths, (4096 + strlen(*allPaths)));
      strcat(*allPaths, dirname);
      strcat(*allPaths, "\n");
      return;
    }
    else{
      char newIno[2048];
      lstat(dirname, &info);
      sprintf(newIno, "%ld", info.st_ino);
      // // increase size of knownInodes
      *knownInodes = realloc(*knownInodes, (4096 + strlen(*knownInodes)));
      strcat(*knownInodes, newIno);
      strcat(*knownInodes, "\n");
      // printf("NEWINO:\t%s\n", newIno);
      *allPaths = realloc(*allPaths, (4096 + strlen(*allPaths)));
      strcat(*allPaths, dirname);
      strcat(*allPaths, "\n");
      return;
    }
}

long getSize(char dirname[]){
  DIR *dirp;
  long total = 0;
  struct stat info;
  if((dirp = opendir(dirname)) != NULL){
    struct dirent *direntp;
    while((direntp = readdir(dirp)) != NULL){
      lstat(direntp->d_name, &info);
      if((strcmp(direntp->d_name, ".") != 0) && (strcmp(direntp->d_name, "..") != 0)){
        char realPath[4096];
        realpath(dirname, realPath);
        strcat(realPath, "/");
        strcat(realPath, direntp->d_name);
        // total += (info.st_blksize * info.st_blocks);
        total += getSize(realPath);

      }
    }
    lstat(dirname, &info);
    // total += (info.st_size);
    total += (info.st_blksize * info.st_blocks);
    return total;
  }
  else{
    lstat(dirname, &info);
    // return (info.st_size);
    return (info.st_blksize * info.st_blocks);
  }
}
