#include "large_number.h"
#include <algorithm>
#include <cctype>
#include <ctime>
#include <cmath>

#define IS_POS true
#define IS_NEG false

using std::vector;
using std::cout;
using std::istream;
using std::ostream;
using std::max;
using std::min;
using std::string;
using std::swap;
using std::complex;

//funstions for constructing

large_number::large_number() { is_positive = IS_POS, digits.push_back(0); }

large_number::large_number(ll x)
{
	ll i = x; digits.clear();
	if (x >= 0) is_positive = IS_POS;
	else is_positive = IS_NEG, i = -i;
	do{
		digits.push_back(i % 10);
		i = i / 10;
	}while (i != 0);
}

large_number::large_number(string x)
{
	const string neg_zero = "-0"; digits.clear();
	if (x == neg_zero) x.erase(0, 1);
	if (isdigit(x[0])) x = "+" + x;
	if (x[0] == '+') is_positive = IS_POS;
	else is_positive = IS_NEG;
	for (int i = x.size() - 1; i >= 1; i--) digits.push_back(x[i] - '0');
}

//functions for normal usage

vector<int>::size_type large_number::size() const
{
	return digits.size();
}

void large_number::show() const
{
	cout << *this; 
}

large_number large_number::absv() const
{
	large_number ret = *this;
	ret.is_positive = IS_POS;
	return ret;
}
bool large_number::is_zero() const
{
	return this->size() == 1 && this->digits[0] == 0;
}

void large_number::trim_pre_zero()
{
	while (this->digits.back() == 0 && this->size() > 1) this->digits.pop_back();
}

istream& operator>>(istream& is, large_number& a)
{
	string x;
	is >> x;
	a = large_number(x);
	return is;
}

ostream& operator<<(ostream& os, const large_number& a)
{
	if(a.size() > 0) os << (a.is_positive ? "" : "-");
	else os << "nan";
	for (int i = a.size() - 1; i >= 0; i--)
		os << a.digits[i];
	return os;
}


//functions for comparing

bool operator==(const large_number& x, const large_number& y)
{
	if (x.size() != y.size()) return false;
	if (x.is_positive != y.is_positive)
	{
		return x.is_zero() && y.is_zero();
	}
	else // xy >= 0
	{
		for (int i = x.size() - 1; i >= 0 ; i--)
		{
			if (x.digits[i] != y.digits[i])
				return false;
		}
		return true;
	}
}

bool operator!=(const large_number& x, const large_number& y)
{
	return !(x == y);
}

bool operator>(const large_number& x, const large_number& y)
{
	if (x.is_positive != y.is_positive)
	{
		return x.is_positive && (!x.is_zero() || !y.is_zero());
	}
	else // xy >= 0
	{
		if (x.size() > y.size())
			return x.is_positive;
		else if (x.size() < y.size())
			return !x.is_positive;
		for (int i = x.size() - 1; i >= 0 ; i--)
		{
			if (x.digits[i] > y.digits[i]) return x.is_positive;
			else if (x.digits[i] < y.digits[i]) return !x.is_positive;
		}
		return !x.is_positive;
	}
}

bool operator<(const large_number& x, const large_number& y)
{
	if (x.is_positive != y.is_positive)
	{
		return !x.is_positive && (!x.is_zero() || !y.is_zero());
	} 
	else // xy >= 0
	{
		if (x.size() < y.size())
			return x.is_positive;
		else if (x.size() > y.size())
			return !x.is_positive;
		for (int i = x.size() - 1; i >= 0 ; i--)
		{
			if (x.digits[i] < y.digits[i]) return x.is_positive;
			else if (x.digits[i] > y.digits[i]) return !x.is_positive;
		}
		return !x.is_positive;
	}
}

bool operator>=(const large_number& x, const large_number& y)
{
	return x > y || x == y;
}

bool operator<=(const large_number& x, const large_number& y)
{
	return x < y || x == y;
}

large_number& large_number::operator++()
{
	*this += large_number(1);
	return *this;
}

large_number large_number::operator++(int)
{
	large_number temp = *this;
	*this += large_number(1);
	return temp;
}

large_number& large_number::operator--()
{
	*this -= large_number(1);
	return *this;
}

large_number large_number::operator--(int)
{
	large_number temp = *this;
	*this -= large_number(1);
	return temp;
}

//functions for mathematic caculation

large_number& large_number::operator=(const large_number& x)
{
	if (this != &x) this->digits = x.digits , this->is_positive = x.is_positive;
	return *this;
}

large_number operator-(const large_number& x)
{
	if (x.is_zero()) return x.absv();
	large_number ret = x;
	ret.is_positive ^= 1;
	return ret;
}

//Addition & Subtraction functions

