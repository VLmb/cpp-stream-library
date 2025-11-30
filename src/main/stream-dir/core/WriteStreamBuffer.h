#ifndef LAB_1_WRITESTREAMBUFFER_H
#define LAB_1_WRITESTREAMBUFFER_H

/**
 * Определяет полиморфный контракт для любого приёмника данных,
 * будь то файл, коллекция в памяти или что-то иное.
 * Его задача — предоставить простой интерфейс для записи объектов типа T
 * и для принудительного сброса буфера.
 */
template <typename T>
class WriteStreamBuffer {
protected:
  WriteStreamBuffer() = default;

  // Чтобы не конфликтовали
  WriteStreamBuffer(const WriteStreamBuffer&) = delete;
  WriteStreamBuffer& operator=(const WriteStreamBuffer&) = delete;
  WriteStreamBuffer(WriteStreamBuffer&&) = delete;
  WriteStreamBuffer& operator=(WriteStreamBuffer&&) = delete;

public:
  virtual ~WriteStreamBuffer() = default;

  virtual void write(const T& source) = 0;

  virtual void flush() = 0;
};

#endif // LAB_1_WRITESTREAMBUFFER_H
