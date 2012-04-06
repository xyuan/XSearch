#include "stringfun.h"


StringFunction::StringFunction() {}
StringFunction::~StringFunction() {}
    
void StringFunction::upperToLower ( string & str ) {
    char d = 'A' - 'a';
    for ( int i = 0; i < str.length(); i++ ) {
        if ( str[i] >= 'A' && str[i] <= 'Z' ) {
            str[i] -= d;
        }
    }
}

string StringFunction::numToString ( long long i ) {

}

string::size_type StringFunction::findPostion(string source, string target, int posFrom = NULL ) {

}

void StringFunction::replaceStr(string & source, string subSrc, string dest) {
}

void StringFunction::eraseStr(string & source, string substr) {
}

