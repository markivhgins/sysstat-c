# SysStat-C (C, procfs-based)

A lightweight Linux system monitoring tool written in **C** that reads directly from the Linux kernel’s **/proc virtual filesystem** to compute real-time system statistics.

This project focuses on understanding **Linux internals**, **kernel–userspace interaction**, and how system monitoring tools work at a low level, without relying on external utilities or libraries.

---

## Features

### CPU Usage
- Reads cumulative CPU statistics from `/proc/stat`
- Uses two snapshots and delta-based calculation
- Computes actual CPU usage percentage

### Memory Usage
- Reads memory information from `/proc/meminfo`
- Uses `MemTotal` and `MemAvailable` (not `MemFree`)
- Provides realistic memory usage percentage

### Network Throughput
- Reads RX and TX byte counters from `/proc/net/dev`
- Uses snapshot-based rate calculation
- Computes RX and TX in KB/s
- Tested on WSL and native Linux

### Design
- Modular structure (separate CPU, memory, and network modules)
- Clear separation of parsing, computation, and output
- No global state
- No external dependencies

---

## Why procfs?

`/proc` is a virtual filesystem provided by the Linux kernel that exposes real-time system information.

This project intentionally uses `/proc` directly in order to:
- Learn how system monitoring tools work internally
- Interact directly with kernel-provided counters
- Build rate-based metrics from cumulative values
- Avoid abstraction layers and hidden logic

---

## Project Structure

# Linux System Monitor (C, procfs-based)

A lightweight Linux system monitoring tool written in **C** that reads directly from the Linux kernel’s **/proc virtual filesystem** to compute real-time system statistics.

This project focuses on understanding **Linux internals**, **kernel–userspace interaction**, and how system monitoring tools work at a low level, without relying on external utilities or libraries.

---

## Features

### CPU Usage
- Reads cumulative CPU statistics from `/proc/stat`
- Uses two snapshots and delta-based calculation
- Computes actual CPU usage percentage

### Memory Usage
- Reads memory information from `/proc/meminfo`
- Uses `MemTotal` and `MemAvailable` (not `MemFree`)
- Provides realistic memory usage percentage

### Network Throughput
- Reads RX and TX byte counters from `/proc/net/dev`
- Uses snapshot-based rate calculation
- Computes RX and TX in KB/s
- Tested on WSL and native Linux

### Design
- Modular structure (separate CPU, memory, and network modules)
- Clear separation of parsing, computation, and output
- No global state
- No external dependencies

---

## Why procfs?

`/proc` is a virtual filesystem provided by the Linux kernel that exposes real-time system information.

This project intentionally uses `/proc` directly in order to:
- Learn how system monitoring tools work internally
- Interact directly with kernel-provided counters
- Build rate-based metrics from cumulative values
- Avoid abstraction layers and hidden logic

---

## Project Structure

project-root/
├── include/
│ ├── cpu.h
│ ├── mem.h
│ └── net.h
├── src/
│ ├── main.c
│ ├── cpu.c
│ ├── mem.c
│ └── net.c
├── README.md
└── LICENSE


---

## How It Works

### CPU Usage
- Reads cumulative CPU counters from `/proc/stat`
- Takes two readings separated by a time interval
- Calculates usage using active vs idle time deltas

### Memory Usage
- Reads `/proc/meminfo`
- Extracts `MemTotal` and `MemAvailable`
- Calculates used memory as `(total - available)`

### Network Throughput
- Reads cumulative RX and TX byte counters from `/proc/net/dev`
- Takes two snapshots separated by time
- Calculates throughput using byte deltas per second

---

## Build and Run

### Compile
```bash
gcc src/main.c src/cpu.c src/mem.c src/net.c -o monitor
```

### Run

```bash
./monitor
```

### Generating Network Traffic (for testing)
```bash
ping google.com
```

### Sample output
```bash
CPU Usage    : 12.45%
Memory Usage : 63.21%
Network RX   : 256.34 KB/s
Network TX   : 48.12 KB/s
```

