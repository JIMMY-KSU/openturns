// SWIG file UserDefinedStationaryCovarianceModel.i

%{
#include "UserDefinedStationaryCovarianceModel.hxx"
%}


%include UserDefinedStationaryCovarianceModel.hxx
namespace OT{ %extend UserDefinedStationaryCovarianceModel { UserDefinedStationaryCovarianceModel(const UserDefinedStationaryCovarianceModel & other) { return new OT::UserDefinedStationaryCovarianceModel(other); } } }
