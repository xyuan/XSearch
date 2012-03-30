#include "url.h"

bool Url::parse_url(string url)
{
    char protocol[10]; //协议
    char host[HOST_LEN]; //主机
    char request[256]; //请求
    int port = -1;

    memset(protocol,0,sizeof(protocol));
    memset(host,0,sizeof(host));
    memset(request,0,sizeof(request));
}

void Url::parse_scheme( const char * url ) {
    //比较url的头部是否是htpp开头或者ftp开头
    if ( strncasecmp ( url, HEAD_HTTP, strlen(HEAD_HTTP) ) == 0 ) {
        this->m_scheme = SCHEME_HTTP;
    }
    else if ( strncasecmp ( url, HEAD_FTP, strlen(HEAD_HTTP) ) == 0 ) {
        this->m_scheme = SCHEME_INVALID;
    }
    this->m_scheme = SCHEME_INVALID;
}
