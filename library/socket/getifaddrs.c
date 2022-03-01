/*
 * $Id: getifaddrs.c,v 1.0 2022-02-10 17:02:58 apalmate Exp $
 *
 * :ts=4
 *
 * Portable ISO 'C' (1994) runtime library for the Amiga computer
 * Copyright (c) 2002-2015 by Olaf Barthel <obarthel (at) gmx.net>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *   - Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *
 *   - Neither the name of Olaf Barthel nor the names of contributors
 *     may be used to endorse or promote products derived from this
 *     software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef _UNISTD_HEADERS_H
#include "unistd_headers.h"
#endif /* _UNISTD_HEADERS_H */

#ifndef _SOCKET_HEADERS_H
#include "socket_headers.h"
#endif /* _SOCKET_HEADERS_H */

#include <ifaddrs.h>
#include <net/if.h>

#define ROUNDUP(x, size)    ((((x) + (size) - 1) / (size)) * (size))
#define IFCONF_STARTENT 10
#define IFCONF_MAXENT 1000

struct ifawrap {
    struct ifaddrs *ifaddrs;
    struct ifaddrs *prev;
};

static int
ifaddrs_add(struct ifawrap *ifawrap, char *name, unsigned int flags,
            struct sockaddr *addr, struct sockaddr *netmask,
            struct sockaddr *dstaddr, struct sockaddr *data, size_t addrlen) {
    size_t nameoff, addroff, maskoff, dstoff;

    struct ifaddrs *new;
    size_t addrskip;
    size_t namelen;
    size_t nsize;
    char *p;

    namelen = strlen(name) + 1;

    addrskip = ROUNDUP(addrlen, sizeof(uint32_t));

    nsize = 0;
    nsize += ROUNDUP(sizeof(struct ifaddrs), sizeof(uint32_t));
    nameoff = nsize;

    nsize += ROUNDUP(namelen, sizeof(uint32_t));

    nsize += ROUNDUP(sizeof(flags), sizeof(uint32_t));
    addroff = nsize;

    if (addr != NULL)
        nsize += addrskip;
    maskoff = nsize;

    if (netmask != NULL)
        nsize += addrskip;
    dstoff = nsize;

    if (dstaddr != NULL)
        nsize += addrskip;

    if (data != NULL) /*XXX*/
        nsize += addrskip; /*XXX*/

    if ((new = malloc(nsize)) == NULL)
        return -1; /* let caller free already allocated data */
    if (ifawrap->ifaddrs == NULL)
        ifawrap->ifaddrs = new;
    else
        ifawrap->prev->ifa_next = new;
    ifawrap->prev = new;

    new->ifa_next = NULL;

    p = (char *) new + nameoff;
    strncpy(p, name, namelen - 1);
    p[namelen - 1] = '\0';
    new->ifa_name = p;

    new->ifa_flags = flags;

    if (addr != NULL) {
        p = (char *) new + addroff;
        memcpy(p, addr, addrlen);
        new->ifa_addr = (struct sockaddr *) p;
    } else
        new->ifa_addr = NULL;

    if (netmask != NULL) {
        p = (char *) new + maskoff;
        memcpy(p, netmask, addrlen);
        new->ifa_netmask = (struct sockaddr *) p;
    } else
        new->ifa_netmask = NULL;

    if (dstaddr != NULL) {
        p = (char *) new + dstoff;
        memcpy(p, dstaddr, addrlen);
        new->ifa_dstaddr = (struct sockaddr *) p;
    } else
        new->ifa_dstaddr = NULL;

    new->ifa_data = NULL;

    return 0;
}

int getifaddrs(struct ifaddrs **ifap) {

    unsigned int success = 0;

    struct List *netiflist = NULL;
    struct Node *node = NULL;
    struct ifawrap ifawrap;
    size_t addrlen;

    memset(&ifawrap, 0, sizeof(struct ifawrap));

    ifawrap.ifaddrs = NULL;
    netiflist = __ISocket->ObtainInterfaceList();
    if (netiflist != NULL) {
        node = GetHead(netiflist);
        if (node != NULL) {
            while (node != NULL) {
                if (node->ln_Name != NULL) {
                    UBYTE hwAddress[IF_NAMESIZE] = {0};
                    LONG mtu, metric, state, bindType, index, debug, ptp;
                    ULONG packetsReceived, packetsSent, badData, overruns;
                    struct sockaddr localAddress, destinationAddress, broadcastAddress;
                    struct sockaddr_in netmask, primaryDns, secondaryDns;
                    unsigned int flags = 0;
                    // FOUND ONE
                    long querySuccess = __ISocket->QueryInterfaceTags(node->ln_Name,
                                                                         IFQ_HardwareAddress, &hwAddress,
                                                                         IFQ_HardwareMTU, &mtu,
                                                                         IFQ_DeviceUnit, &index,
                                                                         IFQ_PacketsReceived, &packetsReceived,
                                                                         IFQ_PacketsSent, &packetsSent,
                                                                         IFQ_BadData, &badData,
                                                                         IFQ_Overruns, &overruns,
                                                                         IFQ_Address, &localAddress,
                                                                         IFQ_DestinationAddress, &destinationAddress,
                                                                         IFQ_BroadcastAddress, &broadcastAddress,
                                                                         IFQ_NetMask, &netmask,
                                                                         IFQ_Metric, &metric,
                                                                         IFQ_State, &state,
                                                                         IFQ_GetDebugMode, &debug,
                                                                         IFQ_AddressBindType, &bindType,
                                                                         IFQ_PrimaryDNSAddress, &primaryDns,
                                                                         IFQ_SecondaryDNSAddress, &secondaryDns,
                                                                         TAG_DONE);
                    if (querySuccess) {
                        addrlen = sizeof(struct sockaddr);
                        /* TODO - Move this to ioctl with SIOCGIFFLAGS request */
                        if (state == SM_Online)
                            flags |= IFF_UP;
                        if (state == SM_Up)
                            flags |= IFF_RUNNING;
                        if (debug == TRUE)
                            flags |= IFF_DEBUG;

                        if (ifaddrs_add(&ifawrap, node->ln_Name, flags, &localAddress, (struct sockaddr*) &netmask, &broadcastAddress, NULL, addrlen) == -1) {
                            if (ifawrap.ifaddrs != NULL) {
                                freeifaddrs(ifawrap.ifaddrs);
                                success = -1;
                                break;
                            }
                        }
                    } else {
                        success = -1;
                        break;
                    }
                }
                node = GetSucc(node);
            }
        }
        __ISocket->ReleaseInterfaceList(netiflist);
    }

    if (success == 0 && ifawrap.ifaddrs != NULL)
        *ifap = ifawrap.ifaddrs;

    return success;
}