#include "page.h"
#include "stringfun.h"

Page::Page() {
    this->m_url = "";
    this->m_header = "";
    this->m_status = 0;
    this->m_locate = "";
}

Page::~Page() {}
Page::Page( string url, string locate, char * header, char * body ) {
    this->m_url = url;
    this->m_locate = locate;
    this->m_header = header;
    this->m_body = body;
}

void Page::getStatus ( string head ) {
    StringFunction::upperToLower(head);
    //TODO:http:/ ? or http/
    char* pos = strstr(head.c_str(),"http:/");
    if ( pos == NULL ) {
        this->m_status = -1;
        return;
    }
    while ( *pos != ' ' && *(pos+1) !='\0') {
        pos++;
    }
    int result = sscanf(pos,"%i",&this->m_status);
    if (result != 1)  {
        this->m_status = -1;
    }
}
