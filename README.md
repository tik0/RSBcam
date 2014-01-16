RSBcam
======

Using an RSB-informer for publishing OpenCV camera pictures from the BeBot and displaying it with an RSB-listener on a remote PC.
Also introducing an own converter for OpenCV "mat" variables.

The project consists out of two programms `capture` and `show`.
`capture` opens the camera device "/dev/video3" and send the images via socket transport to the `/image` scope. (view rsb.conf for setup)
`show` reads from this scope and shows the captured frames on screen. (This is the socket server and has to be run first (view rsb.conf for setup))

Compilation hints
-----------------------------------

I used the following software:
* Ubuntu 13.10
* rsb 0.9
* opencv 2.4.7
* cmake version 2.8.11.2

You maybe have to add some symbolic links for rsb 0.9 libraries by running the following commands in `/usr/lib/`:
* `ln -s librsb.so.0.9 librsb.so`
* `ln -s librsc0.9.so.0.9 librsc.so`



Some helpfull links which helped me
-----------------------------------

* [Video capture in RSB](http://docs.cor-lab.de//distributed-computer-vision-with-rsb-tutorial/trunk/html/index.html)
* [Manual for writing converters for RSB](http://docs.cor-lab.org/rsb-manual/trunk/html/examples-writing-converters.html#tutorial-writing-converters)
