#!/sbin/sh
variant=$(getprop ro.product.variant)

#This is a patch for current recoveries
#New recovery will be setting the variant value correctly
if [ "$variant" = "" ]; then 
    board_id="default";
    for e in $(cat /proc/cmdline);
    do
        tmp=$(echo $e | grep "board_id" > /dev/null);
        if [ "0" == "$?" ];
        then
            board_id=$(echo $e |cut -d":" -f0 |cut -d"=" -f2);
        fi
    done
    
    case "$board_id" in
        "S82918B1")
            variant="A6020a46"
            ;;
        "S82918D1")
            variant="A6020a40"
            ;;
        "S82918E1")
            variant="A6020a41"
            ;;
        "S82918F1")
            variant="A6020l36"
            ;;
        "S82918G1")
            variant="A6020l37"
            ;;
        "S82918H1")
            variant="A6020a46"
            ;;
    esac
    setprop ro.product.variant "$variant"
fi
echo $variant;
