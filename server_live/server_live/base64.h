#pragma once

#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>

using namespace std;
class Base64
{
public:
	Base64();
	~Base64();

	string encode(char*, int len);
	vector<char> decode(std::string &str);
};

