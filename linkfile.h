#ifndef _LINKFILE_H
#define _LINKFILE_H

#include "fileengine.h"
#include "xsearch.h"
#include "url.h"

class LinkFile : public FileEngine 
{

public:
    LinkFile();
    LinkFile(string filename);
    virtual ~LinkFile();
    inline int getFileType() { return LINK; }
    virtual bool write(void *arg);
};

#endif
