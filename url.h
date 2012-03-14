#include <string>

using namespace std;


enum url_schema {
    SCHEME_HTTP;
    SCHEME_FTP;
    SCHEME_INVALID;
};

const unsigned int URL_LEN = 256;
const unsigned int HOST_LEN = 256;
const int DEFAULT_HTTP_PORT = 80;
const int DEFAULT_FTP_PORT = 21;


class Url
{
public:
    Url();
    ~Url();

    bool parse_url ( string url );
private:
    string url;
    string host;
    string port;
    string path;

}
