#pragma once
#include "shitrndr/src/shitrndr.h"
#include "huh/vec2.h"
namespace cumt
{
using v2f = vec2<float>; // for world space
using v2i = vec2<int>; // for screen space
}

// convenience functions for interacting with shitrndr's helpers::vec2
template <typename T1, typename T2>
inline vec2<T1> operator+(const vec2<T1>& a, const shitrndr::helpers::vec2<T2>& b) { return vec2<T1>{a.x + static_cast<T1>(b.x), a.y + static_cast<T1>(b.y)}; }
template <typename T1, typename T2>
inline vec2<T1> operator-(const vec2<T1>& a, const shitrndr::helpers::vec2<T2>& b) { return vec2<T1>{a.x - static_cast<T1>(b.x), a.y - static_cast<T1>(b.y)}; }
template <typename T1, typename T2>
inline vec2<T1> operator*(const vec2<T1>& a, const shitrndr::helpers::vec2<T2>& b) { return vec2<T1>{a.x * static_cast<T1>(b.x), a.y * static_cast<T1>(b.y)}; }
template <typename T1, typename T2>
inline vec2<T1> operator/(const vec2<T1>& a, const shitrndr::helpers::vec2<T2>& b) { return vec2<T1>{a.x / static_cast<T1>(b.x), a.y / static_cast<T1>(b.y)}; }

template <typename T1, typename T2>
inline vec2<T1> operator+(const shitrndr::helpers::vec2<T1>& a, const vec2<T2>& b) { return shitrndr::helpers::vec2<T1>{a.x + static_cast<T1>(b.x), a.y + static_cast<T1>(b.y)}; }
template <typename T1, typename T2>
inline vec2<T1> operator-(const shitrndr::helpers::vec2<T1>& a, const vec2<T2>& b) { return shitrndr::helpers::vec2<T1>{a.x - static_cast<T1>(b.x), a.y - static_cast<T1>(b.y)}; }
template <typename T1, typename T2>
inline vec2<T1> operator*(const shitrndr::helpers::vec2<T1>& a, const vec2<T2>& b) { return shitrndr::helpers::vec2<T1>{a.x * static_cast<T1>(b.x), a.y * static_cast<T1>(b.y)}; }
template <typename T1, typename T2>
inline vec2<T1> operator/(const shitrndr::helpers::vec2<T1>& a, const vec2<T2>& b) { return shitrndr::helpers::vec2<T1>{a.x / static_cast<T1>(b.x), a.y / static_cast<T1>(b.y)}; }
