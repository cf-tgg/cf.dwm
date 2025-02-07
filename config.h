/* [ dwm/config.h ] [ last update: 2025-02-05 07:15:28 EST ]
 *         __       _
 *    ___ / _|   __| |_      ___ __ ___
 *   / __| |_   / _` \ \ /\ / / '_ ` _ \
 *  | (__|  _| | (_| |\ V  V /| | | | | |
 *   \___|_|    \__,_| \_/\_/ |_| |_| |_|
 */

#define TERMINAL "st"
#define TERMCLASS "St"
#define BROWSER "qutebrowser"

/*     Appearance      */
static unsigned int borderpx =  1;   /* border pixel of windows */
static unsigned int snap     = 24;   /* snap pixel */
static unsigned int gappih   =  3;   /* horiz inner gap between windows */
static unsigned int gappiv   =  3;   /* vert inner gap between windows */
static unsigned int gappoh   =  3;   /* horiz outer gap between windows and screen edge */
static unsigned int gappov   =  3;   /* vert outer gap between windows and screen edge */

static int swallowfloating = 0; /* 1 means swallow floating windows by default */
static int smartgaps       = 0; /* 1 means no outer gap when there is only one window */

static int showbar = 1;       /* 0 means no bar */
static int topbar  = 1;       /* 0 means bottom bar */

static const int vertpad =  0; /* vertical padding of bar */
static const int sidepad =  0; /* horizontal padding of bar */
static const int user_bh = 48; /* 0 means that dwm will calculate bar height, >= 1 means dwm will user_bh as bar height */

static const char *fonts[] = {
    "Iosevka Nerd Font:size=9:style=Regular:antialias=true:autohint=true",
    "Iosevka Nerd Font Mono:size=11:style=Regular:antialias=true:autohint=true",
    "Iosevka Nerd Font Propo:size=10:style=Regular:antialias=true:autohint=true",
    "Caskaydia Cove Nerd Font:size=9:style=Book:antialias=true:autohint=true",
    "FontAwesome:pixelsize=36:antialias=true:autohint=true",
    "Iosevka Term:size=16:antialias=true:autohint=true",
    "NotoColorEmoji:pixelsize=22:antialias=true:autohint=true",
    "Material Icons:pixelsize=36:antialias=true:autohint=true"
};

static char normbgcolor[] = "#010101";
static char normfgcolor[] = "#99968e";
static char normbordercolor[] = "#0d0d0d";

static char selfgcolor[]     = "#bfbebf";
static char selbgcolor[]     = "#010101";
static char selbordercolor[] = "#1f1f1e";

static const double defaultopacity = 0.96;
static const double activeopacity = 0.98;   /* Window opacity when it's focused (0 <= opacity <= 1) */
static const double inactiveopacity = 0.96; /* Window opacity when it's inactive (0 <= opacity <= 1) */

static const unsigned int borderalpha = OPAQUE;
static const unsigned int baralpha = 200;

static const char *colors[][3] = {
    /*                   fg            bg              border      */
	[SchemeNorm] = { normfgcolor,   normbgcolor,    normbordercolor },
	[SchemeSel]  = { selfgcolor,    selbgcolor,     selbordercolor  },
};

static const unsigned int alphas[][3] = {
    /*                fg     bg       border    */
    [SchemeNorm] = {OPAQUE, baralpha, borderalpha},
    [SchemeSel]  = {OPAQUE, baralpha, borderalpha},
};

typedef struct {
  const char *name;
  const void *cmd;
} Sp;

const char *spcmd1[] = {TERMINAL, "-n", "spterm", "-g", "120x30", NULL};
const char *spcmd2[] = {TERMINAL, "-n", "spcalc", "-f", "monospace:size=50", "-g", "30x5", "-e", "bc",  "-lq", NULL};
const char *spcmd3[] = {TERMINAL, "-n", "spvclp", "-f", "monospace:size=40", "-g", "100x30", "-e",  "vimclip",  NULL};
const char *spcmd4[] = {TERMINAL, "-n", "spmpvq", "-f", "monospace:size=40", "-g", "100x30", "-e",  "mpvqls",   NULL};
const char *spcmd5[] = {TERMINAL, "-n", "spmpvf", "-f", "monospace:size=45", "-g", "90x35", "-e",  "mpvqfzf",   NULL};

static Sp scratchpads[] = {
    /* name         cmd  */
    {"spterm",      spcmd1},
    {"spcalc",      spcmd2},
    {"spvclp",      spcmd3},
    {"spmpvq",      spcmd4},
    {"spmpvf",      spcmd5},
};

/* static const char *tags[] = {"1", "2", "3", "4",  "5", "6", "7", "8 ", "9"}; */
static const char *tags[] = {"", " ", " ",  " ", " ", "", " ", " ", ""};

static const Rule rules[] = {
    /* class          instance     title          tags mask  isfloating  fopacity unfopacity isterminal  noswallow  monitor */
    {"Gimp",          NULL,        NULL,           1 << 4,     0,          1,             0,       1,          0,          -1},
    {"Blender",       NULL,        NULL,           1 << 4,     0,          1,          0.95,       0,          0,          -1},
    {"firefox",       NULL,        NULL,           1 << 2,     0,          1,          0.95,       0,          0,          -1},
    {"brave-browser", NULL,        NULL,           1 << 9,     0,          1,          0.95,       0,          0,          -1},
    {"chromium",      NULL,        NULL,           1 << 6,     0,          1,          0.95,       0,          0,          -1},
    {"surf",          NULL,        NULL,           1 << 2,     0,          1,          0.95,       0,          0,          -1},
    {"obs",           NULL,        NULL,           1 << 6,     0,          1,             1,       0,          0,          -1},
    {"qutebrowser",   NULL,        NULL,           0,          0,          1,          0.95,       0,          0,          -1},
    {"zathura",       NULL,        NULL,           0,          0,       0.90,          0.80,       0,          0,          -1},
    {TERMCLASS,       "neomutt",   NULL,           1 << 6,     0,          1,           0.9,       1,          1,          -1},
    {TERMCLASS,       NULL,        NULL,           0,          0,          1,             0,       1,          0,          -1},
    {TERMCLASS,       "bg",        NULL,           1 << 7,     0,          1,             0,       0,          0,          -1},
    {TERMCLASS,       "floatterm", NULL,           0,          1,          1,             0,       0,          0,          -1},
    {TERMCLASS,       "spterm",    NULL,           SPTAG(0),   1,          1,             0,       0,          0,          -1},
    {TERMCLASS,       "spcalc",    NULL,           SPTAG(1),   1,          1,             0,       0,          0,          -1},
    {TERMCLASS,       "spvclip",   NULL,           SPTAG(2),   1,          1,             0,       1,          1,          -1},
    {TERMCLASS,       "spmpvq",    NULL,           SPTAG(3),   1,          1,             0,       1,          1,          -1},
    {TERMCLASS,       "spmpvf",    NULL,           SPTAG(4),   1,          1,             0,       1,          1,          -1},
    {NULL,            NULL,        "Event Tester", 0,          0,          0,             1,       0,          0,          -1},
};

/* dynamic window swallowing */
static const int  swalretroactive =  15 ;
static const int  swaldecay       =  30 ;
static const char swalsymbol[]    = "👅";

/*  layouts hints */
static float mfact = 0.50;           /* factor of master area size [0.05..0.95] */
static int nmaster = 1;              /* number of clients in master area */
static int resizehints = 0;          /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 0; /* 1 will force focus on the fullscreen window */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
/*  Symbol           Layout                          Description */
    { "[]=",         tile },                      /* Default: Master on left, slaves on right */
    { "TTT",         bstack },                    /* Master on top, slaves on bottom */
    { "[@]",         spiral },                    /* Fibonacci spiral */
    { "[\\]",        dwindle },                   /* Decreasing in size right and leftward */
    { "[D]",         deck },                      /* Master on left, slaves in monocle-like mode on right */
    { "[M]",         monocle },                   /* All windows on top of eachother */
    { "|M|",         centeredmaster },            /* Master in middle, slaves on sides */
    { ">M>",         centeredfloatingmaster },    /* Same but master floats */
    { "===",         bstackhoriz },               /* Same as bstack but horizontal */
    { "HHH",         grid },                      /* Equal grid */
    { "###",         nrowgrid },                  /* Numbered row grid, incnmaster (Ctrl-o/Ctrl-O) to add/sub rows */
    { "---",         horizgrid },                 /* Horizontal grid */
    { ":::",         gaplessgrid },               /* Smarter "gap-less" grid */
    { "><>",         NULL },                      /* No layout means floating behavior */
    { NULL,          NULL },
};

