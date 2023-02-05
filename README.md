# Multi-Code-ESP
This is code for a task switcher program in ESP32 that allows the user to control the display of a bar graph through two switches. 

## Features
- Display a cool effect on the bar graph continuously through task 1
- Display a pattern `11001100` on the bar graph continuously through task 2
- Control the bar graph display through two switches:
  - Pressing switch 1 starts task 1 and halts task 2
  - Pressing switch 2 starts task 2 and halts task 1

## Usage
- Initialize the bar graph module and switch module
- Continuously monitor the state of the switches and control the display of the bar graph accordingly
- Two tasks are created: task 1 and task 2
- Task handler task is created to monitor and control the display of the bar graph through the two switches
- All tasks are suspended at the start

## Requirements
- ESP32 development board
- SRA Board 
- FreeRTOS
- [sra_board.h](https://github.com/SRA-VJTI/sra-board-component) library
- [freertos/FreeRTOS.h](https://www.freertos.org/FreeRTOS-For-Esp32.html) library

## Contributing
This project welcomes contributions and suggestions. Feel free to open an issue or make a pull request.
