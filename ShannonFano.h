#pragma once

#include <iostream>
#include <string>
#include <iomanip>
#include "List.h"
#include "ListWithTwoValues.h"
#include "Map.h"

using namespace std;

class ShannonFano
{
private:
	string originalString;

	List<bool> encodedString;
	
	Map<char, float, List<bool>> map;
	
	List<bool> code;
	
	ListWithTwoValues<char, float> pro;
	
	void setCodes(size_t, size_t);

public:
	ShannonFano();
	
	~ShannonFano();
	
	void setOriginalString();
	
	void display();
	
	void decode();
	
	List<bool> getEncodedString();
	
	void setOriginalString(string);
	
	List<char> decode(string);
};