#ifndef LAB_1_WRITEONLYSTREAM_H
#define LAB_1_WRITEONLYSTREAM_H
#include "../core/WriteStreamBuffer.h"

#include <memory>

template <typename T>
class WriteOnlyStream {
private:
  std::unique_ptr<WriteStreamBuffer<T>> buffer;

public:
  explicit WriteOnlyStream(WriteStreamBuffer<T>* buffer) : buffer(buffer) {}

  WriteOnlyStream<T>& operator<<(const T& source) {
    if (buffer) {
      buffer->write(source);
    }

    return *this;
  }

  void flush() {
    if (buffer) {
      buffer->flush();
    }
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

#endif // LAB_1_WRITEONLYSTREAM_H
