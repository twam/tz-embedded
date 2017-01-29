#include <stdio.h>
#include <string.h>

#include "zones-db.h"

unsigned char* locale_localtime = 0;
unsigned int locale_localtime_len = 0;
unsigned int locale_tz_id = 0;

#include "zones-db-gen.c"

int tz_access(const char *path, int amode)
{
  int ret = -1;

  if (locale_localtime) {
    ret = 0; /* Return success */
  }

  return ret;
}

int tz_open(const char *path, int oflag, ... )
{
  int ret = -1;

  if (locale_localtime) {
    ret = 1; /* Return a non-zero non-neg value */
  }

  return ret;
}

ssize_t tz_read(int fd, void *buf, size_t nbyte)
{
  ssize_t ret = 0;

  switch (fd) {
  case 1:
    if (locale_localtime) {
      ret = locale_localtime_len;
      memcpy(buf,locale_localtime,locale_localtime_len);
    }
    break;
  default:
    break;
  }

  return ret;
}

int tz_close(int fd)
{
  return 0;
}

char *tz_getenv(const char *name)
{
  const char *tz = NULL;

  if (locale_localtime) {
    tz = locale_tz_names[locale_tz_id];
  }

  return (char *) tz;
}

int tz_set_time_zone_by_id(const int tz_id)
{
  // in case of invalid time zone id do nothing
  if ((tz_id < 0) || (tz_id >= (unsigned int)(sizeof(locale_tz_names)/sizeof(const char*)))) {
    return -1;
  }

  locale_tz_id = tz_id;
  (*tz_set_fp[tz_id])();

  return 0;
}

int tz_set_time_zone_by_name(const char* tz_name)
{
  return tz_set_time_zone_by_id(tz_get_time_zone_id(tz_name));
}

unsigned int tz_get_number_of_time_zones(void)
{
	return (unsigned int)(sizeof(locale_tz_names)/sizeof(const char*));
}

const char* tz_get_time_zone_name(const int tz_id)
{
  // in case of invalid time zone id return (null)
  if ((tz_id < 0) || (tz_id >= (unsigned int)(sizeof(locale_tz_names)/sizeof(const char*)))) {
    return "(null)";
  }

	return locale_tz_names[tz_id];
}

int tz_get_time_zone_id(const char* tz_name)
{
  for (unsigned int tz_id = 0; tz_id < (unsigned int)(sizeof(locale_tz_names)/sizeof(const char*)); ++tz_id) {
    if (strcmp(tz_name, locale_tz_names[tz_id]) == 0) {
      return tz_id;
    }
  }

  return -1;
}
