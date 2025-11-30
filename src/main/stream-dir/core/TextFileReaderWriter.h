#ifndef LAB_1_TEXTFILEREADERWRITER_H
#define LAB_1_TEXTFILEREADERWRITER_H

#include "../utils/FileBuffer.h"
#include "../io/serializers/ByteSerializers.h"

#include <stdexcept>
#include <string>

class TextFileReaderWriter {
private:
  FileBuffer byte_buffer;

public:
  explicit TextFileReaderWriter(const std::string& file_path) {
    if (!byte_buffer.open(file_path.c_str(), "r+b")) {
      if (!byte_buffer.open(file_path.c_str(), "w+b")) {
        throw std::runtime_error("Не получилось открыть или создать файл: " + file_path);
      }
    }
  }

  ~TextFileReaderWriter() {
    byte_buffer.close();
  }

  char read_char() {
    return StreamDefaults::default_char_deserializer(byte_buffer);
  }
  std::string read_word() {
    return StreamDefaults::default_word_deserializer(byte_buffer);
  }
  std::string read_line() {
    return StreamDefaults::default_line_deserializer(byte_buffer);
  }

  char* read_buf() {
    return byte_buffer.get_buf();
  }

  std::string read_all() {
    if (!byte_buffer.is_open()) {
      throw std::runtime_error("Файл не открыт.");
    }

    byte_buffer.seek(0, FileBuffer::SeekDirection::beg);

    std::string result;
    result.reserve(4096);

    while (true) {
      char* chunk = byte_buffer.get_buf();
      if (chunk == nullptr) {
        break;
      }

      size_t n = byte_buffer.get_buf_size();
      if (n == 0) {
        break;
      }

      result.append(chunk, n);
    }

    return result;
  }

  bool is_eof() {
    return byte_buffer.peek_char() == -1;
  }

  void write(const std::string& text) {
    for (char c : text) byte_buffer.put_char(c);
  }
  void write_word(const std::string& word) {
    StreamDefaults::default_word_serializer(byte_buffer, word);
  }
  void write_line(const std::string& line) {
    StreamDefaults::default_line_serializer(byte_buffer, line);
  }
  void flush() {
    byte_buffer.flush();
  }

  long seek(long offset, FileBuffer::SeekDirection dir) {
    return byte_buffer.seek(offset, dir);
  }

  long seek_to_start() {
    return byte_buffer.seek(0, FileBuffer::SeekDirection::beg);
  }

  long seek_to_end() {
    return byte_buffer.seek(0, FileBuffer::SeekDirection::end);
  }

  void close() {
    byte_buffer.close();
  }

  bool is_open() const {
    return byte_buffer.is_open();
  }

  TextFileReaderWriter &operator<<(const std::string &text) {
    write(text);
    return *this;
  }

  TextFileReaderWriter &operator<<(const char *text) {
    if (text) {
      write(std::string(text));
    }
    return *this;
  }

  TextFileReaderWriter &operator<<(char c) {
    byte_buffer.put_char(c);
    return *this;
  }

  TextFileReaderWriter &operator>>(std::string &word) {
    word = read_word();
    return *this;
  }

  TextFileReaderWriter &operator>>(char &c) {
    c = read_char();
    return *this;
  }

};

#endif // LAB_1_TEXTFILEREADERWRITER_H
