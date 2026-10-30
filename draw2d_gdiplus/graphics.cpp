#include "platform.h"
#include <climits>
#include <atomic>
#include <chrono>
#include <mutex>
#include "bitmap.h"
#include "graphics.h"
#include "fps_debug.h"
#include "acme/parallelization/parallelization.h"
#include "pen.h"
#include "brush.h"
#include "font.h"
#include "image.h"
#include "path.h"
#include "region.h"
#include "acme/exception/interface_only.h"
#include "acme/exception/not_implemented.h"
#include "acme/graphics/draw2d/_text_stream.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/platform/scoped_restore.h"
#include "acme/prototype/geometry2d/ellipse.h"
#include "acme/prototype/geometry2d/item.h"
#include "acme/prototype/geometry2d/_text_stream.h"
#include "acme/prototype/mathematics/mathematics.h"
#include "acme/prototype/string/international.h"
#include "acme/windowing/window.h"
#include "aura/graphics/draw2d/clip.h"
#include "aura/graphics/draw2d/domain.h"
#include "aura/graphics/draw2d/draw2d.h"
#include "aura/graphics/graphics/buffer_item.h"
#include "aura/graphics/image/context.h"
#include "aura/graphics/image/drawing.h"
#include "aura/graphics/image/map.h"
#include "aura/platform/system.h"
#include "aura/user/user/interaction.h"
//#include "acme/prototype/geometry2d/_enhanced.h"
//#include "acme/prototype/geometry2d/_collection_enhanced.h"
//#include "acme/prototype/geometry2d/_defer_shape.h"


//#undef ___new


::collection::count g_cForkBlend = 0;


#if FPS_DEBUG
namespace
{

   enum class opaque_copy_candidate_skip_reason : ::u32
   {
      eligible,
      alpha_mode,
      page_unit,
      page_scale,
      page_unit_and_scale,
      draw_options,
      source_rectangle,
      target_size,
      target_placement,
      bitmap_size,
      transform,
      compositing_mode,
      alpha_regions,
      count
   };


   const char * opaque_copy_candidate_skip_reason_name(opaque_copy_candidate_skip_reason reason)
   {

      switch (reason)
      {
      case opaque_copy_candidate_skip_reason::eligible: return "eligible";
      case opaque_copy_candidate_skip_reason::alpha_mode: return "alpha_mode";
      case opaque_copy_candidate_skip_reason::page_unit: return "page_unit";
      case opaque_copy_candidate_skip_reason::page_scale: return "page_scale";
      case opaque_copy_candidate_skip_reason::page_unit_and_scale: return "page_unit_and_scale";
      case opaque_copy_candidate_skip_reason::draw_options: return "draw_options";
      case opaque_copy_candidate_skip_reason::source_rectangle: return "source_rectangle";
      case opaque_copy_candidate_skip_reason::target_size: return "target_size";
      case opaque_copy_candidate_skip_reason::target_placement: return "target_placement";
      case opaque_copy_candidate_skip_reason::bitmap_size: return "bitmap_size";
      case opaque_copy_candidate_skip_reason::transform: return "transform";
      case opaque_copy_candidate_skip_reason::compositing_mode: return "compositing_mode";
      case opaque_copy_candidate_skip_reason::alpha_regions: return "alpha_regions";
      default: return "unknown";
      }

   }


   bool is_dabzo5y_image(const ::image::image * pimage)
   {

      if (!pimage || !pimage->m_pathImageSource.has_character())
         return false;

      ::string strImagePath = pimage->m_pathImageSource;
      return strImagePath.case_insensitive_contains("DABZO5y")
         || strImagePath.case_insensitive_contains("DABZ05y");

   }


   bool should_report_dabzo5y_image_once(const ::image::image * pimage,
      ::std::atomic<const void *> & lastImage)
   {

      if (!is_dabzo5y_image(pimage))
         return false;

      return lastImage.exchange(pimage, ::std::memory_order_relaxed) != pimage;

   }


   struct opaque_copy_diagnostics
   {
      ::std::atomic<::u64> candidate_draws{0};
      ::std::atomic<::u64> eligible_draws{0};
      ::std::atomic<::u64> skipped_draws[(::u32)opaque_copy_candidate_skip_reason::count]{};
      ::std::atomic<::u64> full_attempts{0};
      ::std::atomic<::u64> full_successes{0};
      ::std::atomic<::u64> full_fallbacks{0};
      ::std::atomic<::u64> full_saved_pixels{0};
      ::std::atomic<::u64> full_elapsed_nanoseconds{0};
      ::std::atomic<::u64> mixed_attempts{0};
      ::std::atomic<::u64> mixed_successes{0};
      ::std::atomic<::u64> mixed_fallbacks{0};
      ::std::atomic<::u64> mixed_draw_errors{0};
      ::std::atomic<::u64> mixed_region_draws{0};
      ::std::atomic<::u64> mixed_saved_pixels{0};
      ::std::atomic<::u64> mixed_copy_nanoseconds{0};
      ::std::atomic<::u64> mixed_blend_nanoseconds{0};
      ::std::atomic<::u64> mixed_elapsed_nanoseconds{0};
      ::std::atomic<const void *> last_image{nullptr};
      ::std::atomic<::u32> last_page_unit{0};
      ::std::atomic<float> last_page_scale{1.0f};
      ::std::atomic<::i64> next_report_nanoseconds{0};
   };


   enum class opaque_copy_experiment_phase : int
   {
      not_started,
      warmup,
      optimized,
      alpha_blend,
      complete
   };


   enum class opaque_copy_experiment_kind : int
   {
      fully_opaque,
      mixed_alpha
   };


   struct opaque_copy_experiment_bucket
   {
      ::u64 draws = 0;
      ::u64 draw_errors = 0;
      ::u64 optimized_draws = 0;
      ::u64 fallback_draws = 0;
      ::u64 source_pixels = 0;
      ::u64 target_pixels = 0;
      ::u64 potential_opaque_pixels = 0;
      ::u64 opaque_copy_pixels = 0;
      ::u64 blended_pixels = 0;
      ::u64 elapsed_nanoseconds = 0;
      ::i32 source_width = 0;
      ::i32 source_height = 0;
      ::i32 target_width = 0;
      ::i32 target_height = 0;
      ::i32 target_x = 0;
      ::i32 target_y = 0;
      bool dimensions_set = false;
      bool dimensions_vary = false;
   };


   struct opaque_copy_experiment
   {
      ::parallelization::fast_critical_section mutex;
      bool started = false;
      opaque_copy_experiment_phase phase = opaque_copy_experiment_phase::not_started;
      ::std::chrono::steady_clock::time_point start;
      opaque_copy_experiment_bucket buckets[2][2]{};
   };


   opaque_copy_experiment & get_opaque_copy_experiment()
   {

      static opaque_copy_experiment s_experiment;
      return s_experiment;

   }


   const char * opaque_copy_experiment_phase_name(opaque_copy_experiment_phase phase)
   {

      switch (phase)
      {
      case opaque_copy_experiment_phase::warmup: return "warmup";
      case opaque_copy_experiment_phase::optimized: return "optimized";
      case opaque_copy_experiment_phase::alpha_blend: return "alpha_blend";
      case opaque_copy_experiment_phase::complete: return "complete";
      default: return "not_started";
      }

   }


   void report_opaque_copy_experiment_phase(opaque_copy_experiment & experiment,
      opaque_copy_experiment_phase phase)
   {

      if (phase != opaque_copy_experiment_phase::optimized
         && phase != opaque_copy_experiment_phase::alpha_blend)
         return;

      auto phaseIndex = phase == opaque_copy_experiment_phase::optimized ? 0 : 1;
      for (int kindIndex = 0; kindIndex < 2; ++kindIndex)
      {
         const auto & bucket = experiment.buckets[phaseIndex][kindIndex];
         informationf("FPS opaque experiment: phase=%s kind=%s draws=%llu optimized_draws=%llu fallback_draws=%llu draw_errors=%llu "
            "source_pixels=%llu target_pixels=%llu potential_opaque_pixels=%llu opaque_copy_pixels=%llu blended_pixels=%llu "
            "potential_opaque_pct=%.2f opaque_copy_pct=%.2f blended_pct=%.2f "
            "total_ms=%.2f avg_ms=%.3f source=%dx%d target=%dx%d at=(%d,%d) dimensions_vary=%d",
            opaque_copy_experiment_phase_name(phase), kindIndex == 0 ? "fully_opaque" : "mixed_alpha",
            (unsigned long long)bucket.draws, (unsigned long long)bucket.optimized_draws,
            (unsigned long long)bucket.fallback_draws, (unsigned long long)bucket.draw_errors,
            (unsigned long long)bucket.source_pixels, (unsigned long long)bucket.target_pixels,
            (unsigned long long)bucket.potential_opaque_pixels,
            (unsigned long long)bucket.opaque_copy_pixels, (unsigned long long)bucket.blended_pixels,
            bucket.target_pixels ? 100.0 * bucket.potential_opaque_pixels / bucket.target_pixels : 0.0,
            bucket.target_pixels ? 100.0 * bucket.opaque_copy_pixels / bucket.target_pixels : 0.0,
            bucket.target_pixels ? 100.0 * bucket.blended_pixels / bucket.target_pixels : 0.0,
            (double)bucket.elapsed_nanoseconds / 1000000.0,
            bucket.draws ? (double)bucket.elapsed_nanoseconds / 1000000.0 / bucket.draws : 0.0,
            bucket.source_width, bucket.source_height, bucket.target_width, bucket.target_height,
            bucket.target_x, bucket.target_y, (int)bucket.dimensions_vary);
      }

   }


   opaque_copy_experiment_phase get_opaque_copy_experiment_phase(bool eligibleCandidate)
   {

      auto & experiment = get_opaque_copy_experiment();
      ::std::lock_guard<::parallelization::fast_critical_section> lock(experiment.mutex);
      auto now = ::std::chrono::steady_clock::now();
      if (!experiment.started)
      {
         if (!eligibleCandidate)
            return opaque_copy_experiment_phase::not_started;
         experiment.started = true;
         experiment.start = now;
         experiment.phase = opaque_copy_experiment_phase::warmup;
         informationf("FPS opaque experiment: warmup=5s optimized=20s alpha_blend=20s; timer starts on first eligible image draw");
      }

      auto elapsed = now - experiment.start;
      auto nextPhase = elapsed < ::std::chrono::seconds(5)
         ? opaque_copy_experiment_phase::warmup
         : elapsed < ::std::chrono::seconds(25)
            ? opaque_copy_experiment_phase::optimized
            : elapsed < ::std::chrono::seconds(45)
               ? opaque_copy_experiment_phase::alpha_blend
               : opaque_copy_experiment_phase::complete;
      if (nextPhase != experiment.phase)
      {
         report_opaque_copy_experiment_phase(experiment, experiment.phase);
         experiment.phase = nextPhase;
         informationf("FPS opaque experiment: phase=%s elapsed=%.2fs",
            opaque_copy_experiment_phase_name(nextPhase),
            ::std::chrono::duration<double>(elapsed).count());
      }
      return experiment.phase;

   }


   void note_opaque_copy_experiment_draw(opaque_copy_experiment_phase phase,
      opaque_copy_experiment_kind kind, bool drawSucceeded, ::u64 sourcePixels,
      ::u64 targetPixels, ::u64 potentialOpaquePixels, ::u64 opaqueCopyPixels, ::u64 blendedPixels,
      ::u64 elapsedNanoseconds, ::i32 sourceWidth, ::i32 sourceHeight,
      ::i32 targetWidth, ::i32 targetHeight, ::i32 targetX, ::i32 targetY)
   {

      if (phase != opaque_copy_experiment_phase::optimized
         && phase != opaque_copy_experiment_phase::alpha_blend)
         return;
      auto & experiment = get_opaque_copy_experiment();
      ::std::lock_guard<::parallelization::fast_critical_section> lock(experiment.mutex);
      auto phaseIndex = phase == opaque_copy_experiment_phase::optimized ? 0 : 1;
      auto kindIndex = kind == opaque_copy_experiment_kind::fully_opaque ? 0 : 1;
      auto & bucket = experiment.buckets[phaseIndex][kindIndex];
      ++bucket.draws;
      if (!drawSucceeded) ++bucket.draw_errors;
      if (opaqueCopyPixels) ++bucket.optimized_draws;
      else if (phase == opaque_copy_experiment_phase::optimized) ++bucket.fallback_draws;
      bucket.source_pixels += sourcePixels;
      bucket.target_pixels += targetPixels;
      bucket.potential_opaque_pixels += potentialOpaquePixels;
      bucket.opaque_copy_pixels += opaqueCopyPixels;
      bucket.blended_pixels += blendedPixels;
      bucket.elapsed_nanoseconds += elapsedNanoseconds;
      if (!bucket.dimensions_set)
      {
         bucket.source_width = sourceWidth;
         bucket.source_height = sourceHeight;
         bucket.target_width = targetWidth;
         bucket.target_height = targetHeight;
         bucket.target_x = targetX;
         bucket.target_y = targetY;
         bucket.dimensions_set = true;
      }
      else if (bucket.source_width != sourceWidth || bucket.source_height != sourceHeight
         || bucket.target_width != targetWidth || bucket.target_height != targetHeight)
      {
         bucket.dimensions_vary = true;
      }

   }


   opaque_copy_diagnostics & get_opaque_copy_diagnostics()
   {

      static opaque_copy_diagnostics s_diagnostics;
      return s_diagnostics;

   }


   ::i64 opaque_copy_steady_nanoseconds()
   {

      return ::std::chrono::duration_cast<::std::chrono::nanoseconds>(
         ::std::chrono::steady_clock::now().time_since_epoch()).count();

   }


   void report_opaque_copy_diagnostics_if_due()
   {

      auto & diagnostics = get_opaque_copy_diagnostics();
      auto now = opaque_copy_steady_nanoseconds();
      auto next = diagnostics.next_report_nanoseconds.load(::std::memory_order_relaxed);
      if (next == 0)
      {
         diagnostics.next_report_nanoseconds.compare_exchange_strong(
            next, now + 2000000000, ::std::memory_order_relaxed);
         return;
      }
      if (now < next || !diagnostics.next_report_nanoseconds.compare_exchange_strong(
         next, now + 2000000000, ::std::memory_order_relaxed))
         return;

      auto candidateDraws = diagnostics.candidate_draws.exchange(0, ::std::memory_order_relaxed);
      auto eligibleDraws = diagnostics.eligible_draws.exchange(0, ::std::memory_order_relaxed);
      auto skipAlphaMode = diagnostics.skipped_draws[(::u32)opaque_copy_candidate_skip_reason::alpha_mode].exchange(0, ::std::memory_order_relaxed);
      auto skipPageUnit = diagnostics.skipped_draws[(::u32)opaque_copy_candidate_skip_reason::page_unit].exchange(0, ::std::memory_order_relaxed);
      auto skipPageScale = diagnostics.skipped_draws[(::u32)opaque_copy_candidate_skip_reason::page_scale].exchange(0, ::std::memory_order_relaxed);
      auto skipPageUnitAndScale = diagnostics.skipped_draws[(::u32)opaque_copy_candidate_skip_reason::page_unit_and_scale].exchange(0, ::std::memory_order_relaxed);
      auto skipDrawOptions = diagnostics.skipped_draws[(::u32)opaque_copy_candidate_skip_reason::draw_options].exchange(0, ::std::memory_order_relaxed);
      auto skipSourceRectangle = diagnostics.skipped_draws[(::u32)opaque_copy_candidate_skip_reason::source_rectangle].exchange(0, ::std::memory_order_relaxed);
      auto skipTargetSize = diagnostics.skipped_draws[(::u32)opaque_copy_candidate_skip_reason::target_size].exchange(0, ::std::memory_order_relaxed);
      auto skipTargetPlacement = diagnostics.skipped_draws[(::u32)opaque_copy_candidate_skip_reason::target_placement].exchange(0, ::std::memory_order_relaxed);
      auto skipBitmapSize = diagnostics.skipped_draws[(::u32)opaque_copy_candidate_skip_reason::bitmap_size].exchange(0, ::std::memory_order_relaxed);
      auto skipTransform = diagnostics.skipped_draws[(::u32)opaque_copy_candidate_skip_reason::transform].exchange(0, ::std::memory_order_relaxed);
      auto skipCompositingMode = diagnostics.skipped_draws[(::u32)opaque_copy_candidate_skip_reason::compositing_mode].exchange(0, ::std::memory_order_relaxed);
      auto skipAlphaRegions = diagnostics.skipped_draws[(::u32)opaque_copy_candidate_skip_reason::alpha_regions].exchange(0, ::std::memory_order_relaxed);
      auto fullAttempts = diagnostics.full_attempts.exchange(0, ::std::memory_order_relaxed);
      auto fullSuccesses = diagnostics.full_successes.exchange(0, ::std::memory_order_relaxed);
      auto fullFallbacks = diagnostics.full_fallbacks.exchange(0, ::std::memory_order_relaxed);
      auto fullSavedPixels = diagnostics.full_saved_pixels.exchange(0, ::std::memory_order_relaxed);
      auto fullElapsedNanoseconds = diagnostics.full_elapsed_nanoseconds.exchange(0, ::std::memory_order_relaxed);
      auto mixedAttempts = diagnostics.mixed_attempts.exchange(0, ::std::memory_order_relaxed);
      auto mixedSuccesses = diagnostics.mixed_successes.exchange(0, ::std::memory_order_relaxed);
      auto mixedFallbacks = diagnostics.mixed_fallbacks.exchange(0, ::std::memory_order_relaxed);
      auto mixedDrawErrors = diagnostics.mixed_draw_errors.exchange(0, ::std::memory_order_relaxed);
      auto mixedRegionDraws = diagnostics.mixed_region_draws.exchange(0, ::std::memory_order_relaxed);
      auto mixedSavedPixels = diagnostics.mixed_saved_pixels.exchange(0, ::std::memory_order_relaxed);
      auto mixedCopyNanoseconds = diagnostics.mixed_copy_nanoseconds.exchange(0, ::std::memory_order_relaxed);
      auto mixedBlendNanoseconds = diagnostics.mixed_blend_nanoseconds.exchange(0, ::std::memory_order_relaxed);
      auto mixedElapsedNanoseconds = diagnostics.mixed_elapsed_nanoseconds.exchange(0, ::std::memory_order_relaxed);
      if (candidateDraws || fullAttempts || mixedAttempts)
      {
         informationf("FPS opaque-copy: image=%p candidate_draws=%llu eligible_draws=%llu "
            "skip(alpha_mode=%llu page_unit=%llu page_scale=%llu page_unit_and_scale=%llu draw_options=%llu source_rect=%llu target_size=%llu "
            "target_placement=%llu bitmap_size=%llu transform=%llu compositing_mode=%llu alpha_regions=%llu) "
            "page_unit_value=%u page_scale_value=%.6g "
            "full_attempts=%llu full_success=%llu full_fallback=%llu full_saved_Mpx=%.3f full_total_ms=%.2f full_avg_ms=%.2f "
            "mixed_attempts=%llu mixed_success=%llu mixed_fallback=%llu mixed_draw_errors=%llu "
            "mixed_region_draws=%llu mixed_saved_Mpx=%.3f mixed_copy_ms=%.2f mixed_copy_avg_ms=%.2f "
            "mixed_remainder_ms=%.2f mixed_remainder_avg_ms=%.2f mixed_total_ms=%.2f mixed_avg_ms=%.2f",
            diagnostics.last_image.load(::std::memory_order_relaxed),
            (unsigned long long)candidateDraws, (unsigned long long)eligibleDraws,
            (unsigned long long)skipAlphaMode, (unsigned long long)skipPageUnit,
            (unsigned long long)skipPageScale, (unsigned long long)skipPageUnitAndScale,
            (unsigned long long)skipDrawOptions, (unsigned long long)skipSourceRectangle,
            (unsigned long long)skipTargetSize, (unsigned long long)skipTargetPlacement,
            (unsigned long long)skipBitmapSize, (unsigned long long)skipTransform,
            (unsigned long long)skipCompositingMode, (unsigned long long)skipAlphaRegions,
            diagnostics.last_page_unit.load(::std::memory_order_relaxed),
            diagnostics.last_page_scale.load(::std::memory_order_relaxed),
            (unsigned long long)fullAttempts, (unsigned long long)fullSuccesses,
            (unsigned long long)fullFallbacks, (double)fullSavedPixels / 1000000.0,
            (double)fullElapsedNanoseconds / 1000000.0,
            fullAttempts ? (double)fullElapsedNanoseconds / 1000000.0 / fullAttempts : 0.0,
            (unsigned long long)mixedAttempts, (unsigned long long)mixedSuccesses,
            (unsigned long long)mixedFallbacks, (unsigned long long)mixedDrawErrors,
            (unsigned long long)mixedRegionDraws, (double)mixedSavedPixels / 1000000.0,
            (double)mixedCopyNanoseconds / 1000000.0,
            mixedAttempts ? (double)mixedCopyNanoseconds / 1000000.0 / mixedAttempts : 0.0,
            (double)mixedBlendNanoseconds / 1000000.0,
            mixedAttempts ? (double)mixedBlendNanoseconds / 1000000.0 / mixedAttempts : 0.0,
            (double)mixedElapsedNanoseconds / 1000000.0,
            mixedAttempts ? (double)mixedElapsedNanoseconds / 1000000.0 / mixedAttempts : 0.0);
      }

   }


   void note_opaque_copy_candidate_draw(const void * pimage,
      opaque_copy_candidate_skip_reason skipReason, Gdiplus::Unit pageUnit,
      Gdiplus::REAL pageScale)
   {

      auto & diagnostics = get_opaque_copy_diagnostics();
      report_opaque_copy_diagnostics_if_due();
      diagnostics.last_image.store(pimage, ::std::memory_order_relaxed);
      if (skipReason == opaque_copy_candidate_skip_reason::page_unit
         || skipReason == opaque_copy_candidate_skip_reason::page_scale
         || skipReason == opaque_copy_candidate_skip_reason::page_unit_and_scale)
      {
         diagnostics.last_page_unit.store((::u32)pageUnit, ::std::memory_order_relaxed);
         diagnostics.last_page_scale.store(pageScale, ::std::memory_order_relaxed);
      }
      diagnostics.candidate_draws.fetch_add(1, ::std::memory_order_relaxed);
      if (skipReason == opaque_copy_candidate_skip_reason::eligible)
         diagnostics.eligible_draws.fetch_add(1, ::std::memory_order_relaxed);
      else
         diagnostics.skipped_draws[(::u32)skipReason].fetch_add(1, ::std::memory_order_relaxed);

   }


   void report_dabzo5y_opaque_copy_candidate(const ::image::image * pimage,
      opaque_copy_candidate_skip_reason skipReason, Gdiplus::Unit pageUnit,
      Gdiplus::REAL pageScale, ::f64 xSrc, ::f64 ySrc, ::f64 nSrcWidth,
      ::f64 nSrcHeight, ::f64 xDst, ::f64 yDst, ::f64 nDstWidth,
      ::f64 nDstHeight)
   {

      static ::std::atomic<const void *> s_lastImage{nullptr};
      if (!should_report_dabzo5y_image_once(pimage, s_lastImage))
         return;

      auto strProvenance = pimage->image_debug_provenance();
      informationf("FPS DABZO5y opaque-copy candidate: image=%p reason=%s page_unit=%u page_scale=%.6g "
         "source_size=%dx%d source_rect=(%.2f,%.2f,%.2f,%.2f) target_rect=(%.2f,%.2f,%.2f,%.2f) "
         "cached_fully_opaque=%d provenance=%s",
         pimage, opaque_copy_candidate_skip_reason_name(skipReason), (::u32)pageUnit,
         (double)pageScale, pimage->width(), pimage->height(), xSrc, ySrc,
         nSrcWidth, nSrcHeight, xDst, yDst, nDstWidth, nDstHeight,
         (int)pimage->has_cached_fully_opaque_pixels(), strProvenance.c_str());

   }


   void report_dabzo5y_opaque_stretch(const ::image::image * pimage,
      ::draw2d::enum_image_opacity_policy opacityPolicy, bool bStaticCacheCurrent,
      bool bActiveGraphicsLease, bool bCacheLockAvailable, bool bCacheValid,
      ::image::pixel_usage cachedPixelUsage, ::i32_size sizeCached, ::i32_point pointCached,
      bool bActivePixmapLease,
      const ::image::alpha_statistics & statistics,
      bool bPreserveOpaqueStaticStretch, bool bUseEdgeExtendedSampling,
      Gdiplus::Status wrapStatus, Gdiplus::Status drawStatus,
      Gdiplus::Unit pageUnit, Gdiplus::REAL pageScale,
      ::f64 xSrc, ::f64 ySrc, ::f64 nSrcWidth, ::f64 nSrcHeight,
      ::f64 xDst, ::f64 yDst, ::f64 nDstWidth, ::f64 nDstHeight)
   {

      auto strProvenance = pimage->image_debug_provenance();
      informationf("FPS DABZO5y opaque-stretch: image=%p policy=%u pixel_usage=%u "
         "statistics_current=%d active_graphics_lease=%d statistics_lock_available=%d "
         "cache_valid=%d cached_usage=%u cached_size=%dx%d cached_origin=(%d,%d) current_origin=(%d,%d) "
         "active_pixmap_lease=%d "
         "source_fully_opaque=%d source_alpha=(opaque:%llu translucent:%llu transparent:%llu) "
         "edge_sampling_eligible=%d wrap_status=%d used_edge_sampling=%d draw_status=%d "
         "page_unit=%u page_scale=%.6g source_size=%dx%d source_rect=(%.2f,%.2f,%.2f,%.2f) "
         "target_rect=(%.2f,%.2f,%.2f,%.2f) provenance=%s",
         pimage, (::u32)opacityPolicy, (::u32)pimage->get_pixel_usage(),
         (int)bStaticCacheCurrent, (int)bActiveGraphicsLease,
         (int)bCacheLockAvailable, (int)bCacheValid, (::u32)cachedPixelUsage,
         sizeCached.cx, sizeCached.cy, pointCached.x, pointCached.y,
         pimage->m_point.x, pimage->m_point.y,
         (int)bActivePixmapLease,
         (int)statistics.fully_opaque(),
         (unsigned long long)statistics.opaque,
         (unsigned long long)statistics.translucent,
         (unsigned long long)statistics.transparent,
         (int)bPreserveOpaqueStaticStretch, (int)wrapStatus,
         (int)bUseEdgeExtendedSampling, (int)drawStatus, (::u32)pageUnit,
         (double)pageScale, pimage->width(), pimage->height(), xSrc, ySrc,
         nSrcWidth, nSrcHeight, xDst, yDst, nDstWidth, nDstHeight,
         strProvenance.c_str());

   }


   void note_full_opaque_copy(bool succeeded, ::u64 savedPixels, ::u64 elapsedNanoseconds)
   {

      auto & diagnostics = get_opaque_copy_diagnostics();
      diagnostics.full_attempts.fetch_add(1, ::std::memory_order_relaxed);
      (succeeded ? diagnostics.full_successes : diagnostics.full_fallbacks)
         .fetch_add(1, ::std::memory_order_relaxed);
      diagnostics.full_saved_pixels.fetch_add(savedPixels, ::std::memory_order_relaxed);
      diagnostics.full_elapsed_nanoseconds.fetch_add(elapsedNanoseconds, ::std::memory_order_relaxed);
      report_opaque_copy_diagnostics_if_due();

   }


   void note_mixed_opaque_copy(bool succeeded, bool drawError, ::u64 savedPixels,
      ::u64 regionDraws, ::u64 copyNanoseconds, ::u64 blendNanoseconds,
      ::u64 elapsedNanoseconds)
   {

      auto & diagnostics = get_opaque_copy_diagnostics();
      diagnostics.mixed_attempts.fetch_add(1, ::std::memory_order_relaxed);
      if (succeeded) diagnostics.mixed_successes.fetch_add(1, ::std::memory_order_relaxed);
      else if (drawError) diagnostics.mixed_draw_errors.fetch_add(1, ::std::memory_order_relaxed);
      else diagnostics.mixed_fallbacks.fetch_add(1, ::std::memory_order_relaxed);
      diagnostics.mixed_saved_pixels.fetch_add(savedPixels, ::std::memory_order_relaxed);
      diagnostics.mixed_region_draws.fetch_add(regionDraws, ::std::memory_order_relaxed);
      diagnostics.mixed_copy_nanoseconds.fetch_add(copyNanoseconds, ::std::memory_order_relaxed);
      diagnostics.mixed_blend_nanoseconds.fetch_add(blendNanoseconds, ::std::memory_order_relaxed);
      diagnostics.mixed_elapsed_nanoseconds.fetch_add(elapsedNanoseconds, ::std::memory_order_relaxed);
      report_opaque_copy_diagnostics_if_due();

   }


} // namespace
#endif



/**
*
* Trilinear scale two images, pixels and pixels2, to get a ___new
* interpolated image with ::f64_size width * height.
* pixels is the larger image with ::f64_size w * h.
* pixels2 is the smaller image with ::f64_size w2 * h2.
* width must be w >= width >= w2, width != 0
* height must be h >= height >= h2, height != 0
* Note: in Mip Mapping pixels2 should be half of pixels in dimension.
*
* @lparam pixels Larger image pixels.
* @lparam w Larger image width.
* @lparam h Larger image height.
* @lparam pixels2 Smaller image pixels.
* @lparam w2 Smaller image width.
* @lparam h2 Smaller image height.
* @lparam width New width.
* @lparam height New height.
* @return New array with ::f64_size width * height
*/
void trilinearImageScaling(
   ::color32_t * ret, ::i32 width, ::i32 height, ::i32 scan,
   ::color32_t * pixels, ::i32 w, ::i32 h, // larger image
   ::color32_t * pixels2, ::i32 w2, ::i32 h2, // smaller image
   ::i32 scan2)
{

   ::i32 index, index2;
   ::color32_t A, B, C, D, E, F, G, H;
   ::f32 x, y, x2, y2, w_diff, h_diff, w2_diff, h2_diff, red, green, blue, alpha;
   // find ratio for larger image
   ::f32 w_ratio = ((::f32)(w - 1)) / width;
   ::f32 h_ratio = ((::f32)(h - 1)) / height;
   // find ratio for smaller image
   ::f32 w2_ratio = ((::f32)(w2 - 1)) / width;
   ::f32 h2_ratio = ((::f32)(h2 - 1)) / height;
   // estimate h3 distance
   ::f32 h3_diff = (w - width) / (::f32)(w - w2);
   ::i32 offset = 0;
   ::color32_t * line;
   ::color32_t * line2;
   ::color32_t * lineRet;
   ::i32 wscan = scan / sizeof(::color::color);
   ::i32 wscan2 = scan2 / sizeof(::color::color);
   for (::i32 i = 0; i < height; i++)
   {
      lineRet = ret + wscan * i;
      line = pixels + wscan2 * i;
      line2 = pixels2 + wscan2 * i;
      for (::i32 j = 0; j < width; j++)
      {
         // find w1 and h1 for larger image
         x = w_ratio * j;
         y = h_ratio * i;
         w_diff = x - (::i32)x;
         h_diff = y - (::i32)y;
         index = (::i32)((y)*wscan2 + (x));
         A = line[index];
         B = line[index + 1];
         C = line[index + wscan2];
         D = line[index + wscan2 + 1];
         // find w2 and h2 for smaller image
         x2 = w2_ratio * j;
         y2 = h2_ratio * i;
         w2_diff = x2 - (::i32)x2;
         h2_diff = y2 - (::i32)y2;
         index2 = (::i32)((y2)*wscan2 + (x2));
         E = line2[index2];
         F = line2[index2 + 1];
         G = line2[index2 + wscan2];
         H = line2[index2 + wscan2 + 1];


         // trilinear interpolate blue matter
         blue = (A.u8_blue()) * (1 - w_diff) * (1 - h_diff) * (1 - h3_diff) +
            (B.u8_blue()) * (w_diff) * (1 - h_diff) * (1 - h3_diff) +
            (C.u8_blue()) * (h_diff) * (1 - w_diff) * (1 - h3_diff) +
            (D.u8_blue()) * (w_diff) * (h_diff) * (1 - h3_diff) +
            (E.u8_blue()) * (1 - w2_diff) * (1 - h2_diff) * (h3_diff)+
            (F.u8_blue()) * (w2_diff) * (1 - h2_diff) * (h3_diff)+
            (G.u8_blue()) * (h2_diff) * (1 - w2_diff) * (h3_diff)+
            (H.u8_blue()) * (w2_diff) * (h2_diff) * (h3_diff);

         // trilinear interpolate green matter
         green = ((A.u8_green())) * (1 - w_diff) * (1 - h_diff) * (1 - h3_diff) +
            ((B.u8_green())) * (w_diff) * (1 - h_diff) * (1 - h3_diff) +
            ((C.u8_green())) * (h_diff) * (1 - w_diff) * (1 - h3_diff) +
            ((D.u8_green())) * (w_diff) * (h_diff) * (1 - h3_diff) +
            ((E.u8_green())) * (1 - w2_diff) * (1 - h2_diff) * (h3_diff)+
            ((F.u8_green())) * (w2_diff) * (1 - h2_diff) * (h3_diff)+
            ((G.u8_green())) * (h2_diff) * (1 - w2_diff) * (h3_diff)+
            ((H.u8_green())) * (w2_diff) * (h2_diff) * (h3_diff);

         // trilinear interpolate red matter
         red = ((A.u8_red())) * (1 - w_diff) * (1 - h_diff) * (1 - h3_diff) +
            ((B.u8_red())) * (w_diff) * (1 - h_diff) * (1 - h3_diff) +
            ((C.u8_red())) * (h_diff) * (1 - w_diff) * (1 - h3_diff) +
            ((D.u8_red())) * (w_diff) * (h_diff) * (1 - h3_diff) +
            ((E.u8_red())) * (1 - w2_diff) * (1 - h2_diff) * (h3_diff)+
            ((F.u8_red())) * (w2_diff) * (1 - h2_diff) * (h3_diff)+
            ((G.u8_red())) * (h2_diff) * (1 - w2_diff) * (h3_diff)+
            ((H.u8_red())) * (w2_diff) * (h2_diff) * (h3_diff);

         // trilinear interpolate alpha matter
         alpha = ((A.u8_opacity())) * (1 - w_diff) * (1 - h_diff) * (1 - h3_diff) +
            ((B.u8_opacity())) * (w_diff) * (1 - h_diff) * (1 - h3_diff) +
            ((C.u8_opacity())) * (h_diff) * (1 - w_diff) * (1 - h3_diff) +
            ((D.u8_opacity())) * (w_diff) * (h_diff) * (1 - h3_diff) +
            ((E.u8_opacity())) * (1 - w2_diff) * (1 - h2_diff) * (h3_diff)+
            ((F.u8_opacity())) * (w2_diff) * (1 - h2_diff) * (h3_diff)+
            ((G.u8_opacity())) * (h2_diff) * (1 - w2_diff) * (h3_diff)+
            ((H.u8_opacity())) * (w2_diff) * (h2_diff) * (h3_diff);


         lineRet->m_u32 =
            (::i32)(blue) |
            ((::i32)(green)) << 8 |
            ((::i32)(red)) << 16 |
            ((::i32)(alpha)) << 24;
         lineRet++;
      }
   }

}


namespace draw2d_gdiplus
{


   graphics::graphics()
   {

      //m_pthis = this;
      m_bPrinting = false;
      m_pgdiplusgraphics = nullptr;
      m_hdc = nullptr;
      m_hdcAttach = nullptr;
      m_hdcGraphics = nullptr;
      m_pgdiplusgraphicspath = nullptr;
      m_pgdiplusgraphicspathPaint = nullptr;
      m_ewritetextrendering = ::write_text::e_rendering_none;
      //m_pbitmapMemoryGraphics = nullptr;
      //m_dSizeScaler = 1.0;

   }


   //#ifdef DEBUG
   //
   //
   //   void graphics::assert_ok() const
   //   {
   //
   //      object::assert_ok();
   //
   //   }
   //
   //
   //   void graphics::dump(dump_context & dumpcontext) const
   //   {
   //
   //      object::dump(dumpcontext);
   //
   //      dumpcontext << "m_pgdiplusgraphics = " << (iptr)m_pgdiplusgraphics;
   //      dumpcontext << "\nm_bPrinting = " << m_bPrinting;
   //
   //      dumpcontext << "\n";
   //   }
   //
   //
   //#endif


   graphics::~graphics()
   {

      close_graphics();

   }


   //void graphics::IsPrinting()
   //{

   //   return m_bPrinting;

   //}


   //void graphics::CreateDC(const ::scoped_string & scopedstrDriverName, const ::scoped_string & scopedstrDeviceName, const ::scoped_string & scopedstrOutput, const void * lpInitData)
   //{

   //   return attach_hdc(::CreateDCW(wstring(pszDriverName), wstring(pszDeviceName), wstring(pszOutput), (const DEVMODEW*)lpInitData));

   //}


   //void graphics::CreateIC(const ::scoped_string & scopedstrDriverName, const ::scoped_string & scopedstrDeviceName, const ::scoped_string & scopedstrOutput, const void * lpInitData)
   //{

   //   return attach_hdc(::CreateICW(wstring(pszDriverName), wstring(pszDeviceName), wstring(pszOutput), (const DEVMODEW*) lpInitData));

   //}


   //void graphics::create_compatible_graphics(::draw2d::graphics * pdraw2dgraphics)
   //{

   //   close_graphics();

   //   HDC hdc = nullptr;

   //   if (pdraw2dgraphics == nullptr)
   //   {

   //      hdc = ::CreateCompatibleDC(nullptr);

   //   }
   //   else if (__graphics(pdraw2dgraphics)->m_hdc != nullptr)
   //   {

   //      hdc = ::CreateCompatibleDC(__graphics(pdraw2dgraphics)->m_hdc);

   //   }
   //   else if (__graphics(pdraw2dgraphics)->m_hdcGraphics != nullptr)
   //   {

   //      hdc = ::CreateCompatibleDC(__graphics(pdraw2dgraphics)->m_hdcGraphics);

   //   }
   //   else
   //   {

   //      HDC hdcTemplate = __graphics(pdraw2dgraphics)->get_hdc();

   //      hdc = ::CreateCompatibleDC(hdcTemplate);

   //      __graphics(pdraw2dgraphics)->release_hdc(hdcTemplate);

   //   }

   //   if (hdc == nullptr)
   //   {

