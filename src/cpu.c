#include <stdio.h>
#include "../include/cpu.h"

int read_cpu_stats(cpu_stats_t *stats) {

    FILE *fp = fopen("/proc/stat", "r");
 
   if (fp == NULL) {

        perror("Failed to open /proc/stat");
        return -1;
    }

    char line[256];

    if (fgets(line,sizeof(line),fp) == NULL) {

        fclose(fp);
        return -1;
    }

    fclose(fp);

    int ret = sscanf(line, "cpu %lu %lu %lu %lu %lu %lu %lu",
        &stats->user,
        &stats->nice,
        &stats->system,
        &stats->idle,
        &stats->iowait,
        &stats->irq,
        &stats->softirq
    );

    if (ret != 7) {

        fprintf(stderr, "Failed to parse CPU stats\n");
        return -1;
    }

    return 0;
}

double calculate_cpu_usage(const cpu_stats_t *prev,
                           const cpu_stats_t *curr) {
    unsigned long prev_idle = prev->idle + prev->iowait;
    unsigned long curr_idle = curr->idle + curr->iowait;

    unsigned long prev_total =
        prev->user + prev->nice + prev->system +
        prev->idle + prev->iowait + prev->irq + prev->softirq;

    unsigned long curr_total =
        curr->user + curr->nice + curr->system +
        curr->idle + curr->iowait + curr->irq + curr->softirq;

    unsigned long total_delta = curr_total - prev_total;
    unsigned long idle_delta  = curr_idle - prev_idle;

    if (total_delta == 0)
        return 0.0;

    return (1.0 - (double)idle_delta / total_delta) * 100.0;
}
