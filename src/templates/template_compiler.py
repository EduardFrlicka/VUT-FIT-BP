import sys
import os.path

def main():
    print("#include <map>")
    print("#include <string>")

    print("")

    print("std::map<std::string, std::string> code_templates = {")

    # template_file = "/home/frlic/Programing/OOPN-gen/src/compiler/main.cpp"
    # template = conv_file(template_file, 4)
    # print(template)

    print(conv_file("/home/frlic/Programing/OOPN-gen/src/templates/class.cpp", 4))


    print("};")
    pass


def conv_file(filename: str, align:int):
    template_name, _ = os.path.splitext(os.path.basename(filename))
    template_text = ""

    text_align = align + 5 + len(template_name)

    with open(filename, "r") as f:
        for line in f:
            template_text += f"{'':{text_align}s}\"{conv_line(line)}\"\n"
    
    template_text = template_text.strip()
    
    return f"{'':{align}s}{{\"{template_name}\", {template_text}}},"


def conv_line(line: str):
    return "".join([conv_char(char) for char in line])


def conv_char(char: str):
    exceptions = {
        "\n": "\\n",
        "\"": "\\\"",
    }

    if char in exceptions:
        return exceptions[char]

    if char.isprintable():
        return char

    return f"\\x{ord(char):03x}"


if __name__ == "__main__":
    main()
