#include <iostream>
#include <string>
#include "global.h"

int main(int argc, char** argv)
{
	tests::GLES2Example1::setup();

	printf("sup ya'll?");

	std::string str;
	std::getline(std::cin, str);
}