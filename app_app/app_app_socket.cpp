#include "framework.h"


namespace user_service
{


   static ::collection::count s_countNetnodeSocket = 0;


   socket::socket() :
      ::object(h.get_application()),
      base_socket(h),
      ::sockets::socket(h),
      stream_socket(h),
      tcp_socket(h),
      http_base_socket(h),
      http_socket(h),
      httpd_socket(h)
   {
      m_bSetCookie = true;
      s_countNetnodeSocket++;
   }



   socket::~socket()
   {
      s_countNetnodeSocket--;
   }

   void socket::send_response()
   {

      string strReferer = inheader("referer");

      string_array stra;

      stra.add("http://store.ca2.cc/");
      stra.add("https://store.ca2.cc/");
      stra.add("http://desktop.ca2.cc/");
      stra.add("https://desktop.ca2.cc/");

      string strPrefix;

      for (auto & str : stra)
      {

         if (strReferer.case_insensitive_begins(str))
         {

            strPrefix = str;

            break;

         }

      }

      if (strPrefix.has_char())
      {

         strPrefix.ends_eat_ci("/");

         outheader("Access-Control-Allow-Origin") = strPrefix;

         string strStart;

         if (::str().begins(m_request.m_strRequestUri, "/passthrough/"))
         {
         }
         else if (::str().begins_get_prefix(strStart, m_request.m_strRequestUri, "/start/")
                  || ::str().begins_get_prefix(strStart, m_request.m_strRequestUri, "/start_x86/")
                  || ::str().begins_get_prefix(strStart, m_request.m_strRequestUri, "/start_x64/"))
         {

            string strUserAgent = inheader("user-agent");

            string strRequest = m_request.m_strRequestUri;

            strRequest.case_insensitive_begins_eat(strStart);

            strsize iFind = strRequest.case_insensitive_find('?');

            string strApp = strRequest;

            if (iFind >= 0)
            {

               strApp = strApp.substr(0, iFind);

            }

            ::file::path path;

            if (strStart == "/start_x64/")
            {

               path = ::dir::program_files_x86() / "ca2/app_app/x64/app_app.exe";

            }
            else
            {

               path = ::dir::program_files_x86() / "ca2/app_app/x86/app_app.exe";

            }

            ::fork(get_application(), [=]
            {

               unsigned int uiPid;

               call_async(path, ": app=" + strApp, path.folder(), SW_SHOWNORMAL, false, &uiPid);

            });

            string str = "OK... soon patch applier (SPA) is working...";

            outheader("content-type") = "text/html; charset=UTF-8";

            response().file().write(str);

         }
         else if (::str().begins(m_request.m_strRequestUri, "/matter/"))
         {
            //         outheader("Cache-control") = "public";
            //         outheader("Pragma") = "public";
            //         int iPathCount;
            //         outheader("Expires") = http()->gmdate(pdatetime->strtotime(nullptr, "+1 day", 0, iPathCount));
            //#ifdef WINDOWS
            //         simple_file_server(::file::path("Z:\\") / m_request.m_strRequestUri);
            //#else
            //         simple_file_server(m_request.m_strRequestUri);
            //#endif
         }
         else if (::str().begins(m_request.m_strRequestUri, "/is_user_service_installed/"))
         {

            string strKey = inheader("sec-websocket-key");//
            //string strKey = "dGhlIHNhbXBsZSBub25jZQ==";
            strKey.trim();
            strKey += "258EAFA5-E914-47DA-95CA-C5AB0DC85B11";
            memory mem;
            mem.assign(strKey);
            memory memSha1;
            psystem->crypto().sha1(memSha1, mem);
            strKey = pbase64->encode(memSha1);
            outheader("Sec-WebSocket-Accept") = strKey;
            outheader("Connection") = "Upgrade";
            outheader("Upgrade") = "websocket";
            outattr("http_status_code") = 101;
            outattr("http_version") = "HTTP/1.1";
            outattr("http_status") = "Switching Protocols";
            Respond();
            memory m;
            string strMessage = "yes_fontopus_com";
            m.set_size(strMessage.length() + 2);
            m.get_data()[0] = 0x81;
            m.get_data()[1] = strMessage.length();
            memory_copy(&m.get_data()[2], strMessage.c_str(), strMessage.length());
            write(m.get_data(), m.get_size());
            return;
         }
         else
         {

         }

         if (!outheaders().has_property("content-type") && response().file().get_length() > 0)
         {

            outheader("content-type") = "text/html; charset=UTF-8";

         }
         if (IsSSLServer())
         {

            outheader("strict-transport-security") = "maximum-age=31536000; includeSubDomains";

         }

      }


      int iStatusCode;

      string strStatus;

      if (outattr("http_status_code").is_new() || outattr("http_status").is_new())
      {

         if (outheaders().has_property("location"))
         {

            iStatusCode = 303; // 303 (See Other Location)

            strStatus = "See Other";

         }
         else
         {

            iStatusCode = 200;

            strStatus = "OK";

         }

         outattr("http_status_code") = iStatusCode;

         outattr("http_status") = strStatus;

      }

      outattr("http_version") = "HTTP/1.1";

      if (::str().begins(outheader("content-type"), "image/"))
      {

         m_bSetCookie = false;

      }
      else if (outheader("content-type") == "application/javascript")
      {

         m_bSetCookie = false;

      }
      else if (outheader("content-type") == "text/css")
      {

         m_bSetCookie = false;

      }

      Respond();

   }




