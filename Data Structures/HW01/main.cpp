
#include <string>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <iostream>

const std::string ALPHABET("ABCDEFGHIJKLMNOPQRSTUVWXYZ");

//Prints correctly formatted chart.
void printchart(std::vector<std::vector<std::string> > & seat_chart) {
  std::cout <<"\tA    B    C    D    E    F    G    Seating Class"<<std::endl;
  for (unsigned int i=0; i < seat_chart.size(); i++) {
    std::cout << i+1 <<"\t";
    for (unsigned int j = 1; j < 8; j++) {
      if (seat_chart[i][j] == "."){
        std::cout << "...."<<" ";}
      else if ( seat_chart[i][j] == "!") {
        std::cout << "!!!!"<<" ";}
      else {
          std::cout << seat_chart[i][j]<<" ";}
    }
    std::cout << seat_chart[i][0]<<std::endl;
  }
}

//Removes an ID from the upgrade vectors
void removefromlist(const std::string pass_id, std::vector<std::string> &list) {
   std::vector<std::string> temp_vec;
  int location;
  for (unsigned int i=0; i < list.size(); i++) {
    if (list[i] == pass_id) {
      location = i;}}
  for (unsigned int i = 0; i < list.size(); i++) {
    if (i != location) {
      temp_vec.push_back(list[i]);}}
    list = temp_vec;
  } 


void noseat(std::string pass_id, std::string seat_class) {
//Note: The instructions said to use this error but file output and submitty output neglected it
//std::cout<< "Could not find a seat in the "<<seat_class<< " section for passenger "<<
//pass_id <<"."<< std::endl;
}

//Given function
bool GetSeatRowCol(const std::string& seat_request,
       unsigned int total_rows,
       unsigned int total_columns,
       int& seat_row, std::size_t& seat_col) {
  std::string row_str;
  std::string col_str;
  for (unsigned int i = 0; i < seat_request.size(); ++i) {
    if (seat_request[i] >= '0' && seat_request[i] <= '9')
      row_str += seat_request[i];
    else
      col_str += seat_request[i]; 
  }
    
  seat_row = atoi(row_str.c_str()) - 1;
  if (seat_row < 0 || seat_row > (int) total_rows - 1) {
    return false;
  }

  seat_col = ALPHABET.find(col_str)+1;
  if (seat_col == std::string::npos || seat_col > total_columns - 1) {
    return false;
  }

  return true;
}

/*Search Functions:
Iterate through 2D vector for first available seat, then replaces period with ID*/


//Searches the First class section
bool searchF(std::string pass_id, std::vector<std::vector<std::string> > & seat_chart){
  for (unsigned int i=0; i < seat_chart.size(); i++) {
    if (seat_chart[i][0] == "F") {
      for (unsigned int j=1; j < 8; j++) {
        if (seat_chart[i][j] == ".") {
          seat_chart[i][j] = pass_id;
          std::cout<<"Passenger "<< pass_id<<" was given seat "<<i+1<<ALPHABET[j-1]<<"."<<std::endl;
          return true;}}

    }   
  }
  return false;
}
//Searches the Business class section
bool searchB(std::string pass_id, std::vector<std::vector<std::string> > & seat_chart){
  for (unsigned int i=0; i < seat_chart.size(); i++) {
    if (seat_chart[i][0] == "B") {
      for (unsigned int j=1; j < 8; j++) {
        if (seat_chart[i][j] == ".") {
          seat_chart[i][j] = pass_id;
          std::cout<<"Passenger "<< pass_id<<" was given seat " <<i+1<<ALPHABET[j-1]<<"."<<std::endl;

          return true;}}

    }   
  }
  return false;
}

