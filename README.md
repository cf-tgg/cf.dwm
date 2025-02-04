
# Table of Contents

1.  [A bloated LARBS.](#org496a2c2)
2.  [Luke's Built-In patches and features](#org49361c3)
3.  [Some of the tweaks.](#orgc681cc9)
        1.  [TODO\\'s](#org2b5f867)



<a id="org496a2c2"></a>

# A bloated LARBS.

This is suckless, mmmk.. but feel free to check my [config](./config.h) or diff the rest for any breaking tweaks..  

Luke provided \`larbs.mom\` for his whole system, including the binding he had defined there ;
do compile and check it out for insights, but I wouldn't expect all the bindings to work in this build.
I'v installed the \`keychord' patch to tailor my dwm keymaps to my own heuristics. They most likely won't be
what you expect/like. I'd say make your own! I might document my customizations some day, but I might as well
start from scratch at this point.


<a id="org49361c3"></a>

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


<a id="orgc681cc9"></a>

# Some of the tweaks.

-   [Grid Layouts]: Few additional grid layouts to try them out.
-   [dwm-dynamicswallow-patch](https://dwm.suckless.org/patches/dynamicswallow/): Introduces "dynamic" window swallowing to dwm. 
    -   the patch provides S-<mouse1-drag> for mouse drag swallows.
    -   The [dwmswallow](./dwmswallow) command allows for suckless scripting of custom window swallow behaviours basicly.
        for example, I use the keychord (<kdb>Alt-[h,j,k,l] [h,j,k,l]<kdb>),
        repeating [h,j,k,l] "confirms" I want to swallow the window in that vim-ish motion's direction.
        or (<kbd>Alt-[Left,Down,Up,Right]<kbd>) to immediately swallow adjacent windows dynamically.
        -   The xdotool shell scripts are included in the \`swallow<sub>scripts</sub>' folder.
-   [cfacts](https://dwm.suckless.org/patches/cfacts/): Patched vanitygaps.c with support for cfacts and I believe some of the added layouts.
-   [defaulttransparency](https://dwm.suckless.org/patches/defaulttransparency/): This patch adds a default transparency parameter to config.h.
-   [KeyChords](https://dwm.suckless.org/patches/keychord/dwm-keychord-6.4.diff): When I thought I'd have enough free keybinding, I discovered Emacs.
-   [barpadding](https://dwm.suckless.org/patches/barpadding/dwm-barpadding-20211020-a786211.diff): Round corners look awkful without bar padding.


<a id="org2b5f867"></a>

### TODO\\'s

1.  TODO [ ] Cleanup my dwm related shell scripts.

2.  TODO [ ] Add script symlinks deployment to Makefile.

3.  TODO [+] Fix some conflicting emerging Emacs bindings.

4.  TODO [+] Dynamic Org table of keymap changes.

