
#include <iostream>
#include <string>
#include <cstring>
#include <vector>



template <size_t abSize>
class CDfaMatcher {
private:
	std::vector <std::vector <size_t> > m_autTbl;
	std::string m_pattren;
	
public:
	CDfaMatcher (const std::string &subStr);
	
	void printMatchings (const std::string & textStr);
};


template <size_t abSize>
CDfaMatcher <abSize>::CDfaMatcher (
	const std::string &subStr
):
	m_autTbl (std::vector <std::vector <size_t> > (subStr.size () + 1, std::vector <size_t> (abSize))),
	m_pattren (subStr)
{
	
	return;
}


template <size_t abSize>
void CDfaMatcher <abSize>::printMatchings (const std::string & textStr) {
	//
	
	
	
	return;
}



int main () {
	CDfaMatcher <26> dfaObj ("hello");
	
	dfaObj.printMatchings ("qwerthellodfghjhellodfghjheLLo2131241");
	
	return 0;
}












