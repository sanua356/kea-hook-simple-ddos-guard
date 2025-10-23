#include <config.h>

#include <cc/dhcp_config_error.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/srv_config.h>
#include <exceptions/exceptions.h>
#include <hooks/library_handle.h>
#include <process/daemon.h>

#include <simple_ddos_guard.h>
#include <simple_ddos_guard_log.h>

#include "log/macros.h"

namespace isc {
namespace simple_ddos_guard {

using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::process;
using namespace isc::hooks;

extern "C" {
int
load(isc::hooks::LibraryHandle& handle) {
    try {
        // Make the hook library not loadable by d2 or ca.
        uint16_t family = CfgMgr::instance().getFamily();
        const std::string& proc_name = Daemon::getProcName();
        if (family == AF_INET) {
            if (proc_name != "kea-dhcp4") {
                isc_throw(isc::Unexpected,
                          "Bad process name: " << proc_name << ", expected kea-dhcp4");
            }
        }

        ConstElementPtr enabled = handle.getParameter("enabled");
        ConstElementPtr requests_interval_seconds = handle.getParameter("requests-interval-seconds");
        ConstElementPtr max_clients_storage_size = handle.getParameter("max-clients-storage-size");

        // Not required params
        ConstElementPtr runtime_logging = handle.getParameter("runtime-logging");
        ConstElementPtr renew_rejected_addresses = handle.getParameter("renew-rejected-addresses");

        bool runtime_logging_value = false;

        if (runtime_logging != nullptr) {
            if (runtime_logging->getType() != Element::boolean) {
                LOG_ERROR(simple_ddos_guard_logger, SIMPLE_DDOS_GUARD_RUNTIME_LOGGING_BAD_TYPE);
                return (1);
            }
            runtime_logging_value = runtime_logging->boolValue();
        }

        bool renew_rejected_addresses_value = false;

        if (renew_rejected_addresses != nullptr) {
            if (renew_rejected_addresses->getType() != Element::boolean) {
                LOG_ERROR(simple_ddos_guard_logger,
                          SIMPLE_DDOS_GUARD_RENEW_REJECTED_ADDRESSES_BAD_TYPE);
                return (1);
            }
            renew_rejected_addresses_value = renew_rejected_addresses->boolValue();
        }

        if (enabled == nullptr || requests_interval_seconds == nullptr ||
            max_clients_storage_size == nullptr) {
            LOG_ERROR(simple_ddos_guard_logger, SIMPLE_DDOS_GUARD_MISSING_PARAMS);
            return (1);
        }

        if (enabled->getType() != Element::boolean) {
            LOG_ERROR(simple_ddos_guard_logger, SIMPLE_DDOS_GUARD_ENABLED_PARAM_BAD_TYPE);
            return (1);
        }

        if (requests_interval_seconds->getType() != Element::integer ||
            max_clients_storage_size->getType() != Element::integer) {
            LOG_ERROR(simple_ddos_guard_logger, SIMPLE_DDOS_GUARD_NUMERIC_PARAMS_BAD_TYPE);
            return (1);
        }

        int enabled_value = enabled->boolValue();
        int requests_interval_seconds_value = requests_interval_seconds->intValue();
        int max_clients_storage_size_value = max_clients_storage_size->intValue();

        if (requests_interval_seconds_value < 0 || max_clients_storage_size_value < 0) {
            LOG_ERROR(simple_ddos_guard_logger, SIMPLE_DDOS_GUARD_NUMERIC_PARAMS_LESS_ZERO);
            return (1);
        }

        clearConfiguration();
        storeConfiguration(runtime_logging_value, renew_rejected_addresses_value, enabled_value,
                           requests_interval_seconds_value, max_clients_storage_size_value);
        return (0);
    } catch (const std::exception& ex) {
        LOG_ERROR(simple_ddos_guard_logger, SIMPLE_DDOS_GUARD_LOAD_ERROR);
        return (1);
    }
}

int
unload() {
    clearConfiguration();
    LOG_INFO(simple_ddos_guard_logger, SIMPLE_DDOS_GUARD_UNLOAD_SUCCESS);
    return (0);
}

int
multi_threading_compatible() {
    return (1);
}
}

}  // namespace simple_ddos_guard
}  // namespace isc
