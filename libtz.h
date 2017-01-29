#ifndef LIBTZ_H
#define LIBTZ_H

#ifdef __cplusplus
extern "C" {
#endif

double tz_difftime(time_t time1, time_t time0);

char * tz_asctime_r(register const struct tm *timeptr, char *buf);
char * tz_asctime(register const struct tm *timeptr);

struct tm * tz_gmtime_r(const time_t *timep, struct tm *tmp);
struct tm * tz_gmtime(const time_t *timep);

#ifdef STD_INSPIRED
struct tm * tz_offtime(const time_t *timep, long offset);
#endif

struct tm * tz_localtime(const time_t *timep);
struct tm * tz_localtime_r(const time_t *timep, struct tm *tmp);

char * tz_ctime(const time_t *timep);
char * tz_ctime_r(const time_t *timep, char *buf);

#if NETBSD_INSPIRED
time_t tz_mktime_z(struct state *sp, struct tm *tmp);
#endif

time_t tz_mktime(struct tm *tmp);

#ifdef STD_INSPIRED
time_t tz_timelocal(struct tm *tmp);
time_t tz_timegm(struct tm *tmp);
time_t tz_timeoff(struct tm *tmp, long offset);
#endif

int tz_set_time_zone_by_id(const int tz_id);
int tz_set_time_zone_by_name(const char* tz_name);
unsigned int tz_get_number_of_time_zones(void);
const char* tz_get_time_zone_name(const int tz_id);
int tz_get_time_zone_id(const char* tz_name);

#ifdef __cplusplus
}
#endif

#endif
