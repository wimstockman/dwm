/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int gappx     = 5;        /* gap pixel between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int rmaster            = 1;        /* 1 means master-area is initially on the right */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const char *fonts[]          = { 
		"Mononoki Nerd Font:size=12:antialias=true:autohint=true",
		"Noto Sans Mono:size=12:antialias=true:autohint=true",
		"Symbola:size=12:antialias=true:autohint=true",
		"Monospace:size=12:antialias=true:autohint=true"
};
static const char dmenufont[]       = "Mononoki Nerd Font:size=12:antialias=true:autohint=true";
static const char col_cyan[]          = "#3399FF"; /* border color focused windows and tags */
static const char col_red[]          = "red"; /* border color focused windows and tags */
static const char col_bluemariner[]    = "#3366CC"; /* border color focused windows and tags */
static const char col_white[]          ="#FFFFFF"; /* border color focused windows and tags */
static const char col_black[]          ="#000000"; /* border color focused windows and tags */
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_white, col_black, col_bluemariner },
	[SchemeSel]  = { col_white, col_cyan,  col_red  },

};

/* tagging */
//static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };
static const char *tags[] = { "","☯", "\ue005", "", "", "", "\uf263", "", "" };
static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class     instance  title           tags mask  isfloating  isterminal  noswallow  monitor */
	{ "Gimp",    NULL,     NULL,           0,         1,          0,           0,        -1 },
	{ "Firefox", NULL,     NULL,           1 << 8,    0,          0,          0,        -1 },
	{ "St",      NULL,     NULL,           0,         0,          1,          0,        -1 },
	{ NULL,      NULL,     "Event Tester", 0,         1,          0,           1,        -1 }, /* xev */
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

