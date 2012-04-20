#ifndef _COMMON_DEF_H
#define _COMMON_DEF_H

#define HTTP_VERSION "HTTP/1.0"
#define DEFAULT_USER_AGENT "Tse"
#define VERSION	"1.0"
const int REQUEST_BUF_SIZE = 1024;


const int HEADER_BUF_SIZE = 1024;
const int DEFAULT_PAGE_BUF_SIZE = 1024 * 200;
const int MAX_PAGE_BUF_SIZE = 5 * 1024 * 1024;
const int DEFAULT_TIMEOUT = 30; 
extern map<string,string> hostCacheMap;
extern map<unsigned long,unsigned long> mapIpBlock;
//typedef map<unsigned long,unsigned long>::value_type valTypeIpBlock;
//extern set<string> setVisitedUrlMd5;

#endif
