#include "url.h"

#include <iostream>
using namespace std;

//main function
int main()
{
    Url url;
    //url.parse_url("http://www.peopledaily.com.cn/GB/news/index.html");
    char * result = url.getIpByHost("127.0.0.1");
    cout << result <<endl;
    return 0;
}
