#include <config.h>

#include <hooks/hooks.h>

namespace isc {
namespace simple_ddos_guard {

extern "C" {

int
version() {
    return (KEA_HOOKS_VERSION);
}

}  // extern "C"

}  // namespace simple_ddos_guard
}  // namespace isc
