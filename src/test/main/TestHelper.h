#ifndef LAB_1_TESTHELPER_H
#define LAB_1_TESTHELPER_H
#include <fstream>
#include <iostream>

static int tests_run_count = 0;
static int tests_succeeded_count = 0;
static int tests_failed_count = 0;

inline void assert_true(bool condition, const std::string& test_name) {
  if (!condition) {
    std::cout << "[ FAILED ] " << test_name << std::endl;
    tests_failed_count++;
  }
}

inline void assert_false(bool condition, const std::string& test_name) {
  if (condition) {
    std::cout << "[ FAILED ] " << test_name << std::endl;
    tests_failed_count++;
  }
}

template <typename T>
void assert_array_equal(const T& expected, const T& actual, const std::string& test_name) {
  if (!equal(expected, actual)) {
    std::cout << "[ FAILED ] " << test_name << std::endl;
    tests_failed_count++;
  }
}

template <typename T>
bool equal(const T& expected, const T& actual) {
  return expected == actual;
}

template <typename T, std::size_t N>
void assert_array_equal(const T (&expected)[N], const T (&actual)[N], const std::string& test_name) {
  for (std::size_t i = 0; i < N; i++) {
    if (!equal(expected[i], actual[i])) {
      std::cout << "[ FAILED ] " << test_name << std::endl;
      tests_failed_count++;
      return;
    }
  }
}

template <typename T>
void assert_vector_equal(const std::vector<T>& expected, const std::vector<T>& actual, const std::string& test_name) {
  if (expected.size() != actual.size()) {
    std::cout << "[ FAILED ] " << test_name << std::endl;
    tests_failed_count++;
    return;
  }
  for (std::size_t i = 0; i < expected.size(); i++) {
    if (!equal(expected[i], actual[i])) {
      std::cout << "[ FAILED ] " << test_name << std::endl;
      tests_failed_count++;
      return;
    }
  }
}

void assert_txt_files_equal(const std::string& expected_file_path, const std::string& actual_file_path, const std::string& test_name) {
  std::ifstream expected_file(expected_file_path, std::ifstream::binary);
  std::ifstream actual_file(actual_file_path, std::ifstream::binary);

  if (!expected_file.is_open()) {
    throw std::runtime_error("Couldn't open the file: " + expected_file_path);
  }
  if (!actual_file.is_open()) {
    throw std::runtime_error("Couldn't open the file: " + actual_file_path);
  }

  char char1, char2;
  expected_file.clear();
  actual_file.clear();
  expected_file.seekg(0);
  actual_file.seekg(0);
  while (expected_file.get(char1) && actual_file.get(char2)) {
    if (char1 != char2) {
      std::cout << "[ FAILED ] " << test_name << std::endl;
      tests_failed_count++;
      return;
    }
  }

  if (!expected_file.eof() || !actual_file.eof()) {
    std::cout << "[ FAILED ] " << test_name << std::endl;
    tests_failed_count++;
  }
}

void run_test(const std::function<void()>& test_function, const std::string& test_name) {
  tests_run_count++;
  std::cout << "[ RUNNING ] " << test_name << std::endl;

  const int failures_before = tests_failed_count;
  test_function();
  const int failures_after = tests_failed_count;

  if (failures_before == failures_after) {
    std::cout << "PASSED" << std::endl;
    tests_succeeded_count++;
  }
}

void print_testing_result() {
  std::cout << std::endl;
  std::cout << "Total tests run: " << tests_run_count << std::endl;
  std::cout << "Passed: " << tests_succeeded_count << std::endl;
  std::cout << "Failed: " << tests_failed_count << std::endl;
}


#endif // LAB_1_TESTHELPER_H
