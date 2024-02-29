#include <iostream>
#include <fstream>
#include <cctype>

using namespace std;

bool moveToEndOfChain(int& j, string word);

void writeValidWord(string mask, string word, ofstream& outputFile)
{
    int i = 0, j = 0, last, first, quantity;
    while (i < mask.length())
    {
        if (mask[i] == '%') 
        {
            first = j;
            if (moveToEndOfChain(j, word) == true)
            {
                last = j;
                quantity = (last - first) + 1;
                outputFile << quantity << '(' << word[j] << ')';
            }
            i++;
            j++;
        }
        else if (mask[i] == word[j])
        {
            outputFile << mask[i];
            i++;
            j++;
        }
    }
    outputFile << ' ';
}

bool moveToEndOfChain(int& j, string word)
{
    int buffer = j;
    while (j < word.length())
    {
        if (word[buffer] == word[buffer + 1])
        {
            j++;
        }
        else 
        {
            break;
        }
        buffer = j;  
    }
    return true;
}

void patternMatcher(string mask, string word, ofstream& outputFile)
{
    int i = 0, j = 0;
    while (i < mask.length() || j < word.length())
    {
        if (mask[i] == '%' && isalpha(word[j]))
        {
            moveToEndOfChain(j, word);
            i++;
            j++;
        }
        else if (mask[i] == word[j])
        {
            i++;
            j++;
        }
        else
        {
            return;
        }
    }
    writeValidWord(mask, word, outputFile);
}

void writeWordsToFile(string mask)
{
    ifstream file("input.txt");
    if (!file.is_open()) {
        cout << "File is not open";
        return;
    }
    ofstream outputFile("output.txt");
    if (!file.is_open()) {
        cout << "File is not open";
        return;
    }

    string word;

    cout << "Input file" << endl;

    while (file >> word) {
        cout << word << ' ';
        patternMatcher(mask, word, outputFile);
    }

    outputFile.close();

    ifstream fileOut("output.txt");
    if (!fileOut.is_open()) {
        cout << "File is not open";
        return;
    }

    cout << endl << "Output file" << endl;
    while (fileOut >> word) {
        cout << word << ' ';
    }

    file.close();
    outputFile.close();
}

int main()
{   
    string mask;
    cout << "Input mask:" << endl;
    cin >> mask;
    writeWordsToFile(mask);
    return 0;
}
/*
mask = %%
input file = aaaaaa ===== 11111 aaabbb aaaadddds sssddd aappaapp //sd// ooww
output file = a(3)b(3) s(3)d(3) o(2)w(2) 

mask = abc%
input file = abcccc cbdddd abc0000 abcdddd abcrrrr abc5555 abrrr333 000000abc
output file = abcc(3) abcd(4) abcr(4) 

mask = %cb
input file = aaaacb 555cb iiiaaasss 041cb ...cb lllcb [[[cb]]] '''cb
output file = a(4)cb l(3)cb 

mask = a%b
input file = a88b accccb aeee3 abbb1 abbbb atttb 4dddddb ddddbbbb
output file = ac(4)b at(3)b 
*/