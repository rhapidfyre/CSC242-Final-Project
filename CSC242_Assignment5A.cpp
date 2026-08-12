// CSC242_Assignment5.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>

using namespace std;


/**
 * A class to centralize vector manipulation in one place.
 * Prevents having to add, remove, search, erase, etc., in multiple places in the code.
 */
class WordContainer
{

public:

	int Contains(string CompareWord) const
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

	bool Add(string WordToAdd)
	{
		// Only add the word if it doesn't exist yet.
		if (Contains(WordToAdd) < 0)
			_WordsList.push_back(WordToAdd);
	}

	bool Remove(string WordToRemove)
	{
		// If the word doesn't exist, nothing needs to be done.
		int FoundIndex = Contains(WordToRemove);
		if (FoundIndex < 0)
			return;

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

	// Read in the words file, add the words, then perform the algo.

}