#ifndef _STRINGFUN_H
#define _STRINGFUN_H

#include <string>
#include <sstream>
#include <iostream>
#include <algorithm>

using namespace std;

class StringFunction { 

public:
	StringFunction();
	virtual ~StringFunction();
        
        static void upperToLower ( string & str, int length );
	static string numToString ( long long i );
	static string::size_type findPostion(string source, string target, int posFrom = NULL );

	static void replaceStr(string & source, string subSrc, string dest);
	static void eraseStr(string & source, string substr);
private:
        bool noneCaseCompare( char c1, char c2 );
};

#endif
