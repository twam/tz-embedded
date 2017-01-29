#!/bin/bash

c_zone_name() {
    echo "$1" | sed 's/\//_/g' | sed 's/-/_minus_/g' | sed 's/+/_plus_/g'
}

zone_list=$(find zoneinfo -type f | sed 's/^zoneinfo\///')

rm -f zones-db-gen.c

find zoneinfo -type f | sed 's/^zoneinfo\///' | while read tz; do
    size=$(wc -c < zoneinfo/$tz | sed 's/ //g' )
    tzc=$(c_zone_name ${tz})

    echo "unsigned char __${tzc}[] = {" >> zones-db-gen.c
    xxd -i < zoneinfo/$tz >> zones-db-gen.c
    echo "};" >> zones-db-gen.c
    echo "unsigned int __${tzc}_len = $size;" >> zones-db-gen.c;
    echo "" >> zones-db-gen.c
done

find zoneinfo -type f | sed 's/^zoneinfo\///' | while read tz; do
    tzc=$(c_zone_name ${tz})
    echo "void tz_set_${tzc}(void);" >> zones-db-gen.c
done

echo "" >> zones-db-gen.c

echo "void (*tz_set_fp[])(void) = {" >> zones-db-gen.c
find zoneinfo -type f | sed 's/^zoneinfo\///' | while read tz; do
    tzc=$(c_zone_name ${tz})
    echo "  tz_set_${tzc}," >> zones-db-gen.c
done
echo "};" >> zones-db-gen.c

echo "" >> zones-db-gen.c

echo "const char *locale_tz_names[] = {" >> zones-db-gen.c
find zoneinfo -type f | sed 's/^zoneinfo\///' | while read tz; do
    echo "  \"${tz}\"," >> zones-db-gen.c
done
echo "};" >> zones-db-gen.c

echo "" >> zones-db-gen.c

find zoneinfo -type f | sed 's/^zoneinfo\///' | while read tz; do
    tzc=$(c_zone_name ${tz})
    echo "void tz_set_${tzc}(void)" >> zones-db-gen.c
    echo "{" >> zones-db-gen.c
    echo "  locale_localtime = __${tzc};" >> zones-db-gen.c
    echo "  locale_localtime_len = __${tzc}_len;" >> zones-db-gen.c
    echo "}" >> zones-db-gen.c
    echo "" >> zones-db-gen.c
done;
