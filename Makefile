.SUFFIXES:

TZ_DIR = tz

LIBSRCS = \
  $(TZ_DIR)/localtime.c \
  $(TZ_DIR)/asctime.c \
  $(TZ_DIR)/difftime.c \
  zones-db.c

LIBOBJS = $(LIBSRCS:.c=.o)
AWK = awk
CFLAGS =

TDATA = africa antarctica asia australasia \
	europe northamerica southamerica \
	pacificnew etcetera backward \
	systemv factory

$(LIBOBJS): CFLAGS += \
	-DNETBSD_INSPIRED=0 \
	-DTZDIR=\"\" \
	-Dtime_tz=time_t \
	-include zones-db.h

all: libtz.a example

clean:
	rm -f $(LIBOBJS)
	rm -f test.o
	rm -f test
	rm -f libtz.a
	rm -rf tdata
	rm -rf zoneinfo
	cd $(TZ_DIR) && $(MAKE) clean

.PHONY: clean

$(TZ_DIR)/zic: $(TZ_DIR)/zic.c
	cd $(TZ_DIR) && $(MAKE) zic

libtz.a: $(LIBOBJS)
	rm -f $@
	$(AR) -rc $@ $(LIBOBJS)

example: example.o libtz.a
	gcc -o $@ $^

zones-db.c: zones-db-gen.c

%.o: %.c
	$(CC) -o $@ -c $^ $(CFLAGS)

zones-db-gen.c: zoneinfo gen-zones-db.sh
	./gen-zones-db.sh

tdata/%: $(TZ_DIR)/% | tdata
	cp $^ $@

tdata:
	mkdir tdata

zoneinfo: $(foreach tdatum,$(TDATA),tdata/$(tdatum)) $(TZ_DIR)/zic
	rm -rf zoneinfo
	mkdir zoneinfo
	$(TZ_DIR)/zic -d zoneinfo $(foreach tdatum,$(TDATA),tdata/$(tdatum))
