#include "http.h"
#include "string.h"
#include "url.h"
#include "commondef.h"

char *userAgent = NULL;
int hideUserAgent = 0;

Http::Http() {}
Http::~Http() {}


int Http::fetch ( string urlString, char ** fileBuf, char ** location, int * psock ) {
    /*
     * Downloads the page
     * Param url: the url string
     * Param fileBuf: the buffer of the file
     * Param location: the locate
     * Param sock: the sock
     * Return : size of download 
     */

    char * url = strdup(urlString.c_str());
    int sock;

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
    
    int requestBufferSize = REQUEST_BUF_SIZE
    char * requestBufferfer = (char*)malloc(requestBufferSize);
    if ( requestBufferfer == NULL  ) {
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
        if ( checkBufSize(&requestBufferfer, &requestBufferSize, tempSize) || 
                snprintf( requestBufferfer, requestBufferSize, "GET / %s\r\n",HTTP_VERSION) < 0 ) {
            if ( url ) {
                free(url);
                url = NULL;
            }
            if ( requestBufferfer ) {
                free(requestBufferfer);
                requestBufferfer = NULL;
            }
            cout << "1.check buffer size (request buf ) error !" << endl;
            return -1;
        }
    }
    else {
        tempSize = strlen("GET ") + strlen(path) + strlen(HTTP_VERSION) + 4;
        if ( checkBufSize(&requestBufferfer, &requestBufferSize, tempSize) || 
                snprintf( requestBufferfer, requestBufferSize, "GET / %s %s\r\n",path,HTTP_VERSION) < 0 ) {
            if ( url ) {
                free(url);
                url = NULL;
            }
            if ( requestBufferfer ) {
                free(requestBufferfer);
                requestBufferfer = NULL;
            }
            cout << "2.check buffer size (request buf ) error !" << endl;
            return -1;
        }
    }
    tempSize = (int)strlen("Host: ") + (int)strlen(host) + 3;
    if ( checkBufSize(&requestBufferfer, &requestBufferSize, tempSize + 128 )) {
        if ( url ) {
            free(url);
            url = NULL;
        }
        if ( requestBufferfer ) {
            free(requestBufferfer);
            requestBufferfer = NULL;
        }
        cout << "3.check buffer size (request buf ) error !" << endl;
        return -1;
    }

    strcat(requestBufferfer,"host:");
    strcat(requestBufferfer,host);
    strcat(requestBufferfer,"\r\n");
    if ( !hideUserAgent && userAgent == NULL ) {
        tempSize = (int)strlen("User-Agent: ") + 
            (int)strlen(DEFAULT_USER_AGENT ) +
            (int)strlen(VERSION) + 4;
        if ( checkBufSize(&requestBufferfer, &requestBufferSize, tempSize )) {
            if ( url ) {
                free(url);
                url = NULL;
            }
            if ( requestBufferfer ) {
                free(requestBufferfer);
                requestBufferfer = NULL;
            }
            cout << "4.check buffer size (request buf ) error !" << endl;
            return -1;
        }
        strcat(requestBufferfer, "User-Agent: ");
        strcat(requestBufferfer, DEFAULT_USER_AGENT);
        strcat(requestBufferfer, "/");
        strcat(requestBufferfer, VERSION);
        strcat(requestBufferfer, "\r\n");
    }
    else if ( !hideUserAgent ) {
        tempSize = (int)strlen("User-Agent: ") + (int)strlen(userAgent) + 3;
        if ( checkBufSize(&requestBufferfer, &requestBufferSize, tempSize )) {
            if ( url ) {
                free(url);
                url = NULL;
            }
            if ( requestBufferfer ) {
                free(requestBufferfer);
                requestBufferfer = NULL;
            }
            cout << "5.check buffer size (request buf ) error !" << endl;
            return -1;
        }

        strcat(requestBufferfer, "User-Agent: ");
        strcat(requestBufferfer, userAgent);
        strcat(requestBufferfer, "\r\n");
    }

    tempSize = (int)strlen("Connection: Keep-Alive\r\n\r\n");
    if ( checkBufSize(&requestBufferfer, &requestBufferSize, tempSize )) {
        if ( url ) {
            free(url);
            url = NULL;
        }
        if ( requestBufferfer ) {
            free(requestBufferfer);
            requestBufferfer = NULL;
        }
        cout << "6.check buffer size (request buf ) error !" << endl;
        return -1;
    }
    strcat(requestBufferfer, "Connection: Keep-Alive\r\n\r\n");

    temp = (char *)realloc(requestBuffer, strlen(requestBuffer) + 1);
    if(tmp == NULL){
        if (url) {
            free(url); 
            url=NULL;
        }
        if (requestBuffer)
        {
            free(requestBuffer);
            requestBuffer=NULL;
        }
        cout << "realloc for temp error" << endl;
        return -1;
    }
    requestBufferfer = temp;

    if ( *psock != -1 ) {
        sock = *psock;
        cout << "using pre socket" << endl;
    }
    else {
        sock = createSocket ( host , port );
        if ( sock == -1 ) {
            if (url)
            {
                free(url); 
                url=NULL;
            }
            if (requestBuffer)
            {
                free(requestBuffer);
                requestBuffer=NULL;
            }
            return -3;
        }
        if ( sock == -2 ) {
            if (url)
            {
                free(url); 
                url=NULL;
            }
            if (requestBuffer)
            {
                free(requestBuffer);
                requestBuffer=NULL;
            }
            return -2;
        }
    }

    ret = write ( sock, requestBufferfer, strlen(requestBufferfer) );

    if ( ret == 0 ) {
        cout << "requestBufferfer is " << requestBuffer << endl;
        cout << "write nothing" << endl;
        if (url)
        {
            free(url); 
            url=NULL;
        }
        if (requestBuffer)
        {
            free(requestBuffer);
            requestBuffer=NULL;
        }
        close(sock);
        *psock = -1;
        return -1;
    }
    if ( ret == -1 ) {
        close(sock);
        *psock = -1;
        cout << "2.close pre socket " << *psock << "and get new one " << endl;
        sock = createSocket ( host, port );
        if ( sock == -1 ) {
            if (url)
            {
                free(url); 
                url=NULL;
            }
            if (requestBuffer)
            {
                free(requestBuffer);
                requestBuffer=NULL;
            }
            cout << "3.not able to MakeSocket" << endl;
            return -1;
        }
        if ( sock == -2 ) {
            if (url)
            {
                free(url); 
                url=NULL;
            }
            if (requestBuffer)
            {
                free(requestBuffer);
                requestBuffer=NULL;
            }
            cout << "4.not able to MakeSocket" << endl;
            return -1;
        }
        if ( write (sock, requestBufferfer, strlen(requestBufferfer)) == -1 ) {
            if (url)
            {
                free(url); 
                url=NULL;
            }
            if (requestBuffer)
            {
                free(requestBuffer);
                requestBuffer=NULL;
            }
            close(sock);
            *psock = -1;
            return -1;
            cout << "write error!" << endl;
        }
    }
    if (url)
    {
        free(url); 
        url=NULL;
    }
    if (requestBuffer)
    {
        free(requestBuffer);
        requestBuffer=NULL;
    }
    char headerBuf[HEADER_BUF_SIZE];
    memset ( headerBuf, 0 , HEADER_BUF_SIZE );
    ret = readHeader ( sock, headerBuf );
    if ( ret < 0 ) {
        close ( sock );
        *psock = -1;
        return -1;
    }
    if ( strlen(headerBuf) == 0 ) {
        cout << "header buf == 0" << headerBuf << endl;
        cout << "url:" << url << endl << endl;
        close ( sock );
        *psock = -1;
        return -1;
    }
    Page page;
    page.parseHeaderInfo ( headerBuf );
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

int Http::createSocket ( const char * host, int port ) {
    /*
     * Create a new socket from hsot and port
     * Param host: the host name
     * Param port: the port num
     * Return: if error return -1
     */
    int sock;
    struct sockaddr_in sockAddr;
    unsigned long inaddr;
    int ret;

    Url url;
    char * ip = url.getIpByHost(host);
    if ( ip == NULL ) {
        return -1;
    }
    else {
        if ( url.isValidIp(ip) ) {
            inaddr = (unsigned long)inet_addr(ip);
            if( inaddr == INADDR_NONE ){
                delete [] ip; 
                ip = NULL;
                cout << "invalid ip " << ip << endl;
                return -1;
            }
            memcpy((char *)&sockAddr.sin_addr, (char *)&inaddr, sizeof(inaddr));
            delete [] ip; ip = NULL;
        }
        else {
            delete [] ip; ip = NULL;
            return -2;
        }
    }

    sockAddr.sin_family = AF_INET;
    sockAddr.sin_port = htons(port);	//Put portnum into sockaddr
    sock = -1;
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock < 0 ) { 
        cout << "socket() in CreateSocket" << endl;
        return -1;
    }

    int optval = 1;
    if (setsockopt (sock, SOL_SOCKET, SO_REUSEADDR,(char *)&optval, sizeof (optval)) < 0){
        cout << "setsockopt() in CreateSocket" << endl;
        close(sock);
        return -1;
    }

    ret = this->nonbConnect(sock, (struct sockaddr *)&sockAddr, DEFAULT_TIMEOUT);
    if(ret == -1) { 
        cout << "nonb_connect() in CreateSocket" << endl;
        close(sock);
        return -1; 
    }
    return sock;
}

