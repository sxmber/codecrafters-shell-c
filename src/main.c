#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int isBuiltIn(char *target, char *builtins[]) {
  for (int i = 0; builtins[i]; i++) {
    if (strcmp(target, builtins[i]) == 0) {
      return 1;
    }
  }
  return 0;
}

int findPath(char *argv, char *result, size_t sizeOfResult) {
  char *path = getenv("PATH");
  char *copyPath = strdup(path);
  for (char *dir = strtok(copyPath, ":"); dir != NULL;
       dir = strtok(NULL, ":")) {
    snprintf(result, sizeOfResult, "%s/%s", dir, argv);
    if (access(result, X_OK) == 0) {
      return 1;
    }
  }
  return 0;
}

int main(int argc, char *argv[]) {
  // Flush after every printf
  setbuf(stdout, NULL);

  while (1) {
    printf("$ ");
    char *builtins[] = {"echo", "exit", "type", NULL};
    // take user input as a variable then print $variable: command not found
    char command[1024];
    fgets(command, sizeof(command), stdin);
    command[strcspn(command, "\n")] = '\0';

    if (strcmp(command, "exit") == 0) {
      break;
    } else if (strncmp(command, "echo ", 5) == 0) {
      printf("%s\n", command + 5);

    } else if (strncmp(command, "type ", 5) == 0) {
      char *target = command + 5;
      int foundArg = 0;
      int foundPath = 0;
      if (isBuiltIn(target, builtins)) {
        printf("%s is a shell builtin\n", target);
      } else {
        char fPath[1024];
        if (findPath(target, fPath, sizeof(fPath))) {
          printf("%s is %s\n", target, fPath);

        } else {
          printf("%s: not found\n", target);
        }
      }
    } else {
      printf("%s: command not found\n", command);
    }
  }

  return 0;
}
