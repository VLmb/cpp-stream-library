#ifndef LAB_1_FILEREADWRITESTREAMBUFFER_H
#define LAB_1_FILEREADWRITESTREAMBUFFER_H

#include "../../core/ReadWriteStreamBuffer.h"
#include "../../utils/FileBuffer.h"

#include <functional>
#include <stdexcept>
#include <string>

template <typename T>
class FileReadWriteStreamBuffer : public ReadWriteStreamBuffer<T> {
  using Deserializer = std::function<T(FileBuffer &)>;
  using Serializer = std::function<void(FileBuffer&, const T&)>;
private:
  FileBuffer byte_buffer;
  Serializer serializer;
  Deserializer deserializer;
  bool eof_flag = false;

  void prefetch() {
    if (byte_buffer.peek_char() == -1) {
      eof_flag = true;
    }
  }

public:
  FileReadWriteStreamBuffer(
    const std::string& file_path,
    Deserializer deserializer,
    Serializer serializer
  ) : serializer(std::move(serializer)),
      deserializer(std::move(deserializer))
  {
    if (!byte_buffer.open(file_path.c_str(), "r+b")) {
      if (!byte_buffer.open(file_path.c_str(), "w+b")) {
        throw std::runtime_error("Не получилось открыть или создать файл: " + file_path);
      }
    }
    prefetch();
  }

  ~FileReadWriteStreamBuffer() override {
    byte_buffer.close();
  }

  bool read(T& destination) override {
    if (is_eof()) {
      return false;
    }
    try {
      destination = deserializer(byte_buffer);
      prefetch();
      return true;
    } catch (const std::exception&) {
      eof_flag = true;
      return false;
    }
  }

  void write(const T& source) override {
    eof_flag = false;
    serializer(byte_buffer, source);
  }


  bool is_eof() const override {
    return eof_flag;
  }

  void flush() override {
    byte_buffer.flush();
  }

  long seek(long offset, FileBuffer::SeekDirection dir) {
    return byte_buffer.seek(offset, dir);
  }

};

#endif // LAB_1_FILEREADWRITESTREAMBUFFER_H
