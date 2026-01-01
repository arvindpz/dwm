/* See LICENSE file for copyright and license details. */

/* To store windows-to-tag information before restarts,
 * so that they can be restored */
#define SESSION_FILE "/tmp/dwm-session"

/* appearance */
static const unsigned int borderpx  = 2;    /* border pixel of windows */
static const unsigned int snap      = 32;   /* snap pixel */
static const unsigned int gappih    = 20;   /* horiz inner gap between windows */
static const unsigned int gappiv    = 10;   /* vert inner gap between windows */
static const unsigned int gappoh    = 20;   /* gap between top/bottom of the window to screen's edge */
static const unsigned int gappov    = 20;   /* vert outer gap between windows and screen edge */
static       int smartgaps          = 0;    /* 1 means no outer gap when there is only one window */

static const int showbar            = 1;    /* 0 means no bar */
static const int topbar             = 1;    /* 0 means bottom bar */

static const char *fonts[]          = { "monospace:size=14" };
static const char dmenufont[]       = "monospace:size=10";

static unsigned int baralpha        = 0xa0;
static unsigned int borderalpha     = OPAQUE;

/* The following 6 colors can be set in Xresources too */
/* They can be modified and the reloaded without building dwm */
static char normbgcolor[]           = "#000000";  // Black, Idk where this is used
static char normfgcolor[]           = "#ffffff";  // Same
static char normbordercolor[]       = "#ffffff";

static char selbgcolor[]            = "#000000";  // Unsure where this is used
static char selfgcolor[]            = "#ffffff";  // Same
static char selbordercolor[]        = "#ffffff";

static char clrwhitesmoke[]         = "#f5f5f5";
static char clrplum[]               = "#a19ac8";
static char clrdarkplum[]           = "#5c2eb7";
static char clrblack[]              = "#000000";
static char clrpaleturquoise[]      = "#afeeee";
static char clrdarkslategrey[]      = "#2f4f4f";
static char clrpowderblue[]         = "#bfd8d9";
static char clrunused[]             = "#000000";


static char *colors[][3] = {
	/*                         fg                   bg                     border     */
	[SchemeNorm]      =  { normfgcolor,         normbgcolor,           normbordercolor },   /* Normal client (unselected window) */
	[SchemeSel]       =  { selfgcolor,          selbgcolor,            selbordercolor  },   /* Selected client (selected window) */

	[SchemeStatus]    =  { clrblack,            clrpaleturquoise,      clrunused       },   /* Right portion of the top bar */

	[SchemeTagsSel]   =  { clrdarkplum,         clrwhitesmoke,         clrunused       },
	[SchemeTagsNorm]  =  { clrwhitesmoke,       clrplum,               clrunused       },

	[SchemeInfoSel]   =  { clrdarkslategrey,    clrpowderblue,         clrunused       },   /* Middle portion of top bar for active non-empty tag */
	[SchemeInfoNorm]  =  { clrunused,           clrwhitesmoke,         clrunused       },   /* Middle portion of top bar for inactive or empty tag */
};

#include "vanitygaps.c"

/* applications */
#define TERM "st"
#define BROWSER "brave-browser"

/* tagging */
// How tagmask works - https://dwm.suckless.org/customisation/tagmask/
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class	  instance	title	   tags mask	 isfloating   monitor */
	{ "Gimp",	 NULL,	   NULL,	   0,			1,		   -1 },
};

/* layout(s) */
static const float mfact	 = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster	 = 1;	/* number of clients in master area */
static const int resizehints = 1;	/* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 0; /* 1 will force focus on the fullscreen window */
static const int refreshrate = 120;  /* refresh rate (per second) for client move/resize */

