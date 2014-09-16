
#include <iostream>
#include <string>
#include <cstring>
#include <vector>



const int alphabetSize = 26;
const char minChar = 'a';

template <size_t abSize, char minChar>
class CDfaMatcher {
private:
	std::vector <std::vector <size_t> > m_autTbl; // automata table
	std::string m_pattren;   // pattern text
	
	size_t ChToIndex (char ch) {
		return ch - minChar;
	}
	char IndexToCh (size_t i) {
		return minChar + i;
	}
	void CreateAutomata ();
	size_t SigmaFunction (const std::string & subStr, const std::string & patStr);
	
public:
	CDfaMatcher (const std::string &subStr);
	
	void printMatchings (const std::string & textStr);
	
#ifndef NDEBUG
	void PrintTable () {
		for (int i = 0; i < m_autTbl.size (); ++i) {
			for (int j = 0; j < m_autTbl[i].size (); ++j) {
				std::cout << m_autTbl[i][j] << ' ';
			}
			std::cout << "\n";
		}
		std::cout << "\n\n";
	}
#endif
};


template <size_t abSize, char minChar>
void CDfaMatcher <abSize, minChar>::CreateAutomata () {
	//size_t indPos;
	
	for (size_t i = 0; i < m_pattren.length (); ++i)
	{
		std::string tmpStr1 (m_pattren.c_str (), i);
		tmpStr1 += m_pattren[i];
		for (size_t j = 0; j < abSize; ++j)
		{
			m_autTbl[i][j] = SigmaFunction (tmpStr1, m_pattren); // the name from Corman and co book
		}
	}
	
	return;
}


template <size_t abSize, char minChar>
size_t CDfaMatcher <abSize, minChar>::SigmaFunction (
	const std::string & subStr,
	const std::string & patStr
) 
{
	long long j, lastInd;
	
	for (long long i = subStr.length () - 1; i >= 0; --i) {
		lastInd = patStr.length () - 1;
		for (j = i; j >= 0; --j, --lastInd) {
			if (subStr[j] != patStr[lastInd]) break;
		}
		if (j < 0) return i + 1;
	}
	
	return -1;
}


template <size_t abSize, char minChar>
CDfaMatcher <abSize, minChar>::CDfaMatcher (
	const std::string &subStr
):
	m_autTbl (std::vector <std::vector <size_t> > (subStr.size () + 1, std::vector <size_t> (abSize, -1))),
	m_pattren (subStr)
{
	CreateAutomata ();
	return;
}


template <size_t abSize, char minChar>
void CDfaMatcher <abSize, minChar>::printMatchings (const std::string & textStr) {
	//
	
	
	
	return;
}



int main () {
	//std::cout << sizeof (long long)<<std::endl;
	//return 0;
	
	//CDfaMatcher <alphabetSize, minChar> dfaObj ("hello");
	CDfaMatcher <4, 'a'> dfaObj ("abc");
	
	//dfaObj.printMatchings ("qwerxxxhelloxxxdfghjzzzhellozzzdfghjhelllowwwwwwww");
	dfaObj.PrintTable ();
	dfaObj.printMatchings ("abdabcda");
	
	return 0;
}












