#include "ShannonFano.h"

ShannonFano::ShannonFano() 
{

}

ShannonFano::~ShannonFano() 
{

}

void ShannonFano::setOriginalString() 
{
	cout << "Input original string: ";
	getline(cin, originalString);
	if (originalString.empty())
	{
		throw runtime_error("Original string is not set");
	}
	
	for (int i = 0; i < originalString.length(); i++) 
	{
		map.insert(originalString.at(i), float(1) / originalString.length(), float(1) / originalString.length());
	}
	
	for (int i = 0; i < originalString.length(); i++) 
	{
		pro.sorted_insert(originalString.at(i), map.findValue1(originalString[i]));
	}
	
	if (pro.get_size() == 1)
	{
		code.push_back(0);
		map.setValue2(originalString.at(0), code);
	}
	else
	{
		setCodes(0, pro.get_size());
	}

	List<bool> temp;
	
	for (size_t i = 0; i < originalString.length(); i++) 
	{
		encodedString.push_back(map.findValue2(originalString.at(i)));
	}
}

void ShannonFano::setCodes(size_t a, size_t b) 
{
	if (b - a == 2) 
	{
		code.push_back(0);
		map.setValue2(pro.atFirstValue(a), code);
		code.pop_back();
		code.push_back(1);
		map.setValue2(pro.atFirstValue(b - 1), code);
		code.pop_back();
		return;
	}

	if (b - a == 1) 
	{
		map.setValue2(pro.atFirstValue(a), code);
		return;
	}

	float decStr = 0, sum = 0;

	for (int i = a; i < b; i++) 
	{
		decStr += pro.atSecondValue(i);
	}

	decStr /= 2;
	size_t index = a;

	for (int i = a; i < pro.get_size(); i++) 
	{
		sum += pro.atSecondValue(i);
		index++;

		if (sum >= decStr) 
		{
			break;
		}
	}

	code.push_back(0);
	setCodes(a, index);
	code.pop_back();
	code.push_back(1);
	setCodes(index, b);
	code.pop_back();
}

void ShannonFano::display() 
{
	if (originalString.empty())
	{
		throw runtime_error("Original string is not set");
	}

	cout << "Original: ";
	cout << originalString << endl;
	cout << "Encoded: ";
	encodedString.print_to_console();
	cout << '\n';
	cout << "Size of original: " << originalString.length() * 8 << " bites" << endl;
	cout << "Size of encoded : " << encodedString.get_size() << " bites" << endl;
	cout << "Compression %: " << setprecision(3) << (float)encodedString.get_size() * 100 / (originalString.length() * 8) << '%' << endl;
	cout << "Symbol" << "\t" << "Probability" << "\t" << "Encoding" << endl;
	List<bool> temp;
	
	for (int i = 0; i < pro.get_size(); i++) 
	{
		cout << " \"" << pro.atFirstValue(i) << "\"\t    " << map.findValue1(pro.atFirstValue(i)) << "         ";
		map.findValue2(pro.atFirstValue(i)).print_to_console();
		cout << endl;
	}
}

void ShannonFano::decode() 
{
	if (originalString.empty())
	{
		throw runtime_error("Original string is not set");
	}

	cout << "Input string to decode it: ";
	string encodedToDecoded;
	getline(cin, encodedToDecoded);
	
	if (encodedToDecoded.empty())
	{
		throw runtime_error("Decoded string is not set");
	}

	List<char> decoded_string;
	List<bool> tempCode;
	
	for (int i = 0; i < encodedToDecoded.length(); i++) 
	{
		tempCode.push_back(encodedToDecoded.at(i) - 48);
		
		if (map.codeInDict(tempCode)) 
		{
			decoded_string.push_back(map.findKey(tempCode));
			tempCode.clear();
		}
	}

	if (!tempCode.isEmpty()) 
	{
		throw runtime_error("Decoded string is not correct");
	}
	
	cout << "Decoded: ";
	
	for (int i = 0; i < decoded_string.get_size(); i++) 
	{
		cout << decoded_string.at(i);
	}
	
	cout << endl;
}

List<bool> ShannonFano::getEncodedString()
{
	return encodedString;
}

List<char> ShannonFano::decode(string str) 
{
	if (originalString.empty())
	{
		throw runtime_error("Original string is not set");
	}

	string encodedToDecoded = str;
	
	if (encodedToDecoded.empty())
	{
		throw runtime_error("Decoded string is not set");
	}

	List<char> decodedString;
	List<bool> tempCode;
	
	for (int i = 0; i < encodedToDecoded.length(); i++) 
	{
		tempCode.push_back(encodedToDecoded.at(i) - 48);
	
		if (map.codeInDict(tempCode)) 
		{
			decodedString.push_back(map.findKey(tempCode));
			tempCode.clear();
		}
	}

	if (!tempCode.isEmpty()) 
	{
		throw runtime_error("Decoded string is not correct");
	}
	
	return decodedString;
}

void ShannonFano::setOriginalString(string str)
{
	if (str.empty())
	{
		throw runtime_error("Original string is not set");
	}

	originalString = str;
	
	for (int i = 0; i < originalString.length(); i++) 
	{
		map.insert(originalString.at(i), float(1) / originalString.length(), float(1) / originalString.length());
	}
	
	for (int i = 0; i < originalString.length(); i++) 
	{
		pro.sorted_insert(originalString.at(i), map.findValue1(originalString[i]));
	}
	
	if (pro.get_size() == 1)
	{
		code.push_back(0);
		map.setValue2(originalString.at(0), code);
	}
	else
	{
		setCodes(0, pro.get_size());
	}
	
	List<bool> ls;
	
	for (size_t i = 0; i < originalString.length(); i++) 
	{
		encodedString.push_back(map.findValue2(originalString.at(i)));
	}
}