#include <stdio.h>
#include <unistd.h>
#include "../include/cpu.h"
#include "../include/mem.h"
#include "../include/net.h"

int main() {
    cpu_stats_t prev, curr;

    if (read_cpu_stats(&prev) != 0) {
        return 1;
    }

    sleep(5);

    if (read_cpu_stats(&curr) != 0) {
        return 1;
    }

    double cpu_usage = calculate_cpu_usage(&prev, &curr);

    printf("CPU Usage: %.2f%%\n", cpu_usage);


    mem_stats_t mem;

    if(read_mem_stats(&mem)!=0){
       printf("Reading memory stats failed.\n");
       return 1;
    }

    double mem_usage = calculate_mem_usage(&mem);

    printf("Memory Usage: %.2f%%\n", mem_usage);



    net_stats_t net_prev, net_curr;
    net_rate_t net_rate;

   if(read_net_stats(&net_prev)!=0){

    return 1;
   }

   sleep(5);

   if(read_net_stats(&net_curr)!=0){

   return 1;
   }

   if(calculate_net_rate(&net_prev, &net_curr, 5, &net_rate)!=0){

   return 1;
   }
   
   printf("Network RX:%.2f kbps\n", net_rate.rx_bytes_per_sec/1024.0);
   printf("Network TX:%.2f kbps\n", net_rate.tx_bytes_per_sec/1024.0);


    return 0;
}
