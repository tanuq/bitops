/**
 * @file bitops.h
 * @brief bit operation
 * @author M.Ogata
 * @date 2011/10/13
 */
#pragma once

#include <limits.h> /* CHAR_BIT */

#if defined(__GNUC__)
#include <inttypes.h>
#elif defined(_MSC_VER)
#include "windows.h"
#include <intrin.h> /* BitScanForward */
#include <stdlib.h> /* _uint8_tswap_xx */
#include <tchar.h>
typedef BYTE uint8_t;
typedef WORD uint16_t;
typedef DWORD uint32_t;
typedef UINT64 uint64_t;
typedef INT64 int64_t;

#pragma warning(disable : 4351)
#endif

#if (CHAR_BIT == 8)
#define BITS_PER_UINT8_T (CHAR_BIT)
#define BITS_PER_UINT16_T (BITS_PER_UINT8_T * sizeof(uint16_t))
#define BITS_PER_UINT32_T (BITS_PER_UINT8_T * sizeof(uint32_t))
#define BITS_PER_UINT64_T (BITS_PER_UINT8_T * sizeof(uint64_t))
#else
#error
#endif

/**
 * @brief  endian swap uint16_t
 * @param  x  uint16_t
 * @return uint16_t
 */
static inline uint16_t byte_swap(uint16_t x) {
#if defined(__GNUC__)
  return __builtin_bswap16(x);
#elif defined(_MSC_VER)
  return _uint8_tswap_ushort(x);
#else
  return (x << 8) | (x >> 8);
#endif
}

/**
 * @brief  endian swap uint32_t
 * @param  x  uint32_t
 * @return uint32_t
 */
static inline uint32_t byte_swap(uint32_t x) {
#if defined(__GNUC__)
  return __builtin_bswap32(x);
#elif defined(_MSC_VER)
  return _uint8_tswap_ulong(x);
#else
  return ((x << 24) & 0xff000000) | ((x << 8) & 0x00ff0000) |
         ((x >> 24) & 0x000000ff) | ((x >> 8) & 0x0000ff00);
#endif
}

/**
 * @brief  endian swap uint64_t
 * @param  x  uint64_t
 * @return uint64_t
 */
static inline uint64_t byte_swap(uint64_t x) {
#if defined(__GNUC__)
  return __builtin_bswap64(x);
#elif defined(_MSC_VER)
  return byteswap_uint64(x);
#else
  return ((x << 56) & 0xff00000000000000ULL) |
         ((x << 40) & 0x00ff000000000000ULL) |
         ((x << 24) & 0x0000ff0000000000ULL) |
         ((x << 8) & 0x000000ff00000000ULL) |
         ((x >> 56) & 0x00000000000000ffULL) |
         ((x >> 40) & 0x000000000000ff00ULL) |
         ((x >> 24) & 0x0000000000ff0000ULL) |
         ((x >> 8) & 0x00000000ff000000ULL);
#endif
}

/**
 *
 * @brief  find first bit
 * @param  x  uint32_t
 * @return uint32_t
 */
static inline uint32_t find_first_bit(uint32_t x) {
#if defined(__GNUC__)
  if (x == 0)
    return 0;
  return __builtin_ctzl(x);
#elif defined(_MSC_VER)
  uint32_t i;
  _BitScanForward(&i, x);
  return i;
#else
  uint32_t i;
  if (x == 0)
    return 0;
  for (i = 1; !(x & 1); i++)
    x >>= 1;
  return i;
#endif
}

/**
 * @brief  find first bit
 * @param  x  uint64_t
 * @return uint32_t
 */
static inline uint32_t find_first_bit(uint64_t x) {
#if defined(__GNUC__)
  if (x == 0)
    return 0;
  return __builtin_ctzll(x);
#elif defined(_MSC_VER)
#if defined(_WIN64)
  uint32_t i;
  _BitScanForward64(&i, x);
  return i;
#else
  uint32_t i;
  if (_BitScanForward(&i, static_cast<uint32_t>(x)))
    return i;
  _BitScanForward(&i, static_cast<uint32_t>(x >> 32));
  return i + 32;
#endif
#else
  uint32_t i;
  if (x == 0)
    return 0;
  for (i = 1; !(x & 1); i++)
    x >>= 1;
  return i;
#endif
}

/**
 * @brief  population count
 * @param  x  uint32_t
 * @return uint32_t
 */
