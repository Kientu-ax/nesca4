/*
 * LIBNCSOCK & NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "include/ip.h"

u8 *build_ip_pkt(u32 saddr, u32 daddr, u8 proto, int ttl,
    u16 ipid, u8 tos, bool df, const u8 *ipopt, int ipoptlen,
    const char *data, u16 datalen, u32 *plen)
{
  int myttl = 0, packetlen = 0;
  struct ip_header *ip;
  u8 *packet;

  packetlen = sizeof(struct ip_header) + ipoptlen + datalen;
  packet = (u8*)malloc(packetlen);
  if (!packet)
    return NULL;
  ip = (struct ip_header *)packet;
  assert(ipoptlen % 4 == 0);

  if (ttl == -1)
    myttl = generate_random_u32(39, 255);
  else
    myttl = ttl;

  fill_ip_raw(ip, packetlen, ipopt, ipoptlen, tos, ipid,
      df ? IP_DF : 0, myttl, proto, saddr, daddr);

  if (data && datalen)
    memcpy((u8 *) ip + sizeof(struct ip_header) + ipoptlen, data, datalen);

  *plen = packetlen;
  return packet;
}
