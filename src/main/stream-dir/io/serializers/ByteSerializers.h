#ifndef LAB_1_BYTESERIALIZERS_H
#define LAB_1_BYTESERIALIZERS_H
#include <string>
#include <stdexcept>

#include "../../utils/FileBuffer.h"
#include "../../io/file/FileReadStreamBuffer.h"
#include "../../io/file/FileWriteStreamBuffer.h"
#include "../../io/file/FileReadWriteStreamBuffer.h"

#include <ios>

namespace StreamDefaults {

  inline void default_char_serializer(FileBuffer& buffer, const char& c) {
    buffer.put_char(c);
  }

  inline char default_char_deserializer(FileBuffer& buffer) {
    const int ch = buffer.get_char();
      if (ch == -1) {
        throw std::runtime_error("Default deserializer: Unexpected end of file.");
      }
      return static_cast<char>(ch);
  }

  //Добавить возможность менять разделитель
  inline void default_word_serializer(FileBuffer& buffer, const std::string& word) {
    for (const char c : word) {
      buffer.put_char(c);
    }
    buffer.put_char(' '); // Добавляем разделитель
  }

  inline std::string default_word_deserializer(FileBuffer& buffer) {
    std::string word;
    int ch;

    while ((ch = buffer.peek_char()) != -1 && std::isspace(ch)) {
      buffer.get_char();
    }

    if (ch == -1) {
      throw std::runtime_error("Default word deserializer: Unexpected end of file.: ");
    }

    while ((ch = buffer.peek_char()) != -1 && !std::isspace(ch)) {
      word += static_cast<char>(buffer.get_char());
    }

    return word;
  }

  inline std::string custom_word_deserializer(FileBuffer& buffer, std::string& delimiters) {
    std::string word;
    int ch;

    // Лямбда-функция для удобной проверки, является ли символ разделителем
    auto is_delimiter = [&](char c) {
      return delimiters.find(c) != std::string_view::npos;
    };

    while ((ch = buffer.peek_char()) != -1 && is_delimiter(static_cast<char>(ch))) {
      buffer.get_char();
    }

    if (buffer.peek_char() == -1) {
      throw std::ios_base::failure("End of file reached while searching for a token.");
    }

    while ((ch = buffer.peek_char()) != -1 && !is_delimiter(static_cast<char>(ch))) {
      word += static_cast<char>(buffer.get_char());
    }

    return word;
  }

  inline std::string default_line_deserializer(FileBuffer& buffer) {
    std::string line;
    int ch;

    // Если мы уже в конце файла, сигнализируем об этом.
    if (buffer.peek_char() == -1) {
      throw std::runtime_error("Default line deserializer: End of file.");
    }

    while ((ch = buffer.get_char()) != -1 && ch != '\n') {
      // Учитываем возможное \r\n в Windows-файлах
      if (ch != '\r') {
        line += static_cast<char>(ch);
      }
    }
    return line;
  }


  inline void default_line_serializer(FileBuffer& buffer, const std::string& line) {
    for (const char c : line) {
      buffer.put_char(c);
    }
    buffer.put_char('\n');
  }

  inline FileReadStreamBuffer<char>* make_char_read_stream_buffer(const std::string& file_path) {
      return new FileReadStreamBuffer<char>(file_path, default_char_deserializer);
  }

  inline FileWriteStreamBuffer<char>* make_char_write_stream_buffer(const std::string& file_path) {
      return new FileWriteStreamBuffer<char>(file_path, default_char_serializer);
  }

  inline FileReadWriteStreamBuffer<char>* make_char_read_write_stream_buffer(const std::string& file_path) {
      return new FileReadWriteStreamBuffer<char>(file_path, default_char_deserializer, default_char_serializer);
  }

  inline FileReadStreamBuffer<std::string>* make_word_read_stream_buffer(const std::string& file_path) {
    return new FileReadStreamBuffer<std::string>(file_path, default_word_deserializer);
  }

  inline FileWriteStreamBuffer<std::string>* make_word_write_stream_buffer(const std::string& file_path) {
    return new FileWriteStreamBuffer<std::string>(file_path, default_word_serializer);
  }

  inline FileReadWriteStreamBuffer<std::string>* make_word_read_write_stream_buffer(const std::string& file_path) {
    return new FileReadWriteStreamBuffer<std::string>(file_path, default_word_deserializer, default_word_serializer);
  }

}
#endif // LAB_1_BYTESERIALIZERS_H