static const Layout layouts[] = {
	/* symbol	 arrange function */
	{ "[]=",	  tile },	/* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",	  monocle },
	{ "[@]",      spiral },
	{ "[\\]",     dwindle },
	{ NULL,       NULL }
};

/* key definitions */
#define MODKEY Mod4Mask		   // Use windows key as modifier
#define VISMODKEY Mod1Mask   // Alt
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,					   KEY,	  view,		   {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,		   KEY,	  toggleview,	 {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,			 KEY,	  tag,			{.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,	  toggletag,	  {.ui = 1 << TAG} },

#define STACKKEYS(MOD,ACTION) \
	{ MOD, XK_j,     ACTION##stack, {.i = INC(+1) } }, \
	{ MOD, XK_k,     ACTION##stack, {.i = INC(-1) } }, \
	{ MOD, XK_grave, ACTION##stack, {.i = PREVSEL } }, \
	/* { MOD, XK_q,     ACTION##stack, {.i = 0 } }, \
	{ MOD, XK_a,     ACTION##stack, {.i = 1 } }, \
	{ MOD, XK_z,     ACTION##stack, {.i = 2 } }, \
	{ MOD, XK_x,     ACTION##stack, {.i = -1 } }, */
   /* 0 -> Master pane, 1 -> 1st in stack, 2 -> 2nd in stack
   * -1 -> last in stack, -2 -> second last in stack */

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

#define STATUSBAR "dwmblocks"

/* commands */

// Enable both outputs, then set relative position and primary.
#define START_MONITOR "xrandr --output edP --auto --pos 0x0 --output DisplayPort-1 --auto --pos 1920x0 --primary"
#define STOP_MONITOR "xrandr --output DisplayPort-1 --off && xrandr --output edP --primary"

static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbordercolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]  = { TERM, "-e", "/usr/bin/zsh", "-l", NULL };

static const Key keys[] = {
	/* modifier					 key		function		argument */
	{ MODKEY,					   XK_p,	  spawn,		  {.v = dmenucmd } },
	{ MODKEY,					   XK_Return, spawn,		  {.v = termcmd } },
	{ MODKEY,					   XK_b,	  spawn,		  SHCMD(BROWSER) },
	{ MODKEY,					   XK_F5,	 spawn,		  SHCMD(START_MONITOR) },
	{ MODKEY,					   XK_F6,	 spawn,		  SHCMD(STOP_MONITOR) },
	{ MODKEY|ShiftMask,	 XK_b,	  togglebar,	  {0} },
	{ MODKEY|ShiftMask,  XK_s,      togglesticky,   {0} },
	STACKKEYS(MODKEY,                          focus)
	STACKKEYS(MODKEY|ShiftMask,                push)
	{ MODKEY,					   XK_i,	  incnmaster,	 {.i = +1 } },
	{ MODKEY,					   XK_d,	  incnmaster,	 {.i = -1 } },
	{ MODKEY,					   XK_h,	  setmfact,	   {.f = -0.05} },
	{ MODKEY,					   XK_l,	  setmfact,	   {.f = +0.05} },
	{ MODKEY,					   XK_space,  zoom,		   {0} },

	{ MODKEY|VISMODKEY,              XK_u,      incrgaps,       {.i = +1 } },
	{ MODKEY|VISMODKEY|ShiftMask,    XK_u,      incrgaps,       {.i = -1 } },
	{ MODKEY|VISMODKEY,              XK_i,      incrigaps,      {.i = +1 } },
	{ MODKEY|VISMODKEY|ShiftMask,    XK_i,      incrigaps,      {.i = -1 } },
	{ MODKEY|VISMODKEY,              XK_o,      incrogaps,      {.i = +1 } },
	{ MODKEY|VISMODKEY|ShiftMask,    XK_o,      incrogaps,      {.i = -1 } },
	{ MODKEY|VISMODKEY,              XK_6,      incrihgaps,     {.i = +1 } },
	{ MODKEY|VISMODKEY|ShiftMask,    XK_6,      incrihgaps,     {.i = -1 } },
	{ MODKEY|VISMODKEY,              XK_7,      incrivgaps,     {.i = +1 } },
	{ MODKEY|VISMODKEY|ShiftMask,    XK_7,      incrivgaps,     {.i = -1 } },
	{ MODKEY|VISMODKEY,              XK_8,      incrohgaps,     {.i = +1 } },
	{ MODKEY|VISMODKEY|ShiftMask,    XK_8,      incrohgaps,     {.i = -1 } },
	{ MODKEY|VISMODKEY,              XK_9,      incrovgaps,     {.i = +1 } },
	{ MODKEY|VISMODKEY|ShiftMask,    XK_9,      incrovgaps,     {.i = -1 } },
	{ MODKEY|VISMODKEY,              XK_0,      togglegaps,     {0} },
	{ MODKEY|VISMODKEY|ShiftMask,    XK_0,      defaultgaps,    {0} },

	{ MODKEY,					   XK_Tab,	view,		   {0} },

	// Close current focused client (application window) in the current tag
	{ MODKEY,					   XK_q,	  killclient,	 {0} },

	// Close all the clients except the currently focused client in the current tag
	{ MODKEY|ShiftMask,			 XK_q,	  killclient,	 {.ui = 1} },

	// Close all the clients in the current tag
	// { MODKEY|ShiftMask|ControlMask, XK_c,	  killclient,	 {.ui = 2} },
	{ MODKEY|ShiftMask,					   XK_t,	  setlayout,	  {.v = &layouts[0]} },
	// { MODKEY,					   XK_f,	  setlayout,	  {.v = &layouts[1]} },
	{ MODKEY|ShiftMask,					   XK_m,	  setlayout,	  {.v = &layouts[2]} },
	{ MODKEY|ShiftMask|ControlMask,	 XK_F2,  cyclelayout,	  {.i = +1 } },
	{ MODKEY,					   XK_f,	  togglefullscreen,  {0} },
	{ MODKEY|ShiftMask,			 XK_f,  togglefloating, {0} },
	{ MODKEY,			 XK_m,  focusmaster, {0} },
	{ MODKEY,					   XK_0,	  view,		   {.ui = ~0 } },
	{ MODKEY|ShiftMask,			 XK_0,	  tag,			{.ui = ~0 } },
	{ MODKEY,					   XK_comma,  focusmon,	   {.i = -1 } },
	{ MODKEY,					   XK_period, focusmon,	   {.i = +1 } },
	{ MODKEY|ShiftMask,			 XK_comma,  tagmon,		 {.i = -1 } },
	{ MODKEY|ShiftMask,			 XK_period, tagmon,		 {.i = +1 } },
	TAGKEYS(						XK_1,					  0)
	TAGKEYS(						XK_2,					  1)
	TAGKEYS(						XK_3,					  2)
	TAGKEYS(						XK_4,					  3)
	TAGKEYS(						XK_5,					  4)
	TAGKEYS(						XK_6,					  5)
	TAGKEYS(						XK_7,					  6)
	TAGKEYS(						XK_8,					  7)
	TAGKEYS(						XK_9,					  8)
	// Save window to tag mapping in SESSION_FILE
	{ MODKEY,					   XK_F2,	 saveSession,	{0} },
	// Restart dwm using F3
	{ MODKEY|ShiftMask|ControlMask, XK_F3,	 quit,		   {1} },
	{ MODKEY|ShiftMask|ControlMask, XK_F5,	 xrdb,		   { .v = NULL } },

	/* I don't quit easily */
	{ MODKEY|ShiftMask|ControlMask, XK_q,	  quit,		   {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click				event mask	  button		  function		argument */
	{ ClkLtSymbol,		  0,			  Button1,		setlayout,	  {0} },
	{ ClkLtSymbol,		  0,			  Button3,		setlayout,	  {.v = &layouts[2]} },
	{ ClkWinTitle,		  0,			  Button2,		zoom,		   {0} },
	{ ClkStatusText,        0,              Button1,        sigstatusbar,   {.i = 1} },
	{ ClkStatusText,        0,              Button2,        sigstatusbar,   {.i = 2} },
	{ ClkStatusText,        0,              Button3,        sigstatusbar,   {.i = 3} },
	{ ClkStatusText,        0,              Button1,        sigstatusbar,   {.i = 4} },
	{ ClkStatusText,        0,              Button2,        sigstatusbar,   {.i = 5} },
	{ ClkStatusText,        0,              Button3,        sigstatusbar,   {.i = 6} },
	{ ClkClientWin,		 MODKEY,		 Button1,		movemouse,	  {0} },
	{ ClkClientWin,		 MODKEY,		 Button2,		togglefloating, {0} },
	{ ClkClientWin,		 MODKEY,		 Button3,		resizemouse,	{0} },
	{ ClkTagBar,			0,			  Button1,		view,		   {0} },
	{ ClkTagBar,			0,			  Button3,		toggleview,	 {0} },
	{ ClkTagBar,			MODKEY,		 Button1,		tag,			{0} },
	{ ClkTagBar,			MODKEY,		 Button3,		toggletag,	  {0} },
};
