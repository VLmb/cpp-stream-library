#ifndef LAB_1_SEQUENCEWRITESTREAMBUFFER_H
#define LAB_1_SEQUENCEWRITESTREAMBUFFER_H
#include "../../core/WriteStreamBuffer.h"

#include <algorithm>

template <typename Iterator, typename T>
class SequenceWriteStreamBuffer : public WriteStreamBuffer<T> {
private:
  Iterator insert_iterator;

public:
  explicit SequenceWriteStreamBuffer(Iterator insert_iterator)
  : insert_iterator(std::move(insert_iterator))
  {}

  ~SequenceWriteStreamBuffer() override = default;

  void write(const T& source) override {
    *insert_iterator = source;
    ++insert_iterator;
  }

  void flush() override {}

};


#endif // LAB_1_SEQUENCEWRITESTREAMBUFFER_H
