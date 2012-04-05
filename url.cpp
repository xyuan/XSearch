#include "url.h"
#include "string.h"
#include "stdio.h"
#include "stdlib.h"
#include <iostream>
#include <map>
#include <arpa/inet.h>

using namespace std;

const unsigned int URL_LEN = 256;
const unsigned int HOST_LEN = 256;
const int DEFAULT_HTTP_PORT = 80;
const int DEFAULT_FTP_PORT = 21;
const char* HEAD_HTTP = "http://";
const char* HEAD_FTP = "ftp://";

map<string,string> hostCacheMap;
pthread_mutex_t mutexCacheHost = PTHREAD_MUTEX_INITIALIZER;

Url::Url() {
	/* 
         * The Constructor of the Url class
	 * Author: wangxiao
	 * Since: 2012/2
	 */
	this->m_url = ""; //url地址字符串
	this->m_host = ""; //url主机名
	this->m_port = DEFAULT_HTTP_PORT; //默认端口号
	this->m_path = ""; //路径名？
}

Url::~Url() {
	/* 
         * The Destructorr of the Url class
	 * Author: wangxiao
	 * Since: 2012/2
	 */
}

bool Url::parse_url(string url) {
    /* 
     * Split the url to protocol,host,request and port as member variable
     * Param url: the url string
     * Return: true or false
     * Author: WangXiao
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
    return true;
}

void Url::parse_url(const char * url,char * protocol,int len_protocol, 
		char * host,int len_host, char * request,int len_request, int * port) {
	/*
	 * Split the url to protocol,host,request and port and assignmet them
	 * Param url: the url string
	 * Param protocol: the protocol name
	 * Param len_protocol: the length of the protocol
	 * Param host: the host name
	 * Param len_host: the length of the host
	 * Param request: the request name
	 * Param len_request: the length of the request
	 * Param port: the port number
	 * Author: WangXiao
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
	 * Judge that the char is or not a host's valid char
	 * Param ch: an char
	 * Return: true or false
	 */
	return ( isalpha(ch) || isdigit(ch) || ch == '-' || ch == '.' || ch == ':' || ch == '_' );
}

void Url::parse_scheme( const char * url ) {
    /*
     * Judge the url's Head is Http or not
     */
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

bool Url::isValidHost(const char * host) {
	if( !host || strlen(host) < 6 ){
		return false;
	}
	char ch;
	for(unsigned int i=0; i<strlen(host); i++){
		ch = *(host++);
		if( !is_valid_host_char(ch) ){
			return false;
		}
	}
	return true;
}

char * Url::getIpByHost( const char * host ) {
    /*
     * Get the ip address from the host name
     * Param host: the host name
     * Return: the ip address name
     */
    if ( !host || !isValidHost(host) ) {
        return NULL;
    }
    unsigned long inaddr = 0;
    char * result = NULL;
    int len = 0;
    inaddr = (unsigned long)inet_addr(host);
    if ( inaddr != INADDR_NONE ) {
        //host is the ip address
        len = strlen(host);
	result = new char[len+1];
	memset(result, 0, len+1);
	memcpy(result, host, len);
	return result;
    }
    else {
        map<string,string>::iterator mIter = hostCacheMap.find(host);
        if ( mIter != hostCacheMap.end() ) {
            const char * ipAddress;
            ipAddress =  mIter->second.c_str();
            inaddr = (unsigned long)inet_addr(ipAddress);
            if ( inaddr != INADDR_NONE ) {
                len = strlen(host);
                result = new char[len+1];
                memset(result, 0, len+1);
                memcpy(result, host, len);
                return result;
            }
        }
    }
    //cache the host into map
    struct hostent * hostTent;
    hostTent = gethostbyname(host);
    if ( hostTent == NULL ) {
        return NULL;
    }
    struct in_addr inAddr;
    bcopy(*(hostTent->h_addr_list),(caddr_t)& inAddr, hostTent->h_length);
    char abuf[INET_ADDRSTRLEN];
    if ( inet_ntop(AF_INET,(void *)&inAddr,abuf,sizeof(abuf)) == NULL ) {
        return NULL;
    }
    else {
        pthread_mutex_lock(&mutexCacheHost);
        if( hostCacheMap.find(host) == mapCacheHostLookup.end() ){
            hostCacheMap.insert( valTypeCHL ( host, abuf) );
        }
        pthread_mutex_unlock(&mutexCacheHost);
    }
    len = strlen(abuf);
    result = new char[len+1];
    memset( result, 0, len+1 );
    memcpy( result, abuf, len );
    return result;
}

bool Url::isForeignHost(string host)
{
	if( host.empty() ) {
            return true;
        }
	if( host.size() > HOST_LEN ) {
            return true;
        }

	unsigned long inaddr = 0;

	inaddr = (unsigned long)inet_addr( host.c_str() );
	if ( inaddr != INADDR_NONE) {
		return false;
	}

	string::size_type idx = host.rfind('.');
	string tmp;
	if( idx != string::npos ){
		tmp = host.substr(idx+1);
	}

	CStrFun::Str2Lower( tmp, tmp.size() );
	const char *home_host[] ={
		"cn","com","net","org","info",
		"biz","tv","cc", "hk", "tw"
	};

	int home_host_num = 10;

	for(int i=0; i<home_host_num; i++){
		if( tmp == home_host[i] )
			return false;
	}

	return true;
}
	
	
bool CUrl::IsImageUrl(string url)
{
	if( url.empty() ) return false;
	if( url.size() > HOST_LEN ) return false;

	string::size_type idx = url.rfind('.');
	string tmp;
	if( idx != string::npos ){
		tmp = url.substr(idx+1);
	}

	CStrFun::Str2Lower( tmp, tmp.size() );
	const char *image_type[] ={
		"gif","jpg","jpeg","png","bmp",
		"tif","psd"
	};

	int image_type_num = 7;

	for (int i=0; i<image_type_num; i++)
	{
		if( tmp == image_type[i] )
			return true;
	}

	return false;
}

