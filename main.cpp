// SimpleJSON
// Link: https://github.com/MJPA/SimpleJSON

#include <chrono>
#include <ctime>
#include <iostream>
#include "elapseTimer.h"
#include "functions.h"

// Forward function declarations
bool SimpleTest(bool v = false);

int main(int argc,char* argv[]) {
	ElapsedTimer timer;						// allocate on the stack

	printf("SimpleJSON Unit Tests:\n");

	timer.Start();
	printf("Parsing some simple Json data.\n");
	if (SimpleTest(true))
		printf("\nSimple test passed!\n");
	else
		printf("\nSimple test FAILED!\n");

	printf("Example 1 : Parse more complicated Json data.\n");
	if(example1(true))
		printf("\nExample 1 passed!\n");
	else
		printf("\nExample 1 FAILED!\n");
	printf("\n");
	printf("Example 2 : Add Json elements and data.\n");
	if (example2(true))
		printf("\nExample 2 passed!\n");
	else
		printf("\nExample 2 FAILED!\n");
	printf("\n");
	printf("Example 3 : Print Json compact vs prettyprint.\n");
	if (example3(true))
		printf("\nExample 3 passed!\n");
	else
		printf("\nExample 3 FAILED!\n");
	printf("\n");
	printf("Example 4 : List keys in an object.\n");
	if (example4(true))
		printf("\nExample 4 passed!\n");
	else
		printf("\nExample 4 FAILED!\n");
	printf("\n");


	timer.Stop();
	std::cout << "\nDuration: " << timer.DurationMillis() << "ms (milliseconds)" << std::endl;


	return 0;
}