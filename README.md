# Bikestation

Final Project of my Programation discipline in my college course MEEC at IST


This is my final project for my programation discipline in my college course MEEC at IST Portugal, which I did in pair with a friend.
It is a similarimplementation of the website http://bostonography.com/hubwaymap/ with a textual mode and a graphical mode.

It compiles using gcc with the following command:
gcc *.c -g -I/usr/local/include -Wall -pedantic -std=c99 -L/usr/local/lib -lm -lSDL2 -lSDL2_ttf -lSDL2_image -o bikestation

And it runs with the commands:
./bikestation -g tripdata.csv stationdata.csv (graphical mode)
or
./bikestation -t tripdata.csv stationdata.csv (textual mode)

Grade:
19/20
