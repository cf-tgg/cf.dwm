/*           __       _                    
 *      ___ / _|   __| |_      ___ __ ___  
 *     / __| |_   / _` \ \ /\ / / '_ ` _ \ 
 *    | (__|  _| | (_| |\ V  V /| | | | | |
 *     \___|_|    \__,_| \_/\_/ |_| |_| |_|
 */

#include <X11/X.h>
#include <stddef.h>

#define TERMINAL "st"
#define TERMCLASS "St"
#define BROWSER "qutebrowser"

/*     Appearance      */
static unsigned int borderpx =  1;   /* border pixel of windows */
static unsigned int snap     = 18;   /* snap pixel */
static unsigned int gappih   =  0;   /* horiz inner gap between windows */
static unsigned int gappiv   =  0;   /* vert inner gap between windows */
static unsigned int gappoh   =  0;   /* horiz outer gap between windows and screen edge */
static unsigned int gappov   =  0;   /* vert outer gap between windows and screen edge */

static int swallowfloating = 0; /* 1 means swallow floating windows by default */
static int smartgaps       = 0; /* 1 means no outer gap when there is only one window */

static int topbar  = 1;  /* 0 means bottom bar */
static int showbar = 1;  /* 0 means no bar */

static char *fonts[] = {
    "Caskadia Cove Nerd Font Mono:size=8", "monospace:size=10",
    "Font Awesome 6:pixelsize=24:antialias=true:autohint=true",
    "NotoColorEmoji:pixelsize=16:antialias=true:autohint=true"
};

static char normbgcolor[] = "#010101";
static char normfgcolor[] = "#99968e";
static char normbordercolor[] = "#0d0d0d";

static char selfgcolor[] = "#ebdbb2";
static char selbgcolor[] = "#010101";
static char selbordercolor[] = "#010101";

static const double defaultopacity = 0.95;
static const double activeopacity = 0.98;   /* Window opacity when it's focused (0 <= opacity <= 1) */
static const double inactiveopacity = 0.95;   /* Window opacity when it's inactive (0 <= opacity <= 1) */

static const unsigned int borderalpha = OPAQUE;
static const unsigned int baralpha = 220;

static const char *colors[][3] = { 
                       /* fg            bg              border   */
	[SchemeNorm] = { normfgcolor,   normbgcolor,    normbordercolor },
	[SchemeSel]  = { selfgcolor,    selbgcolor,     selbordercolor  },
};

static const unsigned int alphas[][3] = {
                  /*  fg     bg        border    */
    [SchemeNorm] = {OPAQUE, baralpha, borderalpha},
    [SchemeSel]  = {OPAQUE, baralpha, borderalpha},
};

typedef struct {
  const char *name;
  const void *cmd;
} Sp;

const char *spcmd1[] = {TERMINAL, "-n", "spterm", "-g", "85x25", NULL};
const char *spcmd2[] = {TERMINAL, "-n", "spcalc", "-f", "monospace:size=40", "-g", "12x8", "-e", "bc", "-lq", NULL};

static Sp scratchpads[] = {
    /* name         cmd  */
    {"spterm",      spcmd1},
    {"spcalc",      spcmd2},
};

/* tagging */
/* static const char *tags[] = {"1", "2", "3", "4",  "5", "6", "7", "8 ", "9"}; */
static const char *tags[]  =   {"", "", "",  "", "", "", "", " ", ""};

static const Rule rules[] = {
    /* class        instance     title          tags mask  isfloating  fopacity unfopacity isterminal  noswallow  monitor */
    {"Gimp",        NULL,        NULL,           1 << 4,     0,          1,          0,          1,          0,          -1},
    {"Blender",     NULL,        NULL,           1 << 4,     0,          1,          0.95,       0,          0,          -1},
    {"firefox",     NULL,        NULL,           1 << 2,     0,          1,          0.95,       0,          0,          -1},
    {"surf",        NULL,        NULL,           1 << 2,     0,          1,          0.95,       0,          0,          -1},
    {"qutebrowser", NULL,        NULL,           0,          0,          1,          0.95,       0,          0,          -1},
    {TERMCLASS,     "neomutt",   NULL,           1 << 6,     0,          1,          0.9,        1,          1,          -1},
    {TERMCLASS,     "Zathura",   NULL,           1 << 3,     0,          0.95,       0.9,        1,          0,          -1},
    {TERMCLASS,     NULL,        NULL,           0,          0,          1,          0,          1,          0,          -1},
    {TERMCLASS,     "floatterm", NULL,           0,          1,          1,          0,          0,          0,          -1},
    {TERMCLASS,     "spterm",    NULL,           SPTAG(0),   1,          1,          0,          0,          0,          -1},
    {TERMCLASS,     "bg",        NULL,           1 << 7,     0,          1,          0,          0,          0,          -1},
    {TERMCLASS,     "spcalc",    NULL,           SPTAG(1),   1,          1,          0,          0,          0,          -1},
    {NULL,          NULL,        "Event Tester", 0,          0,          0,          1,          0,          0,          -1},
};

/*      window swallowing   */
static const int  swalretroactive =  15 ;
static const int  swaldecay       =  30 ;
static const char swalsymbol[]    = "👅";