//Searches Coach class
//First searches every other spot because they are aisle or window seats, 
//then searches the leftover seats.
bool searchC(std::string pass_id,  std::vector<std::vector<std::string> > & seat_chart){
  for (unsigned int i=0; i < seat_chart.size(); i++) {
    if (seat_chart[i][0] == "C") {
      for (unsigned int j=1; j < 8; j+=2) {
        if (seat_chart[i][j] == ".") {
          seat_chart[i][j] = pass_id;
          std::cout<<"Passenger "<< pass_id<<" was given seat "<<i+1<<ALPHABET[j-1]<<"."<<std::endl;
          return true;}}}
        }
    for (unsigned int i=0; i < seat_chart.size(); i++) {
    if (seat_chart[i][0] == "C") {
            for (unsigned int j=2; j < 8; j+=4) {
              if (seat_chart[i][j] == ".") {
              seat_chart[i][j] = pass_id;
              std::cout<<"Passenger "<< pass_id<<" was given seat "<<i+1<<ALPHABET[j-1]<<"."<<std::endl;
              return true;}}}
  }
  return false;
}


//For each B and C class if no seats are found, puts in respective upgrade queues

void exeSRN(std::string pass_id, std::string seat_class,
 std::string flyer, std::vector<std::vector<std::string> > &seat_chart,
  std::vector<std::string> &upgradeB, std::vector<std::string> &upgradeF) {

  if (seat_class == "B") {
      if (!searchB(pass_id, seat_chart)) {
        noseat(pass_id, seat_class);
        if (flyer == "Y") {
      upgradeF.push_back(pass_id);}
        }}

    else if (seat_class == "C") {
      if (!searchC(pass_id, seat_chart)) {
        noseat(pass_id, seat_class);
        if (flyer == "Y") {
      upgradeB.push_back(pass_id);}}}

    else if (seat_class == "F") {
      if(!searchF(pass_id, seat_chart)) {
        noseat(pass_id, seat_class);}}
    else {
      std::cout << "Invalid seating class - "<<seat_class<<"."<<std::endl;
    }
    }


//Same as SRN, but searches for the requested seat first
//Since class is not defined, finds the class of the selected row
void exeSSR(std::string pass_id, std::string seat_request, std::string flyer,
     std::vector<std::vector<std::string> >&seat_chart,
     std::vector<std::string> &upgradeB, std::vector<std::string> &upgradeF) {
    int seat_row;
    std::size_t seat_col;
    if (!GetSeatRowCol(seat_request, seat_chart.size(), 8,seat_row, seat_col)) {
        std::cout<<"Passenger "<<pass_id<<" requested an invalid seat "<< seat_request<<"."<<std::endl;}
    else { 
    if (seat_chart[seat_row][seat_col]==".") {
      seat_chart[seat_row][seat_col] = pass_id;
      std::cout<<"Passenger "<< pass_id<<" was given seat "<<seat_row+1<<ALPHABET[seat_col-1]<<"."<<std::endl;
    }
    else {
      if (seat_chart[seat_row][seat_col]!="!"){
        std::cout<<"Passenger "<<pass_id<<" requested an occupied seat "<< seat_request<<"."<<std::endl;}

      if (seat_chart[seat_row][0] == "B") {
      if (!searchB(pass_id, seat_chart)) {
        if (flyer == "Y") {
      upgradeF.push_back(pass_id);}}}

      else if (seat_chart[seat_row][0] == "C") {
      if (!searchC(pass_id, seat_chart)) {
        if (flyer == "Y") {
      upgradeB.push_back(pass_id);}}}
      
      else if (seat_chart[seat_row][0]== "F") {
      searchF(pass_id, seat_chart);}
      }}}
    
//Clears chose ID from seat_chart and upgrade lists.

void exeCXL(std::string pass_id, 
  std::vector<std::vector<std::string> > &seat_chart, 
  std::vector<std::string> &upgradeB, std::vector<std::string> &upgradeF) {
  //Remove from Chart
  //Remove from queues
  for (unsigned int i=0; i < seat_chart.size(); i++) {
    for (unsigned int j = 0; j < 8; j++) {
      if (seat_chart[i][j] == pass_id) {
        seat_chart[i][j] = ".";
      }}}
      removefromlist(pass_id, upgradeF);
      removefromlist(pass_id, upgradeB);
  }

//Uses search functions for all passengers in respective queues

