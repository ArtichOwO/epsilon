#include <quiz.h>
#include <poincare.h>
#include <assert.h>

#include "tree/helpers.h"

using namespace Poincare;

QUIZ_CASE(poincare_integer_constructor) {
  Integer a("123");
  Integer na("-123");
  Integer b("12345678910111213141516");
  Integer nb("-12345678910111213141516");
  Integer c(12314);
  Integer nc(-12314);
  Integer d((int64_t)1234567891011121314);
  Integer nd((int64_t)(-1234567891011121314));
  Integer e = Integer::Overflow();
  assert_pool_size(9);
#if POINCARE_TREE_LOG
  log_pool();
#endif
}

static inline void assert_equal(const Integer i, const Integer j) {
  assert(Integer::NaturalOrder(i, j) == 0);
}
static inline void assert_not_equal(const Integer i, const Integer j) {
  assert(Integer::NaturalOrder(i, j) != 0);
}

static inline void assert_lower(const Integer i, const Integer j) {
  assert(Integer::NaturalOrder(i, j) < 0);
}

static inline void assert_greater(const Integer i, const Integer j) {
  assert(Integer::NaturalOrder(i, j) > 0);
}

QUIZ_CASE(poincare_integer_compare) {
  assert_equal(Integer(123), Integer(123));
  assert_equal(Integer(-123), Integer(-123));
  assert_equal(Integer("123"), Integer(123));
  assert_not_equal(Integer("-123"), Integer(123));
  assert_equal(Integer("-123"), Integer(-123));
  assert_equal(Integer((int64_t)1234567891011121314), Integer((int64_t)1234567891011121314));
  assert_equal(Integer("1234567891011121314"), Integer((int64_t)1234567891011121314));
  assert_not_equal(Integer("-1234567891011121314"), Integer((int64_t)1234567891011121314));
  assert_lower(Integer(123), Integer(456));
  assert_greater(Integer(456), Integer(123));
  assert_lower(Integer(-100), Integer(2));
  assert_lower(Integer(-200), Integer(-100));
  assert_lower(Integer(123), Integer("123456789123456789"));
  assert_lower(Integer(-123), Integer("123456789123456789"));
  assert_lower(Integer("123456789123456788"), Integer("123456789123456789"));
  assert_lower(Integer("-1234567891234567892109209109"), Integer("123456789123456789"));
  assert_greater(Integer("123456789123456789"), Integer("123456789123456788"));
  //FIXME: assert(Integer("0x2BABE") == Integer(178878));
  //FIXME: assert(Integer("0b1011") == Integer(11));
}

static inline void assert_add_to(const Integer i, const Integer j, const Integer k) {
  assert(Integer::NaturalOrder(Integer::Addition(i, j), k) == 0);
}

QUIZ_CASE(poincare_integer_addition) {
  assert_add_to(Integer("0"), Integer("0"), Integer(0));
  assert_add_to(Integer(123), Integer(456), Integer(579));
  assert_add_to(Integer(123), Integer(456), Integer(579));
  assert_add_to(Integer("123456789123456789"), Integer(1), Integer("123456789123456790"));
  assert_add_to(Integer("-123456789123456789"), Integer("123456789123456789"), Integer("0"));
  assert_add_to(Integer("234"), Integer(-234), Integer(0));
  assert_add_to(Integer("18446744073709551616"), Integer("18446744073709551368"), Integer("36893488147419102984"));
  //2^64+2^64
  assert_add_to(Integer("18446744073709551616"), Integer("18446744073709551616"), Integer("36893488147419103232"));
  //2^64+2^32
  assert_add_to(Integer("18446744073709551616"), Integer("4294967296"), Integer("18446744078004518912"));
  //2^64+1
  assert_add_to(Integer("18446744073709551616"), Integer("1"), Integer("18446744073709551617"));
  //2^32+2^32
  assert_add_to(Integer("4294967296"), Integer("4294967296"), Integer("8589934592"));
  //2^32+1
  assert_add_to(Integer("4294967296"), Integer("1"), Integer("4294967297"));
  //2^16+1
  assert_add_to(Integer("65537"), Integer("1"), Integer("65538"));
  //2^16+2^16
  assert_add_to(Integer("65537"), Integer("65537"), Integer("131074"));
}

