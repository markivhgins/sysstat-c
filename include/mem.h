#ifndef MEM_H
#define MEM_H

typedef struct{

      unsigned long total_kb;
      unsigned long available_kb;

}mem_stats_t;

int read_mem_stats(mem_stats_t *stats);

double calculate_mem_usage(const mem_stats_t *stats);

#endif
