#include "url.h"
#include "stringfun.h"
#include "searchfile.h"
#include "page.h"
#include "linkfile.h"
#include "crawler.h"

#include <iostream>
using namespace std;

void testStringFunction () {
    /*
     * the unitest of the class StringFunction
     */
    string s = "hello,World, i am xiao中国人ming";
    StringFunction::upperToLower(s);
    string number = StringFunction::numToString(1024);
    cout << s <<endl;
    cout << number.length() << endl;
    string::size_type pos = StringFunction::findPostion("what is your name?","is",6);
    cout << pos << endl;
    StringFunction::replaceStr(s,"xiao","zhang");
    StringFunction::eraseStr(s,"hello");
    cout << s << endl;
}

void testUrl () {
    /*
     * the unitest of the class Url
     */
    Url url;
    url.parseUrl("http://www.peopledaily.com.cn/GB/news/index.html");
    cout << url.getUrl()<< endl;
    cout << url.getHost() << endl;
    cout << url.getPort()<< endl;
    cout << url.getPath() << endl;
    cout << url.getIpByHost ( url.getHost().c_str() ) << endl;
    cout << url.isImageUrl ( "http://www.peopledaily.com.cn/GB/news/index.html" ) << endl;
    cout << url.isForeignHost ( "http://www.aatv.com" ) << endl;
}

void testSearchFile() {
    /*
     * the unitest of the class SearchFile
     */
    SearchFile sf;
    cout << sf.getFileType() << endl;
}
void testLinkFile() {
    /*
     * the unitest of the class SearchFile
     */
    LinkFile lf;
    cout << lf.getFileType() << endl;
}

void testPage() {
    /*
     * the unitest of the class Page
     */
    Page page();
}


//main function
int main()
{
    //testUrl();
    //testStringFunction();
    //testSearchFile();
    //testPage();
    //testLinkFile();
    cout << pthread_self() << endl;
    return 0;
}