/*  layouts  */
static float mfact = 0.50; /* factor of master area size [0.05..0.95] */
static int nmaster = 1; /* number of clients in master area */
static int resizehints = 0; /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#define FORCE_VSPLIT 1   /* nrowgrid layout: force two clients to always split vertically */

#include "cfvanitygaps.c"

static const Layout layouts[] = {
/*   symbol          arrange                      function  */
    { "[]=",         tile },                      /* Default: Master on left, slaves on right */
    { "TTT",         bstack },                    /* Master on top, slaves on bottom */
    { "[@]",         spiral },                    /* Fibonacci spiral */
    { "[\\]",        dwindle },                   /* Decreasing in size right and leftward */
    { "[D]",         deck },                      /* Master on left, slaves in monocle-like mode on right */
    { "[M]",         monocle },                   /* All windows on top of eachother */
    { "|M|",         centeredmaster },            /* Master in middle, slaves on sides */
    { ">M>",         centeredfloatingmaster },    /* Same but master floats */
    { "===",         bstackhoriz },
    { "HHH",         grid },
    { "###",         nrowgrid },
    { "---",         horizgrid },
    { ":::",         gaplessgrid },
    { "><>",         NULL },                      /* no layout function means floating behavior */
    { NULL,          NULL },
};

/*  key definitions  */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG)                                                                                            \
       &((Keychord){1, {{MODKEY, KEY}},                                        view,           {.ui = 1 << TAG} }), \
       &((Keychord){1, {{MODKEY|ControlMask, KEY}},                            toggleview,     {.ui = 1 << TAG} }), \
       &((Keychord){1, {{MODKEY|ShiftMask, KEY}},                              tag,            {.ui = 1 << TAG} }), \
       &((Keychord){1, {{MODKEY|ControlMask|ShiftMask, KEY}},                  toggletag,      {.ui = 1 << TAG} }),

