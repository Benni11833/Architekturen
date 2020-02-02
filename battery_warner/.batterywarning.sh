#!/bin/bash

    while true
    do
        export DISPLAY=:0.0
        battery_level=`acpi -b | grep -P -o '[0-9]+(?=%)'`
        if on_ac_power; then
            if [ $battery_level -ge 95 ]; then
                notify-send "Battery charging above 95%. Unplug your AC adapter!" "Charging: ${battery_level}% "
             fi
        else
             if [ $battery_level -le 20 ]; then
                notify-send "Battery is lower 20%. Connect your AC adapter." "Charging: ${battery_level}%"
                if ! on_ac_power; then
                    ./battery_window_popup.py $battery_level   ## Display LOWBATTERY notification window
                fi
             fi
        fi

        sleep 300 # 300 seconds or 5 minutes
    done
