RSBcam
======

Using an RSB-informer for publishing OpenCV camera pictures and displaying it with an RSB-listener.
Also introducing an own converter for OpenCV "mat" variables.

The project consists out of two programms `capture` and `show`.
`capture` opens the camera device and send the images via in-process to the `/image` scope.
`show` reads from this scope and shows the captured frames on screen.

Compilation hints
-----------------------------------

I used the following software:
* Ubuntu 13.10
* rsb 0.9
* opencv 2.4.7
* cmake version 2.8.11.2

You maybe have to add some symbolic links for rsb 0.9 libraries by running the following commands in `/usr/lib/`:
* `ln -s librsb.so.0.9 librsb.so`
* `ln -s librsc.so.0.9 librsc.so`



Some helpfull links which helped me
-----------------------------------

* [Video capture in RSB](http://docs.cor-lab.de//distributed-computer-vision-with-rsb-tutorial/trunk/html/index.html)
* [Manual for writing converters for RSB](http://docs.cor-lab.org/rsb-manual/trunk/html/examples-writing-converters.html#tutorial-writing-converters)