large_number operator+(const large_number& x, const large_number& y)
{
	if (x.is_positive == y.is_positive)// when xy>0
	{
		large_number sum;
		const large_number *mmin, *mmax;
		mmin = x.absv() < y.absv() ? &x : &y;
		mmax = x.absv() > y.absv() ? &x : &y;
		size_t maxlen = mmax->size();
		size_t minlen = mmin->size();
		sum = *mmax;
		sum.digits.push_back(0);
		for (size_t i = 0; i < maxlen; i++)
		{
			int mmin_n = i < minlen ? mmin->digits[i] : 0; //Avoid access to out-of-bounds for small numbers (static arrays can be ignored)
			sum.digits[i + 1] += (mmin_n + sum.digits[i]) / 10;
			sum.digits[i] = (mmin_n + sum.digits[i]) % 10;
		}
		sum.trim_pre_zero();
		return sum;
	}
	else if (!x.is_positive) 
		return y - -x;
	else
		return x - -y;
}

large_number operator-(const large_number& x, const large_number& y)
{
	if (x.is_positive && y.is_positive)// when x>0,y>0
	{
		large_number diff;
		const large_number *mmin, *mmax;
		mmin = x < y ? &x : &y;
		mmax = x > y ? &x : &y;
		size_t maxlen = mmax->size();
		size_t minlen = mmin->size();
		diff = *mmax;
		for (size_t i = 0; i < maxlen; i++)
		{
			int mmin_n = i < minlen ? mmin->digits[i] : 0; //Avoid access to out-of-bounds for small numbers (static arrays can be ignored)
			diff.digits[i] -= mmin_n;
			if(diff.digits[i] < 0) diff.digits[i + 1] -= 1, diff.digits[i] += 10;
		}
		diff.trim_pre_zero();
		return x > y ? diff : -diff;
	}
	else if (!x.is_positive && !y.is_positive)
		return -y - -x;
	else if(!x.is_positive)
		return - (-x + y);
	else 
		return x + -y;
}

large_number & large_number::operator += (const large_number &y)
{
	*this = *this + y;
	return *this;
}
large_number & large_number::operator -= (const large_number &y)
{
	*this = *this - y;
	return *this;
}

// Multiply & Divide functions and etc.

large_number operator*(const large_number& x, const large_number& y) //FFT O(nlogn)
{
	vector<E> a, b;
	large_number multi;
	int xlen = x.size(), ylen = y.size(), len = 1;
	while(len < (max(xlen, ylen) << 1)) len <<= 1;
	for(int i = 0 ; i < len; i++)
	{
		a.push_back(i < xlen ? E(x[i], 0.0) : (0.0, 0.0));
		b.push_back(i < ylen ? E(y[i], 0.0) : (0.0, 0.0));
	}
	FFT(a, len, 1), FFT(b, len, 1);
	for(int i = 0; i < len; i++) a[i] *= b[i];
	FFT(a, len, -1); multi.digits.clear();
	for(int i = 0; i < len; i++) multi.digits.push_back((int)(a[i].real()+0.5));
	multi.digits.push_back(0);
	for(int i = 0; i < len; i++)
	{
		multi.digits[i + 1] += multi.digits[i] / 10;
		multi.digits[i] %= 10;
	}
	multi.is_positive = !(x.is_positive ^ y.is_positive);
	multi.trim_pre_zero();
	return multi;
}

large_number operator*(const large_number& x, const ll& y)
{
	return y == 1ll ? x : x * large_number(y);
}
large_number& large_number::operator *= (const large_number& y)
{
	*this = *this * y;
	return *this;
}

large_number operator/(const large_number& x, const int& y) // single integer
{
	int xlen = x.size(), carry = 0;
	large_number q; q.digits.resize(xlen);
	for (int i = xlen - 1; i >= 0; i--)
	{
		int sum = carry * 10 + x[i];
		q.digits[i] = sum / y;
		carry = sum % y;
	}
	q.trim_pre_zero();
	return q;
}

large_number operator/(const large_number& x, const large_number& y)
{
	if(y.is_zero()) 
		cout<<"nan", exit(0);
	if(x.is_positive && y.is_positive)
		return division(x, y, true);
	else if (!x.is_positive && !y.is_positive)
		return -x / -y;
	else if (!x.is_positive)
		return -(-x / y);
	else
		return -(x / -y);
}

large_number& large_number::operator /= (const ll& y)
{
	*this = *this / y;
	return *this;
}

large_number& large_number::operator /= (const large_number& y)
{
	*this = *this / y;
	return *this;
}

large_number operator%(const large_number& x, const large_number& y)
{
	if(y.is_zero())
		cout<<"nan",exit(0);
	if(x.is_positive && y.is_positive)
		return division(x, y, false);
	else if (!x.is_positive && !y.is_positive)
		return -(-x % -y);
	else if (!x.is_positive)
		return -(-x % y);
	else
		return (x % -y);
}

large_number& large_number::operator %= (const large_number& y)
{
	*this = *this % y;
	return *this;
}

// nth_root & nth_pow functions

