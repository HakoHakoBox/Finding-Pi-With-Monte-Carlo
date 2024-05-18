# Finding-Pi-With-Monte-Carlo

Monte Carlo can be used to estimate the value of Pi (3.41). In processor 0, we populate two arrays with random numbers. MPI_Scatter is called to send the numbers from each processor. Using the numbers from each array, we generate random pairs and check if x^2 + y^2 <= 1. If this is true then the variable 'count' is incremented. MPI_Reduce then has all the processors return the 'count' variable to 'final_count', which is then used to caculate Pi.
