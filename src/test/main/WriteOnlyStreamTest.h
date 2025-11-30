#ifndef LAB_1_WRITEONLYSTREAMTEST_H
#define LAB_1_WRITEONLYSTREAMTEST_H
#include "../../main/io/serializers/ByteSerializers.h"
#include "../../main/streams/WriteOnlyStream.h"
#include "TestHelper.h"
#include "TmpFile.h"

const std::string write_test_file = "../src/test/resources/write_test.txt";
const std::string tmp_test_file = "../src/test/resources/test.txt";

inline void shouldWriteCharsInTxtFile() {
  const TmpFile file(tmp_test_file);

  WriteOnlyStream<char> stream(
    StreamDefaults::make_char_write_stream_buffer(file.get_file_path())
    );

  char chars[15] = {
    'L', 'i', 'f', 'e', '_', 'i', 's',
    '_', 's', 'h', 'o', 'r', 't', ' ', ';'
  };

  for (char c : chars) {
    stream << c;
  }

  assert_txt_files_equal(
  write_test_file,
    file.get_file_path(),
    "Write chars in txt file."
    );
}

inline void runWriteOnlyStreamTest() {
  run_test(shouldWriteCharsInTxtFile, "Write chars in txt file.");
}

#endif // LAB_1_WRITEONLYSTREAMTEST_H
