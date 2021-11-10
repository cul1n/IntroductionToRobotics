# Introduction To Robotics 2021 @ FMI UNIBUC.
Making cool robots, [hopefully](https://www.youtube.com/watch?v=sa9MpLXuLs0)?

Introduction to Robotics laboratory homeworks, taken in the 3rd year at the Faculty of Mathematics and Computer Science, University of Bucharest. Each homework includes requirements, implementation details, code and image files.

# Homeworks
### Homework #0 :
Installing Arduino IDE and creating a repository for this course.

### Homework #1 :

Task Requirements: Use a separate potentiometer in controlling each of the color of the RGB LED. The control must be done with digital electronics.

Componenets used: RGB LED, 3 potentiometers, 3 resistors (330 ohm) and wires.

Setup: ![Setup 1](https://github.com/cul1n/IntroductionToRobotics/blob/main/Setups/Homework1.jpeg)

Video: https://youtu.be/Es6KPtZ223A

### Homework #2 :

Task Requirements: Building the traffic lights for a crosswalk. You will use 2 Leds to represent the traffic lights for people (red and green) and 3 LEDs to represent the traffic lights for cars (red, yellow and green).

The system has the following states:

1. State 1 (default, reinstated after state 4 ends): green light for cars, red light for people, no sounds. Duration: indefinite,  changed by pressing the button.

2. State 2 (initiated by counting down 10 seconds after a button press): the light should be yellow for cars, red for people and no sounds. Duration: 3 seconds.

3. State 3 (iniated after state 2 ends): red for cars, green for people anda beeping sound from the buzzer at a constant interval.  Duration: 10 seconds.

4. State 4 (initiated after state 3 ends): red for cars, blinking green for people and a beeping sound from the buzzer, at a constant interval, faster than the beeping in state 3. This state should last 5 seconds.

Components used: 5 LEDs, 1 button, 1 buzzer, 6 resistors (5 x 330 ohm and 1 x 100 ohm) and wires.

Setup: ![Setup 2](https://github.com/cul1n/IntroductionToRobotics/blob/main/Setups/Homework2.jpeg)

Video: https://youtu.be/JCdbuBRL7vs

### Homework #3 :

Task Requirements: Build an EMF detector (aka a ghost detector). The EMF detector should print the value on the 7-segment display and should make a sound based on the intensity.

Components used: 7-segment display, 1 buzzer, 7 resistors (1 x 100 ohm, 2 x 1k ohm , 4 x 1M ohm) and wires.

Setup: ![Setup 3](https://github.com/cul1n/IntroductionToRobotics/blob/main/Setups/Homework3.jpeg)

Video: https://youtu.be/nn8UQ7oQ1_4
