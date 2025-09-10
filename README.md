# StreamPipes
> A collection of user-space pseudo device files (`/dev/szmelc/*`) that simulate real-time streams for fun, prototyping, automation, and terminal magic.

> This project blurs the line between `/dev/null`-tier trash and cutting-edge terminal wizardry. Built for mad scientists, hackers, and shell sorcerers.

---

## 📁 Streams Overview

### `/dev/szmelc/asciibuffer`
A virtual terminal session recorder that acts as a RAM-backed log of terminal interaction. 

- **Write** → starts capturing with `asciinema` into an in-memory buffer  
- **Read** → dumps the latest cast stream as `.cast` JSON  
- Can be redirected live to web players or replayed instantly  
- Temporary and volatile – dies with the system, just like your sanity

---

### `/dev/szmelc/shortlog`
A minimal terminal command snapshot stream.

- **Write** → appends a short entry (like `whoami`, `ls`, etc.)
- **Read** → shows the last N (configurable) entries
- Optional timestamps, session markers, or user-based prefixes
- Think of it as `.bash_history` but alive and kicking

---

### `/dev/szmelc/syspeek`
A synthetic real-time system status stream.

- **Read** → always returns:
  - Current `uptime`
  - `loadavg`
  - RAM and disk usage (via `free`, `df`, `iostat`)
  - Optional: current net throughput, number of forks, zombie count
- Constantly refreshing snapshot of your system guts

---

### `/dev/szmelc/gpt`
The mad bastard: a virtual AI pipe.

- **Write** → question, task, or prompt
- **Read** → response from local LLM (like `llama.cpp`) or API (e.g. OpenAI)
- Supports conversation history, stateful mode
- Injects a full LLM into your terminal stream... just because we can

---

## 🔧 Tech Stack Ideas

- C or Go backends with FUSE, or `/dev/fd`/`tmpfs` hacks
- Wrapper shell scripts (e.g., `tee`, `tail`, `socat`, `jq`) for quick tests
- Optional daemon to simulate continuous output (e.g., polling system stats or talking to LLM)

---

## 🚀 Use Cases

- Live monitoring dashboards
- LLM-enhanced terminal assistants
- Bizarre prompt logging for pentesting
- Post-apocalyptic hacker aesthetics

---

## 🧪 Example

```sh
# Stream current system info
cat /dev/szmelc/syspeek

# Ask AI for help directly from terminal
echo 'summarize this directory' > /dev/szmelc/gpt
cat /dev/szmelc/gpt

# Record a session and replay
asciinema rec /dev/szmelc/asciibuffer
asciinema play /dev/szmelc/asciibuffer
```

---

## 📦 Future

- `/dev/szmelc/gibberish` → randomly generates ANSI chaos
- `/dev/szmelc/xlog` → real-time colored logs from your services
- `/dev/szmelc/entropy` → absurd junk for `/dev/random` haters
- `/dev/szmelc/waifu` → simulated anime girlfriend (no, really)

---

**Made by Szmelc.INC — for hackers, by hackers.**  
`2025-09-10T02:36:13.896469`  
