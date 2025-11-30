#ifndef LAB_1_READSTREAMBUFFER_H
#define LAB_1_READSTREAMBUFFER_H

/**
 * Определяет контракт, которому должен следовать
 * любой источник данных, ориентированный на чтение.
 * Он работает с объектами типа T, полностью абстрагируясь от низкоуровневых
 * деталей того, как и откуда эти объекты получаются. Его задача — предоставить
 * два простых метода: прочитать следующий объект и проверить, не закончились ли данные.
 */
template <typename T>
class ReadStreamBuffer {
protected:
    ReadStreamBuffer() = default;

    //Чтобы не конфликтовали за ресуры
    ReadStreamBuffer(const ReadStreamBuffer&) = delete;
    ReadStreamBuffer& operator=(const ReadStreamBuffer&) = delete;
    ReadStreamBuffer(ReadStreamBuffer&&) = delete;
    ReadStreamBuffer& operator=(ReadStreamBuffer&&) = delete;
public:
    virtual ~ReadStreamBuffer() = default;

    virtual bool read(T& destination) = 0;

    virtual bool is_eof() const = 0;


};

#endif // LAB_1_READSTREAMBUFFER_H