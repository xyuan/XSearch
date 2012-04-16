#include "url.h"
#include "stringfun.h"

#include <iostream>
using namespace std;

//main function
int main()
{
    /*
     * the unitest of the class StringFunction
     */
    /*
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
    */
    //-----------------------------------------
	
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

    return 0;
}
