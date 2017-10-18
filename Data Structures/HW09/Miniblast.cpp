#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "BlastHash.h"

int main() {
	std::string command;
	float occupancy = 0.5;
	unsigned int table_size = 100;
	unsigned int kmer;
	std::string gene;
	int error;
	std::string sequence;
	std::cin>>command;
	if (command == "genome") {
		std::cin>>command;
		std::ifstream genome(command.c_str());
		while (genome>>command) {
			gene+=command;
		}
	}

	std::cin>>command;

	while (command != "query") {
		if (command == "occupancy") {
			std::cin>> occupancy;
			std::cin>> command; }
		else if (command == "table_size") {
			std::cin>> table_size;
			std::cin>>command; }
		else if (command == "kmer")
			std::cin>>kmer;
			std::cin>>command;
	}

	BlastHash table(table_size, occupancy, kmer);
	table.fill(gene);
		
	while (command != "quit") {
		if (command == "query") {
			std::cin>>error;
			std::cin>>sequence;
			std::cin>>command;
			table.query(sequence, error); }
	}

	//table.print();

	return 0;
}