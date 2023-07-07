#pragma once

#include "file_position.h"
#include "token.h"
#include <fstream>
#include <stdio.h>

class FileReader : std::ifstream {
  private:
    FilePosition pos;
    typedef std::ifstream super;

  public:
    FilePosition &getPos();

    /**
     * @brief return current character, read next one
     *
     * @return int
     */
    int get();

    /**
     * @brief return character without reading next one
     *
     * @return int
     */
    int peek();

    int peek2();

    FileReader(const std::string&);
};
