// Refactor by camilo on 2024-05-27 10:59 <3ThomasBorregaardSorensen!!
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
//char * as_string(const_char_pointer pszFilename);
//
//
//char * get_line(char * str, char * & next);
//char * get_command_output(const_char_pointer pszCommand);
//
//
//char * start_temporary_file_name();
//void end_temporary_file_name(char * ptmpname);
//char * end_temporary_file_name_as_string(char * ptmpname);

namespace command_line
{


   namespace nano
   {


      namespace http
      {


         bool http::_wget_check_url_ok(const ::url::url & url, ::property_set & set)
         {

            ::string strCommand;

            ::string strUserAgent = set["in_headers"]["user-agent"];

            if (strUserAgent.is_empty())
            {

               strUserAgent = m_strUserAgentFallback;

            }

            ::string strUrl(url.as_string());

            strCommand.formatf("wget --spider -S -U \"%s\" \"%s\"", strUserAgent.c_str(), strUrl.c_str());

            print_line(strCommand);

            //debug() << strCommand;

            ::string strOutput;

            ::string strError;

            auto iExitCode = node()->get_posix_shell_command_output(strOutput, strError, strCommand);

            ::string strOut;

            strOut += strOutput;

            strOut += "\n";

            strOut += strError;

            //auto ptmpname = start_temporary_file_name();

            //sprintf(szCommand, "wget -o \"%s\" -S \"%s\"", ptmpname, pszUrl);

            //::system(szCommand);

            //rcmdauto psz = end_temporary_file_name_as_string(ptmpname);

            ::string_array_base stra;

            stra.add_lines(strOut);

            bool bOk = false;

            for (auto &newline: stra)
            {

//auto pszNewLine = get_line(scopedstr, psz);

               print_line(newline);

               ::string str(newline);

               str.trim();

               if (str.begins_eat("HTTP/"))
               {

                  ::string strHttpVersion = str.get_word(" ");

                  if (strHttpVersion.is_empty())
                  {

                     continue;

                  }

                  ::string strStatus = str.get_word(" ");

                  if (strStatus.is_empty())
                  {

                     continue;

                  }

                  if (strStatus == "200")
                  {

                     if (iExitCode == 0)
                     {

                        print_line("*** status is ok and exit code has no errors!! ***");

                        bOk = true;

                     }

                  }

               }

            }

            return bOk;

         }


         ::url::url http::_wget_get_effective_url(const ::url::url & url, ::property_set & set)
         {

            ::string strCommand;

            ::string strUrl(url.as_string());

            strCommand.formatf("wget --spider %s", strUrl.c_str());

            ::string strOutput;

            ::string strError;

            auto iExitCode= node()->get_command_output(strOutput, strError, strCommand);

            if (strError.is_empty()) {

               return strUrl;

            }

            ::string_array_base stra;

            stra.add_lines(strError);

            for (auto &newline: stra) {

//auto pszNewLine = get_line(scopedstr, psz);

               if (newline.is_empty()) {

                  break;

               }

               newline.trim();

               if (newline.case_insensitive_begins_eat("location:"))
               {

                  newline.trim();

                  if(newline.has_character())
                  {

                     strUrl = newline;

                  }

               }

            }

            strUrl.ends_eat(" [following]");

            if (strUrl.is_empty())
            {

               strUrl = url.as_string();

               return strUrl;

            }

            return strUrl;

         }


         void http::_wget(::nano::http::get * pnanohttpget)
         {

            auto strUserAgent = pnanohttpget->m_strUserAgent;

            if (strUserAgent.is_empty())
            {

               strUserAgent = m_strUserAgentFallback;

            }

            auto strUrl = pnanohttpget->url().as_string();

            ::string strCommand;

            strCommand.format("wget -q -S -O - --user-agent=\"{}\" \"{}\"", strUserAgent, strUrl);

            ::memory memoryOutput;

            ::memory memoryError;

            print_line(strCommand);

            int iExitCode = node()->get_command_output_memory(
               memoryOutput,
               memoryError,
               strCommand);

            ::string strOutHeaders;

            strOutHeaders = memoryError.as_utf8();

            print_line("OutHeaders:");

            print_line(strOutHeaders);

            pnanohttpget->get_memory_response()->assign(memoryOutput);

            string_array_base straOutHeaders;

            straOutHeaders.add_lines(strOutHeaders, true);

            straOutHeaders.trim();

            pnanohttpget->property_set().parse_network_headers(straOutHeaders);

         }


         void http::_wget_download(const ::file::path & path, const ::url::url & url, ::property_set & set )
         {

            ::string strCommand;

            ::string strUrl(url.as_string());

            auto strUserAgent = set["in_headers"]["user-agent"].as_string();

            if (strUserAgent.is_empty())
            {

               strUserAgent = m_strUserAgentFallback;

            }

            strCommand.formatf("wget -q -S --user-agent=\"%s\" \"%s\" -O \"%s\"", strUserAgent.c_str(),strUrl.c_str(), path.c_str());

            ::memory memoryOutput;

            ::memory memoryError;

            print_line(strCommand);

            int iExitCode = node()->get_command_output_memory(memoryOutput, memoryError, strCommand);

            ::string strOutHeaders;

            strOutHeaders = memoryError.as_utf8();

            if (strOutHeaders.has_character())
            {

               string_array_base straOutHeaders;

               straOutHeaders.add_lines(strOutHeaders, true);

               straOutHeaders.trim();

               set.parse_network_headers(straOutHeaders);

            }

         }


      } // namespace http


   } // namespace nano


} // namespace command_line

