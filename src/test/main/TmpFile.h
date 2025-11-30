//
// Created by admin on 11.11.2025.
//

#ifndef LAB_1_TMPFILE_H
#define LAB_1_TMPFILE_H
#include <string>

class TmpFile {
private:
  std::string file_path;

public:
  TmpFile(const std::string& file_path);

  ~TmpFile();
  TmpFile(const TmpFile&) = delete;
  TmpFile& operator=(const TmpFile&) = delete;

  const std::string& get_file_path() const;
};

#endif // LAB_1_TMPFILE_H
