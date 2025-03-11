# Understaing the Problem

From wikipedia: 
The problem was designed to illustrate the challenges of avoiding  deadlock, a system state in which no progress is possible. To see that a proper solution to this problem is not obvious, consider a proposal in which each philosopher is instructed to behave as follows:

- think unless the left fork is available; when it is, pick it up;
- think unless the right fork is available; when it is, pick it up;
- when both forks are held, eat for a fixed amount of time;
- put the left fork down;
- put the right fork down;
- repeat from the beginning.

### Solution ?
Dijkstra's solution negates resource holding; the philosophers atomically pick up both forks or wait, never holding exactly one fork outside of a critical section. To accomplish this, Dijkstra's solution uses one mutex, one semaphore per philosopher and one state variable per philosopher. This solution is more complex than the resource hierarchy solution.
____________________________________________________________________________________________________________

### Problem Simplified
1. Startvation: When a philosopher is dies waiting for too long to eat
2. Deadlocks: Deadlocks happen when a philosopher is waiting for his resources (fork1 or fork2)

### Solution 1 ?
Having a monitor:
    - Checking whether a philo has both forks available? if so "Yes" else "Wait"
    - Prioratizing the ones who has not eaten to avoid death by starvation

### Technical definition: 
a problem of operating systems which deals with resource allocation
    - philosophers = processes
    - forks = resources that have to be shared between processes
    - time to eat, sleep and think = rules that we have to obey and cannot be violated

**limited resources that have to shared between processes in a syncronized manner without violating any rules, they are maybe resources that can be used by other processes at a time, the other processes cannot access a resource that has been locked by another process** 

[tutorials to understand](https://www.youtube.com/watch?v=FYUi-u7UWgw&t=113s)
____________________________________________________________________________________________________________

### Plan:
first try to implement the program without the sleeping state, just thinking and eating.
    - start with thinking (duration: time_to_think)
    - switch to eating (current_state: thinking -> eating)
    - if only both forks availbale lock mutexes and eat (duration: time_to_eat) then unlock mutexes to put down the forks back on the table 



# Debug flags
gcc -g -Wall -Wextra -Werror

# With sanitizers
gcc -g -Wall -Wextra -Werror -fsanitize=address
gcc -g -Wall -Wextra -Werror -fsanitize=thread

# Basic memory check
valgrind ./philo

# Detailed memory check
valgrind --leak-check=full --show-leak-kinds=all ./philo

# With thread checking
valgrind --tool=helgrind ./philo
valgrind --tool=drd ./philo

# Combined detailed options
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./philo