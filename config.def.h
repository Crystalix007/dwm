/* See LICENSE file for copyright and license details. */

//Include XFree86 key definitions
#include <X11/XF86keysym.h>

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "droid sans mono:size=14" };
static const char dmenufont[]       = "droid sans mono 12";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#335577";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

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
	{ "cantata",  NULL,       NULL,       1 << 1,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

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
static char launchermon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
// static const char *launchercmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *launchercmd[] = { "rofi", "-show", "run", "-monitor ", launchermon, "-matching", "regex", "-font", dmenufont, NULL};
static const char *termcmd[]  = { "konsole", NULL };

//Modify "Master" to be whichever interface has capability 'pvolume' when running `amixer`
static const char *volupactioncmd[]  = { "amixer", "set", "Master", "1%+", NULL };
static const char *voldownactioncmd[]  = { "amixer", "set", "Master", "1%-", NULL };
static const char *audiomuteactioncmd[] = { "amixer", "set", "Master", "toggle", NULL };

//Current volume notification
static const char *volnotifycmd[] = { "bash", "-c", "~/script/notify-send.sh --replace-file=/tmp/volumenotification --expire-time 1000 `amixer get Master | sed -ne \'/Front Left/s/.*\\[\\(.*\\)%\\].*/\\1% volume/p\'`", NULL };

static const char *audiomutenotifycmd[] = { "bash", "-c", "~/script/notify-send.sh --replace-file=/tmp/mutenotification --expire-time 1000 \"`amixer get Master | sed -E -ne \'/Front Left/s/.*\\[([^0-9].*)\\].*/Audio output \\1/p\'`\"", NULL };
//static const char *audiomutenotifycmd[] = { "bash", "-c", "echo \"~/script/notify-send.sh --replace-file=/tmp/mutenotification --expire-time 1000 \'`amixer get Master | sed -E -ne \'/Front Left/s/.*\\[([^0-9].*)\\].*/Audio output \\1/p\'`\'\" >> ~/Mute.log", NULL };

//Will end up pausing and resuming all music clients currently open
static const char *mediatogglecmd[] = { "bash", "-c", "for i in $(qdbus org.mpris.MediaPlayer2.*); do qdbus $i /org/mpris/MediaPlayer2 org.mpris.MediaPlayer2.Player.PlayPause; done", NULL };

//Will stop all music clients entirely
static const char *mediastopcmd[] = { "bash", "-c", "for i in $(qdbus org.mpris.MediaPlayer2.*); do qdbus $i /org/mpris/MediaPlayer2 org.mpris.MediaPlayer2.Player.Stop; done", NULL };

//Will go forward a track in all music clients
static const char *medianextcmd[] = { "bash", "-c", "for i in $(qdbus org.mpris.MediaPlayer2.*); do qdbus $i /org/mpris/MediaPlayer2 org.mpris.MediaPlayer2.Player.Next; done", NULL };

//Will go backward a track in all music clients
static const char *mediaprevcmd[] = { "bash", "-c", "for i in $(qdbus org.mpris.MediaPlayer2.*); do qdbus $i /org/mpris/MediaPlayer2 org.mpris.MediaPlayer2.Player.Previous; done", NULL };

static const Arg volupcmd[] = { { .v = volupactioncmd }, { .v = volnotifycmd }, { .v = NULL } };
static const Arg voldowncmd[] = { { .v = voldownactioncmd }, { .v = volnotifycmd }, { .v = NULL } };
static const Arg audiomutecmd[] = { { .v = audiomuteactioncmd }, { .v = audiomutenotifycmd }, { .v = NULL } };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ 0,				XF86XK_AudioRaiseVolume, spawns, { .v = volupcmd } },
	{ 0,				XF86XK_AudioLowerVolume, spawns, { .v = voldowncmd } },
	{ 0,				XF86XK_AudioMute, spawns, { .v = audiomutecmd } },
	{ 0,				XF86XK_AudioPlay, spawn,  {.v = mediatogglecmd } },
	{ 0,				XF86XK_AudioStop, spawn,  {.v = mediastopcmd } },
	{ 0,				XF86XK_AudioNext, spawn,  {.v = medianextcmd } },
	{ 0,				XF86XK_AudioPrev, spawn,  {.v = mediaprevcmd } },
	{ MODKEY,                       XK_p,      spawn,          {.v = launchercmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_k,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_l,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_j,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_semicolon,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_F4,     quit,           {Quit} },
	{ MODKEY|ShiftMask,		XK_r,      quit,           {Restart} },
};

/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
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

