#!/sbin/sh
source /tmp/install/bin/get_board_id.sh
mv /system/etc/$variant/venus* /system/etc/firmware/
mv /system/etc/$variant/thermal* /system/etc/
