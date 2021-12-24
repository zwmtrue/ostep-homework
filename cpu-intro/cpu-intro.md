# CPU Abstraction

## Virtualiztion(Time Sharing): run a program, then stop and switch to another. To provide the illusion of many CPUs

## Mechanisms: Low level machinery that implement a needed piece of functionality

## Policy: Algorithms for making decision within the OS.

## Asbtraction: A process *is* a running program. 

### Machine State of a process: 
1. Address Space(Memory that the process can address)
2. Registers: 
	1. Program Counter(PC)/instruction pointer(IP)
	2. Stack Pointer& Frame Pointer: Manages stack for function parameters.
3. I/O info

## Process API: provides control to a running process

## Process Creation
1. Load program (early OS does this eagerly, moden lazily)
2. Allocate memory for *stack*
	1. In c , stack is used for local var, function parameters and return addresses
	2. Initialize stack w arguments, argc, argv[]
3. Allocate memory for *heap*
	1. In C, used for explicitly requested dynamic data(via malloc()). Need to free().
4. Other init tasks(I/O etc)



