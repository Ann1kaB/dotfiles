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
        status = open("/sys/class/power_supply/%s/status" % bat).read().rsplit('\n')[0]
        os.popen("notify-send \"LOW BATTERY, SHUTTING DOWN IN %d SECONDS.\"" % i)
        time.sleep(1)
        i = i - 1
        if status == "Charging":
            run_check()
    os.popen("poweroff")

def run_check():
    while True:
        f=open(percent_path, 'r')
        # battery percent here to shutdown
        if int(f.read().rstrip('\n')) < 15:
            shutdown()
        time.sleep(900)
run_check()
