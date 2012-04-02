#include "url.h"
#include "string.h"
#include "stdio.h"
#include "stdlib.h"
#include <iostream>

using namespace std;

const unsigned int URL_LEN = 256;
const unsigned int HOST_LEN = 256;
const int DEFAULT_HTTP_PORT = 80;
const int DEFAULT_FTP_PORT = 21;
const char* HEAD_HTTP = "http://";
const char* HEAD_FTP = "ftp://";

Url::Url() {
	/*
	 *The Constructor of the Url class
	 *Author: wangxiao
	 *Since: 2012/2
	 */
	this->m_url = ""; //url地址字符串
	this->m_host = ""; //url主机名
	this->m_port = DEFAULT_HTTP_PORT; //默认端口号
	this->m_path = ""; //路径名？
}

Url::~Url() {
	/*
	 *The Destructorr of the Url class
	 *Author: wangxiao
	 *Since: 2012/2
	 */
}

bool Url::parse_url(string url) {
	/*
	 *Split the url to protocol,host,request and port as member variable
	 *Param url: the url string
	 *Return: true or false
	 *Author: WangXiao
	 */
    char protocol[10];
    char host[HOST_LEN];
    char request[256];
    int port = -1;

    memset(protocol,0,sizeof(protocol));
    memset(host,0,sizeof(host));
    memset(request,0,sizeof(request));
	this->parse_scheme( url.c_str() );
	if ( this->m_scheme != SCHEME_HTTP ) {
		return false;
	}
	this->parse_url(url.c_str(),
			protocol,sizeof(protocol),
			host,sizeof(host),
			request,sizeof(request),
			&port);

	cout << protocol << endl;
	cout << host << endl;
	cout << request << endl;
	cout << port << endl;
	return true;
}

void Url::parse_url(const char * url,char * protocol,int len_protocol, 
		char * host,int len_host, char * request,int len_request, int * port) {
	/*
	 *Split the url to protocol,host,request and port and assignmet them
	 *Param url: the url string
	 *Param protocol: the protocol name
	 *Param len_protocol: the length of the protocol
	 *Param host: the host name
	 *Param len_host: the length of the host
	 *Param request: the request name
	 *Param len_request: the length of the request
	 *Param port: the port number
	 *Author: WangXiao
	 */
	int len_url = strlen(url);

	*port = DEFAULT_HTTP_PORT;
	*protocol = 0;
	*host = 0;
	*request = 0;

	char * work_url = new char[len_url+1];
	memset(work_url, 0 , len_url + 1 );
	strncpy(work_url, url, len_url);

	char * ptr;
	ptr = strchr(work_url,':');
	if ( ptr != NULL ) {
		*(ptr++) = 0;
		strncpy( protocol, work_url, ptr - work_url );
	}
	else {
		strncpy( protocol, "HTTP", len_protocol );
		ptr = work_url;
	}
	if ( ( *ptr == '/' ) && (*(ptr + 1) == '/' ) ) {
		ptr += 2;
	}
	char * ptr_host = ptr;
	while ( this->is_valid_host_char(*ptr_host) && *ptr_host ) {
		ptr_host++;
	}
	*ptr_host = 0;
	strncpy ( host, ptr, len_host );
	
	int offset = ptr_host - work_url;
	const char * p_str = url + offset;
	strncpy ( request, p_str, len_request );
	ptr = strchr ( ptr_host,':' );
	if ( ptr != NULL ) {
		*ptr = 0;
		*port = atoi(ptr+1);
	}
	delete []work_url;
	work_url = NULL;
}

bool Url::is_valid_host_char( char ch ){
	/*
	 *Judge that the char is or not a host's valid char
	 *Param ch: an char
	 *Return: true or false
	 */
	return ( isalpha(ch) || isdigit(ch) || ch == '-' || ch == '.' || ch == ':' || ch == '_' );
}

void Url::parse_scheme( const char * url ) {
    //比较url的头部是否是htpp开头或者ftp开头
    if ( strncasecmp ( url, HEAD_HTTP, strlen(HEAD_HTTP) ) == 0 ) {
        this->m_scheme = SCHEME_HTTP;
    }
    else if ( strncasecmp ( url, HEAD_FTP, strlen(HEAD_HTTP) ) == 0 ) {
        this->m_scheme = SCHEME_INVALID;
    }
	else {
		this->m_scheme = SCHEME_INVALID;
	}
	return ;
}
