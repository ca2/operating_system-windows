#include "platform.h"
#if defined(WINDOWS)
#include "http.h"
#include "acme/nano/http/get.h"
#include "acme/prototype/prototype/url.h"
#include <wininet.h>

namespace windows { namespace nano { namespace http_native {

namespace {
   struct native_handle
   {
      HINTERNET value;
      explicit native_handle(HINTERNET h) : value(h) {}
      ~native_handle() { if (value) InternetCloseHandle(value); }
      native_handle(const native_handle&) = delete;
      native_handle& operator=(const native_handle&) = delete;
   };

   ::string native_error(const char* operation, DWORD code)
   {
      ::string text;
      text.formatf("%s failed (Windows error %lu / 0x%08lX).", operation,
         (unsigned long)code, (unsigned long)code);
      wchar_t description[2048] = {};
      auto module = GetModuleHandleW(L"wininet.dll");
      if (FormatMessageW(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_FROM_HMODULE
            | FORMAT_MESSAGE_IGNORE_INSERTS, module, code, 0, description, 2048, nullptr))
         text += " " + ::string(description);
      if (code == ERROR_INTERNET_SEC_CERT_DATE_INVALID)
         text += " Check the client clock and server certificate validity dates.";
      if (code == ERROR_INTERNET_INVALID_CA)
         text += " The certificate authority is not trusted by this system.";
      if (code == ERROR_INTERNET_SEC_CERT_CN_INVALID)
         text += " The certificate hostname does not match.";
      if (code == ERROR_INTERNET_SECURITY_CHANNEL_ERROR)
         text += " Schannel could not establish TLS; protocol/cipher compatibility may be the cause.";
      return text;
   }
}

void http::perform(::nano::http::get* request)
{
   information() << "HTTPS backend: native WinINet (system Schannel); GET " << request->m_url.as_string();
   auto fail = [this](const char* operation, DWORD code)
   {
      auto message = native_error(operation, code);
      error() << message;
      throw ::exception(error_failed, message);
   };
   ::wstring agent(request->m_strUserAgent);
   native_handle session(InternetOpenW(agent, INTERNET_OPEN_TYPE_PRECONFIG, nullptr, nullptr, 0));
   if (!session.value) fail("InternetOpenW", GetLastError());
   DWORD timeout = 30000;
   for (DWORD option : {INTERNET_OPTION_CONNECT_TIMEOUT, INTERNET_OPTION_SEND_TIMEOUT, INTERNET_OPTION_RECEIVE_TIMEOUT})
      if (!InternetSetOptionW(session.value, option, &timeout, sizeof(timeout)))
         information() << "WinINet timeout setup failed: " << (unsigned long)GetLastError();

   ::wstring host(request->m_url.connect().host());
   native_handle connection(InternetConnectW(session.value, host, INTERNET_DEFAULT_HTTPS_PORT,
      nullptr, nullptr, INTERNET_SERVICE_HTTP, 0, 0));
   if (!connection.value) fail("InternetConnectW", GetLastError());
   ::wstring uri(request->m_url.request().as_string());
   const wchar_t* accepts[] = {L"*/*", nullptr};
   // No certificate-ignore flags and no interactive certificate/authentication prompts.
   native_handle response(HttpOpenRequestW(connection.value, L"GET", uri, nullptr, nullptr, accepts,
      INTERNET_FLAG_SECURE | INTERNET_FLAG_RELOAD | INTERNET_FLAG_NO_CACHE_WRITE
         | INTERNET_FLAG_NO_UI | INTERNET_FLAG_NO_COOKIES, 0));
   if (!response.value) fail("HttpOpenRequestW", GetLastError());
   if (!HttpSendRequestW(response.value, nullptr, 0, nullptr, 0))
   {
      const DWORD code = GetLastError();
      DWORD flags = 0, size = sizeof(flags);
      if (InternetQueryOptionW(response.value, INTERNET_OPTION_SECURITY_FLAGS, &flags, &size))
      {
         ::string details;
         details.formatf("WinINet request security flags=0x%08lX (not validation results).", (unsigned long)flags);
         error() << details;
      }
      fail("HttpSendRequestW", code);
   }
   DWORD status = 0, size = sizeof(status);
   if (!HttpQueryInfoW(response.value, HTTP_QUERY_STATUS_CODE | HTTP_QUERY_FLAG_NUMBER,
         &status, &size, nullptr)) fail("HttpQueryInfoW(status)", GetLastError());
   request->set_status(status);
   request->payload("out_attributes")["http_status_code"] = (::i64)status;
   information() << "WinINet HTTP status " << (unsigned long)status;

   DWORD headerSize = 0;
   if (!HttpQueryInfoW(response.value, HTTP_QUERY_RAW_HEADERS_CRLF, nullptr, &headerSize, nullptr)
         && GetLastError() == ERROR_INSUFFICIENT_BUFFER)
   {
      ::wstring headers;
      auto buffer = headers.get_buffer(headerSize / sizeof(wchar_t));
      const BOOL ok = HttpQueryInfoW(response.value, HTTP_QUERY_RAW_HEADERS_CRLF, buffer, &headerSize, nullptr);
      headers.release_buffer();
      if (!ok) fail("HttpQueryInfoW(headers)", GetLastError());
      ::string raw(headers);
      request->payload("out_headers").as_property_set().parse_network_headers(raw);
      ::string_array_base lines;
      lines.add_lines(raw, true);
      request->property_set().parse_network_headers(lines);
   }
   if (request->payload("only_headers").as_bool()) return;
   DWORD contentLength = 0;
   size = sizeof(contentLength);
   if (!HttpQueryInfoW(response.value, HTTP_QUERY_CONTENT_LENGTH | HTTP_QUERY_FLAG_NUMBER,
         &contentLength, &size, nullptr)) contentLength = 0;
   transfer_progress_function progress;
   progress = request->payload("transfer_progress_function");
   char buffer[32768];
   for (;;)
   {
      DWORD received = 0;
      if (!InternetReadFile(response.value, buffer, sizeof(buffer), &received))
         fail("InternetReadFile", GetLastError());
      if (!received) break;
      request->get_memory_response()->append(buffer, received);
      if (progress)
      {
         const auto count = request->get_memory_response()->size();
         progress(contentLength ? (::f64)count / contentLength : 0., count, contentLength);
      }
   }
}

}}}
#endif
