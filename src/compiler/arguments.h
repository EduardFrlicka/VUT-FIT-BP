#pragma once
#include <string>
#include <vector>

class Arguments {
  public:
    std::string target_dir;
    std::string target_bin;

    std::string compiler_templates_path;
    std::string static_templates_path;

    std::vector<std::string> sources;

    bool help = false;

    Arguments();
    Arguments(int argc, char *argv[]);
};

extern Arguments args;
