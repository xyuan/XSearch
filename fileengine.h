#ifndef _FILEENGINE_H 
#define _FILEENGINE_H 

#include "dataengine.h"
#include "url.h"
#include "page.h"

enum fileengine_type
{
    ISAM,
    XSEARCH,
    LINK
};

class CUrl;
class CPage;

struct file_arg
{
    Url *pUrl;
    Page *pPage;
};

class FileEngine : public DataEngine
{
public:
    ofstream m_ofs;

public:
    FileEngine();
    FileEngine(string str);
    virtual ~FileEngine();
    virtual int getFileType() = 0;
    int getEngineType() { return FILE_ENGINE; }
    bool open(string filename);
    inline void close() { m_ofs.close(); }
};

#endif
