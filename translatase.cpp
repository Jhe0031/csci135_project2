#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>

using namespace std;

int main() {
	ifstream fin("dna2b.txt"); //Opens file
	if (fin.fail()) { //Sets fail code
	    cerr << "File cannot be read, opened, or does not exist.\n"; //Prints fail message
	    exit(1); //Exits fail code
	}
	string strand; //Creates integer to input string into
	string new_s = "";
	while(getline(fin, strand)) { //Reads file and inputs into string strand
	    for (int i = 0; i < strand.length(); i+0) { //Sets for loop
	    	if (strand[i] == 'A' || strand[i] == 'a') { //Checks if the letter is A
	    		new_s += "U"; //Changes letter to U
	    	} else if (strand[i] == 'T' || strand[i] == 't') { //Checks if the letter is T
	    		new_s += "A"; //Changes letter to A
	    	} else if (strand[i] == 'C' || strand[i] == 'c') { //Checks if the letter is C
	    		new_s += "G"; //Changes letter to G
	    	} else if (strand[i] == 'G' || strand[i] == 'g') { //Checks if the letter is G
	    		new_s += "C"; //Changes leter to C
	    	} else { //Otherwise
	    		new_s += ""; //Prints a new line
	    	}
	    	i += 1;
	    }
	    new_s += ""; //Prints a new line when string reaches its end
	}
	fin.close();

	ifstream dict("codons.tsv"); //Opens file
	if (dict.fail()) { //Sets fail code
	    cerr << "File cannot be read, opened, or does not exist.\n"; //Prints fail message
	    exit(1); //Exits fail code
	}
	int j = 0;
	string codon = "";
	string three = "";
	while (j < new_s.length()) {
		for (int k = 0; k < 3; k++) {
			three += new_s[j];
			j += 1;
		}
		if (three == "AUG") {
			while (j < new_s.length()) {
				if (three == "UAA" || three == "UGA" || three == "UAG") {
					codon = codon.substr(0, codon.size()-1);
					codon += "\n";
					three = "";
					break;
				}
				string key, value;
				dict.clear(); // reset error state
				dict.seekg(0); // return file pointer to the beginning
				while (dict >> key >> value) {
					if (key == three) {
						codon += value;
						codon += "-";
					}
				}
				three = "";
				for (int k = 0; k < 3; k++) {
					three += new_s[j];
					j += 1; 
				}
			}
		} else {
			three = "";
		}
		if (j >= new_s.length()) {
			codon = codon.substr(0, codon.size()-1);
		}
	}
	cout << codon;
	fin.close(); //Closes file
	return 0;
}