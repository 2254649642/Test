#if 0
#include <iostream>
#include <string.h>

using namespace std;

class String {
public:
	String(const char* chStr = nullptr) {
		if (chStr == nullptr) {
			_chStr = new char[1];
			memset(_chStr, 0, 1);
		}
		else {
			_chStr = new char[strlen(chStr) + 1];
			memset(_chStr, 0, strlen(chStr) + 1);
			strcpy(_chStr, chStr);
		}

	}

	String(const String& str) {
		_chStr = new char[strlen(str._chStr) + 1];
		strcpy(_chStr, str._chStr);
	}

	~String() {
		delete[] _chStr;
		_chStr = nullptr;
	}

	char& operator[] (int index) {
		return _chStr[index];
	}

	const char& operator[] (int index) const {
		return _chStr[index];
	}

	String& operator=(const String& rhs) {
		if (this == &rhs) {
			return *this;
		}

		delete[] _chStr;
		_chStr = new char[strlen(rhs._chStr) + 1];
		strcpy(_chStr, rhs._chStr);
		return *this;
	}

	String& operator=(const char* rhs) {
		delete[] _chStr;
		_chStr = new char[strlen(rhs) + 1];
		strcpy(_chStr, rhs);
		return *this;
	}

	bool operator>(const String& rhs) {
		return strcmp(_chStr, rhs._chStr) > 0;
	}

	bool operator<(const String& rhs) {
		return strcmp(_chStr, rhs._chStr) < 0;
	}

	bool operator==(const String& rhs) {
		return strcmp(_chStr, rhs._chStr) == 0;
	}

	int length() {
		return strlen(_chStr);
	}
private:
	char* _chStr;

	friend String operator+(const String& lhs, const String& rhs);
	friend ostream& operator<<(ostream& out, const String& str);
	friend istream& operator>>(istream& in, String& str);
};

ostream& operator<<(ostream& out, const String& str) {
	out << str._chStr;
	return out;
}

istream& operator>>(istream& in, String& str) {
	int chMax = 100;
	char tmp[100] = { 0 };

	in.getline(tmp, chMax);
	delete[] str._chStr;
	str._chStr = new char[strlen(tmp) + 1];
	strcpy(str._chStr, tmp);

	return in;
}

String operator+(const String& lhs, const String& rhs) {
	String tmp;
	tmp._chStr = new char[strlen(lhs._chStr) + strlen(rhs._chStr) + 1];
	strcpy(tmp._chStr, lhs._chStr);
	strcat(tmp._chStr, rhs._chStr);
	return tmp;
}

int main() {
	const String str1("123");
	String str2("first1");
	String str3 = str2 + str1;
	cout << str3 << endl;

	int a = 1;
	cout << str1[1] << endl;
	return 0;
}
#endif