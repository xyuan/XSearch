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
    //constructed function
    Url();
    ~Url();

    //public functions
    bool parseUrl ( string url );
    char * getIpByHost ( const char * host );
    bool isForeignHost ( string host );
    bool isImageUrl ( string url );

    //the functions to get the member variable
    string getUrl() { return this->m_url; }
    string getHost() { return this->m_host; }
    int getPort() { return this->m_port; }
    string getPath() { return this->m_path; }

private:
    //private functions
    void parseScheme ( const char * url );
    bool isValidHostChar( char ch );
    void parseUrl(const char * url,char * protocol,int len_protocol, 
                    char * host,int len_host, 
                    char * request,int len_request, 
                    int * port);
    bool isValidHost ( const char * host );
    bool isUnVisitedUrl ( const char * url );
    bool isVisitedUrl ( const char * url );

public:
    //member variable
    enum url_scheme m_scheme;
    string m_url;
    string m_host;
    int m_port;
    string m_path;
};

#endif
