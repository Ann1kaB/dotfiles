#!/bin/sh
if [[ $(optimus-manager --status | awk '/^Current GPU mode/{print $5}') == "nvidia" ]]; then
	xrandr --setprovideroutputsource modesetting NVIDIA-0
	xrandr --auto
	nvidia-settings --assign CurrentMetaMode="nvidia-auto-select +0+0 { ForceFullCompositionPipeline = On }"
	xrandr --dpi 96
fi
userresources=$HOME/.Xresources
usermodmap=$HOME/.Xmodmap
sysresources=/etc/X11/xinit/.Xresources
sysmodmap=/etc/X11/xinit/.Xmodmap
# Make sure this is before the 'exec' command or it won't be sourced.
[ -f /etc/xprofile ] && . /etc/xprofile
[ -f ~/.xprofile ] && . ~/.xprofile

wm[0]="dwm"
wm[1]="bspwm"
wm[2]="ratpoison"
wm[3]="openbox"
wm[4]="stumpwm"
wm[5]="spectrwm"
wm[6]="herbsluftwm"
wm[7]="dtkwm"
wm[8]="i3"
wm[9]="xfwm"
wm[10]="snapwm"
wm[11]="icewm"
wm[12]="uwm"
wm[13]="stumpwm"
wm[14]="plasma"
wm[15]=""

rand=$(( $RANDOM % 15 ))

exec ${wm[$rand]}

# merge in defaults and keymaps
if [ -f $sysresources ]; then







    xrdb -merge $sysresources

fi

if [ -f $sysmodmap ]; then
    xmodmap $sysmodmap
fi

if [ -f "$userresources" ]; then







    xrdb -merge "$userresources"

fi

if [ -f "$usermodmap" ]; then
    xmodmap "$usermodmap"
fi

# start some nice programs

if [ -d /etc/X11/xinit/xinitrc.d ] ; then
 for f in /etc/X11/xinit/xinitrc.d/?*.sh ; do
  [ -x "$f" ] && . "$f"
 done
 unset f
fi

exec dbus-launch --sh-syntax --exit-with-session dwm
exec --no-startup-id start-pulseaudio-x11

