
// Features
// Insert word into dictionary
// Delete word from dictionary
// find word and display its meaning
// display synonim
// display antonym
// display message not found if not present in the dictionary
// exit option
// for delete insert the given word in another file  - just mark it as deleted .



#include<bits/stdc++.h>
using namespace std;
const int DEFAULT_SIZE = 26;

// 0 means deleted or not yet inserted
// 1 means present in the dictionary
class TRIENODE {
public:
	TRIENODE* CHILD[DEFAULT_SIZE]; // for alphabets from 'a' to 'z' .
	bool IsEndOfWord;
	string MEANING ;
	int NoOfWords;
	int isDeleted;// 0 means deleted or not yet inserted // 1 means present in the dictionary
	TRIENODE() // Constructor
	{
		for (int itr = 0 ; itr < DEFAULT_SIZE; itr ++)
		{
			CHILD[itr] = NULL;
		}
		IsEndOfWord = false;
		MEANING = "";
		NoOfWords = 0;
		isDeleted = 0;
	}
	void InsertWord(string, string, int);
	pair<bool, string> FindMeaningOfWord(string);
	void DeleteWord(string);
	void DisplayDictionary(string);
};


void TRIENODE::InsertWord(string Word, string Meaning, int deleted) {
	TRIENODE* CURRENT = this;
	for (int itr = 0 ; itr < (int)Word.size(); itr ++)
	{
		char CH = Word[itr];
		if (CURRENT->CHILD[CH - 'a'] == NULL)
			CURRENT->CHILD[CH - 'a'] = new TRIENODE();
		CURRENT = CURRENT->CHILD[CH - 'a'];
	}
	CURRENT->IsEndOfWord = true;
	CURRENT->isDeleted = deleted;
	NoOfWords++;
	CURRENT->MEANING = Meaning;// Assign Meaning of the WORD
}

pair<bool, string> TRIENODE::FindMeaningOfWord(string Word)
{
	if (this->NoOfWords == 0)
		return {false, "WORD NOT FOUND :("};
	TRIENODE* CURRENT = this;
	for (int itr = 0 ; itr < (int)Word.size(); itr++)
	{
		CURRENT = CURRENT->CHILD[Word[itr] - 'a'];
		if (CURRENT == NULL)
			return {false, "WORD NOT FOUND :("};

	}
	if (CURRENT->IsEndOfWord && !(CURRENT->isDeleted))
		return {true, CURRENT->MEANING};
	return {false, "WORD NOT FOUND :("};
}


void TRIENODE::DeleteWord(string Word)
{
	if (this->NoOfWords == 0)
		cout << "WORD NOT FOUND :(" << "\n";
	TRIENODE* CURRENT = this;
	for (int itr = 0 ; itr < (int)Word.size(); itr++)
	{
		CURRENT = CURRENT->CHILD[Word[itr] - 'a'];
		if (CURRENT == NULL)
			cout << "WORD NOT FOUND :(" << "\n";

	}
	if (CURRENT->IsEndOfWord && (CURRENT->isDeleted))
		cout << "WORD NOT FOUND :(" << "\n";
	CURRENT->isDeleted = 1;
	cout << "WORD DELETED SUCCESSFULLY :)" << "\n";
}




