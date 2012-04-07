//#include "url.h"
#include "stringfun.h"

#include <iostream>
using namespace std;

//main function
int main()
{
    //Url url;
    //url.parse_url("http://www.peopledaily.com.cn/GB/news/index.html");
    //char * result = url.getIpByHost("127.0.0.1");
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

    return 0;
}
