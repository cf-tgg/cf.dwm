# cf's build of dwm

## FAQ

> What are the bindings?

This is suckless, mmmbud, the source code is the documentation! Check out [config.h](config.h).

Okay, okay, actually I keep a readme in `larbs.mom` for my whole system, including the binds here.
Press <kbd>super+F1</kbd> to view it in dwm (zathura is required for that binding).
I haven't kept `man dwm`/`dwm.1` updated though. PRs welcome on that, lol.

## Patches and features

- [Clickable statusbar](https://dwm.suckless.org/patches/statuscmd/) with my build of [dwmblocks](https://github.com/lukesmithxyz/dwmblocks).
- Reads [xresources](https://dwm.suckless.org/patches/xresources/) colors/variables (i.e. works with `pywal`, etc.).
- scratchpad: Accessible with <kbd>mod+shift+enter</kbd>.
- New layouts: bstack, fibonacci, deck, centered master and more. All bound to keys <kbd>super+(shift+)t/y/u/i</kbd>.
- True fullscreen (<kbd>super+f</kbd>) and prevents focus shifting.
- Windows can be made sticky (<kbd>super+s</kbd>).
- [hide vacant tags](https://dwm.suckless.org/patches/hide_vacant_tags/) hides tags with no windows.
- [stacker](https://dwm.suckless.org/patches/stacker/): Move windows up the stack manually (<kbd>super-K/J</kbd>).
- [shiftview](https://dwm.suckless.org/patches/nextprev/): Cycle through tags (<kbd>super+g/;</kbd>).
- [vanitygaps](https://dwm.suckless.org/patches/vanitygaps/): Gaps allowed across all layouts.
- [swallow patch](https://dwm.suckless.org/patches/swallow/): if a program run from a terminal would make it inoperable, it temporarily takes its place to save space.
- [dwm-dynamicswallow-patch](https://dwm.suckless.org/patches/dynamicswallow/): introduces "dynamic" window swallowing to dwm.
- [dwm-alpha](https://dwm.suckless.org/patches/alpha/): Allow dwm to have translucent bars, while keeping all the text on it opaque.
- [pertag](https://dwm.suckless.org/patches/pertag/): More general approach to taglayouts patch. This patch keeps layout, mwfact, barpos and nmaster per tag.
- [defaulttransparency](https://dwm.suckless.org/patches/defaulttransparency/): This patch adds a default transparency parameter to config.h.
- [cfacts](https://dwm.suckless.org/patches/cfacts/): Window resizing bindings in all directions by increasing/decreasing cfact values, per tag.
- [keychord](https://dwm.suckless.org/patches/keychord/dwm-keychord-6.4.diff): Unlocks 2500+ key combos, using only the MODKEY, should be enough for now (until the Keychain patch).
- [barpadding](https://dwm.suckless.org/patches/barpadding/dwm-barpadding-20211020-a786211.diff): Round corners look awkful without it.

## Installation for newbs

```bash
git clone https://github.com/cf-tgg/cf.dwm.git
cd dwm
sudo make install
```

There is also a `PKGBUILD` usable on distributions with pacman. Run `makepkg -si` instead of `sudo make install`.
