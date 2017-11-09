#include "constants_and_libraries.h"

using namespace std;

//Programm looks for occurences of specific words given as an argument in
//a given string.
//Syntax: searchForParams "['arg1', ..., 'argN']" "inputString"
//Returns first found parameter

int main(int argc, char** argv) {
	string listOfParams;
	string searchString;
	size_t tempVar;
	vector<string> params;
	
	stdLogPrefix=argv[0];
	stdLogPrefix+=": ";
	
	if(argc!=3) {
		writeToLog("errors.log", stdLogPrefix+error(1));
		return 1;
	}
	listOfParams=argv[1];
	searchString=argv[2];
	tempVar=0;
	
	while(listOfParams.find("\'")!=string::npos) {
		tempVar=listOfParams.find("\'");
		params.push_back(listOfParams.substr(tempVar+1, listOfParams.find("\'", tempVar+1)-tempVar-1));
		listOfParams.erase(listOfParams.begin(), listOfParams.begin()+listOfParams.find("\'", tempVar+1)+1);
	}
	
	for(auto currParam : params) {
		if(searchString.find(currParam)!=string::npos) {
			cout<<currParam;
			return 0;
		}
	}
	
	cout<<"";
	return 0;
}
