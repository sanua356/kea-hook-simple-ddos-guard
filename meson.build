dhcp_simple_ddos_guard_lib = shared_library(
    'dhcp_simple_ddos_guard',
    'pkt4_receive.cc',
    'simple_ddos_guard_log.cc',
    'simple_ddos_guard_messages.cc',
    'load_unload.cc',
    'version.cc',
    include_directories: [include_directories('.')] + INCLUDES,
    install: true,
    install_dir: HOOKS_PATH,
    install_rpath: INSTALL_RPATH,
    build_rpath: BUILD_RPATH,
    link_with: LIBS_BUILT_SO_FAR,
    name_suffix: 'so',
)
dhcp_simple_ddos_guard_archive = static_library(
    'dhcp_simple_ddos_guard',
    objects: dhcp_simple_ddos_guard_lib.extract_all_objects(recursive: false),
)
