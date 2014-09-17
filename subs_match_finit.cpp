
#include <iostream>
#include <string>
#include <cstring>
#include <cassert>
#include <vector>



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
		for (size_t i = 0; i < m_autTbl.size (); ++i) {
			for (size_t j = 0; j < m_autTbl[i].size (); ++j) {
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
	
	for (size_t i = 0; i < m_pattren.length (); ++i) {
		std::string tmpStr1 (m_pattren.c_str (), i);
		tmpStr1 += IndexToCh (0); // for padding
		for (size_t j = 0; j < abSize; ++j) {
			tmpStr1 [tmpStr1.length () - 1] = IndexToCh (j);
			m_autTbl[i][j] = SigmaFunction (tmpStr1, m_pattren); // the name from Corman and co book
		}
	}
	
	// for the last string at the table
	std::string tmpStr1 (m_pattren.begin () + 1, m_pattren.end ());
	tmpStr1 += IndexToCh (0);
//std::cout << tmpStr1 << " -- " << m_autTbl.size () << std::endl;
	for (size_t j = 0, i = m_autTbl.size () - 1; j < abSize; ++j) {
		tmpStr1 [tmpStr1.length () - 1] = IndexToCh (j);
		m_autTbl[i][j] = SigmaFunction (tmpStr1, m_pattren);
	}
	
	return;
}


template <size_t abSize, char minChar>
size_t CDfaMatcher <abSize, minChar>::SigmaFunction (
	const std::string & subStr,
	const std::string & patStr
) 
{
	long long j, k, maxInd = subStr.length () - 1;
	bool notMatch;
	
	assert (subStr.length () <= patStr.length ());
//std::cout << subStr << " - " << patStr << std::endl;
	
	for (long long i = 0; i <= maxInd; ++i) {
		notMatch = false;
		for (j = i, k = 0; j <= maxInd; ++j, ++k) {
			if (subStr[j] != patStr[k]) {
				notMatch = true;
				break;
			}
		}
		if (!notMatch) return k;
	}
	
	return 0;
}


template <size_t abSize, char minChar>
CDfaMatcher <abSize, minChar>::CDfaMatcher (
	const std::string &subStr
):
	m_autTbl (std::vector <std::vector <size_t> > (subStr.size () + 1, std::vector <size_t> (abSize, 10))),
	m_pattren (subStr)
{
	CreateAutomata ();
	return;
}


template <size_t abSize, char minChar>
void CDfaMatcher <abSize, minChar>::printMatchings (const std::string & textStr) {
	size_t initState = 0;
	
	for (size_t i = 0; i < textStr.length (); ++i) {
		initState = m_autTbl [initState][ChToIndex (textStr[i])];
		if (initState == m_pattren.length ()) {
			size_t mtchPos = i - m_pattren.length () + 1;
			std::cout << "Matching has found at index: " << mtchPos
					  << " of the string" << std::endl;
		}
	}
	
	return;
}


namespace NmUtil {

	const int alphabetSize = 26;
	const char minChar = 'a', maxChar = 'z';

	bool CheckStr (const std::string & inpStr) {
		for (size_t i = 0; i < inpStr.length (); ++i) {
			if (inpStr[i] > maxChar || inpStr[i] < minChar) return false;
		}
		
		return true;
	}
 	
}


//
// To run so: printf "qwerxxxhelloxxxdfghjzzzhellozzzdfghjhelllowwwwwwww" | ./subs_match_finit_elf hello
//

int main (int argc, char **argv) {
	std::string txtStr;
	
	if (argc < 2) {
		std::cout << "Enter a pattern string\n";
		return 1001;
	}
	
	std::getline (std::cin, txtStr);
	if (!NmUtil::CheckStr (argv[1]) || !NmUtil::CheckStr (txtStr)) {
		std::cout << "Have found not corrected symbols at the string\n";
		return 1002;
	}
	
	CDfaMatcher <NmUtil::alphabetSize, NmUtil::minChar> dfaObj (argv[1]);
	//CDfaMatcher <4, 'a'> dfaObj ("abc");
	
	dfaObj.printMatchings (txtStr);
	//dfaObj.PrintTable ();
	//dfaObj.printMatchings ("abdabcda");
	
	return 0;
}












