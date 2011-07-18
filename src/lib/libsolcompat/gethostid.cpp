#include <NetworkInterface.h>
#include <NetworkRoster.h>
#include <arpa/inet.h>

extern "C" int32_t gethostid()
{
	// grab the first network interface with a valid ip address
	BNetworkRoster& roster = BNetworkRoster::Default();
	BNetworkInterface interface;
	BNetworkAddress hw_addr;
	BNetworkInterfaceAddress interface_addr;
	struct in_addr in;
	uint32 cookie = 0;
	
	while (roster.GetNextInterface(&cookie, interface) == B_OK) {
 		if (interface.GetHardwareAddress(hw_addr) == B_OK) {
 			// we don't want the local loopback
 			if (hw_addr.LinkLevelType() == IFT_LOOP)
 				continue;
 			
 			// grab the first address we can find
 			if (interface.GetAddressAt(0, interface_addr) == B_OK)
 				break;
 		}
	}
	
	inet_pton(interface_addr.Address().Family(),
		interface_addr.Address().ToString().String(), &in);
	
	return (int32_t) (in.s_addr << 16 | in.s_addr >> 16);
}
