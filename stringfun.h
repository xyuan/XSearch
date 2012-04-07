#ifndef _STRINGFUN_H
#define _STRINGFUN_H

#include <string>
#include <sstream>
#include <iostream>
#include <algorithm>

using namespace std;

class StringFunction { 
	/*
	 * The class that process string
	 * Author: wangxiao
	 * Date: 2012/4/7
	 */

public:
	//public functions
	StringFunction();
	virtual ~StringFunction();
	static void upperToLower ( string & str );
	static string numToString ( long long i );
	static string::size_type findPostion(string source, string target, int posFrom = NULL );

	static void replaceStr(string & source, string subSrc, string dest);
	static void eraseStr(string & source, string substr);
};

#endif
