# dwm

My fork of [dwm](https://dwm.suckless.org) :)

![Preview of my dwm](preview.png)

### Patches Applied
1. [bulkill](https://dwm.suckless.org/patches/bulkill/dwm-bulkill-20231029-9f88553.diff)
2. [restartsig](https://dwm.suckless.org/patches/restartsig/dwm-restartsig-20180523-6.2.diff)
3. [restoreafterrestart](https://dwm.suckless.org/patches/restoreafterrestart/dwm-restoreafterrestart-20220709-d3f93c7.diff)
4. [focusmonmouse](https://dwm.suckless.org/patches/focusmonmouse/dwm-focusmonmouse-6.2.diff)
5. [hide_vacant_tags](https://dwm.suckless.org/patches/hide_vacant_tags/)
6. [focusfullscreen](https://dwm.suckless.org/patches/focusfullscreen/dwm-focusfullscreen-20211121-95e7342.diff)
7. [stacker](https://dwm.suckless.org/patches/stacker/dwm-stacker-6.6.diff)
8. [sticky](https://dwm.suckless.org/patches/sticky/dwm-sticky-6.5.diff)
9. [vanitygaps](https://dwm.suckless.org/patches/vanitygaps/dwm-vanitygaps-6.2.diff)
10. [cyclelayouts](https://dwm.suckless.org/patches/cyclelayouts/dwm-cyclelayouts-20180524-6.2.diff)
11. [focusmaster](https://dwm.suckless.org/patches/focusmaster/dwm-focusmaster-return-6.2.diff)
12. [xrdb](https://dwm.suckless.org/patches/xrdb/dwm-xrdb-6.4.diff)
13. [colorbar](https://dwm.suckless.org/patches/colorbar/dwm-colorbar-6.3.diff)
14. [alpha](https://dwm.suckless.org/patches/alpha/dwm-alpha-20250918-74edc27.diff)
15. [statuscmd](https://dwm.suckless.org/patches/statuscmd/dwm-statuscmd-20241009-8933ebc.diff)
16. [pango](https://dwm.suckless.org/patches/pango/dwm-pango-20230520-e81f17d.diff)

Apart from this, I have patched it slightly here and there, like making the font heignt customisable with pango.

### Getting started

If dwm is your first experience with tiling window manager, I would suggest installing the [restartsig](https://dwm.suckless.org/patches/restartsig/dwm-restartsig-20180523-6.2.diff) patch first which makes testing the changes easier.

If you are like me, you will love the process of building your version of dwm. The code is not that complicated. It will all connect if you spend a few days getting familiar with the code. I have a small [blog post](https://bytesnbessy.org/posts/what-happens-when-you-press-a-key) on how hotkeys work in dwm which may also help

### Installation
```bash
git clone https://github.com/arvindpz/dwm
cd dwm
sudo make clean install
```

> [!WARNING]
> I occasionally face some issues when I am running picom and play some videos on my browser. My computer becomes less snappy. I didn't get time to look into it, but stopping picom and restarting dwm should resolve the issue

