extern "C"
{
#include <ngx_config.h>
#include <ngx_core.h>
#include <ngx_http.h>
}
#include "parser_face.h"
#include "DLogMana.h"

static DLogMana LogMana("./commu-logs/", "nw_msg_svr_face");
DParser_Face parser_face;

static char* module_conf(ngx_conf_t* cf, ngx_command_t* module_cmds, void* conf);
static ngx_int_t msg_handler(ngx_http_request_t *req); 

static ngx_command_t module_cmds[] = 
{
	{
		ngx_string("nw_msg_svr_face"),
		NGX_HTTP_LOC_CONF | NGX_CONF_NOARGS,
		module_conf,
		NGX_HTTP_LOC_CONF_OFFSET,
		0,
		NULL
	},
	ngx_null_command
};

static ngx_http_module_t ctx_module = 
{
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL
};

ngx_module_t nw_msg_svr_face = 
{
	NGX_MODULE_V1,
	&ctx_module,
	module_cmds,
	NGX_HTTP_MODULE,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NGX_MODULE_V1_PADDING
};


static char* module_conf(ngx_conf_t* cf, ngx_command_t* module_cmds, void* conf)
{
	ngx_http_core_loc_conf_t *clcf;
	
	clcf = ngx_http_conf_get_module_loc_conf(cf, ngx_http_core_module);
	clcf->handler = msg_handler;

	return NGX_CONF_OK;
}

static ngx_int_t msg_handler(ngx_http_request_t *req)
{ 
	char remote_addr[32] = {0};
	memcpy(remote_addr, req->connection->addr_text.data, req->connection->addr_text.len);
	LOG(INFO) << "recv request from:" << remote_addr << endl;

	return parser_face.parse_msg(req); 
}
