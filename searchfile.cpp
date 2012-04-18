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

    Url * url = pFile->pUrl;
    Page * page = pFile->pPage;

    char strDownloadTime[128];
    time_t tDate;

    memset(strDownloadTime, 0, 128);
    time(&tDate);
    strftime(strDownloadTime, 128, "%a, %d %b %Y %H:%M:%S GMT", gmtime(&tDate));

    m_ofs << "version: 1.0\n";
    if ( page->m_locate.length()==0 ) {
        m_ofs << "url: " << url->m_url;
    }
    else {
        m_ofs << "url: " << url->m_url;
        m_ofs << "\norigin: " << page->m_locate;
    }
    
    m_ofs << "\ndate: " << strDownloadTime;
    if ( hostCacheMap.find(url->m_host) == hostCacheMap.end() ) {
        m_ofs << "\nip: " << url->m_host;
    }
    else {
        m_ofs << "\nip: " << ( *(hostCacheMap.find(url->m_host))).second;
    }
    m_ofs << "\nlength: " << page->m_contentLen + page->m_headerLen + 1 << "\n\n" << page->m_header << "\n";
    //write path,and len?
    m_ofs.write( page->m_content.c_str(),page->m_contentLen );
    m_ofs << endl;
    return true;
}
