#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

class RLECompression
{
	int runLength;	
	int nextByte;
	int previousByte;
	
	public:
		RLECompression(char* option, ifstream& inFile, ofstream& outFile);
		void compress(ifstream& inFile, ofstream& outFile);
		void decompress(ifstream& inFile, ofstream& outFile);
};

RLECompression::RLECompression(char* option, ifstream& inFile, ofstream& outFile)
{
	if(strcmp(option, "-c") == 0)
		compress(inFile, outFile);
	else if(strcmp(option, "-d") == 0)
		decompress(inFile, outFile);	
}

void RLECompression::compress(ifstream& inFile, ofstream& outFile)
{
	nextByte = inFile.get();
	previousByte = nextByte;
	
	while(nextByte != EOF)
	{
		runLength = 1;
		
		previousByte = nextByte;
		
		while((nextByte = inFile.get()) != EOF && nextByte == previousByte)
			runLength++;
			
		outFile.put(runLength);
		outFile.put(previousByte);
	}
}

void RLECompression::decompress(ifstream& inFile, ofstream& outFile)
{
	while((runLength = inFile.get()) != EOF)
	{	
		nextByte = inFile.get();
		
		for(int i = 0; i < runLength; i++)
			outFile.put(nextByte);
	}
}

int main(int argc, char* argv[])
{
	ifstream inFile;
 	ofstream outFile;
 	
 	char* option = argv[1];
 	inFile.open(argv[2]);
	outFile.open(argv[3]);
	
	RLECompression* compression = new RLECompression(option, inFile, outFile);

	inFile.close();
	outFile.close();
	
	return 0;
}
