# KEA Simple DDOS Guard Hook

## Introduction

This repository is an example of a custom KEA hook implementation.
The hook implements a simple function to protect a DHCP server from DDOS attacks by setting a timer between user attempts to request an address.

## Service Info
The hook is implemented only for `kea-dhcp4` service.

## Parameters
### Optional
`runtime-logging` - Boolean type (by default: false). Determines whether to log lease rejection events from clients to the log file.

`renew-rejected-addresses` - Boolean type (by default: false). Determines whether the last address request timer should be updated even if the address was rejected by the server.

### Required
`enabled` - Boolean type. Determines the hook's operating status. False - disabled. True - enabled.

`requests-interval-seconds` - Unsigned Integer. Specifies the number of seconds after which the client is allowed to request the address again.

`max-clients-storage-size` - Unsigned Integer. While the hook is running, its memory stores information about users MAC addresses and the time of their last attempt to request an address. This parameter determines the number of clients that can be simultaneously stored in the hook's memory.

## Example configuration
```json
{
	"enabled":  true,
	"runtime-logging":  true,
	"renew-rejected-addresses": true,
	"requests-interval-seconds":  10,
	"max-clients-storage-size":  100
}
```

## Build

### Build with G++
1. Install kea-dev package (In Arch it is part of the KEA package, in other distributions it may be a separate package).
2. Clone this repository `git clone https://github.com/sanua356/kea-hook-simple-ddos-guard.git`.
3. Go to the repository directory `cd ./kea-hooks-simple-ddos-guard`.
4. Make the build script executable `chmod +x ./build.sh`.
5. Run build script `./build.sh` (sudo rights may be required).
6. Find ".so" library in current directory.

### Build with Meson
1. Clone KEA official repository: `git clone https://gitlab.isc.org/isc-projects/kea.git`.
2. Clone current repository in KEA repository path `/src/hooks/dhcp/`.
3. In file `meson.build` by path `/src/hooks/dhcp` paste new line `subdir('simple_ddos_guard')` .
4. Run `meson compile -C build` in terminal.
5. After compilation the library file is located at the path `/build/src/hooks/dhcp/simple_ddos_guard`.

## License

MIT
