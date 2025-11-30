#pragma once
#include <cstdio>

#ifndef LAB_1_FILEBUFFER_H
#define LAB_1_FILEBUFFER_H

class FileBuffer {
private:
    FILE* file_handle;
    char* buffer;
    size_t buffer_size;

    // Указатели для зоны записи
    char* write_pos;

    // Указатели для зоны чтения
    char* read_pos;
    char* read_end;

    int sync();

    int flush();
    int underflow();

public:

    enum class SeekDirection { beg, cur, end };

    explicit FileBuffer(size_t size = 1024);
    ~FileBuffer();

    FileBuffer(const FileBuffer&) = delete;
    FileBuffer& operator=(const FileBuffer&) = delete;

    bool open(const char* file_path, const char* mode);
    bool is_open() const;
    bool close();

    long seek(long offset, SeekDirection dir);

    // int flush();

    int put_char(char c);
    int get_char();
    char* get_buf();
    size_t get_buf_size() const;
    int peek_char();
};

#endif //LAB_1_FILEBUFFER_H