   void socket::OnExecute()
   {
      string strUrl = m_request.attr("http_protocol").get_string() + "://" + m_request.header("host").get_string() + m_request.attr("request_uri").get_string();
      informationf("netnode::socket::OnExecute Url ----**START**====> %s", strUrl);
auto tickExecuteBeg = ::tick::now();
      m_bEnd = false;
      send_response();
auto tickExecuteEnd = ::tick::now();
      informationf("netnode::socket::OnExecute Url ----**END****====> %s", strUrl);
      informationf("netnode::socket::OnExecute Ms -----**END****====> " __prtick, __pr(tickExecuteEnd - tickExecuteBeg));
   }

   void socket::OnResponseComplete()
   {
   }


   bool socket::http_filter_response_header(atom key, string_array & straValue)
   {
      if (key == "location" && straValue.get_count() >= 1)
      {
         for (int i = 0; i < straValue.get_size(); i++)
         {
            url_domain domain;
            domain.create(purl->get_server(straValue[i]));
            if (domain.m_strName == "account.ca2.cc")
            {
               //straValue[i] = "https://" + papplication->m_strFontopusServer + purl->get_object(straValue[i]);
            }
         }
      }
      else if (!m_bSetCookie && key == "set-cookie")
      {
         return false;
      }
      return true;
   }

   void socket::OnSSLAccept()
   {

      ::sockets::httpd_socket::OnSSLAccept();
   }

   void socket::simple_file_server(const ::string & pszPath)
   {

      pointer_array < ::i32_array > rangea;

      if (strlen(inheader("range")) > 0)
      {
         string_array straItem;
         straItem.explode("=", inheader("range"));
         if (straItem.get_count() == 2)
         {
            string strUnit = straItem[0];
            string_array stra;
            stra.explode(",", straItem[1]);
            for (int i = 0; i < stra.get_count(); i++)
            {
               string_array straRange;
               straRange.explode("-", stra[i]);
               if (straRange.get_count() == 2)
               {
                  rangea.add(___new ::i32_array());
                  rangea.last_ptr()->add(atoi(straRange[0]));
                  straRange[1].trim();
                  if (strlen(straRange[1]) == 0)
                     rangea.last_ptr()->add(-1);
                  else
                     rangea.last_ptr()->add(atoi(straRange[1]));
               }
            }
         }
      }

      read_file(pszPath, &rangea);

   }

   void socket::simple_image_server(const ::string & pszPath, int iMaxWidth, int iMaxHeight)
   {

      if (iMaxWidth <= 0 && iMaxHeight <= 0)
      {
         simple_file_server(pszPath);
      }
      else
      {
/*         ::image::image_pointer pimage;

/*         pimage->load_image(pszPath);

         double dRateW = 1.0;

         if (iMaxWidth > 0)
         {
/*            if (pimage->width() > iMaxWidth)
            {
/*               dRateW = (double)iMaxWidth / (double)pimage->width();
            }
         }

         double dRateH = 1.0;

         if (iMaxHeight > 0)
         {
/*            if (pimage->height() > iMaxHeight)
            {
/*               dRateH = (double)iMaxHeight / (double)pimage->width();
            }
         }

         double dRate = minimum(dRateW, dRateH);

/*         ::image::image_pointer pimage;

/*         pimage = create_image({(int)(pimage->width() * dRate),  (int)(pimage->height() * dRate)});

/*         pimage->stretch_image(pimage);

/*         ::image::save_options saveoptions;

/*         savepimage->m_eformat = pimage::e_format_jpeg;
/*         savepimage->m_iQuality = 50;

         outheader("content-type") = "image/jpeg";


/*         pimage->save_to_file(&response().file(), saveoptions);


      }

   }






} // namespace user_service

