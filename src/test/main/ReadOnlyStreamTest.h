#ifndef LAB_1_READONLYSTREAMTEST_H
#define LAB_1_READONLYSTREAMTEST_H
#include "../../main/io/sequence/SequenceReadStreamBuffer.h"
#include "../../main/io/serializers/ByteSerializers.h"
#include "../../main/streams/ReadOnlyStream.h"
#include "TestHelper.h"

static const std::string read_test_file = "../src/test/resources/read_test.txt";

inline void shouldReadCharsFromFile() {
  ReadOnlyStream<char> stream(
  StreamDefaults::make_char_read_stream_buffer(read_test_file)
    );

  char expected[] = {'T', 'h', 'e', 'r', 'e'};
  char actual[std::size(expected)];
  for (char& ch : actual) {
    stream >> ch;
  }

  assert_array_equal(expected, actual, "Read chars from txt file.");
}

inline void shouldReadWordsFromFile() {
  ReadOnlyStream<std::string> stream(
  StreamDefaults::make_word_read_stream_buffer(read_test_file)
    );

  std::string expected[] = {"There", "are", "two", "great", "tyrants",
    "in", "the", "world:", "chance", "and", "time."};
  std::string actual[std::size(expected)];
  for (std::string& w : actual) {
    stream >> w;
  }

  assert_array_equal(expected, actual, "Read words from txt file.");
}

inline void shouldReadStringFromVector() {
  std::vector<std::string> source = {
    "There", "are", "two", "great", "tyrants",
    "in", "the", "world:", "chance", "and", "time."
  };

  ReadOnlyStream<std::string> stream(
    new SequenceReadStreamBuffer(source.begin(), source.end())
    );

  auto expected = source;
  std::vector<std::string> actual;
  std::string word;
  while (!stream.is_eof()) {
    stream >> word;
    actual.push_back(word);
    // std::cout << word << std::endl;
  }
  assert_vector_equal(expected, actual, "Read string from vector.");
}

inline void runReadOnlyStreamTest() {
  run_test(shouldReadCharsFromFile, "Read chars from txt file.");
  run_test(shouldReadWordsFromFile, "Read words from txt file.");
  run_test(shouldReadStringFromVector, "Read string from vector.");
}
#endif // LAB_1_READONLYSTREAMTEST_H
