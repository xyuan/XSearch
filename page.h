#ifndef _PAGE_H
#define _PAGE_H

#include <string>


class Page {
public:
    //public functions
    Page();
    Page(string url, string locate, char* header, char* body);
    ~Page();
private:
    void getStatus(string head);
private:
    //private functions
    string m_url;
    string m_header;
    int m_status;

};
~Page();

#endif