#include "fibonacci.c"
#include "layouts.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "TTT",      bstack },
	{ "===",      bstackhoriz },
	{ "[M]",      monocle },
	{ "|M|",      centeredmaster },
 	{ "[@]",      spiral },
 	{ "[\\]",     dwindle },
	{ "HHH",      grid },
	{ ">M>",      centeredfloatingmaster },
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ NULL,       NULL },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                     KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ Mod5Mask,                   KEY,      tag,            {.ui = 1 << TAG} }, \
	{ Mod5Mask|ShiftMask,         KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_white, "-nf", col_cyan, "-sb", col_cyan, "-sf", col_bluemariner, NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *filemanager[]  = { "st","nnn","-d", NULL };
static const char *brave[]  = { "brave", NULL };
static const char *firefox[]  = { "firefox", NULL };
static const char *thunderbird[]  = { "thunderbird", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ Mod5Mask,                     XK_v,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY	,             	XK_Return, spawn,          {.v = termcmd } },
	{ Mod5Mask,             	XK_b,	   spawn,          {.v = brave } },
	{ Mod5Mask,             	XK_m,	   spawn,          {.v = thunderbird } },
	{ Mod5Mask,             	XK_w,	   spawn,          {.v = firefox } },
	{ Mod5Mask,             	XK_z,	   spawn,          {.v = filemanager } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ Mod5Mask,                     XK_h,      focusstack,     {.i = -1 } },
	{ Mod5Mask,                     XK_n,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_c,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_t,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_n,      setmfact,       {.f = +0.05} },
	{ Mod5Mask,                     XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ Mod5Mask,             	XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_a,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_o,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_e,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_u,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY,                       XK_i,      setlayout,      {.v = &layouts[4]} },
	{ MODKEY|ShiftMask,             XK_a,      setlayout,      {.v = &layouts[5]} },
	{ MODKEY|ShiftMask,             XK_o,      setlayout,      {.v = &layouts[6]} },
	{ MODKEY|ShiftMask,             XK_e,      setlayout,      {.v = &layouts[7]} },
	{ MODKEY|ShiftMask,             XK_u,      setlayout,      {.v = &layouts[8]} },
	{ MODKEY|ShiftMask,             XK_i,      setlayout,      {.v = &layouts[9]} },
	{ Mod5Mask,		        XK_k,      cyclelayout,    {.i = -1 } },
	{ Mod5Mask,                     XK_x,      cyclelayout,    {.i = +1 } },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ Mod5Mask,                     XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_r,      togglermaster,  {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ Mod5Mask,                     XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_f,      tagmon,             {.i = -1 } },
	{ MODKEY,                       XK_d,      tagmon,             {.i = +1 } },
	{ Mod5Mask,                     XK_f,  focusmon,          {.i = -1 } },
	{ Mod5Mask,                     XK_d, focusmon,         {.i = +1 } },
	{ MODKEY,                       XK_equal, setgaps,         {.i = +1 } },
	{ Mod5Mask,                     XK_equal,  setgaps,        {.i = -1 } },
	TAGKEYS(                        XK_ampersand,                      0)
	TAGKEYS(                        XK_bracketleft,                    1)
	TAGKEYS(                        XK_braceleft,                      2)
	TAGKEYS(                        XK_braceright,                     3)
	TAGKEYS(                        XK_parenleft,                      4)
	TAGKEYS(                        XK_asterisk,                       5)
	TAGKEYS(                        XK_parenright,                     6)
	TAGKEYS(                        XK_plus,                           7)
	TAGKEYS(                        XK_bracketright,                   8)
	{ Mod5Mask,             XK_q,      quit,           {0} },
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

static const char *dwmfifo = "/tmp/dwm.fifo";
static Command commands[] = {
	{ "dmenu",           spawn,          {.v = dmenucmd} },
	{ "term",            spawn,          {.v = termcmd} },
	{ "quit",            quit,           {0} },
	{ "togglebar",       togglebar,      {0} },
	{ "focusstack+",     focusstack,     {.i = +1} },
	{ "focusstack-",     focusstack,     {.i = -1} },
	{ "incnmaster+",     incnmaster,     {.i = +1} },
	{ "incnmaster-",     incnmaster,     {.i = -1} },
	{ "setmfact+",       setmfact,       {.f = +0.05} },
	{ "setmfact-",       setmfact,       {.f = -0.05} },
	{ "zoom",            zoom,           {0} },
	{ "view",            view,           {0} },
	{ "killclient",      killclient,     {0} },
	{ "setlayout-tiled", setlayout,      {.v = &layouts[0]} },
	{ "setlayout-float", setlayout,      {.v = &layouts[1]} },
	{ "setlayout-mono",  setlayout,      {.v = &layouts[2]} },
	{ "togglelayout",    setlayout,      {0} },
	{ "togglefloating",  togglefloating, {0} },
	{ "viewall",         view,           {.ui = ~0} },
	{ "tag",             tag,            {.ui = ~0} },
	{ "focusmon+",       focusmon,       {.i = +1} },
	{ "focusmon-",       focusmon,       {.i = -1} },
	{ "tagmon+",         tagmon,         {.i = +1} },
	{ "tagmon-",         tagmon,         {.i = -1} },
	{ "view1",           view,           {.ui = 1 << 0} },
	{ "view2",           view,           {.ui = 1 << 1} },
	{ "view3",           view,           {.ui = 1 << 2} },
	{ "view4",           view,           {.ui = 1 << 3} },
	{ "view5",           view,           {.ui = 1 << 4} },
	{ "view6",           view,           {.ui = 1 << 5} },
	{ "view7",           view,           {.ui = 1 << 6} },
	{ "view8",           view,           {.ui = 1 << 7} },
	{ "view9",           view,           {.ui = 1 << 8} },
	{ "toggleview1",     toggleview,     {.ui = 1 << 0} },
	{ "toggleview2",     toggleview,     {.ui = 1 << 1} },
	{ "toggleview3",     toggleview,     {.ui = 1 << 2} },
	{ "toggleview4",     toggleview,     {.ui = 1 << 3} },
	{ "toggleview5",     toggleview,     {.ui = 1 << 4} },
	{ "toggleview6",     toggleview,     {.ui = 1 << 5} },
	{ "toggleview7",     toggleview,     {.ui = 1 << 6} },
	{ "toggleview8",     toggleview,     {.ui = 1 << 7} },
	{ "toggleview9",     toggleview,     {.ui = 1 << 8} },
	{ "tag1",            tag,            {.ui = 1 << 0} },
	{ "tag2",            tag,            {.ui = 1 << 1} },
	{ "tag3",            tag,            {.ui = 1 << 2} },
	{ "tag4",            tag,            {.ui = 1 << 3} },
	{ "tag5",            tag,            {.ui = 1 << 4} },
	{ "tag6",            tag,            {.ui = 1 << 5} },
	{ "tag7",            tag,            {.ui = 1 << 6} },
	{ "tag8",            tag,            {.ui = 1 << 7} },
	{ "tag9",            tag,            {.ui = 1 << 8} },
	{ "toggletag1",      toggletag,      {.ui = 1 << 0} },
	{ "toggletag2",      toggletag,      {.ui = 1 << 1} },
	{ "toggletag3",      toggletag,      {.ui = 1 << 2} },
	{ "toggletag4",      toggletag,      {.ui = 1 << 3} },
	{ "toggletag5",      toggletag,      {.ui = 1 << 4} },
	{ "toggletag6",      toggletag,      {.ui = 1 << 5} },
	{ "toggletag7",      toggletag,      {.ui = 1 << 6} },
	{ "toggletag8",      toggletag,      {.ui = 1 << 7} },
	{ "toggletag9",      toggletag,      {.ui = 1 << 8} },
};
