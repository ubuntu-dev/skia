/*
 * Copyright 2016 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef SkCurveMeasure_DEFINED
#define SkCurveMeasure_DEFINED

#include "SkPoint.h"
#include "SkNx.h"

// These are weights and abscissae for gaussian quadrature with weight function
// w(x) = 1
static SkScalar weights8[8] = {0.3626837833783620f, 0.3626837833783620f,
                               0.3137066458778873f, 0.3137066458778873f,
                               0.2223810344533745f, 0.2223810344533745f,
                               0.1012285362903763f, 0.1012285362903763f};
static SkScalar absc8[8] = {-0.1834346424956498f, 0.1834346424956498f,
                            -0.5255324099163290f, 0.5255324099163290f,
                            -0.7966664774136267f, 0.7966664774136267f,
                            -0.9602898564975363f, 0.9602898564975363f};

static Sk8f weights = Sk8f::Load(weights8);
static Sk8f absc = 0.5f*(Sk8f::Load(absc8) + 1.0f);


// this is the same enum as in SkPathMeasure but it doesn't have a name there
enum SkSegType {
    kLine_SegType,
    kQuad_SegType,
    kCubic_SegType,
    kConic_SegType,
};

class ArcLengthIntegrator {
public:
    ArcLengthIntegrator() {}
    ArcLengthIntegrator(const SkPoint* pts, SkSegType segType);
    SkScalar computeLength(SkScalar t);

private:
    SkSegType fSegType;

    // precomputed coefficients for derivatives in Horner form
    Sk8f xCoeff[3];
    Sk8f yCoeff[3];
};

class SkCurveMeasure {
public:
    SkCurveMeasure() {}
    SkCurveMeasure(const SkPoint* pts, SkSegType segType);

    SkScalar getTime(SkScalar targetLength);
    void getPosTan(SkScalar distance, SkPoint* pos, SkVector* tan);
    SkScalar getLength();

private:
    SkPoint evaluateQuad(SkScalar t);
    SkVector evaluateQuadDerivative(SkScalar t);
    //SkPoint evaluate_cubic(SkScalar t);
    //SkVector evaluate_cubic_derivative(SkScalar t);
    //SkPoint evaluate_conic(SkScalar t);
    //SkVector evaluate_conic_derivative(SkScalar t);

    const SkScalar kTolerance = 0.0001f;
    const int kNewtonIters = 5;
    const int kBisectIters = 5;

    SkSegType fSegType;
    SkPoint fPts[4];
    SkScalar fLength = -1.0f;
    ArcLengthIntegrator fIntegrator;

    // for debug purposes
    int fIters;
};

#endif  // SkCurveMeasure_DEFINED
