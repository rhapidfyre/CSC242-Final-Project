// CSC242_Assignment5B.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

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
	void encryptFile(string inputName, string outputName)
	{
		ifstream inputFile(inputName);
		ofstream outputFile(outputName);

		if (!inputFile)
		{
			cout << "Error opening the input file." << endl;
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
	void decryptFile(string inputName, string outputName)
	{
		ifstream inputFile(inputName);
		ofstream outputFile(outputName);

		if (!inputFile)
		{
			cout << "Error opening the input file." << endl;
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

public:

	// runs the program
	void run()
	{
		string choice;
		string keyword;
		string inputFile;
		string outputFile;

		cout << "Random Monoalphabetic Cipher" << endl;
		cout << "----------------------------" << endl;

		cout << "Enter 'E' to encrypt or 'D' to decrypt: ";
		cin >> choice;

		cout << "Enter the keyword: ";
		cin >> keyword;

		cout << "Enter the input file name: ";
		cin >> inputFile;

		cout << "Enter the output file name: ";
		cin >> outputFile;

		createCipher(keyword);

		if (choice == "E" || choice == "e")
		{
			encryptFile(inputFile, outputFile);
		}
		else if (choice == "D" || choice == "d")
		{
			decryptFile(inputFile, outputFile);
		}
		else
		{
			cout << "Invalid selection." << endl;
		}
	}

};

// main driver
int main()
{
	MonoalphabetCipher Cipher;

	Cipher.run();

	return 0;
}