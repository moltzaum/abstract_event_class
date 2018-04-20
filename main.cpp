#include <iostream>
#include <string>
#include "Bank.h"

int main() {
	std::string fileName = "input.txt";
	try {
		BankSimulation sim = BankSimulation(fileName);
	} catch (FileIOException) {
		std::cout << "The file by the name of \"" << fileName << "\" doesn't exist." << std::endl;
		return 1;
	}
}
