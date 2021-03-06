#pragma once
#include <appcenter/sdk/core/logger.hpp>
#include <appcenter/sdk/service/internalService.hpp>
#include <appcenter/sdk/service/service.hpp>
#include <appcenter/util/mixin/singleton.hpp>
#include <future>
#include <string>
#include <string_view>

// GUID
#include <libuuid/UUID.hpp>

namespace appcenter::sdk::core {
class Platform : public util::mixin::Singleton<Platform>,
                 public service::InternalService<Platform> {
	// todo: move this to the requests/ingestion layer
	bool networkAllowed{true};
	libUUID::UUID installId{libUUID::UUID()};
	// todo: implement a way to change the log url in the ingestion service
	std::string logUrl;
	// todo: add a application configuration service
	std::string userId;
	std::string countryCode;
	std::string appSecret;
	bool configured{false};
	// todo: add a way to change the max storage size in the ingestion service
	size_t maxStorageSize{0};

  public:
	Platform() : InternalService<Platform>("AppCenter") {}
	// Error message to display for unsupported targets
	// const std::string_view getErrorMessage();

	/**
	 * @brief Get the Platform Log Level object
	 *
	 * @return the Platform Log Level
	 */
	const core::logging::LogLevel getPlatformLogLevel() const;

	/**
	 * @brief Set the Platform Log Level object
	 *
	 * @param logLevel the Platform Log Level
	 */
	void setPlatformLogLevel(const core::logging::LogLevel level);

	/**
	 * @brief Get if Network requests are allowed
	 *
	 */
	const bool isNetworkAllowed() const;

	/**
	 * @brief Set if Network requests are allowed
	 *
	 */
	void setNetworkAllowed(const bool allowed);

	// ignore PlatformIsEnabledAsync
	// ignore PlatformSetEnabledAsync

	/**
	 * @brief return the InstallID
	 *
	 * @note if the install id is not set, it will be generated
	 *
	 * @return the InstallID
	 */
	const libUUID::UUID getInstallId();

	/**
	 * @brief sets the Log URL
	 */
	void setLogUrl(const std::string_view url);

	/**
	 * @brief sets the userId
	 */
	void setUserId(const std::string_view userId);

	/**
	 * @brief sets the country code
	 *
	 * @param countryCode the two-letter ISO country code
	 */
	void setCountryCode(const std::string_view countryCode);

	/**
	 * @brief check if the platform is configured
	 *
	 * @return true the platform is configured
	 * @return false the platform is not configured
	 */
	const bool isConfigured() const;

	/**
	 * @brief configure the platform with the given app secret
	 *
	 * @param appSecret the app secret
	 */
	void configure(const std::string_view appSecret);

	// TODO: implement a propper way to start services
	/**
	 * @brief start a service
	 *
	 * @param service the service to start
	 */
	void start(service::Service *service);

	/**
	 * @brief start the given services
	 */
	void start(const std::vector<service::Service *> services);

	/**
	 * @brief start the given services
	 *
	 * @param appSecret the app secret
	 * @param services the services to start
	 */
	void start(const std::string_view appSecret,
	           const std::vector<service::Service *> services);

	/**
	 * @brief Set the Max Storage Size for App Center
	 *
	 * @note the default value is 10MB, the minimum allowed is 20KB, also the
	 * sdk rounds the size up to the next multiple of the page size. The App
	 * Center SDK uses a page size of 4KB, finally, all the logs older than 25
	 * days will be discarded.
	 *
	 * @param bytes the max storage size in bytes
	 * @return std::future<bool> the future of the operation
	 */
	std::future<bool> setMaxStorageSizeAsync(size_t bytes);

	bool setMaxStorageSize(size_t bytes);

	// void unsetInstance();
  private:
	std::vector<sdk::service::Service *> services;
};
} // namespace appcenter::sdk::core