#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include "BlastHash.h"



BlastHash::BlastHash(unsigned int size, float o, int n) {
	m_size = size;
	occupancy = o;
	m_table = std::vector<bucket>(m_size);
	contains = 0;
	k = n;
}

//Hashing Function by Paul Larson who does research at Microsoft
//source: http://stackoverflow.com/questions/98153/whats-the-best-hashing-algorithm-to-use-on-a-stl-string-when-using-hash-map
unsigned int BlastHash::hash(const char* key) {
    unsigned h = 0;
    while (*key)
        h = h * 101 + (unsigned) *key++;
    return h;
}


void BlastHash::fill(const std::string &genome) {
	gene = genome;
	std::string kmer;
	for (unsigned int i = 0; i <= genome.size()-k; i++) {
		kmer.clear();
		//Load Kmer
		for (unsigned int j = 0; j < k; j++) {
			kmer.push_back(genome[i+j]); }
		//Run through hash and insert into table
		unsigned int index = hash(kmer.c_str()) % m_size;
		
		while (index < m_table.size()) {
			//If same kmer was already inserted, add position to slot
			if (m_table[index].first == kmer) {
				m_table[index].second.push_back(i);
				contains += 1;
				break;
			}
			//If slot is empty add the first value
			else if (m_table[index].second.size() == 0) {
				m_table[index].first = kmer;
				m_table[index].second.push_back(i);
				contains += 1;
				break;
			}
			//increment index if neither cond. is satisfied.
			//circle back to beginning if run off end
			index+=1;
			if (index == m_size) {
				index = 0;
			} 
		}
		//Check occupancy and resize if needed.
		if (float(contains)/m_size > occupancy) {
			resize();
		}
	}
	
}

//Print function for QOL and debugging.
void BlastHash::print() {
	for (unsigned int i = 0; i < m_table.size(); i++) {
		std::cout<<i<<": "<<m_table[i].first<<"--";
		for (unsigned int j = 0; j < m_table[i].second.size(); j++) {
			std::cout<<m_table[i].second[j]<<",";
		}
		std::cout<<std::endl;
	}
}

//Make a new table, for each spot in old table, recalculate new index and copy data to new table
//replace old table with new one
void BlastHash::resize() {
	m_size*=2;
	std::vector<bucket> new_table = std::vector<bucket>(m_size);
	for (unsigned int i = 0; i < m_table.size(); i++) {
		int new_index = hash(m_table[i].first.c_str()) % m_size;
		new_table[new_index].first = m_table[i].first;
		new_table[new_index].second = m_table[i].second;
	}

	m_table = new_table;

}


//checking function to see if
//1: seed in the genome contains the query
//2: whether or not there is a valid number of errors
//3: printing if a similar match is found
bool BlastHash::valid_loc(std::string &sequence, int error, int seed) {
	//std::cout<<seed<<std::endl;
	int difference = 0;
	std::string segment = "";
	for (unsigned int i = 0; i < sequence.size(); i++) {
		if (seed+i == gene.size()) {
			return false; }
		if (gene[seed+i] != sequence[i]) {
			difference+=1; }
		segment.push_back(gene[seed+i]);
	}
	
	if (difference > error) {
		return false;
	}
	else {
		std::cout<<seed<<" "<<difference<<" "<<segment<<std::endl;
		return true;
	}

}

//Takes the kmer from the start of the query string
//finds index, then travels down table until that kmer is found
//for each seed in the vector of ints, test checking function to see if that spot is valid

void BlastHash::query(std::string sequence, int error) {
	std::cout<<"Query: "<<sequence<<std::endl;
	//break up query sequence
	std::string section;
	for (unsigned int i = 0; i < k; i++ ) {
		section.push_back(sequence[i]);
	}

	//find valid starting points
	unsigned int index;
	int matches = 0;
	index = hash(section.c_str()) % m_table.size();
	int circle = 0;

	//initial assumption kmer is in table
	bool foundkmer = true;
	while (m_table[index].first != section) {
		index +=1;
		circle+=1;
		if (index == m_size) {
			index = 0;
		}

		if (circle == m_size) {
			foundkmer = false;
			break;
		}
	}
	//If kmer wasn't found, don't go around searching the wrog index
	if (foundkmer) {
		for (unsigned int i = 0; i < m_table[index].second.size(); i++) {
			if (valid_loc(sequence, error, m_table[index].second[i]))
				matches+=1;
		}
	}
	if (matches == 0)
		std::cout<<"No Match"<<std::endl;
}
