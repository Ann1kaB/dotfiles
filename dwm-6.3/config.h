/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 0;        /* border pixel of windows */
static const int startwithgaps       = 0;        /* 1 means gaps are used by default */
static const unsigned int gappx     = 10;       /* default gap between windows in pixels */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "Fira Mono:size=10:style=Regular", "Noto Sans Symbols2:size=12" };
static const char dmenufont[]       = "monospace:size=12";
//#include "/home/hyperkvm/.cache/wal/colors-wal-dwm.h"
static const char norm_fg[] = "#b5d0e8";
static const char norm_bg[] = "#000000";
static const char norm_border[] = "#ac9aa5";

static const char sel_fg[] = "#b5d0e8";
static const char sel_bg[] = "#000000";
static const char sel_border[] = "#f6ddec";

/*
static const char urg_fg[] = "#a36599";
static const char urg_bg[] = "#D5A3D2";
static const char urg_border[] = "#D5A3D2";
*/
static const char *colors[][3]      = {
    /*               fg           bg         border                         */
    [SchemeNorm] = { norm_fg,     norm_bg,   norm_border }, // unfocused wins
    [SchemeSel]  = { sel_fg,      sel_bg,    sel_border },  // the focused win
//    [SchemeUrg] =  { urg_fg,      urg_bg,    urg_border },
};

#include <X11/XF86keysym.h>

/* tagging */
static const char *tags[] = { "一", "二", "三", "四", "五", "六", "七", "八", "九" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      	  	instance    		title			tags mask     	isfloating   monitor */
	{ "Gimp",     	  		NULL,			NULL,       				0,		1,           -1 },
	{ "firefox",  	  		NULL,			NULL,       				1 << 8,		0,           -1 },
	{ "discord",  	  		NULL,       		NULL,       				1,		0,           -1 },
	{ "Pavucontrol", 		NULL,			"Volume Control",			1 << 2,		0,           -1 },
	{ "Nvidia-settings", 		NULL,			"NVIDIA Settings",			1 << 2,		0,           -1 },
	{ "dolphin-emu",  		NULL,			NULL,					1 << 3,		0,           -1 },
	{ "Ryujinx",  			NULL,			"Ryujinx 1.0.0-ldn2.4",			1 << 3,		0,           -1 },
	{ "Steam",			NULL,			"Steam",				1 << 4,		0,           -1 },
	{ "an-anime-game-launcher",	NULL,			"An Anime Game Launcher - 2.7.0",	1 << 4,		0,           -1 },
	//{ "St",				NULL,			NULL,					1 << 5,		0,           -1 },

};

//#include <X11/XF86keysym.h>

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 0; /* 1 will force focus on the fullscreen window */

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

/* commands */
static const char status[] = "dwm-status";
static const char sleep_time[] = "10";
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, NULL };
static const char *termcmd[]  = { "st", NULL };
//volume control
static const char *mutecmd[] = { status, "volume --mute", sleep_time, NULL };
static const char *volupcmd[] = { status, "volume --up", sleep_time, NULL };
static const char *voldowncmd[] = { status, "volume --down", sleep_time, NULL };
static const char *micmutecmd[] = { status, "volume --source-mute", sleep_time, NULL };
static const char *switchsink[] = { status, "volume --switch-sink", sleep_time, NULL };
static const char *switchsource[] = { status, "volume --switch-source", sleep_time, NULL };
static const char *switchcodec[] = { status, "volume --switch-codec", sleep_time, NULL };
//brightness control
static const char *brupcmd[] = { status, "backlight --up", sleep_time, NULL };
static const char *brdowncmd[] = { status, "backlight --down", sleep_time, NULL };
//media control
static const char *tracknext[] = { "playerctl", "next", NULL };
static const char *trackprev[] = { "playerctl", "previous", NULL };
static const char *trackplaypause[] = { "playerctl", "play-pause", NULL };
//screenshot control
static const char *fullscreenshot[] = { "screenshot",  NULL };
static const char *windowscreenshot[] = { "screenshot", "window", NULL };
static const char *selscreenshot[] = { "screenshot", "select", NULL };
//system info
static const char *fanmode[] = { status, "fanmode", sleep_time, NULL };
static const char *tracker[] = { status, NULL };
static const char *xrandrkey[] = { status, "xrandrconf", sleep_time, NULL };
//TDP switch
static const char *tdpswitch[] = { status, "sudo set-tdp", sleep_time, NULL };
//screen lock
static const char *setslock[] = { "slock", "NULL" };
//ASUS aura RGB control
static const char *auramodedown[] = { status, "auramodeswitch", sleep_time, NULL };
static const char *auramodeup[] = { status, "auramodeswitch -u", sleep_time, NULL };
static const char *auramodecheck[] = { status, "auramodeswitch -c", sleep_time, NULL };