int Http::nonbConnect(int sock,struct sockaddr* sockAddr,int sec)
{
    /*
     * Create a none blocking connect socket
     * Param sock: the socket
     * Param sockAddr: the sock address
     * Param sec: the timout
     * Return: -1 if create error
     */
    int flags
    int status;
    fd_set mask;
    struct timeval timeout;

    //set the socket as nonblocking
    flags=fcntl(sock,F_GETFL,0);
    if(flags<0) {
        return -1;
    }
    flags|=O_NONBLOCK;
    if(fcntl(sock,F_SETFL,flags) < 0){
        cout << "1.fcntl() in nonb_connect" << endl;
        return -1;
    }

    if( connect(sock,sockAddr,sizeof(struct sockaddr)) == 0){
        flags&=~O_NONBLOCK;
        fcntl(sock,F_SETFL,flags);
        return sock;
    }

    FD_ZERO(&mask);
    FD_SET(sock,&mask);
    timeout.tv_sec=sec;
    timeout.tv_usec=0;
    status=select(sock+1,NULL,&mask,NULL,&timeout);

    switch(status) {
        case -1:    // Select error, set the socket as default blocking
            flags&=~O_NONBLOCK;
            fcntl(sock,F_SETFL,flags);
            cout << "2.fcntl() in nonb_connect" << endl;
            return -1;
        case 0:     //Connection timed out.
            flags&=~O_NONBLOCK;
            fcntl(sock,F_SETFL,flags);
            cout << "3.fcntl() in nonb_connect" << endl;
            return -1;
        default:    // Connected successfully.
            FD_CLR(sock,&mask);
            flags&=~O_NONBLOCK;
            fcntl(sock,F_SETFL,flags);
            return 0;
    }
}