#define STACKKEYS(MOD, ACTION)                       \
    &((Keychord){1, {{MOD, XK_j}}, ACTION##stack, {.i = INC(+1)} }), \
    &((Keychord){1, {{MOD, XK_k}}, ACTION##stack, {.i = INC(-1)} }), \
    &((Keychord){1, {{MOD, XK_v}}, ACTION##stack, {.i = 0}}),

/*
 *  { MOD, XK_grave, ACTION##stack, {   .i = PREVSEL  }  }, \
 *  { MOD, XK_a,     ACTION##stack, {   .i = 1        }  }, \
 *  { MOD, XK_z,     ACTION##stack, {   .i = 2        }  }, \
 *  { MOD, XK_x,     ACTION##stack, {   .i = -1       }  },
 */


/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd)                                                             \
  {                                                                            \
    .v = (const char *[]) { "/bin/sh", "-c", cmd, NULL }                       \
  }



/* commands */
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
    STACKKEYS(MODKEY, focus) STACKKEYS(MODKEY | ShiftMask, push)
    TAGKEYS(XK_1, 0) TAGKEYS(XK_2, 1) TAGKEYS(XK_3, 2)
    TAGKEYS(XK_4, 3) TAGKEYS(XK_5, 4) TAGKEYS(XK_6, 5)
    TAGKEYS(XK_7, 6) TAGKEYS(XK_8, 7) TAGKEYS(XK_9, 8)

    /* Keychord      modifier / combos                  key               function       argument */
    &((Keychord){1, {{MODKEY,                           XK_0}},           view,          {.ui = ~0}}),
    &((Keychord){1, {{MODKEY | ShiftMask,               XK_0}},           tag,           {.ui = ~0}}),

    &((Keychord){1, {{MODKEY | ShiftMask,               XK_Escape}},      spawn,         {.v = termcmd}}),
    &((Keychord){1, {{MODKEY,                           XK_grave}},       spawn,         {.v = (const char *[]){"dmenuunicode", NULL}}}),
    /* &((Keychord){1, {{MODKEY | ShiftMask,           XK_grave}},       togglescratch, SHCMD("") }), */
    &((Keychord){1, {{MODKEY,                           XK_Tab}},         view,          {0}}),
    &((Keychord){1, {{MODKEY,                           XK_q}},           killclient,    {0}}),
    &((Keychord){1, {{MODKEY,                           XK_minus}},       spawn,         SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 5%-; kill -44 $(pidof dwmblocks)")}),
    &((Keychord){1, {{MODKEY | ShiftMask,               XK_minus}},       spawn,         SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 15%-; kill -44 $(pidof dwmblocks)")}),
    &((Keychord){1, {{MODKEY,                           XK_equal}},       spawn,         SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 5%+; kill -44 $(pidof dwmblocks)")}),
    &((Keychord){1, {{MODKEY | ShiftMask,               XK_equal}},       spawn,         SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 15%+; kill -44 $(pidof dwmblocks)")}),
    &((Keychord){1, {{MODKEY,                           XK_BackSpace}},   spawn,         {.v = (const char *[]){"sysact", NULL}}}),
    &((Keychord){1, {{MODKEY | ShiftMask,               XK_BackSpace}},   spawn,         {.v = (const char *[]){"sysact", NULL}}}),
    &((Keychord){1, {{MODKEY | ShiftMask,               XK_q}},           spawn,         {.v = (const char *[]){"sysact", NULL}}}),
    &((Keychord){1, {{MODKEY,                           XK_w}},           spawn,         {.v = (const char *[]){BROWSER, NULL}}}),
    &((Keychord){1, {{MODKEY | ControlMask,             XK_Tab}},         spawn,         SHCMD("/home/cf/.local/bin/kb-toggle")}),
    &((Keychord){1, {{MODKEY | ControlMask,             XK_space}},       spawn,         SHCMD("/home/cf/.local/bin/kb-toggle")}),
    &((Keychord){1, {{Mod1Mask,                         XK_space}},       spawn,         SHCMD("/home/cf/.local/bin/kb-toggle")}),
    &((Keychord){1, {{MODKEY | ShiftMask,               XK_w}},           spawn,         {.v = (const char *[]){TERMINAL, "-e", "sudo", "nmtui", NULL}}}),
    &((Keychord){1, {{MODKEY,                           XK_e}},           spawn,         SHCMD(TERMINAL " -e neomutt ; pkill -RTMIN+12 dwmblocks; rmdir ~/.abook 2>/dev/null")}),
    &((Keychord){1, {{MODKEY | ShiftMask,               XK_e}},           spawn,         SHCMD(TERMINAL " -e abook -C ~/.config/abook/abookrc --datafile ~/.config/abook/addressbook")}),
    &((Keychord){1, {{MODKEY,                           XK_r}},           spawn,         {.v = (const char *[]){TERMINAL, "-e", "lfub", NULL}}}),
    &((Keychord){1, {{MODKEY | ShiftMask,               XK_r}},           spawn,         {.v = (const char *[]){TERMINAL, "-e", "htop", NULL}}}),

    &((Keychord){1, {{MODKEY, XK_t}},                  setlayout,     {.v = &layouts[0]}}),  /* tile */
    &((Keychord){1, {{MODKEY|ShiftMask, XK_t}},        setlayout,     {.v = &layouts[1]}}),  /* bstack */
    &((Keychord){1, {{MODKEY, XK_y}},                  setlayout,     {.v = &layouts[2]}}),  /* spiral */
    &((Keychord){1, {{MODKEY|ShiftMask, XK_y}},        setlayout,     {.v = &layouts[3]}}),  /* dwindle */
    &((Keychord){1, {{MODKEY, XK_u}},                  setlayout,     {.v = &layouts[4]}}),  /* deck */
    &((Keychord){1, {{MODKEY|ShiftMask, XK_u}},        setlayout,     {.v = &layouts[5]}}),  /* monocle */
    &((Keychord){1, {{MODKEY, XK_i}},                  setlayout,     {.v = &layouts[6]}}),  /* centeredmaster */
    &((Keychord){1, {{MODKEY|ControlMask, XK_i}},      setlayout,     {.v = &layouts[7]}}),  /* centeredfloatingmaster */
    &((Keychord){1, {{MODKEY|ControlMask, XK_t}},      setlayout,     {.v = &layouts[8]}}),  /* bstackhoriz */
    &((Keychord){1, {{MODKEY|ControlMask, XK_y}},      setlayout,     {.v = &layouts[9]}}),  /* grid */
    &((Keychord){1, {{MODKEY|ControlMask, XK_u}},      setlayout,     {.v = &layouts[10]}}), /* nrowgrid */
    &((Keychord){1, {{MODKEY|ControlMask, XK_i}},      setlayout,     {.v = &layouts[11]}}), /* horizgrid */
    &((Keychord){1, {{MODKEY|ControlMask, XK_o}},      setlayout,     {.v = &layouts[11]}}), /* gaplessgrid */

    &((Keychord){1, {{MODKEY|ControlMask, XK_a}}, changefocusopacity,    {.f = +0.025}}),
    &((Keychord){1, {{MODKEY|ControlMask, XK_s}}, changefocusopacity,    {.f = -0.025}}),
    &((Keychord){1, {{MODKEY|ControlMask, XK_z}}, changeunfocusopacity,  {.f = +0.025}}),
    &((Keychord){1, {{MODKEY|ControlMask, XK_x}}, changeunfocusopacity,  {.f = -0.025}}),

    &((Keychord){1, {{MODKEY, XK_o}},           incnmaster,              {.i = +1}}),
    &((Keychord){1, {{MODKEY|ShiftMask, XK_o}}, incnmaster,              {.i = -1}}),

    &((Keychord){1, {{MODKEY, XK_backslash}},          view,                 {0}}),
    &((Keychord){1, {{MODKEY|ShiftMask, XK_backslash}}, spawn,               {.v = (const char *[]){"bmcommand", NULL}}}),
    &((Keychord){1, {{MODKEY|ShiftMask, XK_Up}},       spawn,               SHCMD("xdotool type \"$(grep -v '^#' ~/Notes/bmcmd | dmenu -i -l 50 | cut -d' ' -f2 -)\"")}),
    &((Keychord){1, {{MODKEY|ShiftMask, XK_Down}},     spawn,               {.v = (const char *[]){"bmcommand", NULL}}}),
    &((Keychord){1, {{MODKEY|ControlMask, XK_p}},      spawn,               {.v = (const char *[]){"scrncast", NULL}}}),
    &((Keychord){1, {{MODKEY|ShiftMask|ControlMask, XK_p}}, spawn,          {.v = (const char *[]){"dmenurecord", "kill", NULL}}}),
    /* &((Keychord){1, {{MODKEY|ShiftMask, XK_backslash}}, spawn,          SHCMD("")}), */
    /* &((Keychord){1, {{MODKEY|ControlMask, XK_w}},      spawn,           {.v = (const char *[]){"camcast", NULL}}}), */

    &((Keychord){1, {{MODKEY, XK_d}},                 spawn,               {.v = (const char *[]){"dmenu_run", NULL}}}),
    &((Keychord){1, {{MODKEY|ShiftMask, XK_d}},       spawn,               {.v = (const char *[]){"passmenu", NULL}}}),
    &((Keychord){1, {{MODKEY, XK_f}},                 togglefullscr,        {0}}),
    &((Keychord){1, {{MODKEY|ShiftMask, XK_f}},       setlayout,            {.v = &layouts[8]}}),
    &((Keychord){1, {{MODKEY, XK_g}},                 shiftview,            {.i = -1}}),
    &((Keychord){1, {{MODKEY|ShiftMask, XK_g}},       shifttag,             {.i = -1}}),
    &((Keychord){1, {{MODKEY, XK_h}},                 setmfact,             {.f = -0.05}}),
    &((Keychord){1, {{MODKEY, XK_l}},                 setmfact,             {.f = +0.05}}),

    /* cfacts */
    &((Keychord){1, {{MODKEY|ShiftMask, XK_h}},       setcfact,             {.f = +0.05}}),
    &((Keychord){1, {{MODKEY|ShiftMask, XK_l}},       setcfact,             {.f = -0.05}}),
    &((Keychord){1, {{MODKEY|ShiftMask, XK_o}},       setcfact,             {.f = 0.00}}),

    /* Resize gaps */
    &((Keychord){1, {{MODKEY,               XK_a}},            togglegaps,     {0}}),
    &((Keychord){1, {{MODKEY | ShiftMask,   XK_a}},            defaultgaps,    {0}}),
    &((Keychord){1, {{MODKEY,               XK_s}},            togglesticky,   {0}}),
    &((Keychord){1, {{MODKEY,               XK_z}},            incrgaps,       {.i = -1}}),
    &((Keychord){1, {{MODKEY,               XK_x}},            incrgaps,       {.i = +1}}),
    &((Keychord){1, {{MODKEY,               XK_semicolon}},    shiftview,      {.i = 1}}),
    &((Keychord){1, {{MODKEY | ShiftMask,   XK_semicolon}},    shifttag,       {.i = 1}}),
    &((Keychord){1, {{MODKEY | ShiftMask,   XK_space}},        togglefloating, {0}}),
    &((Keychord){1, {{MODKEY,               XK_b}},            togglebar,      {0}}),
    &((Keychord){1, {{MODKEY,               XK_Return}},       spawn,          {.v = termcmd}}),
    &((Keychord){1, {{MODKEY | ShiftMask,   XK_Return}},       togglescratch,  {.ui = 0}}),
    &((Keychord){1, {{MODKEY,               XK_apostrophe}},   togglescratch,  {.ui = 1}}),

    /* Additional spawn commands */
    &((Keychord){1, {{MODKEY,               XK_n}},            spawn,          SHCMD(TERMINAL " -e newsboat; pkill -RTMIN+6 dwmblocks")}),
    &((Keychord){1, {{MODKEY,               XK_c}},            spawn,          SHCMD(TERMINAL " -e calcurse")}),
    &((Keychord){1, {{MODKEY | ShiftMask,   XK_b}},            spawn,          {.v = (const char *[]){ "bookmarkthis", NULL}}}),

    /*           'tites fonctions de manipulation de textes             */
    /*{ ControlMask | ShiftMask, XK_r,         spawn,      SHCMD("echo \"$(xclip -o)\" >> ~/Notes/clipregisters/r")},*/
    /*{ MODKEY | ControlMask,    XK_r,         spawn,      SHCMD("echo \"\" > ~/Notes/clipregisters/r")},*/
    /*{ ControlMask | ShiftMask, XK_a,         spawn,      SHCMD("echo \"$(xclip -o)\" > ~/Notes/clipregisters/a")},*/
    /*{ MODKEY | ControlMask,    XK_a,         spawn,      SHCMD("echo \"\" > ~/Notes/clipregisters/a")},*/
    /*{ ControlMask | ShiftMask, XK_s,         spawn,      SHCMD("echo \"$(xclip -o)\" >> ~/Notes/clipregisters/s")},*/
    /*{ MODKEY | ControlMask,    XK_s,         spawn,      SHCMD("echo \"\" > ~/Notes/clipregisters/s")},*/
    /*{ ControlMask,             XK_x,         spawn,      SHCMD("xclip -selection primary -o | xsel -s -a")},*/
    /*{ ControlMask | ShiftMask, XK_x,         spawn,      SHCMD("xsel --exchange")},*/
    /*{ ControlMask | ShiftMask, XK_d,         spawn,      SHCMD("echo \"$(xclip -selection secondary -o)\" > ~/Notes/clipregisters/a")},*/
    /*{ ControlMask | ShiftMask, XK_f,         spawn,      SHCMD("xclip -selection clipboard -o | xclip -selection primary")},*/
    /*{ MODKEY | ShiftMask,      XK_n,         spawn,      SHCMD("$(head -n 1 ~/Notes/selclips | xclip -o )")},*/

    /*{ MODKEY | ShiftMask | ControlMask,      XK_r,         spawn,      SHCMD("cat ~/Notes/clipregisters/r | tts")},*/
    /*{ MODKEY | ShiftMask | ControlMask,      XK_a,         spawn,      SHCMD("cat ~/Notes/clipregisters/a | tts -m en_US-libritts-high")},*/
    /*{ MODKEY | ShiftMask | ControlMask,      XK_s,         spawn,      SHCMD("cat ~/Notes/clipregisters/s | tts")},*/

    /* Media controls */
    &((Keychord){1, {{MODKEY | ShiftMask,   XK_m}},            spawn,          SHCMD("wpctl set-mute @DEFAULT_AUDIO_SINK@ toggle; kill -44 $(pidof dwmblocks)")}),
    &((Keychord){1, {{MODKEY,               XK_m}},            spawn,          {.v = (const char *[]){ TERMINAL, "-e", "ncmpcpp", NULL}}}),
    &((Keychord){1, {{ControlMask,          XK_comma}},        spawn,          {.v = (const char *[]){"mpc", "prev", NULL}}}),
    &((Keychord){1, {{ControlMask | ShiftMask, XK_comma}},     spawn,          {.v = (const char *[]){"mpc", "seek", "0%", NULL}}}),
    &((Keychord){1, {{ControlMask,          XK_period}},       spawn,          {.v = (const char *[]){"mpc", "next", NULL}}}),
    &((Keychord){1, {{ControlMask | ShiftMask, XK_period}},    spawn,          {.v = (const char *[]){"mpc", "repeat", NULL}}}),
    &((Keychord){1, {{MODKEY,               XK_p}},            spawn,          {.v = (const char *[]){"mpc", "toggle", NULL}}}),
    &((Keychord){1, {{MODKEY,               XK_bracketleft}},  spawn,          {.v = (const char *[]){"mpc", "seek", "-10", NULL}}}),
    &((Keychord){1, {{MODKEY | ShiftMask,   XK_bracketleft}},  spawn,          {.v = (const char *[]){"mpc", "seek", "-60", NULL}}}),
    &((Keychord){1, {{MODKEY,               XK_bracketright}}, spawn,          {.v = (const char *[]){"mpc", "seek", "+10", NULL}}}),
    &((Keychord){1, {{MODKEY | ShiftMask,   XK_bracketright}}, spawn,          {.v = (const char *[]){"mpc", "seek", "+60", NULL}}}),

    /* Super + [left|right] to switch monitor focus; Super + Shift + [left|right] to send windows to other monitor */
    &((Keychord){1, {{MODKEY,               XK_Left}},         focusmon,   {.i = +1}}),
    &((Keychord){1, {{MODKEY,               XK_Right}},        focusmon,   {.i = -1}}),
    &((Keychord){1, {{MODKEY | ShiftMask,   XK_Left}},         tagmon,     {.i = +1}}),
    &((Keychord){1, {{MODKEY | ShiftMask,   XK_Right}},        tagmon,     {.i = -1}}),
    
    /* Super directional plus additional accessible keys */
    &((Keychord){1, {{MODKEY,               XK_period}},      focusmon,        {.i = -1}}),
    &((Keychord){1, {{MODKEY,               XK_comma}},       focusmon,        {.i = +1}}),
    &((Keychord){1, {{MODKEY | ShiftMask,   XK_period}},      tagmon,          {.i = -1}}),
    &((Keychord){1, {{MODKEY | ShiftMask,   XK_comma}},       tagmon,          {.i = +1}}),
    
    /* Moving windows in the stack */
    &((Keychord){1, {{MODKEY,               XK_Page_Up}},    shiftview,      {.i = -1}}),
    &((Keychord){1, {{MODKEY | ShiftMask,   XK_Page_Up}},    shifttag,       {.i = -1}}),
    &((Keychord){1, {{MODKEY,               XK_Page_Down}},  shiftview,      {.i = +1}}),
    &((Keychord){1, {{MODKEY | ShiftMask,   XK_Page_Down}},  shifttag,       {.i = +1}}),

    /* Super + Control + [left|right|up|down] to rotate monitor view */
    /* { MODKEY | ControlMask,  XK_Right,       spawn,          SHCMD("xrandr --output eDP-1 --rotate left && setbg")}, */
    /* { MODKEY | ControlMask,  XK_Left,        spawn,          SHCMD("xrandr --output eDP-1 --rotate right && setbg")}, */
    /* { MODKEY | ControlMask,  XK_Up,          spawn,          SHCMD("xrandr --output eDP-1 --rotate inverted && setbg")}, */
    /* { MODKEY | ControlMask,  XK_Down,        spawn,          SHCMD("xrandr --output eDP-1 --rotate normal && setbg")}, */

    /* Delegation to the swallowing window manager */
    &((Keychord){1, {{MODKEY | ShiftMask, XK_apostrophe}},    swalstopsel,     {0}}),
    /* &((Keychord){1, {{0,                     XK_Left}},        swalstopsel,  {0}}), */
    /* &((Keychord){1, {{0,                     XK_Right}},       swalstopsel,  {0}}), */
    /* &((Keychord){1, {{0,                     XK_Up}},          spawn,        SHCMD("unswal 1")}), */
    &((Keychord){2, {{MODKEY,XK_Down}, {0,XK_Down}},           spawn,           SHCMD("unswal 1")}),


    /* Alt + directional keys to move windows */
    &((Keychord){2, {{Mod1Mask, XK_h}, {0, XK_h}},             spawn,           SHCMD("winLeft")}),
    &((Keychord){2, {{Mod1Mask, XK_j}, {0, XK_j}},             spawn,           SHCMD("winUnder")}),
    &((Keychord){2, {{Mod1Mask, XK_k}, {0, XK_k}},             spawn,           SHCMD("winAbove")}),
    &((Keychord){2, {{Mod1Mask, XK_l}, {0, XK_l}},             spawn,           SHCMD("winRight")}),
    &((Keychord){1, {{Mod1Mask, XK_Left}},                     spawn,           SHCMD("winLeft")}),
    &((Keychord){1, {{Mod1Mask, XK_Down}},                     spawn,           SHCMD("winUnder")}),
    &((Keychord){1, {{Mod1Mask, XK_Up}},                       spawn,           SHCMD("winAbove")}),
    &((Keychord){1, {{Mod1Mask, XK_Right}},                    spawn,           SHCMD("winRight")}),


    /* Super + functions for various scripts and utilities */
    &((Keychord){1, {{MODKEY | ShiftMask,   XK_s}},       spawn, SHCMD("xdotool type $(grep -v '^#' ~/Notes/snippets | dmenu -i -l 50 |cut -d' ' -f1)")}),
    &((Keychord){1, {{MODKEY | ShiftMask,   XK_Insert}},  spawn, SHCMD("xdotool type --delay 50 \"$(grep -v '^#' ~/Notes/bmcmd | dmenu -i -l 50 | cut -d' ' -f2-)\"")}),
    &((Keychord){1, {{MODKEY,               XK_F1}},      spawn, SHCMD("man -k . | dmenu -l 30 | awk '{print $1}' | xargs -r man -Tpdf | zathura -")}),
    &((Keychord){1, {{MODKEY,               XK_F2}},      spawn, SHCMD("readit -c")}),
    &((Keychord){1, {{MODKEY | ShiftMask,   XK_F2}},    spawn, {.v = (const char *[]){"tutorialvids", NULL}}}),
    &((Keychord){1, {{MODKEY,               XK_F3}},      spawn, {.v = (const char *[]){"displayselect", NULL}}}),
    &((Keychord){1, {{MODKEY,               XK_F4}},      spawn, SHCMD(TERMINAL " -e pulsemixer; kill -44 $(pidof dwmblocks)")}),
    &((Keychord){1, {{MODKEY,               XK_F5}},      xrdb,  {.v = NULL}}),
    &((Keychord){1, {{MODKEY,               XK_F6}},      spawn, {.v = (const char *[]){"torwrap", NULL}}}),
    &((Keychord){1, {{MODKEY,               XK_F7}},      spawn, {.v = (const char *[]){"td-toggle", NULL}}}),
    &((Keychord){1, {{MODKEY,               XK_F8}},      spawn, {.v = (const char *[]){"mailsync", NULL}}}),
    &((Keychord){1, {{MODKEY,               XK_F9}},      spawn, {.v = (const char *[]){"mounter", NULL}}}),
    &((Keychord){1, {{MODKEY,               XK_F10}},     spawn, {.v = (const char *[]){"unmounter", NULL}}}),
    &((Keychord){1, {{MODKEY,               XK_F11}},     spawn, SHCMD("mpv --untimed --no-cache --profile=low-latency --title=webcam $(ls /dev/video** | head -n 1)")}),
    /* &((Keychord){1, {{MODKEY,             XK_F11}},     spawn, SHCMD("mpv --untimed --no-cache --no-osc --no-input-default-bindings --profile=low-latency --input-conf=/dev/null --title=webcam $(ls /dev/video** | head -n 1)")}), */
    &((Keychord){1, {{MODKEY,               XK_F12}},     spawn, SHCMD("remaps")}),
    &((Keychord){1, {{MODKEY,               XK_space}},   zoom,  {0}}),

    &((Keychord){1, {{ControlMask | ShiftMask, XK_p}},               spawn, SHCMD("shotgun -g $(hacksaw) $(date +%Y-%m-%d-%H%M-%S).png")}),
    &((Keychord){1, {{ControlMask | ShiftMask, XK_p}},               spawn, SHCMD("maim pic-full-$(date '+%y%m%d-%H%M-%S').png")}),
    &((Keychord){1, {{0, XK_Print}},                               spawn, SHCMD("flameshot gui")}),
    &((Keychord){1, {{0, XK_Print}},                               spawn, SHCMD("maim pic-full-$(date '+%y%m%d-%H%M-%S').png")}),
    &((Keychord){1, {{ShiftMask, XK_Print}},                        spawn, {.v = (const char *[]){"maimpick", NULL}}}),
    &((Keychord){1, {{MODKEY, XK_Print}},                           spawn, {.v = (const char *[]){"dmenurecord", NULL}}}),
    &((Keychord){1, {{MODKEY | ShiftMask, XK_Print}},               spawn, {.v = (const char *[]){"dmenurecord", "kill", NULL}}}),
    &((Keychord){1, {{MODKEY, XK_Delete}},                          spawn, {.v = (const char *[]){"dmenurecord", "kill", NULL}}}),
    &((Keychord){1, {{MODKEY, XK_Scroll_Lock}},                     spawn, SHCMD("killall screenkey || screenkey &")}),
    &((Keychord){1, {{0, XF86XK_AudioMute}},                        spawn, SHCMD("wpctl set-mute @DEFAULT_AUDIO_SINK@ toggle; kill -44 $(pidof dwmblocks)")}),
    &((Keychord){1, {{0, XF86XK_AudioRaiseVolume}},                 spawn, SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 0%- && wpctl set-volume @DEFAULT_AUDIO_SINK@ 3%+; kill -44 $(pidof dwmblocks)")}),
    &((Keychord){1, {{0, XF86XK_AudioLowerVolume}},                 spawn, SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 0%+ && wpctl set-volume @DEFAULT_AUDIO_SINK@ 3%-; kill -44 $(pidof dwmblocks)")}),
    &((Keychord){1, {{0, XF86XK_AudioPrev}},                        spawn, {.v = (const char *[]){"mpc", "prev", NULL}}}),
    &((Keychord){1, {{0, XF86XK_AudioNext}},                        spawn, {.v = (const char *[]){"mpc", "next", NULL}}}),
    &((Keychord){1, {{0, XF86XK_AudioPause}},                       spawn, {.v = (const char *[]){"mpc", "pause", NULL}}}),
    &((Keychord){1, {{0, XF86XK_AudioPlay}},                        spawn, {.v = (const char *[]){"mpc", "play", NULL}}}),
    &((Keychord){1, {{0, XF86XK_AudioStop}},                        spawn, {.v = (const char *[]){"mpc", "stop", NULL}}}),
    &((Keychord){1, {{0, XF86XK_AudioRewind}},                      spawn, {.v = (const char *[]){"mpc", "seek", "-10", NULL}}}),
    &((Keychord){1, {{0, XF86XK_AudioForward}},                     spawn, {.v = (const char *[]){"mpc", "seek", "+10", NULL}}}),
    &((Keychord){1, {{0, XF86XK_AudioMedia}},                       spawn, {.v = (const char *[]){TERMINAL, "-e", "ncmpcpp", NULL}}}),
    &((Keychord){1, {{0, XF86XK_AudioMicMute}},                     spawn, SHCMD("pactl set-source-mute @DEFAULT_SOURCE@ toggle")}),
    &((Keychord){1, {{0, XF86XK_Calculator}},                       spawn, {.v = (const char *[]){TERMINAL, "-e", "bc", "-l", NULL}}}),
    &((Keychord){1, {{0, XF86XK_Sleep}},                            spawn, {.v = (const char *[]){"sudo", "-A", "zzz", NULL}}}),
    &((Keychord){1, {{0, XF86XK_WWW}},                              spawn, {.v = (const char *[]){BROWSER, NULL}}}),
    &((Keychord){1, {{0, XF86XK_DOS}},                              spawn, {.v = termcmd}}),
    &((Keychord){1, {{0, XF86XK_ScreenSaver}},                      spawn, SHCMD("slock & xset dpms force off; mpc pause; pauseallmpv")}),
    &((Keychord){1, {{0, XF86XK_TaskPane}},                         spawn, {.v = (const char *[]){TERMINAL, "-e", "htop", NULL}}}),
    &((Keychord){1, {{0, XF86XK_Mail}},                             spawn, SHCMD(TERMINAL " -e neomutt ; pkill -RTMIN+12 dwmblocks")}),
    &((Keychord){1, {{0, XF86XK_MyComputer}},                       spawn, {.v = (const char *[]){TERMINAL, "-e", "lfub", "/", NULL}}}),
    &((Keychord){1, {{0, XF86XK_Launch1}},                         spawn, {.v = (const char *[]){"xset", "dpms", "force", "off", NULL}}}),
    &((Keychord){1, {{0, XF86XK_TouchpadToggle}},                   spawn, SHCMD("(synclient | grep 'TouchpadOff.*1' && synclient TouchpadOff=0) || synclient TouchpadOff=1")}),
    &((Keychord){1, {{0, XF86XK_TouchpadOff}},                      spawn, {.v = (const char *[]){"synclient", "TouchpadOff=1", NULL}}}),
    &((Keychord){1, {{0, XF86XK_TouchpadOn}},                       spawn, {.v = (const char *[]){"synclient", "TouchpadOff=0", NULL}}}),
    &((Keychord){1, {{0, XF86XK_MonBrightnessUp}},                  spawn, SHCMD("sudo light -A 10.00")}),
    &((Keychord){1, {{0, XF86XK_MonBrightnessDown}},                spawn, SHCMD("sudo light -U 10.00")}),
    &((Keychord){1, {{MODKEY|ShiftMask, XK_q}},                     quit,           {0}}),

    /*&((Keychord){1, {{ShiftMask, XK_F1}},         spawn, SHCMD("")}),*/
    /*&((Keychord){1, {{ShiftMask, XK_F2}},         spawn, SHCMD("")}),*/
    /*&((Keychord){1, {{ShiftMask, XK_F3}},         spawn, SHCMD("")}),*/
    &((Keychord){1, {{ShiftMask, XK_F4}},           spawn, SHCMD("toggleblur")}),
    &((Keychord){1, {{ShiftMask, XK_F5}},           spawn, SHCMD("walfeh")}),
    &((Keychord){1, {{ShiftMask, XK_F6}},           spawn, SHCMD("yank_zathura_page.sh")}),
    &((Keychord){1, {{ShiftMask, XK_F7}},           spawn, SHCMD("yankmon 1")}),
    &((Keychord){1, {{ShiftMask, XK_F8}},           spawn, SHCMD("readit -c")}),
    &((Keychord){1, {{ShiftMask, XK_F9}},           spawn, SHCMD("yankmon 2")}),
    &((Keychord){1, {{0, XK_F10}},                  spawn, SHCMD("unswal 1")}),
    &((Keychord){1, {{ShiftMask, XK_F11}},          spawn, SHCMD("xmouse")}),
    &((Keychord){2, {{ShiftMask, XK_w},{0, XK_w}},  spawn, SHCMD("xmouse")}),
    /*&((Keychord){1, {{0, XK_F12}},                spawn, SHCMD("")}), */

    /*&((Keychord){2, {{MODKEY, XK_}, {MODKEY, XK_m}}, spawn, SHCMD("xmouse")}),*/

    /* Keypad bindings */
    &((Keychord){1, {{ControlMask, XK_KP_Insert}},    spawn, SHCMD("~/Scripts/numpad/0")}),
    &((Keychord){1, {{ControlMask, XK_KP_End}},       spawn, SHCMD("~/Scripts/numpad/1")}),
    &((Keychord){1, {{ControlMask, XK_KP_Down}},      spawn, SHCMD("~/Scripts/numpad/2")}),
    &((Keychord){1, {{ControlMask, XK_KP_Page_Down}}, spawn, SHCMD("~/Scripts/numpad/3")}),
    &((Keychord){1, {{ControlMask, XK_KP_Left}},      spawn, SHCMD("~/Scripts/numpad/4")}),
    &((Keychord){1, {{ControlMask, XK_KP_Begin}},     spawn, SHCMD("~/Scripts/numpad/5")}),
    &((Keychord){1, {{ControlMask, XK_KP_Right}},     spawn, SHCMD("~/Scripts/numpad/6")}),
    &((Keychord){1, {{ControlMask, XK_KP_Home}},      spawn, SHCMD("~/Scripts/numpad/7")}),
    &((Keychord){1, {{ControlMask, XK_KP_Up}},        spawn, SHCMD("~/Scripts/numpad/8")}),
    &((Keychord){1, {{ControlMask, XK_KP_Page_Up}},   spawn, SHCMD("~/Scripts/numpad/9")}),


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
    { ClkStatusText, ShiftMask,       Button3,        spawn,                  SHCMD(TERMINAL " -e nvim ~/.local/src/dwmblocks/config.h")},
    { ClkClientWin,  MODKEY,          Button1,        movemouse,              {0}},
    { ClkClientWin,  MODKEY,          Button2,        defaultgaps,            {0}},
    { ClkClientWin,  MODKEY,          Button3,        resizemouse,            {0}},
    /* { ClkClientWin, MODKEY,      Button4,        incrgaps,               {.i = +1} }, */
    /* { ClkClientWin, MODKEY,      Button5,        incrgaps,               {.i = -1} }, */
    { ClkClientWin, MODKEY,           Button4,        changefocusopacity,     {.f = +0.025}},
    { ClkClientWin, MODKEY,           Button5,        changefocusopacity,     {.f = -0.025}},
    { ClkClientWin, MODKEY|ShiftMask, Button1,        swalmouse,              {0}},
    { ClkTagBar,    0,                Button1,        view,                   {0}},
    { ClkTagBar,    0,                Button3,        toggleview,             {0}},
    { ClkTagBar,    MODKEY,           Button1,        tag,                    {0}},
    { ClkTagBar,    MODKEY,           Button3,        toggletag,              {0}},
    { ClkTagBar,    0,                Button4,        shiftview,              {.i = -1}},
    { ClkTagBar,    0,                Button5,        shiftview,              {.i = 1}},
    { ClkRootWin,   0,                Button2,        togglebar,              {0}},
};


