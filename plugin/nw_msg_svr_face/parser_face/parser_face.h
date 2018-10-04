#include "../global_inc.h"

extern "C"
{
#include <ngx_config.h>
#include <ngx_core.h>
#include <ngx_http.h>
}

#include <stdint.h>
#include <map>
using namespace std;

#ifndef __PARSER_FACE_H__
#define __PARSER_FACE_H__

class DParser_Face
{
public:
	DParser_Face();
	~DParser_Face();

public:
	int parse_msg(ngx_http_request_t* r);
	
protected:
	void splite_args(string& strArgs, map<string, string>& mapArgs);
	int send_reply_header(ngx_http_request_t* r, uint32_t status, uint32_t len_content, const char* content_type);
	int send_reply_content(ngx_http_request_t* r, const char* data, uint32_t len, uint8_t is_last_pack);

private:
	
};

#endif



