//
// From http.cpp by camilo on 20/08/2023 02:08 <3ThomasBorregaardSorensen!!
//
#include "platform.h"
#include "request.h"
#include "connect.h"
#include "acme/nano/http/get.h"


namespace windows
{


   namespace nano
   {


      namespace http
      {


         request::request(connect& connect, const ::scoped_string& scopedstrOperation, const ::scoped_string& scopedstrObject) :
            m_connect(connect)
         {

            wstring wstrOperation(scopedstrOperation);

            wstring wstrObject(scopedstrObject);

            m_hinternet = WinHttpOpenRequest(connect.m_hinternet, wstrOperation, wstrObject, NULL,
               WINHTTP_NO_REFERER,
               WINHTTP_DEFAULT_ACCEPT_TYPES,
               WINHTTP_FLAG_SECURE);
            if (m_hinternet && WinHttpSetStatusCallback(m_hinternet, &request::status_callback,
               WINHTTP_CALLBACK_FLAG_SECURE_FAILURE, 0) == WINHTTP_INVALID_STATUS_CALLBACK)
            {
               m_callbackError = GetLastError();
            }
            if (m_hinternet)
            {
               DWORD_PTR context = reinterpret_cast<DWORD_PTR>(this);
               if (!WinHttpSetOption(m_hinternet, WINHTTP_OPTION_CONTEXT_VALUE, &context, sizeof(context)))
                  m_contextError = GetLastError();
            }
            //DWORD dwOptionValue = WINHTTP_DISABLE_REDIRECTS;
            //BOOL b = WinHttpSetOption(m_hinternet, 
             //  WINHTTP_OPTION_DISABLE_FEATURE, &dwOptionValue, sizeof(dwOptionValue));

         }


         request::~request()
         {
            // This backend is synchronous. Close while callback state is still alive.
            if (m_hinternet)
            {
               WinHttpCloseHandle(m_hinternet);
               m_hinternet = nullptr;
            }
         }


         void CALLBACK request::status_callback(HINTERNET, DWORD_PTR context, DWORD status,
            LPVOID information, DWORD informationLength) noexcept
         {
            const auto savedError = GetLastError();
            if (context && status == WINHTTP_CALLBACK_STATUS_SECURE_FAILURE && information
               && informationLength >= sizeof(DWORD))
            {
               auto self = reinterpret_cast<request*>(context);
               self->m_secureFailureCount.fetch_add(1, std::memory_order_relaxed);
               self->m_secureFailureFlags.fetch_or(*static_cast<DWORD*>(information), std::memory_order_relaxed);
            }
            SetLastError(savedError);
         }


