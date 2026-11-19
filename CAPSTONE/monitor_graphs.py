"""Matplotlib graphs for the OS Process Monitoring project (CSA0404)
Install :  pip install psutil matplotlib
Live     :  python monitor_graphs.py          (opens a live dashboard)
Save PNG :  python monitor_graphs.py --save   (saves 4 figures, no window)
"""
import sys, time, collections
import psutil
import matplotlib
SAVE = "--save" in sys.argv
if SAVE:
    matplotlib.use("Agg")
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation

HISTORY = 40                                   # samples kept on the graph
cpu_hist = collections.deque(maxlen=HISTORY)
mem_hist = collections.deque(maxlen=HISTORY)
t_hist   = collections.deque(maxlen=HISTORY)
start = time.time()

# prime per-process CPU counters (first call always returns 0.0)
for p in psutil.process_iter():
    try: p.cpu_percent(None)
    except (psutil.NoSuchProcess, psutil.AccessDenied): pass

def read_processes():
    """Return one dict per process: pid, name, state, cpu %, memory %."""
    rows = []
    for p in psutil.process_iter(['pid', 'name', 'status']):
        try:
            rows.append({'pid': p.info['pid'], 'name': p.info['name'] or '?',
                         'status': p.info['status'],
                         'cpu': p.cpu_percent(None), 'mem': p.memory_percent()})
        except (psutil.NoSuchProcess, psutil.AccessDenied):
            continue
    return rows

def draw(ax, rows):
    """Draw all graphs from one set of readings."""
    cpu_hist.append(psutil.cpu_percent())
    mem_hist.append(psutil.virtual_memory().percent)
    t_hist.append(time.time() - start)

    # 1) CPU and memory trend (line graph)
    ax[0].clear()
    ax[0].plot(t_hist, cpu_hist, color='black', lw=2, label='CPU %')
    ax[0].plot(t_hist, mem_hist, color='#777777', lw=2, ls='--', label='Memory %')
    ax[0].set_ylim(0, 105); ax[0].set_xlabel('Time (s)'); ax[0].set_ylabel('Usage (%)')
    ax[0].set_title('System CPU and Memory Usage', fontweight='bold')
    ax[0].grid(color='#cccccc'); ax[0].legend(loc='upper left', frameon=False)

    # 2) Top 5 processes by CPU (horizontal bar)
    top = sorted(rows, key=lambda r: r['cpu'], reverse=True)[:5][::-1]
    ax[1].clear()
    ax[1].barh([f"{r['name'][:12]} ({r['pid']})" for r in top],
               [r['cpu'] for r in top], color='#222222')
    ax[1].set_title('Top 5 Processes by CPU %', fontweight='bold'); ax[1].set_xlabel('CPU %')

    # 3) Top 5 processes by memory (horizontal bar)
    topm = sorted(rows, key=lambda r: r['mem'], reverse=True)[:5][::-1]
    ax[2].clear()
    ax[2].barh([f"{r['name'][:12]} ({r['pid']})" for r in topm],
               [r['mem'] for r in topm], color='#888888')
    ax[2].set_title('Top 5 Processes by Memory %', fontweight='bold'); ax[2].set_xlabel('Memory %')

    # 4) Process state distribution (bar)
    states = collections.Counter(r['status'] for r in rows)
    ax[3].clear()
    ax[3].bar(states.keys(), states.values(), color='#555555', edgecolor='black')
    ax[3].set_title(f'Process States (Active: {len(rows)})', fontweight='bold')
    ax[3].set_ylabel('Number of processes')

def update(_):
    draw(axes, read_processes())
    fig.tight_layout()

fig, axs = plt.subplots(2, 2, figsize=(12, 7))
axes = axs.flatten()
fig.canvas.manager.set_window_title('Real-Time Process Monitor') if not SAVE else None

if SAVE:
    for _ in range(20):                         # collect 20 samples (about 10 s)
        time.sleep(0.5); draw(axes, read_processes())
    fig.tight_layout(); fig.savefig('dashboard.png', dpi=200)
    names = ['trend', 'top_cpu', 'top_mem', 'states']
    for a, nme in zip(axes, names):             # also save each graph separately
        ext = a.get_tightbbox(fig.canvas.get_renderer()).transformed(fig.dpi_scale_trans.inverted())
        fig.savefig(f'{nme}.png', bbox_inches=ext.expanded(1.05, 1.1), dpi=200)
    print('Saved: dashboard.png, trend.png, top_cpu.png, top_mem.png, states.png')
else:
    ani = FuncAnimation(fig, update, interval=1000, cache_frame_data=False)   # refresh every 1 s
    plt.show()
