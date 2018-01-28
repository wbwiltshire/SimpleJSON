/*
* File demo/example.cpp part of the SimpleJSON Library Demo - http://mjpa.in/json
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

#include <iostream>
#include <string>
#include <sstream>
#include <time.h>
#include "JSON.h"
#include "functions.h"

// Just some sample JSON text, feel free to change but could break demo
const wchar_t* EXAMPLE = L"\
{ \
	\"string_name\" : \"string\tvalue and a \\\"quote\\\" and a unicode char \\u00BE and a c:\\\\path\\\\ or a \\/unix\\/path\\/ :D\", \
	\"bool_name\" : true, \
	\"bool_second\" : FaLsE, \
	\"null_name\" : nULl, \
	\"negative\" : -34.276, \
	\"sub_object\" : { \
						\"foo\" : \"abc\", \
						 \"bar\" : 1.35e2, \
						 \"blah\" : { \"a\" : \"A\", \"b\" : \"B\", \"c\" : \"C\" } \
					}, \
	\"array_letters\" : [ \"a\", \"b\", \"c\", [ 1, 2, 3  ]  ] \
}    ";

// Example 1
bool example1(bool verbose = false)
{
	bool status = true;
	// Parse example data
	JSONValue *value = JSON::Parse(EXAMPLE);

	// Did it go wrong?
	if (value == NULL)
	{
		if (verbose) std::wcout << L"Example code failed to parse, did you change it?\n";
		status = false;
	}
	else
	{
		// Retrieve the main object
		JSONObject root;
		if (value->IsObject() == false)
		{
			if (verbose) std::wcout << L"The root element is not an object, did you change the example?\n";
			status = false;
		}
		else
		{
			root = value->AsObject();

			// Retrieving a string
			if (root.find(L"string_name") != root.end() && root[L"string_name"]->IsString())
			{
				if (verbose) {
					std::wcout << L"string_name:\n";
					std::wcout << L"------------\n";
					std::wcout << root[L"string_name"]->AsString().c_str();
					std::wcout << L"\n\n";
				}
			}

			// Retrieving a boolean
			if (root.find(L"bool_second") != root.end() && root[L"bool_second"]->IsBool())
			{
				if (verbose) {
					std::wcout << L"bool_second:\n";
					std::wcout << L"------------\n";
					std::wcout << (root[L"bool_second"]->AsBool() ? L"it's true!" : L"it's false!");
					std::wcout << L"\n\n";
				}
			}

			// Retrieving an array
			if (root.find(L"array_letters") != root.end() && root[L"array_letters"]->IsArray())
			{
				JSONArray array = root[L"array_letters"]->AsArray();
				if (verbose) {
					std::wcout << L"array_letters:\n";
					std::wcout << L"--------------\n";
					for (unsigned int i = 0; i < array.size(); i++)
					{
						std::wstringstream output;
						output << L"[" << i << L"] => " << array[i]->Stringify() << L"\n";
						std::wcout << output.str().c_str();
					}
					std::wcout << L"\n";
				}
			}

			// Retrieving nested object
			if (root.find(L"sub_object") != root.end() && root[L"sub_object"]->IsObject())
			{
				if (verbose) {
					std::wcout << L"sub_object:\n";
					std::wcout << L"-----------\n";
					std::wcout << root[L"sub_object"]->Stringify().c_str();
					std::wcout << L"\n\n";
				}
			}
		}

		delete value;

	}

	return status;
}

// Example 2
bool example2(bool verbose = false)
{
	bool status = false;
	JSONObject root;

	// Adding a string
	root[L"test_string"] = new JSONValue(L"hello world");

	// Create a random integer array
	JSONArray array;
	srand((unsigned)time(0));
	for (int i = 0; i < 10; i++)
		array.push_back(new JSONValue((double)(rand() % 100)));
	root[L"sample_array"] = new JSONValue(array);

	// Create a value
	JSONValue *value = new JSONValue(root);

	// Print it
	if (verbose) std::wcout << value->Stringify().c_str();
	std::wstring out = value->Stringify().c_str();
	if (out.length() > 0) status = true;

	// Clean up
	delete value;

	return status;
}

// Example 3 : compact vs. prettyprint
bool example3(bool verbose = false)
{
	bool status = true;
	const wchar_t* EXAMPLE3 =
		L"{\
	 \"SelectedTab\":\"Math\",\
	 	\"Widgets\":[\
			{\"WidgetPosition\":[0,369,800,582],\"WidgetIndex\":1,\"WidgetType\":\"WidgetCheckbox.1\"},\
			{\"WidgetPosition\":[235,453,283,489],\"IsWidgetVisible\":-1,\"Caption\":\"On\",\"EnableCaption\":-1,\"Name\":\"F2.View\",\"CaptionPosition\":2,\"ControlWidth\":25,\"ControlHeight\":36,\"Font\":0,\"Value\":\"Off\",\"WidgetIndex\":2,\"WidgetType\":\"WidgetCheckbox.1\"},\
			{\"WidgetPosition\":[235,494,283,530],\"IsWidgetVisible\":-1,\"Caption\":\"On\",\"EnableCaption\":-1,\"Name\":\"F3.View\",\"CaptionPosition\":2,\"ControlWidth\":25,\"ControlHeight\":36,\"Font\":0,\"Value\":\"Off\",\"WidgetIndex\":3,\"WidgetType\":\"WidgetCheckbox.1\"},\
			{\"WidgetPosition\":[235,536,283,572],\"IsWidgetVisible\":-1,\"Caption\":\"On\",\"EnableCaption\":-1,\"Name\":\"F4.View\",\"CaptionPosition\":2,\"ControlWidth\":25,\"ControlHeight\":36,\"Font\":0,\"Value\":\"Off\",\"WidgetIndex\":4,\"WidgetType\":\"WidgetCheckbox.1\"},\
			{\"WidgetPosition\":[287,417,400,439],\"IsWidgetVisible\":-1,\"Caption\":\"\",\"EnableCaption\":0,\"Name\":\"F1.Equation\",\"CaptionPosition\":1,\"ControlWidth\":113,\"ControlHeight\":22,\"Font\":0,\"AlignText\":0,\"EnableBorder\":0,\"CaptionOnly\":0,\"Value\":\"FFT(C1)\",\"WidgetIndex\":9,\"WidgetType\":\"WidgetStaticText.1\"},\
			{\"WidgetPosition\":[191,409,230,445],\"IsWidgetVisible\":0,\"Caption\":\"F1\",\"EnableCaption\":0,\"Name\":\"F1.MeasureOpGui\",\"CaptionPosition\":1,\"ControlWidth\":39,\"ControlHeight\":36,\"Font\":0,\"ButtonOnly\":-1,\"PickerTitle\":\"Select Measurement To Graph\",\"Value\":\"Amplitude\",\"WidgetIndex\":17,\"WidgetType\":\"WidgetProcessorCombobox.1\"},\
			{\"WidgetPosition\":[191,409,230,445],\"IsWidgetVisible\":-1,\"Caption\":\"F1\",\"EnableCaption\":0,\"Name\":\"F1.Operator1gui\",\"CaptionPosition\":1,\"ControlWidth\":39,\"ControlHeight\":36,\"Font\":0,\"ButtonOnly\":-1,\"PickerTitle\":\"Select Math Operator\",\"Value\":\"FFT\",\"WidgetIndex\":25,\"WidgetType\":\"WidgetProcessorCombobox.1\"},\
			{\"WidgetPosition\":[191,452,230,487],\"IsWidgetVisible\":-1,\"Caption\":\"F2\",\"EnableCaption\":0,\"Name\":\"F2.Operator1gui\",\"CaptionPosition\":1,\"ControlWidth\":39,\"ControlHeight\":36,\"Font\":0,\"ButtonOnly\":-1,\"PickerTitle\":\"Select Math Operator\",\"Value\":\"Zoom\",\"WidgetIndex\":26,\"WidgetType\":\"WidgetProcessorCombobox.1\"}\
		]\
	 }";

	// Parse example data
	JSONValue *value = JSON::Parse(EXAMPLE3);
	if (value)
	{
		if (verbose) {
			std::wcout << L"-----------\n";
			std::wcout << value->Stringify().c_str();
			std::wcout << L"\n";
			std::wcout << L"-----------\n";
			std::wcout << value->Stringify(true).c_str();
			std::wcout << L"\n";
			std::wcout << L"-----------\n";
		}
	}
	else
		status = false;

	// Clean up
	delete value;
	return status;
}

// Example 4 : List keys in an object.
bool example4(bool verbose = false)
{
	bool status = true;

	// Parse the example.
	JSONValue *main_object = JSON::Parse(EXAMPLE);
	if (main_object == NULL)
	{
		if (verbose) std::wcout << L"Example code failed to parse, did you change it?\n";
		status = false;
	}
	else if (!main_object->IsObject())
	{
		if (verbose) std::wcout << L"Example code is not an object, did you change it?\n";
		delete main_object;
		status = false;
	}
	else
	{
		if (verbose) {
			// Print the main object.
			std::wcout << L"Main object:\n";
			std::wcout << main_object->Stringify(true).c_str();
			std::wcout << L"-----------\n";

			// Fetch the keys and print them out.
			std::vector<std::wstring> keys = main_object->ObjectKeys();

			std::vector<std::wstring>::iterator iter = keys.begin();
			while (iter != keys.end())
			{
				std::wcout << L"Key: ";
				std::wcout << (*iter).c_str();
				std::wcout << L"\n";

				// Get the key's value.
				JSONValue *key_value = main_object->Child((*iter).c_str());
				if (key_value)
				{
					std::wcout << L"Value: ";
					std::wcout << key_value->Stringify().c_str();
					std::wcout << L"\n";
					std::wcout << L"-----------\n";
				}

				// Next key.
				iter++;
			}
		}
		delete main_object;
	}

	return status;
}