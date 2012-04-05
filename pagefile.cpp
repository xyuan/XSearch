#include "pagefile.h"

extern map<string,string> mapCacheHostLookup;

PageFile::PageFile()
{

}

PageFile::PageFile(string filename) : BaseFile( filename )
{

}

PageFile::~PageFile()
{
	m_ofsfile.close();
}

bool PageFile::write ( void * arg, Url * pUrl, Page * pPage ) {
    if ( !pUrl || !pUrl || !m_ofsfile ) {
        return false;
    }
    return true;
}
