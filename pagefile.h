#ifndef _PAGEFILE_H
#define _PAGEFILE_H

class Url;
class Page;

class PageFile : public BaseFile
{
public:
    PageFile(string filename);
    PageFile();
    virtual ~PageFile();
    virtual bool write( void * arg );
};

#endif

