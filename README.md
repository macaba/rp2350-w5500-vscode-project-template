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