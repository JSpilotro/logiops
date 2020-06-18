#include <cassert>

#include "Device.h"
#include "../hidpp/defs.h"

using namespace logid::backend::hidpp20;

std::vector<uint8_t> Device::callFunction(uint8_t feature_index,
        uint8_t function, std::vector<uint8_t>& params)
{
    hidpp::Report::Type type;

    assert(params.size() <= hidpp::LongParamLength);
    if(params.size() <= hidpp::ShortParamLength)
        type = hidpp::Report::Type::Short;
    else if(params.size() <= hidpp::LongParamLength)
        type = hidpp::Report::Type::Long;

    hidpp::Report request(type, deviceIndex(), feature_index, function,
            LOGID_HIDPP_SOFTWARE_ID);
    std::copy(params.begin(), params.end(), request.paramBegin());

    auto response = this->sendReport(request);
    return std::vector<uint8_t>(response.paramBegin(), response.paramEnd());
}