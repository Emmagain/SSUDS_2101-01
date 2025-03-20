#include <WordReader.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

namespace ssuds
{

	WordReader::WordReader()
	{
		//std::ifstream fp("../../media/english-words.80", std::ios::binary);("../../media/english-words.80", std::ios::binary);
		fp.open("../../media/my_words.txt", std::ios::binary); //"../../media/english-words.80"
		fp.seekg(0, std::ios::end);
		file_len = fp.tellg();
	}

	WordReader::~WordReader()
	{
		fp.close();
	}

	std::string WordReader::extractWord()
	{
		int randNum = std::rand() % file_len - 1;
		fp.seekg(randNum, std::ios::beg);
		fp.seekg(-1, std::ios::cur);    // Go back one character
		char c = fp.peek();
		while (c != 'a')
		{
			fp.seekg(-1, std::ios::cur);
			c = fp.peek();
		}
		std::string read_word;
		std::getline(fp, read_word);
		return read_word;
	}
}