#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <cmath>

using namespace std;

string mrna(string strand) {
	string new_s = "";
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
	return new_s;
}

string codon(string new_s, ifstream &dict) {
	if (dict.fail()) { //Sets fail code
	    cerr << "codons.tsv: File cannot be read, opened, or does not exist.\n"; //Prints fail message
	    // exit(1); //Exits fail code
	}
	int j;
	string codon = "";
	string three = "";
	for (int i = 0; i < new_s.length(); i++) {
		if (new_s[i] == char(65) && new_s[i+1] == char(85) && new_s[i+2] == char(71)) {
			j = i;
			break;
		}
	}
	while (j < new_s.length()) {
		for (int k = 0; k < 3; k++) {
			three += new_s[j];
			j += 1;
		}
		if (three == "UAA" || three == "UGA" || three == "UAG") {
			codon = codon.substr(0, codon.size()-1);
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
		// for (int k = 0; k < 3; k++) {
		// 	three += new_s[j];
		// 	j += 1; 
		// }
		if (j >= new_s.length()) {
			codon = codon.substr(0, codon.size()-1);
		}
	}
	return codon;
}

int main() {
	ifstream fin("frameshift_mutations.txt"); //Opens file
	if (fin.fail()) { //Sets fail code
	    cerr << "frameshift_mutations.txt: File cannot be read, opened, or does not exist.\n"; //Prints fail message
	    exit(1); //Exits fail code
	}
	string norm, frame; // Creates string variables to hold the two lines
	while (getline (fin, norm), getline (fin, frame)) { // Takes in the two lines
		string new_norm = mrna(norm);
		string new_frame = mrna(frame);

		ifstream read_dict("codons.tsv");
		string norm_codon = codon(new_norm, read_dict);
		string frame_codon = codon(new_frame, read_dict);
		cout << norm_codon << "\n" << frame_codon << "\n";
	}
	fin.close();
	return 0;
}