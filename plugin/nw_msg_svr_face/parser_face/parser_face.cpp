#include "parser_face.h"
#include "../DLogMana/DLogMana.h"

DParser_Face::DParser_Face()
{
	LOG(INFO) << "DParser_Face::DParser_Face\n";
}

DParser_Face::~DParser_Face()
{
	LOG(INFO) << "DParser_Face::~DParser_Face\n";
}

int DParser_Face::parse_msg(ngx_http_request_t* r)
{
	assert(r);

	ngx_chain_t out;

	if (!r->args.data || r->args.len == 0)
		return NGX_HTTP_BAD_REQUEST;

	string strArgs(r->args.data, r->args.len);

	map<string, string> mapArgs;
	splite_args(strArgs, mapArgs);

//	map<string, string>::iterator it = mapArgs.begin();
//	for(; it != mapArgs.end(); ++it)
//	{
//		LOG(INFO) << it->first << ":" << it->second << endl;
//	} 
//

	char *pstr = "hello nginx";
	char *pstr1 = "\t by xuhai.duan@nexwise";
	char *pstr2 = "\r\n2018-09-22";
	char* content_type = "text/plain";

	int ret = send_reply_header(r, NGX_HTTP_OK, strlen(pstr)+strlen(pstr1)+strlen(pstr2), content_type);
	if (ret != 0)
		return ret;

	ret = send_reply_content(r, pstr, strlen(pstr), 0);
	if (ret != 0)
		return ret;
	ret = send_reply_content(r, pstr1, strlen(pstr1), 0);
	if (ret != 0)
		return ret;
	ret = send_reply_content(r, pstr2, strlen(pstr2), 1);
	if (ret != 0)
		return ret;

	return ret;

	//char *pstr = "hello nginx";
	//char *pstr1 = "\t by xuhai.duan@nexwise";
	//int len_str = strlen(pstr);
	//int len_str1 = strlen(pstr1);

	//r->headers_out.status = NGX_HTTP_OK;
	//r->headers_out.content_length = len_str+len_str1;
	//r->headers_out.content_type = (ngx_str_t)ngx_string("text/plain");

	//ngx_int_t ret = ngx_http_send_header(r);
	//if (ret != 0)
	//	return ret;

	//ngx_buf_t *buf = ngx_create_temp_buf(r->pool, len_str);
	//if (!buf)
	//	return NGX_HTTP_INTERNAL_SERVER_ERROR;

	//ngx_memcpy(buf->pos, pstr, len_str);
	//buf->last = buf->pos + len_str;
	//buf->last_buf = 0;
	//
	//out.buf = buf;
	//out.next = NULL;

	//ngx_http_output_filter(r, &out);

	//buf = ngx_create_temp_buf(r->pool, len_str1);
	//ngx_memcpy(buf->pos, pstr1, len_str1);
	//buf->last = buf->pos + len_str1;
	//buf->last_buf = 1;

	//out.buf = buf;
	//out.next = NULL;
	//
	//return ngx_http_output_filter(r, &out); 
}

void DParser_Face::splite_args(string& strArgs, map<string, string>& mapArgs)
{
	mapArgs.clear();
	if (strArgs.empty())
		return ;

	bool fin = false;
	
	while (1)
	{
		string::size_type pos = strArgs.find("&");
		string temp;
		
		if (pos == string::npos)
			fin = true;
		temp = strArgs.substr(0, pos);
		
		string::size_type pos1 = temp.find("=");
		if (pos1 != string::npos)
		{
			string key(temp, 0, pos1);
			string val(temp, pos1+1);
			mapArgs.insert(make_pair(key, val));
		}
		if (fin)
		{
			strArgs = "";
			break;
		}

		strArgs = strArgs.substr(pos+1, string::npos); 
	}
}

int DParser_Face::send_reply_header(ngx_http_request_t* r, uint32_t status, uint32_t len_content, const char* content_type)
{
	assert(r && content_type);
	r->headers_out.status = status;
	r->headers_out.content_length = len_content;
//	r->headers_out.content_type = (ngx_str_t)ngx_string(content_type);
	r->headers_out.content_type.data = content_type;
	r->headers_out.content_type.len = strlen(content_type);

	return ngx_http_send_header(r);
}

int DParser_Face::send_reply_content(ngx_http_request_t* r, const char* data, uint32_t len, uint8_t is_last_pack)
{
	assert(r && data);

	ngx_chain_t chain;
	ngx_buf_t *buf = ngx_create_temp_buf(r->pool, len);

	if (!buf)
		return NGX_HTTP_INTERNAL_SERVER_ERROR;

	ngx_memcpy(buf->pos, data, len);
	buf->last = buf->pos + len;
	buf->last_buf = is_last_pack ? 1 : 0;

	chain.buf = buf;
	chain.next = NULL;

	return ngx_http_output_filter(r, &chain); 
}
