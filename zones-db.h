#ifndef FILE_REDIRECT_H
#define FILE_REDIRECT_H

#include <unistd.h>

#undef  access
#define access tz_access
#undef  open
#define open tz_open
#undef  read
#define read tz_read
#undef  close
#define close tz_close
#undef  getenv
#define getenv tz_getenv
#undef  FILENAME_MAX
#define FILENAME_MAX 256       /* This lib will never open a file so this is safe */
#undef  TZNAME_MAX
#define TZNAME_MAX 255       /* This lib will never open a file so this is safe */

int tz_access(const char *path, int amode);
int tz_open(const char *path, int oflag, ... );
ssize_t tz_read(int fildes, void *buf, size_t nbyte);
int tz_close(int fildes);
char *tz_getenv(const char *name);

int tz_set_time_zone_by_id(const int tz_id);
int tz_set_time_zone_by_name(const char* tz_name);
unsigned int tz_get_number_of_time_zones(void);
const char* tz_get_time_zone_name(const int tz_id);
int tz_get_time_zone_id(const char* tz_name);

#endif
