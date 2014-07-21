/**
 * \file
 * \brief Circles
 *//*
 * Authors:
 *      Marco Cecchetti <mrcekets at gmail.com>
 *
 * Copyright 2008  authors
 *
 * This library is free software; you can redistribute it and/or
 * modify it either under the terms of the GNU Lesser General Public
 * License version 2.1 as published by the Free Software Foundation
 * (the "LGPL") or, at your option, under the terms of the Mozilla
 * Public License Version 1.1 (the "MPL"). If you do not alter this
 * notice, a recipient may use your version of this file under either
 * the MPL or the LGPL.
 *
 * You should have received a copy of the LGPL along with this library
 * in the file COPYING-LGPL-2.1; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 * You should have received a copy of the MPL along with this library
 * in the file COPYING-MPL-1.1
 *
 * The contents of this file are subject to the Mozilla Public License
 * Version 1.1 (the "License"); you may not use this file except in
 * compliance with the License. You may obtain a copy of the License at
 * http://www.mozilla.org/MPL/
 *
 * This software is distributed on an "AS IS" basis, WITHOUT WARRANTY
 * OF ANY KIND, either express or implied. See the LGPL or the MPL for
 * the specific language governing rights and limitations.
 */

#ifndef LIB2GEOM_SEEN_CIRCLE_H
#define LIB2GEOM_SEEN_CIRCLE_H

#include <2geom/point.h>
#include <2geom/forward.h>
#include <2geom/transforms.h>

namespace Geom {

class EllipticalArc;

class Circle
    : MultipliableNoncommutative< Circle, Translate
    , MultipliableNoncommutative< Circle, Rotate
    , MultipliableNoncommutative< Circle, Zoom
      > > >
{
    Point _center;
    Coord _radius;

public:
    Circle() {}
    Circle(Coord cx, Coord cy, Coord r)
        : _center(cx, cy), _radius(r)
    {}
    Circle(Point const &center, Coord r)
        : _center(center), _radius(r)
    {}

    Circle(Coord A, Coord B, Coord C, Coord D) {
        set(A, B, C, D);
    }

    explicit Circle(std::vector<Point> const& points) {
        fit(points);
    }

    // build a circle by its implicit equation:
    // Ax^2 + Ay^2 + Bx + Cy + D = 0
    void set(Coord A, Coord B, Coord C, Coord D);

    // build up the best fitting circle wrt the passed points
    // prerequisite: at least 2 points must be passed
    void fit(std::vector<Point> const& points);

    EllipticalArc *
    arc(Point const& initial, Point const& inner, Point const& final,
        bool svg_compliant = true);

    D2<SBasis> toSBasis();
    void getPath(PathVector &path_out);

    Point center() const {
        return _center;
    }
    Coord center(Dim2 d) const {
        return _center[d];
    }
    Coord radius() const {
        return _radius;
    }
    void setCenter(Point const &p) {
        _center = p;
    }
    void setRadius(Coord c) {
        _radius = c;
    }

    Circle &operator*=(Translate const &t) {
        _center *= t;
        return *this;
    }
    Circle &operator*=(Rotate const &) {
        return *this;
    }
    Circle &operator*=(Zoom const &z) {
        _center *= z;
        _radius *= z.scale();
        return *this;
    }
};

} // end namespace Geom

#endif // LIB2GEOM_SEEN_CIRCLE_H

/*
  Local Variables:
  mode:c++
  c-file-style:"stroustrup"
  c-file-offsets:((innamespace . 0)(inline-open . 0)(case-label . +))
  indent-tabs-mode:nil
  fill-column:99
  End:
*/
// vim: filetype=cpp:expandtab:shiftwidth=4:tabstop=8:softtabstop=4:fileencoding=utf-8:textwidth=99 :
