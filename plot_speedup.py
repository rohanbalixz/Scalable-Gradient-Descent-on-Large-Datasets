#!/usr/bin/env python3
import os
import matplotlib.pyplot as plt

# Configuration
DATA_FILE = 'scaling_results.txt'
OUTPUT_DIR = 'report'
OUTPUT_FILE = os.path.join(OUTPUT_DIR, 'speedup.png')

# 1) Ensure the output directory exists
os.makedirs(OUTPUT_DIR, exist_ok=True)

# 2) Read the scaling data
threads = []
times = []
with open(DATA_FILE) as f:
    for line in f:
        line = line.strip()
        if not line:
            continue
        # Expect: "Threads=4 Time=12.345"
        t_str, time_str = line.split()
        threads.append(int(t_str.split('=')[1]))
        times.append(float(time_str.split('=')[1]))

# 3) Compute speedup
T1 = times[0]
speedup = [T1 / t for t in times]

# 4) Plot
plt.figure()
plt.plot(threads, speedup, marker='o')
plt.title('Strong Scaling Speedup')
plt.xlabel('Threads')
plt.ylabel('Speedup (T₁/Tₚ)')
plt.xticks(threads)
plt.grid(True)
plt.tight_layout()

# 5) Save the figure
plt.savefig(OUTPUT_FILE)
print(f"Saved speedup plot to {OUTPUT_FILE}")