void exeUPP(std::vector<std::vector<std::string> > &seat_chart, 
  std::vector<std::string> &upgradeB, std::vector<std::string> &upgradeF) {
  for (unsigned int i = 0; i < upgradeF.size(); i++) {
    if (searchF(upgradeF[i], seat_chart)) {
      std::cout<<"Passenger "<<upgradeF[i]<<" was upgraded to the first class section."<<std::endl;
    }
  }
  for (unsigned int i = 0; i < upgradeB.size(); i++) {
    if (searchB(upgradeB[i], seat_chart)) {
      std::cout<<"Passenger "<<upgradeB[i]<<" was upgraded to the first class section."<<std::endl;
    }
}
}


int main(int argc, char* argv[]) {

//Initialize seating chart
std::ifstream plane_row_col(argv[1]);
std::ifstream plane_read(argv[1]);
std::vector<std::vector<std::string> > seat_chart;
std::vector<std::string> row;
std::string col;
std::string plane_name = argv[1];
std::vector<std::string> upgradeB;
std::vector<std::string> upgradeF;

//Reads in plane size and seating from file
//Optimized for unknown plane sizes

int row_count = 0;
int col_count = 0;
std::string tmp;
while (plane_row_col >> tmp) {
  if (tmp == "F" || tmp == "B" || tmp == "C") {
    row_count += 1;
  }
  if (row_count == 1) {
    col_count += 1;}
}

for (int i = 0; i < row_count; i++) {
      row.clear();
      for (int j = 0; j <col_count; j++) {
        plane_read >> col;
        row.push_back(col); }
      seat_chart.push_back(row);
    }



/*if (plane_name == "acme_jet_seats.txt") {
    for (int i = 0; i < 10; i++) {
      row.clear();
      for (int j = 0; j <8; j++) {
        plane_file >> col;
        row.push_back(col);


      }
      seat_chart.push_back(row);
    }
  }
else if (plane_name == "acme_prop_seats.txt") {
  for (int i = 0; i < 4; i++) {
      row.clear();
      for (int j = 0; j <8; j++) {
        plane_file >> col;
        row.push_back(col);
        
      }
      seat_chart.push_back(row);
      }
} */

//Reads in commands
//Takes in a certain amount of other commands based on first one
//Executes functions using parameters taken in.

std::ifstream flight_file(argv[2]);
int flight_num;
flight_file >> flight_num;
std::string command;
std::vector<std::string> line;
while (flight_file >> command) {
  line.clear();
  //SRN Command
  if (command == "SRN") {
      //line.push_back(command);
      int i = 0;
      while (i < 3){
        flight_file >> command;
        line.push_back(command);
        i++;
      }
      exeSRN(line[0],line[1],line[2], seat_chart,upgradeB,upgradeF);
    }
  //SSR
  else if (command == "SSR") { 
      //line.push_back(command);
      int i = 0;
      while (i < 3){
        flight_file >> command;
        line.push_back(command);
        i++;}
        exeSSR(line[0],line[1],line[2], seat_chart,upgradeB,upgradeF);
      }
   //CXL Command
  else if (command == "CXL") { 
      flight_file >> command;
      line.push_back(command);
      exeCXL(line[0], seat_chart, upgradeB,upgradeF);}
  else if (command == "UPL") {
      std::cout<<"The following passengers are scheduled to be upgraded to first class:" << std::endl;
      for (unsigned int i = 0; i < upgradeF.size(); i++){
        std::cout << upgradeF[i]<<std::endl;}
      std::cout<<"The following passengers are scheduled to be upgraded to business class:" << std::endl;
      for (unsigned int i = 0; i < upgradeB.size(); i++){
        std::cout << upgradeB[i]<<std::endl;}
      }
  else if (command == "UPP") {
      exeUPP(seat_chart, upgradeB, upgradeF);}
  else if (command == "PRT") {
      std::cout << "Seating Chart for Flight "<<flight_num<<std::endl;
     printchart(seat_chart);
   }
  }
return 0;

}