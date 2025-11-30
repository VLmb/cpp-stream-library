#ifndef LAB_1_FILESTREAMBUFFER_H
#define LAB_1_FILESTREAMBUFFER_H

#include <functional>
#include <string>
#include <stdexcept>

#include "../../core/ReadStreamBuffer.h"
#include "../../utils/FileBuffer.h"

/**
 * Конкретная реализация ReadStreamBuffer для чтения объектов из файла.
 *
 * FileStreamBuffer является адаптером, который представляет файл на диске как
 * поток объектов типа T. Он использует FileBuffer для эффективного
 * буферизованного чтения байтов и предоставленный пользователем десериализатор
 * для преобразования этих байтов в готовые объекты.
 */
template <typename T>
class FileReadStreamBuffer : public ReadStreamBuffer<T> {
private:
    using Deserializer = std::function<T(FileBuffer&)>;

    void prefetch() {
        if (byte_buffer.peek_char() == -1) {
            eof_flag = true;
        }
    }

    FileBuffer byte_buffer;
    Deserializer deserializer;
    bool eof_flag;

public:

    FileReadStreamBuffer(const std::string& file_path, Deserializer deserializer)
        : deserializer(std::move(deserializer)), eof_flag(false)
    {
        if (!byte_buffer.open(file_path.c_str(), "rb")) {
            throw std::runtime_error("Не получилось открыть файл: " + file_path);
        }

        prefetch();
    }

    ~FileReadStreamBuffer() override {
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

    bool is_eof() const override {
        return eof_flag;
    }
};


#endif // LAB_1_FILESTREAMBUFFER_H
