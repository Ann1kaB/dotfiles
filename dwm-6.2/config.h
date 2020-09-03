/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 0;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "Fira Code Mono:size=10", "Noto Sans Symbols2:size=10" };
static const char dmenufont[]       = "monospace:size=12";
#include "/home/hyperkvm/.cache/wal/colors-wal-dwm.h"
#include <X11/XF86keysym.h>

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }
//commands
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, NULL };
static const char *termcmd[]  = { "st", NULL };
//volume control
static const char *mutecmd[] = { "./.volcontrol/mute", NULL };
static const char *volupcmd[] = { "./.volcontrol/volup", NULL };
static const char *voldowncmd[] = { "./.volcontrol/voldown", NULL };
//brightness control 
static const char *brupcmd[] = { "./.backlightcontrol/backlightup", NULL };
static const char *brdowncmd[] = { "./.backlightcontrol/backlightdown", NULL };
//media control
static const char *tracknext[] = { "playerctl", "next", NULL };
static const char *trackprev[] = { "playerctl", "previous", NULL };
static const char *trackplaypause[] = { "playerctl", "play-pause", NULL };
//screenshot control
static const char *fullscreenshot[] = { "scrot", "-e", "\''mv $f Pictures/'\'", "-d", "2", NULL };
static const char *windowscreenshot[] = { "scrot", "-e", "\''mv $f Pictures/'\'", "-u", "-d", "2", NULL };
static const char *selscreenshot[] = { "./.importscript", NULL };
//system info
static const char *fanmode[] = { "./.fanmode", NULL };
static const char *sysinfo[] = { "sh", ".sysxroot", NULL };
static const char *xrandrkey[] = { "./.xrandrconf", NULL };
//TDP switch
static const char *tdpswitch[] = { "sudo", "./.set-tdp/set-tdp", NULL };
//Display Reset (becaase ASUS is a pile of dogshit)
static const char *dispswitch[] = { "./.bull-shit", NULL };
//screen lock
static const char *setslock[] = { "slock", "NULL" };
static Key keys[] = {
	/* modifier                     key        			function        argument */
	{ MODKEY,                       XK_o,      			spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_b,      			togglebar,      {0} },
	{ MODKEY,                       XK_j,      			focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      			focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      			incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      			incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      			setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      			setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, 			zoom,           {0} },
	{ MODKEY,                       XK_Tab,    			view,           {0} },
	{ MODKEY,                       XK_t,      			setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      			setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      			setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  			setlayout,      {0} },
	{ MODKEY,                       XK_0,      			view,           {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  			focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, 			focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  			tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, 			tagmon,         {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_c,      			killclient,     {0} },
	{ MODKEY|ShiftMask,             XK_space,  			togglefloating, {0} },
	{ MODKEY|ShiftMask,             XK_0,      			tag,            {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_Return, 			spawn,		{.v = termcmd } },
	{ MODKEY,			XK_F9, 				spawn, 		{.v = xrandrkey} },
	{ MODKEY,			XK_s, 				spawn, 		{.v = sysinfo} },
	{ MODKEY,			XK_F5,				spawn,		{.v = fanmode} },
	{ MODKEY,			XK_t,				spawn,		{.v = tdpswitch} },
	{ MODKEY,			XK_r,				spawn,		{.v = dispswitch} },
	{ 0, 				XF86XK_AudioMute, 		spawn, 		{.v = mutecmd } },
	{ 0, 				XF86XK_AudioLowerVolume, 	spawn, 		{.v = voldowncmd } },
	{ 0, 				XF86XK_AudioRaiseVolume, 	spawn, 		{.v = volupcmd } },
	{ 0, 				XF86XK_MonBrightnessUp, 	spawn, 		{.v = brupcmd} },
	{ 0, 				XF86XK_MonBrightnessDown, 	spawn, 		{.v = brdowncmd} },
	{ 0, 				XF86XK_AudioNext, 		spawn, 		{.v = tracknext} },
	{ 0, 				XF86XK_AudioPrev, 		spawn, 		{.v = trackprev} },
	{ 0, 				XF86XK_AudioPlay, 		spawn, 		{.v = trackplaypause} },
	{ 0,				XK_Print, 			spawn, 		{.v = fullscreenshot} },
	{ MODKEY,			XK_Print, 			spawn, 		{.v = windowscreenshot} },
	{ MODKEY|ShiftMask,		XK_Print, 			spawn, 		{.v = selscreenshot} },
	{ MODKEY|ShiftMask,		XK_l,				spawn,		{.v = setslock} },
	TAGKEYS(                        XK_1,                      			0)
	TAGKEYS(                        XK_2,                      			1)
	TAGKEYS(                        XK_3,                      			2)
	TAGKEYS(                        XK_4,                      			3)
	TAGKEYS(                        XK_5,                      			4)
	TAGKEYS(                        XK_6,                      			5)
	TAGKEYS(                        XK_7,                      			6)
	TAGKEYS(                        XK_8,                      			7)
	TAGKEYS(                        XK_9,                      			8)
	{ MODKEY|ShiftMask,             XK_q,      			quit,		{0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

