#ifndef _PAGE_H
#define _PAGE_H

#include <string>
using namespace std;

class Page {
public:
    //public functions
    Page();
    Page(string url, string locate, char* header, char* body, int bodylen);
    ~Page();
public:
    //private functions
    
    void parseHeader(string header);
    void getContentLength(string header);
    void getStatus(string header);
    void getLocation(string header);
    void getCharset(string header);
public:
    //member variables
    string m_url;
    string m_header;
    string m_locate;
    string m_body;
    int m_contentLen;
    string m_content;
    int m_headerLen;
    int m_status;
};

#endif
