#ifndef _PAGE_H
#define _PAGE_H

#include <string>
using namespace std;

class Page {
public:
    //public functions
    Page();
    Page(string url, string locate, char* header, char* body);
    ~Page();
public:
    //private functions
    void getStatus(string head);
private:
    //private functions
    string m_url;
    string m_header;
    string m_locate;
    string m_body;
    int m_status;
};

#endif
