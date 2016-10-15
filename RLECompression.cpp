#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

class RLECompression
{
	int runLength;	
	int nextByte;
	int previousByte;
	
	public:
		RLECompression(char* option, FILE* inFile, FILE* outFile);
		void compress(FILE* inFile, FILE* outFile);
		void decompress(FILE* inFile, FILE* outFile);
};

RLECompression::RLECompression(char* option, FILE* inFile, FILE* outFile)
{
	if(strcmp(option, "-c") == 0)
		compress(inFile, outFile);
	else if(strcmp(option, "-d") == 0)
		decompress(inFile, outFile);	
}

void RLECompression::compress(FILE* inFile, FILE* outFile)
{
	nextByte = fgetc(inFile);
	previousByte = nextByte;
	
	while(nextByte != EOF)
	{
		runLength = 1;
		
		previousByte = nextByte;
		
		while((nextByte = fgetc(inFile)) != EOF && nextByte == previousByte)
			runLength++;
			
		fputc(runLength, outFile);
		fputc(previousByte, outFile);
	}
}

void RLECompression::decompress(FILE* inFile, FILE* outFile)
{
	while((runLength = fgetc(inFile)) != EOF)
	{	
		nextByte = fgetc(inFile);
		
		for(int i = 0; i < runLength; i++)
			fputc(nextByte, outFile);
	}
}

int main(int argc, char* argv[])
{
	FILE* inFile;
 	FILE* outFile;
 	
 	char* option = argv[1];
 	inFile = fopen(argv[2], "r");
	outFile = fopen(argv[3], "w");
	
	RLECompression* compression = new RLECompression(option, inFile, outFile);

	fclose(inFile);
	fclose(outFile);
	
	return 0;
}
