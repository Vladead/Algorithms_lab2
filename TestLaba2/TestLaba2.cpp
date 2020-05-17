#include "pch.h"
#include "CppUnitTest.h"
#include "../ShannonFano.h"
#include "../ShannonFano.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestLaba2
{
	TEST_CLASS(TestLaba2)
	{
	private:
		string str;

	public:
		TEST_METHOD(test_setOriginalString) {
			ShannonFano encoder;

			try 
			{
				encoder.setOriginalString(str);
			}
			catch (runtime_error e) 
			{
				Assert::AreEqual(e.what(), "Original string is not set");
			}

			str.append("Cyber");
			encoder.setOriginalString(str);
			List<bool> encoded = encoder.getEncodedString();

			Assert::AreEqual(encoded.at(0), false);
			Assert::AreEqual(encoded.at(1), false);
			Assert::AreEqual(encoded.at(2), false);
			Assert::AreEqual(encoded.at(3), false);
			Assert::AreEqual(encoded.at(4), false);
			Assert::AreEqual(encoded.at(5), true);
			Assert::AreEqual(encoded.at(6), false);
			Assert::AreEqual(encoded.at(7), true);
			Assert::AreEqual(encoded.at(8), true);
			Assert::AreEqual(encoded.at(9), false);
			Assert::AreEqual(encoded.at(10), true);
			Assert::AreEqual(encoded.at(11), true);
		}

		TEST_METHOD(test_display)
		{
			ShannonFano encoder;

			try 
			{
				encoder.display();
			}
			catch (runtime_error e)
			{
				Assert::AreEqual("Original string is not set", e.what());
			}
		}

		TEST_METHOD(test_decode)
		{
			ShannonFano encoder;

			try 
			{
				encoder.decode();
			}
			catch (runtime_error e) 
			{
				Assert::AreEqual("Original string is not set", e.what());
			}

			encoder.setOriginalString("Cyber");

			try 
			{
				encoder.decode("");
			}
			catch (runtime_error e) 
			{
				Assert::AreEqual("Decoded string is not set", e.what());
			}

			try 
			{
				encoder.decode("101010100101010");
			}
			catch (runtime_error e) 
			{
				Assert::AreEqual("Decoded string is not correct", e.what());
			}

			List<char>decoder = encoder.decode("000001011011");

			Assert::AreEqual(decoder.at(0), 'C');
			Assert::AreEqual(decoder.at(1), 'y');
			Assert::AreEqual(decoder.at(2), 'b');
			Assert::AreEqual(decoder.at(3), 'e');
			Assert::AreEqual(decoder.at(4), 'r');
		}
	};
}
