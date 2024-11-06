#pragma once

#include "aura/.h"
#include "aura/os/windows/windows_app_console.inl"

#include <stdio.h>
//SPALIB_API string spa_version(string strVersion= "");
//SPALIB_API string spa_title(string strTitle= "");

class app_t:
   public ::aura::platform::application
{
public:

   bool m_bMainRepos;


   app_t()
   {

      //Sleep(15000);
      m_hinstance             = ::GetModuleHandleA(nullptr);
      m_argc = 0;
      LPWSTR* pwa = CommandLineToArgvW(
                    GetCommandLineW(),
                    &m_argc
                    );
      m_argv = ___new char *[m_argc];
      for(::collection::index i = 0; i < m_argc; i++)
      {
         m_argv[i] = ansi_duplicate(string(pwa[i]));
      }

      m_bMainRepos = file_system()->exists("C:\\ca2\\config\\repos\\main.txt");

   };


   virtual ~app_t() {}


   virtual void win_sync_out(string str,string strRepos);


   virtual int run();

   string call(string str);


} ;

void app_t::win_sync_out(string strLocal,string strRepos)
{

   //::earth::time timeNow = ::earth::time::now();

   //string strTimeNow;

   //strTimeNow = datetime().international().get_gmt_date_time(timeNow);

   //::file::path pathRepos = strLocal;

   //pathRepos /= strReposParam;

   //string strRepos = pathRepos;

   //string strAlt = strRepos;

   //strAlt.replace("\\","/");

   //strAlt = "file:///" + strAlt;




   //string strLog;

   //strLog += "syncing Repository " + strRepos + " " + strTimeNow;

   //string str;

   //string_array stra;

   //try
   //{

//     string strUser = file_system()->as_string("C:\\sensitive\\sensitive\\seed\\user.txt");

   //	string strPass = file_system()->as_string("C:\\sensitive\\sensitive\\seed\\pass.txt");

   //	if(m_bMainRepos)
   //	{

   //		strLog += "\r\n";

   //		strLog += "\r\n";

   //		str = call("svnadmin lstxns " + strRepos);

   //		str.trim();

   //		if(str.has_char())
   //		{

   //			strLog += "Found spurious transactions";

   //			strLog += "\r\n";

   //			strLog += "\r\n";

   //			strLog += str;

   //			strLog += "\r\n";

   //			strLog += "\r\n";

   //			stra.add_lines(str);

   //			str = stra.implode(" ");

   //			strLog += "Removing spurious transactions";

   //			str = call("svnadmin rmtxns " + strRepos + " " + str);

   //			strLog += str;

   //			strLog += "\r\n";

   //			strLog += "\r\n";

   //		}

   //		strLog += "Removing locks...\r\n";
   //		strLog += "UNLOCKING! ATTENTION!\r\n";
   //		strLog += "Only one script like this should run at the same time!\r\n";
   //		strLog += call("svn pdel --revprop -r 0 svn:synchronization_object-lock " + strAlt);
   //		strLog += "\r\n";

   //		strLog += "\r\n";

   //		strLog += call("svnsync --non-interactive --synchronization_object-username " + strUser + " --synchronization_object-password " + strPass + " --source-username " + strUser + " --source-password " + strPass + " synchronization_object " + strAlt);

   //		strLog += "\r\n";

   //		strLog += "\r\n";

   //		string strUni = unitext("");

   //		const char * textoBunitin = strUni;

   //		char ch0 = *(textoBunitin + 0);

   //		char ch0b = textoBunitin[0];

   //		char ch4 = *(textoBunitin + 4);

   //		char ch4b = textoBunitin[4];

   //	}


   //if(strReposParam == "net" || ::str().begins(strReposParam,"net"))
   //{

   //	strLog += call("svn cleanup C:\\netnodenet\\" + strReposParam);

   //	strLog += "\r\n";

   //	strLog += "\r\n";
   //
   //	strLog += call("svn update --username " + strUser + " --password " + strPass + " C:\\netnodenet\\" + strReposParam);

   //	strLog += "\r\n";

   //	strLog += "\r\n";

   //}



   //}
   //catch(...)
   //{

   //	strLog += "some error occured (exception... cautcht) (2)";

   //}

   //string strFileTime = strTimeNow;

   //strFileTime.replace(":","-");

   //file::path pathLog = pathRepos / "synchronization_object-log" / strFileTime + ".txt";

   //file_system()->put_contents(pathLog,strLog);


   ::system("C:\\bergedge\\hi5\\program\\hstart /NOCONSOLE \"cmd.exe /D /S /c call C:\\sensitive\\sensitive\\ca2\\fontopus\\script\\repossyncitem.bat " + strLocal + " " + strRepos + "\"");

}


