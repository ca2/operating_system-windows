// Created by camilo on 2026-07-20 20:30 <3ThomasBorregaardSørensen!! Mummi!! Bilbo!!
#pragma once


namespace acme_windows
{


   class unique_handle
   {
   public:

      unique_handle() noexcept = default;

      explicit unique_handle(HANDLE handle) noexcept :
         m_handle(handle)
      {}

      ~unique_handle()
      {

         reset();

      }

      unique_handle(const unique_handle &) = delete;
      unique_handle & operator=(const unique_handle &) = delete;

      unique_handle(unique_handle && other) noexcept :
         m_handle(other.release())
      {}

      unique_handle & operator=(unique_handle && other) noexcept
      {

         if (this != &other)
         {

            reset(other.release());

         }

         return *this;

      }

      [[nodiscard]]
      HANDLE get() const noexcept
      {

         return m_handle;

      }

      [[nodiscard]]
      bool is_valid() const noexcept
      {

         return m_handle != nullptr &&
            m_handle != INVALID_HANDLE_VALUE;

      }

      HANDLE release() noexcept
      {

         HANDLE handle = m_handle;

         m_handle = nullptr;

         return handle;

      }

      void reset(HANDLE handle = nullptr) noexcept
      {

         if (is_valid())
         {

            CloseHandle(m_handle);

         }

         m_handle = handle;

      }


   private:

      HANDLE m_handle = nullptr;

   };



} // namespace acme_windows



