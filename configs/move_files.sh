#!/sbin/sh
source /tmp/install/bin/get_board_id.sh

mv /system/etc/firmware/variant/$variant/venus* /system/etc/firmware/
rm -rf /system/etc/firmware/variant
