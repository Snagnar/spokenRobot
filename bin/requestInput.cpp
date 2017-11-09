#include "constants_and_libraries.h"
#include "recognition_tools.hpp"

using namespace std;

//Starts a record, which will be transcribed by googles speech api
//Return transcript.
//Syntax: requestInput

int main(int argc, char** argv) {
	string tempString;
	
	tempString="sox -r 44000 -c 1 -d "+localPath+"temp/output.wav silence 0 1 0:00:02 0.5%";
	system(tempString.c_str());
	
	tempString=localPath+"scripts/aufnahme.sh";
	system(tempString.c_str());
	
	cout<<getTranscript();
	return 0;
}
