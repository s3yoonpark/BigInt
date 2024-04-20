#include <bits/stdc++.h>
using namespace std; 

struct BigInt {
    bool sign=1;
    vector<int> v = {0}; 
    string str = "0"; 

    string convert_to_string(BigInt& x) {
        string ans = ""; 
        if (!x.sign) ans = "-"; 
        for (int i : x.v) ans += to_string(i); 
        return ans; 
    }

    BigInt(string s) {
        sign = (s[0]!='-'); 
        vector<int> temp; 
        for (char c : s) {
            if (c != '-') temp.push_back(c-'0'); 
        }
        swap(v, temp); 
        str = s; 
    }

    BigInt &operator=(string s) {
        sign = (s[0]!='-'); 
        vector<int> temp; 
        for (char c : s) {
            temp.push_back(c-'0'); 
        }
        swap(v, temp); 
        str = s; 
        return *this; 
    }

    BigInt &operator=(BigInt b) {
        v = b.v; 
        sign = b.sign; 
        str = b.str; 
        return *this; 
    }

    BigInt &operator+=(BigInt other) {
        if (sign == other.sign) {
            // addition 
            vector<int> vv;
            int carry = 0;  
            for (int i = 0; i < max((int)v.size(), (int)other.v.size()); ++i) {
                int s = carry;
                if ((int)v.size()-i-1 >= 0) s += v[(int)v.size()-i-1]; 
                if ((int)other.v.size()-i-1 >= 0) s += other.v[(int)other.v.size()-i-1]; 
                vv.push_back(s % 10); 
                carry = s / 10; 
            }
            if (carry != 0) vv.push_back(carry); 
            reverse(vv.begin(), vv.end()); 
            swap(vv, v);    
        } else {
            if (sign) {
                other.sign = 1; 
                *this -= other; 
            } else {
                sign = 1; 
                other -= *this; 
                swap(other, *this); 
            }
        }
        str = convert_to_string(*this); 
        return *this; 
    }

    BigInt operator+(BigInt b) {
        BigInt c = BigInt("0");  
        c += *this;  
        c += b; 
        return c; 
    }

    BigInt &operator-=(BigInt other) {
        if (sign == other.sign) {
            if (sign) {
                if (*this >= other) {
                    vector<int> vv; 
                    int carry = 0;  
                    for (int i = 0; i < max((int)v.size(), (int)other.v.size()); ++i) {
                        if (carry != 0) {
                            if (v[(int)v.size()-i-1] - 1 >= 0) {
                                --v[(int)v.size()-i-1]; 
                                carry = 0; 
                            } else {
                                v[(int)v.size()-i-1] = 9; 
                            }
                        }
                        if ((int)other.v.size()-i-1 < 0) {
                            vv.push_back(v[(int)v.size()-i-1]); 
                            continue; 
                        }
                        if (v[(int)v.size()-i-1] >= other.v[(int)other.v.size()-i-1]) {
                            vv.push_back(v[(int)v.size()-i-1] - other.v[(int)other.v.size()-i-1]); 
                        } else {
                            carry = -1; 
                            vv.push_back(10 + v[(int)v.size()-i-1] - other.v[(int)other.v.size()-i-1]); 
                        }
                    }
                    while (!vv.back() && (int)vv.size() > 1) vv.pop_back(); 
                    reverse(vv.begin(), vv.end()); 
                    swap(vv, v); 
                } else {
                    other -= *this; 
                    other.sign = 0; 
                    swap(*this, other); 
                }
            } else {
                other.sign = true; 
                sign = true; 
                other -= *this; 
                swap(*this, other); 
            }           
        } else {
            if (!other.sign) {
                other.sign = 1; 
                other += *this; 
                swap(*this, other); 
            } else {
                sign = 1; 
                *this += other; 
                sign = 0; 
            }
        }
        str = convert_to_string(*this);
        return *this; 
    }

    BigInt operator-(BigInt other) {
        BigInt c = BigInt("0");  
        c += *this;  
        c -= other; 
        return c;  
    }

    bool operator==(BigInt other) { 
        if ((int)v.size() != (int)other.v.size()) return false; 
        for (int i = 0; i < (int)v.size(); ++i) {
            if (v[i] != other.v[i]) return false; 
        }
        return true; 
    }

    bool operator<=(BigInt other) {
        return (*this < other) || (*this == other); 
    }

    bool operator<(BigInt other) {
        return !(*this >= other); 
    }

    bool operator>=(BigInt other) {
        if (sign != other.sign) {
            return sign; 
        }
        if (sign) {
            if ((int)v.size() > (int)other.v.size()) return true; 
            if ((int)other.v.size() > (int)v.size()) return false; 
            for (int i = 0; i < (int)v.size(); ++i) {
                if (v[i] < other.v[i]) return false; 
            }
            return true; 
        } else {
            for (int i = 0; i < (int)v.size(); ++i) {
                if (v[i] > other.v[i]) return false;
            }
            return true; 
        }
    }

    bool operator>(BigInt other) {
        return !(*this <= other); 
    }
}; 

int main() {
    BigInt a = BigInt("1234543"), b = BigInt("9999999999"); 
    cout << (a - b).str << '\n'; 
   

    return 0; 
}