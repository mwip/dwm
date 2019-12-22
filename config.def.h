/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "Ubuntu Mono Nerd Font:size=11" };
static const char dmenufont[]       = "Ubuntu Mono Nerd Font:size=11";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char col_red[]         = "#ff0000";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_red  },
};

/* tagging */
static const char *tags[] = { "1:", "2:", "3:", "4:", "5:", "6:ﱘ", "7:", "8:", "9:" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            0,           -1 },
	{ "Firefox",  NULL,       NULL,       0,            0,           -1 },
	{ "KeePassXC",NULL,       NULL,       0,            0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.5; /* factor of master area size [0.05..0.95] */
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
#define XF86AudioMute 0x1008ff12
#define XF86AudioLowerVolume 0x1008ff11
#define XF86AudioRaiseVolume 0x1008ff13
#define XF86AudioPlay 0x1008ff14
#define XF86AudioNext 0x1008ff17
#define XF86AudioPrev 0x1008ff16
#define XF86MonBrightnessUp 0x1008ff02
#define XF86MonBrightnessDown 0x1008ff03
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "/home/loki/.scripts/dmenu_recent.sh", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "urxvtc", NULL };
static const char *browsercmd[] = { "firefox", NULL };
static const char *brightness_up[]  =   { "/home/loki/.scripts/brightness.sh", "+", NULL };
static const char *brightness_down[]  = { "/home/loki/.scripts/brightness.sh", "-", NULL };
static const char *volume_up[]  = { "/home/loki/.scripts/adjust_volume.sh", "+", NULL };
static const char *volume_down[]  = { "/home/loki/.scripts/adjust_volume.sh", "-", NULL };
static const char *volume_mute[] = { "/home/loki/.scripts/adjust_volume.sh", "m", NULL };
static const char *ref_bar[] = {"/home/loki/.scripts/dwm_ref_bar.sh", NULL };
static const char *file_menu[] = {"/home/loki/.scripts/dmenu_filemanager.sh", NULL };
static const char *display_select[] = {"/home/loki/.scripts/dmenu_displayselect.sh", NULL };
static const char *exit_menu[] = {"/home/loki/.scripts/dmenu_exit.sh", NULL };
static const char *emacscmd[] = {"emacs", NULL};
static const char *screenshot[] = {"/home/loki/.scripts/screenshot_full.sh", NULL};
static const char *screenshot_region[] = {"/home/loki/.scripts/screenshot_region.sh", NULL};
static const char *mpc_playpause[] = {"/home/loki/.scripts/mpc_playpause.sh", NULL };
static const char *mpc_next[] = {"mpc", "next", NULL };
static const char *mpc_prev[] = {"mpc", "prev", NULL };
static const char *reset_bt[] = {"/home/loki/.scripts/pabluezswitch.sh", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_r,      spawn,          {.v = dmenucmd } },
	{ ControlMask|Mod1Mask,         XK_e,      spawn,          {.v = emacscmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY|ControlMask,           XK_Return, spawn,          {.v = browsercmd } },
	{ MODKEY,                       XK_e,      spawn,          {.v = file_menu } },
	{ MODKEY,                       XK_p,      spawn,          {.v = display_select } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_q,      killclient,     {0} },
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
	{ MODKEY|ShiftMask,             XK_q,      spawn,          {.v = exit_menu } },
	{ MODKEY|ShiftMask|ControlMask, XK_q,      quit,           {0} },
	{ 0,                            XF86MonBrightnessUp, spawn, {.v = brightness_up } },
	{ 0,                            XF86MonBrightnessUp, spawn, {.v = ref_bar } },
	{ 0,                            XF86MonBrightnessDown, spawn, {.v = brightness_down } },
	{ 0,                            XF86MonBrightnessDown, spawn, {.v = ref_bar } },
	{ 0,                            XF86AudioMute, spawn,      {.v = volume_mute } },
	{ 0,                            XF86AudioMute, spawn,      {.v = ref_bar } },
	{ 0,                            XF86AudioRaiseVolume, spawn, {.v = volume_up } },
	{ 0,                            XF86AudioRaiseVolume, spawn, {.v = ref_bar } },
	{ 0,                            XF86AudioLowerVolume, spawn, {.v = volume_down } },
	{ 0,                            XF86AudioLowerVolume, spawn, {.v = ref_bar } },
	{ MODKEY,                       XK_s,      spawn,          {.v = screenshot } },
	{ MODKEY|ShiftMask,             XK_s,      spawn,          {.v = screenshot_region } },
	{ 0,                            XF86AudioPlay, spawn, 	   {.v = mpc_playpause } },
	{ 0,                            XF86AudioNext, spawn,      {.v = mpc_next } },
	{ 0,                            XF86AudioPrev, spawn,      {.v = mpc_prev } },
	{ MODKEY|ShiftMask,		XK_b, 	spawn, 		{.v = reset_bt } },
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

