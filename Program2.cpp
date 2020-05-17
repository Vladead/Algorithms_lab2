#include <iostream>
#include "ShannonFano.h"

int main()
{
	ShannonFano encoder;
	string str = "Cyber";

	encoder.setOriginalString(str);
	List<bool> encoded = encoder.getEncodedString();

	encoder.display();
	encoder.decode();
}
