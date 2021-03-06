#include <r_util.h>
#include "minunit.h"

bool test_r_hex_from_code() {
	char *s;
	s = "char *s = \"ABCD\";";
	mu_assert_streq (r_hex_from_code (s), "41424344", s);
	s = "char *s = \"AB\" \"CD\";";
	mu_assert_streq (r_hex_from_code (s), "41424344", s);
	s = "char *s = \"\x41\x42\x43\x44\"";
	mu_assert_streq (r_hex_from_code (s), "41424344", s);
	s = "char *s = \"\x41\x42\" /* test */ \"\x43\x44\";";
	mu_assert_streq (r_hex_from_code (s), "41424344", s);
	s = "char *s = \"\n\r\e\"";
	mu_assert_streq (r_hex_from_code (s), "0a0d1b", s);
	s = "uint8_t buffer[3] = {0x41, 0x42, 0x43, 0x44};";
	mu_assert_streq (r_hex_from_code (s), "41424344", s);
	s = "uint8_t buffer[3] = {0x41,\n0x42,\n0x43,\n0x44};";
	mu_assert_streq (r_hex_from_code (s), "41424344", s);
	s = "uint8_t buffer[3] = { 0x41 , \n 0x42, \n 0x43 , \n 0x44 } ;";
	mu_assert_streq (r_hex_from_code (s), "41424344", s);
	s = "uint8_t buffer[3] = {0x41, /* test */0x42, 0x43,/*test*/ 0x44};";
	mu_assert_streq (r_hex_from_code (s), "41424344", s);

	s = "buf = \"\x41\x42\x43\x44\"";
	mu_assert_streq (r_hex_from_code (s), "41424344", s);
	s = "buf = [0x41, 0x42, 0x43, 0x44]";
	mu_assert_streq (r_hex_from_code (s), "41424344", s);

	mu_end;
}

bool test_r_hex_from_c() {
	char *s;
	s = "char *s = \"ABCD\";";
	mu_assert_streq (r_hex_from_c (s), "41424344", s);
	s = "char *s = \"AB\" \"CD\";";
	mu_assert_streq (r_hex_from_c (s), "41424344", s);
	s = "char *s = \"\x41\x42\x43\x44\"";
	mu_assert_streq (r_hex_from_c (s), "41424344", s);
	s = "char *s = \"\x41\x42\" /* test */ \"\x43\x44\";";
	mu_assert_streq (r_hex_from_c (s), "41424344", s);
	s = "char *s = \"\n\r\e\"";
	mu_assert_streq (r_hex_from_c (s), "0a0d1b", s);
	s = "uint8_t buffer[3] = {0x41, 0x42, 0x43, 0x44};";
	mu_assert_streq (r_hex_from_c (s), "41424344", s);
	s = "uint8_t buffer[3] = {0x41,\n0x42,\n0x43,\n0x44};";
	mu_assert_streq (r_hex_from_c (s), "41424344", s);
	s = "uint8_t buffer[3] = { 0x41 , \n 0x42, \n 0x43 , \n 0x44 } ;";
	mu_assert_streq (r_hex_from_c (s), "41424344", s);
	s = "uint8_t buffer[3] = {0x41, /* test */0x42, 0x43,/*test*/ 0x44};";
	mu_assert_streq (r_hex_from_c (s), "41424344", s);

	mu_end;
}

bool test_r_hex_from_py() {
	char *s;
	s = "s = \"ABCD\";";
	mu_assert_streq (r_hex_from_py (s), "41424344", s);
	s = "s = \"\x41\x42\x43\x44\"";
	mu_assert_streq (r_hex_from_py (s), "41424344", s);
	s = "s = \"\n\r\"";
	mu_assert_streq (r_hex_from_py (s), "0a0d", s);
	s = "buffer = [0x41, 0x42, 0x43, 0x44]";
	mu_assert_streq (r_hex_from_py (s), "41424344", s);
	s = "buffer = [0x41,\n0x42,\n0x43,\n0x44]";
	mu_assert_streq (r_hex_from_py (s), "41424344", s);
	s = "buffer = [ 0x41 , \n 0x42, \n 0x43 , \n 0x44 ]";
	mu_assert_streq (r_hex_from_py (s), "41424344", s);

	mu_end;
}

bool test_r_hex_no_code() {
	const char *s;
	s = "\"ABCD\"";
	mu_assert_streq (r_hex_no_code (s), "41424344", s);
	s = "\"AB\" \"CD\"";
	mu_assert_streq (r_hex_no_code (s), "41424344", s);
	s = "\"AB\"\n\"CD\"\n";
	mu_assert_streq (r_hex_no_code (s), "41424344", s);
	s = "\"\x41\x42\x43\x44\"";
	mu_assert_streq (r_hex_no_code (s), "41424344", s);
	s = "\"\x41\x42\"  \"\x43\x44\";";
	mu_assert_streq (r_hex_no_code (s), "41424344", s);

	mu_end;
}

bool all_tests() {
	mu_run_test (test_r_hex_from_c);
	mu_run_test (test_r_hex_from_py);
	mu_run_test (test_r_hex_from_code);
	mu_run_test (test_r_hex_no_code);
	return tests_passed != tests_run;
}

int main(int argc, char **argv) {
	return all_tests();
}
