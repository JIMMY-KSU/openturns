// SWIG file SpectralModelImplementation.i

%{
#include "SpectralModelImplementation.hxx"
%}


%include SpectralModelImplementation.hxx
namespace OT{ %extend SpectralModelImplementation { SpectralModelImplementation(const SpectralModelImplementation & other) { return new OT::SpectralModelImplementation(other); } } }