   //      throw ::exception(error_failed);

   //   }

   //   m_hdcGraphics = hdc;

   //   m_pgdiplusgraphics = øraw_new Gdiplus::Graphics(m_hdcGraphics);

   //   m_pgdiplusgraphics->SetPageUnit(Gdiplus::UnitPixel);

   //   set_text_rendering_hint(::write_text::e_rendering_system_default);

   //   set_smooth_mode(::draw2d::e_smooth_mode_anti_alias_8x8);

   //   m_osdata[0] = m_pgdiplusgraphics;

   //   //      return true;

   //}


   void graphics::create_for_window_draw2d(::user::interaction * puserinteraction, const ::i32_size & size)
   {

      m_bForWindowDraw2d = true;

      if (::is_null(draw2d_domain()))
      {

         set_draw2d_domain(puserinteraction->draw2d_domain());

      }

      m_sizeTotal2 = size;

      defer_constructø(m_pgraphicsbufferitem->m_pimageBufferItem);

      m_pgraphicsbufferitem->m_pimageBufferItem->update_as_render_target(size, draw2d_domain(),this);

      //constructø(m_pdraw2dbitmapTarget);

      auto & reference_pimageBufferItem = m_pgraphicsbufferitem->m_pimageBufferItem.m_p;

      m_pimageTarget = m_pgraphicsbufferitem->m_pimageBufferItem;

      auto & reference_pimageTarget = m_pimageTarget.m_p;

      //::memory memory;

      //m_pdraw2dbitmapTarget->create_bitmap(this, size, memory, nullptr);
      //
      create_bitmap_graphics(m_pimageTarget->m_pdraw2dbitmap, puserinteraction->draw2d_domain());

   }


   void graphics::create_bitmap_graphics(::draw2d::bitmap * pdraw2dbitmap, ::draw2d::domain * pdraw2ddomain)
   {

      ::cast < ::draw2d_gdiplus::bitmap > pdraw2dgdiplusbitmap = pdraw2dbitmap;

      auto pgdiplusbitmap = pdraw2dgdiplusbitmap->m_pgdiplusbitmap;

      if (::is_null(pgdiplusbitmap))
      {

         throw ::exception(error_wrong_state);

      }

      close_graphics();

      defer_constructø(m_pimageTarget);

      //m_pimageTarget->create_as_descriptor(pdraw2dgdiplusbitmap->size());

      m_pimageTarget->m_pdraw2dbitmap = pdraw2dgdiplusbitmap;

      auto pgdiplusgraphics = new Gdiplus::Graphics(pgdiplusbitmap);

      // GDI+ starts image-backed Graphics in UnitDisplay; draw2d coordinates
      // for this bitmap target are pixel coordinates.
      auto pageUnitStatus = pgdiplusgraphics->SetPageUnit(Gdiplus::UnitPixel);
      if (pageUnitStatus != Gdiplus::Ok)
      {
         warningf("GDI+ failed to set pixel page units for bitmap graphics: status=%d",
            (int)pageUnitStatus);
      }

      m_sizeTotal2 = m_pimageTarget->m_pdraw2dbitmap->size();

      m_pgdiplusgraphics = ::as_pointer(pgdiplusgraphics);

      //m_osdata[0] = pgdiplusgraphics;

      //m_bCreated = true;

      set_ok_flag();

   }


   void graphics::_create_memory_graphics(const ::i32_size & size, ::draw2d::domain *pdraw2ddomain)
   {

      //__UNREFERENCED_PARAMETER(size);
      //__UNREFERENCED_PARAMETER(pacmeuserinteractionAffinity);

      /////create_memory_graphics({}, nullptr); // create_compatible_graphics(nullptr);
      ////if (!create_compatible_graphics(nullptr))
      ////{

      ////   return false;

      ////}

      ////return true;

      auto pbitmapNew = createø<::draw2d::bitmap>();

      pbitmapNew->create_bitmap(this, size, nullptr);

      ::cast < ::draw2d_gdiplus::bitmap > pdraw2dgdiplusbitmapNew = pbitmapNew;

      auto pgdiplusbitmap = pdraw2dgdiplusbitmapNew->m_pgdiplusbitmap;

      if (::is_null(pgdiplusbitmap))
      {

         throw ::exception(error_wrong_state);

      }

      close_graphics();

      //m_pdraw2dbitmap = pdraw2dbitmap;

      defer_constructø(m_pimageTarget);

      m_pimageTarget->create_as_descriptor(pbitmapNew->size(), pdraw2ddomain);

      m_pimageTarget->m_pdraw2dbitmap = pbitmapNew;

      auto pgdiplusgraphics = new Gdiplus::Graphics(pgdiplusbitmap);

      auto pageUnitStatus = pgdiplusgraphics->SetPageUnit(Gdiplus::UnitPixel);
      if (pageUnitStatus != Gdiplus::Ok)
      {
         warningf("GDI+ failed to set pixel page units for memory graphics: status=%d",
            (int)pageUnitStatus);
      }

      m_sizeTotal2 = m_pimageTarget->m_pdraw2dbitmap->size();

      m_pgdiplusgraphics = ::as_pointer(pgdiplusgraphics);

      //m_osdata[0] = pgdiplusgraphics;

      set_ok_flag();

   }


   ::image::image_pointer graphics::get_current_target_image()
   {

      return m_pgraphicsbufferitem->m_pimageBufferItem;

   }


   void graphics::start_layer(bool bFirstLayer, ::user::interaction * puserinteraction)
   {

      set_alpha_mode(::draw2d::e_alpha_mode_set);

      set_text_rendering_hint(::write_text::e_rendering_system_default);

      //defer_constructø(m_pimage);

      ::f64_point pointTarget;
      ::f64_size sizeTarget;

      if (m_pgraphicsbufferitem)
      {

         pointTarget = m_pgraphicsbufferitem->m_bTightRawBuffer
            ? ::f64_point{} : ::f64_point(m_pgraphicsbufferitem->m_pointBufferItem);
         sizeTarget = m_pgraphicsbufferitem->m_sizeBufferItem;

      }
      else
      {

         auto pacmewindowingwindow = puserinteraction->acme_windowing_window();

         pointTarget = pacmewindowingwindow->m_pointWindowBuffer;
         sizeTarget = pacmewindowingwindow->m_sizeWindowBuffer;

      }

      m_pointTarget = pointTarget;
      m_sizeTarget = sizeTarget;
      m_bTargetRectangleModified = true;

      // on_acquire_memory_graphics() updates the target metadata too, so comparing
      // only m_pointTarget cannot tell whether the native GDI+ transform is stale.
      // Apply it at the frame boundary before any primitive is issued.
      defer_on_target_rectangle_update();

      if (m_pgraphicsbufferitem)
      {

         //m_pgraphicsbufferitem->m_pimageBufferItem = m_pimage;

         auto pimage = m_pgraphicsbufferitem->m_pimageBufferItem;

         if (pimage)
         {

            ::f64_point pointf64Image = pimage->m_point;
            ::f64_size sizef64Image = pimage->m_size;
            ::f64_size sizef64ImageRaw = pimage->m_sizeRaw;

            if (pointf64Image != m_pointTarget || sizef64Image != m_sizeTarget || sizef64ImageRaw != m_sizeTotal2)
            {

               pimage->m_point = m_pointTarget;

               pimage->m_size = m_sizeTarget;

               pimage->m_sizeRaw = m_sizeTotal2;

               pimage->m_pdraw2dbitmap = m_pimageTarget->m_pdraw2dbitmap;

               pimage->set_ok_flag();

               pimage->m_estatus = success;

            }

         }

      }

      //::color::color color(0, 0, 0, 0);

      // fill_rectangle(get_size(), color);

      // return true;

   }



   void graphics::begin_draw(bool bExternalRendering, ::user::interaction * puserinteraction,
      const ::i32_rectangle & rectangleFrame, ::image::image * pimageTarget)
   {

      ::draw2d::graphics::begin_draw(bExternalRendering, puserinteraction, rectangleFrame, pimageTarget);

#if FPS_DEBUG
      if (!bExternalRendering && m_pgraphicsbufferitem && m_pgdiplusgraphics
         && (!m_bReportedFrameGeometry || m_rectangleLastReportedFrame != rectangleFrame))
      {

         Gdiplus::Matrix transform;
         Gdiplus::REAL elements[6]{};
         Gdiplus::RectF clip{}, visibleClip{};
         auto transformStatus = m_pgdiplusgraphics->GetTransform(&transform);
         auto elementsStatus = transform.GetElements(elements);
         auto clipStatus = m_pgdiplusgraphics->GetClipBounds(&clip);
         auto visibleClipStatus = m_pgdiplusgraphics->GetVisibleClipBounds(&visibleClip);

         informationf("Restore drawing trace: frame=(%d,%d,%d,%d) target=(%.1f,%.1f,%.1f,%.1f) "
            "raw=(%.1f,%.1f) transform=(%.3f,%.3f,%.3f,%.3f,%.1f,%.1f) "
            "clip=(%.1f,%.1f,%.1f,%.1f) visible_clip=(%.1f,%.1f,%.1f,%.1f) "
            "status=(%d,%d,%d,%d)",
            rectangleFrame.left, rectangleFrame.top, rectangleFrame.right, rectangleFrame.bottom,
            (double)m_pointTarget.x, (double)m_pointTarget.y,
            (double)m_sizeTarget.cx, (double)m_sizeTarget.cy,
            (double)m_sizeTotal2.cx, (double)m_sizeTotal2.cy,
            (double)elements[0], (double)elements[1], (double)elements[2],
            (double)elements[3], (double)elements[4], (double)elements[5],
            (double)clip.X, (double)clip.Y, (double)clip.Width, (double)clip.Height,
            (double)visibleClip.X, (double)visibleClip.Y,
            (double)visibleClip.Width, (double)visibleClip.Height,
            (int)transformStatus, (int)elementsStatus, (int)clipStatus, (int)visibleClipStatus);

         m_rectangleLastReportedFrame = rectangleFrame;
         m_bReportedFrameGeometry = true;

      }
#endif

   }


   ::i32 graphics::GetDeviceCaps(::i32 nIndex)
   {

      throw ::not_implemented();

      return -1;

   }


   ::f64_point graphics::GetBrushOrg()
   {

      throw ::not_implemented();

      return {};

   }


   ::f64_point graphics::SetBrushOrg(::f64 x, ::f64 y)
   {

      //ASSERT(get_handle1() != nullptr);

      //::i32_point point;

      //VERIFY(::SetBrushOrgEx(get_handle1(), x, y, &point));

      //return point;

      throw ::not_implemented();

      return {};

   }


   ::f64_point graphics::SetBrushOrg(const ::f64_point & point)
   {
      //ASSERT(get_handle1() != nullptr);
      //::i32_point
      //VERIFY(::SetBrushOrgEx(get_handle1(), point.x, point.y, &point));
      //return point;

      throw ::interface_only();

      return {};

   }

   //::i32 graphics::EnumObjects(::i32 nObjectType, ::i32 (CALLBACK* pfn)(LPVOID, LPARAM), LPARAM lpData)

   //{
   //   //ASSERT(get_handle2() != nullptr);
   //   //return ::EnumObjects(get_handle2(), nObjectType, (GOBJENUMPROC)pfn, lpData);

   //   throw ::interface_only();

   //   return -1;

   //}


   void graphics::set(::draw2d::bitmap * pdraw2dbitmap)
   {

      if (::is_null(pdraw2dbitmap))
      {

         //return ::error_failed;

         throw ::exception(error_failed);

      }

      if (::is_set(m_pgdiplusgraphics))
      {

         try
         {

            m_pgdiplusgraphics.destroy();

         }
         catch (...)
         {

            information() << "graphics::set(::draw2d::bitmap *) : Failed to delete Gdiplus::Graphics";

         }

      }

      ::cast < ::draw2d_gdiplus::bitmap > pdraw2dgdiplusbitmap = pdraw2dbitmap;

      auto pgdiplusbitmap = pdraw2dgdiplusbitmap->m_pgdiplusbitmap;

      m_pgdiplusgraphics = ::as_pointer(Gdiplus::Graphics::FromImage(pgdiplusbitmap));

      m_pgdiplusgraphics->SetPageUnit(Gdiplus::UnitPixel);

      set_text_rendering_hint(::write_text::e_rendering_system_default);

      set_smooth_mode(::draw2d::e_smooth_mode_anti_alias_8x8);

      m_pdraw2dbitmap = pdraw2dbitmap;

      //m_osdata[0] = m_pgdiplusgraphics;

      //return ::success;

   }


   //::color::color graphics::GetNearestColor(const ::color::color & color)
   //{

   //   //return ::GetNearestColor(get_handle2(), color);
   //   throw ::not_implemented();

   //   return -1;

   //}


   //UINT graphics::RealizePalette()
   //{

   //   return 0;

   //   //throw ::interface_only();

   //   //return ::RealizePalette(get_handle1());
   //}

   //void graphics::UpdateColors()
   //{
   //   //::UpdateColors(get_handle1());

   //}

   //::i32 graphics::GetPolyFillMode()
   //{
   //   //return ::GetPolyFillMode(get_handle2());
   //   throw ::not_implemented();

   //   return -1;

   //}

   //::i32 graphics::GetROP2()
   //{
   //   //return ::GetROP2(get_handle2());
   //   throw ::not_implemented();

   //   return -1;

   //}

   //::i32 graphics::GetStretchBltMode()
   //{
   //   //return ::GetStretchBltMode(get_handle2());
   //   throw ::not_implemented();

   //   return -1;

   //}

   //::i32 graphics::GetMapMode()
   //{
   //   //return ::GetMapMode(get_handle2());
   //   throw ::not_implemented();

   //   return -1;

   //}


   //::i32 graphics::GetGraphicsMode()
   //{

   //   //return ::GetGraphicsMode(get_handle2());
   //   throw ::not_implemented();

   //   return -1;


   //}


   //void graphics::GetWorldTransform(XFORM* pXform)
   //{



   //   m_pgdiplusgraphics->GetTransform(((graphics *)this)->m_pm);

   //   Gdiplus::REAL i32_rectangle[6];

   //   m_pm->GetElements(rectangle);

   //   pXform->eM11 = i32_rectangle[0];
   //   pXform->eM12 = i32_rectangle[1];
   //   pXform->eM21 = i32_rectangle[2];
   //   pXform->eM22 = i32_rectangle[3];

   //   pXform->eDx = i32_rectangle[4];
   //   pXform->eDy = i32_rectangle[5];


   //   return true;

   //}


   ::f64_size graphics::get_extents()
   {

      //::f64_size ::f64_size;

      //::GetViewportExtEx(get_handle2(), &::f64_size);

      //return ::f64_size;
      throw ::not_implemented();

      return {};


   }


   ::f64_point graphics::GetWindowOrg()
   {

      //::i32_point point;

      //::GetWindowOrgEx(get_handle2(), &point);

      //return point;
      throw ::interface_only();

      return {};

   }


   ::f64_size graphics::GetWindowExt()
   {
      //::f64_size ::f64_size;
      //::GetWindowExtEx(get_handle2(), &::f64_size);
      //return ::f64_size;

      throw ::interface_only();

      return {};

   }


   ::f64_size graphics::set_extents(const ::f64_size & size)
   {

      return set_extents(size.cx, size.cy);

   }


   ::f64_point graphics::SetWindowOrg(const ::f64_point & point)
   {

      return SetWindowOrg(point.x, point.y);

   }


   //::f64_size graphics::set_window_ext(const ::f64_size & size)
   //{

   //   return set_window_ext(size.cx, size.cy);

   //}


   //void graphics::DPtoLP(::f64_point * pPoints, ::collection::count nCount)
   //{

   //   //::DPtoLP(get_handle2(), pPoints, (::i32) nCount);

   //}


   // void graphics::DPtoLP(::f64_rectangle * prectangle)
   // {

   // //   //::DPtoLP(get_handle2(), (LPPOINT)prectangle, 2);

   // }

   // void graphics::LPtoDP(::f64_point * pPoints,::collection::count nCount)
   // {
   // 
   //    //::LPtoDP(get_handle2(), pPoints, (::i32)  nCount);

   // }

   // void graphics::LPtoDP(::f64_rectangle * prectangle)

   // {
   // //   //::LPtoDP(get_handle2(), (LPPOINT)prectangle, 2);

   // }


   void graphics::fill_region(::draw2d::region * pregion, ::draw2d::brush * pdraw2dbrush)
   {

      //return ::FillRgn(get_handle1(), (HRGN)pRgn->get_os_data(), (HBRUSH)pBrush->get_os_data()) != false;
      throw ::interface_only();

      //return false;

   }


   void graphics::frame_region(::draw2d::region * pregion, ::draw2d::brush * pdraw2dbrush, ::f64 nWidth, ::f64 nHeight)
   {

      //return ::FrameRgn(get_handle1(), (HRGN)pRgn->get_os_data(), (HBRUSH)pBrush->get_os_data(), nWidth, nHeight) != false;
      throw ::interface_only();

      //return false;

   }


   void graphics::invert_region(::draw2d::region * pregion)
   {

      //ASSERT(get_handle1() != nullptr);

      //return ::InvertRgn(get_handle1(), (HRGN)pRgn->get_os_data()) != false;

      throw ::interface_only();

      //return false;

   }


   void graphics::paint_region(::draw2d::region * pregion)
   {

      //ASSERT(get_handle1() != nullptr);

      //return ::PaintRgn(get_handle1(), (HRGN)pRgn->get_os_data())  != false;

      throw ::interface_only();

      //return false;

   }


   //void graphics::PtVisible(::f64 x, ::f64 y)
   //{

   //   //ASSERT(get_handle1() != nullptr);

   //   //return ::PtVisible(get_handle1(), x, y) != false;

   //   throw ::interface_only();

   //   return false;


   //}

   //void graphics::PtVisible(const ::i32_point & point)
   //{
   //   //ASSERT(get_handle1() != nullptr);   // call virtual
   //   return PtVisible(point.x, point.y);
   //}


   //void graphics::rectVisible(const i32_rectangle &  prectangle)
   //{

   //   //return ::rectVisible(get_handle1(), &prectangle) != false;
   //   throw ::not_implemented();

   //   return false;

   //}


   ::f64_point graphics::current_position()
   {
      //ASSERT(get_handle2() != nullptr);
      //::i32_point point;
      //VERIFY(::GetCurrentPositionEx(get_handle2(), &point));
      //return point;

      throw ::interface_only();

      return {};


   }


   void graphics::polyline(const ::f64_point * ppointsParam, ::collection::count nCount)
   {

      if (nCount <= 0)
      {

         return;

      }

      bool bOk1 = false;

      array < Gdiplus::PointF  > pointa;

      pointa.set_size(nCount);

      try
      {

         for (::i32 i = 0; i < nCount; i++)
         {

            pointa[i].X = (Gdiplus::REAL)ppointsParam[i].x;
            pointa[i].Y = (Gdiplus::REAL)ppointsParam[i].y;

         }

         m_pdraw2dpen->defer_update(this);

         ::cast < ::draw2d_gdiplus::pen>pdraw2dgdipluspen = m_pdraw2dpen;

         auto pgdipluspen = pdraw2dgdipluspen->m_pgdipluspen;

         bOk1 = m_pgdiplusgraphics->DrawLines(pgdipluspen, pointa.data(), (INT)nCount) == Gdiplus::Status::Ok;

      }
      catch (...)
      {
      }


      //return bOk1;

   }


   //void graphics::Arc(::f64 x1,::i32 y1,::f64 x2,::i32 y2,::f64 x3,::i32 y3,::f64 x4,::i32 y4)
   //{

   //   ::f64 centerx    = (x2 + x1) / 2.0;
   //   ::f64 centery    = (y2 + y1) / 2.0;

   //   ::f64 start      = atan2(y3 - centery,x3 - centerx) * 180.0 / π;
   //   ::f64 end        = atan2(y4 - centery,x4 - centerx) * 180.0 / π;
   //   ::f64 sweep      = fabs(end - start);

   //   /*if(GetArcDirection() == AD_COUNTERCLOCKWISE)
   //   {
   //      sweep = -sweep;
   //   }
   //   */

   //   return Arc(x1,y1,x2-x1,y2-y1,start,sweep);

   //}


   void graphics::arc(::f64 x1, ::f64 y1, ::f64 x2, ::f64 y2, ::f64 x3, ::f64 y3, ::f64 x4, ::f64 y4)
   {

      ::f64 centerx = (x2 + x1) / 2.0;
      ::f64 centery = (y2 + y1) / 2.0;

      //::pointer<::aura::system>psystem = system();

      auto pmathematics = ::mathematics::mathematics();

      auto start = radians(atan2(y3 - centery, x3 - centerx));
      auto end = radians(atan2(y4 - centery, x4 - centerx));
      auto sweep = radians(fabs(end - start));

      /*if(GetArcDirection() == AD_COUNTERCLOCKWISE)
      {
         sweep = -sweep;
      }
      */

      return arc(x1, y1, x2 - x1, y2 - y1, start, sweep);

   }


   //void graphics::Arc(::f64 x1,::i32 y1,::i32 w,::i32 h, angle start, angle extends)
   //{

   //   ::Gdiplus::Rect i32_rectangle(x1,y1,w,h);

   //   return m_pgdiplusgraphics->DrawArc(m_pdraw2dpen->get_os_data < Pen * >(this),rectangle,(Gdiplus::REAL) start.degree(),(Gdiplus::REAL) extends.degree()) == Gdiplus::Status::Ok;

   //}


   void graphics::arc(::f64 x1, ::f64 y1, ::f64 w, ::f64 h, ::f64_angle start, ::f64_angle extends)
   {

      ::Gdiplus::RectF rectf((Gdiplus::REAL)x1, (Gdiplus::REAL)y1, (Gdiplus::REAL)w, (Gdiplus::REAL)h);

      m_pdraw2dpen->defer_update(this);

      ::cast < ::draw2d_gdiplus::pen>pdraw2dgdipluspen = m_pdraw2dpen;

      auto pgdipluspen = pdraw2dgdipluspen->m_pgdipluspen;

      m_pgdiplusgraphics->DrawArc(pgdipluspen, rectf, (Gdiplus::REAL)start.degree(), (Gdiplus::REAL)extends.degree());

   }


   void graphics::frame_rectangle(const ::f64_rectangle & rectangle, ::draw2d::brush * pdraw2dbrush)
   {

      return draw_inset_rectangle(rectangle, pdraw2dbrush->m_color, 1.0);

   }


   void graphics::rectangle(const ::f64_rectangle & rectangle)
   {

      //bool bOk1 = 

      fill_rectangle(rectangle);

      //bool bOk2 = 

      draw_rectangle(rectangle);

      //return bOk1 && bOk2;

   }


   void graphics::draw_rectangle(const ::f64_rectangle & rectangleParam, ::draw2d::pen * pdraw2dpen)
   {

      if (m_bTargetRectangleModified)
      {

         defer_on_target_rectangle_update();

      }

      Gdiplus::RectF rectangle;

      copy(rectangle, rectangleParam);

      //if (rectangleParam.height() > 400)
      //{

      //   if (pdraw2dpen->m_color.u8_red() > 180)
      //   {

      //      information() << "draw_rectangle,400+,red180+ " << rectangleParam;

      //   }

      //}

      pdraw2dpen->defer_update(this);

      ::cast < ::draw2d_gdiplus::pen>pdraw2dgdipluspen = pdraw2dpen;

      auto pgdipluspen = pdraw2dgdipluspen->m_pgdipluspen;

      if (::is_null(pdraw2dgdipluspen))
      {

         throw ::exception(error_wrong_state);

      }

      m_pgdiplusgraphics->DrawRectangle(pgdipluspen, rectangle);

   }


   void graphics::invert_rectangle(const ::f64_rectangle & rectangle)
   {

      //::draw2d::save_context savecontext(this);

      //Gdiplus::REAL colorMatrixElements[][] = {
      //   {-1,  0,  0,  0, 0},
      //   {0,  -1,  0,  0, 0},
      //   {0,   0,  -1, 0, 0},
      //   {0,   0,  0,  1, 0},
      //   {1,   1,  1,  0, 1}};

      //ColorMatrix * colorMatrix = ___new ColorMatrix(colorMatrixElements);

      //imageAttributes.SetColorMatrix(
      //   colorMatrix,
      //   ColorMatrixFlag.Default,
      //   ColorAdjustType.Bitmap);

      //e.Graphics.DrawImage(pimage, 10, 10, width, height);

      //e.Graphics.DrawImage(
      //   image,
      //   ___new Rectangle(150, 10, width, height),  // destination i32_rectangle
      //   0, 0,        // upper-left corner of source i32_rectangle
      //   width,       // width of source i32_rectangle
      //   height,      // height of source i32_rectangle
      //   GraphicsUnit.Pixel,
      //   imageAttributes);
      //auto e = m_pgdiplusgraphics->GetCompositingMode();

      //m_pgdiplusgraphics->SetCompositingMode(Gdiplus::CombineModeXor);

      //Gdiplus::SolidBrush b(Color(255, 255, 255, 255));

      //Gdiplus::Rect i32_rectangle;

      //__copy(rectangle, pcrect);


      //m_pgdiplusgraphics->FillRectangle(&b, rectangle);

      //m_pgdiplusgraphics->SetCompositingMode(e);

      //return false;

   }


   void graphics::Chord(const ::f64_rectangle & rectangleParam, const ::f64_point & pointStart, const ::f64_point & pointEnd)
   {

      //ASSERT(get_handle1() != nullptr);
      //return ::Chord(get_handle1(),rectangleParam.left,rectangleParam.top,
      //               rectangleParam.right,rectangleParam.bottom,pointStart.x,pointStart.y,
      //               pointEnd.x, pointEnd.y) != false;
      throw ::not_implemented();

      //return false;

   }


   void graphics::DrawFocusRect(const ::f64_rectangle & rectangleParam)
   {

      //ASSERT(get_handle1() != nullptr);
      //::DrawFocusRect(get_handle1(),&rectangleParam);
      throw ::not_implemented();


   }


   void graphics::clear_current_point()
   {

      //return ::success;

   }


   //void graphics::DrawEllipse(::f64 x1, ::i32 y1, ::f64 x2, ::i32 y2)
   //{

   //   if (m_pgdiplusgraphics == nullptr)
   //   {

   //      return false;

   //   }

   //   Gdiplus::Pen * pdraw2dpen = m_pdraw2dpen->get_os_data < Pen >(this);

   //   if (pdraw2dpen == nullptr)
   //   {

   //      return false;

   //   }

   //   return (m_pgdiplusgraphics->DrawEllipse(pdraw2dpen, x1, y1, x2 - x1, y2 - y1)) == Gdiplus::Status::Ok;

   //}


   //void graphics::DrawEllipse(const i32_rectangle &  rectangleParam)
   //{

   //   if (m_pgdiplusgraphics == nullptr)
   //   {

   //      return false;

   //   }

   //   Gdiplus::Pen * pdraw2dpen = m_pdraw2dpen->get_os_data < Pen >(this);

   //   if (pdraw2dpen == nullptr)
   //   {

   //      return false;

   //   }

   //   return (m_pgdiplusgraphics->DrawEllipse(pdraw2dpen,rectangleParam.left,rectangleParam.top,rectangleParam.right - rectangleParam.left,rectangleParam.bottom - rectangleParam.top)) == Gdiplus::Status::Ok;

   //}



   //void graphics::draw_ellipse(::f64 x1,::f64 y1,::f64 x2,::f64 y2)
   //{

   //   if (m_pgdiplusgraphics == nullptr)
   //   {

   //      return false;

   //   }

   //   Gdiplus::Pen * pdraw2dpen = m_pdraw2dpen->get_os_data < Pen * >(this);

   //   if (pdraw2dpen == nullptr)
   //   {

   //      return false;

   //   }

   //   return (m_pgdiplusgraphics->DrawEllipse(pdraw2dpen,(Gdiplus::REAL)x1,(Gdiplus::REAL)y1,(Gdiplus::REAL)(x2 - x1),(Gdiplus::REAL)(y2 - y1))) == Gdiplus::Status::Ok;

   //}


   void graphics::draw_ellipse(const ::f64_rectangle & rectangleParam)
   {

      if (m_pgdiplusgraphics == nullptr)
      {

         //return false;

         throw ::exception(error_null_pointer);

      }

      if (m_bTargetRectangleModified)
      {

         defer_on_target_rectangle_update();

      }

      m_pdraw2dpen->defer_update(this);

      ::cast < ::draw2d_gdiplus::pen>pdraw2dgdipluspen = m_pdraw2dpen;

      auto pgdipluspen = pdraw2dgdipluspen->m_pgdipluspen;

      if (pgdipluspen == nullptr)
      {

         //return false;

         throw ::exception(error_null_pointer);

      }

      auto x = (Gdiplus::REAL)rectangleParam.left;
      auto y = (Gdiplus::REAL)rectangleParam.top;
      auto greekdeltax = (Gdiplus::REAL)rectangleParam.width();
      auto greekdeltay = (Gdiplus::REAL)rectangleParam.height();

      auto status = m_pgdiplusgraphics->DrawEllipse(pgdipluspen, x, y, greekdeltax, greekdeltay);

      if (status != Gdiplus::Status::Ok)
      {

         warningf("Gdiplus Failed to DrawEllipse (%f, %f, %f, %f)", x, y, greekdeltax, greekdeltay);

      }

   }


   /*void graphics::fill_ellipse(::f64 x1, ::i32 y1, ::f64 x2, ::i32 y2)
   {

      if (m_pgdiplusgraphics == nullptr)
      {

         return false;

      }

      Gdiplus::Brush * pdraw2dbrush = m_pdraw2dbrush->get_os_data < Brush * >(this);

      if (pdraw2dbrush == nullptr)
      {

         return false;

      }

      return (m_pgdiplusgraphics->FillEllipse(pdraw2dbrush, x1, y1, x2 - x1, y2 - y1)) == Gdiplus::Status::Ok;

   }


   void graphics::FillEllipse(const i32_rectangle &  rectangleParam)
   {

      if (m_pgdiplusgraphics == nullptr)
      {

         return false;

      }

      Gdiplus::Brush * pdraw2dbrush = m_pdraw2dbrush->get_os_data < Brush * >(this);

      if (pdraw2dbrush == nullptr)
      {

         return false;

      }

      return (m_pgdiplusgraphics->FillEllipse(pdraw2dbrush, rectangleParam.left, rectangleParam.top, rectangleParam.right - rectangleParam.left, rectangleParam.bottom - rectangleParam.top)) == Gdiplus::Status::Ok;

   }*/


   //void graphics::fill_ellipse(::f64 x1,::f64 y1,::f64 x2,::f64 y2)
   //{

   //   if (m_pgdiplusgraphics == nullptr)
   //   {

   //      return false;

   //   }

   //   Gdiplus::Brush * pdraw2dbrush = m_pdraw2dbrush->get_os_data < Brush * >(this);

   //   if (pdraw2dbrush == nullptr)
   //   {

   //      return false;

   //   }

   //   return (m_pgdiplusgraphics->FillEllipse(pdraw2dbrush,(Gdiplus::REAL)x1,(Gdiplus::REAL)y1,(Gdiplus::REAL)(x2 - x1),(Gdiplus::REAL)(y2 - y1))) == Gdiplus::Status::Ok;

   //}


   void graphics::fill_ellipse(const ::f64_rectangle & rectangleParam)
   {


      if (m_pgdiplusgraphics == nullptr)
      {

         //return false;

         throw ::exception(error_null_pointer);

      }

      if (m_bTargetRectangleModified)
      {

         defer_on_target_rectangle_update();

      }

      m_pdraw2dbrush->defer_update(this);

      ::cast < ::draw2d_gdiplus::brush>pdraw2dgdiplusbrush = m_pdraw2dbrush;

      auto pgdiplusbrush = pdraw2dgdiplusbrush->m_pgdiplusbrush;

      if (pgdiplusbrush == nullptr)
      {

         //return false;

         throw ::exception(error_null_pointer);

      }

      auto x = (Gdiplus::REAL)rectangleParam.left;
      auto y = (Gdiplus::REAL)rectangleParam.top;
      auto greekdeltax = (Gdiplus::REAL)rectangleParam.width();
      auto greekdeltay = (Gdiplus::REAL)rectangleParam.height();

      auto status = m_pgdiplusgraphics->FillEllipse(pgdiplusbrush, x, y, greekdeltax, greekdeltay);

      if (status != Gdiplus::Status::Ok)
      {

         warningf("Gdiplus Failed to FillEllipse (%f, %f, %f, %f)", x, y, greekdeltax, greekdeltay);

      }

   }


   //void graphics::Pie(::f64 x1, ::i32 y1, ::f64 x2, ::i32 y2, ::f64 x3, ::i32 y3, ::f64 x4, ::i32 y4)
   //{

   //   //ASSERT(get_handle1() != nullptr);
   //   //return ::Pie(get_handle1(), x1, y1, x2, y2, x3, y3, x4, y4) != false;
   //   throw ::not_implemented();

   //   return false;

   //}


   void graphics::Pie(const ::f64_rectangle & rectangleParam, const ::f64_point & pointStart, const ::f64_point & pointEnd)
   {

      //ASSERT(get_handle1() != nullptr);
      //return ::Pie(get_handle1(), rectangleParam.left, rectangleParam.top,
      //             rectangleParam.right, rectangleParam.bottom, pointStart.x, pointStart.y,
      //             pointEnd.x, pointEnd.y) != false;
      throw ::not_implemented();

      //return false;

   }


   void graphics::fill_polygon(const ::f64_point * ppointParam, ::collection::count nCount)
   {

      if (nCount <= 0)
      {

         //return true;

         return;

      }

      if (m_bTargetRectangleModified)
      {

         defer_on_target_rectangle_update();

      }

      bool bOk1 = false;

      //ap(Gdiplus::PointF) ppoint(ppointParam, nCount);

      array < Gdiplus::PointF > pa;

      pa.set_size(nCount);

      for (::collection::index i = 0; i < nCount; i++)
      {

         pa[i].X = (FLOAT)ppointParam[i].x;

         pa[i].Y = (FLOAT)ppointParam[i].y;

      }

      //try
      //{

      m_pdraw2dbrush->defer_update(this);

      ::cast < ::draw2d_gdiplus::brush>pdraw2dgdiplusbrush = m_pdraw2dbrush;

      auto pgdiplusbrush = pdraw2dgdiplusbrush->m_pgdiplusbrush;

      bOk1 = m_pgdiplusgraphics->FillPolygon(pgdiplusbrush, pa.data(), (INT)nCount, gdiplus_get_fill_mode()) == Gdiplus::Status::Ok;

      //}
      //catch(...)
      //{
      //}

      //return bOk1;

   }


   //void graphics::fill_polygon(const ::f64_point * ppointParam,::collection::count nCount)
   //{

   //   if (nCount <= 0)
   //   {

   //      return true;

   //   }

   //   bool bOk1 = false;

   //   ap(Gdiplus::Point) ppoint(ppointParam, nCount);

   //   try
   //   {

   //      //m_pgdiplusgraphics->SetInterpolationMode(Gdiplus::InterpolationModeHighQualityBicubic);

   //      bOk1 = m_pgdiplusgraphics->FillPolygon(m_pdraw2dbrush->get_os_data < Gdiplus::Brush * >(this), ppoint, (INT)  nCount, gdiplus_get_fill_mode()) == Gdiplus::Status::Ok;

   //   }
   //   catch(...)
   //   {
   //   }

   //   //try
   //   //{
   //   //   delete ppoints;
   //   //}
   //   //catch(...)
   //   //{
   //   //}

   //   return bOk1;

   //}


   void graphics::draw_polygon(const ::f64_point * ppointParam, ::collection::count nCount)
   {

      if (nCount <= 0)
      {

         return;

      }

      if (m_bTargetRectangleModified)
      {

         defer_on_target_rectangle_update();

      }

      bool bOk1 = false;

      array < Gdiplus::PointF > pointa;

      pointa.set_size(nCount);

      for (::i32 i = 0; i < nCount; i++)
      {

         pointa[i].X = (Gdiplus::REAL)ppointParam[i].x;
         pointa[i].Y = (Gdiplus::REAL)ppointParam[i].y;

      }

      m_pdraw2dpen->defer_update(this);

      ::cast < ::draw2d_gdiplus::pen>pdraw2dgdipluspen = m_pdraw2dpen;

      auto pgdipluspen = pdraw2dgdipluspen->m_pgdipluspen;

      try
      {

         //m_pgdiplusgraphics->SetInterpolationMode(Gdiplus::InterpolationModeHighQualityBicubic);

         bOk1 = m_pgdiplusgraphics->DrawPolygon(pgdipluspen, pointa.data(), (INT)nCount) == Gdiplus::Status::Ok;

      }
      catch (...)
      {
      }



      //return bOk1;
   }


   //void graphics::draw_polygon(const ::f64_point * ppointParam, ::collection::count nCount)
   //{

   //   if (nCount <= 0)
   //   {

   //      return true;

   //   }

   //   bool bOk1 = false;

   //   ap(Gdiplus::PointF) ppoint(ppointParam, nCount);

   //   try
   //   {

   //      //m_pgdiplusgraphics->SetInterpolationMode(Gdiplus::InterpolationModeHighQualityBicubic);

   //      bOk1 = m_pgdiplusgraphics->DrawPolygon(m_pdraw2dpen->get_os_data < Pen * >(this), ppoint, (INT) nCount) == Gdiplus::Status::Ok;

   //   }
   //   catch(...)
   //   {
   //   }

   //   return bOk1;

   //}


   void graphics::fill_rectangle(const ::f64_rectangle & rectangleParam, ::draw2d::brush * pdraw2dbrush)
   {

      if (m_bTargetRectangleModified)
      {

         defer_on_target_rectangle_update();

      }

      if (::is_null(pdraw2dbrush))
      {

         //return false;

         throw ::exception(error_null_pointer);

      }

      if (payload("log_fill_rectangle").is_true())
      {

         if (rectangleParam.minimum_dimension() > 24)
         {

            tracer()->width(4);

            tracer()->precision(0);

            //information() << "log_fill_rectangle " << rectangleParam << " color: " << pdraw2dbrush->m_color;

         }

      }

      Gdiplus::Rect rectangle;

      copy(rectangle, rectangleParam);

      pdraw2dbrush->defer_update(this);

      ::cast < ::draw2d_gdiplus::brush>pdraw2dgdiplusbrush = pdraw2dbrush;

      auto pgdiplusbrush = pdraw2dgdiplusbrush->m_pgdiplusbrush;

      if (::is_null(pgdiplusbrush))
      { 

         throw ::exception(error_wrong_state);
      
      }

      bool bOk = m_pgdiplusgraphics->FillRectangle(pgdiplusbrush, rectangle) == Gdiplus::Status::Ok;

      if (!bOk)
      {

         warningf("Gdiplus Failed to FillRectangle (%d, %d, %d, %d)",
            rectangle.X, rectangle.Y, rectangle.Width, rectangle.Height);

      }

      //return bOk;

   }


