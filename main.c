#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>

double write_one_byte(char * filename) ;

int main(int argc, char ** argv) {
  time_t t;
  struct tm tm ;
  while(true) {
    t = time(NULL);
    tm = *localtime(&t);
    printf("%d-%02d-%02d %02d:%02d:%02d : ", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
    printf("time to write one byte: %f seconds\n", write_one_byte(argv[1])); 
    fflush(stdout);
    sleep(1);
  }
  return(0);
}

double write_one_byte(char * filename) {
  FILE * fd;
  char data = 'X';
  struct timeval tv_before, tv_after;
  double seconds;
  gettimeofday(&tv_before, NULL);
  fd = fopen(filename, "w");
  if (fd) {
    fwrite(&data, 1, 1, fd);
    fsync(fileno(fd));
    fclose(fd);
    gettimeofday(&tv_after, NULL);
    seconds = (double) (tv_after.tv_usec - tv_before.tv_usec) / 1000000 +
              (double) (tv_after.tv_sec - tv_before.tv_sec);
    return(seconds);
  }
  return(-1);
}