large_number nth_root(const large_number& x, const ll& times) // O(nlog^2 n) Newton-Raphson
{
	if(!((times & 1) || x.is_positive)) 
		cout << "nan", exit(0);
	if(x.is_zero() || x == large_number(1))
		return x;
	int sup = x.size() - 1;
	large_number r1 = large_number("1" + string(max((x.size() + times - 1)/ times, 0ull),'0')), r2(0);
	--r1;
//	if (r1 > x.absv()) r1 = x.absv();
	ll top = r1.size() - 1;
	ll L = 0, R = 9;
	while (L <= R)
	{
		ll mid = L + (R - L) / 2;
		r1.digits[top] = mid;
		if (nth_pow(r1, times) <= x.absv()) L = mid + 1;
		else R = mid - 1;
	}
	r1.digits[top] = L;
	r1.trim_pre_zero();

	r2 = (r1 * (times - 1) + x.absv() / nth_pow(r1, times - 1)) / times;
	while (r2 < r1 && r1 != large_number(1)) 
	{
		swap(r1.digits, r2.digits);
		r2 = (r1 * (times - 1) + x.absv() / nth_pow(r1, times - 1)) / times;
	}
	r1.is_positive = x.is_positive;
	return r1;
}

large_number nth_pow(const large_number &x, ll times)  //Fast Power O(nlog(n)*log(times))
{
	large_number ret(1), I = x;
	while (times) 
	{
		if (times & 1) ret = ret * I;
		times >>= 1, I = I * I;
	}
	return ret;
}

large_number nth_pow(const large_number& x, const large_number& y) //Fast Power
{
	large_number ret(1), I = x ,times = y;
	while (times > large_number(0))
	{
		if (times.digits[0] & 1) ret = ret * I;
		times /= 2, I = I * I;
	}
	return ret;
}

// Auxiliary functions

large_number inv_(const large_number& y) // Find the reciprocal of y, Recursive version
{
	if (y.size() == 1) 
		return large_number(100 / y.digits[0]);
	if (y.size() == 2) 
	{
		large_number sum(0), lim(10000);
		large_number y_inv; y_inv.digits.resize(4, 0);
		const int lgM = 17;
		large_number db[lgM];
		db[0] = y;
		for (int i = 1; i < lgM; ++i) db[i] = db[i - 1] + db[i - 1];
		for (int i = 3; i >= 0; --i) 
		{
			for (int k = lgM - 1; k >= 0; --k)
				if (sum + db[k].move(i) <= lim)
				{
					sum += db[k].move(i);
					y_inv.digits[i] |= 1 << k;
				}
		}
		return y_inv;
	}
	int n = y.size(), k = (n + 2) >> 1;
	large_number y_inv; 
	y_inv.digits.clear();
	y_inv.digits.insert(y_inv.digits.end(), y.digits.end() - k, y.digits.end());
	y_inv = inv_(y_inv);
	return (large_number(2) * y_inv).move(n - k) - (y * (y_inv * y_inv)).move(-(k << 1));
}

large_number division(const large_number& x, const large_number& y, bool is_get_quotient) // Newton-Raphson Division
{
	int m = x.digits.size(), n = y.digits.size(), t = 0;
	if (m < n) return large_number(0);
	if (m > (n << 1)) t = m - (n << 1);
	double _fir = clock() * 0.1 / CLOCKS_PER_SEC;
	
	large_number y_inv = inv_(y.move(t));
	large_number q = x.move(t) * y_inv;
	
	std::cerr << "\tNewton-Raphson Division quotient:" << clock() * 0.1 / CLOCKS_PER_SEC - _fir << " s" << std::endl;
	_fir = clock() * 0.1 / CLOCKS_PER_SEC;
	
	q = q.move(-((n + t) << 1));
	large_number r = x - y * q;
	int _x = 0, _y = 0;
	while (y <= r) ++q, r -= y, ++_x;
	while (x < y * q) --q, r += y, ++_y;
	
	std::cerr << "\tCheck quotient_err:" << clock() * 0.1 / CLOCKS_PER_SEC - _fir << " s | +" << _x << " -" << _y << std::endl;
	
	if(is_get_quotient) return q;
	else return r;
}

large_number large_number::move(ll k) const
{
	if (k == 0) return *this;
	large_number ret;
	if (this->is_zero()) return large_number(0);
	if (k < 0) 
	{
		if (-k >= this->size()) return large_number(0);
		ret.digits.clear();
		ret.digits.insert(ret.digits.end() ,digits.begin() + (-k), digits.end());
		return ret;
	}
	ret.digits.resize(k, 0);
	ret.digits.insert(ret.digits.end(), digits.begin(), digits.end());
	return ret;
}

void Rader(vector<E> &y, int n)
{
	for(int i = 0, j = 0; i < n; i++)
	{
		if(i < j) swap(y[i], y[j]);
		int k = n;
		while(j & (k >>= 1)) j &= ~k;
		j |= k; 
	}
}

void FFT(vector<E> &y, int n, int inv)
{
	Rader(y, n);
	for(int h = 2; h <= n; h <<= 1)
	{
		E Wn(cos(2 * PI/h),inv * sin(2 * PI/h));
		for(int i = 0; i < n; i += h)
		{
			E W(1, 0);
			for(int j = i; j < i + h/2; j++)
			{
				E u = y[j], t = W * y[j + h/2];
				y[j] = u + t;
				y[j + h/2] = u - t;
				W *= Wn;
			}
		}
	}
	if(inv == -1) for(int i = 0; i < n; i++) y[i] /= n;
}
