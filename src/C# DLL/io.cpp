#include "io.hpp"
#include "IO/io.hpp"

void createFile(const char* path, bool overwrite) {
    io::files::create(path, overwrite);
}

void createFileWithContent(const char* path, const char* content, bool overwrite) {
    io::files::create(path, content, overwrite);
}