//                                               -*- C++ -*-
/**
 *  @brief A sequence of numerical math function collection
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
#ifndef OPENTURNS_BASISSEQUENCE_HXX
#define OPENTURNS_BASISSEQUENCE_HXX

#include "TypedCollectionInterfaceObject.hxx"
#include "BasisSequenceImplementation.hxx"

BEGIN_NAMESPACE_OPENTURNS



/**
 * @class BasisSequence
 *
 * A sequence of numerical math function collection.
 */
class OT_API BasisSequence
  : public TypedCollectionInterfaceObject<BasisSequenceImplementation>
{
  CLASSNAME;

public:


  /** Default constructor */
  BasisSequence();

  /** Default constructor */
  BasisSequence(const Basis & psi);

  /** Contructor from implementation */
  BasisSequence(const BasisSequenceImplementation & implementation);

  /** Dimension accessor */
  UnsignedInteger getDimension() const;

  /** Returns the master basis */
  Basis getMasterBasis() const;

  /** Sub-basis accessor */
  Basis getBasis(const UnsignedInteger index) const;

  /** Indices accessor */
  Indices getIndices(const UnsignedInteger index) const;

  /** Converter to Basis collection */
  operator PersistentCollection< Indices > () const;

  /** String converter */
  virtual String __repr__() const;
  virtual String __str__(const String & offset = "") const;

}; /* class BasisSequence */


END_NAMESPACE_OPENTURNS

#endif /* OPENTURNS_BASISSEQUENCE_HXX */
