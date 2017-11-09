#include "constants_and_libraries.h"

using namespace std;

//Programm searches for occurence of a number in argument
//Syntax: searchForNumber "content_to_search_in"
//Returns a number if found

int main(int argc, char** argv) {
	string searchString;
	string tempString;
	vector<string> singleWords;
	
	stdLogPrefix=argv[0];
	stdLogPrefix+=": ";
	
	if(argc!=2) {
		writeToLog("errors.log", stdLogPrefix+error(1));
		return 1;
	}
	searchString=argv[1];
	
	for(int x=0; x<searchString.size(); x++) {
		if(searchString[x]==' ') {
			singleWords.push_back(tempString);
			tempString="";
			continue;
		}
		tempString+=searchString[x];
	}
	for(auto it : singleWords)
		if(convertStringToNumber(it)!=-1) {
			cout<<convertStringToNumber(it);
			return 0;
		}
	
	cout<<"";
	return 0;
}
