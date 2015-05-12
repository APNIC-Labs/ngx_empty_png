
/*
 * Copyright (C) Igor Sysoev
 * Copyright (C) Nginx, Inc.
 */

#include <ngx_config.h>
#include <ngx_core.h>
#include <ngx_http.h>


static char *ngx_empty_png(ngx_conf_t *cf, ngx_command_t *cmd,
    void *conf);

static ngx_command_t  ngx_empty_png_commands[] = {

    { ngx_string("empty_png"),
      NGX_HTTP_LOC_CONF|NGX_CONF_NOARGS,
      ngx_empty_png,
      0,
      0,
      NULL },

      ngx_null_command
};


/* the minimal single pixel transparent png, 63 bytes */

static u_char  ngx_the_empty_png[] = {
0x89,0x50, 0x4e,0x47, 0x0d,0x0a, 0x1a,0x0a,
0x00,0x00, 0x00,0x0d, 0x49,0x48, 0x44,0x52,
0x00,0x00, 0x00,0x01, 0x00,0x00, 0x00,0x01,
0x08,0x06, 0x00,0x00, 0x00,0x1f, 0x15,0xc4,
0x89,0x00, 0x00,0x00, 0x0a,0x49, 0x44,0x41,
0x54,0x78, 0x9c,0x63, 0x00,0x01, 0x00,0x00,
0x05,0x00, 0x01,0x0d, 0x0a,0x2d, 0xb4,0x00,
0x00,0x00, 0x00,0x49, 0x45,0x4e, 0x44,0xae,
0x42,0x60, 0x82,0x00

/*
$ od -c blank.png
0000000  211   P   N   G  \r  \n 032  \n  \0  \0  \0  \r   I   H   D   R
0000020   \0  \0  \0 001  \0  \0  \0 001  \b 006  \0  \0  \0 037 025   ĉ
0000040   **  \0  \0  \0  \n   I   D   A   T   x 234   c  \0 001  \0  \0
0000060  005  \0 001  \r  \n   - 264  \0  \0  \0  \0   I   E   N   D 256
0000100    B   ` 202
0000103
$ od -x blank.png
0000000      5089    474e    0a0d    0a1a    0000    0d00    4849    5244
0000020      0000    0100    0000    0100    0608    0000    1f00    c415
0000040      0089    0000    490a    4144    7854    639c    0100    0000
0000060      0005    0d01    2d0a    00b4    0000    4900    4e45    ae44
0000100      6042    0082
0000103
$
*/

};


static ngx_http_module_t  ngx_empty_png_module_ctx = {
    NULL,                          /* preconfiguration */
    NULL,                          /* postconfiguration */

    NULL,                          /* create main configuration */
    NULL,                          /* init main configuration */

    NULL,                          /* create server configuration */
    NULL,                          /* merge server configuration */

    NULL,                          /* create location configuration */
    NULL                           /* merge location configuration */
};


ngx_module_t  ngx_empty_png_module = {
    NGX_MODULE_V1,
    &ngx_empty_png_module_ctx, /* module context */
    ngx_empty_png_commands,   /* module directives */
    NGX_HTTP_MODULE,               /* module type */
    NULL,                          /* init master */
    NULL,                          /* init module */
    NULL,                          /* init process */
    NULL,                          /* init thread */
    NULL,                          /* exit thread */
    NULL,                          /* exit process */
    NULL,                          /* exit master */
    NGX_MODULE_V1_PADDING
};


static ngx_str_t  ngx_png_type = ngx_string("image/png");


static ngx_int_t
ngx_empty_png_handler(ngx_http_request_t *r)
{
    ngx_http_complex_value_t  cv;

    if (!(r->method & (NGX_HTTP_GET|NGX_HTTP_HEAD))) {
        return NGX_HTTP_NOT_ALLOWED;
    }

    ngx_memzero(&cv, sizeof(ngx_http_complex_value_t));

    cv.value.len = sizeof(ngx_the_empty_png);
    cv.value.data = ngx_the_empty_png;
    r->headers_out.last_modified_time = 23349600;

    return ngx_http_send_response(r, NGX_HTTP_OK, &ngx_png_type, &cv);
}


static char *
ngx_empty_png(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
{
    ngx_http_core_loc_conf_t  *clcf;

    clcf = ngx_http_conf_get_module_loc_conf(cf, ngx_http_core_module);
    clcf->handler = ngx_empty_png_handler;

    return NGX_CONF_OK;
}
