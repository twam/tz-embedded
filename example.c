#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "libtz.h"

void print_tm(struct tm* tm, const char *pre)
{
	printf("%30s: %02i.%02i.%04i %02i:%02i:%02i %4s %+3li:%02li %1i\n", pre, tm->tm_mday, tm->tm_mon, 1900+tm->tm_year, tm->tm_hour, tm->tm_min, tm->tm_sec, tm->tm_zone, tm->tm_gmtoff/3600, ((tm->tm_gmtoff/60)%60), tm->tm_isdst);

}

int main(int argc, char **argv) {
	time_t a = 0;

	struct tm* tm = tz_gmtime(&a);

	printf("List of compiled-in time zones:\n");
	for (unsigned int i = 0; i < tz_get_number_of_time_zones(); ++i) {
		printf("  %s\n", tz_get_time_zone_name(i));
	}

	printf("\n");
	printf("Timezone                        Date       Time     TZ   Offset DST\n");
	printf("-------------------------------------------------------------------\n");

	print_tm(tm, "gmtime");

	const char* timezones[] = {
		"UTC",
		"Europe/Berlin",
		"America/New_York",
		"America/Argentina/Buenos_Aires",
		"Asia/Kolkata",
		"Australia/Sydney",
		"Australia/Tasmania",
		"Etc/GMT-14",
		"Etc/GMT+12"
		};

	for (int i = 0; i < sizeof(timezones)/sizeof(const char *); ++i) {
		tz_set_time_zone_by_name(timezones[i]);
		tm = tz_localtime(&a);
		print_tm(tm, timezones[i]);
	}

	return 0;
}