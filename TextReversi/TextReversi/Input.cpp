#include "Input.h"

#include <algorithm>
#include <iostream>

char AskYesOrNoQuestion(std::string question)
{
	std::string response;

	do
	{
		std::cout << question << " (y/n): ";
		getline(std::cin, response);

		std::transform(response.begin(), response.end(), response.begin(), ::tolower);
	} while (response != "y" && response != "yes" && response !=  "n" && response != "no");

	return response[0];
}