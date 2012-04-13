#ifndef _HTTP_H
#define _HTTP_H

#include <map>
#include <string>

using namespace std;

class Http
{
public:
    Http();
    virtual ~Http();
    int fetch( string urlString, char **fileBuf, char **fileHead, char**location, int *sock );
private:
    int readHeader(int sock, char * header );
    int createSocket ( const char * host, int port);
    int checkBufSize ( char ** buf, int * bufsize, int more);
    int nonbConnect ( int sock, struct sockaddr * addr, int sec );
};
#endif
