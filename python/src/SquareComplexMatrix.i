// SWIG file SquareComplexMatrix.i

%{
#include "SquareComplexMatrix.hxx"
%}

%include SquareComplexMatrix_doc.i

%rename(__pow__) OT::SquareComplexMatrix::power(const UnsignedInteger n) const;

%include SquareComplexMatrix.hxx

namespace OT {

%extend SquareComplexMatrix {

  SquareComplexMatrix(const SquareComplexMatrix & other) { return new OT::SquareComplexMatrix(other); }

  SquareComplexMatrix(PyObject * pyObj) { return new OT::SquareComplexMatrix( OT::convert<OT::_PySequence_,OT::SquareComplexMatrix>(pyObj) ); }

  OTComplexMatrixGetAccessors()

  SquareComplexMatrix __truediv__(NumericalComplex s) { return (*self) / s; }

} // SquareComplexMatrix
} // OT
