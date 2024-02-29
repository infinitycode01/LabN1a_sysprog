#include <iostream>
#include <fstream>
#include <cctype>

using namespace std;

/*
Написати EBNF

Метасимвол – %. Зміст метасимволу – ланцюжок однакових символів
повинен бути присутнім в слові в потрібній позиції.

Маска: %hgf%l

EBNF:
<word> ::= <meta>'hgf'<meta>'l'
<meta> ::= {<any>}
<any> := <letter> | <digit> | <other>
<letter> ::= 'A' | 'B' | 'C' | 'D' | 'E' | 'F' | 'G' | 'H' | 'I' 
| 'J' | 'K' | 'L' | 'M' | 'N' | 'O' | 'P' | 'Q' | 'R' | 'S' | 'T' 
| 'U' | 'V' | 'W' | 'X' | 'Y' | 'Z' | 'a' | 'b' | 'c' | 'd' | 'e' 
| 'f' | 'g' | 'h' | 'i' | 'j' | 'k' | 'l' | 'm' | 'n' | 'o' | 'p' 
| 'q' | 'r' | 's' | 't' | 'u' | 'v' | 'w' | 'x' | 'y' | 'z'
<digit> ::= '0' | '1' | '2' | '3' | '4' | '5' | '6' | '7' | '8' | '9'
<other> ::= "~" | "_" | "!" | "@" | "#" | "$" | "%" | "^" | "&" | "*" | "(" | ")" | "-" | "+"

*/

string moveToEndOfSymbolsChain(int& i, const string& mask) {
    string newString;
    int buffer = i;
    char bufferChar;

    while (i < mask.length()) 
    {
        if (buffer <= mask.length() && mask[buffer + 1] != '%') 
        {
            bufferChar = mask[i];
            newString.push_back(bufferChar);
            i++;
        } 
        else 
        {
            break;
        }
        buffer = i;  
    }
    bufferChar = mask[i];
    newString.push_back(bufferChar);

    return newString;
}
void generateEBNF(string mask) 
{
    string symbols;

    cout << "<word> ::= ";
    for (int i = 0; i < mask.length(); i++) 
    {
        if (mask[i] == '%')
        {
            cout << "<meta>";
        }
        else
        {
            symbols = moveToEndOfSymbolsChain(i, mask);
            cout << "'" << symbols << "'";
        }
    }
    cout << endl;
    cout << "<meta> ::= {<any>}" << endl;
    cout << "<any> ::= <letter> | <digit> | <other>" << endl;
    cout << "<letter> ::= 'A' | 'B' | 'C' | 'D' | 'E' | 'F' | 'G' | 'H' | 'I' | 'J' | 'K' | 'L' | 'M' | 'N' | 'O' | 'P' | 'Q' | 'R' | 'S' | 'T' | 'U' | 'V' | 'W' | 'X' | 'Y' | 'Z' | 'a' | 'b' | 'c' | 'd' | 'e' | 'f' | 'g' | 'h' | 'i' | 'j' | 'k' | 'l' | 'm' | 'n' | 'o' | 'p' | 'q' | 'r' | 's' | 't' | 'u' | 'v' | 'w' | 'x' | 'y' | 'z'" << endl;
    cout << "<digit> ::= '0' | '1' | '2' | '3' | '4' | '5' | '6' | '7' | '8' | '9'" << endl;
    cout << "<other> ::= \"~\" | \"_\" | \"!\" | \"@\" | \"#\" | \"$\" | \"%\" | \"^\" | \"&\" | \"*\" | \"(\" | \")\" | \"-\" | \"+\"" << endl;
}

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
        if (mask[i] == '%')
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
    generateEBNF(mask);
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