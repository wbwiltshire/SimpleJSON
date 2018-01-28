/******************************************************************************/
// Run a simple test for the SimpleJSON library
/******************************************************************************/
#include <iostream>
#include "JSON.h"

// Just some sample JSON text, feel free to change but could break demo
const wchar_t* MSFT_EXAMPLE = L"\
{ \
	\"Ticker\" : \"MSFT\", \
	\"Name\" : \"Microsoft\", \
	\"Dividend\" : true, \
	\"Price\" : 100.01, \
	\"Founded\" : 1975 \
}    ";

bool SimpleTest(bool verbose = false) {
	bool status = true;
	JSONValue *value = JSON::Parse(MSFT_EXAMPLE);
	
	printf("\nRunning Simple Test->\n");
	if (value == NULL) {
		std::cout << "Oops, something went wrong!" << std::endl;
		status = false;
	}
	else {
		//Retrieve the main root
		JSONObject root;
		if (value->IsObject() == false)
			std::cout << "The root element is not an object, did you change the example?" << std::endl;
		else {
			root = value->AsObject(); 
			if (verbose) std::cout << "\tGot the root!" << std::endl;

			// Retrieving a Ticker
			if (root.find(L"Ticker") != root.end() && root[L"Ticker"]->IsString())
			{
				if (verbose) {
					std::cout << "\tTicker: ";
					std::wcout << (root[L"Ticker"]->AsString().c_str());
					printf("\n");
				}
				if (wcsncasecmp(root[L"Ticker"]->AsString().c_str(), L"MSFT", 4) != 0)
					status = false;
			}
			else
				status = false;

			// Retrieving Name
			if (root.find(L"Name") != root.end() && root[L"Name"]->IsString())
			{
				if (verbose) {
					std::cout << "\tName: ";
					std::wcout << (root[L"Name"]->AsString().c_str());
					printf("\n");
				}
				if (wcsncasecmp(root[L"Name"]->AsString().c_str(), L"Microsoft", 9) != 0)
					status = false;
			}
			else
				status = false;

			// Retrieving Dividend flag
			if (root.find(L"Dividend") != root.end() && root[L"Dividend"]->IsBool())
			{
				if (verbose) {
					printf("\tDividend: ");
					std::wcout << (root[L"Dividend"]->AsBool() ? L"True" : L"False");
					printf("\n");
				}
				if (!root[L"Dividend"]->AsBool())
					status = false;
			}
			else
				status = false;

			// Retrieving Price
			if (root.find(L"Price") != root.end() && root[L"Price"]->IsNumber())
			{
				if (verbose) {
					printf("\tPrice: $");
					std::wcout << (root[L"Price"]->AsNumber());
					printf("\n");
				}
				if (root[L"Price"]->AsNumber() != 100.01)
					status = false;
			}
			else
				status = false;

			// Retrieving Founded
			if (root.find(L"Founded") != root.end() && root[L"Founded"]->IsNumber())
			{
				if (verbose) {
					printf("\tFounded: ");
					std::wcout << (root[L"Founded"]->AsNumber());
					printf("\n");
				}
				if (root[L"Founded"]->AsNumber() != 1975)
					status = false;
			}
			else
				status = false;
		}
	}

	return status;
}