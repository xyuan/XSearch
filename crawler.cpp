#include <iostream>
#include "Crawler.h"

multimap<string,string> unvisited_url;

pthread_mutex_t collection_mutex;

void Crawler::fetch ( void * arg ) {
    /*
     *fetch the url from web page 
     *Param arg: Crawler handle
     *Return: None
     */
    string host_name;
    string url_name;

    bool do_fetch = true;
    while ( do_fetch ) {
        pthread_mutex_lock( &collection_mutex ); //lock the collection thread
        int url_num = unvisited_url.size();
        if ( url_num > 0 ) {
            cout << "剩余" << url_num << "urls" << endl;
            multimap<string,string>::iterator miter = unvisited_url.begin();
            uvisited_url.erase( (*miter).second );
            pthread_mutex_unlock( &collection_mutex );

            //TODO:需要解析一下URL是否是合法的

            ((Crawler *)arg)->download();
        }
        if ( do_fetch == false ) {
            break;
        }
    }
}