static inline uint32_t population_count(uint32_t x) {
#if defined(__GNUC__)
  return __builtin_popcountl(x);
/* SSE4.2以上のCPUでないと使えない
#elif defined(_MSC_VER)
return _popcnt(x);
*/
#else
  x = (x & 0x55555555) + (x >> 1 & 0x55555555);
  x = (x & 0x33333333) + (x >> 2 & 0x33333333);
  x = (x & 0x0f0f0f0f) + (x >> 4 & 0x0f0f0f0f);
  x = (x & 0x00ff00ff) + (x >> 8 & 0x00ff00ff);
  return (x & 0x0000ffff) + (x >> 16 & 0x0000ffff);
#endif
}

/**
 * @brief  population count
 * @param  x  uint64_t
 * @return uint32_t
 */
static inline uint32_t population_count(uint64_t x) {
#if defined(__GNUC__)
  return __builtin_popcountll(x);
/* SSE4.2以上のCPUでないと使えない
#elif defined(_MSC_VER)
return _popcnt64(x);
*/
#else
  x = (x & 0x5555555555555555) + (x >> 1 & 0x5555555555555555);
  x = (x & 0x3333333333333333) + (x >> 2 & 0x3333333333333333);
  x = (x & 0x0f0f0f0f0f0f0f0f) + (x >> 4 & 0x0f0f0f0f0f0f0f0f);
  x = (x & 0x00ff00ff00ff00ff) + (x >> 8 & 0x00ff00ff00ff00ff);
  x = (x & 0x0000ffff0000ffff) + (x >> 16 & 0x0000ffff0000ffff);
  return (x & 0x00000000ffffffff) + (x >> 32 & 0x00000000ffffffff);
#endif
}

/**
 * @brief  make bit mask
 * @param  width  mask bit count
 * @return T
 */
template <typename T> T mk_bit_mask(int width) {
  return (T)(~0) >> (sizeof(T) * CHAR_BIT - width);
}

/**
 * @brief  bit extract
 * @param  d  source value
 * @param  start_bit  first bit position
 * @param  bit_width  bit count
 * @return T
 */
template <typename T, typename U>
T bit_extract(U d, int start_bit, int bit_width) {
  return static_cast<T>((d & (mk_bit_mask<U>(bit_width) << start_bit)) >>
                        start_bit);
}

/**
 * @brief  make bit pattern
 * @param  d  source value
 * @param  start_bit  first bit
 * @param  bit_width  bit count
 * @return T
 */
template <typename T, typename U> U bit_ptn(T d, int start_bit, int bit_width) {
  return static_cast<T>((d & mk_bit_mask<T>(bit_width)) << start_bit);
}

/**
 * @brief  bit or
 * @param  d  destination
 * @param  x  or value
 * @param  start_bit  first bit position
 * @param  bit_width  bit count
 * @return distination
 */
template <typename T, typename U>
U bit_insert(U &d, T x, int start_bit, int bit_width) {
  d |= bit_ptn<T, U>(x, start_bit, bit_width);
  return d;
}

/**
 * @brief  bit replace
 * @param  d  destination
 * @prama  x  replace value
 * @param  start_bit  first bit position
 * @param  bit_width  bit count
 * @return distination
 */
template <typename T, typename U>
U bit_replace(U &d, T x, int start_bit, int bit_width) {
  d = (d & ~(mk_bit_mask<U>(bit_width) << start_bit)) |
      bit_ptn<T, U>(x, start_bit, bit_width);
  return d;
}

#if defined(_MSC_VER) || defined(__GNUC__)
#pragma pack(push, 1)
#endif

/* 40bit uint64_t */
typedef struct {
  uint32_t l;
  uint8_t h;
  typedef uint8_t htype;
} uint64_t_40;

/* 48bit uint64_t */
typedef struct {
  uint32_t l;
  uint16_t h;
  typedef uint16_t htype;
} uint64_t_48;

#if defined(_MSC_VER) || defined(__GNUC__)
#pragma pack(pop)
#endif

/**
 * @brief  uint64_t to uint64_t_40/48
 * @param  val destination reference
 * @prama  u64val source value;
 * @return uint64_t
 */
template <typename T> uint64_t u64compress(T &val, uint64_t u64val) {
  val.l = bit_extract<uint32_t, uint64_t>(u64val, 0, BITS_PER_UINT32_T);
  val.h = bit_extract<typename T::htype, uint64_t>(u64val, BITS_PER_UINT32_T,
                                                   sizeof(typename T::htype));
  return u64val;
}

/**
 * @brief  uint64_t_40/48 to uint64_t
 * @param  val source reference
 * @return uint64_t
 */
template <typename T> uint64_t u64decompress(const T &val) {
  return static_cast<uint64_t>(val.l) +
         (static_cast<uint64_t>(val.h) << BITS_PER_UINT32_T);
}
