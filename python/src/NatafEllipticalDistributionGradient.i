// SWIG file NatafEllipticalDistributionGradient.i

%{
#include "NatafEllipticalDistributionGradient.hxx"
%}

%include NatafEllipticalDistributionGradient.hxx
namespace OT { %extend NatafEllipticalDistributionGradient { NatafEllipticalDistributionGradient(const NatafEllipticalDistributionGradient & other) { return new OT::NatafEllipticalDistributionGradient(other); } } }
