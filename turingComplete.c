#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <ulimit.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

const char *get_filename_ext(const char *filename) {
    const char *dot = strrchr(filename, '.');
    if(!dot || dot == filename) return "";
    return dot + 1;
}

int main(int argc, char *argv[]){
  //creates a pipe, usualy to capture all output of child process!!! it also prevents keyboard interaction with child process!
  int fd [2];
  char *progName;

  //error checking if the pipe got establisehed correctly
  if (pipe(fd) == -1){
    perror("piping failed!");
    exit(1);
  }

  //check if amount of arguments is correct!
  if( argc > 3 ){
      printf("Too many arguments supplied.\n");
      exit(1);
  }
  if( argc == 2 ){
      printf("Odd number of arguments supplied, I only accept 2 arguments a C program name and bytes for memory allocation\n");
      exit(1);
  }

  //stores the comand of the file to be run
  progName = argv[2];

  printf("--beginning of program\n");

  //Note: a forked process runs in a completely seprate memory space, but as an exact copy of the parent,
  //so if the program crashes it wont affect other processes!
  pid_t pid = fork();
  char readbuffer[atoi(argv[1])/1000];

  if (pid == 0){
      // child processes`
      //setting limits for Virtual memory space
      struct rlimit limit, Lim;
      limit.rlim_cur = atoi(argv[1]);
      limit.rlim_max = atoi(argv[1]); 
      setrlimit(RLIMIT_AS, &limit);
      //setting limits for max size of file, that way child process cannot write or alter a file
      limit.rlim_cur = 0;
      limit.rlim_max = 0;
      setrlimit(RLIMIT_FSIZE, &limit);
      getrlimit(RLIMIT_FSIZE, &Lim);
      limit.rlim_cur = 4;
      limit.rlim_max = 4;
      setrlimit(RLIMIT_NOFILE, &limit);

      //closes the input pipe so that child process can send data to parent process!
      close(fd[0]);
      dup2(fd[1], 1);  // send stdout to the pipe
      execve(progName, NULL, NULL);// can run c and c++ compiled code!
  }
  else if (pid > 0){
    //parent process
    //closes output pipe so that parent could read for the child process!
    close(fd[1]);
  }
  else{
      // fork failed
      printf("fork() failed!\n");
      return 1;
  }
  printf("--end of program--\n");

  //I spawned another process to output result after sandbox terminates
  pid = fork();
  if (pid == 0){
    while (read(fd[0], readbuffer, sizeof(readbuffer)) != 0){
      printf("%s", readbuffer);
    }
  }
  else if (pid > 0){
    ;
  }
  else{
      // fork failed
      printf("fork() failed!\n");
      return 1;
  }  
  return 0;
}