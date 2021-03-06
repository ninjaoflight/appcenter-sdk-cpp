#include <appcenter/sdk/ingestion/device.hpp>
#include <appcenter/sdk/ingestion/models/log.hpp>
#include <appcenter/sdk/util/Date.hpp>
#include <string_view>

namespace appcenter::sdk::ingestion::model {
const util::date::Date &Log::getTimestamp() const { return timestamp; }
void Log::setTimestamp(const util::date::Date &timestamp) {
	this->timestamp = timestamp;
}
const libUUID::UUID &Log::getSid() const { return sid; }
void Log::setSid(const libUUID::UUID &sid) { this->sid = sid; }
const std::string_view Log::getDistributionGroupId() const {
	return distributionGroupId;
}
void Log::setDistributionGroupId(const std::string &distributionGroupId) {
	this->distributionGroupId = distributionGroupId;
}
const std::string_view Log::getUserId() const { return userID; }
void Log::setUserId(const std::string &userID) { this->userID = userID; }
const Device &Log::getDevice() const { return device; }
void Log::setDevice(const Device &device) { this->device = device; }
const std::any &Log::getTag() const { return tag; }
void Log::setTag(const std::any &tag) { this->tag = tag; }
void Log::addTransmissionTargetToken(
    const std::string &transmissionTargetToken) {
	transmissionTargetTokens.insert(transmissionTargetToken);
}
const std::set<std::string> &Log::getTransmissionTargetTokens() const {
	return transmissionTargetTokens;
}
} // namespace appcenter::sdk::ingestion::model