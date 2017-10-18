// -----------------------------------------------------------------
// HOMEWORK 7 WORD FREQUENCY MAPS
//
// You may use all of, some of, or none of the provided code below.
// You may edit it as you like (provided you follow the homework
// instructions).
// -----------------------------------------------------------------

#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <cstdlib>
#include <cassert>
#include "mtrand.h"



// ASSIGNMENT: FILL IN YOUR OWN MAP STRUCTURE
typedef std::map<std::string, std::map<std::string, int> > MY_MAP;



// Custom helper function that reads the input stream looking for
// double quotes (a special case delimiter needed below), and white
// space.  Contiguous blocks of alphabetic characters are lowercased &
// packed into the word.
bool ReadNextWord(std::istream &istr, std::string &word) {
  char c;
  word.clear();
  while (istr) {
    // just "peek" at the next character in the stream
    c = istr.peek();
    if (isspace(c)) {
      // skip whitespace before a word starts
      istr.get(c);
      if (word != "") {
	// break words at whitespace
	       return true;
      }
    } 
    else if (c == '"') {
      // double quotes are a delimiter and a special "word"
      if (word == "") {
        istr.get(c);
	       word.push_back(c);
      }
      return true;
    } 

    else if (isalpha(c)) {
      // this a an alphabetic word character
      istr.get(c);
      word.push_back(tolower(c));
    } else {
      // ignore this character (probably punctuation)
      istr.get(c);
    }
  }
  return false;
}


// Custom helper function that reads the input stream looking a
// sequence of words inside a pair of double quotes.  The words are
// separated by white space, but the double quotes might not have
// space between them and the neighboring word.  Punctuation is
// ignored and words are lowercased.
std::vector<std::string> ReadQuotedWords(std::istream &istr) {
  // returns a vector of strings of the different words
  std::vector<std::string> answer;
  std::string word;
  bool open_quote = false;
  while (ReadNextWord(istr,word)) {
    if (word == "\"") {
      if (open_quote == false) { open_quote= true; }
      else { break; }
    } else {
      // add each word to the vector
      answer.push_back(word);
    }
  }
  return answer;
}



// Loads the sample text from the file, storing it in the map data
// structure Window specifies the width of the context (>= 2) of the
// sequencing stored in the map.  parse_method is a placeholder for
// optional extra credit extensions that use punctuation.
void LoadSampleText(MY_MAP &data, const std::string &filename, int window, const std::string &parse_method) {
  // open the file stream
  std::string word;
  std::string back1;
  std::string back2;
  std::ifstream istr(filename.c_str());
  if (!istr) { 
    std::cerr << "ERROR cannot open file: " << filename << std::endl; 
    exit(1);
  } 
  // verify the window parameter is appropriate
  // verify that the parse method is appropriate
  bool ignore_punctuation = false;
  if (parse_method == "ignore_punctuation") {
    ignore_punctuation = true;
  } else {
    std::cerr << "ERROR unknown parse method: " << parse_method << std::endl;
    exit(1);
  }

  std::cout<<"Loaded "<<filename<<" with window = "<<window<<" and parse method = "<<parse_method<<std::endl<<std::endl;
  ReadNextWord(istr, back1);
  while (ReadNextWord(istr,word)) {
    // skip the quotation marks (not used for this part)
    if (word == "\"") continue;
    data[back1][word]+=1;
    back1 = word;
  }

  data[back1]["last_word__"]+=1;



}


void LoadSampleText3(std::map<std::string, MY_MAP> &data3, const std::string &filename, int window, const std::string &parse_method) {
  // open the file stream
  std::string word;
  std::string back1;
  std::string back2;
  std::ifstream istr(filename.c_str());
  if (!istr) { 
    std::cerr << "ERROR cannot open file: " << filename << std::endl; 
    exit(1);
  }
  
  // verify that the parse method is appropriate
  bool ignore_punctuation = false;
  if (parse_method == "ignore_punctuation") {
    ignore_punctuation = true;
  } else {
    std::cerr << "ERROR unknown parse method: " << parse_method << std::endl;
    exit(1);
  }

  std::cout<<"Loaded "<<filename<<" with window = "<<window<<" and parse method = "<<parse_method<<std::endl<<std::endl;
  //store words in the indexes of the previous 2 words
    ReadNextWord(istr, back2);
    ReadNextWord(istr, back1);
    while (ReadNextWord(istr,word)) {
    // skip the quotation marks (not used for this part)
      if (word == "\"") continue;
      data3[back2][back1][word]+=1;
    
      back2 = back1;
      back1 = word;

  }

  //Dummy map key to signify last word, word occurs but there
  // is not enough words after it to use as map keys
  data3[back2][back1]["last_word__"]+=1;
  data3[back1][word]["last_word__"]+=1;

}

