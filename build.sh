g++ -ggdb -I. -I /usr/include/kea -L /usr/lib/kea/lib -fpic -shared -o simple_ddos_guard.so \
  load_unload.cc pkt4_receive.cc version.cc simple_ddos_guard_messages.cc simple_ddos_guard_log.cc  \
  -lkea-dhcpsrv -lkea-dhcp -lkea-hooks -lkea-log -lkea-util -lkea-exceptions -lcurl
