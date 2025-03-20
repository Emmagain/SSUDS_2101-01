#pragma once

#include <iostream>
#include <fstream>
namespace ssuds
{

	class WordReader
	{
	private:
		size_t file_len;
		std::ifstream fp;
	public:
		WordReader();

		~WordReader();

		std::string extractWord();

	};
}