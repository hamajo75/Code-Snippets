# Profiling

## perf
Based on https://dev.to/etcwilde/perf---perfect-profiling-of-cc-on-linux-of

```
sudo perf record ./executable.exe
```
will create `record.data`
```
perf report
```
will show a view like this

```
Samples: 15K of event 'cpu-clock:pppH', Event count (approx.): 3993000000
Overhead  Command         Shared Object      Symbol
  99,81%  executable.exe  executable.exe     [.] fib
   0,13%  executable.exe  [kernel.kallsyms]  [k] 0xffffffffa7f6a0ea
   0,03%  executable.exe  [kernel.kallsyms]  [k] 0xffffffffa8e00073
   0,01%  executable.exe  [kernel.kallsyms]  [k] 0xffffffffa8b70f05
   0,01%  executable.exe  [kernel.kallsyms]  [k] 0xffffffffa7edff2c
   0,01%  executable.exe  [kernel.kallsyms]  [k] 0xffffffffa8149436
```

This tells us we are spending most of the time in the fib function.

Go deeper with the `-g` option.
```
sudo perf record -g ./executable.exe
```
