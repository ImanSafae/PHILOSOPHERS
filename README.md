# PHILOSOPHERS

This program is the school 42 **philosophers** project.

Its goal is to simulate a dinner between *n* philosophers. 
Each philosopher has a fork and **requires two forks to eat** from the spaghetti plate at the center of the table.

Once a philosopher is done eating, they proceed to sleep, then think, then repeat.
They take a given amount of time to eat and sleep, and can only go without eating a certain amount of time before dying.

The program can take an additional argument which is the amount of times each philosopher must eat before the simulation ends.
If that argument is not specified, the philosophers will repeat the cycle until one of them dies.

The program must allow the simulation to last as long as possible without a philosopher dying.

In the **regular part** of this project, each philosopher is represented by a **thread**, and forks by **mutexes**.
In the **bonus part** of this project, each philosophers is represented by a **process**, and all forks by a **semaphore**.


This program allowed me to validate the Philosophers project with a score of **125/100**, with the **bonus part included**.
