#pragma once
#include <cstdint>
#include <functional>
#include <string>
namespace ca2_tls {
struct response {
    unsigned status = 0;
    std::string headers;
    std::uint64_t content_length = 0;
};
using logger = std::function<void(const std::string&)>;
using receiver = std::function<void(const unsigned char*, std::size_t, std::uint64_t)>;
response get(const std::string& url, const std::string& user_agent, bool headers_only,
    const receiver& receive, const logger& log);
// Four attempts, waiting 1, 2 and 4 seconds. Reset must discard all partial data.
response get_with_retry(const std::string& url, const std::string& user_agent, bool headers_only,
    const receiver& receive, const logger& log, const std::function<void()>& reset,
    const logger& status = {});
}
