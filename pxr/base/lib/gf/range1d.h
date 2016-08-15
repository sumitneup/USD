//
// Copyright 2016 Pixar
//
// Licensed under the Apache License, Version 2.0 (the "Apache License")
// with the following modification; you may not use this file except in
// compliance with the Apache License and the following modification to it:
// Section 6. Trademarks. is deleted and replaced with:
//
// 6. Trademarks. This License does not grant permission to use the trade
//    names, trademarks, service marks, or product names of the Licensor
//    and its affiliates, except as required to comply with Section 4(c) of
//    the License and to reproduce the content of the NOTICE file.
//
// You may obtain a copy of the Apache License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the Apache License with the above modification is
// distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied. See the Apache License for the specific
// language governing permissions and limitations under the Apache License.
//
////////////////////////////////////////////////////////////////////////
// This file is generated by a script.  Do not edit directly.  Edit the
// range.template.h file to make changes.

#ifndef GF_RANGE1D_H
#define GF_RANGE1D_H

/// \file gf/range1d.h
/// \ingroup group_gf_BasicGeometry

#include "pxr/base/gf/traits.h"

#include <boost/functional/hash.hpp>

#include <cfloat>
#include <cstddef>
#include <iosfwd>

class GfRange1d;
class GfRange1f;

template <>
struct GfIsGfRange<class GfRange1d> { static const bool value = true; };

/// \class GfRange1d
/// \ingroup group_gf_BasicGeometry
///
/// Basic type: 1-dimensional floating point range.
///
/// This class represents a 1-dimensional range (or interval) All
/// operations are component-wise and conform to interval mathematics. An
/// empty range is one where max < min.
/// The default empty is [FLT_MAX,-FLT_MAX]
class GfRange1d
{
public:

    /// Helper typedef.
    typedef double MinMaxType;

    static const size_t dimension = 1;
    typedef MinMaxType ScalarType;

    /// Sets the range to an empty interval
    // TODO check whether this can be deprecated.
    void inline SetEmpty() {
	_min =  FLT_MAX;
	_max = -FLT_MAX;
    }

    /// The default constructor creates an empty range.
    GfRange1d() {
        SetEmpty();
    }

    /// This constructor initializes the minimum and maximum points.
    GfRange1d(double min, double max)
        : _min(min), _max(max)
    {
    }

    /// Returns the minimum value of the range.
    double GetMin() const { return _min; }

    /// Returns the maximum value of the range.
    double GetMax() const { return _max; }

    /// Returns the size of the range.
    double GetSize() const { return _max - _min; }

    /// Sets the minimum value of the range.
    void SetMin(double min) { _min = min; }

    /// Sets the maximum value of the range.
    void SetMax(double max) { _max = max; }

    /// Returns whether the range is empty (max < min).
    bool IsEmpty() const {
        return _min > _max;
    }

    /// Modifies the range if necessary to surround the given value.
    /// \deprecated Use UnionWith() instead.
    void ExtendBy(double point) { UnionWith(point); }

    /// Modifies the range if necessary to surround the given range.
    /// \deprecated Use UnionWith() instead.
    void ExtendBy(const GfRange1d &range) { UnionWith(range); }

    /// Returns true if the \p point is located inside the range. As with all
    /// operations of this type, the range is assumed to include its extrema.
    bool Contains(double point) const {
        return (point >= _min && point <= _max);
    }

    /// Returns true if the \p range is located entirely inside the range. As
    /// with all operations of this type, the ranges are assumed to include
    /// their extrema.
    bool Contains(const GfRange1d &range) const {
        return Contains(range._min) && Contains(range._max);
    }

    /// Returns true if the \p point is located inside the range. As with all
    /// operations of this type, the range is assumed to include its extrema.
    /// \deprecated Use Contains() instead.
    bool IsInside(double point) const {
        return Contains(point);
    }

    /// Returns true if the \p range is located entirely inside the range. As
    /// with all operations of this type, the ranges are assumed to include
    /// their extrema.
    /// \deprecated Use Contains() instead.
    bool IsInside(const GfRange1d &range) const {
        return Contains(range);
    }

    /// Returns true if the \p range is located entirely outside the range. As
    /// with all operations of this type, the ranges are assumed to include
    /// their extrema.
    bool IsOutside(const GfRange1d &range) const {
        return (range._max < _min || range._min > _max);
    }

    /// Returns the smallest \c GfRange1d which contains both \p a and \p b.
    static GfRange1d GetUnion(const GfRange1d &a, const GfRange1d &b) {
        GfRange1d res = a;
        _FindMin(res._min,b._min);
        _FindMax(res._max,b._max);
        return res;
    }

    /// Extend \p this to include \p b.
    const GfRange1d &UnionWith(const GfRange1d &b) {
        _FindMin(_min,b._min);
        _FindMax(_max,b._max);
        return *this;
    }

    /// Extend \p this to include \p b.
    const GfRange1d &UnionWith(double b) {
        _FindMin(_min,b);
        _FindMax(_max,b);
        return *this;
    }

