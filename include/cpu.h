#ifndef CPU_H
#define CPU_H

typedef struct {
    unsigned long user;
    unsigned long nice;
    unsigned long system;
    unsigned long idle;
    unsigned long iowait;
    unsigned long irq;
    unsigned long softirq;
} cpu_stats_t;


int read_cpu_stats(cpu_stats_t *stats);


double calculate_cpu_usage(const cpu_stats_t *prev,
                           const cpu_stats_t *curr);

#endif
