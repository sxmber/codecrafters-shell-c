#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char *argv[]) {
  // Flush after every printf
  setbuf(stdout, NULL);

  // TODO: Uncomment the code below to pass the first stage
   while(1){
    
    
    printf("$ ");
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
    else if (strncmp(command, "echo", 3) == 0){ //only looking at the first 3 characters of $command and if it is == to "echo" then run..
      printf("%s\n", command + 5);
    }
    else if(strncmp(command, "type", 3) == 0){
      if(strncmp(command + 5,"echo", 5) == 0){
        printf("echo is a shell builtin\n");
      }
      else if(strncmp(command + 5, "exit", 5) == 0){
        printf("exit is a shell builtin\n");
      }
      else if(strncmp(command + 5, "type", 5) == 0){
        printf("type is a shell builtin\n");
      }
      else {
        printf("%s: not found\n", command + 5);
      }
    }
    else {
    printf("%s: command not found\n" ,command);
    } 
  }
    return 0;
}
