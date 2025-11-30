#ifndef LAB_1_READONLYSTREAMS_H
#define LAB_1_READONLYSTREAMS_H
#include "../core/ReadStreamBuffer.h"

#include <memory>

template <typename T>
class ReadOnlyStream {
private:
  std::unique_ptr<ReadStreamBuffer<T>> buffer;

public:
  explicit ReadOnlyStream(ReadStreamBuffer<T>* buffer) : buffer(buffer) {}

  ReadOnlyStream& operator>>(T& destination) {
    if (buffer) {
      buffer->read(destination);
    }
    return *this;
  }

  explicit operator bool() const {
    return !is_eof();
  }

  bool is_eof() const {
    return !buffer || buffer->is_eof();
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

#endif // LAB_1_READONLYSTREAMS_H
