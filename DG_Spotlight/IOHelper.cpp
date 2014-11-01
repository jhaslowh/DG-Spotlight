#include "IOHelper.h"

// Read text from file 
std::string readFile(const char *fileName){
	std::ifstream in(fileName);
	std::string contents((std::istreambuf_iterator<char>(in)),
		std::istreambuf_iterator<char>());
	in.close();
	return contents;
}