void print2(MY_MAP &data, std::vector<std::string> &words) {
    std::map<std::string, int>::iterator itr;
    int total = 0;
    for (itr = data[words[0]].begin(); itr != data[words[0]].end(); itr++ ) {
      total += itr->second;
    }
    std::cout<<words[0]<<" ("<<total<<")"<<std::endl;


    for (itr = data[words[0]].begin(); itr != data[words[0]].end(); itr++ ) {
    //Dummy key isn't an actual phrase!
     if (itr->first != "last_word__") {
      std::cout<<words[0]<<" "<<itr->first<<" ("<<itr->second<<")"<<std::endl; }
     }
    std::cout<<std::endl;
}

void print3(std::map<std::string, MY_MAP> &data, std::vector<std::string> &words) {
    int total = 0; 
  if (words.size() == 2) {
    std::map<std::string, int>::iterator itr;

    for (itr = data[words[0]][words[1]].begin(); itr != data[words[0]][words[1]].end(); itr++ ) {
      total += itr->second;
    }
    std::cout<<words[0]<<" "<<words[1]<<" ("<<total<<")"<<std::endl;

    for (itr = data[words[0]][words[1]].begin(); itr != data[words[0]][words[1]].end(); itr++ ) {
      if (itr->first != "last_word__") {
      std::cout<<words[0]<<" "<<words[1]<<" "<<itr->first<<" ("<<itr->second<<")"<<std::endl; }
    }
    std::cout<<std::endl;
  }
  
  else if (words.size() == 1) {
    MY_MAP::iterator itr;
    std::map<std::string, int>::iterator itr2;
    for (itr = data[words[0]].begin(); itr != data[words[0]].end(); itr++ ) {
      for (itr2 = itr->second.begin(); itr2 != itr->second.end(); itr2++) {
        total+= itr2->second;
      }
    }
    std::cout<<words[0]<<" ("<<total<<")"<<std::endl;

    for (itr = data[words[0]].begin(); itr != data[words[0]].end(); itr++ ) {
      int total2 = 0;
      for(itr2 = itr->second.begin(); itr2 != itr->second.end(); itr2++) {
        total2 += itr2->second;
      }
      if (itr->first != "last_word__") {
      std::cout<<words[0]<<" "<<itr->first<<" ("<<total2<<")"<<std::endl; }
    }
    std::cout<<std::endl;
  }
}

void generate2(MY_MAP &data, std::vector<std::string> &words, int n, bool random) {
  MY_MAP::iterator itr1;
  std::map<std::string, int>::iterator itr2;
  std::map<std::string, int>::iterator most;
  std::vector<std::string> sentence;

    std::string current = words[0];
    sentence.push_back(current);

    //Find n number of words
    for (int i = 0; i < n; i++) {
      itr1 = data.find(current);
      most = itr1->second.begin();
      current = itr1->second.begin()->first;
      if (!random) {
      for (itr2 = itr1->second.begin(); itr2 != itr1->second.end(); itr2++) {
        if (itr2->second > most->second) {
          current = itr2->first; //current is the next word (had the most counts)
          most = itr2; //word with current most counts
        }
      }
    }
      

      else if (random) {
        std::vector<std::string> randword;
        randword.clear();
        //search through map, store words in vector as many times as they appear
        for (itr2 = itr1->second.begin(); itr2 != itr1->second.end(); itr2++) {
          for (int i = 0; i < itr2->second; i++) {
            randword.push_back(itr2->first);
          }
        }

        //use twister to choose a random word based on frequency in vector
        static MTRand_int32 mtrand;
        int dice_rand = mtrand() % randword.size();
        current = randword[dice_rand];
      }
      sentence.push_back(current);
    }
    for (unsigned int i =0; i < sentence.size(); i++) {
      std::cout<<sentence[i];
      if (i < sentence.size()-1) {
      std::cout<<" "; }
    }

  std::cout<<std::endl<<std::endl;
}

