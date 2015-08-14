//                                               -*- C++ -*-
/**
 *  @brief
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
#include <cstdlib>

#include "SolverImplementation.hxx"
#include "Exception.hxx"
#include "NumericalPoint.hxx"
#include "ResourceMap.hxx"
#include "PersistentObjectFactory.hxx"

BEGIN_NAMESPACE_OPENTURNS

CLASSNAMEINIT(SolverImplementation);

static Factory<SolverImplementation> RegisteredFactory("SolverImplementation");

/** Second parameter constructor */
SolverImplementation::SolverImplementation(const NumericalScalar absoluteError,
    const NumericalScalar relativeError,
    const NumericalScalar residualError,
    const UnsignedInteger maximumFunctionEvaluation)
  : PersistentObject()
  , maximumFunctionEvaluation_(maximumFunctionEvaluation)
  , usedFunctionEvaluation_(0)
  , absoluteError_(absoluteError)
  , relativeError_(relativeError)
  , residualError_(residualError)
{
  // Nothing to do
}

/** Virtual constructor */
SolverImplementation * SolverImplementation::clone() const
{
  return new SolverImplementation(*this);
}

/** Comparison operator */
Bool SolverImplementation::operator ==(const SolverImplementation & other) const
{
  if (this == &other) return true;
  return (absoluteError_ == other.absoluteError_) &&
         (relativeError_ == other.relativeError_) &&
         (residualError_ == other.residualError_) &&
         (maximumFunctionEvaluation_ == other.maximumFunctionEvaluation_)
         && (usedFunctionEvaluation_ == other.usedFunctionEvaluation_);
}

/** String converter */
String SolverImplementation::__repr__() const
{
  OSS oss;
  oss << "class=" << SolverImplementation::GetClassName()
      << " absoluteError=" << absoluteError_
      << " relativeError=" << relativeError_
      << " residualError=" << residualError_
      << " maximumFunctionEvaluation=" << maximumFunctionEvaluation_
      << " usedFunctionEvaluation=" << usedFunctionEvaluation_;
  return oss;
}

/* Method save() stores the object through the StorageManager */
void SolverImplementation::save(Advocate & adv) const
{
  PersistentObject::save(adv);
  adv.saveAttribute("absoluteError_", absoluteError_);
  adv.saveAttribute("relativeError_", relativeError_);
  adv.saveAttribute("residualError_", residualError_);
  adv.saveAttribute("maximumFunctionEvaluation_", maximumFunctionEvaluation_);
}

/* Method load() reloads the object from the StorageManager */
void SolverImplementation::load(Advocate & adv)
{
  PersistentObject::load(adv);
  adv.loadAttribute("absoluteError_", absoluteError_);
  adv.loadAttribute("relativeError_", relativeError_);
  adv.loadAttribute("residualError_", residualError_);
  adv.loadAttribute("maximumFunctionEvaluation_", maximumFunctionEvaluation_);
}

/** Absolute error accessor */
void SolverImplementation::setAbsoluteError(const NumericalScalar absoluteError)
{
  absoluteError_ = absoluteError;
}

NumericalScalar SolverImplementation::getAbsoluteError() const
{
  return absoluteError_;
}

/** Relative error accessor */
void SolverImplementation::setRelativeError(const NumericalScalar relativeError)
{
  relativeError_ = relativeError;
}

NumericalScalar SolverImplementation::getRelativeError() const
{
  return relativeError_;
}

/** Residual error accessor */
void SolverImplementation::setResidualError(const NumericalScalar residualError)
{
  residualError_ = residualError;
}

NumericalScalar SolverImplementation::getResidualError() const
{
  return residualError_;
}

/** Maximum function evaluation accessor */
void SolverImplementation::setMaximumFunctionEvaluation(const UnsignedInteger maximumFunctionEvaluation)
{
  maximumFunctionEvaluation_ = maximumFunctionEvaluation;
}

UnsignedInteger SolverImplementation::getMaximumFunctionEvaluation() const
{
  return maximumFunctionEvaluation_;
}

UnsignedInteger SolverImplementation::getUsedFunctionEvaluation() const
{
  return usedFunctionEvaluation_;
}

/** Solve attempt to find one root to the equation function(x) = value in [infPoint, supPoint] */
NumericalScalar SolverImplementation::solve(const NumericalMathFunction & function,
    const NumericalScalar value,
    const NumericalScalar infPoint,
    const NumericalScalar supPoint) const
{
  if ((function.getInputDimension() != 1) || (function.getOutputDimension() != 1)) throw InvalidDimensionException(HERE) << "Error: solver implementation requires a scalar function, here input dimension=" << function.getInputDimension() << " and output dimension=" << function.getOutputDimension();
  if (maximumFunctionEvaluation_ < 2) throw InternalException(HERE) << "Error: solver needs to evaluate the function at least two times, here maximumFunctionEvaluation=" << maximumFunctionEvaluation_;
  /* We take into account the fact that we use 2 function calls when using the other solve method */
  maximumFunctionEvaluation_ -= 2;
  NumericalScalar root(solve(function, value, infPoint, supPoint, function(NumericalPoint(1, infPoint))[0], function(NumericalPoint(1, supPoint))[0]));
  maximumFunctionEvaluation_ += 2;
  usedFunctionEvaluation_ += 2;
  return root;
}

/** Solve attempt to find one root to the equation function(x) = value in [infPoint, supPoint] given function(infPoint) and function(supPoint) */
NumericalScalar SolverImplementation::solve(const NumericalMathFunction & function,
    const NumericalScalar value,
    const NumericalScalar infPoint,
    const NumericalScalar supPoint,
    const NumericalScalar infValue,
    const NumericalScalar supValue) const
{
  throw NotYetImplementedException(HERE) << "In SolverImplementation::solve(const NumericalMathFunction & function, const NumericalScalar value, const NumericalScalar infPoint, const NumericalScalar supPoint, const NumericalScalar infValue, const NumericalScalar supValue) const";
}

END_NAMESPACE_OPENTURNS
