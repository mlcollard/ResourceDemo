/*
    ResourceDemo.cpp

    Shows reaching a resource limit on file descriptors.
    A file is open with a file descriptor, but not closed.
    Therefore a resource leak occurs.

    To view file descriptor limits:

    ulimit -n

    To set file descriptor limits, i.e., to 4096:

    ulimit -n 4096
*/

#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
#include <string_view>

using namespace std::literals::string_view_literals;

int main(int argc, char* argv[]) {

    // require filename
    if (argc != 2) {
        std::cerr << "usage: " << argv[0] << " <filename> " << '\n';
        return 1;
    }

    // write to the output file as many lines as we can
    int counter = 0;
    while (true) {

        // Open a file using low-level open()
        int fd = open(argv[1], O_WRONLY | O_CREAT | O_APPEND, 0644);
        if (fd == -1) {
            std::cerr << "Failed to open file." << std::endl;
            return 1;
        }

        // Write to the file
        const std::string_view text = "Writing this to a file.\n"sv;
        write(fd, text.data(), text.size());

        // Status
        std::cerr << ++counter << '\n';

        // Intentionally not closing the file descriptor to cause a leak
        // close(fd);
    }

    return 0;
}
