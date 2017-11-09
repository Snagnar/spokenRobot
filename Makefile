all: output voiceControl searchForParams searchForNumber requestInput

output: bin/output.cpp bin/ukisSpeak.hpp bin/constants_and_libraries.h
	g++ bin/output.cpp -o bin/export/output -std=c++11
	
voiceControl: bin/voiceControl.cpp bin/ukisSpeak.hpp bin/constants_and_libraries.h bin/recognition_tools.hpp
	g++ bin/voiceControl.cpp -o bin/voiceControl -std=c++11
	
searchForParams: bin/searchForParams.cpp bin/constants_and_libraries.h
	g++ bin/searchForParams.cpp -o bin/export/searchForParams -std=c++11
	
searchForNumber: bin/searchForNumber.cpp bin/constants_and_libraries.h
	g++ bin/searchForNumber.cpp -o bin/export/searchForNumber -std=c++11
	
requestInput: bin/requestInput.cpp bin/constants_and_libraries.h bin/recognition_tools.hpp
	g++ bin/requestInput.cpp -o bin/export/requestInput -std=c++11
	
replaceLine: bin/replaceLine.cpp
	g++ bin/replaceLine.cpp -o bin/export/replaceLine -std=c++11
