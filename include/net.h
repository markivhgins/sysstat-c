#ifndef NET_H
#define NET_H

typedef struct{

   unsigned long rx_bytes;
   unsigned long tx_bytes;

}net_stats_t;

typedef struct{

  unsigned long rx_bytes_per_sec;
  unsigned long tx_bytes_per_sec;

}net_rate_t;

int read_net_stats(net_stats_t *stats);

int calculate_net_rate(const net_stats_t *prev,const net_stats_t *curr, int interval_sec, net_rate_t *rate);

#endif
