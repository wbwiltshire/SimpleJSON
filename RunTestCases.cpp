/*
* File demo/testcases.cpp part of the SimpleJSON Library Demo - http://mjpa.in/json
*
* Copyright (C) 2010 Mike Anchor
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
* THE SOFTWARE.
*/

/*
* Test cases converted from http://testsuites.opera.com/JSON/runner.htm
*/

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <iomanip>
#include "JSON.h"
#include "functions.h"
#include "elapseTimer.h"

// Set to the width of the description column
#define DESC_LENGTH	 50
#define EDESC_LENGTH 50

// Defined in example.cpp
extern const wchar_t* EXAMPLE;

void runExamples() {
	int count = 1;
	std::wstring exampleOutput;
	std::wstring vert_sep = std::wstring(L"+--+") + std::wstring(EDESC_LENGTH, L'-') + std::wstring(L"+--------+\r\n");

	std::wcout << vert_sep.c_str();

	std::wstring header = std::wstring(L"|  | Examples ") + std::wstring(EDESC_LENGTH - 14 + 3, L' ') + std::wstring(L" | Result |\r\n");
	std::wcout << header.c_str();
	std::wcout << vert_sep.c_str();

	exampleOutput = std::wstring(L"|") + std::to_wstring(count) + std::wstring(L" | Parse example data") + std::wstring(DESC_LENGTH - 21 + 1, L' ') + std::wstring(L" | ");
	exampleOutput += example1(false) ? L"pass   |\n" : L"fail   |\n";
	std::wcout << exampleOutput.c_str();
	count++;

	exampleOutput = std::wstring(L"|") + std::to_wstring(count) + std::wstring(L" | Add Json elements") + std::wstring(DESC_LENGTH - 20 + 1, L' ') + std::wstring(L" | ");
	exampleOutput += example2(false) ? L"pass   |\n" : L"fail   |\n";
	std::wcout << exampleOutput.c_str();
	count++;

	exampleOutput = std::wstring(L"|") + std::to_wstring(count) + std::wstring(L" | Compact vs. prettyprint") + std::wstring(DESC_LENGTH - 26 + 1, L' ') + std::wstring(L" | ");
	exampleOutput += example3(false) ? L"pass   |\n" : L"fail   |\n";
	std::wcout << exampleOutput.c_str();
	count++;

	exampleOutput = std::wstring(L"|") + std::to_wstring(count) + std::wstring(L" | List keys in an object.") + std::wstring(DESC_LENGTH - 26 + 1, L' ') + std::wstring(L" | ");
	exampleOutput += example4(false) ? L"pass   |\n" : L"fail   |\n";
	std::wcout << exampleOutput.c_str();
	count++;

	std::wcout << vert_sep.c_str();
	std::wcout << std::endl;
}

// Helper to do a quick parse check
bool parseCheck(std::wstring str)
{
	JSONValue *v = JSON::Parse(str.c_str());
	if (v)
	{
		delete v;
		return true;
	}
	else
		return false;
}

// Helper to get a files contents
bool getFile(std::string filename, std::wstring &description, std::wstring &data)
{
	std::wifstream in(filename.c_str());
	if (in.is_open() == false)
		return false;

	std::getline(in, description);
	if (description.length() > DESC_LENGTH)
		description.resize(DESC_LENGTH);

	std::wstring line;
	data = L"";
	while (std::getline(in, line))
	{
		data += line;
		if (!in.eof()) data += L"\n";
	}
	return true;
}

// Run a pass / fail test
int runTestType(bool type, int offset)
{
	int test = 0;
	std::wstring data = L"", name = L"";
	std::ostringstream stream;
	std::wostringstream wstream;

	while (true)
	{
		stream.str("");
		stream << "TestCases/" << (type ? "pass" : "fail") << (++test) << ".json";
		if (getFile(stream.str(), name, data) == false) break;

		std::wcout << L"|" << std::setw(2) << offset + test  << " | ";

		wstream.str(L"");
		wstream.setf(std::ios_base::left, std::ios_base::adjustfield);
		wstream << std::setw(DESC_LENGTH) << name;
		std::wcout << wstream.str().c_str();

		std::wcout << " | ";
		std::wcout << (parseCheck(data) != type ? L"failed" : L"passed");
		std::wcout << L" |\n";
	}

	return test;
}

