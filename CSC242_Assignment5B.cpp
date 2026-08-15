// CSC242_Assignment5B.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

/* ---------------------------------------------------------------------------
** I attest that this following code represents my own work and is subject to
** the plagiarism policy found in the course syllabus.
** 
** Class: 	CSC 242
** Assignment: 	Lesson # 5
** File: 	source.cpp
** Description: Random monoalphabet cipher.
**
** Author: 	Matthew Perea, Melanie Harris
** Date: 	08/13/2026
** -------------------------------------------------------------------------*/

#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <cstdlib>

using namespace std;


/**
 * A simple class that manages all encryption and decryption logic, that way any information that
 * is encrypted (or decrypted) is handled within the class, and the main program just gets the result.
 */
class MonoalphabetCipher
{
private:
	string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	string cipherAlphabet;

	// creates the cipher alphabet with the keyword.
	void createCipher(string keyword)
	{
		cipherAlphabet = "";

		// adds the letters that are not duplicates.
		for (int i = 0; i < keyword.length(); i++) 
		{
			char letter = toupper(keyword[i]);

			if (isalpha(letter) && cipherAlphabet.find(letter) == string::npos)
			{
				cipherAlphabet += letter;
			}
		}
		// adds the unused letters in reverse order.
		for (int i = alphabet.length() - 1; i >= 0; i--) 
		{
			char letter = alphabet[i];

			if (cipherAlphabet.find(letter) == string::npos)
			{
				cipherAlphabet += letter;
			}
		}
	}

	// encrypts a character
	char encryptCharacter(char letter)
	{
		char upperLetter = toupper(letter);

		size_t position = alphabet.find(upperLetter);

		// if it is not a letter leave it.
		if (position == string::npos)
		{
			return letter;
		}

		char result = cipherAlphabet[position];

		// returns to a lowercase if was lowercase.
		if (islower(letter))
		{
			result = tolower(result);
		}
		
		return result;
	}

	// decrypts a character
	char decryptCharacter(char letter)
	{
		char upperLetter = toupper(letter);

		size_t position = cipherAlphabet.find(upperLetter);

		// if it is not a letter leave it.
		if (position == string::npos)
		{
			return letter;
		}

		char result = alphabet[position];

		// returns to a lowercase if was lowercase.
		if (islower(letter))
		{
			result = tolower(result);
		}

		return result;
	}

	// encrypts a file
	void encryptFile()
	{
		ifstream inputFile(GetInputFileName());
		if (!inputFile)
		{
			cout << "Error opening the input file." << endl;
			return;
		}

		ofstream outputFile(GetOutputFileName());
		if (!outputFile)
		{
			cout << "Error creating or opening the output file. Do you have permission?" << endl;
			return;
		}

		char letter;
		while (inputFile.get(letter))
		{
			outputFile << encryptCharacter(letter);
		}

		inputFile.close();
		outputFile.close();

		cout << "The file was encrypted successfully." << endl;
	}

	// decrypts a file
	void decryptFile()
	{
		ifstream inputFile(GetInputFileName());
		if (!inputFile)
		{
			cout << "Error opening the input file." << endl;
			return;
		}

		ofstream outputFile(GetOutputFileName());
		if (!outputFile)
		{
			cout << "Error creating or opening the output file. Do you have permission?" << endl;
			return;
		}

		char letter;

		while (inputFile.get(letter))
		{
			outputFile << decryptCharacter(letter);
		}

		inputFile.close();
		outputFile.close();

		cout << "The file was decrypted successfully." << endl;

	}

	string mInputFileName;
	string mOutputFileName;

public:

	const string& GetInputFileName() const  { return mInputFileName;  }
	const string& GetOutputFileName() const { return mOutputFileName; }

	bool IsValidFile(const string& FileName)
	{
		if (FileName.empty()) return false;
		ifstream FileToTest(FileName);
		return FileToTest.good();
	};

	// runs the program based on arguments
	bool parseArguments(int argc, char* argv[], string& choice, string& keyword)
	{
		if (argc != 5)
		{
			cerr << "Usage: <-e|-d> -k<keyword> <input_file> <output_file>" << endl;
			return false;
		}

		string CryptDirection{ argv[1] };
		string KeywordArg{ argv[2] };

		if (CryptDirection == "-d")
			choice = "D";

		else if (CryptDirection == "-e")
			choice = "E";

		else
		{
			cerr << "Invalid Crypt Direction. Use -e or -d.";
			return false;
		}

		if (KeywordArg.substr(0, 2) != "-k")
		{
			cerr << "Crypt Keyword must be specified using -k<keyword>, without spaces.";
			return false;
		}

		keyword = KeywordArg.substr(2); // Trim -k and leave the rest.
		mInputFileName = argv[3];
		if (!IsValidFile(GetInputFileName()))
		{
			cerr << "The input file could not be opened as specified: " << GetInputFileName() << endl;
			return false;
		}

		mOutputFileName = argv[4];
		if (GetInputFileName() == GetOutputFileName())
		{
			cerr << "Input and Output files must be different." << endl;
			return false;
		}

		return true;
	}

	// runs the program
	void run()
	{
		string choice;
		string keyword;
		string inputFile;
		string outputFile;

		cout << "Random Monoalphabetic Cipher" << endl;
		cout << "----------------------------" << endl;

		do
		{
			cout << "Enter 'E' (or leave blank) to encrypt or 'D' to decrypt: ";
			getline(cin, choice);

			if (choice.empty())
				choice = 'E';

			choice = toupper(choice[0]);
			if (choice != "E" && choice != "D")
				cerr << "Invalid Selection" << endl;

		} while (choice != "E" && choice != "D");

		// Ensures a keyword is provided (assignment requirement).
		do
		{
			cout << "Enter the keyword: ";
			getline(cin, keyword);

			if (keyword.empty())
				cerr << "Keyword cannot be empty. Try again." << endl;

		} while (keyword.empty());

		// Validate input file as a valid file.
		do
		{
			cout << "Enter the input file name: ";
			getline(cin, inputFile);

		} while (!IsValidFile(inputFile));
		mInputFileName = inputFile;

		// Ensure output file is a valid target and not the same as the input file.
		do
		{
			cout << "Enter the output file name (relative to project folder): ";
			getline(cin, outputFile);

			if (outputFile.empty())
				cerr << "Output file must be specified. Try again." << endl;

			else if (outputFile == GetInputFileName())
				cerr << "Input and Output files must be a different file. Try again." << endl;

		} while (outputFile.empty() || outputFile == GetInputFileName());
		mOutputFileName = outputFile;

		Algorithm(choice, keyword);
	}

	void Algorithm(const string& InChoice, const string& InKeyword)
	{
		createCipher(InKeyword);
		if (InChoice == "E")	  encryptFile();
		else if (InChoice == "D") decryptFile();
		else					  cout << "Invalid selection." << endl;
	}

};

// main driver
int main(int argc, char* argv[])
{
	MonoalphabetCipher Cipher;

	if (argc == 1)
	{
		Cipher.run();
		return EXIT_SUCCESS;
	}

	string choice, keyword;
	if (!Cipher.parseArguments(argc, argv, choice, keyword))
		return EXIT_FAILURE;

	Cipher.Algorithm(choice, keyword);
	return EXIT_SUCCESS;
}
