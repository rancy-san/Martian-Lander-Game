## Martian Lander

### Description

Solve Ordinary differential Equations (ODEs) in real-time for a planetary lander flight simulator. Algorithm The simulation uses Heun’s adaptation of Euler’s method, as explained in lecture notes, to solve the following differential equations that describe the descent of a landing module on Mars under gravity with atmospheric drag and an additional booster term B: dv/dt = g – c*(v + a*(v/vmax)3) – B v = dx/dt The values of the constants are g = 3.7, c = 0.13, a = 8.3, vmax = 46 Solving these equations means calculating the velocity v and position x of the module as time t (seconds) passes after it starts its descent from an initial location 1000 meters above the Martian surface at the instant of being released from the mother ship. It then falls to the surface under the above equations. The meanings of the terms are:

### Algorithm

1.dv/dt in the acceleration of the lander module as it falls to the surface where v (in metres/second)is positive in a downward direction. At the instant of release v is zero and x is 1000 metres andtime t (in seconds) is zero. Time is measured from the computer clock.

2.g is the downward acceleration caused by gravity (which on Mars is only 38% of Earth’s gravity).

3.c*(v + a*(v/vmax)3) is the deceleration caused by atmospheric drag. It is small when the velocityis small and gets large as a power law as the velocity increases. At some high velocity (called theterminal velocity) it balances gravity and acceleration becomes zero..

4.B is the deceleration cause by a burn from the braking rocket on the landing module. This alwaysacts in an upward direction to counter gravity. 

### Use

Compile in Microsoft Visual Studio 2015.
Or run using the executable file.

This rocket can be turned on and off and adjustedfrom the keyboard using the keys W (increases B) and E (decreases B). However, braking usesup fuel at the rate of B units per second and so depletes the fixed reserve of 100 units.
