#include "TmpFile.h"

TmpFile::TmpFile(const std::string &file_path) : file_path(file_path) {}

TmpFile::~TmpFile() {
  std::remove(file_path.c_str());
}

const std::string& TmpFile::get_file_path() const {
  return file_path;
}


