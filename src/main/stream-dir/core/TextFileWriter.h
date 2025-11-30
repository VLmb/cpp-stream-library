#ifndef LAB_1_TEXTFILEWRITER_H
#define LAB_1_TEXTFILEWRITER_H

#include "../utils/FileBuffer.h"
#include "../io/serializers/ByteSerializers.h" // StreamDefaults
#include <string>

class TextFileWriter {
private:
    FileBuffer byte_buffer;

public:
    explicit TextFileWriter(const std::string& file_path) {
        if (!byte_buffer.open(file_path.c_str(), "r+b")) {
            if (!byte_buffer.open(file_path.c_str(), "w+b")) {
                throw std::runtime_error("Не получилось открыть или создать файл: " + file_path);
            }
        }
    }

    virtual ~TextFileWriter() {
        byte_buffer.close();
    }

    void write(const std::string& text) {
        for (char c : text) {
            byte_buffer.put_char(c);
        }
    }

    void write_word(const std::string& word) {
        StreamDefaults::default_word_serializer(byte_buffer, word);
    }

    void write_line(const std::string& line) {
        StreamDefaults::default_line_serializer(byte_buffer, line);
    }

    void flush() {
        byte_buffer.flush();
    }

    long seek(long offset, FileBuffer::SeekDirection dir) {
        return byte_buffer.seek(offset, dir);
    }

    long seek_to_start() {
        return byte_buffer.seek(0, FileBuffer::SeekDirection::beg);
    }

    long seek_to_end() {
        return byte_buffer.seek(0, FileBuffer::SeekDirection::end);
    }

    void close() {
        byte_buffer.close();
    }

    bool is_open() const {
        return byte_buffer.is_open();
    }

    TextFileWriter &operator<<(const std::string &text) {
        write(text);
        return *this;
    }

    TextFileWriter &operator<<(const char *text) {
        if (text) {
            write(std::string(text));
        }
        return *this;
    }

    TextFileWriter &operator<<(char c) {
        byte_buffer.put_char(c);
        return *this;
    }
};

#endif // LAB_1_TEXTFILEWRITER_H
