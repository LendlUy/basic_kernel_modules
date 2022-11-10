#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

const char *new_directory(char *string, char *directory) {
  strcpy(string, "");
  strcpy(string, directory);
  strcat(string, "/");
  return string;
}

const char *read_file(char *directory) {

  FILE *fp;
  char *line = NULL;
  size_t len = 0;
  ssize_t read;

  fp = fopen(directory, "r");

  while ((read = getline(&line, &len, fp)) != -1) {
    printf("%s", line);
  }

  fclose(fp);
  if (line) {
    free(line);
  }
  
  return line;
}

int main() {

  // Initialize of temporary variables
  struct dirent *pDirent_top;
  DIR *pDir_top;
  struct dirent *pDirent_bot;
  DIR *pDir_bot;

  FILE* ptr;
  char ch;
  char nvme_id[10];

  int result;
  int result_1;
  int result_2;

  char directory[] = "/sys/bus/pci/devices";
  char tmp_dir[100];
   
  pDir_top = opendir(directory);

  if (pDir_top == NULL) {
    printf("Cannot open directory '%s'\n", directory);
    return 1;
  }

  // Searches for all PCI devices connected to the machine
  while ((pDirent_top = readdir(pDir_top)) != NULL) {

    result_1 = strcmp(".", pDirent_top->d_name);
    result_2 = strcmp("..", pDirent_top->d_name);

    if ((result_1 == 0) || (result_2 == 0)) {
      continue;
    }

    strcpy(tmp_dir, new_directory(tmp_dir, directory));
    strcat(tmp_dir, pDirent_top->d_name);
    //print("New directory: %s\n", tmp_dir);

    pDir_bot = opendir(tmp_dir);

    if (pDir_bot == NULL) {
      printf("Cannot open subdirectory '%s'\n", tmp_dir);
      continue;
    }

    /*
     * Checks if PCI device found is an NVMe device
     * Prints the device ID and vendor ID
     */

    while ((pDirent_bot = readdir(pDir_bot)) != NULL) {

      result = strcmp("nvme", pDirent_bot->d_name);

      if (result == 0){
        printf("NVMe device found!\n");

        strcpy(tmp_dir, new_directory(tmp_dir, directory));
        strcat(tmp_dir, pDirent_top->d_name);
        strcat(tmp_dir, "/vendor");
        printf("Reading: %s\n", tmp_dir);

        read_file(tmp_dir);

        strcpy(tmp_dir, new_directory(tmp_dir, directory));
        strcat(tmp_dir, pDirent_top->d_name);
        strcat(tmp_dir, "/device");
        printf("Reading: %s\n", tmp_dir);

        read_file(tmp_dir);
      }
    }
  }

  closedir(pDir_top);
  return 0;
}

main();