//int main()
//{
//
//   if(!defer_aura_init())
//   {
//
//      return -1;
//
//   }
//
//   app_t * psystem = ___new app_t;
//
//   int iReturnCode = ::app_main(psystem, nullptr,nullptr,nullptr,0);
//
//   defer_aura_term();
//
//   return iReturnCode;
//
//}


::aura::application * get_acid_app(::particle * pparticle)
{

   return ___new app_t();

}






int app_t::run()
{
   /*printf("I am the post-commit wizard and oracle!!\n");
   printf("First: Be patient!! Keep calm, take it easy and try to enjoy the ride!!\n");
   printf("Second: If you are patient, you are, let's say, sick or ill!!\n");
   printf("Third: If you are an Angel or great God, you act immediately!!\n");
   printf("Few people are like the last because they are still patient and ill!!\n");
   printf("Straw-man shut up, you just fit words, they do not make sense, at least, I don't want to believe it, even if it is true (EVEN IF IT IS ***TRUE***) I prefer a lie and illusion than another bigbang childhood!!\n");
   */

   //Sleep(25000);

   printf("Number of arguments : %d\n", m_argc);

   for (::collection::index i = 0; i < m_argc; i++)
   {
      printf("m_argv[%d] = \"%s\"\n", i, m_argv[i]);
   }

   string str;

   string_array stra;

   if (m_argc >= 2)
   {

      ::file::path path = m_argv[1];

      string strRepos = path.name();

      if (strRepos.case_insensitive_find("repos2") >= 0)
      {
         m_bMainRepos = false;
      }

      string strUser = file_system()->as_string("C:\\sensitive\\sensitive\\seed\\user.txt");

      string strPass = file_system()->as_string("C:\\sensitive\\sensitive\\seed\\pass.txt");

      if (m_bMainRepos)
      {

         str = file_system()->as_string("C:\\ca2\\config\\repos\\mirror_list.txt");

         stra.add_lines(str);

         for (auto str : stra)
         {
            if (str.has_char())
            {

               ::system("C:\\bergedge\\hi5\\program\\hstart /NOCONSOLE \"svnsync --non-interactive --synchronization_object-username " + strUser + " --synchronization_object-password " + strPass + " --source-username " + strUser + " --source-password " + strPass + " synchronization_object https://" + str + "-repos.ca2.cc:8443/" + strRepos + "\"");
            }
         }

      }

      str = file_system()->as_string("C:\\ca2\\config\\repos\\mirror_list_here.txt");

      stra.erase_all();

      stra.add_lines(str);


      int iCount = 0;

      for (auto str : stra)
      {
         if (str.has_char())
         {
            iCount++;
            ::fork(this, [&]()
            {

               win_sync_out(str, strRepos);

               iCount--;

            });


         }
      }

      while (iCount > 0)
      {
         Sleep(500);
      }

   }

   return 0;
}

string app_t::call(string str)
{

   string strLog;

   try
   {

      DWORD tickTimeout = 840 * 1000; // 14 minutes

      ::process::process_pointer process(e_create);

      process->create_child_process(str, true, nullptr, ::e_priority_highest);
auto tickStart = ::tick::now();

      unsigned int dwExitCode;

      bool bTimeout = false;

      while (true)
      {

         strLog += process->read();

         if (process->has_exited(&dwExitCode))
            break;

         Sleep(100);

         if (tickStart.elapsed() > tickTimeout) // 14 minutes
         {

            bTimeout = true;

            break;

         }

      }

      strLog += process->read();

      if (bTimeout)
      {

         process->kill();

         return "";

      }
   }
   catch (...)
   {

   }

   return strLog;

}

