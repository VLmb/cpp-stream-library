#include "FileBuffer.h"
#include <stdexcept>
#include <cstring>

FileBuffer::FileBuffer(size_t size)
: file_handle(nullptr),
  buffer(new char[size]),
  buffer_size(size),
  write_pos(buffer),
  read_pos(buffer),
  read_end(buffer)
{
    if (buffer_size == 0) throw std::runtime_error("Буффер не может быть пустым.");
}

FileBuffer::~FileBuffer() {
    close();
    delete[] buffer;
}

bool FileBuffer::open(const char* file_path, const char* mode) {
    if (is_open()) return false;
    file_handle = fopen(file_path, mode);
    return is_open();
}

bool FileBuffer::is_open() const { return file_handle != nullptr; }

bool FileBuffer::close() {
    if (!is_open()) return true;

    if (sync() == -1) {
        fclose(file_handle);
        file_handle = nullptr;
        return false;
    }

    int result = fclose(file_handle);
    file_handle = nullptr;
    return result == 0;
}

char* FileBuffer::get_buf() {
    if (!is_open()) {
        return nullptr;
    }

    if (underflow() == -1) {
        return nullptr;
    }

    return buffer;
}

size_t FileBuffer::get_buf_size() const {
    return static_cast<size_t>(read_end - read_pos);
}

int FileBuffer::sync() {

    if (write_pos > buffer) {
        if (flush() == -1) {
            return -1;
        }
    }
    write_pos = buffer;

    read_pos = buffer;
    read_end = buffer;

    return 0;
}

long FileBuffer::seek(long offset, SeekDirection dir) {
    if (!is_open()) return -1;

    if (sync() == -1) {
        return -1;
    }

    int where = (dir == SeekDirection::beg) ? SEEK_SET :
                 (dir == SeekDirection::cur) ? SEEK_CUR : SEEK_END;

    if (fseek(file_handle, offset, where) != 0) {
        return -1;
    }

    return ftell(file_handle);
}

// int FileBuffer::flush() {
//     return overflow();
// }

int FileBuffer::flush() {
    if (!is_open()) return -1;

    long write_start_pos = ftell(file_handle);
    if (write_start_pos == -1) {
        return -1;
    }

    const size_t count = write_pos - buffer;
    if (count == 0) {
        return 0;
    }

    const size_t written_count = fwrite(buffer, 1, count, file_handle);
    if (written_count != count) {
        return -1;
    }

    write_pos = buffer;
    read_pos  = buffer;
    read_end  = buffer;

    fseek(file_handle, write_start_pos + written_count, SEEK_SET);

    return 0;
}

int FileBuffer::underflow() {
    if (sync() == -1) {
        return -1;
    }

    const size_t read_count = fread(buffer, 1, buffer_size, file_handle);
    if (read_count == 0) {
        return -1;
    }

    read_pos = buffer;
    read_end = buffer + read_count;

    return static_cast<unsigned char>(*read_pos);
}

int FileBuffer::put_char(char c) {
    if (!is_open()) return -1;

    if (read_pos < read_end) {
        long current_read_offset = ftell(file_handle) - (read_end - read_pos);
        fseek(file_handle, current_read_offset, SEEK_SET);
        read_pos = buffer;
        read_end = buffer;
    }

    if (write_pos >= buffer + buffer_size) {
        if (flush() == -1) {
            return -1;
        }
    }

    *write_pos++ = c;
    return static_cast<unsigned char>(c);
}


int FileBuffer::peek_char() {
    if (read_pos >= read_end) {
        if (underflow() == -1) {
            return -1;
        }
    }
    return static_cast<unsigned char>(*read_pos);
}

int FileBuffer::get_char() {
    int ch = peek_char();
    if (ch != -1) {
        read_pos++;
    }
    return ch;
}