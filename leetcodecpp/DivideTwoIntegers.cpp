#include <iostream>
#include <stdlib.h>
#include <limits>

using namespace std;

class DivideTwoIntegers {
public:
    int divide2(int dividend, int divisor) {
        // for cases where dividend or divisor is INT_MIN, 
        // by using a higher type, we take the whole number
        // else abs cannot work since its based on 2's complement
        // and 2's complement of n bit number is undefined if its 
        // the min number. try taking out the 2's complement of 
        // -8 for a 4 bit number, behaviour is undefined 
        long a = labs(dividend);
        long b = labs(divisor);
        long sign = ((dividend < 0) ^ (divisor < 0)) ? -1 : 1;
        // overflow cases : denominator == 0 or dividing by a number makes the number 
        // greater than INT_MAX
        if (b == 0 || dividend == numeric_limits<int>::min() && divisor == -1) {
	  return numeric_limits<int>::max();
        } else if (b == 1) {
             return sign * a;
         }

        long result = 0;
        int i = 0;
        while(a >= b) {
            i = 0;
            while(a >= b<<i) {
                a -= b<<i;
                result += 1<<i;
                i++;
            }
        }
        return (sign * result);
    }

  public:
    int divide(int dividend, int divisor) {

      int sign = 1;
      long long result = 0;
      if (divisor == 0 || 
	  (dividend == numeric_limits<int>::min() && divisor == -1) ||
	  (dividend == numeric_limits<int>::max() && divisor == 1))
	return numeric_limits<int>::max();

      if ((divisor < 0 && 0 < dividend) || (dividend < 0 && 0 < divisor))
	sign = -1;
      
      long long ldivisor = divisor;
      long long ldividend = dividend;
      ldivisor = llabs(ldivisor);
      ldividend = llabs(ldividend);
      if (ldivisor > ldividend)
	return result;
      if (ldividend == ldivisor)
	return sign;

      unsigned int count = 0; //record the count of left-shift
      while (ldivisor <= ldividend) {
	count++;
	ldivisor = ldivisor << 1;
      }

      for (unsigned int i = 0;i < count;i++) {
	ldivisor = ldivisor >> 1;
	if (ldividend > ldivisor) {
	  result = (result << 1) + 1;
	  ldividend -= divisor;
	} else if (ldividend == ldivisor) {
	  result = (result << 1) + 1;
	  result = result << (count - i - 1);
	  break;
	} else {
	  result = result << 1;
	}
      } //for

      if (result >= numeric_limits<int>::max())
	result = numeric_limits<int>::max();

      return result * sign;
    }
};

#define DIVIDETWOINTERGERS_H
#ifdef DIVIDETWOINTERGERS_H
int main() {
  DivideTwoIntegers divide;
  //int a = -1010369383;
  //int b = -2147483648;
  //int a = 5, b = 2;
  int a = -2147483648;
  int b = 2;
  //long long l = llabs((long long)a);
  //cout<<l<<endl;

   int result = divide.divide(a, b);
  cout<<a<<endl<<b<<endl<<result<<endl;
  
  return 0;
}
#endif //DIVIDETWOINTERGERS_H
