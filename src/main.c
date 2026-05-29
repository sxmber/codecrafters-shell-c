#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char *argv[]) {
  // Flush after every printf
  setbuf(stdout, NULL);

  // TODO: Uncomment the code below to pass the first stage
   while(1){
    
    //char *paths = getenv("PATH");
    //printf("%s", paths);
    printf("$ ");
    char *builtins[] = {
      "echo",
      "exit",
      "type",
      NULL
    };
    //take user input as a variable then print $variable: command not found
    char command[1024];
    fgets(command, sizeof(command), stdin);
    command[strcspn(command, "\n")] = '\0';

    if(strcmp(command,"exit") == 0){
      break;
    }
    //Strings are pointers in C. A pointer is a memory address. %s will take the memory address and print the value.
    //* takes a memory address and grabs the value stored there.
    //& takes a variable/value and reveals it memory address.
    if (strncmp(command, "echo", 4) == 0){ //only looking at the first 3 characters of $command and if it is == to "echo" then run..
      printf("%s\n", command + 5);
    }
    if(strncmp(command, "type", 4) == 0){ 
      char *target = command + 5; 
      int found = 0;

      for (int i =0; builtins[i] != NULL; i++){
        if(strcmp(target, builtins[i]) == 0) {
          printf("%s is a shell builtin\n", target);
          found = 1;
          break;
        }
        
      }
      //if builtin not found, check PATH
      //Get path, split it by : and save each one to an array?
      //loop through each iteration and check the direcory for a match of what user inputed

      if(!found){
        char *path = getenv("PATH");
        char *splitPath = strtok(path, ":");
        printf("path: %s\nsplitpath: %s",path,splitPath);
      }
     
    //else target not found 
      
    } 
    else {
    printf("%s: command not found\n" ,command);
    } 
  }
    return 0;
}
