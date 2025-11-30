#include "src/StreamLib.h"

int main() {

  TextFileReaderWriter file("C:/Users/admin/Desktop/test.txt");

  std::cout << file.read_word() << std::endl;
  std::cout << file.read_word() << std::endl;
  file.seek(0, FileBuffer::SeekDirection::end);
  file.write_word("TUTUTU");
  file.flush();
  file.write_word("tu");
  // file << " " << "x" << " ";

}
