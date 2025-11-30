#ifndef LAB_1_FILEWRITESTREAMBUFFER_H
#define LAB_1_FILEWRITESTREAMBUFFER_H
#include "../../utils/FileBuffer.h"
#include "../../core/WriteStreamBuffer.h"

#include <functional>
#include <stdexcept>
#include <string>

/**
 * Конкретная реализация WriteStreamBuffer для записи объектов в файл.
 * Этот класс, является адаптером. Его задача — взять готовый объект типа T и, используя
 * сериализатор, превратить его в последовательность байтов и передать их в
 * FileBuffer.
 */
template<typename T>
class FileWriteStreamBuffer : public WriteStreamBuffer<T> {
  using Serializer = std::function<void(FileBuffer &, const T &)>;

private:
  FileBuffer byte_buffer;
  Serializer serializer;

public:

  FileWriteStreamBuffer(const std::string& file_path, Serializer serializer) : serializer(std::move(serializer)) {
    if (!byte_buffer.open(file_path.c_str(), "r+b")) {
      if (!byte_buffer.open(file_path.c_str(), "w+b")) {
        throw std::runtime_error("Не получилось открыть или создать файл: " + file_path);
      }
    }
  }

  ~FileWriteStreamBuffer() override {
    byte_buffer.close();
  }

  void write(const T& source) override {
    serializer(byte_buffer, source);
  }

  void flush() override {
    byte_buffer.flush();
  }

};
#endif // LAB_1_FILEWRITESTREAMBUFFER_H
