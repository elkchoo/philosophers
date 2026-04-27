*This project has been created as part of the 42 curriculum by echoo.*

## Description

This project creates a program that simulates philosophers eating given the following rules:

• One or more philosophers sit at a round table.
There is a large bowl of spaghetti in the middle of the table.\
• The philosophers take turns eating, thinking, and sleeping.
While they are eating, they are not thinking nor sleeping;
while thinking, they are not eating nor sleeping;
and, of course, while sleeping, they are not eating nor thinking.\
• There are also forks on the table. There are as many forks as philosophers.\
• Since eating spaghetti with just one fork is impractical, a philosopher must pick up
both the fork to their right and the fork to their left before eating.\
• When a philosopher has finished eating, they put their forks back on the table and
start sleeping. Once awake, they start thinking again. The simulation stops when
a philosopher dies of starvation.\
• Every philosopher needs to eat and should never starve.\
• Philosophers do not communicate with each other.\
• Philosophers do not know if another philosopher is about to die.

## Instructions

### Compilation

Move into the philo folder with
```bash
cd philo
```
and the compile with

```bash
make
```
or

```bash
make all
```

### Execution

```bash
./philo (number_of_philosophers) (time_to_die) (time_to_eat) (time_to_sleep) (optional: number_of_times_each_philosopher_must_eat)
```

## Resources

### Documentation & References

Details of the Dining Philosophers problem can be found on Wikipedia: https://en.wikipedia.org/wiki/Dining_philosophers_problem

### AI Usage

AI helped me to understand the pros and cons of many implementation ideas, as well as the limitations of what was possible given the functions I had available. It was also very useful for debugging when I had trouble understanding the behaviour of the functions, and was invaluable for diagnosing many bugs I encountered and understanding bug reports.
