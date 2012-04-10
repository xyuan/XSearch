#include "page.h"
#include "stringfun.h"

Page::Page() {
    m_url = "";
    m_header = "";
}

Page::Page( string url, string locate, char * header, char * body ) {

}

void Page::getStatus ( string head ) {
    StringFunction::upperToLower(head);
    char * pos = strstr(head.c_str(),"http/");
    if ( pos == NULL ) {
        this->m_status = -1;
        return;
    }

}
