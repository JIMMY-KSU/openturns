// SWIG file OrdinalSumCopula.i

%{
#include "PythonWrappingFunctions.hxx"
#include "OrdinalSumCopula.hxx"
%}


%include OrdinalSumCopula_doc.i


%include OrdinalSumCopula.hxx

namespace OT {

%extend OrdinalSumCopula {

     OrdinalSumCopula(PyObject * pyObj, const NumericalPoint & bounds)
{
  OT::Pointer<OT::Collection<OT::Copula> > p_coll =  OT::buildCollectionFromPySequence<OT::Copula>( pyObj );
  return new OT::OrdinalSumCopula( *p_coll, bounds );
}

OrdinalSumCopula(const OrdinalSumCopula & other)
{
  return new OT::OrdinalSumCopula(other);
}

} // OrdinalSumCopula
 
} // OT
