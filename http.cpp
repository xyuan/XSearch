#include "http.h"
#include "string.h"
#include "url.h"
#include "commondef.h"

char *userAgent = NULL;
int hideUserAgent = 0;

Http::Http() {}
Http::~Http() {}


int Http::fetch ( string urlString, char ** fileBuf, char ** location, int * sock ) {
    /*
     * Downloads the page
     * Param url: the url string
     * Param fileBuf: the buffer of the file
     * Param location: the locate
     * Param sock: the sock
     * Return : size of download 
     */

    char * url = strdup(urlString.c_str());

    if ( url.empty() ) {
        cout << "url is empty error !" << endl;
        return -1;
    }

    if ( url == NULL ) {
        cout << "url strdup error!" << endl;
        return -1;
    }

    Url curl;
    if ( curl.parseUrl ( url ) == false ) {
        cout << "parse url error! : " << urlString << endl;
        return -1;
    }
    host = curl.m_host.c_str();
    path = curl.m_path.c_str();
    port = curl.m_port;
    if ( !(port > 0) ) {
        port = 80;
    }
    
    int requestBufSize = REQUEST_BUF_SIZE
    char * requestBuffer = (char*)malloc(requestBufSize);
    if ( requestBuffer == NULL  ) {
        if ( url ) {
            free ( url );
            url = NULL;
            cout << "malloc buf size error !" << endl;
            return -1;
        }
    }
    if ( strlen( path ) < 1 ) {
        //it means their's no '/' char in the url ,it is the root url
        int tempSize = strlen("GET /") + strlen(HTTP_VERSION) + 2;
    }


    strcat(requestBuffer,"host:");
    strcat(requestBuffer,host);
    strcat(requestBuffer,"\r\n");
    if ( !hideUserAgent && userAgent == NULL ) {

    }
}

int Http::checkBufSize ( char ** buf, int * bufsize, int more ) {
    /*
     * Judge the bufsize is or not enough , if not grow up it
     * Param buf: the buffer
     * Param bufsize: the size of the buffer
     * Param more: how mutch to grow up
     */
    char * temp;
    int leftSize = *bufsize - ( strlen(*buf) ) + 1;
    if ( leftSize > more ) {
        return 0;
    }
    temp = (char *)realloc(*buf, *bufsize + more + 1);
    if(tmp == NULL) {
        return -1;
    }
    *buf = temp;
    *bufsize += more + 1;
    return 0;
}
