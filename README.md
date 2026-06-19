# rp2350-w5500-vscode-project-template

This is a Raspberry Pi Pico project template for running under VS Code with full debugging (using Picoprobe) without any CLI usage during normal development.

This adds support for the W5500 ethernet offload IC. The development board is W5500-EVB-Pico2.

## Getting started

- Install the "Raspberry Pi Pico" VS Code extension

- Flash the pico-probe with up-to-date firmware  
(https://github.com/raspberrypi/debugprobe/releases/tag/debugprobe-v2.0.1)

- Copy the files from the template directory into a new project directory

- Open the `CMakeLists.txt` file and edit all instances of the template name to the desired project name  
e.g.  
`project(template C CXX ASM)`  
to  
`project(project-name C CXX ASM)`  

- Open the project folder in VS Code

## Notes

* To run a function from RAM:  
`__not_in_flash_func(function-name_here)`

* Types of binary that can be generated with a CMakeLists.txt entry:  

   `pico_set_binary_type(project-name default)`  
   Store & run from flash. The default mode.   

   `pico_set_binary_type(project-name no_flash)`  
   Run from RAM and allow SWD debugging. No flash IC required. Firmware must be loaded on every reboot.   

   `pico_set_binary_type(project-name copy_to_ram)`  
   Store in flash, then copy to RAM before executing.     

* Disable optimisation to improve SWD debugging experience, place this at the top of main.c:   
`#pragma GCC optimize ("O0")`
