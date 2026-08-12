// CSC242_Assignment5.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>

using namespace std;


namespace Helpers
{
	/** @brief  Prints the given message out to the terminal, and then flushes the buffer.
	*
	* @param InValue    The value to output to the terminal.
	*/
	template <typename T>
	void PrintLine(const T& InValue)
	{
		std::cout << InValue << std::endl;
	}

	/** @brief  As PrintLine, but for errors.
	*
	* @param ErrorContext   The error to output to the terminal.
	*/
	void PrintError(const std::string& ErrorContext)
	{
		std::cerr << ErrorContext << std::endl;
	}

	/** @brief  Captures user input as string, assigning input by reference.
	*
	* @param UserInput  The variable to assign the captured input.
	*/
	void Input(std::string& UserInput)
	{
		getline(cin, UserInput); // Capture the entire line this time.
	}
}


/**
 * A class to centralize vector manipulation in one place.
 * Prevents having to add, remove, search, erase, etc., in multiple places in the code.
 */
class WordContainer
{

public:

	/** @brief Checks if the Words List contains the specified word.
	* 
	* @param CompareWord	The word to test against the word list. Must be exact. Case sensitive.
	* @return				-1 on failure, otherwise the index of the vector where the word was found.
	*/
	int Contains(const string& CompareWord) const
	{
		int Index = 0;
		for (const auto& Word : _WordsList)
		{
			if (Word == CompareWord)
				return Index;

			Index++;
		}
		return -1;
	}

	/** @brief Adds the given word to the vector if it does not already exist within it.
	*
	* @param WordToAdd	The word to be added.
	* @return			True on success, false if the word already exists.
	*/
	bool Add(const string& WordToAdd)
	{
		/* TODO - The assignment doesn't call for this, and it slows it down with O(n) lookup... Is it necessary?
		* 
		// Only add the word if it doesn't exist yet.
		if (Contains(WordToAdd) >= 0)
			return false;
		*/

		_WordsList.push_back(WordToAdd);
		return true;
	}

	/** @brief Removes the given word from the vector if it exists.
	*
	* @param WordToAdd	The word to be removed.
	* @return			True on success, false if the word wasn't found.
	*/
	bool Remove(const string& WordToRemove)
	{
		// If the word doesn't exist, nothing needs to be done.
		int FoundIndex = Contains(WordToRemove);
		if (FoundIndex < 0)
			return false;

		// https://cplusplus.com/reference/vector/vector/erase/
		_WordsList.erase(_WordsList.begin() + FoundIndex);
	}

private:
	vector<string> _WordsList;

};


// main driver
int main()
{
	WordContainer WordsList;
	string		  DictionaryFileName;
	string		  ChallengeFileName;
	string		  DictionaryWord;
	string		  ChallengeWord;
	
	cout << "Enter the file path, or press Enter to use the included 'words.txt'." << endl;
	Helpers::Input(DictionaryFileName);

	if (DictionaryFileName.empty())
		DictionaryFileName = "words.txt";

	ifstream DictionaryFile(DictionaryFileName);
	if (!DictionaryFile.is_open())
	{
		Helpers::PrintError("Could not open dictionary file: " + DictionaryFileName);
		return EXIT_FAILURE;
	}

	// Add each line in the file until there's nothing left.
	// (Stream reads data first, then returns a success boolean, while eof() performs a check before the read)
	// https://stackoverflow.com/questions/23175114/difference-between-whilefile-eof-and-whilefile-variable
	while (DictionaryFile >> DictionaryWord)
		WordsList.Add(DictionaryWord);

	DictionaryFile.close();

	cout << "Enter the file to challenge against the dictionary file, or press Enter to use the included 'words_test.txt'." << endl;
	Helpers::Input(ChallengeFileName);

	if (ChallengeFileName.empty())
		ChallengeFileName = "words_test.txt";

	ifstream ChallengeFile(ChallengeFileName);
	if (!ChallengeFile.is_open())
	{
		Helpers::PrintError("Could not open challenge file: " + ChallengeFileName);
		return EXIT_FAILURE;
	}

	while (ChallengeFile >> ChallengeWord)
	{
		// Print the word if it's not in the dictionary list.
		if (WordsList.Contains(ChallengeWord) < 0)
			cout << ChallengeWord << '\n';
	}

	ChallengeFile.close();
	return EXIT_SUCCESS;
}