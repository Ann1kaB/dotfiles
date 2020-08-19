#!/usr/bin/env python3
import os
import sys
import time

path = "/sys/class/power_supply/"
for i in os.listdir(path):
    if i.startswith("BAT"):
        bat = i
batpath = path + bat
percent_path = batpath + "/capacity"
status = open("/sys/class/power_supply/%s/status" % bat).read().rsplit('\n')[0]

def shutdown():
    i = 61
    while i > 0:
        i = i - 1
        os.popen("notify-send \"LOW BATTERY, SHUTTING DOWN IN %d SECONDS.\"" % i)
        time.sleep(1)
    os.popen("poweroff")

while True:
    f=open(percent_path, 'r')
    # battery percent here to shutdown
    if int(f.read().rstrip('\n')) < 35 and status == "Discharging":
        shutdown()
    time.sleep(900)
