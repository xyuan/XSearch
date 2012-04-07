#include "stringfun.h" 

bool noneCaseCompare(char c1,char c2) {
	/*
	 * compare two char that ignore
	 * Param c1,c2: the two char to compare
	 * Return: true or false
	 */
	return toupper(c1) == toupper(c2);
}

StringFunction::StringFunction() {}
StringFunction::~StringFunction() {}

void StringFunction::upperToLower ( string & str ) {
	/*
	* replace the string's all char from upper to lower case
	* Param str: the string
	* Return: as the input string
	*/
    char d = 'A' - 'a';
    for ( int i = 0; i < str.length(); i++ ) {
        if ( str[i] >= 'A' && str[i] <= 'Z' ) {
            str[i] -= d;
        }
    }
}

string StringFunction::numToString ( long long number ) {
	/*
	* convert an integer to string type
	* Param number: the number wait to convert
	* Return: an string object
	*/
	stringstream s;
	s << number;
	return s.str();
}

string::size_type StringFunction::findPostion(string source, string target, int posFrom ) {
	/*
	 * find the pos that target in source
	 * Param source: the string that want's to be find
	 * Param target: the string maybe in source
	 * Param posFrom: the pos in source
	 * Return: the size_type
	 */
	if ( source.empty() || target.empty() ) {
		return string::npos;
	}
	string::iterator siter;
	if ( posFrom != NULL ) {
		siter = search(source.begin() + posFrom,source.end(),target.begin(),target.end(),noneCaseCompare);
	}
	else {
		siter = search(source.begin(),source.end(),target.begin(),target.end(),noneCaseCompare);
	}
	if ( siter == source.end() ) {
		return string::npos;
	}
	else {
		return ( siter - source.begin() );
	}
}

void StringFunction::replaceStr(string & str, string src, string dest) {
	/*
	 * replace the all the src in string source to dest
	 * Param str: the input string
	 * Param src: the string in str
	 * Param dest: the dest string that replace src in str
	 * Return: as the input str
	 */
	if ( str.size() == 0 || src.size() == 0 ) {
		return ;
	}
	string::size_type index = 0;
	string::size_type srcLength = src.length();
	index = str.find(src,index);
	while ( index != string::npos ) {
		str.replace( index,srcLength, dest );
		if ( index + dest.size() > str.size() ) {
			break;
		}
		index = str.find(src,index+dest.size());
	}
}

void StringFunction::eraseStr(string & str, string substr) {
	/*
	 * erase the substr in the string
	 * Param str: the input str
	 * Param substr: the string want's to earsed in str
	 * Return: as the input str
	 */
	if( str.size() == 0 || substr.size() == 0 )
		return;
	string::size_type index = 0;
	string::size_type sub_length = substr.length();
	index = str.find(substr,index);
	while( index != string::npos ){
		str.erase(index,sub_length);
		index = str.find(substr,index);
	}
}
