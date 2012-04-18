#include "linkfile.h"

extern map<string,string> hostCacheMap;
extern vector<string> parsedLinksVec;

LinkFile::LinkFile() {}

LinkFile::LinkFile(string filename) : FileEngine(filename) {}

LinkFile::~LinkFile() {
    m_ofs.close();
}


bool LinkFile::write ( void * arg ) {
    if (!arg || !this->m_ofs) { 
        return false;
    }
    if (parsedLinksVec.size()==0) {
        return false;
    }

    file_arg *pFile = (file_arg *)arg;

    Url *url = pFile->pUrl;
    Page *page = pFile->pPage;

    char strDownloadTime[128];
    time_t tDate;

    memset(strDownloadTime, 0, 128);
    time(&tDate);
    strftime(strDownloadTime, 128, "%a, %d %b %Y %H:%M:%S GMT", gmtime(&tDate));

    string links;
    vector<string>::iterator it;
    for (it=parsedLinksVec.begin(); it!=parsedLinksVec.end(); ++it)
    {
        links = links + *it + "\n";
    }

    this->m_ofs << "version: 1.0\n";
    if( page->m_locate.length() == 0 ){
            this->m_ofs << "url: " << url->m_url;
    } else {
            this->m_ofs << "url: " << page->m_locate;
            this->m_ofs << "\norigin: " << url->m_url;
    }

    this->m_ofs << "\ndate: " << strDownloadTime;
    if( hostCacheMap.find(url->m_host) == hostCacheMap.end() ){
            this->m_ofs << "\nip: " << url->m_host;
    } else {
            this->m_ofs << "\nip: " << ( *(hostCacheMap.find(url->m_host)) ).second;
    }

    this->m_ofs << "\noutdegree: " << parsedLinksVec.size();
    this->m_ofs << "\nlength: " << links.size() + page->m_headerLen + 1 
            << "\n\n" << page->m_header << "\n";
    this->m_ofs << links;
    this->m_ofs << endl;

    return true;
}
