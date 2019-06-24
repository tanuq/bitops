#include "digit_sep.h"

using namespace std;

string digit_sep(const string& s, size_t len, const string& sep)
{
	string str;
	for (size_t pos = 0;;) {
		if ((s.length() - pos) % len) {
			str += s.substr(pos, s.length() % len);
			pos += (s.length() % len);
		} else {
			str += s.substr(pos, len);
			pos += len;
		}
		if (pos >= s.length()) {
			break;
		} else {
			str += sep;
		}
	}
	return str;
}

