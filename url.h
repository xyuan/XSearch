#ifndef _URL_H
#define _URL_H

#include <string>

using namespace std;
enum url_scheme {
    SCHEME_HTTP,
    SCHEME_FTP,
    SCHEME_INVALID,
};

const unsigned int URL_LEN = 256;
const unsigned int HOST_LEN = 256;
const int DEFAULT_HTTP_PORT = 80;
const int DEFAULT_FTP_PORT = 21;
const char* HEAD_HTTP = "http://";
const char* HEAD_FTP = "ftp://";

class Url
{
public:
    Url() {};
    ~Url() {};

    bool parse_url ( string url );
private:
    void parse_scheme ( const char * url );

private:
    enum url_scheme m_scheme;
    string m_url;
    string m_host;
    string m_port;
    string m_path;
};

#endif