void generate3(std::map<std::string, MY_MAP> &data, std::vector<std::string> &words, int n, bool random) {
  MY_MAP::iterator itr1;
  std::map<std::string, int>::iterator itr2;
  MY_MAP::iterator most1;
  std::map<std::string, int>::iterator most2;
  std::vector<std::string> sentence;
  std::string current2;
  unsigned int s = n+words.size()-1;

    std::string current = words[0];
    sentence.push_back(current);

  //if there is only one word, look at the sizes of the nested  maps to determine second word
  if (!random) {
  if (words.size() == 1) {
    most1 = data[current].begin();
      for (itr1 = data[current].begin(); itr1 != data[current].end(); itr1++) {
        if (itr1->second.size() > most1->second.size()) {
          most1 = itr1; }
  current2 = most1->first;
  }
}
  else {
    current2 = words[1];
  }
  sentence.push_back(current2);

//loop desired # of times, shifting words each time to get next word
  while (sentence.size() <= s) {
    most2 = data[current][current2].begin();
    for (itr2 = data[current][current2].begin(); itr2 != data[current][current2].end(); itr2++) {
      if (itr2->second > most2->second) {
        most2 = itr2;
      }
    }
    current = current2;
    current2 = most2->first;
    sentence.push_back(current2);
  }
}
//Use mersenne twister on a vector to find random word based on frequency
else if (random) {
  std::vector<std::string> randword;
  int dice_rand;
  static MTRand_int32 mtrand;
  if (words.size() == 1) {
      for (itr1 = data[current].begin(); itr1 != data[current].end(); itr1++) {
        for (unsigned int i = 0; i < itr1->second.size(); i++) {
          randword.push_back(itr1->first);
        }
      }
    dice_rand = mtrand() % randword.size();
    current2 = randword[dice_rand];
  }
 else {
  current2 = words[1];
 } 
 sentence.push_back(current2);
 while (sentence.size() <= s) {
    randword.clear();
    for (itr2 = data[current][current2].begin(); itr2 != data[current][current2].end(); itr2++) {
      for (int i = 0; i < itr2->second; i++) {
        randword.push_back(itr2->first);
      }
    }
    dice_rand = mtrand() % randword.size();
    current = current2;
    current2 = randword[dice_rand];
    sentence.push_back(current2);
  }
}


   for (unsigned int i =0; i < sentence.size(); i++) {
     std::cout<<sentence[i];
     if (i < sentence.size()-1) {
      std::cout<<" ";
     }
    }

  std::cout<<std::endl<<std::endl; 
}
int main () {

  // ASSIGNMENT: THE MAIN DATA STRUCTURE
  //Use 2 structures for ease of implementation.
  MY_MAP data2;
  std::map<std::string, MY_MAP> data3;
  // Parse each command
  std::string command;
  int window;

  while (std::cin >> command) {

    // load the sample text file
    if (command == "load") {
      std::string filename;
      std::string parse_method;
      std::cin >> filename >> window >> parse_method;
      if (window < 2) {
      std::cerr << "ERROR window size must be >= 2:" << window << std::endl;
    }
      // ASSIGNMENT: ADD YOUR COMMANDS HERE
      // Call different functions for diff structures
      if (window == 2) {
        LoadSampleText(data2, filename, window, parse_method); }
      else if (window == 3) {
        LoadSampleText3(data3, filename, window, parse_method); }

    } 

    // print the portion of the map structure with the choices for the
    // next word given a particular sequence.
    else if (command == "print") {
      std::vector<std::string> sentence = ReadQuotedWords(std::cin);
      if (window == 2) {
        print2(data2, sentence);
        sentence.clear();
      }
      else if (window == 3) {
        print3(data3, sentence);
        sentence.clear();
      }

    }

    // generate the specified number of words 
   else if (command == "generate") {
      std::vector<std::string> sentence = ReadQuotedWords(std::cin);
      // how many additional words to generate
      int length;
      std::cin >> length;
      std::string selection_method;
      std::cin >> selection_method;
      bool random_flag;
      if (selection_method == "random") {
	    random_flag = true; } 
      else {
	    assert(selection_method == "most_common");
	   random_flag = false; }
      if (window == 2) {
        generate2(data2, sentence, length, random_flag);
      }
      else if (window == 3) {
        generate3(data3, sentence, length, random_flag);
      }
     }

    else if (command == "quit") {
      break;
    } else {
      std::cout << "WARNING: Unknown command: " << command << std::endl;
    }
  }
}
