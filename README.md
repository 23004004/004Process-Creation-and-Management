# Lab004 – Process Creation and Management  

This lab studies the creation and management of processes in operating systems.
Windows is used as the operating system for this lab.

A process is created automatically when we run a program. That is, every time we run an `.exe` file, the operating system creates a process that contains:

- Its own memory space
- A unique identifier (PID)
- Resources allocated by the system
- One or more threads of execution

In addition, a process can create threads or child processes.


## The process creation steps

The parent process is created when our program is executed.
In Windows, to create a child process we use:

- `CreateProcessA()`

    Create a new process from the one that was running.
    Allocate virtual memory to the new process.
    Create its main thread.
    Return information about the created process.

Each process has its own virtual memory space, so they do not share memory directly.

## How synchronization works

When a parent process creates a child, both run concurrently.
If the parent process needs to wait for the child to finish executing, synchronization is used. We see this in task 2. In Windows, this is done with:

- `WaitForSingleObject()`
    This function blocks the execution of the parent process until the child process terminates.
    
    Synchronization is important to ensure the correct order of execution and to release resources correctly.


## How IPC mechanisms function

Processes do not share memory by default. Each process has its own virtual memory space.
To communicate, they must use Inter-Process Communication (IPC) mechanisms.
In this lab, they were implemented in two different ways:

- Pipes `CreatePipe()`:

    - It works as follows:
        The parent writes to one end of the pipe.
        The child reads from the other end.
        The data passes through a buffer in the kernel.

        We use this in task03.


- Shared Memory `CreateFileMappingA()` `MapViewOfFile()`:

    - It works as follows:
        A shared memory region is created in the kernel.
        Both processes map that region into their virtual space.
        The data is not copied: both access the same physical memory.

        We use this in task05.



## Tasks
| Task | Description |
|------|------------|
| [Task 01](./Task01/) | Creating a New Process |
| [Task 02](./Task02/) | Synchronizing Parent and Child Process |
| [Task 03](./Task03/) | Inter-Process Communication Using Pipes |
| [Task 04](./Task04/) | Creating Multiple Child Processes |
| [Task 05](./Task05/) | Shared Memory (Advanced Task) |



### References:

1. https://learn.microsoft.com/es-mx/windows/win32/api/_processthreadsapi/

2. https://learn.microsoft.com/es-es/windows/win32/api/_base/

3. https://learn.microsoft.com/es-es/windows/win32/fileio/file-systems

4. https://learn.microsoft.com/es-es/windows/win32/procthread/processes-and-threads