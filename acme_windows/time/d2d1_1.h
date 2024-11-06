#pragma once

#undef ___new

#include <D2d1_1.h>

#define ___new ACME_NEW

inline void copy(D2D1_RECT_F * prectTarget, const ::int_rectangle * prectSource) { ::copy_rect(prectTarget, prectSource); }
inline void copy(D2D1_RECT_U * prectTarget, const ::int_rectangle * prectSource) { ::copy_rect(prectTarget, prectSource); }
//inline void copy(D2D1_RECT_L * prectTarget, const ::int_rectangle * prectSource) { ::copy_rect(prectTarget, prectSource); }


inline void copy(D2D1_RECT_F * prectTarget, const ::double_rectangle * prectSource) { ::copy_rect(prectTarget, prectSource); }
inline void copy(D2D1_RECT_U * prectTarget, const ::double_rectangle * prectSource) { ::copy_rect(prectTarget, prectSource); }
//inline void copy(D2D1_RECT_L * prectTarget, const ::double_rectangle * prectSource) { ::copy_rect(prectTarget, prectSource); }



inline void copy(::int_rectangle * prectTarget, const D2D1_RECT_F * prectSource) { ::copy_rect(prectTarget, prectSource); }
inline void copy(::int_rectangle * prectTarget, const D2D1_RECT_U * prectSource) { ::copy_rect(prectTarget, prectSource); }
//inline void copy(::int_rectangle * prectTarget, const D2D1_RECT_L * prectSource) { ::copy_rect(prectTarget, prectSource); }


inline void copy(::double_rectangle * prectTarget, const D2D1_RECT_F * prectSource) { ::copy_rect(prectTarget, prectSource); }
inline void copy(::double_rectangle * prectTarget, const D2D1_RECT_U * prectSource) { ::copy_rect(prectTarget, prectSource); }
//inline void copy(::double_rectangle * prectTarget, const D2D1_RECT_L * prectSource) { ::copy_rect(prectTarget, prectSource); }



