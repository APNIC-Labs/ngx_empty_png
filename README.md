Overview
========

`ngx_empty_png` is a module that exposes `empty_png`:  the 63 byte empty png.

built on

http://nginx.org/en/docs/http/ngx_http_empty_gif_module.html

Build
=====

  * Configure and nginx with `--add-module=path/to/ngx_txserial`

Example
=======

	location /1x1.png {
            empty_png;
        }

```

Background
==========

empty_gif is 43 bytes. but we have a large namespace using a 1x1.png. we wanted a png.

Technique
=========

get an empty png off the net, with the obvious google search. od -x the bits to get a hexdump

embed in the array.

s/gif/png/ in the original sourcecode
