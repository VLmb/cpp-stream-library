#ifndef LAB_1_READWRITESTREAMBUFFER_H
#define LAB_1_READWRITESTREAMBUFFER_H
#include "ReadStreamBuffer.h"
#include "WriteStreamBuffer.h"
#include "../utils/FileBuffer.h"

/**
 * Цель —
 * объединить интерфейсы ReadStreamBuffer и WriteStreamBuffer с помощью
 * множественного наследования.
 */
template <typename T>
class ReadWriteStreamBuffer : public ReadStreamBuffer<T>, public WriteStreamBuffer<T> {

protected:
  ReadWriteStreamBuffer() = default;
  ReadWriteStreamBuffer(const ReadWriteStreamBuffer&) = delete;
  ReadWriteStreamBuffer& operator=(const ReadWriteStreamBuffer&) = delete;
  ReadWriteStreamBuffer(ReadWriteStreamBuffer&&) = delete;
  ReadWriteStreamBuffer& operator=(ReadWriteStreamBuffer&&) = delete;

public:
  ~ReadWriteStreamBuffer() override = default;

  virtual long seek(long offset, FileBuffer::SeekDirection dir) = 0;

};

#endif // LAB_1_READWRITESTREAMBUFFER_H
