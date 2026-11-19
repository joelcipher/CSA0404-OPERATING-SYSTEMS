"""Real-Time OS Process Monitoring & Resource Management (CSA0404)
Modules: 1 Process Identification & Status | 2 CPU & Memory Monitoring | 3 Resource Utilization Reporting
"""
import time, psutil
import matplotlib
matplotlib.use("Agg")
import matplotlib.pyplot as plt

def collect_processes():                                   # MODULE 1
    rows = []
    for p in psutil.process_iter(['pid', 'name', 'username', 'status', 'num_threads']):
        try:
            p.cpu_percent(None)
            rows.append(p)
        except (psutil.NoSuchProcess, psutil.AccessDenied):
            pass
    return rows

def snapshot(procs):                                       # MODULE 2
    data = []
    for p in procs:
        try:
            data.append({'pid': p.pid, 'name': p.info['name'] or '?',
                         'status': p.info['status'], 'threads': p.info['num_threads'],
                         'cpu': p.cpu_percent(None), 'mem': p.memory_percent(),
                         'rss': p.memory_info().rss / 2**20})
        except (psutil.NoSuchProcess, psutil.AccessDenied):
            continue
    return data

def sample_system(n=30, dt=0.5):                           # MODULE 2 (system-wide history)
    cpu, mem, procs_n = [], [], []
    for _ in range(n):
        cpu.append(psutil.cpu_percent(interval=dt))
        mem.append(psutil.virtual_memory().percent)
        procs_n.append(len(psutil.pids()))
    return cpu, mem, procs_n

if __name__ == "__main__":
    procs = collect_processes()
    time.sleep(1.0)
    data = snapshot(procs)
    data.sort(key=lambda d: (d['cpu'], d['mem']), reverse=True)
    print(f"{'PID':>7} {'NAME':<22}{'STATE':<10}{'CPU%':>6}{'MEM%':>7}{'RSS(MB)':>9}")
    for d in data[:12]:
        print(f"{d['pid']:>7} {d['name'][:21]:<22}{d['status']:<10}{d['cpu']:>6.1f}{d['mem']:>7.2f}{d['rss']:>9.1f}")
