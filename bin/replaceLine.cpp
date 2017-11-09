#include <iostream>
#include <fstream>
#include <string>
#include <math.h>

using namespace std;

//replaces a line in a file with argument
//Syntax: replaceLine lineNr|"keyword_to_search_for_in_lines" "content_to_replace" "file"

static int convertStringToNumber(std::string String) {
	int result=0;
	for(int x=0; x<String.size(); x++) {
		if((String[String.size()-x-1]-0x30)>9||(String[String.size()-x-1]-0x30)<0) {
			return -1;
		}
		result+=(String[String.size()-x-1]-0x30)*pow(10,x);
	}
	return result;
}

int main(int argc, char** argv) {
	ifstream readFile;
	string line;
	string newContent;
	int lineNr;
	
	if(argc!=4) {
		cout<<"Error: Falsche Anzahl an Argumenten übergeben! "<<argc<<endl;
		return 1;
	}
	//for(int x=0; x<argc; x++)
		//cout<<"Arg nr. "<<x<<": "<<argv[x]<<endl;
	
	readFile.open(argv[3], ios::in);
	newContent="";
	lineNr=1;
	
	while(getline(readFile, line)) {
		if((convertStringToNumber(argv[1])!=-1&&convertStringToNumber(argv[1])==lineNr)||(convertStringToNumber(argv[1])==-1&&line.find(argv[1])!=string::npos)) {
			newContent+=argv[2];
			newContent+="\n";
		}
		else {
			newContent+=line+"\n";
		}
		lineNr++;
	}
	
	cout<<newContent;
	return 0;
}
