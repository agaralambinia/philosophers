# philosophers
Solution for dining philosopher with threads

visualizer
https://nafuka11.github.io/philosophers-visualizer/

**For mandatory part**
- For even philo cnt death time must be >= 2 * max(eat time, sleep time)
- For odd philo cnt death time must be >= 3 * eat time && eat time + sleep time <= death time

**System limits**
- amount of philos (running threads) is limited by OS. (usually about 8000 on MAC, in Linux its defined in /proc/sys/kernel/threads-max, don't try to find it out practically!)
- limit of min time in milliseconds is determened by Processor frecuency. For M2 it's 3.50 GHz that is 3500 operations for microsecond. That means that theoretically I can not set the limit, but it's better to set in for safety reasons.