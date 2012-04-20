#include "Crawler.h"
#include "xsearch.h"
#include "url.h"
#include "md5.h"
#include "page.h"
#include "stringfun.h"
#include "http.h"


multimap<string,string> unvisitedUrl;

pthread_mutex_t collection_mutex;

bool isOver;
map<unsigned long,unsigned long> mapIpBlock;

vector<string> parsedLinksVec;

void Crawler::download ( SearchFile * pSearchFile, LinkFile * pLinkFile, Url & url, int & gSock ) {
    /*
     * Download the page from url
     * Param pSearchFile: the SearchFile pointer
     * Param pLinkFile: the LinkFile pointer
     * Param url: the url string
     * Param gSock: the socket of pre global
     * Return: none
     */
    char * downloadFile = NULL;
    char * fileHead = NULL;
    char * locate = NULL;
    int fileLength = 0;
    string urlLocate = "";
    int sock = gSock;
    cout << "1. pid=" << pthread_self() << "sock= " << sock << endl;
    Http http;
}

void Crawler::fetch ( void * arg ) {
    /*
     *fetch the url from web page 
     *Param arg: Crawler handle
     *Return: None
     */
    string urlString;
    string host;
    int gSock = -1;
    string  gHost = "";
    int sleepCnt = 0;

    string ofsName = DATA_SEARCH_FILE + "." + StringFunction::numToString((long long int )pthread_self());
    SearchFile searchFile ( ofsName );

    ofsName = DATA_LINK_FILE + "." + StringFunction::numToString((long long int )pthread_self());
    LinkFile linkFile(ofsName);

    bool do_fetch = true;
    while ( do_fetch ) {
        pthread_mutex_lock( &collection_mutex ); //lock the collection thread
        int cnt = unvisitedUrl.size();
        if ( cnt > 0 ) {
            cout << "has" << cnt << "unvisited urls" << endl;
            multimap<string,string>::iterator miter = unvisitedUrl.begin();
            if ( miter != unvisitedUrl.end() ) {
                urlString = (*miter).second;
                unvisitedUrl.erase( (*miter).second );
                pthread_mutex_unlock( &collection_mutex );

                Url url;
                if  ( url.parseUrl(urlString) == false ) {
                    cout << "parse url error in fetch!" << endl;
                    continue;
                }

                if ( gHost != url.m_host ) {
                    close ( gSock );
                    gSock = -1;
                    gHost = url.m_host;
                }

                ((Crawler *)arg)->download(&searchFile,&linkFile,url,gSock);
                cnt = 0;
            }
            else {
                pthread_mutex_unlock( &collection_mutex );
            }
        }
        else {
            pthread_mutex_unlock( &collection_mutex );
            usleep(1000);
            sleepCnt++;
        }
        if ( isOver == true ) {
            do_fetch = false;
        }
    }
    searchFile.close();
    linkFile.close();
}
