#!/bin/bash

EXE_DIR=/usr/bin
WWW_DIR=/usr/bin/shared/
BASEDIR=$(dirname "$0")

# ensure executables are executable
chmod +x $BASEDIR/digilent-dcu
chmod +x $BASEDIR/dcu-startup

# move the dcu.exe to /usr/bin
cp $BASEDIR/digilent-dcu $EXE_DIR

# make shared folder in /usr/bin
mkdir $WWW_DIR

# move the dcu-www to /usr/bin/shared
cp -r $BASEDIR/dcu-www/ $WWW_DIR

# move dcu-startup script to /etc/init.d
cp $BASEDIR/dcu-startup /etc/init.d

# move the dmc60c library to /usr/lib
cp $BASEDIR/libdmc60c.so /usr/lib

# move the dmc60c library to /usr/local/frc/lib
# cp $BASEDIR/libdmc60c.so /usr/local/frc/lib

# install the startup script with default settings @ /usr/sbin/update-rc.d -f $NAME defaults
/usr/sbin/update-rc.d -f dcu-startup start 99 runlvl 5 .

# start things up for the user
/etc/init.d/dcu-startup start > /dev/null &