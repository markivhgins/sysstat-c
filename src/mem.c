#include <stdio.h>
#include <string.h>
#include "../include/mem.h"

int read_mem_stats(mem_stats_t *stats){

FILE * fp=fopen("/proc/meminfo", "r");

if(fp==NULL){
   perror("Failed to open file.");
   return -1;
}

char line[256];

stats->total_kb=0;
stats->available_kb=0;

while(fgets(line, sizeof(line), fp)!=NULL){
     
      if(strncmp(line,"MemTotal:", sizeof("MemTotal:")-1)==0){
           int ret = sscanf(line, "%*[^0-9]%lu", &stats->total_kb);
    
}

     else if(strncmp(line, "MemAvailable:", sizeof("MemAvailable:")-1)==0){
           int ret = sscanf(line, "%*[^0-9]%lu", &stats->available_kb);            
}

    if(stats->total_kb!=0&&stats->available_kb!=0){
        break;
}
}

     fclose(fp);

     if(stats->total_kb==0||stats->available_kb==0){
           fprintf(stderr, "Failed to parse.");
           return -1;

}
   return 0;
}
double calculate_mem_usage(const mem_stats_t *stats){

       unsigned long used_kb = stats->total_kb - stats->available_kb;


       return ((double)used_kb/stats->total_kb)*100;

}




