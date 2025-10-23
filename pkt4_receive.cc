// pkt4_receive.cc
#include <dhcp/pkt4.h>

#include <string>

#include <boost/algorithm/string.hpp>

#include <simple_ddos_guard.h>
#include <simple_ddos_guard_log.h>

using namespace isc::dhcp;
using namespace isc::hooks;
using namespace isc::simple_ddos_guard;

namespace {
bool runtime_logging = false;
bool renew_rejected_addresses = false;
bool enabled = false;
int requests_interval = 0;
int max_clients_storage_size_value = 0;
std::vector<DHCPClient> clients;
}  // namespace

namespace isc {
namespace simple_ddos_guard {

void
storeConfiguration(bool param_runtime_logging,
                   bool param_renew_rejected_addresses,
                   bool param_enabled,
                   int param_requests_interval,
                   int param_max_clients_storage_size_value) {
    runtime_logging = param_runtime_logging;
    renew_rejected_addresses = param_renew_rejected_addresses;
    enabled = param_enabled;
    requests_interval = param_requests_interval;
    max_clients_storage_size_value = param_max_clients_storage_size_value;
    clients.clear();
}

void
clearConfiguration() {
    runtime_logging = false;
    renew_rejected_addresses = false;
    enabled = false;
    requests_interval = 0;
    max_clients_storage_size_value = 0;
    clients.clear();
}
}  // namespace simple_ddos_guard
}  // namespace isc

extern "C" {

int
pkt4_receive(CalloutHandle& handle) {
    CalloutHandle::CalloutNextStep status = handle.getStatus();
    if (status == CalloutHandle::NEXT_STEP_DROP || status == CalloutHandle::NEXT_STEP_SKIP) {
        return (0);
    }

    if (!enabled) {
        return (0);
    }

    // This isn't a completely secure method. It's wiser to clean up some of the clients.
    if (clients.size() > (size_t)max_clients_storage_size_value) {
        clients.clear();
    }

    Pkt4Ptr query4_ptr;
    handle.getArgument("query4", query4_ptr);
    if (!query4_ptr) {
        return (0);
    }

    std::string hwaddr_text = query4_ptr->getHWAddr()->toText(false);
    long long current_timestamp = std::chrono::duration_cast<std::chrono::seconds>(
                                      std::chrono::system_clock::now().time_since_epoch())
                                      .count();

    DHCPClient* client = nullptr;
    for (size_t i = 0; i < clients.size(); i++) {
        if (clients[i].mac == hwaddr_text) {
            client = &clients[i];
            break;
        }
    }

    if (client == nullptr) {
        DHCPClient temp;
        temp.mac = hwaddr_text;
        temp.last_request_timestamp = current_timestamp;
        clients.push_back(temp);
        return (0);
    }

    if ((current_timestamp - client->last_request_timestamp) < requests_interval) {
        handle.setStatus(CalloutHandle::NEXT_STEP_DROP);

        if(renew_rejected_addresses) {
        	client->last_request_timestamp = current_timestamp;
        }

        if (runtime_logging) {
            LOG_INFO(simple_ddos_guard_logger, SIMPLE_DDOS_GUARD_LEASE_INTERVAL_VIOLATED)
                .arg(hwaddr_text);
        }

        return (0);
    }

    return (0);
}
}
