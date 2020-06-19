#include <vector>
#include <cstddef>
#include <iostream>
#include <cstring>
#include <complex>

typedef std::complex<double> E;
typedef long long ll;
const double PI = acos(-1), eps = 1e-8;

class large_number 
{
private:

	std::vector<int> digits;
	int operator[](size_t i) const{ return digits[i]; }
	bool is_positive;

public:

	//construct functions
	large_number();
	explicit large_number(long long x);
	explicit large_number(std::string x);
	
	std::vector<int>::size_type size() const;
	void show() const;
	large_number absv() const;
	bool is_zero() const;
	void trim_pre_zero();

	large_number move(ll) const;
	friend large_number inv_(const large_number&);

	large_number& operator=(const large_number&);

	friend std::istream& operator>>(std::istream&,large_number&);
	friend std::ostream& operator<<(std::ostream&,const large_number&);

	friend large_number operator-(const large_number&);
	friend large_number operator+(const large_number&, const large_number&);
	friend large_number operator-(const large_number&, const large_number&);
	friend large_number operator*(const large_number&, const large_number&);
	friend large_number operator*(const large_number&, const ll&);
	friend large_number operator/(const large_number&, const large_number&);
	friend large_number operator/(const large_number&, const int&);
	friend large_number division(const large_number&, const large_number&, bool);
	friend large_number operator%(const large_number&, const large_number&);
	friend large_number nth_root(const large_number&, const ll&);
	friend large_number nth_pow(const large_number&,ll);
	friend large_number nth_pow(const large_number&, const large_number&);

	friend bool operator==(const large_number&, const large_number&);
	friend bool operator>(const large_number&, const large_number&);
	friend bool operator!=(const large_number&, const large_number&);
	friend bool operator<(const large_number&, const large_number&);
	friend bool operator<=(const large_number&, const large_number&);
	friend bool operator>=(const large_number&, const large_number&);
//	friend large_number & operator++(large_number&);
//	friend large_number operator++(large_number&, large_number);
	
	large_number & operator++();
	large_number operator++(int);
	large_number & operator--();
	large_number operator--(int);
	large_number & operator += (const large_number &);
	large_number & operator -= (const large_number &);
	large_number & operator *= (const large_number &);
	large_number & operator /= (const large_number &);
	large_number & operator /= (const ll&);
	large_number & operator %= (const large_number &);
};

void FFT(std::vector<E>&, int, int);
void Rader(std::vector<E>&, int);