int main() {

	TRIENODE* DICTIONARY = new TRIENODE();
	std::ifstream count;
	count.open("DICT_FILE.txt", ios::binary);
	count.seekg(0, ios::end);
	int file_size = count.tellg();
	count.close();
	std::ifstream in;
	in.open("DICT_FILE.txt");
	int TrackNoofWordsreaded = 0;
	string Word, Meaning;
	int isDeleted;
	Word = "%";
	long double BYTES = 0.0000;
	cout << "\n\n\n\n\n\n\t\t\t\t\t\t\t\t\t\t\t\tLOADING..." << "0.00%";
	while (in.peek() != EOF) {
		in >> Word;
		getline(in, Meaning);
		in >> isDeleted;
		//cout << Word << " " << Meaning << "\n";
		transform(Word.begin(), Word.end(), Word.begin(), ::tolower);
		transform(Meaning.begin(), Meaning.end(), Meaning.begin(), ::tolower);
		DICTIONARY->InsertWord(Word, Meaning, isDeleted);
		TrackNoofWordsreaded++;
		BYTES += (long double)Word.size();
		BYTES += (long double)Meaning.size();
		system("CLS");
		cout << setprecision(2) << fixed;
		cout << "\n\n\n\n\n\n\t\t\t\t\t\t\t\t\t\t\t\tLOADING..." << ((long double)(BYTES) / ((long double)file_size * (1.000)))*(long double)100.000 << "%";
		//sleep(0.5);
	}
	system("CLS");
	cout << "\n\n\n\n\n\n\t\t\t\t\t\t\t\t\t\t\t\tLOADING..." << "100.00%" << "\n";
	//sleep(1);
	system("CLS");
	cout << "\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t\t\t\t\tLOADED SUCCESSFULLY :) " << "\n";
	in.close();
	while (1) {
		cout << "\n\n\t\t\t\t\t\t\t\t\t\t\t\t1.> INSERT\n\n" << "\t\t\t\t\t\t\t\t\t\t\t\t2.> FIND MEANING\n\n" << "\t\t\t\t\t\t\t\t\t\t\t\t3.>DELETE\n\n";
		int opt;
		cout << "\n\n\t\t\t\t\t\t\t\t\t\t\t\tCHOICE : ";
		cin >> opt;
		if (opt == 1) {
			string WORD, MEANING;
			cout << "\n\n\t\t\t\t\t\t\t\t\t\t\t\tENTER WORD: ";
			cin >> WORD;
			cout << "\n\n\t\t\t\t\t\t\t\t\t\t\t\tENTER MEANING: ";
			getline(cin, MEANING);
			getline(cin, MEANING);
			transform(WORD.begin(), WORD.end(), WORD.begin(), ::tolower);
			transform(MEANING.begin(), MEANING.end(), MEANING.begin(), ::tolower);
			if ((DICTIONARY->FindMeaningOfWord(WORD)).first != true) {
				std::ofstream outfile;
				outfile.open("DICT_FILE.txt", std::ios_base::app);
				outfile << WORD << " ";
				outfile << MEANING << "\n";

				DICTIONARY->InsertWord(WORD, MEANING, 0);
				outfile.close();
			}
			else {
				cout << "\n\n\t\t\t\t\t\t\t\t\t\t\t\tSEEMS LIKE THIS WORD ALREADY PRESENT :) " << "\n";
			}
			continue;
		}
		else if (opt == 2) {
			string WORD;
			cout << "\n\n\t\t\t\t\t\t\t\t\t\t\t\tENTER WORD: ";
			getline(cin, WORD);
			getline(cin, WORD);
			transform(WORD.begin(), WORD.end(), WORD.begin(), ::tolower);
			ifstream in;
			in.open("DELETE2.txt");
			string Find;
			bool isfound = false;
			while (in.peek() != EOF) {
				in >> Find;
				if (Find == WORD) {
					isfound = true;
					break;
				}
			}
			cout << isfound << "\n";
			if (isfound) {
				cout << "WORD NOT FOUND" << "\n";
				continue;
			}
			else {
				in.close();
				pair<bool, string> FIND = DICTIONARY->FindMeaningOfWord(WORD);
				cout << "\n\n\t\t\t\t\t\t\t\t\t\t\t\tTHE MEANING OF THE ENTERED WORD IS : ";
				cout << "\n\n\t\t\t\t\t\t\t\t\t\t\t\t";
				cout << FIND.second << "\n";
				continue;
			}
		}
		else if (opt == 3) {
			string Word;
			getline(cin, Word);
			getline(cin, Word);
			DICTIONARY->DeleteWord(Word);
		}
		else
			break;
	}
}