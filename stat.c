#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include <time.h>

int main() {
  struct stat file_data;
  int error = stat("stat.c", &file_data);
  if (error == -1) {
    printf("%s\n", strerror(errno));
    return 0;
  }

  // print file size, mode (permissions), time of last access
  printf("\nPRINTING INFORMATION ABOUT STAT.C\n\n");
  printf("File Size: %d\n", file_data.st_size);
  printf("Mode: %d\n", file_data.st_mode);
  time_t access_time = file_data.st_atime;
  printf("Time of Last Access: %s\n", ctime(&access_time));

  // print file size in regular language
  char buffer[100];
  float size2;
  int size = file_data.st_size;
  char *unit = "B";
  if (size > 1000) {
    float size2 = size / 1000.0;
    unit = "KB";
    sprintf(buffer, "%.2f%s", size2, unit);
  } else {
    sprintf(buffer, "%d%s", size, unit);
  }
  printf("File Size: %s\n", buffer);

  char permission[100];
  sprintf(permission, "%o", file_data.st_mode & 511);

  // there's definitely a better way to do this but I'm not smart enough for that...
  printf("File permissions: -");
  int i = 0;
  for (; i < 3; i++) {
    if (permission[i] == '0') {
      printf("---");
    } else if (permission[i] == '1') {
      printf("--x");
    } else if (permission[i] == '2') {
      printf("-w-");
    } else if (permission[i] == '3') {
      printf("-wx");
    } else if (permission[i] == '4') {
      printf("r--");
    } else if (permission[i] == '5') {
      printf("r-x");
    } else if (permission[i] == '6') {
      printf("rw-");
    } else {
      printf("rwx");
    }
  }
  printf("\n");

  return 0;
}