         ::string request::security_diagnostics()
         {
            const auto savedError = GetLastError();
            const auto flags = m_secureFailureFlags.load(std::memory_order_relaxed);
            SYSTEMTIME now{};
            GetSystemTime(&now);
            ::string text;
            text.formatf("WinHTTP secure failure flags=0x%08lX; callback registration error=%lu; client UTC=%04u-%02u-%02u %02u:%02u:%02u.",
               flags, (unsigned long)m_callbackError, now.wYear, now.wMonth, now.wDay,
               now.wHour, now.wMinute, now.wSecond);
            if (!flags)
               text += " No detailed security flags were reported by WinHTTP.";
            if (flags & WINHTTP_CALLBACK_STATUS_FLAG_INVALID_CA)
               text += " INVALID_CA: certificate authority is not trusted by this system.";
            if (flags & WINHTTP_CALLBACK_STATUS_FLAG_CERT_DATE_INVALID)
               text += " CERT_DATE_INVALID: certificate validity dates or client clock are invalid.";
            if (flags & WINHTTP_CALLBACK_STATUS_FLAG_CERT_CN_INVALID)
               text += " CERT_CN_INVALID: certificate does not match the requested hostname.";
            if (flags & WINHTTP_CALLBACK_STATUS_FLAG_CERT_REV_FAILED)
               text += " CERT_REV_FAILED: certificate revocation check could not complete.";
            if (flags & WINHTTP_CALLBACK_STATUS_FLAG_CERT_REVOKED)
               text += " CERT_REVOKED: certificate has been revoked.";
            if (flags & WINHTTP_CALLBACK_STATUS_FLAG_INVALID_CERT)
               text += " INVALID_CERT: certificate is invalid.";
            if (flags & WINHTTP_CALLBACK_STATUS_FLAG_SECURITY_CHANNEL_ERROR)
               text += " SECURITY_CHANNEL_ERROR: Schannel failed; inspect TLS, cipher and certificate algorithm compatibility.";
            ::string callbackDetails;
            callbackDetails.formatf("\nWinHTTP security callback count=%lu; context setup error=%lu.",
               m_secureFailureCount.load(std::memory_order_relaxed), (unsigned long)m_contextError);
            text += callbackDetails;

            DWORD securityFlags = 0;
            DWORD size = sizeof(securityFlags);
            ::string details;
            if (WinHttpQueryOption(m_hinternet, WINHTTP_OPTION_SECURITY_FLAGS, &securityFlags, &size))
               details.formatf("\nWinHTTP request security option flags=0x%08lX (not certificate validation results).", (unsigned long)securityFlags);
            else
               details.formatf("\nWinHTTP security option query unavailable: Windows error %lu.", (unsigned long)GetLastError());
            text += details;

            // WinHTTP owns the other, reserved members. Only subject and issuer are LocalFree allocations.
            struct certificate_info : WINHTTP_CERTIFICATE_INFO
            {
               certificate_info() : WINHTTP_CERTIFICATE_INFO{} {}
               ~certificate_info()
               {
                  if (lpszSubjectInfo) LocalFree(lpszSubjectInfo);
                  if (lpszIssuerInfo) LocalFree(lpszIssuerInfo);
               }
            } certificate;
            size = sizeof(WINHTTP_CERTIFICATE_INFO);
            if (WinHttpQueryOption(m_hinternet, WINHTTP_OPTION_SECURITY_CERTIFICATE_STRUCT, &certificate, &size))
            {
               text += "\nServer certificate subject: ";
               text += certificate.lpszSubjectInfo ? ::string(certificate.lpszSubjectInfo) : "(not supplied)";
               text += "\nServer certificate issuer: ";
               text += certificate.lpszIssuerInfo ? ::string(certificate.lpszIssuerInfo) : "(not supplied)";
               SYSTEMTIME starts{}, expires{};
               if (FileTimeToSystemTime(&certificate.ftStart, &starts) && FileTimeToSystemTime(&certificate.ftExpiry, &expires))
               {
                  details.formatf("\nCertificate validity UTC: %04u-%02u-%02u %02u:%02u:%02u through %04u-%02u-%02u %02u:%02u:%02u.",
                     starts.wYear, starts.wMonth, starts.wDay, starts.wHour, starts.wMinute, starts.wSecond,
                     expires.wYear, expires.wMonth, expires.wDay, expires.wHour, expires.wMinute, expires.wSecond);
                  text += details;
               }
               else
                  text += "\nCertificate validity dates unavailable.";
               details.formatf("\nWinHTTP certificate connection key size: %lu bits.", (unsigned long)certificate.dwKeySize);
               text += details;
            }
            else
            {
               details.formatf("\nServer certificate query unavailable: Windows error %lu. WinHTTP may not expose a certificate after a failed handshake; this does not establish whether the certificate is valid.", (unsigned long)GetLastError());
               text += details;
            }
            SetLastError(savedError);
            return text;
         }


         bool request::send_request(::nano::http::get* pnanohttpget)
         {

            ::wstring wstrHost = m_connect.m_wstrHost;

            //wstring wstrMoreHeaders;

            //wstring wstrUserAgent(pnanohttpget->m_strUserAgent);

            //wstrMoreHeaders += L"Host: ";
            //wstrMoreHeaders += wstrHost;
            //wstrMoreHeaders += L"\r\n";
            //wstrMoreHeaders += L"Accept: */*\r\n";
            ////wstrMoreHeaders += L"User-Agent: " + wstrUserAgent + L"\r\n";

            //auto bResults = WinHttpSendRequest(m_hinternet, wstrMoreHeaders, 0, WINHTTP_NO_REQUEST_DATA, 0, 0, 0);
            auto bResults = WinHttpSendRequest(m_hinternet, nullptr, 0, WINHTTP_NO_REQUEST_DATA, 0, 0, reinterpret_cast<DWORD_PTR>(this));
            // End the request.

            return bResults != FALSE;

         }


