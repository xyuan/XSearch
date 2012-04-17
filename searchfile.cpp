#include "searchfile.h"

extern map<string,string> hostCacheMap;

SearchFile::SearchFile() {}

SearchFile::SearchFile(string filename) : FileEngine(filename) {}

SearchFile::~SearchFile()
{
    /* 
     * The Destructorr of the Url class
     * Close the ofstream
     */
    m_ofs.close();
}

bool SearchFile::write(void * arg)
{
    /*
     * Write the file in hard
     * Param arg: the grgument handle
     * Return: true if success writed false if not
     */
    if( !arg || !m_ofs ){
        return false;
    }
    file_arg *pFile = (file_arg *)arg;

    Url *iUrl = pFile->pUrl;
    Page *iPage = pFile->pPage;

    char strDownloadTime[128];
    time_t tDate;

    memset(strDownloadTime, 0, 128);
    time(&tDate);
    strftime(strDownloadTime, 128, "%a, %d %b %Y %H:%M:%S GMT", gmtime(&tDate));
    return true;
}