QUIZ_CASE(poincare_integer_subtraction) {
#if 0
  assert(Integer::Subtraction(Integer(123), Integer(23)).isEqualTo(Integer(100)));
  assert(Integer::Subtraction(Integer("123456789123456789"), Integer("9999999999")).isEqualTo(Integer("123456779123456790")));
  assert(Integer::Subtraction(Integer(23), Integer(100)).isEqualTo(Integer(-77)));
  assert(Integer::Subtraction(Integer(23), Integer(23)).isEqualTo(Integer(0)));
  assert(Integer::Subtraction(Integer(-23), Integer(-23)).isEqualTo(Integer(0)));
  assert(Integer::Subtraction(Integer("-123456789123456789"), Integer("-123456789123456789")).isEqualTo(Integer(0)));
  assert(Integer::Subtraction(Integer("123456789123456789"), Integer("123456789123456789")).isEqualTo(Integer(0)));
  assert(Integer::Subtraction(Integer("18446744073709551616"), Integer("18446744073709551368")).isEqualTo(Integer(248)));

  //2^64-2^64
  assert(Integer::Subtraction(Integer("18446744073709551616"), Integer("18446744073709551616")).isEqualTo(Integer("0")));
  //2^64-2^32
  assert(Integer::Subtraction(Integer("18446744073709551616"), Integer("4294967296")).isEqualTo(Integer("18446744069414584320")));
  //2^32-2^64
  assert(Integer::Subtraction(Integer("4294967296"), Integer("18446744073709551616")).isEqualTo(Integer("-18446744069414584320")));
  //2^64-1
  assert(Integer::Subtraction(Integer("18446744073709551616"), Integer("1")).isEqualTo(Integer("18446744073709551615")));
  //1-2^64
  assert(Integer::Subtraction(Integer("1"), Integer("18446744073709551616")).isEqualTo(Integer("-18446744073709551615")));
  //2^32-2^32
  assert(Integer::Subtraction(Integer("4294967296"), Integer("4294967296")).isEqualTo(Integer("0")));
  //2^32-1
  assert(Integer::Subtraction(Integer("4294967296"), Integer("1")).isEqualTo(Integer("4294967295")));
  //2^16-1
  assert(Integer::Subtraction(Integer("65537"), Integer("1")).isEqualTo(Integer("65536")));
  //2^16-2^16
  assert(Integer::Subtraction(Integer("65537"), Integer("65537")).isEqualTo(Integer("0")));
#endif
}

QUIZ_CASE(poincare_integer_multiplication) {
#if 0
  assert(Integer::Multiplication(Integer(12), Integer(34)).isEqualTo(Integer(408)));
  assert(Integer::Multiplication(Integer(56), Integer(0)).isEqualTo(Integer(0)));
  assert(Integer::Multiplication(Integer(-12), Integer(34)).isEqualTo(Integer(-408)));
  assert(Integer::Multiplication(Integer(-12), Integer(-34)).isEqualTo(Integer(408)));
  assert(Integer::Multiplication(Integer(123456), Integer(654321)).isEqualTo(Integer("80779853376")));
  assert(Integer::Multiplication(Integer("9999999999"), Integer("9999999999")).isEqualTo(Integer("99999999980000000001")));
  assert(Integer::Multiplication(Integer("-23"), Integer("0")).isEqualTo(Integer("0")));
  assert(Integer::Multiplication(Integer("-23456787654567765456"), Integer("0")).isEqualTo(Integer("0")));
#endif
}