static Key keys[] = {
        /* modifier                     key                             function        argument */
        { MODKEY,                       XK_o,                           spawn,          {.v = dmenucmd } },
        { MODKEY,                       XK_b,                           togglebar,      {0} },
        { MODKEY,                       XK_j,                           focusstack,     {.i = +1 } },
        { MODKEY,                       XK_k,                           focusstack,     {.i = -1 } },
        { MODKEY,                       XK_i,                           incnmaster,     {.i = +1 } },
        { MODKEY,                       XK_d,                           incnmaster,     {.i = -1 } },
        { MODKEY,                       XK_h,                           setmfact,       {.f = -0.05} },
        { MODKEY,                       XK_l,                           setmfact,       {.f = +0.05} },
        { MODKEY,                       XK_Return,                      zoom,           {0} },
        { MODKEY,                       XK_Tab,                         view,           {0} },
        { MODKEY,                       XK_t,                           setlayout,      {.v = &layouts[0]} },
        { MODKEY,                       XK_f,                           setlayout,      {.v = &layouts[1]} },
        { MODKEY,                       XK_m,                           setlayout,      {.v = &layouts[2]} },
        { MODKEY,                       XK_space,                       setlayout,      {0} },
        { MODKEY,                       XK_0,                           view,           {.ui = ~0 } },
        { MODKEY,                       XK_comma,                       focusmon,       {.i = -1 } },
        { MODKEY,                       XK_period,                      focusmon,       {.i = +1 } },
        { MODKEY|ShiftMask,             XK_comma,                       tagmon,         {.i = -1 } },
        { MODKEY|ShiftMask,             XK_period,                      tagmon,         {.i = +1 } },
        { MODKEY|ShiftMask,             XK_c,                           killclient,     {0} },
        { MODKEY|ShiftMask,             XK_space,                       togglefloating, {0} },
        { MODKEY|ShiftMask,             XK_0,                           tag,            {.ui = ~0 } },
        { MODKEY|ShiftMask,             XK_period, 			tagmon,         {.i = +1 } },
        { MODKEY,                       XK_minus,  			setgaps,        {.i = -5 } },
        { MODKEY,                       XK_equal,  			setgaps,        {.i = +5 } },
        { MODKEY|ShiftMask,             XK_minus,  			setgaps,        {.i = GAP_RESET } },
        { MODKEY|ShiftMask,             XK_equal,  			setgaps,        {.i = GAP_TOGGLE} },
        { MODKEY|ShiftMask,             XK_Return,                      spawn,          {.v = termcmd } },
        { MODKEY,                       XK_F9,                          spawn,          {.v = xrandrkey} },
        { MODKEY,                       XK_s,                           spawn,          {.v = tracker} },
        { MODKEY,                       XK_F5,                          spawn,          {.v = fanmode} },
        { MODKEY,                       XK_Down,                        spawn,          {.v = auramodedown} },
        { MODKEY,                       XK_Up,                          spawn,          {.v = auramodeup} },
        { MODKEY,                       XK_a,                           spawn,          {.v = auramodecheck} },
        { MODKEY,                       XK_p,                           spawn,          {.v = tdpswitch} },
        { 0,                            XF86XK_AudioMute,               spawn,          {.v = mutecmd } },
        { 0,                            XF86XK_AudioLowerVolume,        spawn,          {.v = voldowncmd } },
        { 0,                            XF86XK_AudioRaiseVolume,        spawn,          {.v = volupcmd } },
	{ ShiftMask,			XF86XK_AudioMute,		spawn,		{.v = switchsink } },
	{ MODKEY,			XK_F4,				spawn,		{.v = micmutecmd } },
	{ MODKEY|ShiftMask,		XK_F4,				spawn,		{.v = switchsource } },
	{ ShiftMask,			XK_F4,				spawn,		{.v = switchcodec } },
        { 0,                            XF86XK_MonBrightnessUp,         spawn,          {.v = brupcmd} },
        { 0,                            XF86XK_MonBrightnessDown,       spawn,          {.v = brdowncmd} },
        { 0,                            XF86XK_AudioNext,               spawn,          {.v = tracknext} },
        { 0,                            XF86XK_AudioPrev,               spawn,          {.v = trackprev} },
        { 0,                            XF86XK_AudioPlay,               spawn,          {.v = trackplaypause} },
        { 0,                            XK_Print,                       spawn,          {.v = fullscreenshot} },
        { MODKEY,                       XK_Print,                       spawn,          {.v = windowscreenshot} },
        { MODKEY|ShiftMask,             XK_Print,                       spawn,          {.v = selscreenshot} },
        { MODKEY|ShiftMask,             XK_l,                           spawn,          {.v = setslock} },
        TAGKEYS(                        XK_1,                                           0)
        TAGKEYS(                        XK_2,                                           1)
        TAGKEYS(                        XK_3,                                           2)
        TAGKEYS(                        XK_4,                                           3)
        TAGKEYS(                        XK_5,                                           4)
        TAGKEYS(                        XK_6,                                           5)
        TAGKEYS(                        XK_7,                                           6)
        TAGKEYS(                        XK_8,                                           7)
        TAGKEYS(                        XK_9,                                           8)
        { MODKEY|ShiftMask,             XK_q,                           quit,           {0} },
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

