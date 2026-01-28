#include <stdio.h>
#include <string.h>
#include "../include/net.h"

int read_net_stats(net_stats_t *stats){

   FILE * fp=fopen("/proc/net/dev", "r");
   if(fp==NULL){
    perror("Failed to open");
     return -1;
}


   char line[256];
   stats->rx_bytes=0;
   stats->tx_bytes=0;

  fgets(line, sizeof(line), fp);
  fgets(line, sizeof(line), fp);

  while(fgets(line, sizeof(line), fp)){
    
      if(strncmp(line, "  eth0:", sizeof("  eth0")-1)==0){
         sscanf(line, "%*[^:]: %lu %*u %*u %*u %*u %*u %*u %*u %lu", 
         &stats->rx_bytes,
         &stats->tx_bytes);
         break;
}        
} 
       fclose(fp);
    
    if(stats->rx_bytes==0&&stats->tx_bytes==0){
        fprintf(stderr, "Failed to read");
        return -1;
}

       return 0;

}


int calculate_net_rate(const net_stats_t *prev, const net_stats_t *curr, int interval_sec, net_rate_t *rate){

    if(interval_sec<=0){
         return -1;
}

     unsigned long rx_delta = curr->rx_bytes - prev->rx_bytes;
     unsigned long tx_delta = curr->tx_bytes - prev->tx_bytes;

     rate->rx_bytes_per_sec= (double)rx_delta/interval_sec;
     rate->tx_bytes_per_sec= (double)tx_delta/interval_sec;

     




    return 0;
}
