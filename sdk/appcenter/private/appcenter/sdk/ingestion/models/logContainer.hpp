#pragma once
#include <appcenter/sdk/ingestion/models/log.hpp>

#include <functional>
#include <memory>
#include <utility>
#include <vector>

namespace appcenter::sdk::ingestion::model {
class LogContainer {
	/**
	 * @brief the list of logs
	 *
	 */
	std::vector<std::unique_ptr<Log>> logs;

  public:
	/**
	 * @brief Get the Logs object
	 *
	 * @return const std::vector<Log>& the logs value
	 */
	const std::vector<std::unique_ptr<Log>> &getLogs() const { return logs; }

	/**
	 * @brief Set the Logs object
	 *
	 * @param logs the logs value to set
	 */
	void setLogs(std::vector<std::unique_ptr<Log>> &&logs) {
		this->logs = std::move(logs);
	}

	bool operator==(const LogContainer &other) const {
		if(logs.size() != other.logs.size()) {
			return false;
		}
		
		for(size_t i = 0; i < logs.size(); i++) {
			if(logs[i] != other.logs[i]) {
				return false;
			}
		}
		return true;
	}

	std::size_t hashCode() const {
		std::size_t seed = logs.size();
		for (auto &i : logs) {
			seed ^= size_t(&i) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
		}
		return seed;
	}
};
} // namespace appcenter::sdk::ingestion::model