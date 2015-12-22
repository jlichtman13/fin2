# Summary
In this program and eventual plot 3 functions are seen representing the calculation of the givin 6 dimensional integral.
The methods used were a Vegas integration which is done using the integral_vegas function from the gnu library, a home made monte carlo
integration which is derived from the two-cubes-integral file provided, and a dipole approximation (more in note).  The Vegas integral
took around 275 seconds to run while the home made took about 25 seconds to run.  The reason the home made one took so much faster was due to
the innacuracy in it as the vegas integral calculates it to a much higher precision.  In order for the home made (monte carlo) integral to reach
the same precision it would have to be running for about 100 times as long which is due to the convergance of the monte-carlo integral.

![alt tag](https://github.com/jlichtman13/fin2/blob/master/finalplot.png)


#Note
The dipole function is lower than it most likely should be and I will contunue to try and fix it for my own curiosity as to why it is not
working and will update it when this happens but yet I am still submitting everything.

#acknowledgements

Big thanks to Hope Whitelock and Daniel Kovner for assisting me.
