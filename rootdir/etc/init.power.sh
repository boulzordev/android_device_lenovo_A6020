#!/system/bin/sh

################################################################################
# helper functions to allow Android init like script

function write() {
    echo -n $2 > $1
}

function copy() {
    cat $1 > $2
}

function get-set-forall() {
    for f in $1 ; do
        cat $f
        write $f $2
    done
}

################################################################################

# RPS mask
write /sys/class/net/rmnet0/queues/rx-0/rps_cpus 10

# switch to BFQ
setprop sys.io.scheduler bfq

################################################################################

# disable thermal core_control to update interactive gov settings
write /sys/module/msm_thermal/core_control/enabled 0

# some files in /sys/devices/system/cpu are created after the restorecon of
# /sys/. These files receive the default label "sysfs".
# Restorecon again to give new files the correct label.
restorecon -R /sys/devices/system/cpu

# configure governor settings for little cluster
write /sys/devices/system/cpu/cpu4/online 1
write /sys/devices/system/cpu/cpu4/cpufreq/scaling_governor "interactive"
restorecon -R /sys/devices/system/cpu # must restore after interactive
write /sys/devices/system/cpu/cpu4/cpufreq/interactive/above_hispeed_delay 19000
write /sys/devices/system/cpu/cpu4/cpufreq/interactive/go_hispeed_load 99
write /sys/devices/system/cpu/cpu4/cpufreq/interactive/timer_rate 20000
write /sys/devices/system/cpu/cpu4/cpufreq/interactive/hispeed_freq 998400
write /sys/devices/system/cpu/cpu4/cpufreq/interactive/io_is_busy 0
write /sys/devices/system/cpu/cpu4/cpufreq/interactive/target_loads "50 800000:80"
write /sys/devices/system/cpu/cpu4/cpufreq/interactive/min_sample_time 39000
write /sys/devices/system/cpu/cpu4/cpufreq/scaling_min_freq 499200

# configure governor settings for big cluster
write /sys/devices/system/cpu/cpu0/online 1
write /sys/devices/system/cpu/cpu0/cpufreq/scaling_governor "interactive"
restorecon -R /sys/devices/system/cpu # must restore after interactive
write /sys/devices/system/cpu/cpu0/cpufreq/interactive/above_hispeed_delay "19000 1113600:49000"
write /sys/devices/system/cpu/cpu0/cpufreq/interactive/go_hispeed_load 85
write /sys/devices/system/cpu/cpu0/cpufreq/interactive/timer_rate 20000
write /sys/devices/system/cpu/cpu0/cpufreq/interactive/hispeed_freq 1113600
write /sys/devices/system/cpu/cpu0/cpufreq/interactive/io_is_busy 0
write /sys/devices/system/cpu/cpu0/cpufreq/interactive/target_loads "85 1113600:90 1344000:95"
write /sys/devices/system/cpu/cpu0/cpufreq/interactive/min_sample_time 39000
write /sys/devices/system/cpu/cpu0/cpufreq/interactive/max_freq_hysteresis 59000
write /sys/devices/system/cpu/cpu0/cpufreq/scaling_min_freq 533333

# Enable thermal core_control now
write /sys/module/msm_thermal/core_control/enabled 1

# input boost configuration
write /sys/module/cpu_boost/parameters/input_boost_freq "0:800000 4:1113600"
write /sys/module/cpu_boost/parameters/input_boost_ms 150

# Setting b.L scheduler parameters
write /proc/sys/kernel/sched_migration_fixup 1
write /proc/sys/kernel/sched_upmigrate 75
write /proc/sys/kernel/sched_downmigrate 60

write /proc/sys/kernel/sched_small_task 20
write /proc/sys/kernel/sched_mostly_idle_load 30
write /proc/sys/kernel/sched_mostly_idle_nr_run 3

write /proc/sys/kernel/sched_prefer_idle 0

# android background processes are set to nice 10. Never schedule these on the big cluster.
write /proc/sys/kernel/sched_upmigrate_min_nice 9

# Enable bus-dcvs
for cpubw in /sys/class/devfreq/cpubw*/; do
    write $cpubw/governor "bw_hwmon"
    write $cpubw/bw_hwmon/io_percent 20
done

get-set-forall /sys/class/devfreq/*gpubw*/governor bw_hwmon
get-set-forall /sys/class/devfreq/*gpubw*/bw_hwmon/io_percent 40
get-set-forall /sys/class/devfreq/*mincpubw*/governor cpufreq

# Bring up all cores online
for cpu in /sys/devices/system/cpu/cpu*/online; do
	write $cpu 1
done
restorecon -R /sys/devices/system/cpu # must restore after online

# workaround for 'QCOM PowerHAL' rewriting minimum frequency on big cluster
## revoke permissions on 'scaling_min_freq'
chown root root /sys/devices/system/cpu/cpu0/cpufreq/scaling_min_freq
chmod 0444 /sys/devices/system/cpu/cpu0/cpufreq/scaling_min_freq

# Enable all LPMs by default
# This will enable C4, D4, D3, E4 and M3 LPMs
write /sys/module/lpm_levels/parameters/sleep_disabled N

# change GPU initial power level from 400Mhz(level 2) to 220MHz(level 3) for power savings
write /sys/class/kgsl/kgsl-3d0/default_pwrlevel 3
