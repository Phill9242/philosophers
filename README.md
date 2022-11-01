# Philosophers

In this project we must solve the famous "Dining philosophers" problem with some aditional challenges

![image](https://user-images.githubusercontent.com/85121830/199342187-1f3924b5-e1ff-41f2-bdcc-b9ee8dc4c0e7.png)


### General Scenario 

In this scenario of the problem, a N number of philosopher is at the dinning table. 

They need to eat at "time_to_die" time. If a philosopher could not eat before this time, he dies.

Each of them needs to eat X times, if X it's not defined, they must eat until one of them die of starvation.

To eat, they need hold 2 forks during the meal. Each meal has "time_to_eat" time to be finish.

After finish the meal they must drop the forks and start to sleep for "time_to_sleep" time.

Once awake, the philosopher start to think until a fork become avaiable to his next meal.

The simulation stops when a philosopher die of hunger or every philosopher eated a number of X meals.


### Augments

The philo program took as argument 4 or 5 numbers:
  - Number of philosophers;
  - time_to_die (in ms)
  - time_to_eat (in ms);
  - time_to_sleep (in ms);
  - number of meals (optional argument).
  
### Rules
  - Each philosopher has 1 fork and need 2 of them to eat;
  - each philosopher **NEED** to be a thread;
  - to prevent that more then one philosopher take a fork at the same time, each fork must be a mutex;
  - it's not allowed to use atomic or global variables;
  - every action should be displayed with the time of the action in the terminal. The following actions are possible
    - philosopher x take a fork;
    - philosopher x start to eat;
    - philosopher x start to sleep;
    - philosopher x start to think;
    - philosopher x died
  - the messages should not be mixed up;
  - Data race and memory leak are forbidden;
  - nothing should be displayed after a philospher's death;
  - the message of the actual death of a philosophers shouldn't take longer than 10 ms to be displayerd in the terminal