/*  <Super> as main modkey */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
       &((Keychord){1, {{MODKEY, KEY}},                           view,           {.ui = 1 << TAG} }), \
       &((Keychord){1, {{MODKEY|ControlMask, KEY}},               toggleview,     {.ui = 1 << TAG} }), \
       &((Keychord){1, {{MODKEY|ShiftMask, KEY}},                 tag,            {.ui = 1 << TAG} }), \
       &((Keychord){1, {{MODKEY|ControlMask|ShiftMask, KEY}},     toggletag,      {.ui = 1 << TAG} }),

/* Stack window push and master focus */
#define STACKKEYS(MOD, ACTION)                                       \
    &((Keychord){1, {{MOD, XK_j}}, ACTION##stack, {.i = INC(+1)} }), \
    &((Keychord){1, {{MOD, XK_k}}, ACTION##stack, {.i = INC(-1)} }), \
    &((Keychord){1, {{MOD, XK_v}}, ACTION##stack, {.i = 0}}),

/*
 *  &((Keychord){1, {{MOD, XK_grave}}, ACTION##stack, {   .i = PREVSEL  }  }, \
 *  &((Keychord){1, {{MOD, XK_a}},     ACTION##stack, {   .i = 1        }  }, \
 *  &((Keychord){1, {{MOD, XK_z}},     ACTION##stack, {   .i = 2        }  }, \
 *  &((Keychord){1, {{MOD, XK_x}},     ACTION##stack, {   .i = -1       }  },
 */

/* Helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char *[]) { "/bin/sh", "-c", cmd, NULL } }

/* Declared Commands */
static const char *termcmd[] = { TERMINAL, NULL };

/* Xresources preferences to load at startup */
ResourcePref resources[] = {
    { "color0",           STRING,     &normbordercolor },
    { "color8",           STRING,     &selbordercolor },
    { "color0",           STRING,     &normbgcolor },
    { "color4",           STRING,     &normfgcolor },
    { "color0",           STRING,     &selfgcolor },
    { "color4",           STRING,     &selbgcolor },
    { "borderpx",         INTEGER,    &borderpx },
    { "snap",             INTEGER,    &snap },
    { "showbar",          INTEGER,    &showbar },
    { "topbar",           INTEGER,    &topbar },
    { "nmaster",          INTEGER,    &nmaster },
    { "resizehints",      INTEGER,    &resizehints },
    { "mfact",            FLOAT,      &mfact },
    { "gappih",           INTEGER,    &gappih },
    { "gappiv",           INTEGER,    &gappiv },
    { "gappoh",           INTEGER,    &gappoh },
    { "gappov",           INTEGER,    &gappov },
    { "swallowfloating",  INTEGER,    &swallowfloating },
    { "smartgaps",        INTEGER,    &smartgaps },
};

#include "shiftview.c"
#include <X11/XF86keysym.h>

static Keychord *keychords[] = {
    /* Stack --> [Super|Super+Shift] & Tags --> [1-9] workspaces [0] groups all windows from all workspaces */
    STACKKEYS(MODKEY, focus) STACKKEYS(MODKEY | ShiftMask, push)
    TAGKEYS(XK_1, 0) TAGKEYS(XK_2, 1) TAGKEYS(XK_3, 2)
    TAGKEYS(XK_4, 3) TAGKEYS(XK_5, 4) TAGKEYS(XK_6, 5)
    TAGKEYS(XK_7, 6) TAGKEYS(XK_8, 7) TAGKEYS(XK_9, 8)

    /* Keychord      modifier combos                    key               function         argument */
    &((Keychord){1, {{MODKEY,                           XK_0}},           view,          {.ui = ~0}}),
    &((Keychord){1, {{MODKEY | ShiftMask,               XK_0}},           tag,           {.ui = ~0}}),

    &((Keychord){1, {{MODKEY,                           XK_grave}},       togglescratch, {.ui = 0}}),
    &((Keychord){1, {{Mod1Mask,                     XK_backslash}},       togglescratch, {.ui = 0}}),
    &((Keychord){1, {{MODKEY|ShiftMask|ControlMask,         XK_q}},       quit,                {0}}),
    &((Keychord){1, {{MODKEY,                             XK_Tab}},       view,                {0}}),
    &((Keychord){1, {{Mod1Mask,                           XK_Tab}},       view,                {0}}),
    &((Keychord){1, {{MODKEY,                               XK_q}},       killclient,          {0}}),

    &((Keychord){0, {{MODKEY|ShiftMask,                 XK_Escape}},      spawn,         {.v = termcmd}}),
    &((Keychord){1, {{MODKEY|ShiftMask,                 XK_q}},           spawn,         {.v = (const char *[]){"wmreup", NULL}}}),
    &((Keychord){1, {{MODKEY|ShiftMask,                 XK_grave}},       spawn,         {.v = (const char *[]){"dmenuunicode", NULL}}}),
    &((Keychord){1, {{MODKEY,                           XK_BackSpace}},   spawn,         {.v = (const char *[]){"sysact",    NULL}}}),
    &((Keychord){1, {{MODKEY | ShiftMask,               XK_BackSpace}},   spawn,         {.v = (const char *[]){"sysact",    NULL}}}),
    &((Keychord){1, {{MODKEY|ControlMask,               XK_space}},       spawn,         {.v = (const char *[]){"piper-tgpt", NULL}}}),
    &((Keychord){1, {{MODKEY,                           XK_space}},       spawn,         {.v = (const char *[]){"kb-toggle", NULL}}}),
    &((Keychord){1, {{MODKEY | ShiftMask,               XK_w}},           spawn,         {.v = (const char *[]){TERMINAL, "-e", "sudo", "nmtui", NULL}}}),
    &((Keychord){1, {{MODKEY,                           XK_r}},           spawn,         {.v = (const char *[]){TERMINAL, "-e", "lfub", NULL}}}),
    &((Keychord){1, {{MODKEY | ShiftMask,               XK_r}},           spawn,         {.v = (const char *[]){TERMINAL, "-e", "htop", NULL}}}),

    /* WirePlumber Volume Controls */
    &((Keychord){1, {{MODKEY,                           XK_minus}},       spawn,         SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 5%-; kill -44 $(pidof dwmblocks)")}),
    &((Keychord){1, {{MODKEY | ShiftMask,               XK_minus}},       spawn,         SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 15%-; kill -44 $(pidof dwmblocks)")}),
    &((Keychord){1, {{MODKEY,                           XK_equal}},       spawn,         SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 5%+; kill -44 $(pidof dwmblocks)")}),
    &((Keychord){1, {{MODKEY | ShiftMask,               XK_equal}},       spawn,         SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 15%+; kill -44 $(pidof dwmblocks)")}),

    /* Contacts & Mail Apps */
    &((Keychord){2, {{MODKEY, XK_e},{0, XK_e}},                           spawn,         SHCMD(TERMINAL " -e neomutt ; pkill -RTMIN+12 dwmblocks; rmdir ~/.abook 2>/dev/null")}),
    &((Keychord){2, {{MODKEY, XK_e},{ShiftMask, XK_e}},                   spawn,         SHCMD(TERMINAL " -e abook -C ~/.config/abook/abookrc --datafile ~/.config/abook/addressbook")}),

    /* <Super> + <[o]|[O]> Decrement/Increment focused window master factor  */
    &((Keychord){1, {{MODKEY,             XK_o}},      incnmaster,    {.i = +1}}),
    &((Keychord){1, {{MODKEY|ShiftMask,   XK_o}},      incnmaster,    {.i = -1}}),

    /* Layouts Controls  <[Super|Super+Shift|Super+Ctrl]> + <[t|y|u|i|o]>  */
    &((Keychord){1, {{MODKEY,             XK_t}},      setlayout,     {.v = &layouts[0]}}),  /* tile */
    &((Keychord){1, {{MODKEY|ShiftMask,   XK_t}},      setlayout,     {.v = &layouts[1]}}),  /* bstack */
    &((Keychord){1, {{MODKEY,             XK_y}},      setlayout,     {.v = &layouts[2]}}),  /* spiral */
    &((Keychord){1, {{MODKEY|ShiftMask,   XK_y}},      setlayout,     {.v = &layouts[3]}}),  /* dwindle */
    &((Keychord){1, {{MODKEY,             XK_u}},      setlayout,     {.v = &layouts[4]}}),  /* deck */
    &((Keychord){1, {{MODKEY|ShiftMask,   XK_u}},      setlayout,     {.v = &layouts[5]}}),  /* monocle */
    &((Keychord){1, {{MODKEY,             XK_i}},      setlayout,     {.v = &layouts[6]}}),  /* centeredmaster */
    &((Keychord){1, {{MODKEY|ControlMask, XK_i}},      setlayout,     {.v = &layouts[7]}}),  /* centeredfloatingmaster */
    &((Keychord){1, {{MODKEY|ControlMask, XK_t}},      setlayout,     {.v = &layouts[8]}}),  /* bstackhoriz */
    &((Keychord){1, {{MODKEY|ControlMask, XK_y}},      setlayout,     {.v = &layouts[9]}}),  /* grid */
    &((Keychord){1, {{MODKEY|ControlMask, XK_u}},      setlayout,     {.v = &layouts[10]}}), /* nrowgrid */
    &((Keychord){1, {{MODKEY|ControlMask, XK_i}},      setlayout,     {.v = &layouts[11]}}), /* horizgrid */
    &((Keychord){1, {{MODKEY|ControlMask, XK_o}},      setlayout,     {.v = &layouts[12]}}), /* gaplessgrid */
    &((Keychord){1, {{MODKEY|ShiftMask,   XK_f}},      setlayout,     {.v = &layouts[13]}}), /* floating behaviour */

    &((Keychord){2, {{MODKEY, XK_backslash}, {0, XK_backslash}},           spawn,  {.v = (const char *[]){"bmpaste", NULL}}}),
    &((Keychord){2, {{MODKEY|ShiftMask, XK_backslash}, {0, XK_backslash}}, spawn,  {.v = (const char *[]){"bmcommand", NULL}}}),
    &((Keychord){1, {{MODKEY|ShiftMask, XK_Down}},                         spawn,  {.v = (const char *[]){"unswal", "1", NULL}}}),
    &((Keychord){1, {{MODKEY|ControlMask, XK_w}},                          spawn,  {.v = (const char *[]){"camcast", NULL}}}),
    &((Keychord){1, {{MODKEY,             XK_d}},                          spawn,  {.v = (const char *[]){"dmenu_run", NULL}}}),
    &((Keychord){1, {{MODKEY|ShiftMask,   XK_d}},                          spawn,  {.v = (const char *[]){"passmenu", NULL}}}),
    &((Keychord){1, {{MODKEY|ControlMask, XK_p}},                          spawn,  {.v = (const char *[]){"scrncast", NULL}}}),
    &((Keychord){1, {{Mod1Mask|ShiftMask, XK_t}},                          spawn,  {.v = (const char *[]){"screenconf", NULL}}}),
    &((Keychord){2, {{MODKEY, XK_backslash}, {0, XK_v}},                   spawn,  {.v = (const char *[]){"vscreen", NULL}}}),
    &((Keychord){1, {{MODKEY|ShiftMask|ControlMask, XK_p}},                spawn,  {.v = (const char *[]){"dmenurecord", "kill", NULL}}}),

    /* toggle fullscreen toggles bar too */
    &((Keychord){1, {{MODKEY|ControlMask, XK_space}},          zoom,           {0}}),
    &((Keychord){1, {{MODKEY,                 XK_f}},          togglefullscr,  {0}}),
    &((Keychord){1, {{MODKEY,                 XK_f}},          togglebar,      {0}}),
    &((Keychord){1, {{MODKEY,                 XK_b}},          togglebar,      {0}}),

    /* more toggles */
    &((Keychord){1, {{MODKEY,               XK_s}},            togglesticky,   {0}}),
    &((Keychord){1, {{MODKEY,               XK_a}},            togglegaps,     {0}}),
    &((Keychord){1, {{MODKEY | ShiftMask,   XK_a}},            defaultgaps,    {0}}),
    &((Keychord){1, {{MODKEY | ShiftMask,   XK_space}},        togglefloating, {0}}),

    &((Keychord){1, {{MODKEY | ShiftMask,   XK_Return}},       togglescratch,  {.ui = 0}}),
    &((Keychord){1, {{MODKEY,               XK_apostrophe}},   togglescratch,  {.ui = 1}}),
    &((Keychord){1, {{Mod1Mask | ShiftMask, XK_Return}},       togglescratch,  {.ui = 2}}),

    &((Keychord){1, {{MODKEY, XK_Return}},                     spawn,          {.v = termcmd}}),

    /* mfacts resizing */
    &((Keychord){1, {{MODKEY, XK_h}},                          setmfact,       {.f = -0.05}}),
    &((Keychord){1, {{MODKEY, XK_l}},                          setmfact,       {.f = +0.05}}),

    /* cfacts resizing */
    &((Keychord){1, {{MODKEY|ShiftMask, XK_h}},                setcfact,       {.f = +0.05}}),
    &((Keychord){1, {{MODKEY|ShiftMask, XK_l}},                setcfact,       {.f = -0.05}}),
    &((Keychord){1, {{MODKEY|ShiftMask, XK_o}},                setcfact,       {.f = 0.00}}),

    /* Gap resizing */
    &((Keychord){1, {{MODKEY,               XK_z}},            incrgaps,       {.i = -1}}),
    &((Keychord){1, {{MODKEY,               XK_x}},            incrgaps,       {.i = +1}}),

    /* Workspaces shifting */
    &((Keychord){1, {{MODKEY,               XK_g}},            shiftview,      {.i = -1}}),
    &((Keychord){1, {{MODKEY | ShiftMask,   XK_g}},            shifttag,       {.i = -1}}),
    &((Keychord){1, {{MODKEY,               XK_semicolon}},    shiftview,      {.i = 1}}),
    &((Keychord){1, {{MODKEY | ShiftMask,   XK_semicolon}},    shifttag,       {.i = 1}}),

    /* Focus and unfocused focused window transparency kb control
     * also bound to <[super]|[super+shift]> + <MouseScroll [Up]|[Down]> */
    &((Keychord){1, {{MODKEY|ControlMask, XK_a}},    changefocusopacity,     {.f = +0.025}}),
    &((Keychord){1, {{MODKEY|ControlMask, XK_s}},    changefocusopacity,     {.f = -0.025}}),
    &((Keychord){1, {{MODKEY|ControlMask, XK_z}},    changeunfocusopacity,   {.f = +0.025}}),
    &((Keychord){1, {{MODKEY|ControlMask, XK_x}},    changeunfocusopacity,   {.f = -0.025}}),

    /* Web browsers:    <Super+w>  +  <KEY>                    launches       browser functions  */
    &((Keychord){2, {{MODKEY, XK_w}, {0, XK_w}},               spawn,         {.v = (const char *[]){BROWSER, NULL}}}),
    &((Keychord){2, {{MODKEY, XK_w}, {0, XK_s}},               spawn,         {.v = (const char *[]){"dsurfraw", "-d", NULL}}}),
    &((Keychord){2, {{MODKEY, XK_w}, {0, XK_y}},               spawn,         {.v = (const char *[]){"dsurfraw", "-d", "-e", "youtube", NULL}}}),
    &((Keychord){2, {{MODKEY, XK_w}, {0, XK_p}},               spawn,         SHCMD("surfraw \"$(xclip -selection primary -o)\"")}),
    &((Keychord){2, {{MODKEY, XK_w}, {0, XK_a}},               spawn,         SHCMD("dsurfraw -d -e archwiki")}),
    &((Keychord){2, {{MODKEY, XK_w}, {0, XK_r}},               spawn,         SHCMD("dsurfraw -d -e reddit")}),
    &((Keychord){2, {{MODKEY, XK_w}, {0, XK_f}},               spawn,         SHCMD("dsurfraw -d -e github")}),
    &((Keychord){2, {{MODKEY, XK_w}, {0, XK_i}},               spawn,         SHCMD("dsurfraw -d -e imdb")}),
    &((Keychord){2, {{MODKEY, XK_w}, {0, XK_d}},               spawn,         SHCMD("dsurfraw -d -e discog")}),
    &((Keychord){2, {{MODKEY, XK_w}, {0, XK_g}},               spawn,         SHCMD("dsurfraw -d -e google chromium")}),
    &((Keychord){2, {{MODKEY, XK_w}, {ShiftMask, XK_g}},       spawn,         SHCMD("dsurfraw -d -e google firefox")}),
    &((Keychord){2, {{MODKEY, XK_w}, {0, XK_t}},               spawn,         SHCMD("dsurfraw -d -e duckduckgo torbrowser-launcher")}),

    /* &((Keychord){2, {{MODKEY, XK_w}, {ShiftMask, XK_d}},       spawn,         SHCMD("dsurfraw -d -e duckduckgo librewolf")}), */
    /* &((Keychord){2, {{MODKEY, XK_w}, {Mod1Mask, XK_g}},        spawn,         SHCMD("dsurfraw -d -e google luakit")}), */
    /* &((Keychord){2, {{MODKEY, XK_w}, {0, XK_l}},               spawn,         SHCMD("dsurfraw -d -e archwiki luakit")}), */
    /* &((Keychord){2, {{MODKEY, XK_w}, {0, XK_h}},               spawn,         SHCMD("dsurfraw -d -e wikipedia luakit")}), */

    /* Web browsers:        <Alt+b>  +    <KEY>                launches       select browsers */
    &((Keychord){2, {{Mod1Mask, XK_b}, {0, XK_s}},             spawn,         SHCMD("dsurfraw -d")}),  /* dmenu searchbar surfraw wrapper */
    &((Keychord){2, {{Mod1Mask, XK_b}, {0, XK_q}},             spawn,         SHCMD("qutepriv")}),
    &((Keychord){2, {{Mod1Mask, XK_b}, {0, XK_f}},             spawn,         SHCMD("firefox")}),
    &((Keychord){2, {{Mod1Mask, XK_b}, {0, XK_c}},             spawn,         SHCMD("chromium")}),
    &((Keychord){2, {{Mod1Mask, XK_b}, {0, XK_b}},             spawn,         SHCMD("brave")}),
    &((Keychord){2, {{Mod1Mask, XK_b}, {0, XK_l}},             spawn,         SHCMD("librewolf")}),
    &((Keychord){2, {{Mod1Mask, XK_b}, {0, XK_p}},             spawn,         SHCMD("dwmpatches")}),
    &((Keychord){2, {{Mod1Mask, XK_a}, {0, XK_r}},             spawn,         SHCMD("rssadd \"$(xclip -sel clipboard -o)\" || rssadd \"$(xclip -sel primary -o)\"")}),

    &((Keychord){2, {{MODKEY, XK_w}, {0, XK_q}},               spawn,         SHCMD("qutepriv")}),
    &((Keychord){2, {{MODKEY, XK_w}, {0, XK_f}},               spawn,         SHCMD("firefox")}),
    &((Keychord){2, {{MODKEY, XK_w}, {0, XK_c}},               spawn,         SHCMD("chromium")}),
    &((Keychord){2, {{MODKEY, XK_w}, {0, XK_b}},               spawn,         SHCMD("brave")}),

    /* Media controls */
    &((Keychord){1, {{MODKEY|ControlMask,        XK_m}},        spawn,     SHCMD("wpctl set-mute @DEFAULT_AUDIO_SINK@ toggle; kill -44 $(pidof dwmblocks)")}),
    &((Keychord){2, {{MODKEY, XK_m},         {0, XK_m}},        spawn,     {.v = (const char *[]){TERMINAL, "-e", "ncmpcpp", NULL}}}),
    &((Keychord){1, {{ControlMask,           XK_comma}},        spawn,     {.v = (const char *[]){"mpc", "prev", NULL}}}),
    &((Keychord){1, {{ControlMask|ShiftMask, XK_comma}},        spawn,     {.v = (const char *[]){"mpc", "seek", "0%", NULL}}}),
    &((Keychord){1, {{ControlMask,           XK_period}},       spawn,     {.v = (const char *[]){"mpc", "next", NULL}}}),
    &((Keychord){1, {{ControlMask|ShiftMask, XK_period}},       spawn,     {.v = (const char *[]){"mpc", "repeat", NULL}}}),
    &((Keychord){1, {{MODKEY,                XK_p}},            spawn,     {.v = (const char *[]){"mpc", "toggle", NULL}}}),
    &((Keychord){1, {{MODKEY,                XK_bracketleft}},  spawn,     {.v = (const char *[]){"mpc", "seek", "-10", NULL}}}),
    &((Keychord){1, {{MODKEY | ShiftMask,    XK_bracketleft}},  spawn,     {.v = (const char *[]){"mpc", "seek", "-60", NULL}}}),
    &((Keychord){1, {{MODKEY,                XK_bracketright}}, spawn,     {.v = (const char *[]){"mpc", "seek", "+10", NULL}}}),
    &((Keychord){1, {{MODKEY | ShiftMask,    XK_bracketright}}, spawn,     {.v = (const char *[]){"mpc", "seek", "+60", NULL}}}),

    /* Super + [left|right] to switch monitor focus; Super + Shift + [left|right] to send windows to other monitor */
    &((Keychord){1, {{MODKEY,               XK_Left}},         focusmon,   {.i = +1}}),
    &((Keychord){1, {{MODKEY,               XK_Right}},        focusmon,   {.i = -1}}),
    &((Keychord){1, {{MODKEY | ShiftMask,   XK_Left}},         tagmon,     {.i = +1}}),
    &((Keychord){1, {{MODKEY | ShiftMask,   XK_Right}},        tagmon,     {.i = -1}}),

    /* <Super> + [<] | [>]  directional monitor switch altbinds  */
    &((Keychord){1, {{MODKEY,               XK_period}},       focusmon,   {.i = -1}}),
    &((Keychord){1, {{MODKEY,               XK_comma}},        focusmon,   {.i = +1}}),
    &((Keychord){1, {{MODKEY | ShiftMask,   XK_period}},       tagmon,     {.i = -1}}),
    &((Keychord){1, {{MODKEY | ShiftMask,   XK_comma}},        tagmon,     {.i = +1}}),

    /* <[Alt]|[Alt+Shift]> + <[u]|[i]> monitor switch|shift home row altbinds */
    &((Keychord){1, {{Mod1Mask,             XK_i}},            focusmon,   {.i = -1}}),
    &((Keychord){1, {{Mod1Mask,             XK_u}},            focusmon,   {.i = +1}}),
    &((Keychord){1, {{Mod1Mask | ShiftMask, XK_i}},            tagmon,     {.i = -1}}),
    &((Keychord){1, {{Mod1Mask | ShiftMask, XK_u}},            tagmon,     {.i = +1}}),

    /* Moving windows up and down the stack */
    &((Keychord){1, {{MODKEY,               XK_Page_Up}},      shiftview,  {.i = -1}}),
    &((Keychord){1, {{MODKEY | ShiftMask,   XK_Page_Up}},      shifttag,   {.i = -1}}),
    &((Keychord){1, {{MODKEY,               XK_Page_Down}},    shiftview,  {.i = +1}}),
    &((Keychord){1, {{MODKEY | ShiftMask,   XK_Page_Down}},    shifttag,   {.i = +1}}),

    /* Super + Control + [left|right|up|down] to rotate monitor view */
    &((Keychord){1, {{ MODKEY | ControlMask,  XK_Right}},       spawn,     SHCMD("xrandr --output eDP --rotate left && walfeh -reset")}),
    &((Keychord){1, {{ MODKEY | ControlMask,  XK_Left}},        spawn,     SHCMD("xrandr --output eDP --rotate right && walfeh -reset")}),
    &((Keychord){1, {{ MODKEY | ControlMask,  XK_Up}},          spawn,     SHCMD("xrandr --output eDP --rotate inverted && walfeh -reset")}),
    &((Keychord){1, {{ MODKEY | ControlMask,  XK_Down}},        spawn,     SHCMD("xrandr --output eDP --rotate normal && walfeh -reset")}),

    /* Délégation de l'avaleur à l'avalé des avalés */
    &((Keychord){1, {{MODKEY|ShiftMask,   XK_apostrophe}},      swalstopsel,     {0}}),
    &((Keychord){2, {{MODKEY, XK_Left},     {0, XK_Left}},      swalstopsel,     {0}}),
    &((Keychord){2, {{MODKEY, XK_Right},   {0, XK_Right}},      swalstopsel,     {0}}),

    &((Keychord){2, {{MODKEY, XK_Up},         {0, XK_Up}},      spawn,           {.v = (const char *[]){"unswal", "1", NULL}}}),
    &((Keychord){2, {{MODKEY, XK_Down},     {0, XK_Down}},      spawn,           {.v = (const char *[]){"unswal", "1", NULL}}}),

    /* Alt + [h|j|k|l] dynamic directional swallows */
    /* &((Keychord){2, {{Mod1Mask, XK_h}, {0, XK_h}},         spawn,    {.v = (const char *[]){"winLeft", NULL}}}), */
    /* &((Keychord){2, {{Mod1Mask, XK_j}, {0, XK_j}},         spawn,    {.v = (const char *[]){"winUnder", NULL}}}), */
    /* &((Keychord){2, {{Mod1Mask, XK_k}, {0, XK_k}},         spawn,    {.v = (const char *[]){"winAbove", NULL}}}), */
    /* &((Keychord){2, {{Mod1Mask, XK_l}, {0, XK_l}},         spawn,    {.v = (const char *[]){"winRight", NULL}}}), */
    /* &((Keychord){1, {{Mod1Mask, XK_Left}},                 spawn,    {.v = (const char *[]){"winLeft", NULL}}}), */
    /* &((Keychord){1, {{Mod1Mask, XK_Down}},                 spawn,    {.v = (const char *[]){"winUnder", NULL}}}), */
    /* &((Keychord){1, {{Mod1Mask, XK_Up}},                   spawn,    {.v = (const char *[]){"winAbove", NULL}}}), */
    /* &((Keychord){1, {{Mod1Mask, XK_Right}},                spawn,    {.v = (const char *[]){"winRight", NULL}}}), */

    /* Dynamic directional swallows */
    &((Keychord){2, {{Mod1Mask, XK_h}, {0, XK_h}},         spawn,    {.v = (const char *[]){"swallow_left",  NULL}}}),
    &((Keychord){2, {{Mod1Mask, XK_j}, {0, XK_j}},         spawn,    {.v = (const char *[]){"swallow_under", NULL}}}),
    &((Keychord){2, {{Mod1Mask, XK_k}, {0, XK_k}},         spawn,    {.v = (const char *[]){"swallow_above", NULL}}}),
    &((Keychord){2, {{Mod1Mask, XK_l}, {0, XK_l}},         spawn,    {.v = (const char *[]){"swallow_right", NULL}}}),

    &((Keychord){1, {{Mod1Mask, XK_Left}},                 spawn,    {.v = (const char *[]){"swallow_left",  NULL}}}),
    &((Keychord){1, {{Mod1Mask, XK_Down}},                 spawn,    {.v = (const char *[]){"swallow_under", NULL}}}),
    &((Keychord){1, {{Mod1Mask, XK_Up}},                   spawn,    {.v = (const char *[]){"swallow_above", NULL}}}),
    &((Keychord){1, {{Mod1Mask, XK_Right}},                spawn,    {.v = (const char *[]){"swallow_right", NULL}}}),

    &((Keychord){2, {{MODKEY, XK_n}, {0, XK_n}},           spawn,    SHCMD(TERMINAL " -e newsboat; pkill -RTMIN+6 dwmblocks")}),
    &((Keychord){2, {{MODKEY, XK_c}, {0, XK_c}},           spawn,    SHCMD(TERMINAL " -e calcurse")}),

    &((Keychord){1, {{MODKEY | ShiftMask, XK_b}},          spawn,    {.v = (const char *[]){ "bookmarkthis", NULL}}}),
    &((Keychord){1, {{MODKEY | ShiftMask, XK_s}},          spawn,    SHCMD("xdotool type $(grep -v '^#' ~/Documents/Notes/snippets | dmenu -i -l 50 |cut -d' ' -f1)")}),
    &((Keychord){1, {{MODKEY | ShiftMask, XK_Insert}},     spawn,    SHCMD("xdotool type --delay 50 \"$(grep -v '^#' ~/Documents/Notes/bmcmd | dmenu -i -l 50 | cut -d' ' -f2-)\"")}),

    /* Super + [F1-F12] scripts and utilities */
    &((Keychord){1, {{MODKEY,               XK_F1}},       spawn,    SHCMD("playmuse")}),
    &((Keychord){2, {{MODKEY,XK_m}, {MODKEY,XK_m}},        spawn,    SHCMD(TERMINAL " -e ncmpcpp")}),
    &((Keychord){1, {{MODKEY|ShiftMask,     XK_F1}},       spawn,    SHCMD("man -k . | dmenu -l 30 | awk '{print $1}' | xargs -r man -Tpdf | zathura -")}),
    &((Keychord){1, {{MODKEY,               XK_F2}},       spawn,    {.v = (const char *[]){"readit", "-c", NULL}}}),
    &((Keychord){1, {{MODKEY|ShiftMask,     XK_F2}},       spawn,    {.v = (const char *[]){"tutorialvids", NULL}}}),
    &((Keychord){1, {{MODKEY,               XK_F3}},       spawn,    {.v = (const char *[]){"displayselect", NULL}}}),
    &((Keychord){1, {{MODKEY,               XK_F4}},       spawn,    SHCMD(TERMINAL " -e pulsemixer; kill -44 $(pidof dwmblocks)")}),
    &((Keychord){1, {{MODKEY,               XK_F5}},       xrdb,     {.v = NULL}}),
    &((Keychord){1, {{MODKEY,               XK_F6}},       spawn,    {.v = (const char *[]){"torwrap", NULL}}}),
    &((Keychord){1, {{MODKEY,               XK_F7}},       spawn,    {.v = (const char *[]){"td-toggle", NULL}}}),
    /* &((Keychord){1, {{MODKEY,               XK_F8}},       spawn,    {.v = (const char *[]){"mailsync", NULL}}}), */
    /* &((Keychord){1, {{MODKEY,               XK_F8}},       spawn,    {.v = (const char *[]){"mkwinicon", NULL}}}), */
    &((Keychord){1, {{MODKEY,               XK_F9}},       spawn,    {.v = (const char *[]){"mounter", NULL}}}),
    &((Keychord){1, {{MODKEY,               XK_F10}},      spawn,    {.v = (const char *[]){"unmounter", NULL}}}),
    &((Keychord){1, {{MODKEY,               XK_F11}},      spawn,    {.v = (const char *[]){"mpvcam", NULL}}}),
    &((Keychord){1, {{MODKEY,               XK_F12}},      spawn,    {.v = (const char *[]){"remaps", NULL}}}),

    /* &((Keychord){2, {{ControlMask|MODKEY, XK_p}, {0,XK_p}},   spawn, SHCMD("shotgun -g $(hacksaw) $(date +%Y-%m-%d-%H%M-%S).png")}), */
    /* &((Keychord){1, {{ControlMask|ShiftMask, XK_p}},          spawn, SHCMD("maim pic-full-$(date '+%y%m%d-%H%M-%S').png")}), */
    &((Keychord){1, {{0, XK_Print}},                          spawn, SHCMD("mon_prntscrn")}),
    &((Keychord){1, {{Mod1Mask, XK_Print}},                   spawn, {.v = (const char *[]){"flameshot", "gui", NULL}}}),
    &((Keychord){1, {{ShiftMask, XK_Print}},                  spawn, {.v = (const char *[]){"maimpick", NULL}}}),
    &((Keychord){1, {{MODKEY, XK_Print}},                     spawn, {.v = (const char *[]){"dmenurecord", NULL}}}),
    &((Keychord){1, {{MODKEY|ShiftMask, XK_Print}},           spawn, {.v = (const char *[]){"dmenurecord", "kill", NULL}}}),
    &((Keychord){1, {{MODKEY, XK_Delete}},                    spawn, {.v = (const char *[]){"dmenurecord", "kill", NULL}}}),
    &((Keychord){2, {{Mod1Mask, XK_s}, {0, XK_s}},            spawn, SHCMD("killall screenkey || screenkey -M -s small -M -g 669x1560+1620+0 --opacity 0.6 --bak-mode full --mods-mode emacs")}),
    /* &((Keychord){1, {{MODKEY, XK_space}},                     spawn, SHCMD("win_icons_align")}), */

    /* XF86 media/function keys */
    &((Keychord){1, {{0, XF86XK_AudioMute}},                  spawn, SHCMD("wpctl set-mute @DEFAULT_AUDIO_SINK@ toggle; kill -44 $(pidof dwmblocks)")}),
    &((Keychord){1, {{0, XF86XK_AudioRaiseVolume}},           spawn, SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 0%- && wpctl set-volume @DEFAULT_AUDIO_SINK@ 3%+; kill -44 $(pidof dwmblocks)")}),
    &((Keychord){1, {{0, XF86XK_AudioLowerVolume}},           spawn, SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 0%+ && wpctl set-volume @DEFAULT_AUDIO_SINK@ 3%-; kill -44 $(pidof dwmblocks)")}),
    &((Keychord){1, {{0, XF86XK_AudioPrev}},                  spawn, {.v = (const char *[]){"mpc", "prev", NULL}}}),
    &((Keychord){1, {{0, XF86XK_AudioNext}},                  spawn, {.v = (const char *[]){"mpc", "next", NULL}}}),
    &((Keychord){1, {{0, XF86XK_AudioPause}},                 spawn, {.v = (const char *[]){"mpc", "pause", NULL}}}),
    &((Keychord){1, {{0, XF86XK_AudioPlay}},                  spawn, {.v = (const char *[]){"mpc", "play", NULL}}}),
    &((Keychord){1, {{0, XF86XK_AudioStop}},                  spawn, {.v = (const char *[]){"mpc", "stop", NULL}}}),
    &((Keychord){1, {{0, XF86XK_AudioRewind}},                spawn, {.v = (const char *[]){"mpc", "seek", "-10", NULL}}}),
    &((Keychord){1, {{0, XF86XK_AudioForward}},               spawn, {.v = (const char *[]){"mpc", "seek", "+10", NULL}}}),
    &((Keychord){1, {{0, XF86XK_AudioMedia}},                 spawn, {.v = (const char *[]){TERMINAL, "-e", "ncmpcpp", NULL}}}),
    &((Keychord){1, {{0, XF86XK_AudioMicMute}},               spawn, SHCMD("pactl set-source-mute @DEFAULT_SOURCE@ toggle")}),
    &((Keychord){1, {{0, XF86XK_Calculator}},                 spawn, {.v = (const char *[]){TERMINAL, "-e", "bc", "-l", NULL}}}),
    &((Keychord){1, {{0, XF86XK_Sleep}},                      spawn, {.v = (const char *[]){"sudo", "-A", "zzz", NULL}}}),
    &((Keychord){1, {{0, XF86XK_WWW}},                        spawn, {.v = (const char *[]){BROWSER, NULL}}}),
    &((Keychord){1, {{0, XF86XK_DOS}},                        spawn, {.v = termcmd}}),
    &((Keychord){1, {{0, XF86XK_ScreenSaver}},                spawn, SHCMD("slock & xset dpms force off; mpc pause; pauseallmpv")}),
    &((Keychord){1, {{0, XF86XK_TaskPane}},                   spawn, {.v = (const char *[]){TERMINAL, "-e", "htop", NULL}}}),
    &((Keychord){1, {{0, XF86XK_Mail}},                       spawn, SHCMD(TERMINAL " -e neomutt ; pkill -RTMIN+12 dwmblocks")}),
    &((Keychord){1, {{0, XF86XK_MyComputer}},                 spawn, {.v = (const char *[]){TERMINAL, "-e", "lfub", "/", NULL}}}),
    &((Keychord){1, {{0, XF86XK_Launch1}},                    spawn, {.v = (const char *[]){"xset", "dpms", "force", "off", NULL}}}),
    &((Keychord){1, {{0, XF86XK_TouchpadToggle}},             spawn, SHCMD("toggle_touchpad")}),
    &((Keychord){1, {{0, XF86XK_TouchpadOff}},                spawn, {.v = (const char *[]){"synclient", "TouchpadOff=1", NULL}}}),
    &((Keychord){1, {{0, XF86XK_TouchpadOn}},                 spawn, {.v = (const char *[]){"synclient", "TouchpadOff=0", NULL}}}),
    &((Keychord){1, {{0, XF86XK_MonBrightnessUp}},            spawn, SHCMD("bright 12")}),
    &((Keychord){1, {{0, XF86XK_MonBrightnessDown}},          spawn, SHCMD("bright -12")}),

    /*                 Shift + [F1-F12]                          for handy scripts and utilities */
    &((Keychord){1, {{ShiftMask, XK_F1}},                 spawn, {.v = (const char *[]){"linkhandler", NULL}}}),
    &((Keychord){1, {{ShiftMask, XK_F2}},                 spawn, {.v = (const char *[]){"killall", "pacat", NULL}}}),
    &((Keychord){1, {{ShiftMask, XK_F3}},                 spawn, {.v = (const char *[]){"readit", "-c", NULL}}}),
    &((Keychord){1, {{ShiftMask, XK_F4}},                 spawn, {.v = (const char *[]){"walfeh", "-backward", NULL}}}),
    &((Keychord){1, {{ShiftMask, XK_F5}},                 spawn, {.v = (const char *[]){"walfeh", "-toggle", NULL}}}),
    &((Keychord){1, {{ShiftMask, XK_F6}},                 spawn, {.v = (const char *[]){"walfeh" , "-forward", NULL}}}),
    &((Keychord){1, {{ShiftMask, XK_F7}},                 spawn, {.v = (const char *[]){"toggleblur", NULL}}}),
    &((Keychord){1, {{ShiftMask, XK_F8}},                 spawn, {.v = (const char *[]){"yankmon", NULL}}}),
    &((Keychord){1, {{ShiftMask, XK_F9}},                 spawn, {.v = (const char *[]){"sd", NULL}}}),
    &((Keychord){1, {{ShiftMask, XK_F10}},                spawn, {.v = (const char *[]){"redunst", NULL}}}),
    &((Keychord){1, {{ShiftMask, XK_F11}},                spawn, {.v = (const char *[]){"yankzp", NULL}}}),
    &((Keychord){1, {{ShiftMask, XK_F12}},                spawn, {.v = (const char *[]){"remaps", NULL}}}),

    /* &((Keychord){1, {{0, XK_F1}},                         spawn, {.v = (const char *[]){"linkhandler", NULL}}}), */
    /* &((Keychord){1, {{0, XK_F2}},                         spawn, {.v = (const char *[]){"pkill", "piper-tts", NULL}}}), */
    /* &((Keychord){1, {{0, XK_F3}},                         spawn, {.v = (const char *[]){"mpctl", NULL}}}), */
    &((Keychord){1, {{0, XK_F4}},                         spawn, {.v = (const char *[]){"mpc", "prev", NULL}}}),
    &((Keychord){1, {{0, XK_F5}},                         spawn, {.v = (const char *[]){"mpctl", NULL}}}),
    &((Keychord){1, {{0, XK_F6}},                         spawn, {.v = (const char *[]){"mpc", "next", NULL}}}),
    /* &((Keychord){2, {{0, XK_F7}},                         spawn, {.v = (const char *[]){"playmuse", NULL}}}), */
    /* &((Keychord){2, {{0, XK_F8}},                         spawn, {.v = (const char *[]){"mpc-voice-search", NULL}}}), */
    &((Keychord){1, {{0, XK_F9}},                         spawn, {.v = (const char *[]){"touchpad_toggle", NULL}}}),
    &((Keychord){1, {{0, XK_F10}},                        spawn, {.v = (const char *[]){"unswal", "1", NULL}}}),
    /* &((Keychord){1, {{0, XK_F11}},                        spawn, {.v = (const char *[]){"yankzp", NULL}}}), */
    &((Keychord){1, {{0, XK_F12}},                        spawn, {.v = (const char *[]){"redunst", NULL}}}),

    &((Keychord){2, {{Mod1Mask, XK_F7}, {0, XK_F7}},      spawn, {.v = (const char *[]){"playmuse", NULL}}}),
    &((Keychord){2, {{Mod1Mask, XK_F8}, {0, XK_F8}},      spawn, {.v = (const char *[]){"mpc-voice-search", NULL}}}),

    /*                 Ctrl + [F1-F12]                    for scripts and utilities */
    &((Keychord){1, {{ControlMask, XK_F1}},               spawn,  {.v = (const char *[]){"cliplink", NULL}}}),
    &((Keychord){1, {{ControlMask, XK_F2}},               spawn,  {.v = (const char *[]){"primarylink", NULL}}}),
    &((Keychord){1, {{ControlMask, XK_F3}},               spawn,  {.v = (const char *[]){"mpvq", "play", NULL}}}),
    &((Keychord){1, {{ControlMask, XK_F4}},               spawn,  {.v = (const char *[]){"mpvq", "dnd", NULL}}}),
    &((Keychord){1, {{ControlMask, XK_F5}},               spawn,  {.v = (const char *[]){"mpv_ipc", NULL}}}),
    &((Keychord){1, {{ControlMask, XK_F6}},               spawn,  {.v = (const char *[]){"mpvq", "download", NULL}}}),
    &((Keychord){1, {{ControlMask, XK_F7}},               togglescratch,  {.ui = 3}}),
    &((Keychord){1, {{ControlMask, XK_F8}},               spawn,  {.v = (const char *[]){"stexec", "mpvqdl", NULL}}}),
    &((Keychord){1, {{ControlMask, XK_F9}},               spawn,  {.v = (const char *[]){"mpvplay", NULL}}}),
    &((Keychord){1, {{ControlMask, XK_F10}},              togglescratch,  {.ui = 4}}),
    &((Keychord){1, {{ControlMask, XK_F11}},              spawn,  {.v = (const char *[]){"vcn","DisplayPort-2","6", NULL}}}),
    &((Keychord){1, {{ControlMask, XK_F12}},              spawn,  {.v = (const char *[]){"xkill", NULL}}}),
    /* &((Keychord){1, {{ControlMask, XK_F11}},              spawn,  {.v = (const char *[]){"", "", NULL}}}), */

    &((Keychord){1, {{ControlMask|ShiftMask, XK_e}},      spawn,  {.v = (const char *[]){"emacs", NULL}}}),

    &((Keychord){1, {{ControlMask|ShiftMask, XK_F1}},     spawn,  {.v = (const char *[]){"cliplink", NULL}}}),
    &((Keychord){1, {{ControlMask|ShiftMask, XK_F2}},     spawn,  {.v = (const char *[]){"emacsclient", NULL}}}),
    &((Keychord){1, {{ControlMask|ShiftMask, XK_F3}},     spawn,  {.v = (const char *[]){"mpvqfzf", "play", NULL}}}),
    &((Keychord){1, {{ControlMask|ShiftMask, XK_F4}},     spawn,  {.v = (const char *[]){"mpvq", "dnd", NULL}}}),
    &((Keychord){1, {{ControlMask|ShiftMask, XK_F5}},     spawn,  {.v = (const char *[]){"mpvqls", NULL}}}),
    &((Keychord){1, {{ControlMask|ShiftMask, XK_F6}},     spawn,  {.v = (const char *[]){"mpvq", "next", NULL}}}),
    &((Keychord){1, {{ControlMask|ShiftMask, XK_F7}},     spawn,  {.v = (const char *[]){"vcn", "eDP", "1", NULL}}}),
    &((Keychord){1, {{ControlMask|ShiftMask, XK_F8}},     spawn,  {.v = (const char *[]){"vcn", "DisplayPort-2", "2", NULL}}}),
    &((Keychord){1, {{ControlMask|ShiftMask, XK_F9}},     spawn,  {.v = (const char *[]){"vcn", "eDP", "3", NULL}}}),
    &((Keychord){1, {{ControlMask|ShiftMask, XK_F10}},    spawn,  {.v = (const char *[]){"vcn", "DisplayPort-2", "4", NULL}}}),
    &((Keychord){1, {{ControlMask|ShiftMask, XK_F11}},    spawn,  {.v = (const char *[]){"vcn", "eDP", "5", NULL}}}),
    &((Keychord){1, {{ControlMask|ShiftMask, XK_F12}},    spawn,  {.v = (const char *[]){"vcn", "DisplayPort-2", "6", NULL}}}),

    &((Keychord){2, {{Mod1Mask, XK_w},{0, XK_w}},         spawn, {.v = (const char *[]){"xmouse", NULL}}}),
    &((Keychord){2, {{Mod1Mask, XK_w},{0, XK_h}},         spawn, {.v = (const char *[]){"yankmon", "1", NULL}}}),
    &((Keychord){2, {{Mod1Mask, XK_w},{0, XK_l}},         spawn, {.v = (const char *[]){"linkclip", NULL}}}),
    &((Keychord){2, {{Mod1Mask, XK_w},{0, XK_y}},         spawn, {.v = (const char *[]){"wezterm", "-e", "yazi", "~/Videos/yt", NULL}}}),
    &((Keychord){2, {{Mod1Mask, XK_w},{0, XK_e}},         spawn, {.v = (const char *[]){"sd", NULL}}}),
    &((Keychord){2, {{Mod1Mask, XK_w},{0, XK_b}},         spawn, {.v = (const char *[]){"toggleblur", NULL}}}),
    &((Keychord){2, {{Mod1Mask, XK_w},{0, XK_d}},         spawn, {.v = (const char *[]){"xdrag", NULL}}}),
    &((Keychord){2, {{Mod1Mask, XK_w},{0, XK_t}},         spawn, {.v = (const char *[]){"dndmpv", NULL}}}),
    &((Keychord){2, {{Mod1Mask, XK_grave},{Mod1Mask, XK_grave}},   spawn, {.v = (const char *[]){"mpc-voice-search", NULL}}}),

    /* Single       Ctrl + Keypad [0-9]                          script testenv */
    &((Keychord){1, {{ControlMask, XK_KP_Insert}},        spawn, SHCMD("numpad0")}),
    &((Keychord){1, {{ControlMask, XK_KP_End}},           spawn, SHCMD("numpad1")}),
    &((Keychord){1, {{ControlMask, XK_KP_Down}},          spawn, SHCMD("numpad2")}),
    &((Keychord){1, {{ControlMask, XK_KP_Page_Down}},     spawn, SHCMD("numpad3")}),
    &((Keychord){1, {{ControlMask, XK_KP_Left}},          spawn, SHCMD("numpad4")}),
    &((Keychord){1, {{ControlMask, XK_KP_Begin}},         spawn, SHCMD("numpad5")}),
    &((Keychord){1, {{ControlMask, XK_KP_Right}},         spawn, SHCMD("numpad6")}),
    &((Keychord){1, {{ControlMask, XK_KP_Home}},          spawn, SHCMD("numpad7")}),
    &((Keychord){1, {{ControlMask, XK_KP_Up}},            spawn, SHCMD("numpad8")}),
    &((Keychord){1, {{ControlMask, XK_KP_Page_Up}},       spawn, SHCMD("numpad9")}),

    &((Keychord){2, {{MODKEY,XK_x}, {0, XK_c}},           spawn, SHCMD("xclip -selection primary -o | xclip -selection clipboard")}),
    &((Keychord){2, {{MODKEY,XK_x}, {0, XK_a}},           spawn, SHCMD("xclip -selection clipboard -o | xclip -selection primary")}),
    &((Keychord){2, {{MODKEY,XK_x}, {0, XK_x}},           spawn, SHCMD("xsel --exchange")}),

    /* Tests de manipulation par registres */
    /* &((Keychord){2, {{Mod1Mask,XK_c}, {0, XK_r}},              spawn,          SHCMD("echo \"$(xclip -o)\" >> ~/Notes/clipregisters/r")}), */
    /* &((Keychord){2, {{Mod1Mask,XK_c}, {ControlMask, XK_r}},    spawn,          SHCMD("echo \"\" > ~/Notes/clipregisters/r")}), */
    /* &((Keychord){2, {{Mod1Mask,XK_c}, {0, XK_a}},              spawn,          SHCMD("echo \"$(xclip -o)\" > ~/Notes/clipregisters/a")}), */
    /* &((Keychord){2, {{Mod1Mask,XK_c}, {ControlMask, XK_a}},    spawn,          SHCMD("echo \"\" > ~/Notes/clipregisters/a")}), */
    /* &((Keychord){2, {{Mod1Mask,XK_c}, {0, XK_s}},              spawn,          SHCMD("echo \"$(xclip -o)\" >> ~/Notes/clipregisters/s")}), */
    /* &((Keychord){2, {{Mod1Mask,XK_c}, {ControlMask, XK_s}},    spawn,          SHCMD("echo \"\" > ~/Notes/clipregisters/s")}), */
    /* &((Keychord){2, {{Mod1Mask,XK_c}, {0, XK_d}},              spawn,          SHCMD("echo \"$(xclip -selection secondary -o)\" > ~/Notes/clipregisters/a")}), */

    /* Lecture des registres */
    /* &((Keychord){1, {{MODKEY|ShiftMask|ControlMask, XK_r}},    spawn,          SHCMD("cat ~/Notes/clipregisters/r | tts")}), */
    /* &((Keychord){1, {{MODKEY|ShiftMask|ControlMask, XK_a}},    spawn,          SHCMD("cat ~/Notes/clipregisters/a | tts -m en_US-libritts-high")}), */
    /* &((Keychord){1, {{MODKEY|ShiftMask|ControlMask, XK_s}},    spawn,          SHCMD("cat ~/Notes/clipregisters/s | tts")}), */

    /*  unused gap keybinds  */
    /* { MODKEY|Mod4Mask,              XK_h,      incrgaps,       {.i = +1 } }, */
    /* { MODKEY|Mod4Mask,              XK_l,      incrgaps,       {.i = -1 } }, */
    /* { MODKEY|Mod4Mask|ShiftMask,    XK_h,      incrogaps,      {.i = +1 } }, */
    /* { MODKEY|Mod4Mask|ShiftMask,    XK_l,      incrogaps,      {.i = -1 } }, */
    /* { MODKEY|Mod4Mask|ControlMask,  XK_h,      incrigaps,      {.i = +1 } }, */
    /* { MODKEY|Mod4Mask|ControlMask,  XK_l,      incrigaps,      {.i = -1 } }, */
    /* { MODKEY|Mod4Mask|ShiftMask,    XK_0,      defaultgaps,    {0} }, */
    /* { MODKEY,                       XK_y,      incrihgaps,     {.i = +1 } }, */
    /* { MODKEY,                       XK_o,      incrihgaps,     {.i = -1 } }, */
    /* { MODKEY|ControlMask,           XK_y,      incrivgaps,     {.i = +1 } }, */
    /* { MODKEY|ControlMask,           XK_o,      incrivgaps,     {.i = -1 } }, */
    /* { MODKEY|Mod4Mask,              XK_y,      incrohgaps,     {.i = +1 } }, */
    /* { MODKEY|Mod4Mask,              XK_o,      incrohgaps,     {.i = -1 } }, */
    /* { MODKEY|ShiftMask,             XK_y,      incrovgaps,     {.i = +1 } }, */
    /* { MODKEY|ShiftMask,             XK_o,      incrovgaps,     {.i = -1 } }, */

};

static const Button buttons[] = {
/* button definitions click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
#ifndef __OpenBSD__
    /* click         event mask       button          function                argument */
    { ClkWinTitle,   0,               Button2,        zoom,                   {0}},
    { ClkStatusText, 0,               Button1,        sigdwmblocks,           {.i = 1}},
    { ClkStatusText, 0,               Button2,        sigdwmblocks,           {.i = 2}},
    { ClkStatusText, 0,               Button3,        sigdwmblocks,           {.i = 3}},
    { ClkStatusText, 0,               Button4,        sigdwmblocks,           {.i = 4}},
    { ClkStatusText, 0,               Button5,        sigdwmblocks,           {.i = 5}},
    { ClkStatusText, ShiftMask,       Button1,        sigdwmblocks,           {.i = 6}},
#endif
    { ClkStatusText, ShiftMask,       Button3,        spawn,                  SHCMD(TERMINAL " -e $EDITOR ~/.local/src/dwmblocks/config.h")},
    { ClkClientWin,  MODKEY,          Button1,        movemouse,              {0}},
    { ClkClientWin,  MODKEY,          Button2,        defaultgaps,            {0}},
    { ClkClientWin,  MODKEY,          Button3,        resizemouse,            {0}},
    /* { ClkClientWin, MODKEY,           Button4,        incrgaps,               {.i = +1} }, */
    /* { ClkClientWin, MODKEY,           Button5,        incrgaps,               {.i = -1} }, */
    { ClkClientWin, MODKEY,           Button4,        changefocusopacity,     {.f = +0.025}},
    { ClkClientWin, MODKEY,           Button5,        changefocusopacity,     {.f = -0.025}},
    { ClkClientWin, MODKEY|ShiftMask, Button4,        changeunfocusopacity,   {.f = +0.025}},
    { ClkClientWin, MODKEY|ShiftMask, Button5,        changeunfocusopacity,   {.f = -0.025}},
    { ClkClientWin, MODKEY|ShiftMask, Button1,        swalmouse,              {0}},
    /* { ClkClientWin, ControlMask,      Button1,        spawn,                  SHCMD("win_icons_align")}, */
    { ClkTagBar,    0,                Button1,        view,                   {0}},
    { ClkTagBar,    0,                Button3,        toggleview,             {0}},
    { ClkTagBar,    MODKEY,           Button1,        tag,                    {0}},
    { ClkTagBar,    MODKEY,           Button3,        toggletag,              {0}},
    { ClkTagBar,    0,                Button4,        shiftview,              {.i = -1}},
    { ClkTagBar,    0,                Button5,        shiftview,              {.i =  1}},
    { ClkRootWin,   0,                Button2,        togglebar,              {0}},
};

/* vim :ts=4 sw=4 sts=4 ft=c syn=c et: */

