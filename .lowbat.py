#!/usr/bin/env python3
import os
import time

path = "/sys/class/power_supply/"
for i in os.listdir(path):
    if i.startswith("BAT"):
        bat = i
batpath = path + bat
percent_path = batpath + "/capacity"

def shutdown():
    i = 60
    while i > 0:
        with open("/sys/class/power_supply/%s/status" % bat, 'r') as _s:
            status = _s.read().split('\n')
        if status == "Discharging":
            os.popen("notify-send \"LOW BATTERY, SHUTTING DOWN IN %d SECONDS.\"" % i)
            time.sleep(1)
            i -= 1
        elif status == "Charging":
            run_check()
    os.popen("sudo poweroff")

def run_check():
    while True:
        with open(percent_path, 'r') as f:
        # battery percent here to shutdown
            if int(f.read().rstrip('\n')) < 15:
                shutdown()
        time.sleep(300)
run_check()
