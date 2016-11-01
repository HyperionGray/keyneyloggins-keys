#include <unistd.h>

int wait_for_passfile(void) {

  const char filename[] = "/dev/shm/program.shm";
  while(1) {
    sleep(1);
    if( access( fname, R_OK ) != -1 ) {
        break;
    }

  //TODO: Cleanup the .bashrc file

}
