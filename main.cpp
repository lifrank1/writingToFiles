/*
  File: temperature.cpp
  Created by: Frank Li  
  Creation Date: April 19 2022
  Synopsis: Reads input temperatures and sorts them
*/

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>

using namespace std;

class Temperature
{
private:
	double degree;
	bool warm;
	double getKelvin() const;

public:
	double getDegree() const;
	void setDegree(const double temp);
	bool getWarmth() const;
	void setWarmth(const bool warmth);
	string toString() const;
};

// FUNCTION PROTOTYPES GO HERE:
string prompt();
void readTemp(vector<Temperature> & vectorTemps);
void validTemps(vector<Temperature> vectorTemps);
void writeWarmTemps(string fileName, vector<Temperature> & temps);

int main()
{	
	vector<Temperature> temps;
	string file_name;
	
	//calling created functions 
	file_name = prompt(); //retrieving file name
   readTemp(temps); //reading temps vector and determining kept ones 
	cout << "The vector size is " << temps.size() << endl << endl;
	validTemps(temps); //finding valid temps
	writeWarmTemps(file_name, temps); //writing to file (fout)

	return 0;
}
		 
// FUNCTION DEFINITIONS GO HERE:

//prompting for file name 
string prompt() {
   string fileName; //create variable
   cout << "Enter file name: "; //prompt  
   cin >> fileName; //store in variable fileName
   return fileName; //return fileName
}

//reading temps vector and determining kept temps 
void readTemp(vector<Temperature> & vectorTemps) {
   Temperature x; //object made to store 
   int numTemps = 0; //declare number of temperatures variable 
   double temp = 0; //declare temp variable to store the user inputted temp 
   int keptTemps = 0; //declare number of kept temperatures variable for later output 
   cout << "Number of temperatures you will enter: "; //prompt
   cin >> numTemps; //store number of temperatures in vector 
   
   cout << "Enter temperatures (Fahrenheight): "; //prompt fo the temperatures to be stored if valid
   for (int i = 0; i < numTemps; i++) {
      cin >> temp; 
      if (temp >= 30 && temp <= 100) {
         x.setDegree(temp); //if its valid then set x to the temp
         if (temp >= 60 && temp <= 78) {
            x.setWarmth(true); //if its warm then set warm of x to true 
         }
         else {
            x.setWarmth(false); //if not warm then set warm of x to false 
         }
         vectorTemps.push_back(x); //add x to the vector (if its valid) 
      }
   }
   for (int i = 0; i < vectorTemps.size(); i++) { //checking if there are any valid temps 
      if (vectorTemps.at(i).getDegree() >= 30 && vectorTemps.at(i).getDegree() <= 100) {
         keptTemps++; //finding number of kept temperatures 
      }
   }
   cout << "\nKept " << keptTemps << " out of " << numTemps << " temperature(s)." << endl; //outputting number of kept temps 
}


//determining which temps are valid
void validTemps(vector<Temperature> vectorTemps) {
   int keptTemps = 0; //declaring number of kept temperatures 
   for (int i = 0; i < vectorTemps.size(); i++) { //checking if there are any valid temps 
      if (vectorTemps.at(i).getDegree() >= 30 && vectorTemps.at(i).getDegree() <= 100) {
         keptTemps++; //if there are valid temps then increment kept temps to determine if there are valid temps to be printed 
      }
   }
   
   //I didn't realize that I could just do if the vector size was greater or equal to 1 lol my bad
   if (keptTemps >= 1) {
      cout << "You entered the following valid temperature(s): ";
      for (int i = 0; i < vectorTemps.size(); i++) {
         if (vectorTemps.at(i).getDegree() >= 30 && vectorTemps.at(i).getDegree() <= 100) {
            cout << vectorTemps.at(i).getDegree(); //printing the degrees of each object in vector if it's valid 
            if (vectorTemps.at(i).getDegree() >= 60 && vectorTemps.at(i).getDegree() <= 78) {
               cout << " W"; //if its warm then print a W next to it 
            }
         }
         if (i < keptTemps-1) {
            cout << ", "; //formatting for , 
         }
      }
   }
   else {
      cout << "You didn't enter any valid temperatures.";
   }
}


//writing to file 
void writeWarmTemps(string fileName, vector<Temperature> & temps) {
   ofstream fout; //declare stream
   int numWarmTemps = 0;
   for (int i = 0; i < temps.size(); i++) {
      if (temps.at(i).getWarmth()) {
         numWarmTemps++; 
      }
   }
   fout.open(fileName, ios::out); //open the file
   if (!fout.is_open()) { //check if file is open 
      cerr << "Could not open file: " << fileName;
      exit(5);
   }
   
   if (numWarmTemps > 0) {
      cout << numWarmTemps << " warm temperature(s) will be written to the file '" << fileName << "'." << endl; 
      for (int i = 0; i < temps.size(); i++) {
         if (temps.at(i).getWarmth()) {
            fout << temps.at(i).toString() << endl; //print out warm samples 
         }
      }
   }
   else {
      fout << "There are no warm samples." << endl; 
   }
   
   fout.close(); //close the file 
   
}
 
 
 
// CLASS MEMBER FUNCTION DEFINITIONS GO HERE:

//get functions retrieve the private variables, set functions set them 
double Temperature::getDegree() const {
	return degree;
}
	
void Temperature::setDegree(const double temp) {
   degree = temp;
}
	
bool Temperature::getWarmth() const {
   return warm; 

}

void Temperature::setWarmth(const bool warmth) {
   warm = warmth;
}

//printing out the object degrees 
string Temperature::toString() const {
   string output = to_string(degree) + " F (" + to_string(getKelvin()) + " K)"; 
   return output;
}

//converting fahrenheight to kelvin 
double Temperature::getKelvin() const {
   return ((degree-32) * 5 / 9 + 273.15);
}