   //void graphics::fill_rectangle(const ::f64_rectangle & rectangleParam, ::draw2d::brush * pdraw2dbrush)
   //{

   //   Gdiplus::RectF i32_rectangle;

   //   __copy(rectangle, rectangleParam);

   //   return m_pgdiplusgraphics->FillRectangle(pdraw2dbrush->get_os_data<Brush *>(this), rectangle) == Gdiplus::Status::Ok;

   //}


   void graphics::round_rectangle(const ::f64_rectangle & rectangle, ::f64 dRadius)
   {

      throw ::exception(todo);

      //return false;

   }


   //void graphics::round_rectangle(const ::f64_rectangle & rectangle, const ::f64_point & point)
   //{

   //   throw ::exception(todo);

   //}


   //void graphics::PatBlt(::f64 x, ::f64 y, ::f64 nWidth, ::f64 nHeight, ::u32 dwRop)
   //{

   //   //ASSERT(get_handle1() != nullptr);
   //   //return ::PatBlt(get_handle1(), x, y, nWidth, nHeight, dwRop) != false;
   //   throw ::not_implemented();

   //   return false;


   //}

//
//   void graphics::_draw_raw(const ::f64_rectangle & rectangleTarget, ::draw2d::graphics * pgraphicsSrc, const ::f64_rectangle & rectangleSource)
//   {
//
//      if (m_pgdiplusgraphics == nullptr)
//      {
//
//         return false;
//
//      }
//
//      Gdiplus::Status ret = Gdiplus::Status::GenericError;
//
//      try
//      {
//
//         if (pgraphicsSrc == nullptr)
//         {
//
//            return false;
//
//         }
//
//         if (pgraphicsSrc->get_current_bitmap() == nullptr)
//         {
//
//            goto gdi_fallback;
//
//         }
//
//         if (pgraphicsSrc->get_current_bitmap()->nok())
//         {
//
//            goto gdi_fallback;
//
//         }
//
//         if (::is_ok(pgraphicsSrc->m_pimage))
//         {
//
//            pgraphicsSrc->m_pimage->defer_update_image();
//
//         }
//
//
//         //bool bThreadToolsForIncreasedFps = ::get_task()== nullptr ? false : ::get_task()->m_bThreadToolsForIncreasedFps;
//
//         //bool bAvoidProcFork = ::get_task() == nullptr ? true : ::get_task()->m_bAvoidProcFork;
//
//         //if (!bAvoidProcFork
//         //      &&
//         //      bThreadToolsForIncreasedFps &&
//         //      pgraphicsSrc->m_pimage->is_ok()
//         //      && m_pimage->is_ok()
//         //      && pgraphicsSrc->m_pimage->m_bMapped
//         //      && m_pimage->m_bMapped)
//         //{
//
//         //   if (m_ealphamode == ::draw2d::e_alpha_mode_blend)
//         //   {
//
//         //      //single_lock synchronouslock(::get_thread_toolset(::thread::tool_draw2d)->mutex());
//
//         //      if (nHeight >= get_processor_count() * 4 && (nWidth * nHeight) >= (get_processor_count() * 64)
//         //            &&   m_pimage->fork_blend(i32_point(x + GetViewportOrg().x, y + GetViewportOrg().y), pgraphicsSrc->m_pimage,
//         //                  i32_point(xSrc + pgraphicsSrc->GetViewportOrg().x, ySrc + pgraphicsSrc->GetViewportOrg().y),
//         //                  ::f64_size(nWidth, nHeight)))
//         //      {
//
//         //         g_cForkBlend++;
//
//         //         if (g_cForkBlend % 100 == 0)
//         //         {
//         //            output_debug_string("\nfork_blend(" + ::as_string(g_cForkBlend) + ") sample=" + ::as_string(nWidth) + "," + ::as_string(nHeight));
//         //         }
//
//         //         return true;
//
//         //      }
//         //      //else
//         //      //{
//         //      //   m_pimage->blend(i32_point(x + GetViewportOrg().x, y + GetViewportOrg().y), pgraphicsSrc->m_pimage,
//         //      //                                     i32_point(xSrc + pgraphicsSrc->GetViewportOrg().x, ySrc + pgraphicsSrc->GetViewportOrg().y),
//         //      //                                     ::f64_size(nWidth, nHeight));
//
//         //      //}
//         //   }
//         //   //else
//         //   //{
//
//         //   //   m_pimage->from(i32_point(x + GetViewportOrg().x, y + GetViewportOrg().y), pgraphicsSrc->m_pimage,
//         //   //                                    i32_point(xSrc + pgraphicsSrc->GetViewportOrg().x, ySrc + pgraphicsSrc->GetViewportOrg().y),
//         //   //                                    ::f64_size(nWidth, nHeight));
//
//
//         //   //}
//
//         //}
//
//         Gdiplus::Bitmap * pdraw2dbitmap = (Gdiplus::Bitmap *) pgraphicsSrc->get_current_bitmap()->get_os_data();
//
//         if (pgraphicsSrc->m_pimage->is_ok() && pgraphicsSrc->m_pimage->m_bColorMatrix)
//         {
//
//            Gdiplus::ImageAttributes imageattributes;
//
//            Gdiplus::ColorMatrix colormatrix;
//
//            copy_color_matrix(colormatrix.m, pgraphicsSrc->m_pimage->m_colormatrix.a);
//
//            imageattributes.SetColorMatrix(
//            &colormatrix,
//            Gdiplus::ColorMatrixFlagsDefault,
//               Gdiplus::ColorAdjustTypeBitmap);
//
//            Gdiplus::Rect i32_rectangle((INT) rectangleTarget.left, (INT) rectangleTarget.top, (INT) rectangleTarget.width(), (INT) rectangleTarget.height());
//
//            ret = m_pgdiplusgraphics->DrawImage(
//                  pdraw2dbitmap,
//                  rectangle, 
//               (INT) (rectangleSource.left + pgraphicsSrc->GetViewportOrg().x), 
//               (INT) (rectangleSource.top + pgraphicsSrc->GetViewportOrg().y), 
//               (INT) (rectangleSource.width()),
//               (INT) (rectangleSource.height()), 
//               Gdiplus::UnitPixel, &imageattributes);
//
//         }
//         else
//         {
//
//            ::i32 xSrcViewport = (::i32) pgraphicsSrc->GetViewportOrg().x;
//
//            ::i32 ySrcViewport = (::i32) pgraphicsSrc->GetViewportOrg().y;
//
//            ret = m_pgdiplusgraphics->DrawImage(
//               pdraw2dbitmap,
//               (INT) rectangleTarget.left, 
//               (INT) rectangleTarget.top,
//               (INT) (rectangleSource.left + xSrcViewport), 
//               (INT) (rectangleSource.top + ySrcViewport), 
//               (INT) (rectangleSource.width()), 
//               (INT) (rectangleSource.height()),
//               Gdiplus::UnitPixel);
//
//         }
//
//         if(ret != Gdiplus::Status::Ok)
//         {
//
//            return false;
//
//         }
//
//      }
//      catch(...)
//      {
//
//         return false;
//
//      }
//
//      return true;
//
////gdi_fallback:
////
////      HDC hdcDst = get_hdc();
////
////      if (hdcDst == nullptr)
////      {
////
////         return false;
////
////      }
////
////      HDC hdcSrc = __graphics(pgraphicsSrc)->get_hdc();
////
////      if(hdcSrc == nullptr)
////      {
////
////         release_hdc(hdcDst);
////
////         return false;
////
////      }
////
////      bool bOk = ::BitBlt(hdcDst, 
////         rectangleTarget.left, rectangleTarget.top,
////         rectangleTarget.width(), rectangleTarget.height(),
////         hdcSrc,
////         pointSrc.x, pointSrc.y, SRCCOPY) != false;
////
////      __graphics(pgraphicsSrc)->release_hdc(hdcSrc);
////
////      release_hdc(hdcDst);
////
////      return bOk;
//
//   }