QUIZ_CASE(poincare_integer_divide) {
#if 0
  assert(Integer::Division(Integer(8), Integer(4)).quotient.isEqualTo(Integer(2)) && Integer::Division(Integer(8), Integer(4)).remainder.isEqualTo(Integer(0)));
  assert(Integer::Division(Integer("3293920983030066"), Integer(38928)).quotient.isEqualTo(Integer("84615726033")) && Integer::Division(Integer("3293920983030066"), Integer(38928)).remainder.isEqualTo(Integer(17442)));
  assert(Integer::Division(Integer("3293920983030066"), Integer("389282362616")).quotient.isEqualTo(Integer(8461)) && Integer::Division(Integer("3293920983030066"), Integer("389282362616")).remainder.isEqualTo(Integer("202912936090")));
  assert(Integer::Division(Integer("-18940566"), Integer("499030")).quotient.isEqualTo(Integer(-38)) && Integer::Division(Integer("-18940566"), Integer("499030")).remainder.isEqualTo(Integer("22574")));
  assert(Integer::Division(Integer("234567909876"), Integer("-234567898")).quotient.isEqualTo(Integer(-1000)) && Integer::Division(Integer("234567909876"), Integer("-234567898")).remainder.isEqualTo(Integer("11876")));
  assert(Integer::Division(Integer("-567"), Integer("-12")).quotient.isEqualTo(Integer(48)) && Integer::Division(Integer("-567"), Integer("-12")).remainder.isEqualTo(Integer("9")));
  assert(Integer::Division(Integer("-576"), Integer("-12")).quotient.isEqualTo(Integer(48)) && Integer::Division(Integer("-576"), Integer("-12")).remainder.isEqualTo(Integer("0")));
  assert(Integer::Division(Integer("576"), Integer("-12")).quotient.isEqualTo(Integer(-48)) && Integer::Division(Integer("576"), Integer("-12")).remainder.isEqualTo(Integer("0")));
  assert(Integer::Division(Integer("-576"), Integer("12")).quotient.isEqualTo(Integer(-48)) && Integer::Division(Integer("-576"), Integer("12")).remainder.isEqualTo(Integer("0")));
 assert(Integer::Division(Integer("12345678910111213141516171819202122232425"), Integer("10")).remainder.isEqualTo(Integer("5")));
  assert(Integer::Division(Integer("12345678910111213141516171819202122232425"), Integer("10")).quotient.isEqualTo(Integer("1234567891011121314151617181920212223242")));
  assert(Integer::Division(Integer("1234567891011121314151617181920212223242"), Integer("10")).quotient.isEqualTo(Integer("123456789101112131415161718192021222324")) && Integer::Division(Integer("1234567891011121314151617181920212223242"), Integer("10")).remainder.isEqualTo(Integer("2")));
  assert(Integer::Division(Integer("123456789101112131415161718192021222324"), Integer("10")).quotient.isEqualTo(Integer("12345678910111213141516171819202122232")) && Integer::Division(Integer("123456789101112131415161718192021222324"), Integer("10")).remainder.isEqualTo(Integer("4")));
  assert(Integer::Division(Integer("12345678910111213141516171819202122232"), Integer("10")).quotient.isEqualTo(Integer("1234567891011121314151617181920212223")) && Integer::Division(Integer("12345678910111213141516171819202122232"), Integer("10")).remainder.isEqualTo(Integer("2")));
  assert(Integer::Division(Integer("1234567891011121314151617181920212223"), Integer("10")).quotient.isEqualTo(Integer("123456789101112131415161718192021222")) && Integer::Division(Integer("1234567891011121314151617181920212223"), Integer("10")).remainder.isEqualTo(Integer("3")));
  assert(Integer::Division(Integer("123456789101112131415161718192021222"), Integer("10")).quotient.isEqualTo(Integer("12345678910111213141516171819202122")) && Integer::Division(Integer("123456789101112131415161718192021222"), Integer("10")).remainder.isEqualTo(Integer("2")));
  assert(Integer::Division(Integer("12345678910111213141516171819202122"), Integer("10")).quotient.isEqualTo(Integer("1234567891011121314151617181920212")) && Integer::Division(Integer("12345678910111213141516171819202122"), Integer("10")).remainder.isEqualTo(Integer("2")));
  assert(Integer::Division(Integer("0"), Integer("-10")).quotient.isEqualTo(Integer("0")) && Integer::Division(Integer("0"), Integer("-10")).remainder.isEqualTo(Integer("0")));
  assert(Integer::Division(Integer("0"), Integer("-123456789098760")).quotient.isEqualTo(Integer("0")) && Integer::Division(Integer("0"), Integer("-123456789098760")).remainder.isEqualTo(Integer("0")));
  assert(Integer::Division(Integer("2305843009213693952"), Integer("2305843009213693921")).quotient.isEqualTo(Integer("1")) && Integer::Division(Integer("2305843009213693952"), Integer("2305843009213693921")).remainder.isEqualTo(Integer("31")));
#endif
}

#if 0
template<typename T>
void assert_integer_evals_to(const char * i, bool negative, T result) {
  assert(Integer(i, negative).approximate<T>() == result);
}
#endif

QUIZ_CASE(poincare_integer_evaluate) {
#if 0
  assert_integer_evals_to("1", false, 1.0f);
  assert_integer_evals_to("1", false, 1.0);
  assert_integer_evals_to("12345678", false, 12345678.0f);
  assert_integer_evals_to("12345678", false, 12345678.0);
  assert_integer_evals_to("0", false, 0.0f);
  assert_integer_evals_to("0", false, 0.0);
  assert_integer_evals_to("0", true, 0.0f);
  assert_integer_evals_to("0", true, 0.0);
  assert_integer_evals_to("1", true, -1.0f);
  assert_integer_evals_to("1", true, -1.0);
  assert_integer_evals_to("12345678", false, 12345678.0f);
  assert_integer_evals_to("12345678", false, 12345678.0);
  assert_integer_evals_to("4294967295", false, 4294967295.0f);
  assert_integer_evals_to("4294967295", false, 4294967295.0);
  assert_integer_evals_to("4294967296", true, -4294967296.0f);
  assert_integer_evals_to("4294967296", true, -4294967296.0);
  assert_integer_evals_to("2147483648", false, 2147483648.0f);
  assert_integer_evals_to("2147483648", false, 2147483648.0);
  assert_integer_evals_to("18446744073709551615", true, -18446744073709551615.0f);
  assert_integer_evals_to("18446744073709551615", true, -18446744073709551615.0);
  assert_integer_evals_to("18446744073709551616", true, -18446744073709551616.0f);
  assert_integer_evals_to("18446744073709551616", true, -18446744073709551616.0);
  assert_integer_evals_to("92233720372036854775808", false, 92233720372036854775808.0f);
  assert_integer_evals_to("92233720372036854775808", false, 92233720372036854775808.0);
  assert_integer_evals_to("134217720", false, 134217720.0f);
  assert_integer_evals_to("134217720", false, 134217720.0);
  assert_integer_evals_to("67108864", false, 67108864.0f);
  assert_integer_evals_to("67108864", false, 67108864.0);
  assert_integer_evals_to("33554432", false, 33554432.0f);
  assert_integer_evals_to("33554432", false, 33554432.0);
  assert_integer_evals_to("2", false, 2.0f);
  assert_integer_evals_to("2", false, 2.0);
  assert_integer_evals_to("4", false, 4.0f);
  assert_integer_evals_to("4", false, 4.0);
#endif
}
