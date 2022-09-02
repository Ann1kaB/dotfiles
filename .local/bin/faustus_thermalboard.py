#!/usr/bin/python3
import os
import time
import sys

color = "/sys/devices/platform/asus-nb-wmi/leds/asus::multicolour::kbd_backlight/multi_intensity"

MAX_TEMP = 96
MIN_TEMP = 20
MID_TEMP = 56

BR_MULT = 10

debug = False

def get_temp():
    CPU_TEMP = open("/sys/class/thermal/thermal_zone0/hwmon1/temp1_input", 'r').read().splitlines()[0]
    cputemp = int(CPU_TEMP[:2])
    return cputemp


def over_max_temp():
# reset KB B and G color
    with open(color, 'w') as color_w:
        color_w.write("0 0 0")
    time.sleep(1)
# ON
    with open(color, 'w') as red_w:
        red_w.write("255 0 0")
    time.sleep(1)


def red(cputemp):
    redbase = (cputemp - MID_TEMP) * BR_MULT
    if redbase <= 255 and redbase >= 0:
        rval = redbase
    elif redbase > 255:
        rval = 255
    else:
        rval = 0
    return rval


def inc_green(cputemp):
    incgreenbase = (cputemp - MAX_TEMP) * -BR_MULT
    if incgreenbase <= 255 and incgreenbase >= 0:
        incgval = incgreenbase
    elif incgreenbase > 255:
        incgval = 255
    else:
        incgval = 0
    return incgval


def dec_green(cputemp):
    decgreenbase = (cputemp - MIN_TEMP) * BR_MULT
    if decgreenbase <= 255 and decgreenbase >= 0:
        decgval = decgreenbase
    else:
        decgval = 255
    return decgval


def blue(cputemp):
    bluebase = (cputemp - MID_TEMP) * -BR_MULT
    if bluebase <= 255 and bluebase >= 0:
        bval = bluebase
    elif bluebase > 255:
        bval = 255
    else:
        bval = 0
    return bval

def main():

    while True:
        cputemp = get_temp()
        try:
            while cputemp > MAX_TEMP:
                over_max_temp()
                cputemp = get_temp()

            if cputemp >= MID_TEMP:
                rval = red(cputemp)
                if debug:
                    print("rval: %s" % rval, cputemp)

            elif cputemp <= MID_TEMP:
                if debug:
                    print("rval: 0")
                rval = 0

            if cputemp >= MID_TEMP and cputemp <= MAX_TEMP:
                gval = inc_green(cputemp)
                if debug:
                    print("gval: %s" % gval, cputemp)

            elif cputemp <= MIN_TEMP:
                if debug:
                    print("gval: 0")
                gval = 0

            if cputemp >= MIN_TEMP and cputemp <= MID_TEMP:
                gval = dec_green(cputemp)
                if debug:
                    print("gval %s" % gval, cputemp)

            if cputemp <= MID_TEMP:
                bval = blue(cputemp)
                if debug:
                    print("bval: %s" % bval, cputemp)


            if cputemp >= MID_TEMP:
                if debug:
                    print("bval: 0")
                bval = 0
            # keep at least one keyboard bl color fully lit
            max_num=0
            color_list = [bval, gval, rval]
            for _max in color_list:
                if _max > max_num:
                    max_num = _max
                    c_hint = color_list.index(_max)
            if c_hint == 0:
                bval = 255
                if debug:
                    print("adj bval: %s" % bval, cputemp)
            elif c_hint == 1:
                gval = 255
                if debug:
                    print("adj gval: %s" % gval, cputemp)
            elif c_hint == 2:
                rval = 255
                if debug:
                    print("adj rval: %s" % rval, cputemp)
            with open(color, 'w') as set_kb:
                set_kb.write("%s %s %s" % (rval, gval, bval))
                time.sleep(1)

        except KeyboardInterrupt:
            print("Exiting.")
            sys.exit(0)
main()

