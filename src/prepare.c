#include <sys/stat.h>
#include <sys/types.h>

void prepare() {
  mkdir("/etc/...", 0400);
}
