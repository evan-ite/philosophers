## Philosophers 42 Project


In this project, we are simulating a scenario where philosophers sit around a round table, alternately eating, thinking, or sleeping. The simulation continues until a philosopher dies of starvation. The project explores the use of threads, mutexes, child processes and semaphores.

---

**Rules and Functionality**

- Philosophers sit at a round table with a large bowl of spaghetti in the middle.
- They alternate between eating, thinking, and sleeping.
- Each philosopher needs two forks to eat, one on their left and one on their right.
- When a philosopher finishes eating, they put their forks back and start sleeping. After sleeping, they start     thinking again.
- Philosophers should not starve, and the simulation stops if a philosopher dies.
- No communication occurs between philosophers, and they don't know about each other's status.
- The program takes input arguments to control the simulation parameters, including the number of philosophers,    time to die, time to eat, and time to sleep.

---

**Installation:**

1. Clone the repository:
   ```bash
   git clone git@github.com:evan-ite/philosophers.git
   ```

2. Navigate to the project directory:
   ```bash
   cd philosophers
   ```

3. Compile the project using make:
   ```bash
   make
   ```

---

**Usage:**

Run the game by executing the following command:
```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep
[number_of_times_each_philosopher_must_eat]
```

- `number_of_philosophers`: The number of philosophers and also the number
  of forks.
- `time_to_die` (in milliseconds): If a philosopher didn’t start eating time_to_die
  milliseconds since the beginning of their last meal or the beginning of the simulation, they die.
- `time_to_eat` (in milliseconds): The time it takes for a philosopher to eat.
  During that time, they will need to hold two forks.
- `time_to_sleep` (in milliseconds): The time a philosopher will spend sleeping.
- `number_of_times_each_philosopher_must_eat` (optional argument): If all
  philosophers have eaten at least number_of_times_each_philosopher_must_eat
  times, the simulation stops. If not specified, the simulation stops when a
  philosopher dies.

---

**Acknowledgements**
- Elise van Iterson
