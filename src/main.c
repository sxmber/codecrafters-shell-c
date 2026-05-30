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
      free(copyPath);
      return 1;
    }
  }
  free(copyPath);
  return 0;
}

char *readInput() {
  int bufsize = 1024;
  printf("$ ");
  char *buffer = malloc(
      bufsize * sizeof(char)); // Need to malloc to buffer in order to return it

  if (!buffer) { // exit if alloc fails
    exit(EXIT_FAILURE);
  }

  if (fgets(buffer, bufsize, stdin) == NULL) { // if EOF is recieved, exit.
    exit(EXIT_FAILURE);
  }

  buffer[strcspn(buffer, "\n")] = '\0';

  return buffer;
}

int parseInput(char *input, char *args[]) {
  int position = 0;
  for (char *tok = strtok(input, " "); tok != NULL; tok = strtok(NULL, " ")) {
    args[position] = tok;
    position++;
  }
  args[position] = NULL;
  return position;
}

void runBuiltIn(int argCount, char *args[], char *builtins[]) {
  if (isBuiltIn(args[0], builtins)) {
    if (strcmp(args[0], "echo") == 0) {
      for (int i = 1; i < argCount; i++) {
        printf("%s ", args[i]);
      }
      printf("\n");
    } else if (strcmp(args[0], "exit") == 0) {
      exit(EXIT_SUCCESS);
    } else if (strcmp(args[0], "type") == 0) {
      if (argCount < 2) {
        return;
      }
      if (isBuiltIn(args[1], builtins)) {
        printf("%s is a shell builtin\n", args[1]);
      } else {
        char fPath[1024];
        if (findPath(args[1], fPath, sizeof(fPath))) {
          printf("%s is %s\n", args[1], fPath);

        } else {
          printf("%s: not found\n", args[1]);
        }
      }
    }
  }
}

// get user input()
// parse user input. tokenize command + arguments
// handle builtins
// path resolver
// execute external programs

int main(int argc, char *argv[]) {
  // Flush after every printf
  setbuf(stdout, NULL);

  while (1) {
    char *builtins[] = {"echo", "exit", "type", NULL};
    char *args[1024];
    char *input = readInput();
    int argc = parseInput(input, args);
    if (argc == 0) {
      free(input);
      continue;
    }
    runBuiltIn(argc, args, builtins);

    //      printf("$ ");
    //      char *builtins[] = {"echo", "exit", "type", NULL};
    //      // take user input as a variable then print $variable: command not
    //      found char command[1024]; fgets(command, sizeof(command), stdin);
    //      command[strcspn(command, "\n")] = '\0';

    //   if (strcmp(command, "exit") == 0) {
    //     break;
    //   } else if (strncmp(command, "echo ", 5) == 0) {
    //     printf("%s\n", command + 5);

    //   } else if (strncmp(command, "type ", 5) == 0) {
    //     char *target = command + 5;
    //     int foundArg = 0;
    //     int foundPath = 0;
    //     if (isBuiltIn(target, builtins)) {
    //       printf("%s is a shell builtin\n", target);
    //     } else {
    //       char fPath[1024];
    //       if (findPath(target, fPath, sizeof(fPath))) {
    //         printf("%s is %s\n", target, fPath);

    //       } else {
    //         printf("%s: not found\n", target);
    //       }
    //     }
    //   } else {
    //     printf("%s: command not found\n", command);
    //   }
  }

  return 0;
}
