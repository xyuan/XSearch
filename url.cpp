#include "url.h"

using namespace std;

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
    if ( strncasecmp ( url, LEAD_HTTP, strlen(LEAD_HTTP) ) == 0 ) {
        this->m_scheme = SCHEME_HTTP;
    }
    else if ( strncasecmp ( url, LEAD_FTP, strlen(LEAD_HTTP) ) == 0 ) {
        this->m_scheme = SCHEME_INVALID;
    }
    this->m_scheme = SCHEME_INVALID;
}