int Http::readHeader ( int sock, char * header ) {
    /*
     * Read the header info
     * Param sock: the socket
     * Param header: the header string
     * Return: -1 if error
     */
    fd_set rfds;
    struct timeval tv;
    int bytesRead = 0, newlines = 0, ret, selectRet;

    int flags;

    flags=fcntl(sock,F_GETFL,0);
    if(flags<0){
        cout << "1.fcntl() in read_header()< 0" << endl;
        return -1;
    }

    flags|=O_NONBLOCK;
    if(fcntl(sock,F_SETFL,flags)<0){
        cout << "2.fcntl() < 0 in read_header()" << endl;
        return -1;
    }

    while(newlines != 2 && bytesRead != HEADER_BUF_SIZE-1) {
        FD_ZERO(&rfds);
        FD_SET(sock, &rfds);
        tv.tv_sec = timeout;
        tv.tv_usec = 0;

        if(timeout >= 0) {
            selectRet = select(sock+1, &rfds, NULL, NULL, &tv);
        }
        else { 
            selectRet = select(sock+1, &rfds, NULL, NULL, NULL);
        }
        if(selectRet == 0 && timeout < 0) {
            cout << "selectRet == 0 && timeout < 0" << endl;
            return -1;
        }
        else if(selectRet == -1) {
            cout << "selectRet == 0 && timeout < 0 else" << endl;
            return -1;
        }
        ret = read(sock, header, 1);
        if(ret == -1){
            cout << "!error: read() in read_header()" << endl;
            return -1;
        }

        bytesRead++;
        if(*header == '\r') {
            header++;
            continue;
        }
        else if(*header == '\n') {
            newlines++;
        else {    
            newlines = 0;
        }
        header++;
    }
    
    header -= 2;
    *header = '\0';
    return bytesRead;
}
