#pragma once


#undef ___new
#ifdef WINDOWS_DESKTOP
#include <gdiplus.h>
#endif
#define ___new ACME_NEW
#ifdef WINDOWS
#include <D2d1.h>
#endif

rectangle_type(const Gdiplus::Rect & t) noexcept { copy(this, &t); }
rectangle_type(const Gdiplus::RectF & t) noexcept { copy(this, &t); }
rectangle_type(const Gdiplus::Rect * p) noexcept { copy(this, p); }
rectangle_type(const Gdiplus::RectF * p) noexcept { copy(this, p); }


inline auto left(const Gdiplus::Rect * prectangle) { return prectangle->X; }
inline auto top(const Gdiplus::Rect * prectangle) { return prectangle->Y; }
inline auto left(const Gdiplus::RectF * prectangle) { return prectangle->X; }
inline auto top(const Gdiplus::RectF * prectangle) { return prectangle->Y; }

inline auto width(const Gdiplus::Rect * prectangle) { return prectangle->Width; }
inline auto height(const Gdiplus::Rect * prectangle) { return prectangle->Height; }
inline auto width(const Gdiplus::RectF * prectangle) { return prectangle->Width; }
inline auto height(const Gdiplus::RectF * prectangle) { return prectangle->Height; }


template <  typename L, typename T, typename W, typename H >
inline auto _001SetRectDim(Gdiplus::Rect * p, L l, T t, W w, H h) { return set_XYWH_dim(p, l, t, w, h); }
template <  typename L, typename T, typename W, typename H >
inline auto _001SetRectDim(Gdiplus::RectF * p, L l, T t, W w, H h) { return set_XYWH_dim(p, l, t, w, h); }


inline auto copy(Gdiplus::Rect * prectTarget, const ::int_rectangle * prectSource) { return ::_001CopyRect(prectTarget, prectSource); }
inline auto copy(Gdiplus::Rect * prectTarget, const ::double_rectangle * prectSource) { return _001CopyRect(prectTarget, prectSource); }
inline auto copy(Gdiplus::RectF * prectTarget, const ::int_rectangle * prectSource) { return ::_001CopyRect(prectTarget, prectSource); }
inline auto copy(Gdiplus::RectF * prectTarget, const ::double_rectangle * prectSource) { return ::_001CopyRect(prectTarget, prectSource); }


inline void copy(Gdiplus::Point * ppoint1, const ::double_point * ppoint2)
{

   ppoint1->X = (int)ppoint2->x;
   ppoint1->Y = (int)ppoint2->y;

}


inline void copy(Gdiplus::Point * ppoint1, const ::int_point * ppoint2)
{

   ppoint1->X = (int)ppoint2->x;
   ppoint1->Y = (int)ppoint2->y;

}


inline void copy(Gdiplus::PointF * ppoint1, const ::double_point * ppoint2)
{

   ppoint1->X = (Gdiplus::REAL)ppoint2->x;
   ppoint1->Y = (Gdiplus::REAL)ppoint2->y;

}






// template < prototype_point POINT >
// void __copy(POINT & p, const Gdiplus::Point & t) noexcept { ::copy_point(&p, &t); }
// template < prototype_point POINT >
// void __copy(POINT * p1, const Gdiplus::Point * p2) noexcept { ::copy_point(p1, p2); }

// template < prototype_point POINT >
// void __copy(POINT & p, const Gdiplus::PointF & t) noexcept { ::copy_point(&p, &t); }
template < prototype_point POINT >
void copy(POINT * p1, const Gdiplus::PointF * p2) noexcept { ::copy_point(p1, p2); }