         bool request::get_response(::nano::http::get * pnanohttpget)
         {

            auto    bResults = WinHttpReceiveResponse(m_hinternet, NULL);/**/

            if (!bResults)
            {

               DWORD dw = ::GetLastError();

               return false;

            }

            DWORD statusCode = 0;
            DWORD statusSize = sizeof(statusCode);
            if (!WinHttpQueryHeaders(m_hinternet, WINHTTP_QUERY_STATUS_CODE | WINHTTP_QUERY_FLAG_NUMBER,
               WINHTTP_HEADER_NAME_BY_INDEX, &statusCode, &statusSize, WINHTTP_NO_HEADER_INDEX))
               return false;
            pnanohttpget->set_status(statusCode);
            pnanohttpget->payload("out_attributes")["http_status_code"] = (::i64)statusCode;
            DWORD dwSize = 0;
            WinHttpQueryHeaders(m_hinternet,
               WINHTTP_QUERY_FLAG_REQUEST_HEADERS
               | WINHTTP_QUERY_RAW_HEADERS_CRLF,
               WINHTTP_HEADER_NAME_BY_INDEX, NULL,
               &dwSize, WINHTTP_NO_HEADER_INDEX);
            wstring wstrRequestHeaders;
            // Allocate memory for
            // 
            //  the buffer.
            if (GetLastError() == ERROR_INSUFFICIENT_BUFFER)
            {
               auto pwszHeaders = wstrRequestHeaders.get_buffer(dwSize / sizeof(WCHAR));

               // Now, use WinHttpQueryHeaders to retrieve the header.
               bResults = WinHttpQueryHeaders(m_hinternet,
                  WINHTTP_QUERY_FLAG_REQUEST_HEADERS
                  | WINHTTP_QUERY_RAW_HEADERS_CRLF,
                  WINHTTP_HEADER_NAME_BY_INDEX,
                  pwszHeaders, &dwSize,
                  WINHTTP_NO_HEADER_INDEX);
               wstrRequestHeaders.release_buffer();
            }
            ::string strRequestHeaders(wstrRequestHeaders);

            
            DWORD dwOutHeadersSize = 0;
            WinHttpQueryHeaders(m_hinternet, WINHTTP_QUERY_RAW_HEADERS_CRLF,
               WINHTTP_HEADER_NAME_BY_INDEX, NULL,
               &dwOutHeadersSize, WINHTTP_NO_HEADER_INDEX);
            wstring wstrOutHeaders;
            // Allocate memory for
            // 
            //  the buffer.
            if (GetLastError() == ERROR_INSUFFICIENT_BUFFER)
            {
               auto pwszOutHeaders = wstrOutHeaders.get_buffer(dwOutHeadersSize / sizeof(WCHAR));

               // Now, use WinHttpQueryHeaders to retrieve the header.
               bResults = WinHttpQueryHeaders(m_hinternet,
                  WINHTTP_QUERY_RAW_HEADERS_CRLF,
                  WINHTTP_HEADER_NAME_BY_INDEX,
                  pwszOutHeaders, &dwOutHeadersSize,
                  WINHTTP_NO_HEADER_INDEX);
               wstrOutHeaders.release_buffer();
            }

            ::string strOutHeaders(wstrOutHeaders);

            pnanohttpget->payload("out_headers").as_property_set().parse_network_headers(strOutHeaders);

            ::string_array_base straOutHeaders;

            straOutHeaders.add_lines(strOutHeaders, true);

            pnanohttpget->property_set().parse_network_headers(straOutHeaders);

            ::u64 contentLength = 0;

            DWORD dwContentLengthBufferSize = sizeof(contentLength);

            auto bContentLength = WinHttpQueryHeaders(m_hinternet,
               WINHTTP_QUERY_CONTENT_LENGTH | WINHTTP_QUERY_FLAG_NUMBER,
               WINHTTP_HEADER_NAME_BY_INDEX,
               &contentLength,
               &dwContentLengthBufferSize,
               WINHTTP_NO_HEADER_INDEX);

            if (!bContentLength)
            {

               contentLength = 0;

            }

            bool bOnlyHeaders = pnanohttpget->payload("only_headers").as_bool();

            if (bOnlyHeaders)
            {

               return true;

            }

            transfer_progress_function transferprogressfunction;

            transferprogressfunction = pnanohttpget->payload("transfer_progress_function");

            dwSize = 0;
            do
            {

               if (!WinHttpQueryDataAvailable(m_hinternet, &dwSize))
               {
                  //            printf("Error %u in WinHttpQueryDataAvailable.\n", GetLastError());

                  return false;

               }
               ::memory memory;

               memory.set_size(dwSize);
               // Allocate space for the buffer.        
               //pszOutBuffer = ___new byte[dwSize + 1];
               //if (!pszOutBuffer)
               //{
                 // printf("Out of memory\n");
                  //dwSize = 0;
               //}
               //else
               //{
               // 
               memory.zero();
               // Read the Data.            
               //ZeroMemory(scopedstrOutBuffer, dwSize + 1);
               DWORD dwDownloaded = 0;
               if (!WinHttpReadData(m_hinternet, (LPVOID)memory.data(), dwSize, &dwDownloaded))
               {
                  //printf("Error %u in WinHttpReadData.\n", GetLastError());
                  return false;
               }

               memory.set_size(dwDownloaded);

               if (dwDownloaded > 0)
               {

                  pnanohttpget->get_memory_response()->append(memory);

                  if (transferprogressfunction)
                  {

                     if (contentLength > 0)
                     {

                        transferprogressfunction((::f64)pnanohttpget->get_memory_response()->size() /
                           (::f64)contentLength, pnanohttpget->get_memory_response()->size(),
                           contentLength);
                     }
                     else
                     {

                        transferprogressfunction(0., pnanohttpget->get_memory_response()->size(),
                           0);

                     }


                  }

               }

               //dwSize -= dwDownloaded;
               //else
               //
               //{
               //   //printf("%s", pszOutBuffer); 
               //   DWORD wmWritten;
               //   bool fr = WriteFile(hFile, pszOutBuffer, dwSize, &wmWritten, NULL);
               //   ::i32 n = GetLastError();
               ////}
               // Free the memory allocated to the buffer.            
               //delete[] pszOutBuffer;
            //}
            } while (dwSize > 0);

            return true;

         }


      } // namespace http


   }// namespace nano


} // namespace windows



