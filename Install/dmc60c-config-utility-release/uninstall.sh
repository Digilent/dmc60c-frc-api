#!/bin/bash

rm /usr/bin/digilent-dcu

rm -r /usr/bin/shared/dcu-www

/usr/sbin/update-rc.d -f dcu-startup remove

rm /etc/init.d/dcu-startup

rm /usr/lib/libdmc60c.so
