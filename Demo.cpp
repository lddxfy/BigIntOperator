#include <iostream>
#include <string>
using namespace std;

class BigInt {
public:
	BigInt(string str) :s(str) {};
	BigInt operator+(const BigInt& rhs) {
		string res;
		int i = this->s.size()-1;
		int j = rhs.s.size() - 1;
		bool flag = false;
		for (; i >= 0 && j >= 0; i--, j--) {
			int tmp = this->s[i] - '0' + rhs.s[j] - '0';
			if (flag) {
				tmp += 1;
				flag = false;
			}
			if (tmp >= 10) {
				tmp = tmp % 10;
				flag = true;
			}
			res.push_back(tmp + '0');
		}

		if (i >= 0) {
			while (i >= 0) {
				int tmp = this->s[i]-'0';
				if (flag) {
					tmp += 1;
					flag = false;
				}
				if (tmp >= 10) {
					tmp = tmp % 10;
					flag = true;
				}
				i--;
				res.push_back(tmp + '0');
			}
		}
		else if (j>=0) {
			while (j >= 0) {
				int tmp = rhs.s[j]-'0';
				if (flag) {
					tmp += 1;
					flag = false;
				}
				if (tmp >= 10) {
					tmp = tmp % 10;
					flag = true;
				}
				j--;
				res.push_back(tmp + '0');
			}
		}
		if (flag) {
			res.push_back('1');
		}
		reverse(res.begin(), res.end());
		return res;

	}
	BigInt operator-(const BigInt& rhs) {
		string res;
		bool flag = false;
		bool minor = false;
		string maxstr = this->s;
		string minstr = rhs.s;
		if (maxstr.length() < minstr.length()) {
			maxstr = rhs.s;
			minstr = this->s;
			minor = true;

		}
		else if (maxstr.length() == minstr.length()) {
			if (maxstr < minstr) {
				maxstr = rhs.s;
				minstr = this->s;
				minor = true;
			}
			else if (maxstr == minstr) {
				return string("0");
			}
		}
		int i = maxstr.length()-1;
		int j = minstr.length()-1;
		for (; j >= 0 && i >= 0; j--,i--) {
			int tmp = maxstr[i]  - minstr[j];
			if (flag) {
				tmp -= 1;
				flag = false;
			}
			if (tmp < 0) {
				flag = true;
				tmp += 10;
			}
			res.push_back(tmp + '0');
		}

		if (i >= 0) {
			while (i >= 0) {
				int tmp = maxstr[i] - '0';
				if (flag) {
					tmp -= 1;
					flag = false;
				}
				if (tmp < 0) {
					flag = true;
					tmp += 10;
				}
				res.push_back(tmp + '0');
				i--;
			}
		}
		//20100    处理高位0
		string ret;
		auto it = res.rbegin();
		for (; it != res.rend(); it++) {
			if (*it != '0')	break;
		}
		for (; it != res.rend(); it++) {
			ret.push_back(*it);
		}
		if (minor) {
			ret = '-' + ret;
		}
		return ret;
	}
	friend ostream& operator<<(ostream& os,const BigInt& i){
		os << i.s << endl;
		return os;
	}

	
private:
	string s;


};

int main() {
	BigInt int1("99646");
	BigInt int2("99544");
	cout << int1 + int2 << endl;
	cout << int2 - int1 << endl;
	return 0;
}