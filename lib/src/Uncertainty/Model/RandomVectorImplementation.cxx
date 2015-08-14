//                                               -*- C++ -*-
/**
 *  @brief An interface for all implementation class of random vectors
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
#include "PersistentObjectFactory.hxx"
#include "RandomVectorImplementation.hxx"
#include "Exception.hxx"

BEGIN_NAMESPACE_OPENTURNS

CLASSNAMEINIT(RandomVectorImplementation);

static Factory<RandomVectorImplementation> RegisteredFactory("RandomVectorImplementation");

/* Default constructor */
RandomVectorImplementation::RandomVectorImplementation()
  : PersistentObject()
  , description_()
{
  // Nothing to do
}

/* Virtual constructor */
RandomVectorImplementation * RandomVectorImplementation::clone() const
{
  return new RandomVectorImplementation(*this);
}

/* String converter */
String RandomVectorImplementation::__repr__() const
{
  OSS oss;
  oss << "class=" << RandomVectorImplementation::GetClassName();
  return oss;
}



/* Description accessor */
void RandomVectorImplementation::setDescription(const Description & description)
{
  if (description.getSize() != getDimension())
    throw InvalidDimensionException(HERE) << "Description's size must be equal to dimension."
                                          << " Here, description's size=" << description.getSize() << " and dimension=" << getDimension();
  description_ = description;
}

Description RandomVectorImplementation::getDescription() const
{
  return description_;
}


/* Here is the interface that all derived class must implement */


/* Is the underlying random vector composite ? */
Bool RandomVectorImplementation::isComposite() const
{
  return false;
}

/* Dimension accessor */
UnsignedInteger RandomVectorImplementation::getDimension() const
{
  throw NotYetImplementedException(HERE) << "In RandomVectorImplementation::getDimension() const";
}

/* Realization accessor */
NumericalPoint RandomVectorImplementation::getRealization() const
{
  throw NotYetImplementedException(HERE) << "In RandomVectorImplementation::getRealization() const";
}

/* Numerical sample accessor */
NumericalSample RandomVectorImplementation::getSample(const UnsignedInteger size) const
{
  NumericalSample result(size, getDimension());
  for (UnsignedInteger i = 0; i < size; ++i) result[i] = getRealization();
  result.setDescription(getDescription());
  return result;
}

/* Mean accessor */
NumericalPoint RandomVectorImplementation::getMean() const
{
  throw NotYetImplementedException(HERE) << "In RandomVectorImplementation::getMean() const";
}

/* Covariance accessor */
CovarianceMatrix RandomVectorImplementation::getCovariance() const
{
  throw NotYetImplementedException(HERE) << "In RandomVectorImplementation::getCovariance() const";
}

/* Get the random vector corresponding to the i-th marginal component */
RandomVectorImplementation::Implementation RandomVectorImplementation::getMarginal(const UnsignedInteger i) const
{
  throw NotYetImplementedException(HERE) << "In RandomVectorImplementation::getMarginal(const UnsignedInteger i) const";
}

/* Get the marginal random vector corresponding to indices components */
RandomVectorImplementation::Implementation RandomVectorImplementation::getMarginal(const Indices & indices) const
{
  throw NotYetImplementedException(HERE) << "In RandomVectorImplementation::getMarginal(const Indices & indices) const";
}

/* Fake method due to pbs with dynamic_cast and Pointer */
RandomVectorImplementation::Antecedent RandomVectorImplementation::getAntecedent() const
{
  throw NotYetImplementedException(HERE) << "In RandomVectorImplementation::getAntecedent() const";
}

/* Fake method due to pbs with dynamic_cast and Pointer */
NumericalMathFunction RandomVectorImplementation::getFunction() const
{
  throw NotYetImplementedException(HERE) << "In RandomVectorImplementation::getFunction() const";
}

/* Fake method due to pbs with dynamic_cast and Pointer */
Distribution RandomVectorImplementation::getDistribution() const
{
  throw NotYetImplementedException(HERE) << "In RandomVectorImplementation::getDistribution() const";
}

/* Fake method due to pbs with dynamic_cast and Pointer */
ComparisonOperator RandomVectorImplementation::getOperator() const
{
  throw NotYetImplementedException(HERE) << "In RandomVectorImplementation::getOperator() const";
}

/* Fake method due to pbs with dynamic_cast and Pointer */
Process RandomVectorImplementation::getProcess() const
{
  throw NotYetImplementedException(HERE) << "In RandomVectorImplementation::getProcess() const";
}

/* Fake method due to pbs with dynamic_cast and Pointer */
Domain RandomVectorImplementation::getDomain() const
{
  throw NotYetImplementedException(HERE) << "In RandomVectorImplementation::getDomain() const";
}

/* Fake method due to pbs with dynamic_cast and Pointer */
NumericalScalar RandomVectorImplementation::getThreshold() const
{
  throw NotYetImplementedException(HERE) << "In RandomVectorImplementation::getThreshold() const";
}

/* Method save() stores the object through the StorageManager */
void RandomVectorImplementation::save(Advocate & adv) const
{
  PersistentObject::save(adv);
  adv.saveAttribute( "description_", description_ );
}

/* Method load() reloads the object from the StorageManager */
void RandomVectorImplementation::load(Advocate & adv)
{
  PersistentObject::load(adv);
  adv.loadAttribute( "description_", description_ );
}

END_NAMESPACE_OPENTURNS
