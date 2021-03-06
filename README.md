<p align="center">
  <img src="header1.jpg" width="40%" alt="branching" /> <img src="header2.jpg" width="40%" alt="3d"/>
 </p>
    
This project is a fractal generator for common fractals. It is written in C++11 (Qt for GUI), is fully multithreaded (CPU) with a real time progress visualization and implements signal processing concepts for an accurate image reconstruction from samples.  
Mandelbrot, Julia, Budhabrot, Newton and Lyapunov fractals are currently implemented, which includes for them different techniques, e.g. smooth iteration count, addend functions or 3D approximation (most of them are described in the following [thesis](http://jussiharkonen.com/files/on_fractal_coloring_techniques%28lo-res%29.pdf), but this project also takes some inspirations from [FractView](https://github.com/searles/FractviewAndroid), mainly for fold functions). Various rendering algorithms are available each time.
