#include "transport.h"
#include <cstdio>
#include <stdexcept>
#include <string>
int main(int argc, char** argv) {
    if (argc < 2) return 2;
    const bool framing_failure = argc > 3 && std::string(argv[2]) == "fail";
    const bool negative = argc > 2 && std::string(argv[2]) == "reject";
    try {
        std::uint64_t received = 0;
        auto response = ca2_tls::get(argv[1], "ca2-tls-probe", argc <= 2,
            [&received](const unsigned char*, size_t count, std::uint64_t) { received += count; },
            [](const std::string& line) { std::printf("%s\n", line.c_str()); });
        std::printf("status=%u bytes=%llu\n", response.status, (unsigned long long)received);
        return negative || framing_failure || response.status != 200 ? 1 : 0;
    } catch (const std::exception& error) {
        std::printf("%s\n", error.what());
        return (negative && std::string(error.what()).find("Certificate verification:") != std::string::npos)
            || (framing_failure && std::string(error.what()).find(argv[3]) != std::string::npos) ? 0 : 1;
    }
}
