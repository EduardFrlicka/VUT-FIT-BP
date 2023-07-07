#pragma once
#include <string>
#include <vector>

class Arguments {
  public:
    std::string target_dir = "build";
    std::string target_bin = "binary";

    std::vector<std::string> sources;

    bool help = false;

    Arguments();
    Arguments(int argc, char *argv[]);
};

extern Arguments args;
