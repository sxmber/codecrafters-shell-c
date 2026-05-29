#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
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
    else if (strncmp(command, "echo ", 5) == 0){ //only looking at the first 3 characters of $command and if it is == to "echo" then run..
      printf("%s\n", command + 5);
    }
    else if(strncmp(command, "type ", 5) == 0){ 
      char *target = command + 5; 
      int foundArg = 0;
      int foundPath = 0;
      for (int i =0; builtins[i] != NULL; i++){
        if(strcmp(target, builtins[i]) == 0) {
          printf("%s is a shell builtin\n", target);
          foundArg = 1;
          break;
        }
        
      } 

      if(!foundArg){
        char *path = getenv("PATH");
        char *copyPath = strdup(path);
        char *splitPath = strtok(copyPath, ":");
        //printf("path: %s\n",path);
        
        while(splitPath){
          char catPath[1024] = "";//fixed size buffer so i dont need to free memory
          snprintf(catPath, sizeof(catPath), "%s/%s", splitPath, target);//concatanate  the user input target to the path. / is added in the middle. 
          if(access(catPath, F_OK) == 0 && access(catPath, X_OK) == 0){
            printf("%s is %s\n", target, catPath);
            foundPath = 1;
            break;
          }
          splitPath = strtok(NULL, ":");

        }
        if(foundPath == 0){
        printf("%s: is not found\n", target);
      }
        free(copyPath);
      }
      
                
    } 
    else {
    printf("%s: command not found\n" ,command);
    } 
  }
    return 0;
}
