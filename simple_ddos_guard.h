#ifndef SIMPLE_DDOS_GUARD_H
#define SIMPLE_DDOS_GUARD_H

#include <log/macros.h>
#include <log/message_initializer.h>

#include <simple_ddos_guard_messages.h>

namespace isc {
namespace simple_ddos_guard {

struct DHCPClient {
    std::string mac;
    long long last_request_timestamp;
};

void
storeConfiguration(bool runtime_logging,
                   bool renew_rejected_addresses,
                   bool enabled,
                   int requests_interval,
                   int max_clients_storage_size_value);

void
clearConfiguration();

}  // namespace simple_ddos_guard
}  // namespace isc

#endif
