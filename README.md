
# Table of Contents

1.  [A bloated LARBS.](#orge7eca79)
2.  [Luke's Built-In patches and features](#org266857b)
3.  [Some of the tweaks.](#org42b5d8e)



<a id="orge7eca79"></a>

# A bloated LARBS.

This is suckless, mmmk.. but feel free to check my [config](./config.h) or diff the rest for any breaking tweaks..  

Luke provided \`larbs.mom\` for his whole system, including the binding he had defined there ;
do compile and check it out for insights, but I wouldn't expect all the bindings to work in this build.
I'v installed the \`keychord' patch to tailor my dwm keymaps to my own heuristics. They most likely won't be
what you expect/like. I'd say make your own! I might document my customizations some day, but I might as well
start from scratch at this point.


<a id="org266857b"></a>

# Luke's Built-In patches and features

-   A [Clickable statusbar](https://dwm.suckless.org/patches/statuscmd/) with his build of [dwmblocks](https://github.com/lukesmithxyz/dwmblocks).
-   Support for [Xresources](https://dwm.suckless.org/patches/xresources/) colors/variables (i.e. works with \`pywal\`, etc.).
-   Scratchpad: Accessible with <kbd>mod+shift+enter</kbd>.
-   True fullscreen (<kbd>super+f</kbd>) and prevents focus shifting.
-   Windows can be made sticky (<kbd>super+s</kbd>).
-   [pertag](https://dwm.suckless.org/patches/pertag/): More general approach to taglayouts patch. This patch keeps layout, mwfact, barpos and nmaster per tag.
-   [hide vacant tags](https://dwm.suckless.org/patches/hide_vacant_tags/): hides tags with no windows.
-   [stacker](https://dwm.suckless.org/patches/stacker/): Move windows up the stack manually (<kbd>super-K/J</kbd>).
-   [shiftview](https://dwm.suckless.org/patches/nextprev/): Cycle through tags (<kbd>super+g/;</kbd>).
-   [vanitygaps](https://dwm.suckless.org/patches/vanitygaps/): Gaps allowed across all layouts.
-   [swallow patch](https://dwm.suckless.org/patches/swallow/): if a program run from a terminal would make it inoperable, it temporarily takes its place to save space.
-   New layouts: bstack, fibonacci, deck, centered master and more. All bound to keys <kbd>super+(shift+)t/y/u/i</kbd>.
-   [dwm-alpha](https://dwm.suckless.org/patches/alpha/): Allow dwm to have translucent bars, while keeping all the text on it opaque.


<a id="org42b5d8e"></a>

# Some of the tweaks.

-   [dwm-dynamicswallow-patch](https://dwm.suckless.org/patches/dynamicswallow/): Introduces "dynamic" window swallowing to dwm. 
    -   the patch provides S-<mouse1-drag> for mouse drag swallows.
    -   The [dwmswallow](./dwmswallow) command allows for suckless scripting of custom window swallow behaviours basicly.
        for example, I use the keychord \`M-[h,j,k,l] [h,j,k,l]' (\`Mod1Mask-[h,j,k,l] [h,j,k,l]')
        Repeating [h,j,k,l] to "confirm" I want to swallow the window in that motion's direction.
        or Mod1Mask-[Left,Down,Up,Right] to immediately swallow adjacent windows dynamically, using simple
        xdotool shell script that you can take a look at in swallow<sub>scripts</sub>.
-   [cfacts](https://dwm.suckless.org/patches/cfacts/): Added full patched vanitygaps.c to adding support for cfacts in addition to mfacts
-   [defaulttransparency](https://dwm.suckless.org/patches/defaulttransparency/): This patch adds a default transparency parameter to config.h.
-   [KeyChords](https://dwm.suckless.org/patches/keychord/dwm-keychord-6.4.diff): When I thought I'd have enough free keybinding, I discovered Emacs.
-   [barpadding](https://dwm.suckless.org/patches/barpadding/dwm-barpadding-20211020-a786211.diff): Round corners look awkful without bar padding.
-   [Grid Layouts]: I added a few additional layouts to try them out.

