// Refactor by camilo on 2024-05-27 10:47 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "http.h"
#include "acme/platform/node.h"
//#include <stdio.h>
//#include <sys/stat.h>
//#include <stdlib.h>
#include <string.h>
//#include <unistd.h>
//#include <fcntl.h>
//#include <time.h>
//#include <memory.h>
//
//char * get_line(char * str, char * & next);
//char * get_command_output(const_char_pointer pszCommand);

//#include "apex/networking/http/_user_agent.h"

//#define  + m_strUserAgent +  "curl/nano_http_command_line"


namespace command_line
{


   namespace nano
   {


      namespace http
      {


         bool http::_curl_check_url_ok(const ::url::url & url, ::property_set & set)
         {

            ::string strCommand;

            ::string strUserAgent = set["in_headers"]["user-agent"];

            if (strUserAgent.is_empty())
            {

               strUserAgent = m_strUserAgentFallback;

            }

            strCommand = "curl -A \""  + strUserAgent +  "\" --http1.1 --silent -I " + url.as_string();

            auto strOutput = node()->get_command_output(strCommand);

            if(strOutput.is_empty())
            {

               return false;

            }

            debugf("command_line::http::curl check : %s", strOutput.c_str());

            ::string_array_base stra;

            stra.add_lines(strOutput);

            for (auto &newline: stra) {

//auto pszNewLine = get_line(scopedstr, psz);

               if (newline.is_empty()) {

                  return false;

               }

               if(newline[0] == 'H'
               && newline[1] == 'T'
               && newline[2] == 'T'
               && newline[3] == 'P'
               && newline[4] == '/')
               {

                  //printf_line("Found HTTP/ Line : %s", newline.c_str());

                  auto pszSpace = strchr(newline.c_str() + 4, ' ');

                  if(!pszSpace)
                  {

                     return false;

                  }

                  ///printf_line("Found space after HTTP/");

                  auto nonSpace = strspn(pszSpace + 1, " \t");

                  auto pszNonSpace = pszSpace + nonSpace;

                  ::string strStatus = pszNonSpace;

                  strStatus.trim();

                  if(strStatus == "200" || strStatus.begins("200 "))
                  {

                     printf_line("Status is 200 Ok.");

                     return true;

                  }

                  return false;

               }

            }

            return false;

         }


         ::url::url http::_curl_get_effective_url(const ::url::url & url, ::property_set & set)
         {

            ::string strUserAgent = set["in_headers"]["user-agent"];

            if (strUserAgent.is_empty())
            {

               strUserAgent = m_strUserAgentFallback;

            }

            ::string strSourceUrl = url.as_string();

            ::string strCommand;

            //strCommand.format("curl -A \"{}\" --http1.1 -Ls -o /dev/null -w %{{url_effective}} \"{}\"", strUserAgent, strSourceUrl);

            strCommand.format("curl -A \"{}\" --http1.1 -ILs -o /dev/null -w %{{url_effective}} \"{}\"", strUserAgent, strSourceUrl);

            print_line(strCommand);

            ::string strOutput;

            ::string strError;

            auto iExitCode = node()->get_posix_shell_command_output(strOutput, strError, strCommand);

            ::string strOut;

            strOut += strOutput;

            strOut += "\n";

            strOut += strError;

            print_line(strOut);

            if (iExitCode != 0)
            {

               throw ::exception(error_failed);

            }

            auto strEffectiveUrl = strOutput;

            print_line("Source URL : " + strSourceUrl);

            print_line("Effective URL : " + strEffectiveUrl);

            return strEffectiveUrl;

         }



         void http::_curl(::nano::http::get * pnanohttpget)
         {

            auto strUserAgent = pnanohttpget->m_strUserAgent;

            if (strUserAgent.is_empty())
            {

               strUserAgent = m_strUserAgentFallback;

            }

            auto strUrl = pnanohttpget->url().as_string();

            ::string strCommand;

            strCommand.format("curl -s -i -A \"{}\" --http1.0 \"{}\"", strUserAgent, strUrl);

            ::memory memoryOutput;

            ::memory memoryError;

            int iExitCode = node()->get_command_output_memory(
               memoryOutput,
               memoryError,
               strCommand);

            unsigned char * pData = memoryOutput.data();

            unsigned char * pBeginBody = nullptr;

            auto pEndHeaders = memoryOutput.find("\r\n\r\n");

            if(pEndHeaders)
            {

               pBeginBody = pEndHeaders + 4;

            }
            else
            {

               pEndHeaders = memoryOutput.find("\n\n");

               if (pEndHeaders)
               {

                  pBeginBody = pEndHeaders + 2;

               }

            }

            ::string strOutHeaders;

            if(pEndHeaders)
            {

               strOutHeaders.assign((const char *) pData, pEndHeaders - pData);

               memoryOutput.assign(pBeginBody, memoryOutput.end() - pBeginBody);

            }

            pnanohttpget->get_memory_response()->assign(memoryOutput);

            pnanohttpget->property_set().parse_network_headers(strOutHeaders);

         }


         void http::_curl_download(const ::file::path & path, const ::url::url & url, ::property_set & set)
         {

            ::string strCommand;

            ::string strUrl(url.as_string());

            ::string strUserAgent = set["in_headers"]["user-agent"];
            
            print_line("Using the following user agent to download: \""  + strUserAgent +  "\".");

            strCommand.formatf("curl -fL -s -D - -A \"%s\" \"%s\" -o \"%s\"",strUserAgent.c_str(), strUrl.c_str(), path.c_str());

            ::memory memoryOutput;

            ::memory memoryError;

            int iExitCode = node()->get_command_output_memory(memoryOutput, memoryError, strCommand);

            ::string strOutHeaders;

            strOutHeaders = memoryOutput.as_utf8();

            if (strOutHeaders.has_character())
            {

               set.parse_network_headers(strOutHeaders);

            }

         }


      } // namespace http


   } // namespace nano


} // namespace command_line

