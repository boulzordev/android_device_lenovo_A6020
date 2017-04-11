#!/sbin/sh
board_id="";
for e in $(cat /proc/cmdline);
do
    tmp=$(echo $e | grep "board_id" > /dev/null);
    if [ "0" == "$?" ]; then
        board_id=$(echo $e |cut -d":" -f0 |cut -d"=" -f2);
    fi
done

device="A6020a40"; # a40 SD415 is the default variant
case "$board_id" in
    "S82918B1"|"S82918H1")
        device="A6020a46" # a40 SD616 uses the same blobs from a46
    ;;
    "S82918E1")
        device="A6020a41"
    ;;
    "S82918F1")
        device="A6020l36"
    ;;
    "S82918G1")
        device="A6020l37"
    ;;
esac

# Move variant-specific blobs
mv /system/etc/firmware/variant/$device/venus* /system/etc/firmware/
rm -rf /system/etc/firmware/variant
