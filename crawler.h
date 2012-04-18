#include <iostream>
#include "searchfile.h"
#include "linkfile.h"
#include "url.h"
using namespace std;

class Crawler
{
public:
    Crawler();
    ~Crawler();

public:
    void fetch(void * arg);
    void download ( SearchFile * pSearchFile, LinkFile * pLinkFile, Url & url, int & gSock );

private:
    string seed_file_name;
    string output_file_name;
};
