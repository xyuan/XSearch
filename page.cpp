#include "page.h"
#include "stringfun.h"

Page::Page() {
    this->m_url = "";
    this->m_header = "";
    this->m_status = 0;
    this->m_locate = "";
}

Page::~Page() {}
Page::Page( string url, string locate, char * header, char * body, int bodyLen ) {
    this->m_url = url;
    this->m_locate = locate;
    this->m_header = header;
    this->m_body = body;

    this->m_content.assign( body, bodyLen );
    this->m_contentLen = bodyLen;
}


void Page::parseHeader ( string header ) {
    /*
     * Parse the header info
     * Param header: the header of the page
     * Return: as the member variable
     */
    this->getStatus ( header );
    this->getContentLength ( header );
}

void Page::getContentLength ( string header ) {
    /*
     * Get the header's content length
     * Param header: the header of the page
     * Return: as the member variable
     */
    StringFunction::upperToLower( header );
    char * pos = strstr(header.c_str(), "content-length");
    if ( pos == NULL ) {
        return ;
    }
    while ( *pos != ' ' ) {
        pos++;
    }
    pos++;
    int result = sscanf ( pos, "%i", &this->m_contentLen);
    if ( result != 1 ) {
        this->m_contentLen = -1;
    }
}
void Page::getStatus ( string header ) {
    /*
     * Get the status code of the head
     * param head: the head of the url
     * Return: as the member variable
     */
    StringFunction::upperToLower(header);
    char* pos = strstr(header.c_str(),"http/");
    if ( pos == NULL ) {
        this->m_status = -1;
        return;
    }
    while ( *pos != ' ') {
        pos++;
    }
    pos++;
    int result = sscanf(pos,"%i",&this->m_status);
    if (result != 1)  {
        this->m_status = -1;
    }
}
void Page::getLocation ( string header ) {
    /*
     * Get the location of the head
     * param head: the head of the url
     * Return: as the member variable
     */
    string::size_type preIndex,index;
    const string delims = "\r\n";
    string str = header;
    StringFunction::upperToLower(str);
    index = str.find("location:");
    if ( index != string::npos ) {
        preIndex = index + sizeof("location: ")-1;
        index = str.find_first_of(delims,preIndex);
        if ( index != string::npos ) {
            this->m_locate = str.substr(preIndex,index - preIndex);
        }
    }
}

void Page::getCharset ( string header ) {
    /*
     * Get the charset of the head
     * param head: the head of the url
     * Return: as the member variable
     */
}
