#ifndef LAB_1_SEQUENCEREADSTREAMBUFFER_H
#define LAB_1_SEQUENCEREADSTREAMBUFFER_H
#include "../../core/ReadStreamBuffer.h"

#include <iterator>

template <typename Iterator>
class SequenceReadStreamBuffer : public ReadStreamBuffer<typename std::iterator_traits<Iterator>::value_type> {
  using T = typename std::iterator_traits<Iterator>::value_type;
private:
  Iterator current;
  Iterator end;

public:
  SequenceReadStreamBuffer(Iterator begin, Iterator end)
  : current(std::move(begin)),
    end(std::move(end))
  {}

  ~SequenceReadStreamBuffer() override = default;

  bool is_eof() const override {
    return current == end;
  }

  bool read(T& destination) override {
    if (is_eof()) {
      return false;
    }
    destination = *current;
    ++current;
    return true;
  }
};

#endif // LAB_1_SEQUENCEREADSTREAMBUFFER_H
