#ifndef _URL_H
#define _URL_H

#include <string>

using namespace std;


enum url_scheme {
    SCHEME_HTTP,
    SCHEME_FTP,
    SCHEME_INVALID,
};
class Url
{
public:
    Url();
    ~Url();

    bool parse_url ( string url );
private:
    void parse_scheme ( const char * url );
	bool is_valid_host_char( char ch );
	void parse_url(const char * url,char * protocol,int len_protocol, 
			char * host,int len_host, 
			char * request,int len_request, 
			int * port);
private:
    enum url_scheme m_scheme;
    string m_url;
    string m_host;
    string m_port;
    string m_path;
};

#endif