// Tests to run
void runTests()
{
	int count = 0;

	std::wstring vert_sep = std::wstring(L"+---+-") + std::wstring(DESC_LENGTH, L'-') + std::wstring(L"-+--------+\r\n");

	std::wcout << vert_sep.c_str();

	std::wstring header = std::wstring(L"|   | Test case") + std::wstring(DESC_LENGTH - 9, L' ') + std::wstring(L" | Result |\r\n");
	std::wcout << header.c_str();

	std::wcout << vert_sep.c_str();

	count = runTestType(true, 0);
	count += runTestType(false, count);

	// Static test for a very precise decimal number
	double decimal = 40.9358215191158457340974;
	JSONValue *json_value = JSON::Parse("40.9358215191158457340974");
	std::wstring test_output = std::wstring(L"|") + std::to_wstring(count) + std::wstring(L" | Very precise decimal number") + std::wstring(DESC_LENGTH - 27, L' ') + std::wstring(L" | ");
	if (json_value && json_value->IsNumber() && json_value->AsNumber() == decimal)
	{
		test_output += std::wstring(L"passed |\r\n");
		delete json_value;
	}
	else
	{
		test_output += std::wstring(L"failed |\r\n");
	}
	std::wcout << test_output.c_str();
	count++;

	// Static test for a decimal number with leading zeros
	decimal = 1.00034985734000;
	json_value = JSON::Parse("1.00034985734000");
	test_output = std::wstring(L"|") + std::to_wstring(count) + std::wstring(L" | Decimal number with leading zeros") + std::wstring(DESC_LENGTH - 33, L' ') + std::wstring(L" | ");
	if (json_value && json_value->IsNumber() && json_value->AsNumber() == decimal)
	{
		test_output += std::wstring(L"passed |\r\n");
	}
	else
	{
		test_output += std::wstring(L"failed |\r\n");
	}
	std::wcout << test_output.c_str();
	count++;

	// Test case for issue #20.
	test_output = std::wstring(L"|") + std::to_wstring(count) + std::wstring(L" | Testing for valid encoding of ASCII 126") + std::wstring(DESC_LENGTH - 39, L' ') + std::wstring(L" | ");
	std::wstring issue_20_test = L"{\"test\":\"Value \\u00E0\"}";
	json_value = JSON::Parse(issue_20_test.c_str());
	if (json_value && json_value->Stringify() == issue_20_test)
	{
		test_output += std::wstring(L"passed |\r\n");
	}
	else
	{
		test_output += std::wstring(L"failed |\r\n");
	}
	std::wcout << test_output.c_str();
	count++;

	// Test case for issue #24.
	test_output = std::wstring(L"|") + std::to_wstring(count) + std::wstring(L" | Testing JSONValue passing as value") + std::wstring(DESC_LENGTH - 34, L' ') + std::wstring(L" | ");
	JSONValue *value = JSON::Parse(EXAMPLE);
	std::wstring json_check = value->Stringify();
	JSONValue new_value(*value);
	delete value;
	if (new_value.Stringify() == json_check)
	{
		test_output += std::wstring(L"passed |\r\n");
	}
	else
	{
		test_output += std::wstring(L"failed |\r\n");
	}
	std::wcout << test_output.c_str();
	count++;

	// Test case for int initialisation of JSONValue.
	test_output = std::wstring(L"|") + std::to_wstring(count) + std::wstring(L" | Testing JSONValue int initialisation") + std::wstring(DESC_LENGTH - 36, L' ') + std::wstring(L" | ");
	JSONValue int_test = JSONValue(42);
	if (int_test.Stringify() == L"42")
	{
		test_output += std::wstring(L"passed |\r\n");
	}
	else
	{
		test_output += std::wstring(L"failed |\r\n");
	}
	std::wcout << test_output.c_str();

	std::wcout << vert_sep.c_str();
}

// Test Case entry point
int main(int argc, char **argv)
{
	ElapsedTimer timer;						// allocate on the stack

	timer.Start();
	// Required for utf8 chars
	setlocale(LC_CTYPE, "");

	runExamples();
	runTests();
	timer.Stop();
	std::cout << "\nTest duration: " << timer.DurationMillis() << "ms (milliseconds)" << std::endl;

	//std::cin.get();
	return 0;
}