//                                               -*- C++ -*-
/**
 *  @brief Abstract top-level class for all numerical math function implementations
 *
 *  Copyright 2005-2015 Airbus-EDF-IMACS-Phimeca
 *
 *  This library is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  along with this library.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
#ifndef OPENTURNS_BOXCOXTRANSFORM_HXX
#define OPENTURNS_BOXCOXTRANSFORM_HXX

#include "NumericalMathFunction.hxx"
#include "NumericalPoint.hxx"
#include "Collection.hxx"

BEGIN_NAMESPACE_OPENTURNS

/**
 * @class BoxCoxTransform
 *
 * The class that simulates the classical Box Cox method which acts on the spatial part of a time series.
 */

class InverseBoxCoxTransform;

class OT_API BoxCoxTransform
  : public NumericalMathFunction

{
  CLASSNAME;
public:

  /** Default constructor */
  BoxCoxTransform();

  /** Standard parameter constructor */
  BoxCoxTransform(const NumericalPoint & lambda);

  BoxCoxTransform(const NumericalPoint & lambda,
                  const NumericalPoint & shift);

  /** 1D NumericalScalar parameter constructor */
  BoxCoxTransform(const NumericalScalar & lambda);

  BoxCoxTransform(const NumericalScalar & lambda,
                  const NumericalScalar & shift);

  /** Virtual constructor */
  BoxCoxTransform * clone() const;

  /** Lambda accessor */
  NumericalPoint getLambda () const;

  /** Shift accessor */
  NumericalPoint getShift () const;

  /** Inverse accessor */
  InverseBoxCoxTransform getInverse() const;

private:

}; /* class BoxCoxTransform */


END_NAMESPACE_OPENTURNS

#endif /* OPENTURNS_BOXCOXTRANSFORM_HXX */