   void graphics::_draw_raw(const ::image::image_drawing & imagedrawing)
   {

      auto pimageSrc = imagedrawing.image();

      if (!::is_ok(pimageSrc))
      {

         //return false;

         auto pimage2 = imagedrawing.image();

         throw ::exception(error_failed);

      }

      //if (imagedrawing.m_bDoForAllFrames)
      //{

      //   if (pimage->defer_update_all_frames(imagedrawing))
      //   {

      //      return;

      //   }

      //}
      //else
      //{

      auto pimageSource = pimageSrc->get_source_image();

      if (m_bTargetRectangleModified)
      {

         defer_on_target_rectangle_update();

      }


      //}

      //auto pdraw2dgraphicsImage = pimage->acquire_graphics();

      //if (pdraw2dgraphicsImage == nullptr || pdraw2dgraphicsImage->get_current_bitmap() == nullptr)
      //{

         //return false;

        // throw ::exception(error_null_pointer);

      //}

      ::cast < ::draw2d_gdiplus::bitmap > pdraw2dgdiplusbitmap = pimageSource->get_bitmap_as_source(this);

      Gdiplus::Bitmap * pgdiplusbitmapSource = pdraw2dgdiplusbitmap->m_pgdiplusbitmap;

      auto rectangleSource = imagedrawing.source_rectangle();

      auto rectangleTarget = imagedrawing.target_rectangle();

      ::f64 xDst = rectangleTarget.left;

      ::f64 yDst = rectangleTarget.top;

      ::f64 nDstWidth = rectangleTarget.width();

      ::f64 nDstHeight = rectangleTarget.height();

      ::f64 xSrc = rectangleSource.left;

      ::f64 ySrc = rectangleSource.top;

      ::f64 nSrcWidth = rectangleSource.width();

      ::f64 nSrcHeight = rectangleSource.height();

      Gdiplus::RectF rectfTarget((Gdiplus::REAL)xDst, (Gdiplus::REAL)yDst, (Gdiplus::REAL)nDstWidth, (Gdiplus::REAL)nDstHeight);

      Gdiplus::Status ret = Gdiplus::Status::GenericError;
      // Requesting all frames only changes semantics when the source actually
      // contains multiple frames. A one-frame image is safe for static paths.
      auto bDrawsAllFramesOfMultiFrameImage =
         imagedrawing.m_bDoForAllFrames && pimageSource->get_image_count() > 1;

#if FPS_DEBUG
      auto fpsExperimentPhase = opaque_copy_experiment_phase::not_started;
      auto fpsExperimentKind = opaque_copy_experiment_kind::fully_opaque;
      bool bFpsExperimentEligible = false;
      bool bFpsExperimentForceAlphaBlend = false;
      bool bFpsExperimentRecorded = false;
      ::u64 fpsExperimentOpaquePixels = 0;
      auto fpsExperimentOperationStart = ::std::chrono::steady_clock::now();
      if ((::u64)pimageSource->width() * pimageSource->height() >= 65536
         && pimageSource->has_cached_opaque_optimization_candidate())
      {
         auto pageUnit = m_pgdiplusgraphics->GetPageUnit();
         auto pageScale = m_pgdiplusgraphics->GetPageScale();
         auto skipReason = opaque_copy_candidate_skip_reason::eligible;
         if (alpha_mode() != ::draw2d::e_alpha_mode_blend)
            skipReason = opaque_copy_candidate_skip_reason::alpha_mode;
         else if (pageUnit != Gdiplus::UnitPixel && pageScale != 1.0f)
            skipReason = opaque_copy_candidate_skip_reason::page_unit_and_scale;
         else if (pageUnit != Gdiplus::UnitPixel)
            skipReason = opaque_copy_candidate_skip_reason::page_unit;
         else if (pageScale != 1.0f)
            skipReason = opaque_copy_candidate_skip_reason::page_scale;
         else if (bDrawsAllFramesOfMultiFrameImage
            || imagedrawing.is_matrix_filter() || !imagedrawing.opacity().is_opaque())
            skipReason = opaque_copy_candidate_skip_reason::draw_options;
         else if (xSrc != 0 || ySrc != 0 || !pimageSource->m_point.is_null()
            || nSrcWidth <= 0 || nSrcHeight <= 0
            || nSrcWidth != pimageSource->width() || nSrcHeight != pimageSource->height())
            skipReason = opaque_copy_candidate_skip_reason::source_rectangle;
         else if (nDstWidth != nSrcWidth || nDstHeight != nSrcHeight)
            skipReason = opaque_copy_candidate_skip_reason::target_size;
         else if (xDst < INT_MIN || xDst > INT_MAX || yDst < INT_MIN || yDst > INT_MAX
            || xDst + nDstWidth > INT_MAX || yDst + nDstHeight > INT_MAX
            || xDst != (INT)xDst || yDst != (INT)yDst)
            skipReason = opaque_copy_candidate_skip_reason::target_placement;
         else if (pgdiplusbitmapSource->GetWidth() != pimageSource->width()
            || pgdiplusbitmapSource->GetHeight() != pimageSource->height())
            skipReason = opaque_copy_candidate_skip_reason::bitmap_size;
         else
         {
            Gdiplus::Matrix transform;
            Gdiplus::REAL elements[6]{};
            if (m_pgdiplusgraphics->GetTransform(&transform) != Gdiplus::Ok
               || transform.GetElements(elements) != Gdiplus::Ok
               || elements[0] != 1 || elements[1] != 0 || elements[2] != 0 || elements[3] != 1
               || elements[4] < INT_MIN || elements[4] >= INT_MAX
               || elements[5] < INT_MIN || elements[5] >= INT_MAX
               || elements[4] != (INT)elements[4] || elements[5] != (INT)elements[5])
               skipReason = opaque_copy_candidate_skip_reason::transform;
            else if (!pimageSource->has_cached_fully_opaque_pixels())
            {
               if (m_pgdiplusgraphics->GetCompositingMode() != Gdiplus::CompositingModeSourceOver)
                  skipReason = opaque_copy_candidate_skip_reason::compositing_mode;
               else
               {
                  ::image::alpha_statistics statistics;
                  if (!pimageSource->get_cached_opaque_region_statistics(statistics))
                     skipReason = opaque_copy_candidate_skip_reason::alpha_regions;
               }
            }
         }
         if (skipReason == opaque_copy_candidate_skip_reason::eligible)
         {
            if (pimageSource->has_cached_fully_opaque_pixels())
            {
               bFpsExperimentEligible = true;
               fpsExperimentKind = opaque_copy_experiment_kind::fully_opaque;
               fpsExperimentOpaquePixels = (::u64)pimageSource->width() * pimageSource->height();
            }
            else
            {
               ::image::alpha_statistics statistics;
               if (pimageSource->get_cached_opaque_region_statistics(statistics))
               {
                  bFpsExperimentEligible = true;
                  fpsExperimentKind = opaque_copy_experiment_kind::mixed_alpha;
                  fpsExperimentOpaquePixels = statistics.opaque_region_pixels;
               }
            }
            fpsExperimentPhase = get_opaque_copy_experiment_phase(bFpsExperimentEligible);
            bFpsExperimentForceAlphaBlend = bFpsExperimentEligible
               && fpsExperimentPhase == opaque_copy_experiment_phase::alpha_blend;
            fpsExperimentOperationStart = ::std::chrono::steady_clock::now();
         }
         note_opaque_copy_candidate_draw(pimageSource, skipReason, pageUnit, pageScale);
         report_dabzo5y_opaque_copy_candidate(pimageSource, skipReason,
            pageUnit, pageScale, xSrc, ySrc, nSrcWidth, nSrcHeight,
            xDst, yDst, nDstWidth, nDstHeight);
      }
#endif

      // A proven opaque static source needs no destination alpha blending.
      // Restrict this path to a native-size, pixel-aligned full image. Scaling,
      // rotation, filters, opacity and mixed-alpha sources retain the old path.
#if FPS_DEBUG
      if (!bFpsExperimentForceAlphaBlend &&
#else
      if (
#endif
         alpha_mode() == ::draw2d::e_alpha_mode_blend
         && m_pgdiplusgraphics->GetPageUnit() == Gdiplus::UnitPixel
         && m_pgdiplusgraphics->GetPageScale() == 1.0f
         && !bDrawsAllFramesOfMultiFrameImage
         && !imagedrawing.is_matrix_filter() && imagedrawing.opacity().is_opaque()
         && xSrc == 0 && ySrc == 0 && pimageSource->m_point.is_null()
         && nSrcWidth > 0 && nSrcHeight > 0
         && nSrcWidth == pimageSource->width() && nSrcHeight == pimageSource->height()
         && nDstWidth == nSrcWidth && nDstHeight == nSrcHeight
         && (::u64)pimageSource->width() * pimageSource->height() >= 65536
         && xDst >= INT_MIN && xDst <= INT_MAX && yDst >= INT_MIN && yDst <= INT_MAX
         && xDst + nDstWidth <= INT_MAX && yDst + nDstHeight <= INT_MAX
         && xDst == (INT)xDst && yDst == (INT)yDst
         && pgdiplusbitmapSource->GetWidth() == pimageSource->width()
         && pgdiplusbitmapSource->GetHeight() == pimageSource->height()
         && pimageSource->has_cached_fully_opaque_pixels())
      {
#if FPS_DEBUG
         auto timeFullOpaqueCopyStart = ::std::chrono::steady_clock::now();
         bool bFullOpaqueCopySucceeded = false;
#endif
         Gdiplus::Matrix transform;
         Gdiplus::REAL elements[6];
         if (m_pgdiplusgraphics->GetTransform(&transform) == Gdiplus::Ok
            && transform.GetElements(elements) == Gdiplus::Ok
            && elements[0] == 1 && elements[1] == 0 && elements[2] == 0 && elements[3] == 1
            && elements[4] >= INT_MIN && elements[4] < INT_MAX
            && elements[5] >= INT_MIN && elements[5] < INT_MAX
            && elements[4] == (INT)elements[4] && elements[5] == (INT)elements[5])
         {
            auto previousMode = m_pgdiplusgraphics->GetCompositingMode();
            if (m_pgdiplusgraphics->SetCompositingMode(Gdiplus::CompositingModeSourceCopy) == Gdiplus::Ok)
            {
               auto status = m_pgdiplusgraphics->DrawImage(pgdiplusbitmapSource,
                  Gdiplus::Rect((INT)xDst, (INT)yDst, (INT)nSrcWidth, (INT)nSrcHeight),
                  0, 0, (INT)nSrcWidth, (INT)nSrcHeight, Gdiplus::UnitPixel);
               m_pgdiplusgraphics->SetCompositingMode(previousMode);
               if (status == Gdiplus::Ok)
               {
#if FPS_DEBUG
                  bFullOpaqueCopySucceeded = true;
#else
                  return;
#endif
               }
            }
         }
#if FPS_DEBUG
         auto fullElapsedNanoseconds = (::u64)::std::chrono::duration_cast<::std::chrono::nanoseconds>(
            ::std::chrono::steady_clock::now() - timeFullOpaqueCopyStart).count();
         auto fullSavedPixels = bFullOpaqueCopySucceeded
            ? (::u64)pimageSource->width() * pimageSource->height() : 0;
         note_full_opaque_copy(bFullOpaqueCopySucceeded, fullSavedPixels, fullElapsedNanoseconds);
         if (bFullOpaqueCopySucceeded)
         {
            if (bFpsExperimentEligible
               && fpsExperimentPhase == opaque_copy_experiment_phase::optimized)
            {
               auto targetPixels = (::u64)nDstWidth * (::u64)nDstHeight;
               note_opaque_copy_experiment_draw(fpsExperimentPhase, fpsExperimentKind,
                  true, (::u64)pimageSource->width() * pimageSource->height(), targetPixels,
                  fpsExperimentOpaquePixels, fullSavedPixels, 0,
                  (::u64)::std::chrono::duration_cast<::std::chrono::nanoseconds>(
                     ::std::chrono::steady_clock::now() - fpsExperimentOperationStart).count(),
                  pimageSource->width(), pimageSource->height(), (INT)nDstWidth,
                  (INT)nDstHeight, (INT)xDst, (INT)yDst);
               bFpsExperimentRecorded = true;
            }
            return;
         }
#endif
      }

      // A mixed static source can still avoid blending over large regions
      // whose alpha statistics prove every source pixel is opaque. Keep this
      // limited to the same exact pixel-to-pixel transform as the all-opaque
      // path; scaled or filtered draws can sample translucent pixels across
      // an opaque-region boundary.
#if FPS_DEBUG
      if (!bFpsExperimentForceAlphaBlend &&
#else
      if (
#endif
         alpha_mode() == ::draw2d::e_alpha_mode_blend
         && m_pgdiplusgraphics->GetPageUnit() == Gdiplus::UnitPixel
         && m_pgdiplusgraphics->GetPageScale() == 1.0f
         && m_pgdiplusgraphics->GetCompositingMode() == Gdiplus::CompositingModeSourceOver
         && !bDrawsAllFramesOfMultiFrameImage
         && !imagedrawing.is_matrix_filter() && imagedrawing.opacity().is_opaque()
         && xSrc == 0 && ySrc == 0 && pimageSource->m_point.is_null()
         && nSrcWidth > 0 && nSrcHeight > 0
         && nSrcWidth == pimageSource->width() && nSrcHeight == pimageSource->height()
         && nDstWidth == nSrcWidth && nDstHeight == nSrcHeight
         && (::u64)pimageSource->width() * pimageSource->height() >= 65536
         && xDst >= INT_MIN && xDst <= INT_MAX && yDst >= INT_MIN && yDst <= INT_MAX
         && xDst + nDstWidth <= INT_MAX && yDst + nDstHeight <= INT_MAX
         && xDst == (INT)xDst && yDst == (INT)yDst
         && pgdiplusbitmapSource->GetWidth() == pimageSource->width()
         && pgdiplusbitmapSource->GetHeight() == pimageSource->height())
      {
         Gdiplus::Matrix transform;
         Gdiplus::REAL elements[6];
         if (m_pgdiplusgraphics->GetTransform(&transform) == Gdiplus::Ok
            && transform.GetElements(elements) == Gdiplus::Ok
            && elements[0] == 1 && elements[1] == 0 && elements[2] == 0 && elements[3] == 1
            && elements[4] >= INT_MIN && elements[4] < INT_MAX
            && elements[5] >= INT_MIN && elements[5] < INT_MAX
            && elements[4] == (INT)elements[4] && elements[5] == (INT)elements[5])
         {
            ::image::alpha_statistics statistics;
#if FPS_DEBUG
            auto timeMixedCandidateStart = ::std::chrono::steady_clock::now();
#endif
            if (pimageSource->get_cached_opaque_region_statistics(statistics))
            {
#if FPS_DEBUG
               auto timeMixedCopyStart = timeMixedCandidateStart;
               ::u64 mixedCopyNanoseconds = 0;
               ::u64 mixedRegionDraws = 0;
#endif
               Gdiplus::Region blendedRegion(Gdiplus::Rect(
                  (INT)xDst, (INT)yDst, (INT)nDstWidth, (INT)nDstHeight));
               bool bRegionReady = blendedRegion.GetLastStatus() == Gdiplus::Ok;
               for (::collection::index i = 0; bRegionReady
                  && i < statistics.opaque_regions.get_count(); ++i)
               {
                  const auto & opaque = statistics.opaque_regions.element_at(i);
                  Gdiplus::Rect rectangleOpaqueDestination(
                     (INT)xDst + opaque.left, (INT)yDst + opaque.top,
                     opaque.width(), opaque.height());
                  bRegionReady = blendedRegion.Exclude(rectangleOpaqueDestination) == Gdiplus::Ok;
               }

               if (bRegionReady)
               {
                  auto previousMode = m_pgdiplusgraphics->GetCompositingMode();
                  auto savedState = m_pgdiplusgraphics->Save();
                  if (savedState != 0
                     && m_pgdiplusgraphics->SetCompositingMode(Gdiplus::CompositingModeSourceCopy) == Gdiplus::Ok)
                  {
                     bool bOpaqueCopiesSucceeded = true;
                     for (::collection::index i = 0; bOpaqueCopiesSucceeded
                        && i < statistics.opaque_regions.get_count(); ++i)
                     {
                        const auto & opaque = statistics.opaque_regions.element_at(i);
#if FPS_DEBUG
                        auto timeRegionCopyStart = ::std::chrono::steady_clock::now();
#endif
                        auto status = m_pgdiplusgraphics->DrawImage(pgdiplusbitmapSource,
                           Gdiplus::Rect((INT)xDst + opaque.left, (INT)yDst + opaque.top,
                              opaque.width(), opaque.height()),
                           opaque.left, opaque.top, opaque.width(), opaque.height(), Gdiplus::UnitPixel);
#if FPS_DEBUG
                        mixedCopyNanoseconds += (::u64)::std::chrono::duration_cast<::std::chrono::nanoseconds>(
                           ::std::chrono::steady_clock::now() - timeRegionCopyStart).count();
                        ++mixedRegionDraws;
#endif
                        bOpaqueCopiesSucceeded = status == Gdiplus::Ok;
                     }

                     if (bOpaqueCopiesSucceeded
                        && m_pgdiplusgraphics->SetCompositingMode(previousMode) == Gdiplus::Ok
                        && m_pgdiplusgraphics->SetClip(&blendedRegion, Gdiplus::CombineModeIntersect) == Gdiplus::Ok)
                     {
#if FPS_DEBUG
                        auto timeMixedBlendStart = ::std::chrono::steady_clock::now();
#endif
                        auto status = m_pgdiplusgraphics->DrawImage(pgdiplusbitmapSource,
                           Gdiplus::Rect((INT)xDst, (INT)yDst, (INT)nDstWidth, (INT)nDstHeight),
                           0, 0, (INT)nSrcWidth, (INT)nSrcHeight, Gdiplus::UnitPixel);
#if FPS_DEBUG
                        auto mixedBlendNanoseconds = (::u64)::std::chrono::duration_cast<::std::chrono::nanoseconds>(
                           ::std::chrono::steady_clock::now() - timeMixedBlendStart).count();
#endif
                        m_pgdiplusgraphics->Restore(savedState);
                        // Do not retry the full blended draw if GDI+ reports an
                        // error here: it does not promise that a failed draw
                        // left the destination untouched, so retrying could
                        // blend some translucent pixels twice. A later frame
                        // can redraw the image normally.
#if FPS_DEBUG
                        auto bMixedDrawSucceeded = status == Gdiplus::Ok;
                        auto mixedElapsedNanoseconds = (::u64)::std::chrono::duration_cast<::std::chrono::nanoseconds>(
                           ::std::chrono::steady_clock::now() - timeMixedCopyStart).count();
                        auto mixedSavedPixels = bMixedDrawSucceeded ? statistics.opaque_region_pixels : 0;
                        note_mixed_opaque_copy(bMixedDrawSucceeded, !bMixedDrawSucceeded,
                           mixedSavedPixels, mixedRegionDraws, mixedCopyNanoseconds,
                           mixedBlendNanoseconds, mixedElapsedNanoseconds);
                        if (bFpsExperimentEligible
                           && fpsExperimentPhase == opaque_copy_experiment_phase::optimized)
                        {
                           auto targetPixels = (::u64)nDstWidth * (::u64)nDstHeight;
                           auto blendedPixels = bMixedDrawSucceeded
                              ? targetPixels - (mixedSavedPixels > targetPixels ? targetPixels : mixedSavedPixels)
                              : targetPixels;
                           note_opaque_copy_experiment_draw(fpsExperimentPhase, fpsExperimentKind,
                              bMixedDrawSucceeded, (::u64)pimageSource->width() * pimageSource->height(),
                              targetPixels, fpsExperimentOpaquePixels, mixedSavedPixels, blendedPixels,
                              (::u64)::std::chrono::duration_cast<::std::chrono::nanoseconds>(
                                 ::std::chrono::steady_clock::now() - fpsExperimentOperationStart).count(),
                              pimageSource->width(), pimageSource->height(), (INT)nDstWidth,
                              (INT)nDstHeight, (INT)xDst, (INT)yDst);
                           bFpsExperimentRecorded = true;
                        }
#endif
                        (void)status;
                        return;
                     }
                     else
                     {
                        m_pgdiplusgraphics->Restore(savedState);
#if FPS_DEBUG
                        auto mixedElapsedNanoseconds = (::u64)::std::chrono::duration_cast<::std::chrono::nanoseconds>(
                           ::std::chrono::steady_clock::now() - timeMixedCopyStart).count();
                        note_mixed_opaque_copy(false, false, 0, mixedRegionDraws,
                           mixedCopyNanoseconds, 0, mixedElapsedNanoseconds);
#endif
                        // No blended draw has happened yet. A full SourceOver
                        // fallback safely overwrites any opaque regions copied
                        // before a later region failed.
                     }
                  }
                  else
                  {
                     if (savedState != 0) m_pgdiplusgraphics->Restore(savedState);
#if FPS_DEBUG
                     auto mixedElapsedNanoseconds = (::u64)::std::chrono::duration_cast<::std::chrono::nanoseconds>(
                        ::std::chrono::steady_clock::now() - timeMixedCopyStart).count();
                     note_mixed_opaque_copy(false, false, 0, mixedRegionDraws,
                        mixedCopyNanoseconds, 0, mixedElapsedNanoseconds);
#endif
                  }
               }
#if FPS_DEBUG
               else
               {
                  auto mixedElapsedNanoseconds = (::u64)::std::chrono::duration_cast<::std::chrono::nanoseconds>(
                     ::std::chrono::steady_clock::now() - timeMixedCopyStart).count();
                  note_mixed_opaque_copy(false, false, 0, mixedRegionDraws,
                     mixedCopyNanoseconds, 0, mixedElapsedNanoseconds);
               }
#endif
            }
         }
      }

      if (m_bUseImageMipMapsOrResizedImages)
      {

         scoped_restore(m_bUseImageMipMapsOrResizedImages);

         m_bUseImageMipMapsOrResizedImages = false;

         if (pimageSource->is_ok())
         {

            ::i32 iW = (::i32)nDstWidth;
            ::i32 iH = (::i32)nDstHeight;

            if (pimageSource->width() != iW
               && pimageSource->height() != iH
               && xSrc == 0 && ySrc == 0
               && iW > 0 && iH > 0)
            {

               auto pextension = pimageSource->get_extension();

               if (pextension)
               {

                  auto & psizeimage = pextension->m_psizeimage;

                  defer_construct_newø(psizeimage);

                  i32_size size(imagedrawing.m_rectangleTarget.size());

                  bool bExists = false;

                  auto & pimage = psizeimage->get(size, bExists);

                  if (!bExists)
                  {

                     ::image::image_source imagesource3(imagedrawing);

                     ::f64_rectangle r3(0, 0, iW, iH);

                     ::image::image_drawing_options imagedrawingoptions3(r3);

                     ::image::image_drawing imagedrawing3(imagedrawingoptions3, imagesource3);

                     //scoped_restore(pdraw2dgraphicsImage->m_bUseImageMipMapsOrResizedImages);

                     //pdraw2dgraphicsImage->m_bUseImageMipMapsOrResizedImages = false;

                     auto pdraw2dgraphicsImage = pimage->acquire_graphics();

                     pdraw2dgraphicsImage->draw(imagedrawing3);

                  }

                  ::image::image_source imagesource2(pimage);

                  ::image::image_drawing_options imagedrawingoptions2((const ::image::image_drawing_options &)imagedrawing);

                  imagedrawingoptions2.m_rectangleTarget.right = imagedrawingoptions2.m_rectangleTarget.left + (::f64)iW;

                  imagedrawingoptions2.m_rectangleTarget.bottom = imagedrawingoptions2.m_rectangleTarget.top + (::f64)iH;

                  ::image::image_drawing imagedrawing2(imagedrawingoptions2, imagesource2);

                  _draw_raw(imagedrawing2);

                  return;

               }

               if (pimageSource->m_emipmap == ::image::e_mipmap_anisotropic)
               {

                  try
                  {

                     ::collection::index iFind = -1;

                     ::f64 dRateFound = 1024.0;

                     ::i32 xFound;
                     ::i32 yFound;
                     ::i32 cxFound;
                     ::i32 cyFound;

                     for (::collection::index i = 0; i < pimageSource->get_image_count(); i++)
                     {

                        ::i32 x1 = 0;
                        ::i32 y1 = 0;
                        ::i32 x2 = 0;
                        ::i32 y2 = 0;
                        ::i32 dx = (::i32)nSrcWidth;
                        ::i32 dy = (::i32)nSrcHeight;
                        ::i32 cx1 = (::i32)nSrcWidth;
                        ::i32 cy1 = (::i32)nSrcHeight;
                        ::i32 cx2 = (::i32)nSrcWidth;
                        ::i32 cy2 = (::i32)nSrcHeight;

                        while (dx >= nDstWidth)
                        {
                           x1 = x2;
                           x2 += dx;
                           cx1 = dx;
                           dx /= 2;
                           cx2 = dx;
                        }

                        while (dy >= nSrcHeight)
                        {
                           y1 = y2;
                           y2 += dy;
                           cy1 = dy;
                           dy /= 2;
                           cy2 = dy;
                        }

                        if (y1 == nSrcHeight)
                        {
                           y1 = 0;
                        }
                        if (y2 == nSrcHeight)
                        {
                           y2 = 0;
                        }

                        ::f64 dRateX = (::f64)nDstWidth / (::f64)cx1;

                        ::f64 dRateY = (::f64)nDstHeight / (::f64)cy1;

                        ::f64 dRateArea = dRateX * dRateY;

                        if (dRateArea < dRateFound)
                        {

                           iFind = i;

                           dRateFound = dRateArea;

                           xFound = x1;

                           yFound = y1;

                           cxFound = cx1;

                           cyFound = cy1;

                        }

                     }

                     if (iFind >= 0)
                     {

                        ::image::image_pointer pimage = pimageSource->get_image(iFind);

                        auto emode = m_pgdiplusgraphics->GetInterpolationMode();

                        m_pgdiplusgraphics->SetPixelOffsetMode(Gdiplus::PixelOffsetModeHighSpeed);

                        //m_pgdiplusgraphics->SetInterpolationMode(Gdiplus::InterpolationModeNearestNeighbor);

                        //m_pgdiplusgraphics->SetInterpolationMode(Gdiplus::InterpolationModeBilinear);

                        if (imagedrawing.m_bIntegerPlacement)
                        {

                           Gdiplus::Rect r;

                           r.X = (INT)rectfTarget.X;
                           r.Y = (INT)rectfTarget.Y;
                           r.Width = (INT)rectfTarget.Width;
                           r.Height = (INT)rectfTarget.Height;


                           ret = m_pgdiplusgraphics->DrawImage(
                              pgdiplusbitmapSource,
                              r,
                              (INT)xFound, (INT)yFound,
                              (INT)cxFound, (INT)cyFound,
                              Gdiplus::UnitPixel);

                        }
                        else
                        {
                           ret = m_pgdiplusgraphics->DrawImage(
                              pgdiplusbitmapSource,
                              rectfTarget,
                              (Gdiplus::REAL)xFound, (Gdiplus::REAL)yFound,
                              (Gdiplus::REAL)cxFound, (Gdiplus::REAL)cyFound,
                              Gdiplus::UnitPixel);

                        }

                        //m_pgdiplusgraphics->SetInterpolationMode(emode);

                        if (ret == Gdiplus::Status::Ok)
                        {

                           //return true;

                           return;

                        }

                     }

                  }
                  catch (...)
                  {


                  }

               }

            }

         }

      }

      try
      {

         //::cast < ::draw2d_gdiplus::bitmap > pdraw2dgdiplusbitmap = pimage->get_bitmap_as_source();

         //Gdiplus::Bitmap * pgdiplusbitmap = pdraw2dgdiplusbitmap->m_pgdiplusbitmap;

         color_matrix colormatrix;

         if (::is_ok(pimageSource) && imagedrawing.get_matrix(colormatrix))
         {

            Gdiplus::ImageAttributes imageattributes;

            Gdiplus::ColorMatrix gdipluscolormatrix;

            copy(gdipluscolormatrix, colormatrix);

            imageattributes.SetColorMatrix(
               &gdipluscolormatrix,
               Gdiplus::ColorMatrixFlagsDefault,
               Gdiplus::ColorAdjustTypeBitmap);

            if (imagedrawing.m_bIntegerPlacement)
            {

               Gdiplus::Rect r;

               r.X = (INT)rectfTarget.X;
               r.Y = (INT)rectfTarget.Y;
               r.Width = (INT)rectfTarget.Width;
               r.Height = (INT)rectfTarget.Height;

               ret = m_pgdiplusgraphics->DrawImage(pgdiplusbitmapSource, r,
                  (INT)xSrc, (INT)ySrc,
                  (INT)nSrcWidth, (INT)nSrcHeight, Gdiplus::UnitPixel, &imageattributes);

            }
            else
            {

               ret = m_pgdiplusgraphics->DrawImage(pgdiplusbitmapSource, rectfTarget,
                  (Gdiplus::REAL)xSrc, (Gdiplus::REAL)ySrc,
                  (Gdiplus::REAL)nSrcWidth, (Gdiplus::REAL)nSrcHeight, Gdiplus::UnitPixel, &imageattributes);

            }

         }
         else
         {

            auto opacityPolicy = get_effective_image_opacity_policy();
#if FPS_DEBUG
            static ::std::atomic<const void *> s_lastDabzo5yStretchImage{nullptr};
            auto bReportDabzo5yStretch = should_report_dabzo5y_image_once(
               pimageSource, s_lastDabzo5yStretchImage);
            ::image::alpha_statistics sourceStatistics;
            bool bStaticCacheCurrent = false;
            bool bActiveGraphicsLease = pimageSource->has_active_destination_graphics_lease();
            bool bCacheLockAvailable = false;
            bool bCacheValid = false;
            ::image::pixel_usage cachedPixelUsage = ::image::pixel_usage::unknown;
            ::i32_size cachedSize;
            ::i32_point pointCached;
            bool bActivePixmapLease = false;
            if (bReportDabzo5yStretch)
            {
               ::std::unique_lock<::std::recursive_mutex> statisticsLock(
                  pimageSource->m_mutexAlphaStatistics, ::std::try_to_lock);
               bCacheLockAvailable = statisticsLock.owns_lock();
               if (bCacheLockAvailable)
               {
                  bActivePixmapLease = pimageSource->m_pimagepixmaplease != nullptr;
                  const auto & cache = pimageSource->m_alphastatisticscache;
                  bCacheValid = cache.valid;
                  cachedPixelUsage = cache.usage;
                  cachedSize = cache.statistics.size;
                  pointCached = cache.statistics.origin;
                  bStaticCacheCurrent = cachedPixelUsage == ::image::pixel_usage::static_source
                     && bCacheValid && !bActiveGraphicsLease
                     && !bActivePixmapLease && cache.statistics.size == pimageSource->size()
                     && cache.statistics.origin == pimageSource->m_point;
                  if (bStaticCacheCurrent)
                     sourceStatistics = cache.statistics;
               }
            }
#endif
            auto bPreserveOpaqueStaticStretch =
               opacityPolicy == ::draw2d::e_image_opacity_policy_preserve_static_opaque
               && pimageSource->has_cached_fully_opaque_pixels()
               && !bDrawsAllFramesOfMultiFrameImage
               && !imagedrawing.is_matrix_filter()
               && imagedrawing.opacity().is_opaque()
               && xSrc == 0 && ySrc == 0 && pimageSource->m_point.is_null()
               && nSrcWidth == pimageSource->width()
               && nSrcHeight == pimageSource->height()
               && nDstWidth > 0 && nDstHeight > 0
               && (nDstWidth != nSrcWidth || nDstHeight != nSrcHeight);

            Gdiplus::ImageAttributes imageattributes;
            auto wrapStatus = Gdiplus::Status::GenericError;
            bool bUseEdgeExtendedSampling = bPreserveOpaqueStaticStretch
               && (wrapStatus = imageattributes.SetWrapMode(Gdiplus::WrapModeTileFlipXY)) == Gdiplus::Ok;
#if FPS_DEBUG
            bool bFpsExperimentAlphaBlendReady = true;
            bool bFpsExperimentRestoreCompositingMode = false;
            auto fpsExperimentPreviousCompositingMode = m_pgdiplusgraphics->GetCompositingMode();
            if (bFpsExperimentForceAlphaBlend
               && fpsExperimentPreviousCompositingMode != Gdiplus::CompositingModeSourceOver)
            {
               if (m_pgdiplusgraphics->SetCompositingMode(Gdiplus::CompositingModeSourceOver) == Gdiplus::Ok)
                  bFpsExperimentRestoreCompositingMode = true;
               else
               {
                  bFpsExperimentAlphaBlendReady = false;
                  static ::std::atomic<bool> s_reportedAlphaBlendSetupFailure{false};
                  if (!s_reportedAlphaBlendSetupFailure.exchange(true, ::std::memory_order_relaxed))
                     informationf("FPS opaque experiment: failed to select GDI+ SourceOver for alpha-blend baseline");
               }
            }
#endif

            if (bUseEdgeExtendedSampling)
            {

               // Mirroring the outer source pixels gives the resampler opaque
               // edge samples instead of transparent samples beyond the image.
               ret = m_pgdiplusgraphics->DrawImage(pgdiplusbitmapSource, rectfTarget,
                  (Gdiplus::REAL)xSrc, (Gdiplus::REAL)ySrc,
                  (Gdiplus::REAL)nSrcWidth, (Gdiplus::REAL)nSrcHeight,
                  Gdiplus::UnitPixel, &imageattributes);

            }
            else
            {

               ret = m_pgdiplusgraphics->DrawImage(pgdiplusbitmapSource, rectfTarget,
                  (Gdiplus::REAL)xSrc, (Gdiplus::REAL)ySrc,
                  (Gdiplus::REAL)nSrcWidth, (Gdiplus::REAL)nSrcHeight, Gdiplus::UnitPixel);

            }

#if FPS_DEBUG
            if (bFpsExperimentRestoreCompositingMode)
               m_pgdiplusgraphics->SetCompositingMode(fpsExperimentPreviousCompositingMode);
            if (bReportDabzo5yStretch)
            {
               report_dabzo5y_opaque_stretch(pimageSource, opacityPolicy,
                  bStaticCacheCurrent, bActiveGraphicsLease, bCacheLockAvailable,
                  bCacheValid, cachedPixelUsage, cachedSize, pointCached,
                  bActivePixmapLease, sourceStatistics, bPreserveOpaqueStaticStretch,
                  bUseEdgeExtendedSampling, wrapStatus, ret,
                  m_pgdiplusgraphics->GetPageUnit(), m_pgdiplusgraphics->GetPageScale(),
                  xSrc, ySrc, nSrcWidth, nSrcHeight, xDst, yDst, nDstWidth, nDstHeight);
            }
            if (bFpsExperimentEligible && bFpsExperimentAlphaBlendReady && !bFpsExperimentRecorded
               && (fpsExperimentPhase == opaque_copy_experiment_phase::optimized
                  || fpsExperimentPhase == opaque_copy_experiment_phase::alpha_blend))
            {
               auto targetPixels = (::u64)nDstWidth * (::u64)nDstHeight;
               auto elapsedNanoseconds = (::u64)::std::chrono::duration_cast<::std::chrono::nanoseconds>(
                  ::std::chrono::steady_clock::now() - fpsExperimentOperationStart).count();
               note_opaque_copy_experiment_draw(fpsExperimentPhase, fpsExperimentKind,
                  ret == Gdiplus::Status::Ok, (::u64)pimageSource->width() * pimageSource->height(),
                  targetPixels, fpsExperimentOpaquePixels, 0, targetPixels, elapsedNanoseconds,
                  pimageSource->width(), pimageSource->height(), (INT)nDstWidth,
                  (INT)nDstHeight, (INT)xDst, (INT)yDst);
               bFpsExperimentRecorded = true;
            }
#endif

         }

         if (ret != Gdiplus::Status::Ok)
         {

            warningf("Gdiplus Failed to DrawImage (%f, %f, %f, %f) - (%f, %f, %f, %f)",
               rectfTarget.X, rectfTarget.Y, rectfTarget.Width, rectfTarget.Height,
               xSrc, ySrc, nSrcWidth, nSrcHeight);

         }

      }
      catch (...)
      {

         //return false;

         throw ::exception(error_exception);

      }

      //return true;

   }


   //void graphics::draw_raw(const  xDst, ::i32 yDst, ::i32 nDstWidth, ::i32 nDstHeight, ::draw2d::graphics * pgraphicsSrc, ::f64 xSrc, ::i32 ySrc, ::i32 nSrcWidth, ::i32 nSrcHeight, ::u32 dwRop)
   //{

   //   if (pgraphicsSrc == nullptr)
   //   {

   //      return false;

   //   }

   //   Gdiplus::Rect rectangleTarget(xDst, yDst, nDstWidth, nDstHeight);

   //   if (pgraphicsSrc == nullptr || pgraphicsSrc->get_current_bitmap() == nullptr)
   //   {

   //      return false;

   //   }

   //   Gdiplus::Status ret = Gdiplus::Status::GenericError;

   //   if (pgraphicsSrc->m_pimage->is_ok())
   //   {

   //      if (pgraphicsSrc->m_pimage->m_emipmap == ::draw2d::e_mipmap_anisotropic
   //            && (pgraphicsSrc->m_pimage->width() == nSrcWidth
   //                && pgraphicsSrc->m_pimage->height() == nSrcHeight
   //                && xSrc == 0 && ySrc == 0 && nDstWidth > 0 && nDstHeight > 0))
   //      {

   //         try
   //         {

   //            /*::i32 x1 = 0;
   //            ::i32 y1 = 0;
   //            ::i32 x2 = 0;
   //            ::i32 y2 = 0;
   //            ::i32 dx = nSrcWidth;
   //            ::i32 dy = nSrcHeight;
   //            ::i32 cx1 = nSrcWidth;
   //            ::i32 cy1 = nSrcHeight;
   //            ::i32 cx2 = nSrcWidth;
   //            ::i32 cy2 = nSrcHeight;

   //            while (dx >= nDstWidth)
   //            {
   //               x1 = x2;
   //               x2 += dx;
   //               cx1 = dx;
   //               dx /= 2;
   //               cx2 = dx;
   //            }

   //            while (dy >= nSrcHeight)
   //            {
   //               y1 = y2;
   //               y2 += dy;
   //               cy1 = dy;
   //               dy /= 2;
   //               cy2 = dy;
   //            }

   //            if (y1 == nSrcHeight)
   //            {
   //               y1 = 0;
   //            }
   //            if (y2 == nSrcHeight)
   //            {
   //               y2 = 0;
   //            }*/

   //            //::image::image_pointer pimage = m_pimage;
   //            //::i32 iScan = pimage->m_iScan;
   //            //::image::image_pointer pimageMipmap = pgraphicsSrc->m_pimage;
   //            //::color::color * pcrMipmap = imageMipmap.m_pcolorref;
   //            //::i32 iMimapScan = imageMipmap.m_iScan;
   //            //::f64_size sizeMipmap = imageMipmap.m_size;

   //            //trilinearImageScaling(
   //            //&pimage->m_pcolorref[xDst + iScan * yDst / sizeof(::color::color)],
   //            //nDstWidth, nDstHeight,
   //            //iScan,
   //            //&pcrMipmap[x1 + y1 * iMimapScan / sizeof(::color::color)],
   //            //cx1, cy1,
   //            //&pcrMipmap[x2 + y2 * iMimapScan / sizeof(::color::color)],
   //            //cx2, cy2,
   //            //iMimapScan);

   //            index iFind = -1;

   //            ::f64 dRateFound = 1024.0;

   //            ::i32 xFound;
   //            ::i32 yFound;
   //            ::i32 cxFound;
   //            ::i32 cyFound;

   //            for (::collection::index i = 0; i < pgraphicsSrc->m_pimage->get_image_count(); i++)
   //            {

   //               ::i32 x1 = 0;
   //               ::i32 y1 = 0;
   //               ::i32 x2 = 0;
   //               ::i32 y2 = 0;
   //               ::i32 dx = nSrcWidth;
   //               ::i32 dy = nSrcHeight;
   //               ::i32 cx1 = nSrcWidth;
   //               ::i32 cy1 = nSrcHeight;
   //               ::i32 cx2 = nSrcWidth;
   //               ::i32 cy2 = nSrcHeight;

   //               while (dx >= nDstWidth)
   //               {
   //                  x1 = x2;
   //                  x2 += dx;
   //                  cx1 = dx;
   //                  dx /= 2;
   //                  cx2 = dx;
   //               }

   //               while (dy >= nSrcHeight)
   //               {
   //                  y1 = y2;
   //                  y2 += dy;
   //                  cy1 = dy;
   //                  dy /= 2;
   //                  cy2 = dy;
   //               }

   //               if (y1 == nSrcHeight)
   //               {
   //                  y1 = 0;
   //               }
   //               if (y2 == nSrcHeight)
   //               {
   //                  y2 = 0;
   //               }

   //               ::f64 dRateX = (::f64)nDstWidth / (::f64)cx1;

   //               ::f64 dRateY = (::f64)nDstHeight / (::f64)cy1;

   //               ::f64 dRateArea = dRateX * dRateY;

   //               if (dRateArea < dRateFound)
   //               {

   //                  iFind = i;

   //                  dRateFound = dRateArea;

   //                  xFound = x1;

   //                  yFound = y1;

   //                  cxFound = cx1;

   //                  cyFound = cy1;

   //               }

   //            }

   //            if (iFind >= 0)
   //            {

   //               ::image::image_pointer pimage = pgraphicsSrc->m_pimage->get_image(iFind);

   //               auto emode = m_pgdiplusgraphics->GetInterpolationMode();

   //               m_pgdiplusgraphics->SetPixelOffsetMode(Gdiplus::PixelOffsetModeHighSpeed);

   //               //m_pgdiplusgraphics->SetInterpolationMode(Gdiplus::InterpolationModeNearestNeighbor);

   //               //m_pgdiplusgraphics->SetInterpolationMode(Gdiplus::InterpolationModeBilinear);

   //               ret = m_pgdiplusgraphics->DrawImage(
   //                     (Gdiplus::Bitmap *) pimage->get_bitmap()->get_os_data(),
   //                     rectangleTarget, xFound, yFound, cxFound, cyFound, Gdiplus::UnitPixel);

   //               //m_pgdiplusgraphics->SetInterpolationMode(emode);

   //               if (ret == Gdiplus::Status::Ok)
   //               {

   //                  return true;

   //               }

   //            }

   //         }
   //         catch (...)
   //         {


   //         }



   //      }

   //   }

   //   try
   //   {

   //      Gdiplus::Bitmap * pdraw2dbitmap = (Gdiplus::Bitmap *) pgraphicsSrc->get_current_bitmap()->get_os_data();

   //      //if(m_pgdiplusgraphics->GetInterpolationMode() == Gdiplus::InterpolationModeLowQuality
   //      //      && m_pgdiplusgraphics->GetCompositingMode() == Gdiplus::CompositingModeSourceCopy)
   //      //{

   //      //   m_pgdiplusgraphics->SetCompositingQuality(Gdiplus::CompositingQualityHighSpeed);
   //      //   m_pgdiplusgraphics->SetInterpolationMode(Gdiplus::InterpolationModeLowQuality);
   //      //   m_pgdiplusgraphics->SetSmoothingMode(Gdiplus::SmoothingModeNone);
   //      //   m_pgdiplusgraphics->SetPixelOffsetMode(Gdiplus::PixelOffsetModeHighSpeed);

   //      //}

   //      if (pgraphicsSrc->m_pimage->is_ok() && pgraphicsSrc->m_pimage->m_bColorMatrix)
   //      {

   //         Gdiplus::ImageAttributes imageattributes;

   //         Gdiplus::ColorMatrix colormatrix;

   //         copy_color_matrix(colormatrix.m, pgraphicsSrc->m_pimage->m_colormatrix.a);

   //         imageattributes.SetColorMatrix(
   //         &colormatrix,
   //         ColorMatrixFlagsDefault,
   //         ColorAdjustTypeBitmap);

   //         ret = m_pgdiplusgraphics->DrawImage(pdraw2dbitmap, rectangleTarget, xSrc, ySrc, nSrcWidth, nSrcHeight, Gdiplus::UnitPixel, &imageattributes);

   //      }
   //      else
   //      {

   //         if (rectangleTarget.Width == nSrcWidth && rectangleTarget.Height == nSrcHeight)
   //         {

   //            ret = m_pgdiplusgraphics->DrawImage(pdraw2dbitmap, rectangleTarget.X, rectangleTarget.Y, xSrc, ySrc, nSrcWidth, nSrcHeight, Gdiplus::UnitPixel);

   //         }
   //         else
   //         {

   //            ret = m_pgdiplusgraphics->DrawImage(pdraw2dbitmap, rectangleTarget, xSrc, ySrc, nSrcWidth, nSrcHeight, Gdiplus::UnitPixel);

   //         }

   //      }

   //      if (ret != Gdiplus::Status::Ok)
   //      {

   //         return false;

   //      }

   //   }
   //   catch (...)
   //   {

   //      return false;

   //   }

   //   return true;

   //}




   ::color::color graphics::GetPixel(::f64 x, ::f64 y)
   {
      //ASSERT(get_handle1() != nullptr);
      //return ::GetPixel(get_handle1(), x, y);
      throw ::not_implemented();

      return {};

   }


   ::color::color graphics::GetPixel(const ::f64_point & point)
   {
      //ASSERT(get_handle1() != nullptr);
      //return ::GetPixel(get_handle1(), point.x, point.y);
      throw ::not_implemented();

      return color::transparent;

   }


   ::color::color graphics::SetPixel(::f64 x, ::f64 y, const ::color::color & color)
   {

      return color::transparent;

   }


   ::color::color graphics::SetPixel(const ::f64_point & point, const ::color::color & color)
   {

      if (m_pimageTarget->is_ok())
      {

         auto ppixmapImage = m_pimageTarget->map();

         ppixmapImage->set_pixel((::i32)point.x, (::i32)point.y, color);

      }
      else
      {

         fill_rectangle(::f64_rectangle_dimension(point.x, point.y, 1. , 1.), color);

      }

      return color;

   }


   ::color::color graphics::blend_pixel(const ::f64_point & point, const ::color::color & colorChange)
   {

      if (m_pimageTarget->is_ok())
      {

         auto ppixmapImage = m_pimageTarget->map();

         ::color::color color = ppixmapImage->get_pixel((::i32)point.x, (::i32)point.y);

         color.m_u8Red = (::i32)(color.m_u8Red * (1.0 - colorChange.f64_opacity()) + colorChange.m_u8Red * colorChange.f64_opacity());
         color.m_u8Green = (::i32)(color.m_u8Green * (1.0 - colorChange.f64_opacity()) + colorChange.m_u8Green * colorChange.f64_opacity());
         color.m_u8Blue = (::i32)(color.m_u8Blue * (1.0 - colorChange.f64_opacity()) + colorChange.m_u8Blue * colorChange.f64_opacity());

         ppixmapImage->set_pixel((::i32)point.x, (::i32)point.y, color);
         //colorCurrent.m_iA = colorCurrent.m_iA * (1.0 - color.da()) + color.m_iR * color.da();

      }
      else
      {

         fill_rectangle(::f64_rectangle_dimension(point.x, point.y, 1., 1.), colorChange);

      }

      return colorChange;

   }


   //void graphics::FloodFill(::f64 x, ::f64 y, const ::color::color & color)
   //{

   //   //ASSERT(get_handle1() != nullptr);

   //   //return ::FloodFill(get_handle1(), x, y, color) != false;
   //   throw ::not_implemented();

   //   return false;

   //}


   //void graphics::ExtFloodFill(::f64 x, ::f64 y, const ::color::color & color, UINT nFillType)
   //{
   //   //ASSERT(get_handle1() != nullptr);
   //   //return ::ExtFloodFill(get_handle1(), x, y, color, nFillType) != false;
   //   throw ::not_implemented();

   //   return false;

   //}


   // true blend
   // COLOR_DEST = SRC_ALPHA * COLOR_SRC  + (1 - SRC_ALPHA) * COLOR_DST

   // ::f64 blend
   //// COLOR_DEST = SRC_ALPHA * BLEND_ALPHA * COLOR_SRC  + (1 - SRC_ALPHA * BLEND_ALPHA) * COLOR_DST


   //void graphics::ExtTextOut(::f64 x, ::f64 y,UINT nOptions,const ::f64_rectangle &  rectangleParam, const ::scoped_string & scopedstrString,character_count nCount,LPINT lpDxWidths)
   //{

   //   //ASSERT(get_handle1() != nullptr);

   //   //return ::ExtTextOut(get_handle1(),x,y,nOptions,&rectangleParam,pszString,(UINT) nCount,lpDxWidths) != false;
   //   throw ::not_implemented();

   //   return false;


   //}


   //void graphics::ExtTextOut(::f64 x, ::f64 y,UINT nOptions,const ::f64_rectangle &  rectangleParam, const ::scoped_string & scopedstr, LPINT pDxWidths)
   //{

   //   //ASSERT(get_handle1() != nullptr);

   //   //return ::ExtTextOut(get_handle1(),x,y,nOptions,&rectangleParam, str, (UINT)str.length(), pDxWidths) != false;
   //   throw ::not_implemented();

   //   return false;


   //}


   //::f64_size graphics::TabbedTextOut(::f64 x, ::f64 y, const ::scoped_string & scopedstrString, character_count nCount, ::collection::count nTabPositions, LPINT lpnTabStopPositions, ::i32 nTabOrigin)
   //{

   //   //ASSERT(get_handle1() != nullptr);

   //   //return ::TabbedTextOut(get_handle1(), x, y, pszString, (::i32) nCount, (::i32) nTabPositions, lpnTabStopPositions, nTabOrigin);

   //   throw ::not_implemented();

   //   return nullptr;

   //}


   //::f64_size graphics::TabbedTextOut(::f64 x, ::f64 y, const ::scoped_string & scopedstr, ::collection::count nTabPositions, LPINT pnTabStopPositions, ::i32 nTabOrigin)
   //{

   //   //ASSERT(get_handle1() != nullptr);

   //   //return ::TabbedTextOut(get_handle1(), x, y, str, (::i32)str.length(), (::i32) nTabPositions, pnTabStopPositions, nTabOrigin);

   //   throw ::not_implemented();

   //   return nullptr;

   //}


   //::f64_size graphics::GetTabbedTextExtent(const ::scoped_string & scopedstrString, character_count nCount, ::collection::count nTabPositions, LPINT lpnTabStopPositions)
   //{

   //   //ASSERT(get_handle2() != nullptr);

   //   //return ::GetTabbedTextExtent(get_handle2(), pszString, (::i32) nCount, (::i32) nTabPositions, lpnTabStopPositions);
   //   throw ::not_implemented();

   //   return nullptr;


   //}


   //::f64_size graphics::GetTabbedTextExtent(const ::scoped_string & scopedstr, ::collection::count nTabPositions, LPINT pnTabStopPositions)
   //{

   //   //ASSERT(get_handle2() != nullptr);

   //   //return ::GetTabbedTextExtent(get_handle2(), str, (::i32) str.length(), (::i32) nTabPositions, pnTabStopPositions);

   //   throw ::not_implemented();

   //   return nullptr;

   //}


   //::f64_size graphics::GetOutputTabbedTextExtent(const ::scoped_string & scopedstrString, character_count nCount, ::collection::count nTabPositions, LPINT lpnTabStopPositions)
   //{

   //   //ASSERT(get_handle1() != nullptr);

   //   //return ::GetTabbedTextExtent(get_handle1(), pszString, (::i32) nCount, (::i32) nTabPositions, lpnTabStopPositions);

   //   throw ::not_implemented();

   //   return nullptr;

   //}


   //::f64_size graphics::GetOutputTabbedTextExtent(const ::scoped_string & scopedstr, ::collection::count nTabPositions, LPINT pnTabStopPositions)
   //{

   //   //ASSERT(get_handle1() != nullptr);

   //   //return ::GetTabbedTextExtent(get_handle1(), str, (::i32) str.length(), (::i32) nTabPositions, pnTabStopPositions);

   //   throw ::not_implemented();

   //   return nullptr;
   //}


   //void graphics::GrayString(::draw2d::brush* pBrush, bool (CALLBACK* pfnOutput)(HDC, LPARAM, ::i32), LPARAM lpData, ::i32 nCount,::f64 x, ::f64 y, ::f64 nWidth, ::f64 nHeight)

   //{

   //   //ASSERT(get_handle1() != nullptr);

   //   //return ::GrayString(get_handle1(), (HBRUSH)pBrush->get_os_data(),(GRAYSTRINGPROC)pfnOutput, lpData, nCount, x, y, nWidth, nHeight) != false;
   //   throw ::not_implemented();

   //   return false;

   //}


   UINT graphics::GetTextAlign()
   {

      //ASSERT(get_handle2() != nullptr);

      //return ::GetTextAlign(get_handle2());
      throw ::not_implemented();

      return -1;
   }


   //::i32 graphics::GetTextFace(::collection::count nCount, LPTSTR pszFacename)

   //{

   //   //ASSERT(get_handle2() != nullptr);

   //   //return ::GetTextFace(get_handle2(), (::i32) nCount, pszFacename);
   //   throw ::not_implemented();

   //   return -1;

   //}


   //::i32 graphics::GetTextFace(string & rString)
   //{

   //   //ASSERT(get_handle2() != nullptr);

   //   //::i32 nResult = ::GetTextFace(get_handle2(), 256, rString.GetBuffer(256));
   //   //rString.ReleaseBuffer();

   //   //return nResult;
   //   throw ::not_implemented();

   //   return -1;
   //}


   void graphics::get_text_metrics(::write_text::text_metric * pmetric)
   {

      if (m_pgdiplusgraphics == nullptr)
      {

         //return false;

         throw ::exception(error_null_pointer);

      }

      if (m_pwritetextfont == nullptr)
      {

         //return false;

         throw ::exception(error_null_pointer);

      }

      if (m_bTargetRectangleModified)
      {

         defer_on_target_rectangle_update();

      }

      m_pwritetextfont->defer_update(this);

      ::cast < ::draw2d_gdiplus::font > pdraw2dgdiplusfont = m_pwritetextfont;

      Gdiplus::Font * pgdiplusfont = pdraw2dgdiplusfont->m_pgdiplusfont;

      if (::is_null(pgdiplusfont))
      {

         throw ::exception(error_null_pointer);

      }

      Gdiplus::FontFamily * pgdiplusfontfamily = pdraw2dgdiplusfont->m_pgdiplusfontfamily;

      if (pgdiplusfontfamily == nullptr)
      {

         //return false;

         throw ::exception(error_null_pointer);

      }

      INT iStyle = pgdiplusfont->GetStyle();

      //Gdiplus::FontFamily family;

      //pwritetextfont->GetFamily(&family);

      ::f64 dEmHeight = pgdiplusfontfamily->GetEmHeight(iStyle);

      ::f64 dCellAscent = pgdiplusfontfamily->GetCellAscent(iStyle);

      ::f64 dCellDescent = pgdiplusfontfamily->GetCellDescent(iStyle);

      ::f64 dLineSpacing = pgdiplusfontfamily->GetLineSpacing(iStyle);

      ::f64 dFontSize = pgdiplusfont->GetSize();

      //auto pg = (Gdiplus::Graphics*)pdraw2dgraphics->get_os_data();

      ::f64 dFontHeight = pgdiplusfont->GetHeight(m_pgdiplusgraphics);

      auto dpiY = m_pgdiplusgraphics->GetDpiY();
      //m_pgdiplusgraphics->DrawLine(m_pdraw2dpen->get_os_data < Gdiplus::Pen* >(this), Gdiplus::PointF((Gdiplus::REAL)m_point.x, (Gdiplus::REAL)m_point.y), Gdiplus::PointF((Gdiplus::REAL)x, (Gdiplus::REAL)y));
      pmetric->m_dAscent = dFontSize * dCellAscent * dpiY / (dEmHeight * 72.0 + 0.5);

      pmetric->m_dDescent = dFontSize * dCellDescent * dpiY / (dEmHeight * 72.0 + 0.5);

      pmetric->m_dHeight = dFontHeight;

      ::f64 dLineSpacing2 = maximum(dFontHeight, dFontSize * dLineSpacing * dpiY / (dEmHeight *72.0 + 0.5));

      pmetric->m_dInternalLeading = 0;

      pmetric->m_dExternalLeading = dLineSpacing2 - (pmetric->m_dAscent + pmetric->m_dDescent);

      //return true;

   }


   void graphics::get_output_text_metrics(::write_text::text_metric * pmetric)

   {

      //ASSERT(get_handle1() != nullptr);

      //return ::GetTextMetricsW(get_handle1(), pmetric) != false;


      throw ::interface_only();

      //return false;

   }


   //::i32 graphics::GetTextCharacterExtra()
   //{
   //   //ASSERT(get_handle2() != nullptr);
   //   //return ::GetTextCharacterExtra(get_handle2());
   //   throw ::not_implemented();

   //   return -1;
   //}
   //void graphics::GetCharWidth(UINT nFirstChar, UINT nLastChar, LPINT pBuffer)

   //{
   //   //ASSERT(get_handle2() != nullptr);
   //   //return ::GetCharWidth(get_handle2(), nFirstChar, nLastChar, pBuffer) != false;
   //   throw ::not_implemented();

   //   return false;
   //}
   //void graphics::GetOutputCharWidth(UINT nFirstChar, UINT nLastChar, LPINT pBuffer)

   //{
   //   //ASSERT(get_handle1() != nullptr);
   //   //return ::GetCharWidth(get_handle1(), nFirstChar, nLastChar, pBuffer) != false;
   //   throw ::not_implemented();

   //   return false;
   //}
   //::u32 graphics::GetFontLanguageInfo()
   //{
   //   //ASSERT(get_handle1() != nullptr);
   //   //return ::GetFontLanguageInfo(get_handle1());
   //   throw ::not_implemented();

   //   return -1;
   //}


   //::u32 graphics::GetCharacterPlacement(const ::scoped_string & scopedstrString, character_count nCount, character_count nMaxExtent, LPGCP_RESULTS lpResults, ::u32 dwFlags)

   //{

   //   //ASSERT(get_handle1() != nullptr);

   //   //return ::GetCharacterPlacement(get_handle1(), pString, (::i32) nCount, (::i32) nMaxExtent, lpResults, dwFlags);
   //   throw ::not_implemented();

   //   return -1;

   //}


   //::u32 graphics::GetCharacterPlacement(string & str, character_count nMaxExtent, LPGCP_RESULTS pResults, ::u32 dwFlags)

   //{

   //   //ASSERT(get_handle1() != nullptr);

   //   //return ::GetCharacterPlacement(get_handle1(), (const ::string &)str, (::i32) str.length(), (::i32) nMaxExtent, pResults, dwFlags);
   //   throw ::not_implemented();

   //   return -1;

   //}


   //::f64_size graphics::GetAspectRatioFilter()
   //{
   //   //ASSERT(get_handle2() != nullptr);
   //   //::f64_size ::f64_size;
   //   //VERIFY(::GetAspectRatioFilterEx(get_handle2(), &::f64_size));
   //   //return ::f64_size;
   //   throw ::not_implemented();

   //   return nullptr;
   //}
   //void graphics::ScrollDC(::i32 dx, ::i32 dy,
   //                        const i32_rectangle &  pRectScroll,const i32_rectangle &  rectangleClip,

   //                        ::draw2d::region* pRgnUpdate, RECT * pRectUpdate)

   //{
   //   //ASSERT(get_handle1() != nullptr);
   //   //return ::ScrollDC(get_handle1(),dx,dy,&rectangleClip,
   //   //                  &rectangleClip, (HRGN)pRgnUpdate->get_os_data(), pRectUpdate) != false;

   //   throw ::not_implemented();

   //   return false;
   //}

   //// Printer Escape Functions
   //::i32 graphics::Escape(::i32 nEscape, ::i32 nCount, const ::scoped_string & scopedstrInData, LPVOID lpOutData)

   //{
   //   //ASSERT(get_handle1() != nullptr);
   //   //return ::Escape(get_handle1(), nEscape, nCount, pszInData, lpOutData);
   //   throw ::not_implemented();

   //   return -1;
   //}

   // graphics 3.1 Specific functions
   UINT graphics::SetBoundsRect(const ::f64_rectangle & rectangleBounds, UINT flags)
   {
      //ASSERT(get_handle1() != nullptr);
      //return ::SetBoundsRect(get_handle1(), &rectangleBounds, flags);
      throw ::not_implemented();

      return -1;
   }


   UINT graphics::GetBoundsRect(::f64_rectangle * pRectBounds, UINT flags)
   {

      //ASSERT(get_handle2() != nullptr);
      //return ::GetBoundsRect(get_handle2(), pRectBounds, flags);
      throw ::not_implemented();

      return -1;
   }


   //void graphics::ResetDC(const DEVMODE* pDevMode)
   //{

   //   //ASSERT(get_handle2() != nullptr);
   //   //return ::ResetDC(get_handle2(), pDevMode) != nullptr;
   //   throw ::not_implemented();

   //   return false;
   //}


   //UINT graphics::GetOutlineTextMetrics(UINT cbData, LPOUTLINETEXTMETRICW potm)
   //{

   //   //ASSERT(get_handle2() != nullptr);
   //   //return ::GetOutlineTextMetricsW(get_handle2(), cbData, potm);
   //   throw ::not_implemented();

   //   return -1;
   //}


   //void graphics::GetCharABCWidths(UINT nFirstChar, UINT nLastChar, LPABC pabc)

   //{
   //   //ASSERT(get_handle2() != nullptr);
   //   //return ::GetCharABCWidths(get_handle2(), nFirstChar, nLastChar, pabc) != false;
   //   throw ::not_implemented();

   //   return false;
   //}
   //::u32 graphics::GetFontData(::u32 dwTable, ::u32 dwOffset, LPVOID pData,

   //                          ::u32 cbData)
   //{
   //   //ASSERT(get_handle2() != nullptr);
   //   //return ::GetFontData(get_handle2(), dwTable, dwOffset, pData, cbData);
   //   throw ::not_implemented();

   //   return -1;
   //}
   //::i32 graphics::GetKerningPairs(::i32 nPairs, LPKERNINGPAIR pkrnpair)

   //{
   //   //ASSERT(get_handle2() != nullptr);
   //   //return ::GetKerningPairs(get_handle2(), nPairs, pkrnpair);
   //   throw ::not_implemented();

   //   return -1;
   //}
   //::u32 graphics::GetGlyphOutline(UINT nChar, const ::e_align & ealign, const ::e_draw_text & edrawtext, LPGLYPHMETRICS pgm,

   //                              ::u32 cbBuffer, LPVOID pBuffer, const MAT2* lpmat2)

   //{
   //   //ASSERT(get_handle2() != nullptr);
   //   //return ::GetGlyphOutline(get_handle2(), nChar, nFormat,
   //   //                         pgm, cbBuffer, lpBuffer, lpmat2);
   //   throw ::not_implemented();

   //   return -1;
   //}

   //// ::user::document handling functions
   //::i32 graphics::StartDoc(LPDOCINFO pDocInfo)

   //{

   //   //ASSERT(m_hdc != nullptr);

   //   //return ::StartDoc(m_hdc, pDocInfo);

   //   throw ::not_implemented();

   //   return -1;
   //}


   ::i32 graphics::StartPage()
   {

      ASSERT(m_hdc != nullptr);

      ::StartPage(m_hdc);

      m_pgdiplusgraphics = ::as_pointer(new Gdiplus::Graphics(m_hdc));

      m_pgdiplusgraphics->SetPageUnit(Gdiplus::UnitPixel);

      set_text_rendering_hint(::write_text::e_rendering_system_default);

      set_smooth_mode(::draw2d::e_smooth_mode_anti_alias_8x8);

      return 1;

   }


   ::i32 graphics::EndPage()
   {

      ASSERT(m_hdc != nullptr);

      m_pgdiplusgraphics.destroy();

      return ::EndPage(m_hdc);

   }


   //::i32 graphics::SetAbortProc(bool (CALLBACK* pfn)(HDC, ::i32))

   //{

   //   ASSERT(m_hdc != nullptr);

   //   return ::SetAbortProc(m_hdc, (ABORTPROC)pfn);


   //}


   ::i32 graphics::AbortDoc()
   {

      ASSERT(m_hdc != nullptr);

      return ::AbortDoc(m_hdc);

   }


   ::i32 graphics::EndDoc()
   {

      ASSERT(m_hdc != nullptr);

      return ::EndDoc(m_hdc);

   }


   //void graphics::MaskBlt(::f64 x, ::f64 y, ::f64 nWidth, ::f64 nHeight, ::draw2d::graphics * pgraphicsSrc,
   //                       ::f64 xSrc, ::i32 ySrc, ::draw2d::bitmap& maskBitmap, ::f64 xMask, ::i32 yMask, ::u32 dwRop)
   //{
   //   //ASSERT(get_handle1() != nullptr);
   //   //return ::MaskBlt(get_handle1(), x, y, nWidth, nHeight, GDIPLUS_HDC(pgraphicsSrc),
   //   //                 xSrc, ySrc,  (HBITMAP)maskBitmap.get_os_data(), xMask, yMask, dwRop) != false;
   //   throw ::not_implemented();

   //   return false;

   //}


   //void graphics::PlgBlt(LPPOINT pPoint, ::draw2d::graphics * pgraphicsSrc, ::f64 xSrc, ::i32 ySrc,

   //                      ::f64 nWidth, ::f64 nHeight, ::draw2d::bitmap& maskBitmap, ::f64 xMask, ::i32 yMask)
   //{

   //   Gdiplus::Status ret = Gdiplus::Status::GenericError;

   //   try
   //   {

   //      if(pgraphicsSrc == nullptr)
   //         return false;

   //      if(pgraphicsSrc->get_current_bitmap() == nullptr)
   //         return false;

   //      if(pgraphicsSrc->get_current_bitmap()->nok())
   //         return false;

   //      Gdiplus::Point i32_point[3];

   //      i32_point[0].X = pPoint[0].x;

   //      i32_point[0].Y = pPoint[0].y;

   //      i32_point[1].X = pPoint[1].x;

   //      i32_point[1].Y = pPoint[1].y;

   //      i32_point[2].X = pPoint[2].x;

   //      i32_point[2].Y = pPoint[2].y;


   //      ret = m_pgdiplusgraphics->DrawImage((Gdiplus::Bitmap *) pgraphicsSrc->get_current_bitmap()->get_os_data(), point, 3);

   //      if (ret != Gdiplus::Status::Ok)
   //      {

   //         return false;

   //      }

   //   }
   //   catch(...)
   //   {

   //      return false;

   //   }

   //   return true;

   //}



   //void graphics::SetPixelV(::f64 x, ::f64 y, const ::color::color & color)
   //{
   //   //ASSERT(get_handle1() != nullptr);
   //   //return ::SetPixelV(get_handle1(), x, y, color) != false;
   //   throw ::not_implemented();

   //   return false;

   //}
   //
   //
   //void graphics::SetPixelV(const ::f64_point & point, const ::color::color & color)
   //{
   //   //ASSERT(get_handle1() != nullptr);
   //   //return ::SetPixelV(get_handle1(), point.x, point.y, color) != false;
   //   throw ::not_implemented();

   //   return false;

   //}

   void graphics::angle_arc(::f64 x, ::f64 y, ::f64 nRadius, ::f64_angle fStartAngle, ::f64_angle fSweepAngle)
   {
      //   //ASSERT(get_handle1() != nullptr);
      //   //return ::AngleArc(get_handle1(), x, y, nRadius, fStartAngle, fSweepAngle) != false;
      //   throw ::not_implemented();

         //return false;

   }


   void graphics::arc_to(const ::f64_rectangle & rectangleParam, const ::f64_point & pointStart, const ::f64_point & pointEnd)
   {
      ////      ASSERT(get_handle1() != nullptr);
            //return ArcTo(rectangleParam.left, rectangleParam.top, rectangleParam.right,
              //           rectangleParam.bottom, pointStart.x, pointStart.y, pointEnd.x, pointEnd.y);
               //   if (::is_null(m_pgdiplusgraphics))
         //   {

         //      return false;

         //   }

         //   //ASSERT(get_handle1() != nullptr);
         //   //bool bResult = ::ArcTo(get_handle1(), x1, y1, x2, y2, x3, y3, x4, y4) != false;
         //   //if (get_handle1() != get_handle2())
         //   //{
         //   //   ::i32_point point;
         //   //   VERIFY(::GetCurrentPositionEx(get_handle1(), &point));
         //   //   VERIFY(::MoveToEx(get_handle2(), point.x, point.y, nullptr));
         //   //}
         //   //return bResult;
         //   throw ::not_implemented();

            //return false;
   }
   //::i32 graphics::GetArcDirection()
   //{
   //   //ASSERT(get_handle2() != nullptr);
   //   //return ::GetArcDirection(get_handle2());
   //   throw ::not_implemented();

   //   return -1;

   //}


   void graphics::poly_polyline(const ::f64_point * pPoints, const INT * lpPolyPoints, ::collection::count nCount)
   {

      //ASSERT(get_handle1() != nullptr);

      //return ::poly_polyline(get_handle1(), pPoints, (LPDWORD) lpPolyPoints, (DWORD) nCount) != false;

      throw ::not_implemented();

      //return false;

   }


   //void graphics::GetColorAdjustment(LPCOLORADJUSTMENT pColorAdjust)

   //{
   //   //ASSERT(get_handle2() != nullptr);
   //   //return ::GetColorAdjustment(get_handle2(), pColorAdjust) != false;
   //   throw ::not_implemented();

   //   return false;

   //}


   void graphics::poly_bezier(const ::f64_point * pPoints, ::collection::count nCount)
   {

      //ASSERT(get_handle1() != nullptr);

      //return ::poly_bezier(get_handle1(), pPoints, (DWORD) nCount) != false;
      throw ::not_implemented();

      //return false;


   }


   //::i32 graphics::DrawEscape(::i32 nEscape, ::i32 nInputSize, const ::scoped_string & scopedstrInputData)

   //{

   //   //ASSERT(get_handle1() != nullptr);

   //   //return ::DrawEscape(get_handle1(), nEscape, nInputSize, pszInputData);
   //   throw ::not_implemented();

   //   return false;


   //}


   //::i32 graphics::Escape(::i32 nEscape, ::i32 nInputSize, const ::scoped_string & scopedstrInputData,  ::i32 nOutputSize, ::i8 * pszOutputData)

   //{

   //   //ASSERT(get_handle1() != nullptr);

   //   //return ::ExtEscape(get_handle1(), nEscape, nInputSize, pszInputData, nOutputSize, pszOutputData);
   //   throw ::not_implemented();

   //   return false;


   //}


   //void graphics::GetCharABCWidths(UINT nFirstChar, UINT nLastChar,
   //                                LPABCFLOAT pABCF)

   //{
   //   //ASSERT(get_handle2() != nullptr);
   //   //return ::GetCharABCWidthsFloat(get_handle2(), nFirstChar, nLastChar, pABCF) != false;
   //   throw ::not_implemented();

   //   return false;

   //}
   //void graphics::GetCharWidth(UINT nFirstChar, UINT nLastChar, ::f32* pFloatBuffer)

   //{
   //   //ASSERT(get_handle2() != nullptr);
   //   //return ::GetCharWidthFloat(get_handle2(), nFirstChar, nLastChar, pFloatBuffer) != false;
   //   throw ::not_implemented();

   //   return false;

   //}


   void graphics::abort_path()
   {

      if (m_pgdiplusgraphicspath != nullptr)
      {

         m_pgdiplusgraphicspath.destroy();

      }

      //return true;

   }


   void graphics::begin_path()
   {

      if (m_pgdiplusgraphicspath != nullptr)
      {

         m_pgdiplusgraphicspath.destroy();

      }

      m_pgdiplusgraphicspath = ::as_pointer(new Gdiplus::GraphicsPath);

      //return m_pgdiplusgraphicspath != nullptr;

   }


   void graphics::close_figure()
   {

      ASSERT(m_pgdiplusgraphicspath != nullptr);

      if (m_pgdiplusgraphicspath->CloseFigure() != Gdiplus::Status::Ok)
      {

         throw ::exception(error_null_pointer);

      }

   }


   void graphics::end_path()
   {

      if (m_pgdiplusgraphicspath == nullptr)
      {

         //return false;

         throw ::exception(error_null_pointer);

      }

      m_pgdiplusgraphicspathPaint = ::transfer(m_pgdiplusgraphicspath);

      //return true;

   }


   void graphics::fill_path()
   {

      if (m_bTargetRectangleModified)
      {

         defer_on_target_rectangle_update();

      }

      m_pdraw2dbrush->defer_update(this);

      ::cast < ::draw2d_gdiplus::brush>pdraw2dgdiplusbrush = m_pdraw2dbrush;

      auto pgdiplusbrush = pdraw2dgdiplusbrush->m_pgdiplusbrush;

      if (m_pgdiplusgraphics->FillPath(pgdiplusbrush, m_pgdiplusgraphicspath) != Gdiplus::Status::Ok)
      {


         throw ::exception(error_null_pointer);

      }

   }


   void graphics::flatten_path()
   {

      if (m_pgdiplusgraphicspath->Flatten() != Gdiplus::Status::Ok)
      {

         throw ::exception(error_null_pointer);

      }

   }


   ::f32 graphics::GetMiterLimit()
   {
      //ASSERT(get_handle1() != nullptr);
      //::f32 fMiterLimit;
      //VERIFY(::GetMiterLimit(get_handle1(), &fMiterLimit));
      //return fMiterLimit;
      throw ::not_implemented();

      return 0.f;

   }


   //::i32 graphics::GetPath(::f64_point * pPoints, ::u8 * lpTypes, ::collection::count nCount)

   //{

   //   //ASSERT(get_handle1() != nullptr);

   //   //return ::GetPath(get_handle1(), pPoints, lpTypes, (::i32) nCount);

   //   throw ::not_implemented();

   //   return false;

   //}

   void graphics::SetMiterLimit(::f32 fMiterLimit)
   {
      //ASSERT(get_handle1() != nullptr);
      //return ::SetMiterLimit(get_handle1(), fMiterLimit, nullptr) != false;
      throw ::not_implemented();

      //return false;

   }


   void graphics::stroke_and_fill_path()
   {

      if (m_bTargetRectangleModified)
      {

         defer_on_target_rectangle_update();

      }

      m_pdraw2dpen->defer_update(this);

      ::cast < ::draw2d_gdiplus::pen>pdraw2dgdipluspen = m_pdraw2dpen;

      auto pgdipluspen = pdraw2dgdipluspen->m_pgdipluspen;

      m_pdraw2dbrush->defer_update(this);

      ::cast < ::draw2d_gdiplus::brush>pdraw2dgdiplusbrush = m_pdraw2dbrush;

      auto pgdiplusbrush = pdraw2dgdiplusbrush->m_pgdiplusbrush;

      bool bOk1 = m_pgdiplusgraphics->FillPath(pgdiplusbrush, m_pgdiplusgraphicspathPaint) == Gdiplus::Status::Ok;

      bool bOk2 = m_pgdiplusgraphics->DrawPath(pgdipluspen, m_pgdiplusgraphicspathPaint) == Gdiplus::Status::Ok;

      //return bOk1 && bOk2;

   }


   void graphics::stroke_path()
   {

      if (m_bTargetRectangleModified)
      {

         defer_on_target_rectangle_update();

      }

      m_pdraw2dpen->defer_update(this);

      ::cast < ::draw2d_gdiplus::pen>pdraw2dgdipluspen = m_pdraw2dpen;

      auto pgdipluspen = pdraw2dgdipluspen->m_pgdipluspen;

      bool bOk = m_pgdiplusgraphics->DrawPath(pgdipluspen, m_pgdiplusgraphicspathPaint) == Gdiplus::Status::Ok;

   }


   void graphics::widen_path()
   {

      if (m_bTargetRectangleModified)
      {

         defer_on_target_rectangle_update();

      }

      m_pdraw2dpen->defer_update(this);

      ::cast < ::draw2d_gdiplus::pen>pdraw2dgdipluspen = m_pdraw2dpen;

      auto pgdipluspen = pdraw2dgdipluspen->m_pgdipluspen;

      bool bOk = m_pgdiplusgraphicspath->Widen(pgdipluspen) == Gdiplus::Status::Ok;

   }


   void graphics::draw(::draw2d::path * pdraw2dpath)
   {

      if (m_bTargetRectangleModified)
      {

         defer_on_target_rectangle_update();

      }

      //m_pgdiplusgraphics->SetSmoothingMode(Gdiplus::SmoothingModeAntiAlias8x8);
      //m_pgdiplusgraphics->SetCompositingQuality(Gdiplus::CompositingQualityGammaCorrected);
      //m_pgdiplusgraphics->SetInterpolationMode(Gdiplus::InterpolationModeHighQualityBicubic);

      m_pdraw2dpen->defer_update(this);

      ::cast < ::draw2d_gdiplus::pen>pdraw2dgdipluspen = m_pdraw2dpen;

      auto pgdipluspen = pdraw2dgdipluspen->m_pgdipluspen;

      if (::is_null(pgdipluspen))
      {

         throw exception(error_null_pointer);

      }

      pdraw2dpath->defer_update(this);

      ::cast < ::draw2d_gdiplus::path > pdraw2dgdipluspath = pdraw2dpath;

      auto pgdiplusgraphicspath = pdraw2dgdipluspath->m_pgdiplusgraphicspath;

      if (::is_null(pgdiplusgraphicspath))
      {

         throw exception(error_null_pointer);

      }

      bool bOk = m_pgdiplusgraphics->DrawPath(pgdipluspen, pgdiplusgraphicspath) == Gdiplus::Status::Ok;

   }


   void graphics::draw(::draw2d::path * pdraw2dpath, ::draw2d::pen * pdraw2dpen)
   {

      if (m_bTargetRectangleModified)
      {

         defer_on_target_rectangle_update();

      }

      pdraw2dpath->defer_update(this);

      ::cast < ::draw2d_gdiplus::path > pdraw2dgdipluspath = pdraw2dpath;

      auto pgdiplusgraphicspath = pdraw2dgdipluspath->m_pgdiplusgraphicspath;

      if (::is_null(pgdiplusgraphicspath))
      {

         throw ::exception(error_wrong_state);

      }

      pdraw2dpen->defer_update(this);

      ::cast < ::draw2d_gdiplus::pen>pdraw2dgdipluspen = pdraw2dpen;

      auto pgdipluspen = pdraw2dgdipluspen->m_pgdipluspen;

      if (::is_null(pdraw2dgdipluspen))
      {

         throw ::exception(error_wrong_state);

      }

      bool bOk = m_pgdiplusgraphics->DrawPath(pgdipluspen, pgdiplusgraphicspath) == Gdiplus::Status::Ok;

   }


   void graphics::fill(::draw2d::path * pdraw2dpath)
   {

      if (m_bTargetRectangleModified)
      {

         defer_on_target_rectangle_update();

      }

      m_pdraw2dbrush->defer_update(this);

      ::cast < ::draw2d_gdiplus::brush>pdraw2dgdiplusbrush = m_pdraw2dbrush;

      auto pgdiplusbrush = pdraw2dgdiplusbrush->m_pgdiplusbrush;

      if (::is_null(pgdiplusbrush))
      {

         return;

      }

      pdraw2dpath->defer_update(this);

      ::cast < ::draw2d_gdiplus::path > pdraw2dgdipluspath = pdraw2dpath;

      auto pgdiplusgraphicspath = pdraw2dgdipluspath->m_pgdiplusgraphicspath;

      if (::is_null(pgdiplusgraphicspath))
      {

         throw ::exception(error_wrong_state);

      }

      bool bOk = m_pgdiplusgraphics->FillPath(pgdiplusbrush, pgdiplusgraphicspath) == Gdiplus::Status::Ok;

   }


   void graphics::fill(::draw2d::path * pdraw2dpath, ::draw2d::brush * pdraw2dbrush)
   {

      if (pdraw2dpath == nullptr)
      {

         throw ::exception(error_null_pointer);

      }

      if (pdraw2dbrush == nullptr)
      {

         throw ::exception(error_null_pointer);

      }

      if (m_pgdiplusgraphics == nullptr)
      {

         throw ::exception(error_null_pointer);

      }

      if (m_bTargetRectangleModified)
      {

         defer_on_target_rectangle_update();

      }

      pdraw2dbrush->defer_update(this);

      ::cast < ::draw2d_gdiplus::brush>pdraw2dgdiplusbrush = pdraw2dbrush;

      auto pgdiplusbrush = pdraw2dgdiplusbrush->m_pgdiplusbrush;

      if (::is_null(pgdiplusbrush))
      {

         throw ::exception(error_wrong_state);

      }

      pdraw2dpath->defer_update(this);

      ::cast < ::draw2d_gdiplus::path > pdraw2dgdipluspath = pdraw2dpath;

      auto pgdiplusgraphicspath = pdraw2dgdipluspath->m_pgdiplusgraphicspath;

      if (::is_null(pgdiplusgraphicspath))
      {

         throw ::exception(error_wrong_state);

      }

      bool bOk = m_pgdiplusgraphics->FillPath(pgdiplusbrush, pgdiplusgraphicspath) == Gdiplus::Status::Ok;

   }


   void graphics::intersect_clip(::draw2d::path * pdraw2dpath)
   {

      if (pdraw2dpath == nullptr)
      {

         throw ::exception(error_null_pointer);

      }

      if (m_pgdiplusgraphics == nullptr)
      {

         throw ::exception(error_null_pointer);

      }

      pdraw2dpath->defer_update(this);

      ::cast < ::draw2d_gdiplus::path > pdraw2dgdipluspath = pdraw2dpath;

      auto pgdiplusgraphicspath = pdraw2dgdipluspath->m_pgdiplusgraphicspath;

      if (::is_null(pgdiplusgraphicspath))
      {

         throw ::exception(error_wrong_state);

      }

      bool bOk = m_pgdiplusgraphics->SetClip(pgdiplusgraphicspath, Gdiplus::CombineModeIntersect) == Gdiplus::Status::Ok;

   }


   void graphics::set_clip(::draw2d::path * pdraw2dpath)
   {

      if (pdraw2dpath == nullptr)
      {

         throw ::exception(error_null_pointer);

      }

      if (m_pgdiplusgraphics == nullptr)
      {

         throw ::exception(error_null_pointer);

      }

      pdraw2dpath->defer_update(this);

      ::cast < ::draw2d_gdiplus::path > pdraw2dgdipluspath = pdraw2dpath;

      auto pgdiplusgraphicspath = pdraw2dgdipluspath->m_pgdiplusgraphicspath;

      if (::is_null(pgdiplusgraphicspath))
      {

         throw ::exception(error_wrong_state);

      }

      bool bOk = m_pgdiplusgraphics->SetClip(pgdiplusgraphicspath) == Gdiplus::Status::Ok;

   }


   void graphics::AddMetaFileComment(UINT nDataSize, const BYTE * pCommentData)
   {

      //ASSERT(get_handle1() != nullptr);

      //return ::GdiComment(get_handle1(), nDataSize, pCommentData) != false;
      throw ::not_implemented();

      //return false;

   }


   //void graphics::PlayMetaFile(HENHMETAFILE hEnhMF, const ::f64_rectangle &  rectangleBounds)
   //{

   //   Gdiplus::RectF i32_rectangle((Gdiplus::REAL) rectangleBounds.left,(Gdiplus::REAL) rectangleBounds.top,(Gdiplus::REAL) width(rectangleBounds),(Gdiplus::REAL) height(rectangleBounds));

   //   ap(Gdiplus::Metafile) pMeta = ___new Gdiplus::Metafile(hEnhMF, false);

   //   Gdiplus::Status ret = m_pgdiplusgraphics->DrawImage(pMeta, rectangle);

   //   if (ret != Gdiplus::Status::Ok)
   //   {

   //      return false;

   //   }

   //   return true;
   //   //return ::PlayEnhMetaFile(get_handle1(), hEnhMF, pBounds);


   //}

   // true blend
   // COLOR_DEST = SRC_ALPHA * COLOR_SRC  + (1 - SRC_ALPHA) * COLOR_DST

   // ::f64 blend
   // COLOR_DEST = SRC_ALPHA * BLEND_ALPHA * COLOR_SRC  + (1 - SRC_ALPHA * BLEND_ALPHA) * COLOR_DST

// Thank you
// Jiju George T
// Web Developer
// India India
// Member



   //void graphics::_alpha_blend_raw(const ::f64_rectangle & rectangleTarget, ::draw2d::graphics * pgraphicsSrc, const ::f64_rectangle & rectangleSource , ::f64 dRate)
   //{

   //   if (m_pgdiplusgraphics == nullptr || pgraphicsSrc == nullptr)
   //   {

   //      return false;

   //   }

   //   _synchronous_lock slSource(pgraphicsSrc->synchronization());

   //   //bool bThreadToolsForIncreasedFps = ::get_task()->m_bThreadToolsForIncreasedFps;

   //   //bool bAvoidProcFork = ::get_task()->m_bAvoidProcFork;

   //   ////bAvoidProcFork = true;

   //   //if (!bAvoidProcFork && bThreadToolsForIncreasedFps && nDestWidth == nSrcWidth && nDestHeight == nSrcHeight)
   //   //{

   //   //   if (m_ealphamode == ::draw2d::e_alpha_mode_blend)
   //   //   {

   //   //      auto cProcessor = get_processor_count();

   //   //      if (nDestHeight >= cProcessor * 4 && (nDestWidth * nDestHeight) >= (cProcessor * 64))
   //   //      {

   //   //         m_pimage->fork_blend(i32_point(xDest + GetViewportOrg().x, yDest + GetViewportOrg().y), pgraphicsSrc->m_pimage,
   //   //                                                i32_point(xSrc + pgraphicsSrc->GetViewportOrg().x, ySrc + pgraphicsSrc->GetViewportOrg().y),
   //   //                                                ::f64_size(nSrcWidth, nDestHeight), (::u8)(dRate * 255.0f));

   //   //         g_cForkBlend++;

   //   //         if (g_cForkBlend % 100 == 0)
   //   //         {
   //   //            output_debug_string("\nfork_blend(" + ::as_string(g_cForkBlend) + ") sample=" + ::as_string(nSrcWidth) + "," + ::as_string(nDestHeight));
   //   //         }

   //   //      }
   //   //      else
   //   //      {

   //   //         m_pimage->blend(i32_point(xDest + GetViewportOrg().x, yDest + GetViewportOrg().y), pgraphicsSrc->m_pimage,
   //   //                                           i32_point(xSrc+pgraphicsSrc->GetViewportOrg().x, ySrc + pgraphicsSrc->GetViewportOrg().y),
   //   //                                           ::f64_size(nSrcWidth, nDestHeight), (::u8)(dRate * 255.0f));

   //   //      }

   //   //   }
   //   //   else
   //   //   {

   //   //      m_pimage->from(i32_point(xDest + GetViewportOrg().x, yDest + GetViewportOrg().y), pgraphicsSrc->m_pimage,
   //   //                                       i32_point(xSrc + pgraphicsSrc->GetViewportOrg().x, ySrc + pgraphicsSrc->GetViewportOrg().y),
   //   //                                       ::f64_size(nSrcWidth, nDestHeight), (::u8) (dRate * 255.0f));


   //   //   }

   //   //   return true;

   //   //}


   //   ::f32 fA = (::f32) (dRate);


   //   Gdiplus::ColorMatrix colormatrix;

   //   if (pgraphicsSrc->m_pimage->is_ok() && pgraphicsSrc->m_pimage->m_bColorMatrix)
   //   {

   //      copy_color_matrix(colormatrix.m, pgraphicsSrc->m_pimage->m_colormatrix.a);

   //   }
   //   else
   //   {

   //      ::draw2d::color_matrix m;

   //      copy_color_matrix(colormatrix.m, m.a);

   //   }

   //   colormatrix.m[3][3] = fA;

   //   Gdiplus::ImageAttributes imageattributes;

   //   imageattributes.SetColorMatrix(
   //   &colormatrix,
   //      Gdiplus::ColorMatrixFlagsDefault,
   //      Gdiplus::ColorAdjustTypeBitmap);

   //   Gdiplus::RectF rectfDst((Gdiplus::REAL) rectangleTarget.left, (Gdiplus::REAL) rectangleTarget.top, (Gdiplus::REAL) rectangleTarget.width(), (Gdiplus::REAL) rectangleTarget.height());

   //   if (pgraphicsSrc == nullptr)
   //   {

   //      return false;

   //   }

   //   if (pgraphicsSrc->get_current_bitmap() == nullptr)
   //   {

   //      return false;

   //   }

   //   Gdiplus::Bitmap * pdraw2dbitmap = nullptr;

   //   try
   //   {

   //      pdraw2dbitmap = (Gdiplus::Bitmap *) pgraphicsSrc->get_current_bitmap()->get_os_data();

   //   }
   //   catch(...)
   //   {

   //   }

   //   Gdiplus::Status ret = Gdiplus::Status::GenericError;

   //   if(pdraw2dbitmap != nullptr)
   //   {

   //      ret =  m_pgdiplusgraphics->DrawImage(pdraw2dbitmap,rectfDst,
   //         (Gdiplus::REAL) rectangleSource.left,
   //         (Gdiplus::REAL) rectangleSource.top,
   //         (Gdiplus::REAL) rectangleSource.width(),
   //         (Gdiplus::REAL) rectangleSource.height(),
   //         Gdiplus::UnitPixel,&imageattributes);

   //      if (ret != Gdiplus::Status::Ok)
   //      {

   //         return false;

   //      }

   //   }

   //   return true;

   //}




//#define HIMETRIC_INCH   2540    // HIMETRIC units per inch
//
//   void graphics::DPtoHIMETRIC(::f64_size * psize)
//
//   {
//      ASSERT(is_memory_segment_ok(psize, sizeof(const ::f64_size &)));
//
//
//      ::i32 nMapMode;
//      if (this != nullptr && (nMapMode = GetMapMode()) < MM_ISOTROPIC &&
//            nMapMode != MM_TEXT)
//      {
//         // when using a constrained map_base mode, map_base against physical inch
//         ((::draw2d::graphics *)this)->SetMapMode(MM_HIMETRIC);
//         DPtoLP(psize);
//
//         ((::draw2d::graphics *)this)->SetMapMode(nMapMode);
//      }
//      else
//      {
//         
//         ::i32 cxPerInch, cyPerInch;
//         if (this != nullptr)
//         {
//            ASSERT_OK(this);
//            
//            cxPerInch = GetDeviceCaps(LOGPIXELSX);
//            cyPerInch = GetDeviceCaps(LOGPIXELSY);
//         }
//         else
//         {

//         }
//         ASSERT(cxPerInch != 0 && cyPerInch != 0);
//         psize->cx = psize->cx * HIMETRIC_INCH / cxPerInch;
//
//         psize->cy = psize->cy * HIMETRIC_INCH / cyPerInch;
//
//      }
//   }
//
//   void graphics::HIMETRICtoDP(::f64_size * psize)
//
//   {
//      ASSERT(is_memory_segment_ok(psize, sizeof(const ::f64_size&)));
//
//
//      ::i32 nMapMode;
//      if (this != nullptr && (nMapMode = GetMapMode()) < MM_ISOTROPIC &&
//            nMapMode != MM_TEXT)
//      {
//         // when using a constrained map_base mode, map_base against physical inch
//         ((::draw2d::graphics *)this)->SetMapMode(MM_HIMETRIC);
//         LPtoDP(psize);
//
//         ((::draw2d::graphics *)this)->SetMapMode(nMapMode);
//      }
//      else
//      {
//         
//         ::i32 cxPerInch, cyPerInch;
//         if (this != nullptr)
//         {
//            ASSERT_OK(this);
//            
//            cxPerInch = GetDeviceCaps(LOGPIXELSX);
//            cyPerInch = GetDeviceCaps(LOGPIXELSY);
//         }
//         else
//         {

//         }
//         ASSERT(cxPerInch != 0 && cyPerInch != 0);
//         psize->cx = psize->cx* cxPerInch/ HIMETRIC_INCH;
//
//         psize->cy = psize->cy * cyPerInch/ HIMETRIC_INCH;
//
//      }
//   }
//
//   void graphics::LPtoHIMETRIC(::f64_size * psize)
//
//   {
//      ASSERT(is_memory_segment_ok(psize, sizeof(const ::f64_size &)));
//
//
//      LPtoDP(psize);
//
//      DPtoHIMETRIC(psize);
//
//   }
//
//
//   void graphics::HIMETRICtoLP(::f64_size * psize)
//   {
//
//      ASSERT(is_memory_segment_ok(psize, sizeof(const ::f64_size &)));
//
//      HIMETRICtoDP(psize);
//
//      DPtoLP(psize);
//
//   }

   /////////////////////////////////////////////////////////////////////////////
   // special graphics drawing prototypes/helpers

   ::draw2d::brush * graphics::GetHalftoneBrush(::particle * pparticle)
   {
      /*      ::aura::LockGlobals(CRIT_HALFTONEBRUSH);
            if (gen_HalftoneBrush == nullptr)
            {
               WORD grayPattern[8];
               for (::i32 i = 0; i < 8; i++)
                  grayPattern[i] = (WORD)(0x5555 << (i & 1));
               HBITMAP grayBitmap = CreateBitmap(8, 8, 1, 1, grayPattern);
               if (grayBitmap != nullptr)
               {
                  gen_HalftoneBrush = ::CreatePatternBrush(grayBitmap);
                  ::DeleteObject(grayBitmap);
               }
            }
            if (!gen_WingdixTerm)
               gen_WingdixTerm = (::i8)!atexit(&__win_gdi_x_term);
            ::aura::UnlockGlobals(CRIT_HALFTONEBRUSH);

      //      return ::draw2d_gdiplus::brush::from_handle(papp, gen_HalftoneBrush);*/
      return nullptr;
   }


   //void graphics::DrawDragRect(const i32_rectangle &  prectangle, const ::f64_size & size, const i32_rectangle &  lpRectLast, const ::f64_size & sizeLast, ::draw2d::brush* pBrush, ::draw2d::brush* pBrushLast)
   //{

   //   throw ::interface_only();

   //   /*

   //         ASSERT(is_memory_segment_ok(prectangle, sizeof(const i32_rectangle &), false));

   //         ASSERT(pRectLast == nullptr ||

   //            is_memory_segment_ok(pRectLast, sizeof(const i32_rectangle &), false));


   //         // first, determine the update region and select it
   //         ::draw2d::region rgnNew;
   //         ::draw2d::region rgnOutside, rgnInside;
   //         rgnOutside.create_rect(prectangle);

   //         const ::i32_rectangle & rectangle = *prectangle;

   //         rectangle.inflate(-size.cx, -size.cy);
   //         rectangle.intersect(rectangle, prectangle);

   //         rgnInside.create_rect(rectangle);
   //         rgnNew.create_rect(0, 0, 0, 0);
   //         rgnNew.combine(&rgnOutside, &rgnInside, RGN_XOR);

   //         ::draw2d::brush* pBrushOld = nullptr;
   //         if (pBrush == nullptr)
   //         {
   //            pBrush = graphics::GetHalftoneBrush(get_application());
   //         }

   //         ENSURE(pBrush);

   //         if (pBrushLast == nullptr)
   //         {
   //            pBrushLast = pBrush;
   //         }

   //         ::draw2d::region rgnLast, rgnUpdate;
   //         if (pRectLast != nullptr)

   //         {
   //            // find difference between ___new region and old region
   //            rgnLast.create_rect(0, 0, 0, 0);
   //            rgnOutside.SetRectRgn(pRectLast);

   //            rectangle = *pRectLast;

   //            rectangle.inflate(-sizeLast.cx, -sizeLast.cy);
   //            rectangle.intersect(rectangle, pRectLast);

   //            rgnInside.SetRectRgn(rectangle);
   //            rgnLast.CombineRgn(&rgnOutside, &rgnInside, RGN_XOR);

   //            // only diff them if brushes are the same
   //            if (pBrush->get_os_data() == pBrushLast->get_os_data())
   //            {
   //               rgnUpdate.create_rect(0, 0, 0, 0);
   //               rgnUpdate.CombineRgn(&rgnLast, &rgnNew, RGN_XOR);
   //            }
   //         }
   //         if (pBrush->get_os_data() != pBrushLast->get_os_data() && pRectLast != nullptr)

   //         {
   //            // brushes are different -- erase old region first
   //            SelectClipRgn(&rgnLast);
   //            get_clip_box(&rectangle);
   //            pBrushOld = set(pBrushLast);
   //            PatBlt(rectangle.left, rectangle.top, rectangle.width(), rectangle.height(), PATINVERT);
   //            set(pBrushOld);
   //            pBrushOld = nullptr;
   //         }

   //         // draw into the update/___new region
   //         SelectClipRgn(rgnUpdate.get_os_data() != nullptr ? &rgnUpdate : &rgnNew);
   //         get_clip_box(&rectangle);
   //         pBrushOld = set(pBrush);
   //         PatBlt(rectangle.left, rectangle.top, rectangle.width(), rectangle.height(), PATINVERT);

   //         // cleanup DC
   //         if (pBrushOld != nullptr)
   //            set(pBrushOld);
   //         SelectClipRgn(nullptr);

   //   */
   //}

   /*void graphics::fill_rectangle(const i32_rectangle &  prectangle, ::color::color clr)

   {
      ::SetBkColor(get_handle1(), clr);
      ::ExtTextOut(get_handle1(), 0, 0, ETO_OPAQUE, prectangle, nullptr, 0, nullptr);

   }*/


   void graphics::fill_rectangle(const ::f64_rectangle & rectangleParam, const ::color::color & color)
   {

      if (m_bTargetRectangleModified)
      {

         defer_on_target_rectangle_update();

      }

      try
      {

         if (m_pgdiplusgraphics == nullptr)
         {

            throw ::exception(error_null_pointer);

         }

         if (payload("log_fill_rectangle").is_true())
         {

            if (rectangleParam.minimum_dimension() > 24)
            {

               tracer()->width(4);

               tracer()->precision(0);

               //information() << "log_fill_rectangle " << rectangleParam << " color: " << ::file::hex << color;

            }

         }

         Gdiplus::RectF rectangle;

         copy(rectangle, rectangleParam);

         Gdiplus::SolidBrush b(Gdiplus::Color(
            color.m_u8Opacity,
            color.m_u8Red,
            color.m_u8Green,
            color.m_u8Blue));

         auto status = m_pgdiplusgraphics->FillRectangle(&b, rectangle);

         if (status != Gdiplus::Status::Ok)
         {

            //throw ::exception(error_null_pointer);

         }

      }
      catch (...)
      {

      }

      //return true;

   }


   //void graphics::draw_rectangle(const ::f64_rectangle & rectangle, const ::color::color& color, const ::e_border & eborder)
   //{

   //   if (!(eborder & (e_border_left | e_border_right | e_border_top | e_border_bottom)))
   //   {

   //      return false;

   //   }

   //   Gdiplus::Pen pen(Gdiplus::Color(color.alpha, color.red, color.green, color.blue), 1.0);

   //   //if ((eborder & e_border_left) && (eborder & e_border_top)
   //   //   && (eborder & e_border_right) && (eborder & e_border_bottom)
   //   //   && crTopLeft == crBottomRight)
   //   //{

   //   //   m_pgdiplusgraphics->DrawRectangle(&pen, rectangle.left, rectangle.top, rectangle.width(), rectangle.height());

   //   //} else
   //   if ((eborder & e_border_left) && (eborder & e_border_top))
   //   {

   //      Gdiplus::GraphicsPath path;

   //      Gdiplus::PointF pa[3];

   //      pa[0].X = (Gdiplus::REAL) rectangle.left;
   //      pa[0].Y = (Gdiplus::REAL) rectangle.bottom;
   //      pa[1].X = (Gdiplus::REAL) rectangle.left;
   //      pa[1].Y = (Gdiplus::REAL) rectangle.top;
   //      pa[2].X = (Gdiplus::REAL) rectangle.right;
   //      pa[2].Y = (Gdiplus::REAL)rectangle.top;

   //      path.AddLines(pa, 3);

   //      m_pgdiplusgraphics->DrawPath(&pen, &path);

   //   }
   //   else
   //   {

   //      if (eborder & e_border_left)
   //      {

   //         m_pgdiplusgraphics->DrawLine(&pen, 
   //            (Gdiplus::REAL) rectangle.left, 
   //            (Gdiplus::REAL)rectangle.bottom - 1, 
   //            (Gdiplus::REAL)rectangle.left, 
   //            (Gdiplus::REAL)rectangle.top);

   //      }
   //      else if (eborder & e_border_top)
   //      {

   //         m_pgdiplusgraphics->DrawLine(&pen, 
   //            (Gdiplus::REAL)rectangle.left,
   //            (Gdiplus::REAL)rectangle.top, 
   //            (Gdiplus::REAL)rectangle.right, 
   //            (Gdiplus::REAL)rectangle.top);

   //      }

   //   }

   //   if ((eborder & e_border_right) && (eborder & e_border_bottom))
   //   {

   //      Gdiplus::GraphicsPath path;

   //      Gdiplus::PointF pa[3];

   //      pa[0].X = (Gdiplus::REAL) rectangle.left;
   //      pa[0].Y = (Gdiplus::REAL) rectangle.bottom;
   //      pa[1].X = (Gdiplus::REAL) rectangle.right;
   //      pa[1].Y = (Gdiplus::REAL) rectangle.bottom;
   //      pa[2].X = (Gdiplus::REAL) rectangle.right;
   //      pa[2].Y = (Gdiplus::REAL) rectangle.top;

   //      path.AddLines(pa, 3);

   //      m_pgdiplusgraphics->DrawPath(&pen, &path);

   //   }
   //   else
   //   {

   //      if (eborder & e_border_bottom)
   //      {

   //         m_pgdiplusgraphics->DrawLine(&pen,
   //            (Gdiplus::REAL)rectangle.left, 
   //            (Gdiplus::REAL)rectangle.bottom,
   //            (Gdiplus::REAL)rectangle.right,
   //            (Gdiplus::REAL)rectangle.bottom);

   //      }
   //      else if (eborder & e_border_right)
   //      {

   //         m_pgdiplusgraphics->DrawLine(&pen, 
   //            (Gdiplus::REAL)rectangle.right, 
   //            (Gdiplus::REAL)rectangle.bottom, 
   //            (Gdiplus::REAL)rectangle.right, 
   //            (Gdiplus::REAL)rectangle.top + 1);

   //      }

   //   }

   //   return true;

   //}


   //void graphics::draw_rectangle(const ::f64_rectangle& rectangle, const ::color::color& color, const ::e_border & eborder)
   //{

   //   if (!(eborder & (e_border_left | e_border_right | e_border_top | e_border_bottom)))
   //   {

   //      return false;

   //   }

   //   Gdiplus::Pen pen(Gdiplus::Color(color.m_iA, color.m_iR, color.m_iG, color.m_iB), 1.0);

   //   //if ((eborder & e_border_left) && (eborder & e_border_top)
   //   //   && (eborder & e_border_right) && (eborder & e_border_bottom)
   //   //   && crTopLeft == crBottomRight)
   //   //{

   //   //   m_pgdiplusgraphics->DrawRectangle(&pen, rectangle.left, rectangle.top, rectangle.width(), rectangle.height());

   //   //} else
   //   if ((eborder & e_border_left) && (eborder & e_border_top))
   //   {

   //      Gdiplus::GraphicsPath path;

   //      Gdiplus::PointF pa[3];

   //      pa[0].X = (Gdiplus::REAL) rectangle.left;
   //      pa[0].Y = (Gdiplus::REAL) rectangle.bottom - 1;
   //      pa[1].X = (Gdiplus::REAL) rectangle.left;
   //      pa[1].Y = (Gdiplus::REAL) rectangle.top;
   //      pa[2].X = (Gdiplus::REAL) rectangle.right;
   //      pa[2].Y = (Gdiplus::REAL) rectangle.top;

   //      path.AddLines(pa, 3);

   //      m_pgdiplusgraphics->DrawPath(&pen, &path);

   //   }
   //   else
   //   {

   //      if (eborder & e_border_left)
   //      {

   //         m_pgdiplusgraphics->DrawLine(&pen, (Gdiplus::REAL) rectangle.left, (Gdiplus::REAL)rectangle.bottom-1, (Gdiplus::REAL)rectangle.left, (Gdiplus::REAL)rectangle.top);

   //      }
   //      else if (eborder & e_border_top)
   //      {

   //         m_pgdiplusgraphics->DrawLine(&pen, (Gdiplus::REAL)rectangle.left, (Gdiplus::REAL)rectangle.top, (Gdiplus::REAL)rectangle.right, (Gdiplus::REAL)rectangle.top);

   //      }

   //   }


   //   if ((eborder & e_border_right) && (eborder & e_border_bottom))
   //   {

   //      Gdiplus::GraphicsPath path;

   //      Gdiplus::PointF pa[3];

   //      pa[0].X = (Gdiplus::REAL) rectangle.left;
   //      pa[0].Y = (Gdiplus::REAL) rectangle.bottom;
   //      pa[1].X = (Gdiplus::REAL) rectangle.right;
   //      pa[1].Y = (Gdiplus::REAL) rectangle.top;
   //      pa[2].X = (Gdiplus::REAL) rectangle.right;
   //      pa[2].Y = (Gdiplus::REAL) rectangle.top + 1;

   //      path.AddLines(pa, 3);

   //   }
   //   else
   //   {

   //      if (eborder & e_border_bottom)
   //      {

   //         m_pgdiplusgraphics->DrawLine(&pen, (Gdiplus::REAL)rectangle.left, (Gdiplus::REAL)rectangle.bottom, (Gdiplus::REAL)rectangle.right, (Gdiplus::REAL)rectangle.bottom);

   //      }
   //      else if (eborder & e_border_right)
   //      {

   //         m_pgdiplusgraphics->DrawLine(&pen, (Gdiplus::REAL)rectangle.right, (Gdiplus::REAL)rectangle.bottom, (Gdiplus::REAL)rectangle.right, (Gdiplus::REAL)rectangle.top + 1);

   //      }

   //   }

   //}


   //void graphics::draw_inset_3d_rectangle(const ::f64_rectangle & rectangle, const ::color::color& colorTopLeft, const ::color::color& colorBottomRight, const ::e_border & eborder)
   //{

   //   if (!(eborder & (e_border_left | e_border_right | e_border_top | e_border_bottom)))
   //   {

   //      return false;

   //   }


   //   if (colorTopLeft == colorBottomRight)
   //   {

   //      return draw_rectangle(rectangle, colorTopLeft, eborder);

   //   }


   //   if (!(eborder & (e_border_left | e_border_right | e_border_top | e_border_bottom)))
   //   {

   //      return false;

   //   }

   //   {

   //      Gdiplus::Pen pen(Gdiplus::Color(colorTopLeft.alpha, colorTopLeft.red, colorTopLeft.green, colorTopLeft.blue), 1.0);

   //      if ((eborder & e_border_left) && (eborder & e_border_top))
   //      {

   //         Gdiplus::GraphicsPath path;

   //         Gdiplus::PointF pa[3];

   //         pa[0].X = (Gdiplus::REAL) rectangle.left;
   //         pa[0].Y = (Gdiplus::REAL) rectangle.bottom - 1;
   //         pa[1].X = (Gdiplus::REAL) rectangle.left;
   //         pa[1].Y = (Gdiplus::REAL) rectangle.top;
   //         pa[2].X = (Gdiplus::REAL) rectangle.right;
   //         pa[2].Y = (Gdiplus::REAL) rectangle.top;

   //         path.AddLines(pa, 3);

   //         m_pgdiplusgraphics->DrawPath(&pen, &path);

   //      }
   //      else
   //      {

   //         if (eborder & e_border_left)
   //         {

   //            m_pgdiplusgraphics->DrawLine(&pen, (Gdiplus::REAL) rectangle.left, (Gdiplus::REAL)rectangle.bottom - 1, (Gdiplus::REAL)rectangle.left, (Gdiplus::REAL)rectangle.top);

   //         }
   //         else if (eborder & e_border_top)
   //         {

   //            m_pgdiplusgraphics->DrawLine(&pen, (Gdiplus::REAL)rectangle.left, (Gdiplus::REAL)rectangle.top, (Gdiplus::REAL)rectangle.right, (Gdiplus::REAL)rectangle.top);

   //         }

   //      }

   //   }

   //   {

   //      Gdiplus::Pen pen(Gdiplus::Color(colorBottomRight.alpha, colorBottomRight.red, colorBottomRight.green, colorBottomRight.blue), 1.0);

   //      if ((eborder & e_border_right) && (eborder & e_border_bottom))
   //      {

   //         Gdiplus::GraphicsPath path;

   //         Gdiplus::PointF pa[3];

   //         pa[0].X = (Gdiplus::REAL) rectangle.left;
   //         pa[0].Y = (Gdiplus::REAL) rectangle.bottom - 1;
   //         pa[1].X = (Gdiplus::REAL) rectangle.right;
   //         pa[1].Y = (Gdiplus::REAL) rectangle.bottom - 1;
   //         pa[2].X = (Gdiplus::REAL) rectangle.right;
   //         pa[2].Y = (Gdiplus::REAL) rectangle.top + 1;

   //         path.AddLines(pa, 3);

   //         m_pgdiplusgraphics->DrawPath(&pen, &path);

   //      }
   //      else
   //      {

   //         if (eborder & e_border_bottom)
   //         {

   //            m_pgdiplusgraphics->DrawLine(&pen, (Gdiplus::REAL)rectangle.left, (Gdiplus::REAL)rectangle.bottom, (Gdiplus::REAL)rectangle.right, (Gdiplus::REAL)rectangle.bottom);

   //         }
   //         else if (eborder & e_border_right)
   //         {

   //            m_pgdiplusgraphics->DrawLine(&pen, (Gdiplus::REAL)rectangle.right, (Gdiplus::REAL)rectangle.bottom, (Gdiplus::REAL)rectangle.right, (Gdiplus::REAL)rectangle.top + 1);

   //         }

   //      }

   //   }

   //   return true;

   //}


   //void graphics::draw_inset_3d_rectangle(const ::i32_rectangle& rectangle, const ::color::color& colorTopLeft, const ::color::color& colorBottomRight, const ::e_border & eborder)
   //{

   //   if (!(eborder & (e_border_left | e_border_right | e_border_top | e_border_bottom)))
   //   {

   //      return;

   //   }


   //   if (colorTopLeft == colorBottomRight)
   //   {

   //      draw_rectangle(rectangle, colorTopLeft, eborder);

   //      return;

   //   }


   //   if (!(eborder & (e_border_left | e_border_right | e_border_top | e_border_bottom)))
   //   {

   //      return;

   //   }

   //   {

   //      Gdiplus::Pen pen(Gdiplus::Color(colorTopLeft.m_iA, colorTopLeft.m_iR, colorTopLeft.m_iG, colorTopLeft.m_iB), 1.0);

   //      if ((eborder & e_border_left) && (eborder & e_border_top))
   //      {

   //         Gdiplus::GraphicsPath path;

   //         Gdiplus::Point pa[3];

   //         pa[0].X = rectangle.left;
   //         pa[0].Y = rectangle.bottom - 1;
   //         pa[1].X = rectangle.left;
   //         pa[1].Y = rectangle.top;
   //         pa[2].X = rectangle.right;
   //         pa[2].Y = rectangle.top;

   //         path.AddLines(pa, 3);

   //         m_pgdiplusgraphics->DrawPath(&pen, &path);

   //      }
   //      else
   //      {

   //         if (eborder & e_border_left)
   //         {

   //            m_pgdiplusgraphics->DrawLine(&pen, rectangle.left, rectangle.bottom - 1, rectangle.left, rectangle.top);

   //         }
   //         else if (eborder & e_border_top)
   //         {

   //            m_pgdiplusgraphics->DrawLine(&pen, rectangle.left, rectangle.top, rectangle.right, rectangle.top);

   //         }

   //      }

   //   }

   //   {

   //      Gdiplus::Pen pen(Gdiplus::Color(colorBottomRight.m_iA, colorBottomRight.m_iR, colorBottomRight.m_iG, colorBottomRight.m_iB), 1.0);

   //      if ((eborder & e_border_right) && (eborder & e_border_bottom))
   //      {

   //         Gdiplus::GraphicsPath path;

   //         Gdiplus::Point pa[3];

   //         pa[0].X = rectangle.left;
   //         pa[0].Y = rectangle.bottom;
   //         pa[1].X = rectangle.right;
   //         pa[1].Y = rectangle.top;
   //         pa[2].X = rectangle.right;
   //         pa[2].Y = rectangle.top + 1;

   //         path.AddLines(pa, 3);

   //      }
   //      else
   //      {

   //         if (eborder & e_border_bottom)
   //         {

   //            m_pgdiplusgraphics->DrawLine(&pen, rectangle.left, rectangle.bottom, rectangle.right, rectangle.bottom);

   //         }
   //         else if (eborder & e_border_right)
   //         {

   //            m_pgdiplusgraphics->DrawLine(&pen, rectangle.right, rectangle.bottom, rectangle.right, rectangle.top + 1);

   //         }

   //      }

   //   }

   //}


   void graphics::close_graphics()
   {

      if (m_hdcAttach != nullptr)
      {

         detach_hdc();

      }

      if (m_pgdiplusgraphics != nullptr)
      {

         //try
         //{

         //   delete m_pgdiplusgraphics;

         //}
         //catch (...)
         //{

         //   information() << "graphics::DeleteDC : Failed to delete Gdiplus::Graphics";

         //}

         m_pgdiplusgraphics = nullptr;

      }

      if (m_hdcGraphics != nullptr)
      {

         bool bDeleted = ::DeleteDC(m_hdcGraphics) != false;

         if (!bDeleted)
         {

            information() << "graphics::DeleteDC : Failed to delete GDI device context";

         }

         m_hdcGraphics = NULL;

      }

      if (m_pgdiplusgraphicspath != nullptr)
      {

         try
         {

            m_pgdiplusgraphicspath.destroy();

         }
         catch (...)
         {

         }

      }

      if (m_pgdiplusgraphicspathPaint != nullptr)
      {

         try
         {

            m_pgdiplusgraphicspathPaint.destroy();

         }
         catch (...)
         {

         }

      }

   }


   void graphics::DeleteDC()
   {

      close_graphics();

   }


   ::i32 graphics::save_graphics_context()
   {

      Gdiplus::GraphicsState state = m_pgdiplusgraphics->Save();

      return (::i32)state;

   }


   void graphics::restore_graphics_context(::i32 iSaveContext)
   {

      if (::is_null(m_pgdiplusgraphics))
      {

         throw ::exception(error_null_pointer);

      }

      Gdiplus::Status status = m_pgdiplusgraphics->Restore((Gdiplus::GraphicsState)iSaveContext);

      bool bOk = status == Gdiplus::Ok;

   }


   //::draw2d::palette* graphics::SelectPalette(::draw2d::palette* pPalette, bool bForceBackground)
   //{

   //   return nullptr;

   //}


   //::i32 graphics::SetPolyFillMode(::i32 nPolyFillMode)
   //{
   //   //::i32 nRetVal = 0;
   //   //if(get_handle1() != nullptr && get_handle1() != get_handle2())
   //   //   nRetVal = ::SetPolyFillMode(get_handle1(), nPolyFillMode);
   //   //if(get_handle2() != nullptr)
   //   //   nRetVal = ::SetPolyFillMode(get_handle2(), nPolyFillMode);
   //   //return nRetVal;
   //   throw ::not_implemented();

   //   return -1;

   //}

   //::i32 graphics::SetROP2(::i32 nDrawMode)
   //{
   //   //::i32 nRetVal = 0;
   //   //if(get_handle1() != nullptr && get_handle1() != get_handle2())
   //   //   nRetVal = ::SetROP2(get_handle1(), nDrawMode);
   //   //if(get_handle2() != nullptr)
   //   //   nRetVal = ::SetROP2(get_handle2(), nDrawMode);
   //   //return nRetVal;
   //   throw ::not_implemented();

   //   return -1;

   //}


   void graphics::set_interpolation_mode(::draw2d::enum_interpolation_mode einterpolationmode)
   {

      if (m_pgdiplusgraphics == nullptr)
      {

         throw ::exception(error_null_pointer);

      }

      if (einterpolationmode == ::draw2d::e_interpolation_mode_nearest_neighbor)
      {

         m_pgdiplusgraphics->SetInterpolationMode(Gdiplus::InterpolationModeNearestNeighbor);

      }
      else if (einterpolationmode == ::draw2d::e_interpolation_mode_high_quality_bicubic)
      {

         m_pgdiplusgraphics->SetInterpolationMode(Gdiplus::InterpolationModeHighQualityBicubic);

      }
      else
      {

         m_pgdiplusgraphics->SetInterpolationMode(Gdiplus::InterpolationModeLowQuality);

      }

      //return true;

      /*::i32 nRetVal = 0;
      if(get_handle1() != nullptr && get_handle1() != get_handle2())
         nRetVal = ::SetStretchBltMode(get_handle1(), nStretchMode);
      if(get_handle2() != nullptr)
         nRetVal = ::SetStretchBltMode(get_handle2(), nStretchMode);
      return nRetVal;*/

   }


   //::i32 graphics::SetGraphicsMode(::i32 iMode)
   //{
   //   //::i32 nRetVal = 0;
   //   //if(get_handle1() != nullptr && get_handle1() != get_handle2())
   //   //{
   //   //   nRetVal = ::SetGraphicsMode(get_handle1(), iMode);
   //   //}
   //   //if(get_handle2() != nullptr)
   //   //{
   //   //   nRetVal = ::SetGraphicsMode(get_handle2(), iMode);
   //   //}
   //   //return nRetVal;
   //   throw ::not_implemented();

   //   return -1;
   //}


   //void graphics::SetWorldTransform(const XFORM* pXform)
   //{

   //   if (::is_null(m_pgdiplusgraphics))
   //   {

   //      return false;

   //   }

   //   Gdiplus::REAL i32_rectangle[6];

   //   i32_rectangle[0] = pXform->eDx;
   //   i32_rectangle[1] = pXform->eDy;

   //   i32_rectangle[2] = pXform->eM11;
   //   i32_rectangle[3] = pXform->eM12;
   //   i32_rectangle[4] = pXform->eM21;
   //   i32_rectangle[5] = pXform->eM22;

   //   Gdiplus::Matrix m;

   //   m.SetElements(i32_rectangle[2],i32_rectangle[3],i32_rectangle[4],i32_rectangle[5],i32_rectangle[0],i32_rectangle[1]);

   //   m_pgdiplusgraphics->SetTransform(&m);

   //   return true;
   //}

   //void graphics::ModifyWorldTransform(const XFORM* pXform,::u32 iMode)
   //{

   //   if (::is_null(m_pgdiplusgraphics))
   //   {

   //      return false;

   //   }

   //   //bool nRetVal = 0;
   //   //if(get_handle1() != nullptr && get_handle1() != get_handle2())
   //   //{
   //   //   nRetVal = ::ModifyWorldTransform(get_handle1(), pXform, iMode) != false;
   //   //}
   //   //if(get_handle2() != nullptr)
   //   //{
   //   //   nRetVal = ::ModifyWorldTransform(get_handle2(), pXform, iMode) != false;
   //   //}
   //   //return nRetVal;
   //   throw ::not_implemented();

   //   return false;
   //}

   //::i32 graphics::SetMapMode(::i32 nMapMode)
   //{
   //   //::i32 nRetVal = 0;
   //   //if(get_handle1() != nullptr && get_handle1() != get_handle2())
   //   //   nRetVal = ::SetMapMode(get_handle1(), nMapMode);
   //   //if(get_handle2() != nullptr)
   //   //   nRetVal = ::SetMapMode(get_handle2(), nMapMode);
   //   //return nRetVal;
   //   ///throw ::not_implemented();

   //   return -1;
   //}


   ::f64_size graphics::set_extents(::f64 x, ::f64 y)
   {

      ::f64_size size(0, 0);
      //if(get_handle1() != nullptr && get_handle1() != get_handle2())
      //   ::SetViewportExtEx(get_handle1(), x, y, &::f64_size);
      //if(get_handle2() != nullptr)
      //   ::SetViewportExtEx(get_handle2(), x, y, &::f64_size);
      return size;

   }


   ::f64_point graphics::SetWindowOrg(::f64 x, ::f64 y)
   {
      //::i32_point point;
      //if(get_handle1() != nullptr && get_handle1() != get_handle2())
      //   ::SetWindowOrgEx(get_handle1(), x, y, &point);
      //if(get_handle2() != nullptr)
      //   ::SetWindowOrgEx(get_handle2(), x, y, &point);
      return {};
   }


   ::f64_point graphics::offset_window_org(::f64 nWidth, ::f64 nHeight)
   {
      //      ::i32_point point;
            //if(get_handle1() != nullptr && get_handle1() != get_handle2())
            //   ::OffsetWindowOrgEx(get_handle1(), nWidth, nHeight, &point);
            //if(get_handle2() != nullptr)
            //   ::OffsetWindowOrgEx(get_handle2(), nWidth, nHeight, &point);
      return {};
   }


   //::f64_size graphics::set_window_ext(::f64 x, ::f64 y)
   //{
   //   ::f64_size size(0, 0);
   //   //if(get_handle1() != nullptr && get_handle1() != get_handle2())
   //   //   ::SetWindowExtEx(get_handle1(), x, y, &::f64_size);
   //   //if(get_handle2() != nullptr)
   //   //   ::SetWindowExtEx(get_handle2(), x, y, &::f64_size);
   //   return size;
   //}


   //::f64_size graphics::scale_window_ext(::f64 xNum, ::f64 xDenom, ::f64 yNum, ::f64 yDenom)
   //{

   //   ::f64_size size(0, 0);
   //   //if(get_handle1() != nullptr && get_handle1() != get_handle2())
   //   //   ::ScaleWindowExtEx(get_handle1(), xNum, xDenom, yNum, yDenom, &::f64_size);
   //   //if(get_handle2() != nullptr)
   //   //   ::ScaleWindowExtEx(get_handle2(), xNum, xDenom, yNum, yDenom, &::f64_size);
   //   return size;

   //}


   ::i32 graphics::get_clip_box(::f64_rectangle & rectangle)
   {

      if (m_bTargetRectangleModified)
      {

         defer_on_target_rectangle_update();

      }

      Gdiplus::Rect gdiplusrectangle;

      m_pgdiplusgraphics->GetClipBounds(&gdiplusrectangle);

      copy(rectangle, gdiplusrectangle);

      return 1;

   }


   //void graphics::add_clipping_shapes(const shape_array<::draw2d::region> & shapea)
   //{

   //   for (::i32 i = 0; i < shapea.get_count(); i++)
   //   {

   //      if (i + 1 < shapea.get_count())
   //      {

   //         if (shapea[i + 1]->eshape() == e_shape_intersect_clip)
   //         {

   //            switch (shapea[i]->eshape())
   //            {
   //               //case e_shape_rect:
   //               //   intersect_clip(shapea[i]->shape < ::i32_rectangle>());
   //               //   break;
   //            case e_shape_rectangle:
   //               intersect_clip(shapea[i]->shape < ::rectangle>());
   //               break;
   //               //case e_shape_oval:
   //               //   intersect_clip(shapea[i]->shape < ::oval>());
   //               //   break;
   //            case e_shape_ellipse:
   //               intersect_clip(shapea[i]->shape < ::ellipse>());
   //               break;
   //               //case e_shape_polygon:
   //               //   intersect_clip(shapea[i]->shape < ::i32_polygon>());
   //               //   break;
   //            case e_shape_polygon:
   //               intersect_clip(shapea[i]->shape < ::polygon>());
   //               break;

   //            }

   //            i++;

   //         }

   //      }

   //   }

   //   //return ::success;

   //}


   void graphics::reset_clip()
   {

      m_pgdiplusgraphics->ResetClip();

      //return ::success;

   }


   void graphics::_intersect_clip()
   {


   }



   //void graphics::_add_clipping_shape(const ::f64_rectangle & rectangle, ::draw2d::region * pregion)
   //{

   //   //if (!shaperegion.holdee() || shaperegion.holdee()->m_pointOffset != m_pointAddShapeTranslate)
   //   //if (!shaperegion.holdee())
   //   //{

   //   //   auto pregion = createø < ::draw2d::region >();

   //   //   //pregion->m_pointOffset = m_pointAddShapeTranslate;

   //   //   pregion->create_rectangle(rectangle);

   //   //   shaperegion.holdee(pregion);

   //   //}

   //   //Gdiplus::Region* pregion = (Gdiplus::Region*)shaperegion.holdee()->get_os_data(this, 0);

   //   //m_pgdiplusgraphics->SetClip(pregion, Gdiplus::CombineModeIntersect);
   //   // 
   //   Gdiplus::RectF r;

   //   copy(r, rectangle);
   //   m_pgdiplusgraphics->SetClip(r, Gdiplus::CombineModeIntersect);
   //   //return ::success;

   //}


   //void graphics::intersect_clip(const ::rectangle & rectangle)
   //{

   //   Gdiplus::RectF r;

   //   __copy(r, rectangle);

   //   r.X += (Gdiplus::REAL)m_pointAddShapeTranslate.x;

   //   r.Y += (Gdiplus::REAL)m_pointAddShapeTranslate.y;

   //   m_pgdiplusgraphics->IntersectClip(r);

   //   return ::success;

   //}


   void graphics::set_clipping(::draw2d::region * pregion)
   {

      ::pointer < ::draw2d_gdiplus::region > pregionGdiplus = pregion;

      auto p = pregionGdiplus->get(this);

      m_pgdiplusgraphics->SetClip(p, ::Gdiplus::CombineModeReplace);

   }


   //void graphics::_add_clipping_shape(const ::f64_ellipse & ellipse, ::draw2d::region * pregion)
   //{

   //   //if (!shaperegion.holdee() || shaperegion.holdee()->m_pointOffset != m_pointAddShapeTranslate)
   //   //if (!shaperegion.holdee())
   //   //{

   //   //   auto pregion= createø < ::draw2d::region >();

   //   //   //pregion->m_pointOffset = m_pointAddShapeTranslate;

   //   //   pregion->create_ellipse(ellipse);

   //   //   shaperegion.holdee(pregion);

   //   //}

   //   //Gdiplus::Region * pregion = (Gdiplus::Region * ) shaperegion.holdee()->get_os_data(this, 0);

   //   //auto pregion = ___new Gdiplus::Region();

   //   //pregion->

   //   //m_pgdiplusgraphics->SetClip(pregion, Gdiplus::CombineModeIntersect);
   //   Gdiplus::GraphicsPath path;

   //   Gdiplus::RectF r;

   //   copy(r, ellipse);

   //   path.AddEllipse(r);

   //   //auto pregion = ___new Gdiplus::Region(&path);

   //   m_pgdiplusgraphics->SetClip(&path, Gdiplus::CombineModeIntersect);

   //   //delete pregion;

   //}


   //void graphics::intersect_clip(const ::ellipse & ellipse)
   //{

   //   auto pdraw2dpath = __auto(___new Gdiplus::GraphicsPath());

   //   Gdiplus::RectF r;

   //   __copy(r, oval);

   //   r.X += (Gdiplus::REAL)m_pointAddShapeTranslate.x;

   //   r.Y += (Gdiplus::REAL)m_pointAddShapeTranslate.y;

   //   pdraw2dpath->AddArc(r, 0.f, 360.0f);

   //   m_pgdiplusgraphics->SetClip(pdraw2dpath, Gdiplus::CombineModeIntersect);

   //   return ::success;

   //}


   //void graphics::_add_clipping_shape(const ::f64_polygon_base & polygon, ::draw2d::region * pregion)
   //{

   //   //if (!shaperegion.holdee() || shaperegion.holdee()->m_pointOffset != m_pointAddShapeTranslate)
   //   //if (!shaperegion.holdee())
   //   //{

   //   //   auto pregion = createø < ::draw2d::region >();

   //   //   //pregion->m_pointOffset = m_pointAddShapeTranslate;

   //   //   pregion->create_polygon(polygon);

   //   //   shaperegion.holdee(pregion);

   //   //}

   //   //Gdiplus::Region* pregion = (Gdiplus::Region*)shaperegion.holdee()->get_os_data(this, 0);

   //   //m_pgdiplusgraphics->SetClip(pregion, Gdiplus::CombineModeIntersect);

   //   Gdiplus::GraphicsPath path;

   //   array < Gdiplus::PointF > pa;

   //   //::pointer<::geometry2d::polygon_item>pitem = pregion->m_pitem;

   //   for (::i32 i = 0; i < polygon.get_size(); i++)
   //   {
   //      pa.add(Gdiplus::PointF((Gdiplus::REAL)polygon[i].x, (Gdiplus::REAL)polygon[i].y));
   //   }

   //   if (m_efillmode == ::draw2d::e_fill_mode_alternate)
   //   {
   //      path.SetFillMode(Gdiplus::FillModeAlternate);
   //   }
   //   else
   //   {
   //      path.SetFillMode(Gdiplus::FillModeWinding);
   //   }

   //   path.AddPolygon(pa.data(), (::i32)pa.get_count());

   //   m_pgdiplusgraphics->SetClip(&path, Gdiplus::CombineModeIntersect);

   //}


   void graphics::_add_clip_item(Gdiplus::GraphicsPath * pgdiplusgraphicspath, ::draw2d::clip_item * pdraw2clipitem)
   {

      switch (pdraw2clipitem->clip_item_type())
      {
      case ::draw2d::e_clip_item_rectangle:
         _add_shape(pgdiplusgraphicspath, dynamic_cast<::draw2d::clip_rectangle *>(pdraw2clipitem)->m_item);
         break;
      case ::draw2d::e_clip_item_ellipse:
         _add_shape(pgdiplusgraphicspath, dynamic_cast<::draw2d::clip_ellipse *>(pdraw2clipitem)->m_item);
         break;
      case ::draw2d::e_clip_item_polygon:
         _add_shape(pgdiplusgraphicspath, dynamic_cast<::draw2d::clip_polygon *>(pdraw2clipitem)->m_item);
         break;
      default:
         break;
      };

   }


   void graphics::_add_shape(Gdiplus::GraphicsPath * pgdiplusgraphicspath, const ::f64_rectangle & rectangle)
   {

      Gdiplus::RectF rectf;

      copy(rectf, rectangle);

      pgdiplusgraphicspath->AddRectangle(rectf);

   }


   void graphics::_add_shape(Gdiplus::GraphicsPath * pgdiplusgraphicspath, const ::f64_ellipse & ellipse)
   {

      Gdiplus::RectF rectf;

      copy(rectf, ellipse);

      pgdiplusgraphicspath->AddEllipse(rectf);

   }


   void graphics::_add_shape(Gdiplus::GraphicsPath * pgdiplusgraphicspath, const ::f64_polygon_base & polygon)
   {

      ::array<Gdiplus::PointF>pointa;

      for (auto & point : polygon)
      {

         pointa.add({ (Gdiplus::REAL) point.x, (Gdiplus::REAL) point.y });

      }

      pgdiplusgraphicspath->AddPolygon(pointa.data(), (INT) pointa.size());

   }


   void graphics::intersect_clip(::draw2d::clip_group * pdraw2clipgroup)
   {

      auto_pointer < Gdiplus::Region > pgdiplusregion;

      for (auto & pdraw2clipitem : *pdraw2clipgroup)
      {

         if (pdraw2clipitem->clip_item_type() == ::draw2d::e_clip_item_rectangle)
         {

            Gdiplus::Rect rect;

            copy(rect, dynamic_cast<::draw2d::clip_rectangle *>(pdraw2clipitem.m_p)->m_item);

            if (!pgdiplusregion)
            {

               pgdiplusregion = ::as_pointer(new Gdiplus::Region(rect));

            }
            else
            {

               pgdiplusregion->Union(rect);

            }

         }
         else
         {

            auto pdraw2dpath = create_auto_pointerø < Gdiplus::GraphicsPath >();

            pdraw2dpath->SetFillMode(Gdiplus::FillModeWinding);

            _add_clip_item(pdraw2dpath, pdraw2clipitem);

            if (!pgdiplusregion)
            {

               pgdiplusregion = ::as_pointer(new Gdiplus::Region(pdraw2dpath));

            }
            else
            {

               pgdiplusregion->Union(pdraw2dpath);

            }

         }

      }

      if (pgdiplusregion)
      {

         m_pgdiplusgraphics->SetClip(pgdiplusregion, Gdiplus::CombineModeIntersect);

      }

   }


   void graphics::_add_clip_item(::draw2d::clip_item * pdraw2clipitem)
   {

      throw ::exception(error_not_supported);

   }


   void graphics::intersect_clip(const ::f64_rectangle & rectangle)
   {

      if (m_bTargetRectangleModified)
      {

         defer_on_target_rectangle_update();

      }



      Gdiplus::RectF rectf;

      copy(rectf, rectangle);

      m_pgdiplusgraphics->SetClip(rectf, Gdiplus::CombineModeIntersect);

   }


   void graphics::intersect_clip(const ::f64_ellipse & ellipse)
   {

      auto pdraw2dpath = create_auto_pointerø < Gdiplus::GraphicsPath >();

      _add_shape(pdraw2dpath, ellipse);

      m_pgdiplusgraphics->SetClip(pdraw2dpath, Gdiplus::CombineModeIntersect);

   }


   void graphics::intersect_clip(const ::f64_polygon_base & polygon)
   {

      auto pdraw2dpath = create_auto_pointerø < Gdiplus::GraphicsPath >();

      _add_shape(pdraw2dpath, polygon);

      m_pgdiplusgraphics->SetClip(pdraw2dpath, Gdiplus::CombineModeIntersect);

   }


   //void graphics::_intersect_clip()
   //{

   //   throw ::exception(error_not_supported);

   //}


   void graphics::_add_shape(const ::f64_rectangle & rectangle)
   {

      throw ::exception(error_not_supported);

   }


   void graphics::_add_shape(const ::f64_ellipse & ellipse)
   {

      throw ::exception(error_not_supported);

   }


   void graphics::_add_shape(const ::f64_polygon_base & polygon)
   {

      throw ::exception(error_not_supported);

   }


   //::i32 graphics::SelectClipRgn(::draw2d::region * pregion)
   //{

   //   if(pregion == nullptr)
   //   {

   //      m_pgdiplusgraphics->ResetClip();

   //   }
   //   else
   //   {

   //      m_pgdiplusgraphics->SetClip(pregion->get_os_data<Region * >(this));

   //   }

   //   return 0;

   //}


   //::i32 graphics::ExcludeClipRect(::f64 x1, ::i32 y1, ::f64 x2, ::i32 y2)
   //{
   //   ::i32 nRetVal = ERROR;
   //   //if(get_handle1() != nullptr && get_handle1() != get_handle2())
   //   //   nRetVal = ::ExcludeClipRect(get_handle1(), x1, y1, x2, y2);
   //   //if(get_handle2() != nullptr)
   //   //   nRetVal = ::ExcludeClipRect(get_handle2(), x1, y1, x2, y2);
   //   return nRetVal;
   //}

   //::i32 graphics::ExcludeClipRect(const i32_rectangle &  rectangleParam)
   //{
   //   ::i32 nRetVal = ERROR;
   //   //if(get_handle1() != nullptr && get_handle1() != get_handle2())
   //   //   nRetVal = ::ExcludeClipRect(get_handle1(), rectangleParam.left, rectangleParam.top,
   //   //                               rectangleParam.right, rectangleParam.bottom);
   //   //if(get_handle2() != nullptr)
   //   //   nRetVal = ::ExcludeClipRect(get_handle2(), rectangleParam.left, rectangleParam.top,
   //   //                               rectangleParam.right, rectangleParam.bottom);
   //   return nRetVal;
   //}

   //::i32 graphics::IntersectClipRect(::f64 x1, ::i32 y1, ::f64 x2, ::i32 y2)
   //{
   //   ::i32 nRetVal = ERROR;
   //   //if(get_handle1() != nullptr && get_handle1() != get_handle2())
   //   //   nRetVal = ::IntersectClipRect(get_handle1(), x1, y1, x2, y2);
   //   //if(get_handle2() != nullptr)
   //   //   nRetVal = ::IntersectClipRect(get_handle2(), x1, y1, x2, y2);
   //   return nRetVal;
   //}

   //::i32 graphics::IntersectClipRect(const i32_rectangle &  rectangleBounds)
   //{
   //   ::i32 nRetVal = ERROR;

   //   Gdiplus::Rect i32_rectangle(rectangleBounds.left, rectangleBounds.top, width(rectangleBounds),  height(rectangleBounds));

   //   m_pgdiplusgraphics->IntersectClip(rectangle);

   //   //if(get_handle1() != nullptr && get_handle1() != get_handle2())
   //   //   nRetVal = ::IntersectClipRect(get_handle1(),rectangleBounds.left,rectangleBounds.top,rectangleBounds.right,rectangleBounds.bottom);
   //   //if(get_handle2() != nullptr)
   //   //   nRetVal = ::IntersectClipRect(get_handle2(),rectangleBounds.left,rectangleBounds.top,rectangleBounds.right,rectangleBounds.bottom);
   //   return SIMPLEREGION;
   //}

   //::i32 graphics::OffsetClipRgn(::f64 x, ::f64 y)
   //{
   //   ::i32 nRetVal = ERROR;
   //   return OffsetClipRgn({ x, y });
   //   return nRetVal;
   //}

   //::i32 graphics::OffsetClipRgn(const ::f64_size & size)
   //{
   //   ::i32 nRetVal = ERROR;
   //   //if(get_handle1() != nullptr && get_handle1() != get_handle2())
   //   //   nRetVal = ::OffsetClipRgn(get_handle1(), size.cx, size.cy);
   //   //if(get_handle2() != nullptr)
   //   //   nRetVal = ::OffsetClipRgn(get_handle2(), size.cx, size.cy);
   //   m_pgdiplusgraphics->TranslateClip(size.cx, size.cy);
   //   return nRetVal;
   //}


   UINT graphics::SetTextAlign(UINT nFlags)
   {
      UINT nRetVal = GDI_ERROR;
      //if(get_handle1() != nullptr && get_handle1() != get_handle2())
      //   ::SetTextAlign(get_handle1(), nFlags);
      //if(get_handle2() != nullptr)
      //   nRetVal = ::SetTextAlign(get_handle2(), nFlags);
      return nRetVal;
   }

   //::i32 graphics::SetTextJustification(::i32 nBreakExtra, ::i32 nBreakCount)
   //{
   //   ::i32 nRetVal = 0;
   //   //if(get_handle1() != nullptr && get_handle1() != get_handle2())
   //   //   nRetVal = ::SetTextJustification(get_handle1(), nBreakExtra, nBreakCount);
   //   //if(get_handle2() != nullptr)
   //   //   nRetVal = ::SetTextJustification(get_handle2(), nBreakExtra, nBreakCount);
   //   return nRetVal;
   //}

   //::i32 graphics::SetTextCharacterExtra(::i32 nCharExtra)
   //{
   //   //ASSERT(get_handle1() != nullptr);
   //   ::i32 nRetVal = 0x8000000;
   //   //if(get_handle1() != nullptr && get_handle1() != get_handle2())
   //   //   nRetVal = ::SetTextCharacterExtra(get_handle1(), nCharExtra);
   //   //if(get_handle2() != nullptr)
   //   //   nRetVal = ::SetTextCharacterExtra(get_handle2(), nCharExtra);
   //   return nRetVal;
   //}

   //::u32 graphics::SetMapperFlags(::u32 dwFlag)
   //{
   //   //ASSERT(get_handle1() != nullptr);
   //   ::u32 dwRetVal = GDI_ERROR;
   //   //if(get_handle1() != nullptr && get_handle1() != get_handle2())
   //   //   dwRetVal = ::SetMapperFlags(get_handle1(), dwFlag);
   //   //if(get_handle2() != nullptr)
   //   //   dwRetVal = ::SetMapperFlags(get_handle2(), dwFlag);
   //   return dwRetVal;
   //}

   typedef ::u32(CALLBACK * __GDIGETLAYOUTPROC)(HDC);
   typedef ::u32(CALLBACK * __GDISETLAYOUTPROC)(HDC, ::u32);

   ::u32 graphics::GetLayout()
   {
      HINSTANCE hInst = ::GetModuleHandleA("GDI32.DLL");
      ASSERT(hInst != nullptr);
      /*      ::u32 dwGetLayout = LAYOUT_LTR;
            __GDIGETLAYOUTPROC pfn;
            pfn = (__GDIGETLAYOUTPROC) GetProcAddress(hInst, "GetLayout");
            // if they API is available, just call it. If it is not
            // available, indicate an error.
            if (pfn != nullptr)
               dwGetLayout = (*pfn)(get_handle1());
            else
            {
               dwGetLayout = GDI_ERROR;
               SetLastError(ERROR_CALL_NOT_IMPLEMENTED);
            }*/
            //return dwGetLayout;
      return 0;
   }

   ::u32 graphics::SetLayout(::u32 dwSetLayout)
   {
      /*HINSTANCE hInst = ::GetModuleHandleA("GDI32.DLL");
      ASSERT(hInst != nullptr);
      ::u32 dwGetLayout = LAYOUT_LTR;
      __GDISETLAYOUTPROC pfn;
      pfn = (__GDISETLAYOUTPROC) GetProcAddress(hInst, "SetLayout");
      // If the API is availalbe, just call it. If it's not available,
      // setting anything other than LAYOUT_LTR is an error.
      if (pfn != nullptr)
         dwGetLayout = (*pfn)(get_handle1(), dwSetLayout);
      else if (dwSetLayout != LAYOUT_LTR)
      {
         dwGetLayout = GDI_ERROR;
         SetLastError(ERROR_CALL_NOT_IMPLEMENTED);
      }
      return dwGetLayout;*/

      return 0;

   }
   /*
   void window::ScreenToClient(RECT * prectangle)

   {
   ASSERT(::IsWindow(get_handle1()));
   ::ScreenToClient(get_handle1(), (LPPOINT)prectangle);

   ::ScreenToClient(get_handle1(), ((LPPOINT)prectangle)+1);

   if (GetExStyle() & WS_EX_LAYOUTRTL)
   i32_rectangle::swap_left_right(prectangle);

   }

   void window::ClientToScreen(RECT * prectangle)

   {
   ASSERT(::IsWindow(get_handle1()));
   ::ClientToScreen(get_handle1(), (LPPOINT)prectangle);

   ::ClientToScreen(get_handle1(), ((LPPOINT)prectangle)+1);

   if (GetExStyle() & WS_EX_LAYOUTRTL)
   i32_rectangle::swap_left_right(prectangle);

   }*/


   /////////////////////////////////////////////////////////////////////////////
   // Advanced Win32 GDI functions

   //void graphics::ArcTo(::f64 x1, ::i32 y1, ::f64 x2, ::i32 y2, ::f64 x3, ::f64 y3, ::f64 x4, ::f64 y4)
   //{

   //   if (::is_null(m_pgdiplusgraphics))
   //   {

   //      return false;

   //   }

   //   //ASSERT(get_handle1() != nullptr);
   //   //bool bResult = ::ArcTo(get_handle1(), x1, y1, x2, y2, x3, y3, x4, y4) != false;
   //   //if (get_handle1() != get_handle2())
   //   //{
   //   //   ::i32_point point;
   //   //   VERIFY(::GetCurrentPositionEx(get_handle1(), &point));
   //   //   VERIFY(::MoveToEx(get_handle2(), point.x, point.y, nullptr));
   //   //}
   //   //return bResult;
   //   throw ::not_implemented();

   //   return false;
   //}

   //::i32 graphics::SetArcDirection(::i32 nArcDirection)
   //{
   //   //ASSERT(get_handle1() != nullptr);
   //   //::i32 nResult = 0;
   //   //if (get_handle1() != get_handle2())
   //   //   nResult = ::SetArcDirection(get_handle1(), nArcDirection);
   //   //if (get_handle2() != nullptr)
   //   //   nResult = ::SetArcDirection(get_handle2(), nArcDirection);
   //   //return nResult;
   //   throw ::not_implemented();

   //   return -1;
   //}


   void graphics::polydraw(const ::f64_point * pPoints, const BYTE * lpTypes, ::collection::count nCount)
   {

      if (::is_null(m_pgdiplusgraphics))
      {

         //return false;

         throw ::exception(error_null_pointer);

      }

      //ASSERT(get_handle1() != nullptr);

      //bool bResult = ::poly_draw(get_handle1(), pPoints, lpTypes, (::i32) nCount) != false;


      //if (get_handle1() != get_handle2())
      //{
      //   ::i32_point point;
      //   VERIFY(::GetCurrentPositionEx(get_handle1(), &point));
      //   VERIFY(::MoveToEx(get_handle2(), point.x, point.y, nullptr));
      //}
      //return bResult;
      throw ::not_implemented();

      //return false;
   }


   void graphics::polyline_to(const ::f64_point * pPoints, ::collection::count nCount)
   {

      if (::is_null(m_pgdiplusgraphics))
      {

         //return false;
         throw ::exception(error_null_pointer);

      }

      //ASSERT(get_handle1() != nullptr);
      //bool bResult = ::polyline_to(get_handle1(), pPoints, (DWORD) nCount) != false;

      //if (get_handle1() != get_handle2())
      //{
      //   ::i32_point point;
      //   VERIFY(::GetCurrentPositionEx(get_handle1(), &point));
      //   VERIFY(::MoveToEx(get_handle2(), point.x, point.y, nullptr));
      //}
      //return bResult;
      throw ::not_implemented();

      //return false;
   }


   //void graphics::SetColorAdjustment(const COLORADJUSTMENT* pColorAdjust)
   //{

   //   if (::is_null(m_pgdiplusgraphics))
   //   {

   //      return false;

   //   }

   //   //ASSERT(get_handle1() != nullptr);
   //   //bool bResult = false;
   //   //if (get_handle1() != get_handle2())
   //   //   bResult = ::SetColorAdjustment(get_handle1(), pColorAdjust) != false;

   //   //if (get_handle2() != nullptr)
   //   //   bResult = ::SetColorAdjustment(get_handle2(), pColorAdjust) != false;

   //   //return bResult;
   //   throw ::not_implemented();

   //   return false;

   //}


   void graphics::poly_bezier_to(const ::f64_point * ppoints, ::collection::count nCount)
   {

      if (::is_null(m_pgdiplusgraphics))
      {

         //return false;

         throw ::exception(error_null_pointer);

      }

      //ASSERT(get_handle1() != nullptr);
      //bool bResult = ::poly_bezier_to(get_handle1(), pPoints, (DWORD) nCount) != false;

      //if (get_handle1() != get_handle2())
      //{
      //   ::i32_point point;
      //   VERIFY(::GetCurrentPositionEx(get_handle1(), &point));
      //   VERIFY(::MoveToEx(get_handle2(), point.x, point.y, nullptr));
      //}
      //return bResult;
      throw ::not_implemented();

      //return false;

   }


   void graphics::SelectClipPath(::i32 nMode)
   {

      if (::is_null(m_pgdiplusgraphics))
      {

         //return false;

         throw ::exception(error_null_pointer);

      }

      //ASSERT(get_handle1() != nullptr);

      //// output DC always holds the current path
      //if (!::SelectClipPath(get_handle1(), nMode))
      //   return false;

      //// transfer clipping region into the attribute DC
      bool bResult = true;
      //if (get_handle1() != get_handle2())
      //{
      //   HRGN hRgn = ::CreateRectRgn(0, 0, 0, 0);
      //   if (::GetClipRgn(get_handle1(), hRgn) < 0 || !::SelectClipRgn(get_handle2(), hRgn))
      //   {
      //      __trace(trace_category_appmsg, 0, "Error: unable to transfer clip region in graphics::SelectClipPath!\n");
      //      bResult = false;
      //   }
      //   ::DeleteObject(hRgn);
      //}
      //return bResult;
   }


   //::i32 graphics::SelectClipRgn(::draw2d::region* pregion, ::draw2d::enum_combine ecombine)
   //{

   //   if(pregion == nullptr)
   //   {

   //      m_pgdiplusgraphics->ResetClip();

   //   }
   //   else
   //   {

   //      if(ecombine == ::draw2d::e_combine_intersect)
   //      {

   //         m_pgdiplusgraphics->SetClip(pregion->get_os_data<Region *>(this), Gdiplus::CombineModeIntersect);

   //      }
   //      else if(ecombine == ::draw2d::e_combine_add)
   //      {

   //         m_pgdiplusgraphics->SetClip(pregion-> get_os_data<Region * >(this),Gdiplus::CombineModeUnion);

   //      }
   //      else if(ecombine == ::draw2d::e_combine_xor)
   //      {

   //         m_pgdiplusgraphics->SetClip(pregion->get_os_data<Region * >(this),Gdiplus::CombineModeXor);

   //      }
   //      else if(ecombine == ::draw2d::e_combine_copy)
   //      {

   //         m_pgdiplusgraphics->SetClip(pregion->get_os_data<Region * >(this),Gdiplus::CombineModeReplace);

   //      }
   //      else if(ecombine == ::draw2d::e_combine_exclude)
   //      {

   //         m_pgdiplusgraphics->SetClip(pregion->get_os_data<Region * >(this),Gdiplus::CombineModeExclude);

   //      }

   //   }

   //   return 0;

   //}


   /////////////////////////////////////////////////////////////////////////////
   // Special handling for metafile playback

   ::i32 CALLBACK __enum_meta_file_procedure(HDC hDC,
      HANDLETABLE * pHandleTable, METARECORD * pMetaRec, ::i32 nHandles, LPARAM lParam)
   {
      graphics * pdraw2dgraphics = (graphics *)lParam;

      ASSERT_OK(pdraw2dgraphics);

      return pdraw2dgraphics->meta_file_procedure(hDC, pHandleTable, pMetaRec, nHandles);

   }


   ::i32 graphics::meta_file_procedure(HDC hDC, HANDLETABLE * pHandleTable, METARECORD * pMetaRec, ::i32 nHandles)
   {

      //      switch (pMetaRec->rdFunction)
      //      {
      //      // these records have effects different for each graphics derived class
      //      case META_SETMAPMODE:
      //         SetMapMode((::i32)(::i16)pMetaRec->rdParm[0]);
      //         break;
      //      case META_SETWINDOWEXT:
      //         set_window_ext(
      //         (::i32)(::i16)pMetaRec->rdParm[1], (::i32)(::i16)pMetaRec->rdParm[0]);
      //         break;
      //      case META_SETWINDOWORG:
      //         SetWindowOrg(
      //         (::i32)(::i16)pMetaRec->rdParm[1], (::i32)(::i16)pMetaRec->rdParm[0]);
      //         break;
      //      case META_SETVIEWPORTEXT:
      //         set_extents(
      //         (::i32)(::i16)pMetaRec->rdParm[1], (::i32)(::i16)pMetaRec->rdParm[0]);
      //         break;
      //      case META_SETVIEWPORTORG:
      //         SetViewportOrg(
      //         (::i32)(::i16)pMetaRec->rdParm[1], (::i32)(::i16)pMetaRec->rdParm[0]);
      //         break;
      //      case META_SCALEWINDOWEXT:
      //         scale_window_ext(
      //         (::i32)(::i16)pMetaRec->rdParm[3], (::i32)(::i16)pMetaRec->rdParm[2],
      //         (::i32)(::i16)pMetaRec->rdParm[1], (::i32)(::i16)pMetaRec->rdParm[0]);
      //         break;
      //      case META_SCALEVIEWPORTEXT:
      //         ScaleViewportExt(
      //         (::i32)(::i16)pMetaRec->rdParm[3], (::i32)(::i16)pMetaRec->rdParm[2],
      //         (::i32)(::i16)pMetaRec->rdParm[1], (::i32)(::i16)pMetaRec->rdParm[0]);
      //         break;
      //      case META_OFFSETVIEWPORTORG:
      //         OffsetViewportOrg(
      //         (::i32)(::i16)pMetaRec->rdParm[1], (::i32)(::i16)pMetaRec->rdParm[0]);
      //         break;
      //      case META_SAVEDC:
      //         SaveDC();
      //         break;
      //      case META_RESTOREDC:
      //         RestoreDC((::i32)(::i16)pMetaRec->rdParm[0]);
      //         break;
      //      case META_SETBKCOLOR:
      //      {
      //         auto pdraw2dbrush = createø < ::draw2d::brush >();
      //         pdraw2dbrush->create_solid(*(UNALIGNED ::color::color*)&pMetaRec->rdParm[0]);
      //         set(pdraw2dbrush);
      //      }
      //      break;
      //      case META_SETTEXTCOLOR:
      //      {
      //         auto pdraw2dbrush = createø < ::draw2d::brush >();
      //
      //         pdraw2dbrush->create_solid(*(UNALIGNED ::color::color*)&pMetaRec->rdParm[0]);
      //         set(pdraw2dbrush);
      //      }
      //      break;
      //
      //      // need to watch out for set(HFONT), for custom font mapping
      //      case META_SELECTOBJECT:
      //      {
      //         HGDIOBJ hObject = pHandleTable->objectHandle[pMetaRec->rdParm[0]];
      //         UINT nObjType = GetObjectType(hObject);
      //         if (nObjType == 0)
      //         {
      //            // object type is unknown, determine if it is a font
      //            HFONT hStockFont = (HFONT)::GetStockObject(SYSTEM_FONT);
      //            HFONT hFontOld = (HFONT)::set(get_handle1(), hStockFont);
      //            HGDIOBJ hObjOld = ::set(get_handle1(), hObject);
      //            if (hObjOld == hStockFont)
      //            {
      //               // got the stock object back, so must be selecting a font
      //               throw ::not_implemented();
      ////                  set(::draw2d_gdiplus::font::from_handle(pdraw2dgraphics->get_application(), (HFONT)hObject));
      //               break;  // don't play the default record
      //            }
      //            else
      //            {
      //               // didn't get the stock object back, so restore everything
      //               ::set(get_handle1(), hFontOld);
      //               ::set(get_handle1(), hObjOld);
      //            }
      //            // and fall through to PlayMetaFileRecord...
      //         }
      //         else if (nObjType == OBJ_FONT)
      //         {
      //            // play back as graphics::set(::write_text::font*)
      ////               set(::draw2d_gdiplus::font::from_handle(pdraw2dgraphics->get_application(), (HFONT)hObject));
      //            throw ::not_implemented();
      //            break;  // don't play the default record
      //         }
      //      }
      //      // fall through...
      //
      //      default:
      //         ::PlayMetaFileRecord(hDC, pHandleTable, pMetaRec, nHandles);
      //         break;
      //      }

      return 1;

   }


   //void graphics::PlayMetaFile(HMETAFILE hMF)
   //{

   //   if (::is_null(m_pgdiplusgraphics))
   //   {

   //      return false;

   //   }

   //   //if (::GetDeviceCaps(get_handle1(), TECHNOLOGY) == DT_METAFILE)
   //   //{
   //   //   // playing metafile in metafile, just use aura windows API
   //   //   return ::PlayMetaFile(get_handle1(), hMF) != false;
   //   //}

   //   //// for special playback, lParam == pdraw2dgraphics
   //   //return ::EnumMetaFile(get_handle1(), hMF, __enum_meta_file_procedure, (LPARAM)this) != false;

   //   return false;

   //}

   /////////////////////////////////////////////////////////////////////////////
   // Coordinate transforms

   //void graphics::LPtoDP(::f64_size * psize)

   //{
   //   ASSERT(is_memory_segment_ok(psize, sizeof(const ::f64_size &)));


   //   ::f64_size sizeWinExt = GetWindowExt();
   //   ::f64_size sizeVpExt = get_extents();
   //   psize->cx = psize->cx * abs(sizeVpExt.cx) / abs(sizeWinExt.cx);

   //   psize->cy = psize->cy * abs(sizeVpExt.cy) / abs(sizeWinExt.cy);

   //}


   //void graphics::DPtoLP(::f64_size * psize)
   //{

   //   ASSERT(is_memory_segment_ok(psize, sizeof(const ::f64_size &)));

   //   ::f64_size sizeWinExt = GetWindowExt();

   //   ::f64_size sizeVpExt = get_extents();

   //   psize->cx = psize->cx * abs(sizeWinExt.cx) / abs(sizeVpExt.cx);

   //   psize->cy = psize->cy * abs(sizeWinExt.cy) / abs(sizeVpExt.cy);

   //}


   void graphics::_001DrawText(const ::scoped_string & scopedstr, ::f64_rectangle & rectangleParam, const ::e_align & ealign, const ::e_draw_text & edrawtext, bool bMeasure)
   {

      if (::is_null(m_pgdiplusgraphics))
      {

         //return false;

         throw ::exception(error_null_pointer);

      }

      _synchronous_lock synchronouslock(synchronization());

      if (m_pwritetextfont.is_null())
      {

         //return false;

         throw ::exception(error_null_pointer);

      }

      if (m_pgdiplusgraphics == nullptr)
      {

         //return false;

         throw ::exception(error_null_pointer);

      }

      if (m_bTargetRectangleModified)
      {

         defer_on_target_rectangle_update();

      }



      Gdiplus::Status status = Gdiplus::Status::GenericError;

      //if (m_pwritetextfont.is_set() 
      //   && m_ewritetextrendering != m_pwritetextfont->m_erendering
      //   && m_pwritetextfont->m_erendering != ::write_text::e_rendering_undefined)
      //{

      //   set_text_rendering_hint(m_pwritetextfont->m_erendering);

      //}

      //return 

      //::pointer < graphics > p = 

      _gdiplus_draw_text(nullptr, scopedstr, rectangleParam, ealign, edrawtext, m_pwritetextfont, m_pwritetextfont->m_dFontWidth, m_pdraw2dbrush, bMeasure);

   }


   //void graphics::draw_text_ex(const ::scoped_string & scopedstrString,character_count nCount,const i32_rectangle & rectangleParam, const ::e_align & ealign, const ::e_draw_text & edrawtext,LPDRAWTEXTPARAMS lpDTParams)
   //{

   //   if (::is_null(m_pgdiplusgraphics))
   //   {

   //      return false;

   //   }

   //   //if(get_handle1() == nullptr)
   //   //   return -1;

   //   // these flags would modify the string
   //   //ASSERT((nFormat & (DT_END_ELLIPSIS | DT_MODIFYSTRING)) != (DT_END_ELLIPSIS | DT_MODIFYSTRING));
   //   //ASSERT((nFormat & (DT_PATH_ELLIPSIS | DT_MODIFYSTRING)) != (DT_PATH_ELLIPSIS | DT_MODIFYSTRING));
   //   //wstring text.m_wstr = utf8_to_unicode(string(pszString, nCount));

   //   //return ::DrawTextExW(get_handle1(),const_cast<wchar_t *>((const wchar_t *)text.m_wstr),(::i32)wcslen(text.m_wstr),(RECT *) &rectangleParam,nFormat,pDTParams);

   //   throw ::not_implemented();

   //   return false;

   //}


   void graphics::draw_text_ex(const ::scoped_string & scopedstr, const ::f64_rectangle & rectangleParam, const ::e_align & ealign, const ::e_draw_text & edrawtext)
   {

      if (::is_null(m_pgdiplusgraphics))
      {

         //return false;

         throw ::exception(error_null_pointer);

      }

      //ASSERT(get_handle1() != nullptr);
      //// these flags would modify the string
      //ASSERT((nFormat & (DT_END_ELLIPSIS | DT_MODIFYSTRING)) != (DT_END_ELLIPSIS | DT_MODIFYSTRING));
      //ASSERT((nFormat & (DT_PATH_ELLIPSIS | DT_MODIFYSTRING)) != (DT_PATH_ELLIPSIS | DT_MODIFYSTRING));
      //wstring text.m_wstr = utf8_to_unicode(str);
      //return ::DrawTextExW(get_handle1(),const_cast<wchar_t *>((const wchar_t *)text.m_wstr),(::i32)wcslen(text.m_wstr),(RECT *) &rectangleParam,nFormat,pDTParams);
      throw ::not_implemented();

      //return false;

   }


   //void graphics::draw_text_ex(const ::scoped_string & scopedstrString,character_count nCount,const ::f64_rectangle & rectangleParam, const ::e_align & ealign, const ::e_draw_text & edrawtext,LPDRAWTEXTPARAMS lpDTParams)
   //{

   //   if (::is_null(m_pgdiplusgraphics))
   //   {

   //      return false;

   //   }

   //   return ::draw2d::graphics::draw_text_ex(pszString,nCount,rectangleParam,nFormat,lpDTParams);

   //}


   //void graphics::draw_text_ex(const ::scoped_string & scopedstr, const ::f64_rectangle &rectangleParam, const ::e_align & ealign, const ::e_draw_text & edrawtext)
   //{

   //   if (::is_null(m_pgdiplusgraphics))
   //   {

   //      return false;

   //   }

   //   return ::draw2d::graphics::draw_text_ex(str,rectangleParam,ealign, edrawtext);

   //}


   //::collection::count graphics::GetEachCharTextExtent(array < ::f64_size > & sizea, const ::scoped_string & scopedstr)
   //{
   //   sizea.erase_all();
   //   strsize_array iaLen;
   //   character_count iRange = 0;
   //   character_count i = 0;
   //   character_count iLen;
   //   const scoped_string & strStart = str;
   //   const scoped_string & str = pszStart;
   //   while (*psz)
   //   {
   //      const scoped_string & strNext = ::str().utf8_inc(psz);
   //      if (pszNext == nullptr)
   //         break;
   //      iLen = pszNext - psz;
   //      iRange++;
   //      i += iLen;
   //      iaLen.add(i);
   //      if (*pszNext == '\0')
   //         break;
   //      psz = pszNext;
   //   }
   //

   //   for (::i32 iLen : iaLen)
   //   {

   //      sizea.add(get_text_extent(str, iLen));

   //   }



   //   return sizea.get_size();

   //}

   // return Extents per UTF8 Char Boundaries, so there can be lesser
   // "extents" than bytes
   ::collection::count graphics::get_character_extent(::f64_array & daLeft, ::f64_array & daRight, const ::scoped_string & scopedstr, character_count iStartParam, character_count iCountParam)
   {

      if (scopedstr.is_empty())
      {

         return 0;

      }

      if (iCountParam < 0)
      {

         iCountParam += scopedstr.length() - iStartParam + 1;

      }

      _synchronous_lock synchronouslockFontTextMap(::write_text::font::s_pmutexFontTextMap);

      if (m_bTargetRectangleModified)
      {

         defer_on_target_rectangle_update();

      }

      daLeft.erase_all();

      daRight.erase_all();

      wstring wstrBefore(scopedstr.left(iStartParam));

      wstring wstrMiddle(scopedstr.substr(iStartParam, iCountParam));

      m_pwritetextfont->defer_update(this);

      ::cast < ::draw2d_gdiplus::font > pdraw2dgdiplusfont = m_pwritetextfont;

      Gdiplus::Font * pgdiplusfont = pdraw2dgdiplusfont->m_pgdiplusfont;

      if (::is_null(pgdiplusfont))
      {

         throw ::exception(error_null_pointer);

      }

      auto & text = m_pwritetextfont->m_mapFontText[scopedstr];

      if (text.get_item(::write_text::font::text::e_size_backend_draw_text)->get_text().is_empty())
      {

         text.get_item(::write_text::font::text::e_size_backend_draw_text)->set_text(scopedstr);

      }

      ::collection::count cLength = text.get_item(::write_text::font::text::e_size_backend_draw_text)->get_text().length();

      ::collection::count cBeg = wstrBefore.length();

      ::collection::index cEnd = cBeg + wstrMiddle.length();

      ::i32 iCount = 0;

      ::i32 iStart = (::i32)cBeg;

      ::i32 cMaxMeasureCharacterRanges = 32;

      array < Gdiplus::CharacterRange > characterrangea;

      characterrangea.set_size(32);

      Gdiplus::StringFormat strFormat(Gdiplus::StringFormat::GenericTypographic());

      strFormat.SetFormatFlags(strFormat.GetFormatFlags()
         | Gdiplus::StringFormatFlagsMeasureTrailingSpaces
         | Gdiplus::StringFormatFlagsNoClip
         | Gdiplus::StringFormatFlagsNoWrap
         | Gdiplus::StringFormatFlagsNoFitBlackBox
      );

      bool bFirst = true;

      while (true)
      {

         iStart += iCount;

         if (iStart >= cEnd)
         {

            break;

         }

         iCount = minimum((::i32)cMaxMeasureCharacterRanges, (::i32)(cEnd - iStart));


         for (::collection::index j = 0; j < iCount; j++)
         {

            characterrangea[j].First = (::i32)(iStart + j);

            characterrangea[j].Length = 1;

         }

         Gdiplus::Status status = strFormat.SetMeasurableCharacterRanges(iCount, characterrangea.data());

         ::i32 count = strFormat.GetMeasurableCharacterRangeCount();

         //#undef ___new

         array < Gdiplus::Region, const Gdiplus::Region &, ::allocator::rawcopy < Gdiplus::Region> > regiona;

         regiona.set_size(count);

         //regiona.insert_at(5, region)
         //#define ___new ACME_NEW

         Gdiplus::RectF box(0.0f, 0.0f, 0.0f, 0.0f);

         Gdiplus::PointF origin(0.f, 0.f);

         //::cast < ::draw2d_gdiplus::font > pdraw2dgdiplusfont = m_pwritetextfont;

         //auto pgdiplusfont = pdraw2dgdiplusfont->m_pgdiplusfont;

         m_pgdiplusgraphics->MeasureCharacterRanges(text.get_item(::write_text::font::text::e_size_backend_draw_text)->get_text(), (INT)cLength, pgdiplusfont, box, &strFormat, count, regiona.data());

         Gdiplus::RectF rectangleBound;

         for (::i32 i = 0; i < count; i++)
         {

            regiona[i].GetBounds(&rectangleBound, m_pgdiplusgraphics);

            wchar_t wch = text.get_item(::write_text::font::text::e_size_backend_draw_text)->get_text().c_str()[i + iStart];

            auto iUtf8Length = unicode_to_utf8_length(wch);

            for (::collection::index iAnsiChar = 0; iAnsiChar < iUtf8Length; iAnsiChar++)
            {

               ::f64 dLeft = rectangleBound.GetLeft();

               ::f64 dRight = rectangleBound.GetRight();

               daLeft.add(dLeft);

               daRight.add(dRight);

            }

         }

      }

      return daLeft.get_size();

   }


   ::f64_size graphics::get_text_extent(const scoped_string & scopedstrString, character_count iIndex)
   {

      if (::is_null(m_pgdiplusgraphics))
      {

         throw ::exception(error_wrong_state, "invalid state");

      }

      if (scopedstrString.is_empty() || iIndex == 0)
      {

         return ::f64_size(0, 0);

      }

      if (iIndex > scopedstrString.size())
         return ::f64_size(0, 0);

      if (iIndex < 0)
         return ::f64_size(0, 0);

      if (m_bTargetRectangleModified)
      {

         defer_on_target_rectangle_update();

      }

      string str(scopedstrString);

      wstring wstr(str);

      wstring wstrRange = utf8_to_unicode({ scopedstrString.data(), iIndex });

      Gdiplus::CharacterRange charRanges[1] = { Gdiplus::CharacterRange(0, (INT)wstrRange.length()) };

      Gdiplus::StringFormat strFormat(Gdiplus::StringFormat::GenericTypographic());

      strFormat.SetMeasurableCharacterRanges(1, charRanges);

      strFormat.SetFormatFlags(strFormat.GetFormatFlags()
         | Gdiplus::StringFormatFlagsNoClip | Gdiplus::StringFormatFlagsMeasureTrailingSpaces
      );

      ::i32 count = strFormat.GetMeasurableCharacterRangeCount();

      Gdiplus::PointF origin(0, 0);

      m_pwritetextfont->defer_update(this);

      ::cast < ::draw2d_gdiplus::font > pdraw2dgdiplusfont = m_pwritetextfont;

      auto pgdiplusfont = pdraw2dgdiplusfont->m_pgdiplusfont;

      if (count <= 0)
      {

         Gdiplus::RectF box(0.0f, 0.0f, 0.0f, 0.0f);

         wstring wstrRange = utf8_to_unicode({ scopedstrString.data(), iIndex });

         m_pgdiplusgraphics->MeasureString(wstrRange, (::i32)wstrRange.length(), pgdiplusfont, origin, Gdiplus::StringFormat::GenericTypographic(), &box);

         return ::f64_size((LONG)(box.Width * m_pwritetextfont->m_dFontWidth), (LONG)(box.Height));

      }

      Gdiplus::RectF box(0.0f, 0.0f, 128.0f * 1024.0f, 128.0f * 1024.0f);

      //#undef ___new

      Gdiplus::Region * pCharRangeRegions = øraw_new Gdiplus::Region[count];

      //#define ___new ACME_NEW

      m_pgdiplusgraphics->MeasureCharacterRanges(wstr, (INT)wstr.length(), pgdiplusfont, box, &strFormat, (INT)count, pCharRangeRegions);

      for (::collection::index i = 1; i < count; i++)
      {

         pCharRangeRegions[0].Union(&pCharRangeRegions[i]);

      }

      Gdiplus::RectF rectangleBound;

      pCharRangeRegions[0].GetBounds(&rectangleBound, m_pgdiplusgraphics);

      delete[] pCharRangeRegions;

      Gdiplus::SizeF size;

      rectangleBound.GetSize(&size);

      // A prefix extent is an endpoint relative to the drawing origin.
      // Region width alone drops the left bearing and displaces the caret.
      return ::f64_size((::f64)(rectangleBound.GetRight() * m_pwritetextfont->m_dFontWidth), (::f64)(size.Height));

   }


   ::f64_size graphics::GetTextBegin(const scoped_string & strString, ::collection::index iIndex)
   {

      if (strString.is_empty())
      {

         return ::f64_size(0, 0);

      }

      if (iIndex > strString.size())
         return ::f64_size(0, 0);

      if (iIndex < 0)
         return ::f64_size(0, 0);

      wstring wstr(strString);

      wstring wstrRange(::string(strString.begin(), iIndex));

      Gdiplus::CharacterRange charRanges[1] = { Gdiplus::CharacterRange(INT(wstrRange.length()), INT(wstr.length() - wstrRange.length())) };

      Gdiplus::StringFormat strFormat(Gdiplus::StringFormat::GenericTypographic());

      strFormat.SetMeasurableCharacterRanges(1, charRanges);

      strFormat.SetFormatFlags(strFormat.GetFormatFlags()
         | Gdiplus::StringFormatFlagsNoClip | Gdiplus::StringFormatFlagsMeasureTrailingSpaces
      );

      ::i32 count = strFormat.GetMeasurableCharacterRangeCount();

      Gdiplus::PointF origin(0, 0);

      m_pwritetextfont->defer_update(this);

      ::cast < ::draw2d_gdiplus::font > pdraw2dgdiplusfont = m_pwritetextfont;

      auto pgdiplusfont = pdraw2dgdiplusfont->m_pgdiplusfont;

      if (::is_null(pgdiplusfont))
      {

         throw ::exception(error_wrong_state);

      }

      if (count <= 0)
      {
      
         Gdiplus::RectF box(0.0f, 0.0f, 0.0f, 0.0f);

         wstrRange = ::string(strString.begin(), iIndex);

         m_pgdiplusgraphics->MeasureString(wstrRange, (::i32)wstrRange.length(), pgdiplusfont, origin, Gdiplus::StringFormat::GenericTypographic(), &box);

         return ::f64_size((LONG)(box.Width * m_pwritetextfont->m_dFontWidth), (LONG)(box.Height));

      }

      Gdiplus::RectF box(0.0f, 0.0f, 128.0f * 1024.0f, 128.0f * 1024.0f);

      //#undef ___new

      Gdiplus::Region * pCharRangeRegions = øraw_new Gdiplus::Region[count];

      //#define ___new ACME_NEW

      m_pgdiplusgraphics->MeasureCharacterRanges(wstr, (INT)wstr.length(), pgdiplusfont, box, &strFormat, (INT)count, pCharRangeRegions);

      for (::collection::index i = 1; i < count; i++)
      {

         pCharRangeRegions[0].Union(&pCharRangeRegions[i]);

      }

      Gdiplus::RectF rectangleBound;

      pCharRangeRegions[0].GetBounds(&rectangleBound, m_pgdiplusgraphics);

      delete[] pCharRangeRegions;

      return ::f64_size((::f64)(rectangleBound.X * m_pwritetextfont->m_dFontWidth), (::f64)(rectangleBound.Height));

   }


   ::f64_size graphics::get_text_extent(const ::scoped_string & scopedstr)
   {

      ::write_text::font_pointer pwritetextfont(m_pwritetextfont);

      if (!pwritetextfont || scopedstr.is_empty())
      {

         return ::f64_size(0, 0);

      }

      if (m_bTargetRectangleModified)
      {

         defer_on_target_rectangle_update();

      }

      pwritetextfont->defer_update(this);

      {

         _synchronous_lock synchronouslockFontTextMap(::write_text::font::s_pmutexFontTextMap);

         auto & text = pwritetextfont->m_mapFontText[scopedstr];

         if (text.get_item(::write_text::font::text::e_size_unbounded)->has_size())
         {

            return text.get_item(::write_text::font::text::e_size_unbounded)->get_size();

         }

         if (text.get_item(::write_text::font::text::e_size_backend_draw_text)->get_text().is_empty())
         {

            text.get_item(::write_text::font::text::e_size_backend_draw_text)->set_text(scopedstr);

         }

      }

      auto size = this->_get_text_extent(scopedstr);

      _synchronous_lock synchronouslockFontTextMap(::write_text::font::s_pmutexFontTextMap);

      auto & text = pwritetextfont->m_mapFontText[scopedstr];

      if (text.get_item(::write_text::font::text::e_size_backend_draw_text)->get_text().is_empty())
      {

         text.get_item(::write_text::font::text::e_size_backend_draw_text)->set_text(scopedstr);

      }

      text.get_item(::write_text::font::text::e_size_unbounded)->set_size(size);

      return text.get_item(::write_text::font::text::e_size_unbounded)->get_size();

   }


   ::f64_size graphics::_get_text_extent(const ::scoped_string & scopedstr)
   {

      ::write_text::font_pointer pfontText(m_pwritetextfont);

      if (!pfontText || scopedstr.is_empty())
      {

         return ::f64_size(0, 0);

      }

      if (m_bTargetRectangleModified)
      {

         defer_on_target_rectangle_update();

      }

      pfontText->defer_update(this);

      Gdiplus::RectF box{};

      Gdiplus::PointF origin(0, 0);

      Gdiplus::StringFormat stringformat(Gdiplus::StringFormat::GenericTypographic());

      stringformat.SetFormatFlags(stringformat.GetFormatFlags()
         | Gdiplus::StringFormatFlagsNoClip | Gdiplus::StringFormatFlagsMeasureTrailingSpaces
      );

      ::cast < ::draw2d_gdiplus::font > pdraw2dgdiplusfont = pfontText;

      auto pgdiplusfont = pdraw2dgdiplusfont->m_pgdiplusfont;

      if (::is_null(pgdiplusfont))
      {

         return ::f64_size(0.0, 0.0);

      }

      ::wstring wstr(scopedstr);

      auto status = m_pgdiplusgraphics->MeasureString(wstr.c_str(), (INT) wstr.size(), pgdiplusfont, origin, &stringformat, &box);

      if (status != Gdiplus::Ok)
      {

         throw ::exception(error_failed);

      }

      auto size = ::f64_size((::f64)(box.Width * m_pwritetextfont->m_dFontWidth), (::f64)(box.Height));

      return size;

      /*if(get_handle2() == nullptr)
         return ::f64_size(0, 0);
      ::f64_size ::f64_size;
      string str(pszString, nCount);

      wstring text.m_wstr = utf8_to_unicode(str);
      if(!::GetTextExtentPoint32W(get_handle2(), text.m_wstr, (::i32)text.m_wstr.get_length(), &::f64_size))
      {
         return const ::f64_size & size(0, 0);
      }
      return ::f64_size;*/
   }

   //::f64_size graphics::get_text_extent(const ::scoped_string & scopedstr)
   //{
   //   /*      if(get_handle2() == nullptr)
   //            return ::f64_size(0, 0);
   //         ::f64_size ::f64_size;
   //         wstring text.m_wstr = utf8_to_unicode(str);
   //         if(!::GetTextExtentPoint32W(get_handle2(), text.m_wstr, (::i32)text.m_wstr.get_length(), &::f64_size))
   //         {
   //            return const ::f64_size & size(0, 0);
   //         }
   //         return ::f64_size;*/

   //   //class ::f64_size ::f64_size;

   //   //if(!get_text_extent(::f64_size, str, (::i32) str.length(), (::i32) str.length()))
   //   //   return const ::f64_size & size(0, 0);

   //   return get_text_extent(str);

   //   //return const ::f64_size & size(0, 0);

   //   //return const ::f64_size & size((long) size.cx, (long) size.cy);

   //   /*if(m_pgdiplusgraphics == nullptr)
   //      return ::f64_size(0, 0);

   //   wstring text.m_wstr = utf8_to_unicode(str);

   //   Gdiplus::RectF box;

   //   Gdiplus::PointF origin(0, 0);


   //   if(m_pgdiplusgraphics == nullptr)
   //      return ::f64_size(0, 0);

   //   try
   //   {
   //      m_pgdiplusgraphics->MeasureString(text.m_wstr, (::i32) text.m_wstr.get_length(), m_pwritetextfont->get_os_data < Font * >(this), origin, &box);
   //   }
   //   catch(...)
   //   {
   //      return ::f64_size(0, 0);
   //   }

   //   return ::f64_size((::i64) (box.Width * m_fontxyz.m_dFontWidth), (::i64) box.Height);*/

   //}


   //::f64_size graphics::GetOutputTextExtent(const scoped_string & strString, character_count nCount)
   //{

   //   //ASSERT(get_handle1() != nullptr);
   //   //::f64_size ::f64_size;
   //   //string str(pszString, nCount);

   //   //wstring text.m_wstr = utf8_to_unicode(str);
   //   //VERIFY(::GetTextExtentPoint32W(get_handle1(), text.m_wstr, (::i32)text.m_wstr.get_length(), &::f64_size));
   //   //return ::f64_size;

   //   return nullptr;
   //   
   ////}


   //}


   //::f64_size graphics::GetOutputTextExtent(const ::scoped_string & scopedstr)
   //{

   //   //ASSERT(get_handle1() != nullptr);

   //   //::f64_size ::f64_size;

   //   //wstring text.m_wstr = utf8_to_unicode(str);

   //   //VERIFY(::GetTextExtentPoint32W(get_handle1(), text.m_wstr, (::i32)text.m_wstr.get_length(), &::f64_size));

   //   //return ::f64_size;

   //   return nullptr;

   //}


   //::f64_size graphics::get_text_extent(const scoped_string & strString, character_count iIndex)
   //{

   //   if (::is_null(m_pgdiplusgraphics))
   //   {

   //      //return false;

   //      throw ::exception(error_null_pointer);

   //   }

   //   if (m_pwritetextfont.is_null())
   //      throw ::exception(error_null_pointer);
   //   //return false;

   //   if (strString.is_empty())
   //      throw ::exception(error_null_pointer);
   //   //return false;

   //   //if (nCount < 0)
   //     // nCount = strlen(pszString);


   //   if (iIndex > strString.size())
   //      throw ::exception(error_null_pointer);
   //   //return false;

   //   if (iIndex < 0)
   //      throw ::exception(error_null_pointer);
   //   //return false;

   //   m_pwritetextfont->defer_update(this, 0);

   //   wstring wstr = strString;

   //   character_count iRange = 0;
   //   character_count i = 0;
   //   character_count iLen;
   //   const_char_pointer psz = strString.begin();

   //   while (i < iIndex)
   //   {
   //      try
   //      {
   //         iLen = get_utf8_char_length(psz);
   //      }
   //      catch (...)
   //      {
   //         break;
   //      }
   //      if (iLen < 0)
   //         break;
   //      iRange++;
   //      i += iLen;
   //      if (i >= iIndex)
   //         break;
   //      try
   //      {
   //         psz += iLen;
   //      }
   //      catch (...)
   //      {
   //         break;
   //      }
   //      if (psz == nullptr)
   //         break;
   //      if (*psz == '\0')
   //         break;
   //   }

   //   Gdiplus::CharacterRange charRanges[1] = { Gdiplus::CharacterRange(0, (INT)iRange) };

   //   Gdiplus::StringFormat strFormat(Gdiplus::StringFormat::GenericTypographic());
   //   //Gdiplus::StringFormat strFormat;

   //   strFormat.SetMeasurableCharacterRanges(1, charRanges);

   //   strFormat.SetFormatFlags(strFormat.GetFormatFlags()
   //      | Gdiplus::StringFormatFlagsNoClip | Gdiplus::StringFormatFlagsMeasureTrailingSpaces
   //   );

   //   ::i32 count = strFormat.GetMeasurableCharacterRangeCount();

   //   //#undef ___new

   //   Gdiplus::Region * pCharRangeRegions = ___new Gdiplus::Region[count];


   //   //#define ___new ACME_NEW

   //         //Gdiplus::RectF box(0.0f, 0.0f, 128.0f * 1024.0f, 128.0f * 1024.0f);

   //   Gdiplus::PointF origin(0, 0);

   //   // Generate a on_layout i32_rectangle for the text

   //   Gdiplus::RectF layoutRect(0, 0, 10000, 10000);

   //   Gdiplus::Status status = m_pgdiplusgraphics->MeasureString(wstr, (INT)nCount, m_pwritetextfont->get_os_data < Gdiplus::Font * >(this), origin, &layoutRect);

   //   // Prevent clipping

   //   //StringFormat strFormat( StringFormat::GenericTypographic() );
   //   //status = ((graphics *)this)->m_pgdiplusgraphics->SetFormatFlags( StringFormatFlagsNoWrap | StringFormatFlagsNoClip );

   //   //m_pgdiplusgraphics->MeasureString(text.m_wstr, (::i32) text.m_wstr.get_length(), m_pwritetextfont->get_os_data < Font * >(this), origin, Gdiplus::StringFormat::GenericTypographic(), &box);

   //   m_pgdiplusgraphics->MeasureCharacterRanges(wstr, (INT)nCount, m_pwritetextfont->get_os_data < Gdiplus::Font * >(this), layoutRect, &strFormat, (INT)count, pCharRangeRegions);

   //   Gdiplus::Region * pregion = nullptr;


   //   if (count > 0)
   //   {

   //      pregion = pCharRangeRegions[0].Clone();

   //   }

   //   for (i = 1; i < count; i++)
   //   {
   //      pregion->Union(&pCharRangeRegions[i]);
   //   }

   //   delete[] pCharRangeRegions;

   //   if (pregion == nullptr)
   //   {

   //      //return false;

   //      throw ::exception(error_null_pointer);

   //   }

   //   Gdiplus::RectF rectangleBound;

   //   pregion->GetBounds(&rectangleBound, m_pgdiplusgraphics);

   //   delete pregion;

   //   Gdiplus::SizeF ::f32_size;

   //   rectangleBound.GetSize(&::f32_size);

   //   size.cx = ::f32_size.Width * m_pwritetextfont->m_dFontWidth;

   //   size.cy = ::f32_size.Height;

   //   //return true;

   //}


   //::f64_size graphics::get_text_extent(const scoped_string & strString, character_count iIndex)
   //{

   //   if (::is_null(m_pgdiplusgraphics))
   //   {

   //      //return false;

   //      throw ::exception(error_null_pointer);

   //   }

   //   wstring wstr = strString;


   //   Gdiplus::RectF box;

   //   Gdiplus::PointF origin(0, 0);

   //   Gdiplus::StringFormat strFormat(Gdiplus::StringFormat::GenericTypographic());

   //   strFormat.SetFormatFlags(strFormat.GetFormatFlags()
   //      | Gdiplus::StringFormatFlagsNoClip | Gdiplus::StringFormatFlagsMeasureTrailingSpaces
   //   );
   //   bool bOk = true;

   //   try
   //   {

   //      if (m_pgdiplusgraphics->MeasureString(wstr, (::i32)wstr.get_length(), m_pwritetextfont->get_os_data < Gdiplus::Font * >(this), origin, &strFormat, &box) != Gdiplus::Status::Ok)
   //      {

   //         bOk = false;

   //      }

   //   }
   //   catch (...)
   //   {
   //      bOk = false;
   //   }

   //   if (!bOk)
   //      throw ::exception(error_null_pointer);
   //   //return false;

   //   size.cx = box.Width * m_pwritetextfont->m_dFontWidth;

   //   size.cy = box.Height;

   //   //return true;

   //}


//::f64_size graphics::get_text_extent(const ::scoped_string & scopedstr)
//   {
//
//      if (::is_null(m_pgdiplusgraphics) && ::is_null(m_pwritetextfont))
//      {
//
//         //return false;
//
//         throw ::exception(error_null_pointer);
//
//      }
//
//      wstring wstr = scopedstr;
//
//      Gdiplus::RectF box;
//
//      Gdiplus::PointF origin(0, 0);
//
//      m_pwritetextfont->defer_update(this, 0);
//
//      bool bOk = true;
//
//      try
//      {
//
//         if (m_pgdiplusgraphics->MeasureString(wstr, (::i32)wstr.get_length(), m_pwritetextfont->get_os_data < Gdiplus::Font * >(this), origin, &box) != Gdiplus::Status::Ok)
//         {
//
//            bOk = false;
//
//         }
//
//      }
//      catch (...)
//      {
//
//         bOk = false;
//
//      }
//
//      if (!bOk)
//      {
//
//         //return false;
//
//         throw ::exception(error_null_pointer);
//
//      }
//
//      size.cx = box.Width * m_pwritetextfont->m_dFontWidth;
//
//      size.cy = box.Height;
//
//      //return true;
//
//   }


   //void graphics::fill_rectangle(const ::f64_rectangle & rectangle, const ::color::color & color)
   //{

   //   try
   //   {

   //      if(m_pgdiplusgraphics == nullptr)
   //         return;

   //      auto emodeOld = m_pgdiplusgraphics->GetSmoothingMode();

   //      //if(emodeOld != Gdiplus::SmoothingModeNone)
   //      //{

   //      //   m_pgdiplusgraphics->SetSmoothingMode(Gdiplus::SmoothingModeNone);

   //      //}

   //      Gdiplus::SolidBrush b(Gdiplus::Color(color.m_iA, color.m_iR, color.m_iG, color.m_iB));

   //      m_pgdiplusgraphics->FillRectangle(&b, rectangle.left, rectangle.top, rectangle.width(), rectangle.height());

   //      //if (emodeOld != Gdiplus::SmoothingModeNone)
   //      //{

   //      //   m_pgdiplusgraphics->SetSmoothingMode(emodeOld);

   //      //}

   //   }
   //   catch(...)
   //   {

   //   }

   //}


   void graphics::TextOutRaw(::f64 x, ::f64 y, const ::scoped_string & scopedstr)
   {

      if (m_bTargetRectangleModified)
      {

         defer_on_target_rectangle_update();

      }

      if (scopedstr.is_empty())
      {

         return;

         //throw ::exception(error_null_pointer);

      }

      if (::is_null(m_pdraw2dbrush))
      {

         throw ::exception(error_null_pointer);

      }

      if (::is_null(m_pgdiplusgraphics))
      {

         //return false;

         throw ::exception(error_null_pointer);

      }

      if (!m_pwritetextfont)
      {

         //return false;

         throw ::exception(error_null_pointer);

      }

      m_pwritetextfont->defer_update(this);

      ::cast < ::draw2d_gdiplus::font > pdraw2dgdiplusfont = m_pwritetextfont;

      Gdiplus::Font * pgdiplusfont = pdraw2dgdiplusfont->m_pgdiplusfont;

      if (::is_null(pgdiplusfont))
      {

         throw ::exception(error_wrong_state);

      }

      auto psystem = system();

      auto paurasystem = psystem;

      auto pdraw2d = paurasystem->draw2d();

      auto pwritetext = pdraw2d->write_text();

      _synchronous_lock synchronouslockFontTextMap(::write_text::font::s_pmutexFontTextMap);

      ::write_text::font::text* ptext = nullptr;

      ::write_text::font::text text2;

      if (m_pwritetextfont->m_bCacheLayout)
      {

         ptext = &m_pwritetextfont->m_mapFontText[scopedstr];

      }
      else
      {

         ptext = &text2;

      }

      if (ptext->get_item(::write_text::font::text::e_size_backend_draw_text)->get_text().is_empty())
      {

         ptext->get_item(::write_text::font::text::e_size_backend_draw_text)->set_text(scopedstr);

      }

      if (m_pgdiplusgraphics == nullptr)
      {

         //return false;

         throw ::exception(error_null_pointer);

      }

      Gdiplus::Status status = Gdiplus::GenericError;

      m_pdraw2dbrush->defer_update(this);

      ::cast < ::draw2d_gdiplus::brush>pdraw2dgdiplusbrush = m_pdraw2dbrush;

      auto pgdiplusbrush = pdraw2dgdiplusbrush->m_pgdiplusbrush;

      if (::is_null(pgdiplusbrush))
      {

         throw ::exception(error_wrong_state);

      }

      //if (::is_null(m_pgdiplusgraphicspath))
      //{

      //   throw ::exception(error_null_pointer);

      //}

      //if (::is_null(m_pdraw2dbrush))
      //{

      //   throw ::exception(error_null_pointer);

      //}

      ::draw2d::save_context savecontext(this);

      //if(get_alpha_mode() == ::draw2d::e_alpha_mode_blend)
      //{

      //if (m_pwritetextfont->m_erendering)

         // set_alpha_mode(::draw2d::e_alpha_mode_blend);

      //if (m_pwritetextfont->m_erendering != ::write_text::e_rendering_anti_alias)
      //if (m_pwritetextfont->m_erendering != ::write_text::e_rendering_undefined)
      //if (m_pwritetextfont->m_erendering != ::write_text::e_rendering_anti_alias)
      //if (m_pwritetextfont->m_erendering != ::write_text::e_rendering_undefined)
      //{

      //   if (m_ewritetextrendering != m_pwritetextfont->m_erendering)
      //   {

      //      set_text_rendering_hint(m_pwritetextfont->m_erendering);

      //   }

      //}



#define DRAW_BASE_LINE 0

#if DRAW_BASE_LINE

      {
         auto s = get_text_extent(scopedstr);

         auto a = m_pwritetextfont->get_ascent(this);

         ::f64_point p1(x, y+a);
         ::f64_point p2(x + s.cx, y+a);

         auto pdraw2dpen = createø < ::draw2d::pen >();

         pdraw2dpen->m_color = ::color::red;

         pdraw2dpen->m_dWidth = 1.0;

         ::draw2d::graphics::set(pdraw2dpen);

         ::draw2d::graphics::draw_line(p1, p2);


      }

#endif



      Gdiplus::StringFormat format(Gdiplus::StringFormat::GenericTypographic());


      format.SetFormatFlags((format.GetFormatFlags()
         & ~Gdiplus::StringFormatFlagsLineLimit)
         | Gdiplus::StringFormatFlagsNoClip
      );

      format.SetAlignment(Gdiplus::StringAlignmentNear);
      format.SetLineAlignment(Gdiplus::StringAlignmentNear);

      if (m_pwritetextfont->m_dFontWidth == 1.0)
      {

         ::Gdiplus::PointF origin((Gdiplus::REAL)x, (Gdiplus::REAL)y);

         if (m_pgdiplusgraphicspath != nullptr)
         {

            FLOAT fDpiX = m_pgdiplusgraphics->GetDpiX();

            Gdiplus::GraphicsPath path;

            Gdiplus::FontFamily fontfamily;

            pgdiplusfont->GetFamily(&fontfamily);

            ::f64 d1 = pgdiplusfont->GetSize() * m_pgdiplusgraphics->GetDpiX() / 72.0;

            ::f64 d2 = fontfamily.GetEmHeight(pgdiplusfont->GetStyle());

            ::f64 d3 = d1 * d2;

            status = path.AddString(ptext->get_item(::write_text::font::text::e_size_backend_draw_text)->get_text(), (INT)ptext->get_item(::write_text::font::text::e_size_backend_draw_text)->get_text().length(), &fontfamily, pgdiplusfont->GetStyle(), (Gdiplus::REAL)d1, origin, &format);

            m_pgdiplusgraphicspath->AddPath(&path, false);

         }
         else
         {

            auto eTextRenderingMode = m_pgdiplusgraphics->GetTextRenderingHint();

            auto eCompositingMode = m_pgdiplusgraphics->GetCompositingMode();

            if (eCompositingMode == ::Gdiplus::CompositingModeSourceCopy)
            {

               if (eTextRenderingMode != ::Gdiplus::TextRenderingHintAntiAlias)
               {

                  m_pgdiplusgraphics->SetTextRenderingHint(::Gdiplus::TextRenderingHintAntiAlias);

               }

            }

            auto wstrText = ptext->get_item(::write_text::font::text::e_size_backend_draw_text)->get_text();

            auto pszText = wstrText.c_str();

            auto iLenText = (INT)wstrText.length();

            status = m_pgdiplusgraphics->DrawString(wstrText.c_str(), iLenText, pgdiplusfont, origin, &format, pgdiplusbrush);

            if (eCompositingMode == Gdiplus::CompositingModeSourceCopy)
            {

               if (eTextRenderingMode != ::Gdiplus::TextRenderingHintAntiAlias)
               {

                  m_pgdiplusgraphics->SetTextRenderingHint(eTextRenderingMode);

               }

            }

         }

      }
      else
      {

         g_keep k(m_pgdiplusgraphics);

         ::Gdiplus::PointF origin(x, y);

         FLOAT fDpiX = m_pgdiplusgraphics->GetDpiX();

         Gdiplus::Matrix m;

         m_pgdiplusgraphics->GetTransform(&m);

         Gdiplus::REAL elementsA[6];

         m.GetElements(elementsA);

         ::auto_pointer < Gdiplus::Matrix > pmatrixNew;

         if (m_pgdiplusgraphicspath != nullptr)
         {

            //#undef ___new

            pmatrixNew = ::as_pointer(new Gdiplus::Matrix());

            //#define ___new ACME_NEW

         }
         else
         {

            pmatrixNew = ::as_pointer(m.Clone());

         }

         Gdiplus::REAL elementsB[6];

         pmatrixNew->GetElements(elementsB);

         auto offsetX = pmatrixNew->OffsetX();

         auto offsetY = pmatrixNew->OffsetY();

         pmatrixNew->Translate(-x-offsetX, -y - offsetY, Gdiplus::MatrixOrderAppend);

         pmatrixNew->Scale((Gdiplus::REAL)m_pwritetextfont->m_dFontWidth, (Gdiplus::REAL)1.0, Gdiplus::MatrixOrderAppend);

         pmatrixNew->Translate(x + offsetX, y + offsetY, Gdiplus::MatrixOrderAppend);

         if (m_pgdiplusgraphicspath != nullptr)
         {

            Gdiplus::GraphicsPath path;

            Gdiplus::FontFamily fontfamily;

            pgdiplusfont->GetFamily(&fontfamily);

            ::f64 d1 = pgdiplusfont->GetSize() * m_pgdiplusgraphics->GetDpiX() / 72.0;

            ::f64 d2 = fontfamily.GetEmHeight(pgdiplusfont->GetStyle());

            ::f64 d3 = d1 * d2;

            status = path.AddString(ptext->get_item(::write_text::font::text::e_size_backend_draw_text)->get_text(), (INT)ptext->get_item(::write_text::font::text::e_size_backend_draw_text)->get_text().length(), &fontfamily, pgdiplusfont->GetStyle(), (Gdiplus::REAL)d1, origin, &format);

            path.Transform(pmatrixNew);

            m_pgdiplusgraphicspath->AddPath(&path, false);

         }
         else
         {

            m_pgdiplusgraphics->SetTransform(pmatrixNew);

            status = m_pgdiplusgraphics->DrawString(ptext->get_item(::write_text::font::text::e_size_backend_draw_text)->get_text(), (INT)ptext->get_item(::write_text::font::text::e_size_backend_draw_text)->get_text().length(), pgdiplusfont, origin, &format, pgdiplusbrush);

            m_pgdiplusgraphics->SetTransform(&m);

         }
      }

      //return status  == Gdiplus::Status::Ok;

   }


   void graphics::line(::f64 x1, ::f64 y1, ::f64 x2, ::f64 y2)
   {

      if (::is_null(m_pgdiplusgraphics))
      {

         //return false;

         throw ::exception(error_null_pointer);


      }

      _synchronous_lock synchronouslock(synchronization());

      if (m_bTargetRectangleModified)
      {

         defer_on_target_rectangle_update();

      }

      m_pdraw2dpen->defer_update(this);

      ::cast < ::draw2d_gdiplus::pen>pdraw2dgdipluspen = m_pdraw2dpen;

      auto pgdipluspen = pdraw2dgdipluspen->m_pgdipluspen;

      if (pdraw2dgdipluspen->m_epenalign != ::draw2d::e_pen_align_center)
      {

         pgdipluspen->SetAlignment(Gdiplus::PenAlignment::PenAlignmentCenter);

         pdraw2dgdipluspen->m_epenalign = ::draw2d::e_pen_align_center;

      }

      m_pgdiplusgraphics->DrawLine(
         pgdipluspen,
         Gdiplus::PointF((Gdiplus::REAL)x1, (Gdiplus::REAL)y1), 
         Gdiplus::PointF((Gdiplus::REAL)x2, (Gdiplus::REAL)y2));


      m_pointCurrent.x = x2;
      m_pointCurrent.y = y2;


      //return true;

   }

   //void graphics::line_to(::f64 x, ::f64 y)

   //{

   //   _synchronous_lock synchronouslock(synchronization());

   //   if(m_pdraw2dpen.cast < ::draw2d_gdiplus::pen >()->m_egdiplusalign != Gdiplus::PenAlignment::PenAlignmentCenter)
   //   {

   //      //m_pdraw2dpen->get_os_data < Pen * >(this)->SetAlignment(Gdiplus::PenAlignment::PenAlignmentCenter);

   //      m_pdraw2dpen->m_epenalign = ::draw2d::e_pen_align_center;

   //      m_pdraw2dpen->set_modified();

   //      //m_pdraw2dpen.cast < ::draw2d_gdiplus::pen >()-

   //   }

   //   auto pdraw2dpen = m_pdraw2dpen->get_os_data < Pen* >(this);

   //   if (fmod(m_point.x, 1.0) != 0.0 || fmod(m_point.y, 1.0) != 0)
   //   {

   //      m_pgdiplusgraphics->DrawLine(pdraw2dpen, Gdiplus::PointF((Gdiplus::REAL)m_point.x, (Gdiplus::REAL)m_point.y), Gdiplus::PointF((Gdiplus::REAL)point.x, (Gdiplus::REAL) point.y));


   //   }
   //   else
   //   {

   //      m_pgdiplusgraphics->DrawLine(pdraw2dpen, Gdiplus::Point((INT)m_point.x, (INT)m_point.y), Gdiplus::Point((INT)point.x, (INT)point.y));


   //   }

   //   m_point.x = point.x;

   //   m_point.y = point.y;

   //   return true;

   //}


   void graphics::line(::f64 x1, ::f64 y1, ::f64 x2, ::f64 y2, ::draw2d::pen * ppenParam)
   {

      if (::is_null(ppenParam))
      {

         //return false;

         throw ::exception(error_null_pointer);


      }

      _synchronous_lock synchronouslock(synchronization());

      if (m_bTargetRectangleModified)
      {

         defer_on_target_rectangle_update();

      }

      ppenParam->defer_update(this);

      ::cast < ::draw2d_gdiplus::pen > pdraw2dgdipluspen = ppenParam;

      auto pgdipluspen = pdraw2dgdipluspen->m_pgdipluspen;

      if (::is_null(pgdipluspen))
      {

         throw ::exception(error_wrong_state);

      }

      //      pdraw2dpen->SetAlignment(Gdiplus::PenAlignment::PenAlignmentCenter);

      m_pgdiplusgraphics->DrawLine(pgdipluspen, Gdiplus::PointF((Gdiplus::REAL)x1, (Gdiplus::REAL)y1), Gdiplus::PointF((Gdiplus::REAL)x2, (Gdiplus::REAL)y2));

      m_pointCurrent.x = x2;

      m_pointCurrent.y = y2;

      //return true;

   }


   //void graphics::draw_line(::f64 x1, ::f64 y1, ::f64 x2, ::f64 y2, ::draw2d::pen * ppenParam)
   //{

   //   _synchronous_lock synchronouslock(synchronization());

   //   auto pdraw2dpen = (Gdiplus::Pen *) ppenParam->get_os_data(this);

   //   if (!pdraw2dpen)
   //   {

   //      return false;

   //   }

   //   pdraw2dpen->SetAlignment(Gdiplus::PenAlignment::PenAlignmentCenter);

   //   m_pgdiplusgraphics->DrawLine(pdraw2dpen, Gdiplus::Point(point1.x, point1.y), Gdiplus::Point(point2.x, point2.y));

   //   m_point.x = point2.x;

   //   m_point.y = point2.y;

   //   return true;

   //}


   void graphics::set_smooth_mode(::draw2d::enum_smooth_mode esmoothmode)
   {

      try
      {

         if (m_pgdiplusgraphics == nullptr)
         {

            //return false;
            throw ::exception(error_null_pointer);


         }

         if (esmoothmode == ::draw2d::e_smooth_mode_none)
         {

            m_pgdiplusgraphics->SetSmoothingMode(Gdiplus::SmoothingModeNone);

         }
         else if (esmoothmode == ::draw2d::e_smooth_mode_high)
         {

            m_pgdiplusgraphics->SetSmoothingMode(Gdiplus::SmoothingModeHighQuality);

         }
         else if (esmoothmode == ::draw2d::e_smooth_mode_anti_alias_8x4)
         {

            m_pgdiplusgraphics->SetSmoothingMode(Gdiplus::SmoothingModeAntiAlias8x4);

         }
         else if (esmoothmode == ::draw2d::e_smooth_mode_anti_alias_8x8)
         {

            m_pgdiplusgraphics->SetSmoothingMode(Gdiplus::SmoothingModeAntiAlias8x8);

         }

         ::draw2d::graphics::set_smooth_mode(esmoothmode);

         //return true;

      }
      catch (...)
      {

      }

      //return false;

   }


   //void graphics::set_interpolation_mode(::draw2d::e_interpolation_mode einterpolationmode)
   //{

   //   try
   //   {

   //      if (m_pgdiplusgraphics == nullptr)
   //      {

   //         return false;

   //      }

   //      if (einterpolationmode == ::draw2d::interpolation_mode_none)
   //      {

   //         m_pgdiplusgraphics->SetInterpolationMode(Gdiplus::InterpolationModeDefault);

   //      }
   //      else if (einterpolationmode == ::draw2d::interpolation_mode_low_quality)
   //      {

   //         m_pgdiplusgraphics->SetInterpolationMode(Gdiplus::InterpolationModeLowQuality);

   //      }
   //      else if (einterpolationmode == ::draw2d::interpolation_mode_high_quality)
   //      {

   //         m_pgdiplusgraphics->SetInterpolationMode(Gdiplus::InterpolationModeHighQuality);

   //      }

   //      ::draw2d::graphics::set_interpolation_mode(einterpolationmode);

   //      return true;

   //   }
   //   catch (...)
   //   {

   //   }

   //   return false;

   //}



   void graphics::set_compositing_quality(::draw2d::enum_compositing_quality ecompositingquality)
   {

      try
      {

         if (m_pgdiplusgraphics == nullptr)
         {

            //return false;

            throw ::exception(error_null_pointer);


         }

         if (ecompositingquality == ::draw2d::e_compositing_quality_none)
         {

            m_pgdiplusgraphics->SetCompositingQuality(Gdiplus::CompositingQualityDefault);

         }
         else if (ecompositingquality == ::draw2d::e_compositing_quality_high_speed)
         {

            m_pgdiplusgraphics->SetCompositingQuality(Gdiplus::CompositingQualityHighSpeed);

         }
         else if (ecompositingquality == ::draw2d::e_compositing_quality_high_quality)
         {

            m_pgdiplusgraphics->SetCompositingQuality(Gdiplus::CompositingQualityHighQuality);

         }

         ::draw2d::graphics::set_compositing_quality(ecompositingquality);

         //return true;

      }
      catch (...)
      {

      }

      //return false;

   }


   void graphics::set_alpha_mode(::draw2d::enum_alpha_mode ealphamode)
   {

      try
      {

         if (m_pgdiplusgraphics == nullptr)
         {

            //return false;

            throw ::exception(error_null_pointer);


         }

         if (ealphamode == ::draw2d::e_alpha_mode_blend)
         {

            if (m_pgdiplusgraphics->GetCompositingMode() != Gdiplus::CompositingModeSourceOver)
            {

               m_pgdiplusgraphics->SetCompositingMode(Gdiplus::CompositingModeSourceOver);

            }

         }
         else if (ealphamode == ::draw2d::e_alpha_mode_set)
         {

            if (m_pgdiplusgraphics->GetCompositingMode() != Gdiplus::CompositingModeSourceCopy)
            {

               m_pgdiplusgraphics->SetCompositingMode(Gdiplus::CompositingModeSourceCopy);

            }

         }

         ::draw2d::graphics::set_alpha_mode(ealphamode);

         //return true;

      }
      catch (...)
      {

      }

      //return false;

   }


   void graphics::set_text_rendering_hint(::write_text::enum_rendering etextrenderinghint)
   {

      try
      {

         if (m_pgdiplusgraphics == nullptr)
         {

            //return false;

            throw ::exception(error_null_pointer);


         }

         //if (m_ewritetextrendering == etextrenderinghint)
         //{

         //   return;

         //}

         switch (etextrenderinghint)
         {
         case ::write_text::e_rendering_anti_alias:
            m_pgdiplusgraphics->SetTextRenderingHint(Gdiplus::TextRenderingHintAntiAlias);
            break;
         case ::write_text::e_rendering_anti_alias_grid_fit:
            m_pgdiplusgraphics->SetTextRenderingHint(Gdiplus::TextRenderingHintAntiAliasGridFit);
            break;
         case ::write_text::e_rendering_single_bit_per_pixel:
            m_pgdiplusgraphics->SetTextRenderingHint(Gdiplus::TextRenderingHintSingleBitPerPixel);
            break;
         case ::write_text::e_rendering_single_bit_per_pixel_grid_fit:
            m_pgdiplusgraphics->SetTextRenderingHint(Gdiplus::TextRenderingHintSingleBitPerPixelGridFit);
            break;
         case ::write_text::e_rendering_clear_type_grid_fit:
            m_pgdiplusgraphics->SetTextRenderingHint(Gdiplus::TextRenderingHintClearTypeGridFit);
            break;
         case ::write_text::e_rendering_system_default:
         case ::write_text::e_rendering_none:
            m_pgdiplusgraphics->SetTextRenderingHint(Gdiplus::TextRenderingHintSystemDefault);
            break;
         }

         ::draw2d::graphics::set_text_rendering_hint(etextrenderinghint);

         //return true;

      }
      catch (...)
      {

      }

      //return false;

   }


   //void * graphics::get_os_data() const
   //{

   //   return (void *) m_pgdiplusgraphics;

   //}


   //void * graphics::get_os_data_ex(::i32 i) const
   //{

   //   if(i == 1)
   //   {
   //      return m_pgdiplusgraphics->GetHDC();
   //   }
   //   else
   //   {
   //      return ::draw2d::graphics::get_os_data_ex(i);
   //   }

   //}


   //void graphics::release_os_data_ex(::i32 i,void * p)
   //{

   //   if(i == 1)
   //   {

   //      m_pgdiplusgraphics->ReleaseHDC((HDC)p);

   //   }
   //   else
   //   {

   //      ::draw2d::graphics::release_os_data_ex(i, p);

   //   }

   //}


   HDC graphics::get_handle() const
   {

      return m_hdc;

   }


   Gdiplus::Region * graphics::defer_update_os_data(::pointer < ::geometry2d::region > & pregion)
   {

      ::pointer < ::draw2d_gdiplus::region > pdraw2dgdiplusregion = pregion;

      if (!pdraw2dgdiplusregion)
      {

         pdraw2dgdiplusregion = createø < ::draw2d::region >();

         //pgdiplusregion->m_eregion = pregion->m_eregion;

         pdraw2dgdiplusregion->m_pitem = pregion->m_pitem;

         pregion = pdraw2dgdiplusregion;

      }

      pdraw2dgdiplusregion->defer_update(this);

      return pdraw2dgdiplusregion->m_pgdiplusregion;

   }


   //HDC graphics::get_handle1() const
   //{

   //   return get_handle();

   //}


   //HDC graphics::get_handle2() const
   //{

   //   return get_handle();

   //}


   void graphics::_attach(Gdiplus::Graphics * pgdiplusgraphics)
   {

      close_graphics();

      m_pgdiplusgraphics = ::as_pointer(pgdiplusgraphics);

      //m_osdata[0] = pdata;

   }


   bool graphics::_detach(auto_pointer < Gdiplus::Graphics > & pgdiplusgraphics)
   {

      if (!m_pgdiplusgraphics)
      {

         return false;

      }

      pgdiplusgraphics = ::transfer(m_pgdiplusgraphics);

      m_hdc = nullptr;

      return true;

   }


   /*Gdiplus::Font* graphics::m_pwritetextfont->get_os_data < Font >(this);
   {

      if(m_pwritetextfont.is_null())
      {

         m_pwritetextfont.create();

         if(m_pwritetextfont.is_set())
         {

            m_pwritetextfont->m_powner = this;

         }

      }

      if(m_pwritetextfont.is_null())
      {

         return nullptr;

      }

      return m_pwritetextfont->get_os_data< Font * >(this);

   }


   Gdiplus::Brush * graphics::m_pdraw2dbrush->get_os_data < Brush * >(this)
   {

      if(m_pdraw2dbrush.is_null())
      {

         m_pdraw2dbrush.create();

         if(m_pdraw2dbrush.is_set())
         {

            m_pdraw2dbrush->m_powner = this;

         }

      }

      if(m_pdraw2dbrush.is_null())
      {

         return nullptr;

      }

      return m_pdraw2dbrush->get_os_data < Brush * >(this);

   }


   Gdiplus::Pen * graphics::m_pdraw2dpen->get_os_data < Pen * >(this)
   {

      _synchronous_lock synchronouslock(synchronization());

      if(m_pdraw2dpen.is_null())
      {

         m_pdraw2dpen.create();

         if(m_pdraw2dpen.is_set())
         {

            m_pdraw2dpen->m_powner = this;

         }

      }

      if(m_pdraw2dpen.is_null())
      {

         return nullptr;

      }

      return m_pdraw2dpen->get_os_data < Pen * >(this);

   }*/


   Gdiplus::FillMode graphics::gdiplus_get_fill_mode()
   {

      return Gdiplus::FillModeWinding;

   }


   void graphics::blur(bool bExpand, ::f64 dRadius, const ::f64_rectangle & rectangleParam)
   {

      // Commented Out for Running in cosan machine running Windows 2008

      //if(m_pdraw2dbitmap.is_null() || m_pdraw2dbitmap->nok())
      //   return false;

      //Gdiplus::BlurParams myBlurParams;

      //myBlurParams.expandEdge    = bExpand ? 1 : 0;
      //myBlurParams.radius        = (::f32) dRadius;

      //Gdiplus::Blur myBlur;
      //myBlur.SetParameters(&myBlurParams);

      //

      //Gdiplus::Matrix m;
      //m_pgdiplusgraphics->GetTransform(&m);

      //Gdiplus::PointF points[2];

      //points[0].X    = (Gdiplus::REAL) rectangleParam.left;
      //points[0].Y    = (Gdiplus::REAL) rectangleParam.top;
      //points[1].X    = (Gdiplus::REAL) rectangleParam.right;
      //points[1].Y    = (Gdiplus::REAL) rectangleParam.bottom;

      //m.TransformPoints(points, 2);

      ////Gdiplus::RectF rectf(points[0].X, points[0].Y, points[1].X - points[0].X, points[1].Y - points[0].Y);

      //::i32_rectangle rectangle;

      //rectangle.left      = (LONG) points[0].X;
      //rectangle.top       = (LONG) points[0].Y;
      //rectangle.right     = (LONG) points[1].X;
      //rectangle.bottom    = (LONG) points[1].Y;

      //Gdiplus::Bitmap * pdraw2dbitmap = ((Gdiplus::Bitmap *) m_pdraw2dbitmap->get_os_data());

      //pdraw2dbitmap->ApplyEffect(&myBlur, &rectangle);

      //return true;

   }


   //::f64 graphics::get_dpix()
   //{

   //   if (m_pgdiplusgraphics == nullptr)
   //      return 96.0;

   //   return m_pgdiplusgraphics->GetDpiX();

   //}


   //::f64 graphics::get_dpiy()
   //{

   //   if (m_pgdiplusgraphics == nullptr)
   //      return 96.0;

   //   return m_pgdiplusgraphics->GetDpiY();

   //}


   //void graphics::set_fill_mode(::draw2d::enum_fill_mode efillmode) overrid;
   //::draw2d::enum_fill_mode graphics::get_fill_mode()
   //{


   //   auto fillMode = m_pgdiplusgraphics->GetFi

   //}



   void graphics::flush()
   {

      _synchronous_lock synchronouslock(synchronization());

      m_pgdiplusgraphics->Flush();

      //return true;

   }


   void graphics::sync_flush()
   {

      _synchronous_lock synchronouslock(synchronization());

      m_pgdiplusgraphics->Flush(Gdiplus::FlushIntentionSync);

      //return true;

   }

   HDC graphics::get_hdc()
   {

      if (m_hdc != nullptr)
         return m_hdc;

      if (m_pgdiplusgraphics == nullptr)
         return nullptr;

      return m_pgdiplusgraphics->GetHDC();

   }

   void graphics::release_hdc(HDC hdc)
   {

      if (m_hdc != nullptr)
         return;

      m_pgdiplusgraphics->ReleaseHDC(hdc);

   }


   //void graphics::enum_fonts(::write_text::font_enumeration_item_array & itema)
   //{

   //   ::draw2d::wingdi_enum_fonts(itema, false, true, true);

   //}


   void graphics::prefer_mapped_image_on_mix()
   {

      //return true;

   }


   //bool graphics::TextOutAlphaBlend(::f64 x, ::f64 y, const block & block)
   //{

   //   if (m_pimageAlphaBlend->is_set())
   //   {

   //      single_lock synchronouslock(mutex());

   //      if (block.is_empty())
   //      {

   //         //return false;

   //         throw ::exception(error_null_pointer);


   //      }

   //      // "Reference" implementation for TextOutAlphaBlend

   //      ::i32_rectangle rectangleAlphaBlend(m_pointAlphaBlend, m_pimageAlphaBlend->size());

   //      ::i32_rectangle rectangleIntersect;

   //      const ::f64_size & size = ::f64_size(get_text_extent(block));

   //      //size.cx = size.cx * 110 / 100;

   //      //size.cy = size.cy * 110 / 100;

   //      ::i32_rectangle rectangleText(i32_point((LONG)x, (LONG)y), size);

   //      if (rectangleIntersect.intersect(rectangleAlphaBlend, rectangleText))
   //      {

   //         ::image::image_pointer pimage1;

   //         pimage1 = image()->create_image(rectangleText.size());

   //         pimage1->fill(0);

   //         pdraw2dgraphicsImage1->set(get_current_font());

   //         pdraw2dgraphicsImage1->set(get_current_brush());

   //         pdraw2dgraphicsImage1->set_alpha_mode(::draw2d::e_alpha_mode_blend);

   //         pdraw2dgraphicsImage1->set_text_rendering_hint(::write_text::e_rendering_anti_alias);

   //         pdraw2dgraphicsImage1->text_out(0, 0, block);

   //         i32_point pointDst;

   //         pointDst.y = (::i32)maximum(0, rectangleIntersect.top - y);

   //         pointDst.x = (::i32)maximum(0, rectangleIntersect.left - x);

   //         i32_point pointSrc;

   //         pointSrc.y = (::i32)maximum(0, y - rectangleAlphaBlend.top);

   //         pointSrc.x = (::i32)maximum(0, x - rectangleAlphaBlend.left);

   //         pimage1->blend2(pointDst, m_pimageAlphaBlend, pointSrc, rectangleIntersect.size(), 255);

   //         ::image::image_drawing_options imagedrawingoptions;

   //         set_alpha_mode(::draw2d::e_alpha_mode_blend);

   //         _draw_raw(rectangleText, pimage1, imagedrawingoptions, ::f64_point());

   //         return true;

   //      }

   //   }

   //   return false;

   //}


   //void graphics::draw_blend(const ::i32_point & pointDst, ::draw2d::graphics * pgraphicsSrc, const ::i32_rectangle & rectangleSource)
   //{

   //   //return ::draw2d::graphics::BitBltAlphaBlend(x, y, nWidth, nHeight, pgraphicsSrc, xSrc, ySrc, dwRop);

   //   if (m_pimageAlphaBlend->is_set())
   //   {

   //      if (x < 0)
   //      {

   //         xSrc -= x;

   //         nWidth += x;

   //         x = 0;

   //      }

   //      if (y < 0)
   //      {

   //         ySrc -= y;

   //         nHeight += y;

   //         y = 0;

   //      }


   //      ::i32_rectangle rectangleIntersect(m_pointAlphaBlend, m_pimageAlphaBlend->::f64_size());

   //      ::i32_rectangle rectangleBlt(i32_point((::i64)x, (::i64)y), ::f64_size(nWidth, nHeight));

   //      if (rectangleIntersect.intersect(rectangleIntersect, rectangleBlt))
   //      {

   //         //if (m_pointAlphaBlend.x < 0)
   //         //{

   //         //   xSrc += -m_pointAlphaBlend.x;

   //         //}
   //         //if (m_pointAlphaBlend.y < 0)
   //         //{

   //         //   ySrc += -m_pointAlphaBlend.y;

   //         //}

   //         // The following commented out code does not work well when there is clipping
   //         // and some calculations are not precise
   //         //if (m_pimage != nullptr && pgraphicsSrc->m_pimage != nullptr)
   //         //{

   //         //   const ::i32_point & pointOff = GetViewportOrg();

   //         //   x += pointOff.x;

   //         //   y += pointOff.y;

   //         //   return m_pimage->blend(::i32_point(x, y), pgraphicsSrc->m_pimage, ::i32_point(xSrc, ySrc), m_pimageAlphaBlend, i32_point(m_pointAlphaBlend.x - x, m_pointAlphaBlend.y - y), rectangleBlt.::f64_size());

   //         //}
   //         //else
   //         {

   //            ::image::image_pointer pimage1;
   //            
   //            auto estatus = constructø(pimage1);

   //            if (!estatus)
   //            {

   //               return false;

   //            }
   //            
   //            estatus = pimage1->create_as_descriptor(rectangleBlt.::f64_size());

   //            if (!estatus)
   //            {

   //               return false;

   //            }

   //            pdraw2dgraphicsImage1->set_alpha_mode(::draw2d::e_alpha_mode_set);

   //            if (!pimage1->from(nullptr, pgraphicsSrc, ::i32_point(xSrc, ySrc), rectangleBlt.::f64_size()))
   //               return false;

   //            pimage1->blend2(::i32_point(), m_pimageAlphaBlend, i32_point(x - m_pointAlphaBlend.x, y - m_pointAlphaBlend.y), rectangleBlt.::f64_size(), 255);

   //            BitBltRaw(x, y, nWidth, nHeight, pdraw2dgraphicsImage1, 0, 0, dwRop);

   //         }

   //         return true;

   //      }

   //   }

   //   return false;

   //}


   void graphics::_get(::geometry2d::matrix & matrix)
   {

      Gdiplus::Matrix m;

      if (m_pgdiplusgraphics->GetTransform(&m) != Gdiplus::Ok)
      {

         //return false;

         throw ::exception(error_null_pointer);


      }

      ::f32 fa[6];

      m.GetElements(fa);

      matrix = ::geometry2d::matrix();

      matrix.SetElements(fa);

      //return true;

   }


   void graphics::_set(const ::geometry2d::matrix & matrix)
   {

      Gdiplus::Matrix m;

      m.SetElements((Gdiplus::REAL)matrix.a1, (Gdiplus::REAL)matrix.a2, (Gdiplus::REAL)matrix.b1, (Gdiplus::REAL)matrix.b2, (Gdiplus::REAL)matrix.c1, (Gdiplus::REAL)matrix.c2);

      bool bOk = m_pgdiplusgraphics->SetTransform(&m) == Gdiplus::Ok;

   }


   //void graphics::append(const ::geometry2d::matrix & matrix)
   //{

   //   ::geometry2d::matrix m;

   //   get(m);

   //   m.append(matrix);

   //   return set(m);

   //}


   //void graphics::prepend(const ::geometry2d::matrix & matrix)
   //{

   //   ::geometry2d::matrix m;

   //   get(m);

   //   m.prepend(matrix);

   //   return set(m);

   //}

} // namespace draw2d_gdiplus





