#ifndef LAB_1_READWRITESTREAM_H
#define LAB_1_READWRITESTREAM_H
#include <memory>
#include "../core/ReadWriteStreamBuffer.h"

template <typename T>
class ReadWriteStream {
private:
  std::unique_ptr<ReadWriteStreamBuffer<T>> buffer;

public:
  explicit ReadWriteStream(ReadWriteStreamBuffer<T>* buffer) : buffer(buffer) {}

  ReadWriteStream<T>& operator<<(const T& source) {
    if (buffer) {
      buffer->write(source);
    }
    return *this;
  }

  ReadWriteStream<T>& operator>>(T& destination) {
    if (buffer) {
      buffer->read(destination);
    }
    return *this;
  }

  void flush() {
    if (buffer) {
      buffer->flush();
    }
  }

  bool is_eof() const {
    return !buffer || buffer->is_eof();
  }

  explicit operator bool() const {
    return !is_eof();
  }

  long seek(long offset, FileBuffer::SeekDirection dir) {
    if (buffer) {
      return buffer->seek(offset, dir);
    }
    return -1;
  }

  long seek_to_end() {
    return buffer->seek(0, FileBuffer::SeekDirection::end);
  }

  long seek_to_start() {
    return buffer->seek(0, FileBuffer::SeekDirection::beg);
  }
};

#endif // LAB_1_READWRITESTREAM_H
