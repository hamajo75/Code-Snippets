#include <ios>
#include <iostream>
#include <string>
#include <memory>

#include <ifaddrs.h>
#include <net/if.h>

// ifaddrs.h
// /* The `getifaddrs' function generates a linked list of these structures.
//    Each element of the list describes one network interface.  */
// struct ifaddrs
// {
//   struct ifaddrs *ifa_next;	/* Pointer to the next structure.  */

//   char *ifa_name;		/* Name of this network interface.  */
//   unsigned int ifa_flags;	/* Flags as from SIOCGIFFLAGS ioctl.  */

//   struct sockaddr *ifa_addr;	/* Network address of this interface.  */
//   struct sockaddr *ifa_netmask; /* Netmask of this interface.  */
//   union
//   {
//     /* At most one of the following two is valid.  If the IFF_BROADCAST
//        bit is set in `ifa_flags', then `ifa_broadaddr' is valid.  If the
//        IFF_POINTOPOINT bit is set, then `ifa_dstaddr' is valid.
//        It is never the case that both these bits are set at once.  */
//     struct sockaddr *ifu_broadaddr; /* Broadcast address of this interface. */
//     struct sockaddr *ifu_dstaddr; /* Point-to-point destination address.  */
//   } ifa_ifu;
//   /* These very same macros are defined by <net/if.h> for `struct ifaddr'.
//      So if they are defined already, the existing definitions will be fine.  */
// # ifndef ifa_broadaddr
// #  define ifa_broadaddr	ifa_ifu.ifu_broadaddr
// # endif
// # ifndef ifa_dstaddr
// #  define ifa_dstaddr	ifa_ifu.ifu_dstaddr
// # endif

//   void *ifa_data;		/* Address-specific data (may be unused).  */
// };


std::shared_ptr<struct ifaddrs> GetIfAddresses() {
  struct ifaddrs *ifap;

  auto ret = getifaddrs(&ifap);

  if (ret) {
    return nullptr;
  }

  return std::shared_ptr<struct ifaddrs>(ifap,
      [](struct ifaddrs* p) {
        freeifaddrs(p);
      });
}

void ProcessInterface(const struct ifaddrs& ifa) {
  auto if_name = ifa.ifa_name;
  std::cout << "interface name: " << if_name << "\n";
  bool up = ifa.ifa_flags & IFF_UP;
  std::cout << "interface up: " << std::boolalpha << up << "\n";
}

void GoThroughInterfaces(std::shared_ptr<struct ifaddrs> addrs) {
  for (struct ifaddrs *ifa = addrs.get(); ifa != NULL;
                      ifa = ifa->ifa_next) {
    if (ifa->ifa_addr == NULL)
      continue;

    ProcessInterface(*ifa);
  }
}

//-------------------------------------------------------------------------------
int main() {
  auto addrs = GetIfAddresses();
  GoThroughInterfaces(addrs);

  return 0;
}
