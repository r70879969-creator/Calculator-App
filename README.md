# Calculator-App
This repository contains a 4-function digital calculator (+, -, *, /) built using a **PIC16F877A microcontroller** and simulated in Proteus. 

## Included Files
* **calculator_main.c:** The C source code written and compiled using MikroC PRO for PIC.
* **PIC16F877A_Calculator_Report.pdf:** A comprehensive project report detailing the hardware architecture, push-button matrix input, and state machine logic.

## Project Demonstration
https://drive.google.com/file/d/1MsMuv1r04FG1SWZ5ML2EGpsCYH6F2gJr/view?usp=drivesdk

## How It Works
The project uses physical push buttons connected to PORTB and PORTC to act as an input matrix. A software debounce routine filters mechanical noise, and the microcontroller dynamically updates a 16x2 LCD with the user's inputs and calculation results.
