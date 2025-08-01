#include "framework.h"
#include "sal.h"


/*
/////////////////////////////////////////////////////////////////////////////
// Helper functions

static long CLASS_DECL_DRAW2D_GDI _::windows_definition::MultMultDivDiv(
   int factor, int num1, int num2,
   int den1, int den2)
{
#ifdef _WINDOWS_DEFINITION_PORTABLE
   // make sure that (num1 * num2) does not overflow 31-bits.
   long temp = num1 < 0 ? -num1 : num1;
   for (int nBitsResult = 0; temp != 0; nBitsResult++)
      temp >>= 1;
   temp = num2 < 0 ? -num2 : num2;
   for (; temp != 0; nBitsResult++)
      temp >>= 1;
   if (nBitsResult > 31)
   {
      num1 >>= nBitsResult - 31;
      num2 >>= nBitsResult - 31;
   }

   // make sure that (den1 * den2) does not overflow 31-bits
   temp = den1 < 0 ? -den1 : den1;
   for (nBitsResult = 0; temp != 0; nBitsResult++)
      temp >>= 1;
   temp = den2 < 0 ? -den2 : den2;
   for (; temp != 0; nBitsResult++)
      temp >>= 1;
   if (nBitsResult > 31)
   {
      den1 >>= nBitsResult - 31;
      den2 >>= nBitsResult - 31;
   }

   long numerator = (long)num1 * (long)num2;   // no overflow
   long denominator = (long)den1 * (long)den2; // no overflow
#else
   __int64 numerator = (__int64)num1 * (__int64)num2;   // no overflow
   __int64 denominator = (__int64)den1 * (__int64)den2; // no overflow
   __int64 temp;
#endif

   temp = numerator < 0 ? -numerator : numerator;
   int nBitsInNum;
   for (nBitsInNum = 0; temp != 0; nBitsInNum++)
      temp >>= 1;

   temp = factor < 0 ? -factor : factor;
   int nBitsInFactor;
   for (nBitsInFactor = 0; temp != 0; nBitsInFactor++)
      temp >>= 1;

   nBitsInNum += nBitsInFactor;

   //
   // normalizing the denominator to positive results in an easier
   // determination of whether there is overflow
   //
   if (denominator < 0)
   {
      denominator = -denominator;
      numerator = -numerator;
   }

   // get the product of factor * numerator representable in a long/__int64
   // while distributing loss of presision across all three numerator terms
   // Adjust denominator as well
   //
   while (nBitsInNum-- > 31)
   {
      numerator >>= 1;
      denominator >>= 1;
      if (nBitsInNum-- <= 31)
         break;
      numerator >>= 1;
      denominator >>= 1;
      if (nBitsInNum-- <= 31)
         break;
      factor >>= 1;
      denominator >>= 1;
   }
   numerator *= factor;

   if (denominator == 0)
      return numerator < 0 ? LONG_MIN : LONG_MAX;

   return (long) ((numerator + denominator/2) / denominator);
}

/////////////////////////////////////////////////////////////////////////////
// Print Preview DC (preview_dc)

preview_dc::preview_dc()
{
   // Initial scale factor and top-left offset
   m_nScaleNum = m_nScaleDen = 1;
   m_sizeTopLeft.cx() = m_sizeTopLeft.cy() = 8;
   m_hFont = m_hPrinterFont = nullptr;
}

void preview_dc::SetOutputDC(HDC hDC)
{
   ASSERT(hDC != nullptr);
   m_nSaveDCIndex = ::SaveDC(hDC); // restore in ReleaseOutputDC()
   ::draw2d::graphics_pointer::SetOutputDC(hDC);

   if (get_handle2() != nullptr)
   {
      MirrorMappingMode(false);

      if (m_hFont)
         ::SelectObject(get_os_data(), m_hFont);
      else
         MirrorFont();
      MirrorAttributes();
   }
}

void preview_dc::ReleaseOutputDC()
{
   ASSERT(get_os_data() != nullptr);
   ::RestoreDC(get_os_data(), m_nSaveDCIndex); // Saved in SetOutputDC()
   ::draw2d::graphics_pointer::ReleaseOutputDC();
}

void preview_dc::SetAttribDC(HDC hDC)
{
   ASSERT(hDC != nullptr);
   ::draw2d::graphics_pointer::SetAttribDC(hDC);

   MirrorMappingMode(true);
   MirrorFont();
   MirrorAttributes();
}

preview_dc::~preview_dc()
{
   ASSERT(get_os_data() == nullptr);      // Should not have a screen DC at this time
   ::windows_definition::DeleteObject((HGDIOBJ*)&m_hFont);
}

void preview_dc::SetScaleRatio(int nNumerator, int nDenominator)
{
   m_nScaleNum = nNumerator;
   m_nScaleDen = nDenominator;
   if (get_handle2() != nullptr)
   {
      MirrorMappingMode(true);
      MirrorFont();
   }
}

 support
#ifdef _DEBUG
void preview_dc::assert_ok() const
{
   ::draw2d::graphics_pointer::assert_ok();
}


void preview_dc::dump(dump_context & dumpcontext) const
{
   ::draw2d::graphics_pointer::dump(dumpcontext);

   dumpcontext << "Scale Factor: " << m_nScaleNum << "/" << m_nScaleDen;
   dumpcontext << "\n";
}
#endif

int preview_dc::SaveDC()
{
   ASSERT(get_handle2() != nullptr);
   int nAttribIndex = ::SaveDC(get_handle2());
   if (get_os_data() != nullptr)
   {
      // erase font from object
      ::SelectObject(get_os_data(), GetStockObject(SYSTEM_FONT));
      m_nSaveDCDelta = ::SaveDC(get_os_data()) - nAttribIndex;
      // Select font back in after save
      ::SelectObject(get_os_data(), m_hFont);
   }
   else
   {
      m_nSaveDCDelta = 0x7fff;        // impossibly high value
   }
   return nAttribIndex;
}

bool preview_dc::RestoreDC(int nSavedDC)
{
   ASSERT(get_handle2() != nullptr);
   bool bSuccess = ::RestoreDC(get_handle2(), nSavedDC);
   if (bSuccess)
   {
      if (m_nSaveDCDelta != 0x7fff)
      {
         ASSERT(get_os_data() != nullptr);      // erased Output DC after save

         if (nSavedDC != -1)
            nSavedDC += m_nSaveDCDelta;
         bSuccess = ::RestoreDC(get_os_data(), nSavedDC);
         MirrorFont();               // mirror the font
      }
      else
      {
         ASSERT(get_os_data() == nullptr);      // Added the Output DC after save
      }
   }
   return bSuccess;
}

void preview_dc::MirrorAttributes()
{
   ASSERT(get_handle2() != nullptr);

   if (get_os_data() != nullptr)
   {
      // extract and re-set Pen and Brush
      HGDIOBJ hTemp = ::SelectObject(get_handle2(), ::GetStockObject(BLACK_PEN));
      ::SelectObject(get_handle2(), hTemp);
      ::SelectObject(get_os_data(), hTemp);
      hTemp = ::SelectObject(get_handle2(), ::GetStockObject(BLACK_BRUSH));
      ::SelectObject(get_handle2(), hTemp);
      ::SelectObject(get_os_data(), hTemp);

      SetROP2(GetROP2());
      SetBkMode(GetBkMode());
      SetTextAlign(GetTextAlign());
      SetPolyFillMode(GetPolyFillMode());
      SetStretchBltMode(GetStretchBltMode());
      SetTextColor(GetNearestColor(GetTextColor()));
      SetBkColor(GetNearestColor(GetBkColor()));
   }
}

::draw2d::object* preview_dc::SelectStockObject(int nIndex)
{
   ASSERT(get_handle2() != nullptr);

   HGDIOBJ hObj = ::GetStockObject(nIndex);

   switch (nIndex)
   {
   case ANSI_FIXED_FONT:
   case ANSI_VAR_FONT:
   case DEVICE_DEFAULT_FONT:
   case OEM_FIXED_FONT:
   case SYSTEM_FONT:
   case SYSTEM_FIXED_FONT:
   case DEFAULT_GUI_FONT:
      // Handle the stock fonts correctly
      {
         ::draw2d::object* pObject = ::draw2d_gdi::object::from_handle(
                     ::SelectObject(get_handle2(), hObj));

         // Don't re-mirror screen font if this is the same font.
         if (m_hPrinterFont == (HFONT) hObj)
            return pObject;

         m_hPrinterFont = (HFONT) hObj;

         ASSERT(m_hPrinterFont != nullptr); // Do not allow infinite recursion

         MirrorFont();
         return pObject;
      }

   default:
      if (get_os_data() != nullptr)
         ::SelectObject(get_os_data(), hObj);
      return ::draw2d_gdi::object::from_handle(::SelectObject(get_handle2(), hObj));
   }
}

void preview_dc::MirrorFont()
{
   if (get_handle2() == nullptr)
      return;         // Can't do anything without Attrib DC

   if (m_hPrinterFont == nullptr)
   {
      SelectStockObject(DEVICE_DEFAULT_FONT); // will recurse
      return;
   }

   if (get_os_data() == nullptr)
      return;         // can't mirror font without a screen DC

   LOGFONTW logFont;
   // Fill the logFont structure with the original info
   ::get_object(m_hPrinterFont, sizeof(LOGFONTW), (LPVOID)&logFont);

   TEXTMETRICW tm;

   GetTextFace(LF_FACESIZE, (LPTSTR)&logFont.lfFaceName[0]);
   GetTextMetrics(&tm);

   // Set real values based on the Printer's text metrics.

   if (tm.tmHeight < 0)
      logFont.lfHeight = tm.tmHeight;
   else
      logFont.lfHeight = -(tm.tmHeight - tm.tmInternalLeading);

   logFont.lfWidth = tm.tmAveCharWidth;
   logFont.lfWeight = tm.tmWeight;
   logFont.lfItalic = tm.tmItalic;
   logFont.lfUnderline = tm.tmUnderlined;
   logFont.lfStrikeOut = tm.tmStruckOut;
   logFont.lfCharSet = tm.tmCharSet;
   logFont.lfPitchAndFamily = tm.tmPitchAndFamily;

   HFONT hNewFont = ::CreateFontIndirect(&logFont);
   ::SelectObject(get_os_data(), hNewFont);

   ::GetTextMetrics(get_os_data(), &tm);

   // Is the displayed font too large?

   int cyDesired = -logFont.lfHeight;
   int cyActual;
   if (tm.tmHeight < 0)
      cyActual = -tm.tmHeight;
   else
      cyActual = tm.tmHeight - tm.tmInternalLeading;

   int_size sizeWinExt;
   VERIFY(::GetWindowExtEx(get_os_data(), &sizeWinExt));
   int_size sizeVpExt;
   VERIFY(::GetViewportExtEx(get_os_data(), &sizeVpExt));

   // Only interested in Extent Magnitudes, not direction
   if (sizeWinExt.cy() < 0)
      sizeWinExt.cy() = -sizeWinExt.cy();
   if (sizeVpExt.cy() < 0)
      sizeVpExt.cy() = -sizeVpExt.cy();

   // Convert to screen device coordinates to eliminate rounding
   // errors as a source of SmallFont aliasing

   cyDesired = MulDiv(cyDesired, sizeVpExt.cy(), sizeWinExt.cy());
   cyActual = MulDiv(cyActual, sizeVpExt.cy(), sizeWinExt.cy());

   ASSERT(cyDesired >= 0 && cyActual >= 0);

   if (cyDesired < cyActual)
   {
      logFont.lfFaceName[0] = 0;      // let the mapper find a good fit

      if ((logFont.lfPitchAndFamily & 0xf0) == FF_DECORATIVE)
         logFont.lfPitchAndFamily = DEFAULT_PITCH | FF_DECORATIVE;
      else
         logFont.lfPitchAndFamily = DEFAULT_PITCH | FF_DONTCARE;

      HFONT hTempFont = ::CreateFontIndirect(&logFont);
      ::SelectObject(get_os_data(), hTempFont);           // Select it in.
      ::DeleteObject(hNewFont);
      hNewFont = hTempFont;
   }

   ::windows_definition::DeleteObject((HGDIOBJ*)&m_hFont);  // delete the old logical font
   m_hFont = hNewFont;         // save the ___new one
}

::write_text::font* preview_dc::SelectObject(::write_text::font* pFont)
{
   if (pFont == nullptr)
      return nullptr;

   ASSERT(get_handle2() != nullptr);
   ASSERT_VALID(pFont);

   ::write_text::font* pOldFont = (::write_text::font*) ::draw2d_gdi::object::from_handle(
            ::SelectObject(get_handle2(), pFont->get_handle()));

   // If same as already selected, don't re-mirror screen font
   if (m_hPrinterFont != pFont->get_handle())
   {
      m_hPrinterFont = (HFONT)pFont->get_handle();
      MirrorFont();
   }

   return pOldFont;
}

/////////////////////////////////////////////////////////////////////////////
// Drawing-Attribute Functions

::color::color preview_dc::SetBkColor(::color::color crColor)
{
   ASSERT(get_handle2() != nullptr);
   if (get_os_data() != nullptr)
      ::SetBkColor(get_os_data(), ::GetNearestColor(get_handle2(), crColor));
   return ::SetBkColor(get_handle2(), crColor);
}

::color::color preview_dc::SetTextColor(::color::color crColor)
{
   ASSERT(get_handle2() != nullptr);
   if (get_os_data() != nullptr)
      ::SetTextColor(get_os_data(), ::GetNearestColor(get_handle2(), crColor));
   return ::SetTextColor(get_handle2(), crColor);
}

int preview_dc::SetMapMode(int nMapMode)
{
   ASSERT(get_handle2() != nullptr);
   int nModeOld = ::SetMapMode(get_handle2(), nMapMode);
   MirrorMappingMode(true);
   return nModeOld;
}

int_point preview_dc::SetViewportOrg(int x, int y)
{
   ASSERT(get_handle2() != nullptr);
   ::int_point pointOrgOld;
   VERIFY(::SetViewportOrgEx(get_handle2(), x, y, &pointOrgOld));
   MirrorViewportOrg();
   return pointOrgOld;
}

int_point preview_dc::OffsetViewportOrg(int nWidth, int nHeight)
{
   ASSERT(get_handle2() != nullptr);
   ::int_point pointOrgOld;
   VERIFY(::OffsetViewportOrgEx(get_handle2(), nWidth, nHeight, &pointOrgOld));
   MirrorViewportOrg();
   return pointOrgOld;
}

int_size preview_dc::SetViewportExt(int x, int y)
{
   ASSERT(get_handle2() != nullptr);
   int_size sizeExtOld;
   VERIFY(::SetViewportExtEx(get_handle2(), x, y, &sizeExtOld));
   MirrorMappingMode(true);
   return sizeExtOld;
}

int_size preview_dc::ScaleViewportExt(int xNum, int xDenom, int yNum, int yDenom)
{
   ASSERT(get_handle2() != nullptr);
   int_size sizeExtOld;
   VERIFY(::ScaleViewportExtEx(get_handle2(), xNum, xDenom,
      yNum, yDenom, &sizeExtOld));
   MirrorMappingMode(true);
   return sizeExtOld;
}

int_size preview_dc::set_window_ext(int x, int y)
{
   ASSERT(get_handle2() != nullptr);
   int_size sizeExtOld;
   VERIFY(::SetWindowExtEx(get_handle2(), x, y, &sizeExtOld));
   MirrorMappingMode(true);
   return sizeExtOld;
}

int_size preview_dc::scale_window_ext(int xNum, int xDenom, int yNum, int yDenom)
{
   ASSERT(get_handle2() != nullptr);
   int_size sizeExtOld;
   VERIFY(::ScaleWindowExtEx(get_handle2(), xNum, xDenom, yNum, yDenom,
      &sizeExtOld));
   MirrorMappingMode(true);
   return sizeExtOld;
}

/////////////////////////////////////////////////////////////////////////////
// Text Functions

// private helpers for text_out functions

static int CLASS_DECL_DRAW2D_GDI _::windows_definition::ComputeNextTab(int x, UINT nTabStops, LPINT lpnTabStops, int nTabOrigin, int nTabWidth)
{
   ENSURE(nTabWidth!=0);
   x -= nTabOrigin;        // normalize position to tab origin
   for (UINT i = 0; i < nTabStops; i++, lpnTabStops++)
   {
      if (*lpnTabStops > x)
        {
         return *lpnTabStops + nTabOrigin;
        }
   }
   return (x / nTabWidth + 1) * nTabWidth + nTabOrigin;
}

// Compute a character delta table for correctly positioning the screen
// font characters where the printer characters will appear on the page
int_size preview_dc::ComputeDeltas(int& x, const ::scoped_string & scopedstrString, UINT &nCount,
   bool bTabbed, UINT nTabStops, LPINT lpnTabStops, int nTabOrigin,
   __out_z LPTSTR lpszOutputString, int* pnDxWidths, int& nRightFixup)
{
   ASSERT_VALID(this);

   TEXTMETRICW tmAttrib;
   TEXTMETRICW tmScreen;
   ::GetTextMetrics(get_handle2(), &tmAttrib);
   ::GetTextMetrics(get_os_data(), &tmScreen);

   int_size sizeExtent;
   ::GetTextExtentPoint32A(get_handle2(), "A", 1, &sizeExtent);

   ::int_point pointCurrent;
   UINT nAlignment = ::GetTextAlign(get_handle2());
   bool bUpdateCP = (nAlignment & TA_UPDATECP) != 0;
   if (bUpdateCP)
   {
      ::GetCurrentPositionEx(get_os_data(), &pointCurrent);
      x = pointCurrent.x();
   }

   const char * lpszCurChar = lpszString;
   const char * lpszStartRun = lpszString;
   int* pnCurDelta = pnDxWidths;
   int nStartRunPos = x;
   int nCurrentPos = x;
   int nStartOffset = 0;

   int nTabWidth = 0;
   if (bTabbed)
   {
      if (nTabStops == 1)
      {
         nTabWidth = lpnTabStops[0];
      }
      else
      {
         // get default int_size of a tab
         nTabWidth = LOWORD(::GetTabbedTextExtentA(get_handle2(),
            "\t", 1, 0, nullptr));
      }
   }

   for (UINT i = 0; i < nCount; i++)
   {
      bool bSpace = ((_TUCHAR)*lpszCurChar == (_TUCHAR)tmAttrib.tmBreakChar);
      if (bSpace || (bTabbed && *lpszCurChar == '\t'))
      {
         // bSpace will be either true (==1) or false (==0).  For spaces
         // we want the space included in the get_text_extent, for tabs we
         // do not want the tab included
         int nRunLength = (int)(lpszCurChar - lpszStartRun) + bSpace;

         int_size sizeExtent;
         ::GetTextExtentPoint32(get_handle2(), lpszStartRun, nRunLength,
            &sizeExtent);
         int nNewPos = nStartRunPos + sizeExtent.cx()
            - tmAttrib.tmOverhang;

         // now, if this is a Tab (!bSpace), compute the next tab stop
         if (!bSpace)
         {
            nNewPos = _::windows_definition::ComputeNextTab(nNewPos, nTabStops, lpnTabStops,
                        nTabOrigin, nTabWidth);
         }

         // add this width to previous width
         if (pnCurDelta == pnDxWidths)
            nStartOffset += nNewPos - nCurrentPos;
         else
            *(pnCurDelta-1) += nNewPos - nCurrentPos;

         nCurrentPos = nNewPos;

         nStartRunPos = nCurrentPos;     // set start of run
         // *lpszCurChar must be SBC: tmBreakChar or '\t'
         lpszStartRun = lpszCurChar + 1;
      }
      else
      {
         // For the non-tabbed or non-tab-character case
         int cxScreen;
         if (_istlead(*lpszCurChar))
         {
            cxScreen = tmScreen.tmAveCharWidth;
            *pnCurDelta = tmAttrib.tmAveCharWidth;
         }
         else
         {
            ::GetCharWidth(get_os_data(), (_TUCHAR)*lpszCurChar,
               (_TUCHAR)*lpszCurChar, &cxScreen);
            if (!::GetCharWidth(get_handle2(), (_TUCHAR)*lpszCurChar,
               (_TUCHAR)*lpszCurChar, pnCurDelta))
            {
               // If printer driver fails the above call, use the average width
               *pnCurDelta = tmAttrib.tmAveCharWidth;
            }
         }
         *pnCurDelta -= tmAttrib.tmOverhang;
         cxScreen -= tmScreen.tmOverhang;
         nCurrentPos += *pnCurDelta;     // update current position

         // Center character in allotted space
         if (pnCurDelta != pnDxWidths)
         {
            int diff = (*pnCurDelta - cxScreen) / 2;
            *pnCurDelta -= diff;
            *(pnCurDelta - 1) += diff;
         }
         *lpszOutputString++ = *lpszCurChar;
         if (_istlead(*lpszCurChar))
         {
            *lpszOutputString++ = *(lpszCurChar+1); // copy trailing unsigned char
            *(pnCurDelta + 1) = *pnCurDelta;        // double wide
            nCurrentPos += *pnCurDelta;
            pnCurDelta++;
            i++;
         }
         pnCurDelta++;
      }
      lpszCurChar = _tcsinc(lpszCurChar);
   }

   nAlignment &= TA_CENTER|TA_RIGHT;
   sizeExtent.cx() = nCurrentPos - x;
   nRightFixup = 0;

   if (nAlignment == TA_LEFT)
      x += nStartOffset;      // Full left side adjustment
   else if (nAlignment == TA_CENTER)
      x += nStartOffset/2;    // Adjust Center by 1/2 left side adjustment
   else if (nAlignment == TA_RIGHT)
      nRightFixup = nStartOffset; // Right adjust needed later if TA_UPDATECP

   if (bUpdateCP)
      ::MoveToEx(get_os_data(), x, pointCurrent.y(), nullptr);

   nCount = (UINT)(pnCurDelta - pnDxWidths);   // number of characters output
   return sizeExtent;
}

bool preview_dc::text_out(int x, int y, const ::scoped_string & scopedstrString, int nCount)
{
   return ExtTextOut(x, y, 0, nullptr, lpszString, nCount, nullptr);
}

bool preview_dc::ExtTextOut(int x, int y, UINT nOptions, const ::int_rectangle & rectangle,
   const char * lpszString, UINT nCount, LPINT lpDxWidths)
{
   ASSERT(get_os_data() != nullptr);
   ASSERT(get_handle2() != nullptr);
   ASSERT(lpszString != nullptr);
   ASSERT(lpDxWidths == nullptr ||
         fx_is_valid_address(lpDxWidths, sizeof(int) * nCount, false));
   ASSERT(fx_is_valid_address(lpszString, nCount, false));

   int* pDeltas = nullptr;
   LPTSTR pOutputString = nullptr;
   int nRightFixup = 0;

   if (lpDxWidths == nullptr)
   {
      if (nCount == 0)    // Do nothing
         return true;

      try
      {
         pDeltas = ___new int[nCount];
         pOutputString = ___new char[nCount];
      }
      catch(::exception::base * pe)
      {
         delete[] pDeltas;  // in case it was allocated
         // Note: DELETE_EXCEPTION(e) not required
         return false;   // Could not allocate buffer, cannot display
      }
      

      ComputeDeltas(x, (LPTSTR)lpszString, nCount, false, 0, nullptr, 0,
                              pOutputString, pDeltas, nRightFixup);

      lpDxWidths = pDeltas;
      lpszString = pOutputString;
   }

   bool bSuccess = ::ExtTextOut(get_os_data(), x, y, nOptions, rectangle, lpszString,
                                          nCount, lpDxWidths);
   if (nRightFixup != 0 && bSuccess && (GetTextAlign() & TA_UPDATECP))
   {
      ::int_point point;
      ::GetCurrentPositionEx(get_os_data(), &point);
      MoveTo(point.x() - nRightFixup, point.y());
   }
   delete[] pDeltas;
   delete[] pOutputString;

   return bSuccess;
}

int_size preview_dc::TabbedTextOut(int x, int y, const ::scoped_string & scopedstrString, int nCount,
   int nTabPositions, LPINT lpnTabStopPositions, int nTabOrigin)
{
   ASSERT(get_handle2() != nullptr);
   ASSERT(get_os_data() != nullptr);
   ASSERT(lpszString != nullptr);
   ASSERT(fx_is_valid_address(lpszString, nCount, false));
   ASSERT(lpnTabStopPositions == nullptr ||
         fx_is_valid_address(lpnTabStopPositions, sizeof(int) * nTabPositions,
            false));

   if (nCount <= 0)
      return (unsigned int) 0;         // nCount is zero, there is nothing to print

   int* pDeltas = nullptr;
   LPTSTR pOutputString = nullptr;
   int nRightFixup;

   try
   {
      pDeltas = ___new int[nCount];
      pOutputString = ___new char[nCount];
   }
   catch(::exception::base * pe)
   {
      delete[] pDeltas;
      // Note: DELETE_EXCEPTION(e) not required
      return (unsigned int) 0;           // signify error
   }
   

   UINT uCount = nCount;
   int_size sizeFinalExtent = ComputeDeltas(x, lpszString, uCount, true,
                     nTabPositions, lpnTabStopPositions, nTabOrigin,
                     pOutputString, pDeltas, nRightFixup);

   bool bSuccess = ExtTextOut(x, y, 0, nullptr, pOutputString, uCount, pDeltas);

   delete[] pDeltas;
   delete[] pOutputString;

   if (bSuccess && (GetTextAlign() & TA_UPDATECP))
   {
      ::int_point point;
      ::GetCurrentPositionEx(get_os_data(), &point);
      MoveTo(point.x() - nRightFixup, point.y());
   }

   return sizeFinalExtent;
}

// This one is too complicated to do character-by-character output positioning
// All we really need to do here is mirror the current position
int preview_dc::draw_text(const ::scoped_string & scopedstrString, int nCount, RECT * prectangle,
   UINT nFormat)
{
   ASSERT(get_handle2() != nullptr);
   ASSERT(get_os_data() != nullptr);
   ASSERT(lpszString != nullptr);
   ASSERT(rectangle != nullptr);
   ASSERT(fx_is_valid_address(rectangle, sizeof(RECT)));
   ASSERT(nCount == -1 ?
      ::windows_definition::IsValidString(lpszString) :
      fx_is_valid_address(lpszString, nCount, false));

   int retVal = ::draw_text(get_os_data(), lpszString, nCount, rectangle, nFormat);

   int_point pos;
   ::GetCurrentPositionEx(get_os_data(), &pos);
   ::MoveToEx(get_handle2(), pos.x(), pos.y(), nullptr);
   return retVal;
}

int preview_dc::draw_text_ex(__in_ecount(nCount) LPTSTR lpszString, int nCount, RECT * prectangle,
   UINT nFormat, LPDRAWTEXTPARAMS lpDTParams)
{
   ASSERT(get_handle2() != nullptr);
   ASSERT(get_os_data() != nullptr);
   ASSERT(lpszString != nullptr);
   ASSERT(rectangle != nullptr);
   ASSERT(fx_is_valid_address(rectangle, sizeof(RECT)));
   ASSERT(nCount == -1 ?
      ::windows_definition::IsValidString(lpszString) :
      fx_is_valid_address(lpszString, nCount, false));

   int retVal = ::draw_text_ex(get_os_data(), lpszString, nCount, rectangle, nFormat, lpDTParams);

   int_point pos;
   ::GetCurrentPositionEx(get_os_data(), &pos);
   ::MoveToEx(get_handle2(), pos.x(), pos.y(), nullptr);
   return retVal;
}

bool preview_dc::GrayString(::draw2d::brush*,
            bool (CALLBACK *)(HDC, LPARAM, int),
               LPARAM lpData, int nCount, int x, int y, int, int)
{
   information(::radix::trace::category_AppMsg, 0, "text_out() substituted for GrayString() in Print Preview.\n");
   return text_out(x, y, (const ::string &)lpData, nCount);
}

int preview_dc::Escape(int nEscape, int nCount, const ::scoped_string & scopedstrInData, void * lpOutData)
{
   // The tact here is to NOT allow any of the document control escapes
   // to be passed through.  Elimination of StartDoc and EndDoc should
   // eliminate anything actually going to the printer.  Also anything
   // that actually draws something will be filtered.

   ASSERT(get_handle2() != nullptr);

   switch (nEscape)
   {
   case NEXTBAND:
   case SETCOLORTABLE:
   case GETCOLORTABLE:
   case FLUSHOUTPUT:
   case DRAFTMODE:
   case QUERYESCSUPPORT:
   case GETPHYSPAGESIZE:
   case GETPRINTINGOFFSET:
   case GETSCALINGFACTOR:
   case GETPENWIDTH:
   case SETCOPYCOUNT:
   case SELECTPAPERSOURCE:
   case GETTECHNOLOGY:
   case SETLINECAP:
   case SETLINEJOIN:
   case SETMITERLIMIT:
   case BANDINFO:
   case GETVECTORPENSIZE:
   case GETVECTORBRUSHSIZE:
   case ENABLEDUPLEX:
   case GETSETPAPERBINS:
   case GETSETPRINTORIENT:
   case ENUMPAPERBINS:
   case SETDIBSCALING:
   case ENUMPAPERMETRICS:
   case GETSETPAPERMETRICS:
   case GETEXTENDEDTEXTMETRICWS:
   case GETEXTENTTABLE:
   case GETPAIRKERNTABLE:
   case GETTRACKKERNTABLE:
   case ENABLERELATIVEWIDTHS:
   case ENABLEPAIRKERNING:
   case SETKERNTRACK:
   case SETALLJUSTVALUES:
   case SETCHARSET:
   case SET_BACKGROUND_COLOR:
   case SET_SCREEN_ANGLE:
   case SET_SPREAD:
      return ::Escape(get_handle2(), nEscape, nCount, lpszInData, lpOutData);

   default:
      return 0;
   }
}

void preview_dc::MirrorMappingMode(bool bCompute)
{
   ASSERT(get_handle2() != nullptr);
   if (bCompute)
   {
      //
      // The following formula is used to compute the screen's viewport extent
      // From the printer and screen information and the Printer's Viewport
      // Extents.  (Note:  This formula is used twice, once for horizontal
      // and once for vertical)
      //
      // It is assumed that the Window Extents are maintained as equal.
      //
      //                  m * LogPixPerInch(Screen) * VpExt(Printer)
      // VpExt(Screen) = -------------------------------------------------
      //                          n * LogPixPerInch(Printer)
      //
      // Where m/n is the scaling factor.  (m/n > 1 is expansion)
      //

      VERIFY(::GetViewportExtEx(get_handle2(), &m_sizeVpExt));
      VERIFY(::GetWindowExtEx(get_handle2(), &m_sizeWinExt));

      while (m_sizeWinExt.cx() > -0x4000 && m_sizeWinExt.cx() < 0x4000 &&
            m_sizeVpExt.cx()  > -0x4000 && m_sizeVpExt.cx()  < 0x4000)
      {
         m_sizeWinExt.cx() <<= 1;
         m_sizeVpExt.cx()  <<= 1;
      }

      while (m_sizeWinExt.cy() > -0x4000 && m_sizeWinExt.cy() < 0x4000 &&
            m_sizeVpExt.cy()  > -0x4000 && m_sizeVpExt.cy()  < 0x4000)
      {
         m_sizeWinExt.cy() <<= 1;
         m_sizeVpExt.cy()  <<= 1;
      }

      long lTempExt = _::windows_definition::MultMultDivDiv(m_sizeVpExt.cx(),
         m_nScaleNum, ::windows_definition::Data.cxPixelsPerInch,
         m_nScaleDen, ::GetDeviceCaps(get_handle2(), LOGPIXELSX));

      ASSERT(m_sizeWinExt.cx() != 0);
      m_sizeVpExt.cx() = (int)lTempExt;

      lTempExt = _::windows_definition::MultMultDivDiv(m_sizeVpExt.cy(),
         m_nScaleNum, ::windows_definition::Data.cyPixelsPerInch,
         m_nScaleDen, ::GetDeviceCaps(get_handle2(), LOGPIXELSY));

      ASSERT(m_sizeWinExt.cy() != 0);
      m_sizeVpExt.cy() = (int)lTempExt;
   }

   if (get_os_data() != nullptr)
   {
      ::SetMapMode(get_os_data(), MM_ANISOTROPIC);
      ::SetWindowExtEx(get_os_data(), m_sizeWinExt.cx(), m_sizeWinExt.cy(), nullptr);
      ::SetViewportExtEx(get_os_data(), m_sizeVpExt.cx(), m_sizeVpExt.cy(), nullptr);

      // Now that the Logical Units are synchronized, we can set the Viewport Org
      MirrorViewportOrg();
   }
}

void preview_dc::MirrorViewportOrg()
{
   if (get_handle2() == nullptr || get_os_data() == nullptr)
      return;

   ::int_point pointVpOrg;
   VERIFY(::GetViewportOrgEx(get_handle2(), &pointVpOrg));
   PrinterDPtoScreenDP(&pointVpOrg);
   pointVpOrg += m_sizeTopLeft;
   ::SetViewportOrgEx(get_os_data(), pointVpOrg.x(), pointVpOrg.y(), nullptr);

   ::int_point pointWinOrg;
   VERIFY(::GetWindowOrgEx(get_handle2(), &pointWinOrg));
   ::SetWindowOrgEx(get_os_data(), pointWinOrg.x(), pointWinOrg.y(), nullptr);
}

void preview_dc::SetTopLeftOffset(const ::int_size & sizeTopLeft)
{
   ASSERT(get_handle2() != nullptr);
   m_sizeTopLeft = sizeTopLeft;
   MirrorViewportOrg();
}

void preview_dc::ClipToPage()
{
   ASSERT(get_handle2() != nullptr);
   ASSERT(get_os_data() != nullptr);
   // create a int_rectangle in Screen Device coordinates that is one pixel larger
   // on all sides than the actual page.  This is to hide the fact that
   // the printer to screen mapping mode is approximate and may result
   // in rounding error.

   ::int_point point(::GetDeviceCaps(get_handle2(), HORZRES),
            ::GetDeviceCaps(get_handle2(), VERTRES));
   PrinterDPtoScreenDP(&point);

   // Set the screen dumpcontext <<to MM_TEXT and no WindowOrg for the interesection

   ::SetMapMode(get_os_data(), MM_TEXT);
   ::SetWindowOrgEx(get_os_data(), 0, 0, nullptr);
   ::SetViewportOrgEx(get_os_data(), m_sizeTopLeft.cx(), m_sizeTopLeft.cy(), nullptr);
   ::IntersectClipRect(get_os_data(), -1, -1, point.x() + 2, point.y() + 2);

   // Resynchronize the mapping mode
   MirrorMappingMode(false);
}

// these conversion functions can be used without an attached screen DC

void preview_dc::PrinterDPtoScreenDP(LPPOINT lpPoint) const
{
   ASSERT(get_handle2() != nullptr);

   int_size sizePrinterVpExt;
   VERIFY(::GetViewportExtEx(get_handle2(), &sizePrinterVpExt));
   int_size sizePrinterWinExt;
   VERIFY(::GetWindowExtEx(get_handle2(), &sizePrinterWinExt));

   long xScreen = _::windows_definition::MultMultDivDiv(lpPoint->x,
      sizePrinterWinExt.cx(), m_sizeVpExt.cx(),
      sizePrinterVpExt.cx(), m_sizeWinExt.cx());

   lpPoint->x = (int)xScreen;

   long yScreen = _::windows_definition::MultMultDivDiv(lpPoint->y,
      sizePrinterWinExt.cy(), m_sizeVpExt.cy(),
      sizePrinterVpExt.cy(), m_sizeWinExt.cy());

   lpPoint->y = (int)yScreen;
}

////////////////////////////////////////////////////////////////////////////
// ::windows_definition::CreateDC

HDC CLASS_DECL_DRAW2D_GDI ::windows_definition::CreateDC(HGLOBAL hDevNames, HGLOBAL hDevMode)
{
   if (hDevNames == nullptr)
      return nullptr;

   LPDEVNAMES lpDevNames = (LPDEVNAMES)::GlobalLock(hDevNames);
   LPDEVMODE  lpDevMode = (hDevMode != nullptr) ?
                  (LPDEVMODE)::GlobalLock(hDevMode) : nullptr;

   if (lpDevNames == nullptr)
      return nullptr;

   HDC hDC = ::CreateDC((const ::string &)lpDevNames + lpDevNames->wDriverOffset,
                 (const ::string &)lpDevNames + lpDevNames->wDeviceOffset,
                 (const ::string &)lpDevNames + lpDevNames->wOutputOffset,
                 lpDevMode);

   ::GlobalUnlock(hDevNames);
   if (hDevMode != nullptr)
      ::GlobalUnlock(hDevMode);
   return hDC;
}


// IMPLEMENT_DYNAMIC(preview_dc, ::draw2d::graphics_pointer)

/////////////////////////////////////////////////////////////////////////////
*/
