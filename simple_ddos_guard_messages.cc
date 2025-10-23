#include <cstddef>
#include <log/message_types.h>
#include <log/message_initializer.h>

extern const isc::log::MessageID SIMPLE_DDOS_GUARD_RUNTIME_LOGGING_BAD_TYPE = "SIMPLE_DDOS_GUARD_RUNTIME_LOGGING_BAD_TYPE";
extern const isc::log::MessageID SIMPLE_DDOS_GUARD_RENEW_REJECTED_ADDRESSES_BAD_TYPE = "SIMPLE_DDOS_GUARD_RENEW_REJECTED_ADDRESSES_BAD_TYPE";
extern const isc::log::MessageID SIMPLE_DDOS_GUARD_MISSING_PARAMS = "SIMPLE_DDOS_GUARD_MISSING_PARAMS";
extern const isc::log::MessageID SIMPLE_DDOS_GUARD_ENABLED_PARAM_BAD_TYPE = "SIMPLE_DDOS_GUARD_ENABLED_PARAM_BAD_TYPE";
extern const isc::log::MessageID SIMPLE_DDOS_GUARD_NUMERIC_PARAMS_BAD_TYPE = "SIMPLE_DDOS_GUARD_NUMERIC_PARAMS_BAD_TYPE";
extern const isc::log::MessageID SIMPLE_DDOS_GUARD_NUMERIC_PARAMS_LESS_ZERO = "SIMPLE_DDOS_GUARD_NUMERIC_PARAMS_LESS_ZERO";
extern const isc::log::MessageID SIMPLE_DDOS_GUARD_LOAD_ERROR = "SIMPLE_DDOS_GUARD_LOAD_ERROR";
extern const isc::log::MessageID SIMPLE_DDOS_GUARD_UNLOAD_SUCCESS = "SIMPLE_DDOS_GUARD_UNLOAD_SUCCESS";
extern const isc::log::MessageID SIMPLE_DDOS_GUARD_LEASE_INTERVAL_VIOLATED = "SIMPLE_DDOS_GUARD_LEASE_INTERVAL_VIOLATED";

namespace {

const char* values[] = {
    "SIMPLE_DDOS_GUARD_RUNTIME_LOGGING_BAD_TYPE", "Param \"runtime-logging\" must be of boolean type.",
    "SIMPLE_DDOS_GUARD_RENEW_REJECTED_ADDRESSES_BAD_TYPE", "Param \"renew-rejected-addresses\" must be of boolean type.",
    "SIMPLE_DDOS_GUARD_MISSING_PARAMS", "Hook awaiting required parameters: \"enabled\", \"requests-interval-seconds\" and \"max-clients-storage-size\".",
    "SIMPLE_DDOS_GUARD_ENABLED_PARAM_BAD_TYPE", "Param \"enabled\" must be of boolean type.",
    "SIMPLE_DDOS_GUARD_NUMERIC_PARAMS_BAD_TYPE", "Params \"requests-interval-seconds\" or \"max-clients-storage-size\" must be of integer type.",
    "SIMPLE_DDOS_GUARD_NUMERIC_PARAMS_LESS_ZERO", "Params \"requests-interval-seconds\" or \"max-clients-storage-size\" less zero.",
    "SIMPLE_DDOS_GUARD_LOAD_ERROR", "An unexpected error occurred while turning on the hook.",
    "SIMPLE_DDOS_GUARD_UNLOAD_SUCCESS", "Hook unloaded successfully.",
    "SIMPLE_DDOS_GUARD_LEASE_INTERVAL_VIOLATED", "The client is attempting to acquire a lease faster than the lease interval specified in the hook configuration.",
    NULL
};

const isc::log::MessageInitializer initializer(values);

} // Anonymous namespace
