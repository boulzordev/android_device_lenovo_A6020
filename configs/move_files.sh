#!/sbin/sh
device=$(getprop ro.product.device)

### Patch for old recoveries - start
if [ "$device" = "default" ] || [ "$device" = "A6020" ]; then 
    board_id="";
    for e in $(cat /proc/cmdline);
    do
        tmp=$(echo $e | grep "board_id" > /dev/null);
        if [ "0" == "$?" ];
        then
            board_id=$(echo $e |cut -d":" -f0 |cut -d"=" -f2);
        fi
    done
    
    device="A6020a40";
    case "$board_id" in
        "S82918B1"|"S82918H1")
            device="A6020a46"
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
fi
### Patch for old recoveries - end

# Move variant-specific blobs
mv /system/etc/firmware/variant/$device/venus* /system/etc/firmware/
rm -rf /system/etc/firmware/variant