    /// Returns the smallest \c GfRange1d which contains both \p a and \p b
    /// \deprecated Use GetUnion() instead.
    static GfRange1d Union(const GfRange1d &a, const GfRange1d &b) {
        return GetUnion(a, b);
    }

    /// Extend \p this to include \p b.
    /// \deprecated Use UnionWith() instead.
    const GfRange1d &Union(const GfRange1d &b) {
        return UnionWith(b);
    }

    /// Extend \p this to include \p b.
    /// \deprecated Use UnionWith() instead.
    const GfRange1d &Union(double b) {
        return UnionWith(b);
    }

    /// Returns a \c GfRange1d that describes the intersection of \p a and \p b.
    static GfRange1d GetIntersection(const GfRange1d &a, const GfRange1d &b) {
        GfRange1d res = a;
        _FindMax(res._min,b._min);
        _FindMin(res._max,b._max);
        return res;
    }

    /// Returns a \c GfRange1d that describes the intersection of \p a and \p b.
    /// \deprecated Use GetIntersection() instead.
    static GfRange1d Intersection(const GfRange1d &a, const GfRange1d &b) {
        return GetIntersection(a, b);
    }

    /// Modifies this range to hold its intersection with \p b and returns the
    /// result
    const GfRange1d &IntersectWith(const GfRange1d &b) {
        _FindMax(_min,b._min);
        _FindMin(_max,b._max);
        return *this;
    }

    /// Modifies this range to hold its intersection with \p b and returns the
    /// result.
    /// \deprecated Use IntersectWith() instead.
    const GfRange1d &Intersection(const GfRange1d &b) {
        return IntersectWith(b);
    }

    /// unary sum.
    GfRange1d operator +=(const GfRange1d &b) {
        _min += b._min;
        _max += b._max;
        return *this;
    }

    /// unary difference.
    GfRange1d operator -=(const GfRange1d &b) {
        _min -= b._max;
        _max -= b._min;
        return *this;
    }

    /// unary multiply.
    GfRange1d operator *=(double m) {
        if (m > 0) {
            _min *= m;
            _max *= m;
        } else {
            double tmp = _min;
            _min = _max * m;
            _max = tmp * m;
        }
        return *this;
    }

    /// unary division.
    GfRange1d operator /=(double m) {
        return *this *= (1.0 / m);
    }

    /// binary sum.
    GfRange1d operator +(const GfRange1d &b) const {
        return GfRange1d(_min + b._min, _max + b._max);
    }


    /// binary difference.
    GfRange1d operator -(const GfRange1d &b) const {
        return GfRange1d(_min - b._max, _max - b._min);
    }

    /// scalar multiply.
    friend GfRange1d operator *(double m, const GfRange1d &r) {
        return (m > 0 ? 
            GfRange1d(r._min*m, r._max*m) : 
            GfRange1d(r._max*m, r._min*m));
    }

    /// scalar multiply.
    friend GfRange1d operator *(const GfRange1d &r, double m) {
        return (m > 0 ? 
            GfRange1d(r._min*m, r._max*m) : 
            GfRange1d(r._max*m, r._min*m));
    }

    /// scalar divide.
    friend GfRange1d operator /(const GfRange1d &r, double m) {
        return r * (1.0 / m);
    }

    /// hash.
    friend inline size_t hash_value(const GfRange1d &r) {
        size_t h = 0;
        boost::hash_combine(h, r._min);
        boost::hash_combine(h, r._max);
        return h;
    }

    /// The min and max points must match exactly for equality.
    bool operator ==(const GfRange1d &b) const {
        return (_min == b._min && _max == b._max);
    }

    bool operator !=(const GfRange1d &b) const {
        return !(*this == b);
    }

    /// Compare this range to a GfRange1f.
    ///
    /// The values must match exactly and it does exactly what you might
    /// expect when comparing float and double values.
    inline bool operator ==(const GfRange1f& other) const;
    inline bool operator !=(const GfRange1f& other) const;

    /// Compute the squared distance from a point to the range.
    double GetDistanceSquared(double p) const;


  private:
    /// Minimum and maximum points.
    double _min, _max;

    /// Extends minimum point if necessary to contain given point.
    static void _FindMin(double &dest, double point) {
        if (point < dest) dest = point;
    }

    /// Extends maximum point if necessary to contain given point.
    static void _FindMax(double &dest, double point) {
        if (point > dest) dest = point;
    }
};

/// Output a GfRange1d.
/// \ingroup group_gf_DebuggingOutput
std::ostream& operator<<(std::ostream &, GfRange1d const &);

#include "pxr/base/gf/range1f.h"

inline bool
GfRange1d::operator ==(const GfRange1f& other) const {
    return _min == double(other.GetMin()) &&
           _max == double(other.GetMax());
}

inline bool
GfRange1d::operator !=(const GfRange1f& other) const {
    return !(*this == other);
}


#endif // GF_RANGE1D_H
