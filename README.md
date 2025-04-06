# Table of contents:

[1. Introduction](#pipex)

[2. pipe(), Interprocess Communication (IPC) and File Descriptors](#my-projects-code-explained)

[3. Fork() and UNIX Processes](#fork)

[4. Parsing the Commands](#parsing-the-arguments-in-pipex)

[5. Managing File Descriptors](#managing-fds)

[6. Executing Commands](#executing-the-commands)

[7. Using wait() and waitpid()](#using-wait-and-waitpid)

[8. Conclusion](#conclusion)

[9. Resources](#resources)

# Pipex

Welcome to Pipex! This project is part of the Rank 2 of the Common Core curriculum at 42. The aim is to get a better understand of UNIX processes in C and create a program that replicates the behavior of a pipe ( | ) in Shell. So if you give this input to your program: `./pipex infile “cmd1” “cmd2” outfile` it needs to have the same behavior as: `< infile “cmd1” “cmd2” outfile` in Shell.

In this article, I will start by explaining some key concepts (processes, file descriptors, pipes, etc) and the authorized functions for this project. After that, we can dive to the pseudo-code to understand how we can structure our code to build this program correctly!

# My project’s code, explained

I start my `main()` by initializing a list. I’ve decided to keep all the data I need inside a node. This way, if I need to exit the function early, I can free all allocated memory "together" more easily—making it less likely to cause memory leaks!

After initializing the list, I call the `pipe()` function. This is a system call in C that creates a unidirectional data channel used for **interprocess communication (IPC**). In simple terms, it allows one process to send data to another.

```c
int pipe(int fd[2]);
```

- `fd[0]:` the **read end** of the pipe.
- `fd[1]`: the **write end** of the pipe.
- returns `0` on **success**, and `-1` on **failure**.

### About Interprocess Communication (IPC)

IPC refers to the mechanisms that allow **processes to exchange data and signals** with one another. For example, if one process is generating data and another process needs that data to proceed (e.g., for filtering or further processing), they can't just "look" into each other’s memory—each process has its own isolated memory space. So they need IPC.

There are several IPC methods (like message queues, shared memory, sockets), but in this project, we’re using **pipes** (like the `|` operator in the shell).

### About File Descriptors (fd)

A file descriptor is a non-negative integer that the OS uses to keep track of open files and I/O resources for a process. When you open a file, a pipe, or a socket (another IPC method), the OS returns an integer that represents that open resource. So it's not just for regular files on disk—file descriptors apply to anything that can be read from or written to. With a file descriptor, the OS knows where the resource is and what you want to do with it (read, write, etc.).

There are three standard file descriptors you’ve likely already used:

| ame | File Descriptor | Purpose |
| --- | --- | --- |
| `stdin` | 0 | Standard input |
| `stdout` | 1 | Standard output |
| `stderr` | 2 | Standard error output |

So now that we understand how pipes and file descriptors work together: the pipe created by `pipe()` uses file descriptors to read and write data between processes.

If we call our program like this:

```c
./pipex infile "cmd1" "cmd2" outfile
```

Which is equivalent to:

```c
< infile cmd1 | cmd2 > outfile

```

Here’s what happens:

- `cmd1` takes input from `infile`
- The output of `cmd1` is written to the **write end of the pipe**
- `cmd2` reads from the **read end of the pipe**
- The output of `cmd2` is written to `outfile`

So the data flows like this:

```c
[infile] → cmd1 → pipe → cmd2 → [outfile]
```

After calling pipe and handling errors properly , it’s time to call the `fork()` function.

### Fork()

```c
pid_t fork(void);
```

When you call `fork()`, the operating system creates a child process that’s an almost exact copy of the parent process: same code, same memory layout, same open file descriptors, same environment variables. But after the fork, **the two processes run independently and simultaneously**.

But before diving deeper into `fork()`, let’s first understand what a **process** really is.

### About UNIX Processes in C

At its core, a process is a program in execution. A program is just code - like your compiled binary. A process is that code actually running on your machine. So when we run:

```c
./pipex infile "ls" "wc -l" outfile
```

You are creating at leat 3 processes: one for the `./pipex` program, one for `ls`, and one for `wc -l`. Each of these is its own independent process, with its own memory, environment, and state.

Each process has its own:

| Component | What It Means |
| --- | --- |
| **PID** | Process ID—unique number identifying the process |
| **Code** | The instructions it's executing |
| **Heap** | Dynamically allocated memory (from `malloc`, etc.) |
| **Stack** | Keeps track of function calls and local variables |
| **File Descriptors** | Pointers to files, pipes, sockets, etc. (important for `pipex`) |
| **Registers/PC** | CPU state and the program counter (what instruction to run next) |
| **Environment** | Env vars like `PATH`, `USER`, etc. |
| **Parent/Child info** | If the process was created using `fork()` |

You can think of a process as a **sandboxed execution environment**: it has everything it needs to do its job, and it doesn’t share memory with other processes by default.

That’s **why IPC (interprocess communication)** is necessary: processes are isolated from each other. They don’t share memory or variables unless you explicitly connect them (e.g., through a pipe). This isolation is also one of the reasons Linux is **secure and stable**—a crashing app won’t bring down the whole system!

A process lifecycle looks like this:

- **Created** — via `fork()` (from a parent process)
- **Executes** — it runs its code
- **Waits** — sometimes waits for child processes to finish
- **Terminates** — when it finishes or crashes
- **Zombie** — if the parent doesn’t `wait()` for it (OS cleans this up later)

This lifecycle is important for managing the processes we’ll create with `fork()`, so keep it in mind!

Back to `fork()`—when your program calls it, the OS creates a **new process** that is a copy of the original one.

- The original is called the **parent process**.
- The new one is called the **child process**.

They are almost identical at first—same code, file descriptors, and environment—but after `fork()` returns, **they run separately** and can take different paths in your code.

Here’s how we tell them apart:

```c
pid_t pid = fork();

if (pid == -1)
{
    // Error during fork
}
else if (pid == 0)
{
    // This is the child process
}
else
{
    // This is the parent process
}
```

Like you can see in the code above, the way that we can tell them apart is by the return value of fork(), which needs to be saved in a `pid_t` variable. This way, you can branch your logic depending on whether you’re in the child or the parent!

**But why do we need different processes for pipex?**

Because in a pipeline, **each command must run in its own process**.

Using `fork()`, we can:

- Spawn **child processes** to run commands like `ls`, `grep`, or `wc`,
- Use the **parent process** to handle setup (e.g., creating pipes and forking more children),
- Run everything **in parallel**, just like the shell would.

So if you want to run:

```c
< infile cmd1 | cmd2 > outfile
```

You're essentially doing:

1. Fork child 1 → redirect input from `infile`, output to pipe → run `cmd1`
2. Fork child 2 → read from pipe, write to `outfile` → run `cmd2`
3. Parent process → creates the pipe, forks children, and waits for them to finish

Okay! Now that we understand how to use `pipe()` and `fork()`, let’s get to the heart of the project: actually executing the commands.

In my project, I structured the logic inside `main()` like this:

```c
//pseudo code:

pipe(fd);
pid_t pid_1 = fork();
if pid_1 == 0
	execute_child_1();
pid_t pid_2 = fork();
if pid_2 == 0
	execute_child_2();
```

The `execute_child_1()` and `execute_child_2()` functions essentially follow the same steps:

- Parse the arguments (files and commands)
- Manage file descriptors (redirecting and closing)
- Execute the commands

Let’s begin with **parsing**.

### Parsing the arguments in pipex

Parsing the arguments is essential if you want your program to behave like a real shell. I took a stricter approach to error handling and output formatting than what the subject explicitly requires—but I believe it’s a great practice, and it was excellent training for my future `minishell` project!

There are multiple ways to approach parsing, and your implementation can vary depending on your design preferences. I’ll describe how I structured mine, and you can adapt what you like to your own style.

I chose to perform argument parsing inside each of the `execute_child_*()` functions. That way, each side of the pipe parses its own command while running **simultaneously**, just like real shell pipelines do.

I split parsing into two main tasks:

1. Parsing the files (`infile` and `outfile`)
2. Parsing the commands (`cmd1` and `cmd2`)

I separated my parsing into parts: first I will parse the file, and then I will parse the commands. 

**Parsing the files:**

Each child process needs to deal with a different file:, the first child (left side of the pipe) handles the `infile` , and the second child (right side) handles the `outfile` . For `infile`, you need to check if the file exist and if it has read permissions. For `outfile`, ou need to check if the program has write permissions and if the file doesn’t exist, create it with the right permissions.

You can use either `access()` or `open()` to check these conditions. I chose to use `open()` because I also needed the file descriptor (FD) for redirection later, and `open()` handles both the check **and** the file opening in one step.

If `open()` returns `-1`, the file could not be opened. This is where proper error handling is critical. Print a meaningful error message (use `perror()` or `strerror(errno)`), free any allocated memory, and exit the process cleanly. Functions like `perror()`, `strerror()`, `exit()`, and the `errno` variable are all **allowed** by the subject—use them!

I personally used ft_putendl_fd() from Libft to write custom messages that behaved exactly like my PC in 42, just because I am a little OCD. That is an option too!

**Parsing the commands**

Now comes one of the most important parts: **command parsing**.

This is necessary not only because we need to check the existent of the command, but also ecause we eventually need to call `execve()` to execute the command, and it requires two things:

1. A **full path** to the command executable (e.g., `/bin/ls`)
2. An **array of arguments** to pass to the program (like `["ls", "-l", NULL]`)

For this,  you can do the following:

1. split the command string by spaces. You can use your libft ft_split() for this.
2. Use envp array to get the PATH environment variable, and split PATH by : to get a list of possible directories. Again, you can use ft_split.
3. For each directory, join “/” (because the path needs to be /bin/, but after split it will be /bin) plus the command name (and it will look like /bin/ls). You can use ft_strjoin from libft for this.
4. use access in each directory and check if the file exists and is executable.
5. if no directory was successful, do the proper error handling, much like in the file parsing: display the correct message onscreen, free everyting and exit the program.

**Some tests you can do and check if  your program is behaving like Shell:**

- [ ]  nonexistent infile
- [ ]  infile without reading permissions
- [ ]  cmd that does not exist
- [ ]  cmd appends that do not exist
- [ ]  sending cmd1 quote empty “”
- [ ]  sending cmd1 quote as whitespace, like a space or tab
- [ ]  outfile that does not exist (it should create!)
- [ ]  infile and cmd1 incorrect
- [ ]  both cmd1 and cmd2 incorrect
- [ ]  infile and cmd2 incorrect

make those tests both in shell and in your pipex and check if they behave the same!

### Managing FDs

Now that we know how `fork()` works and that it creates a copy of the parent process, an important question is: **what happens to the file descriptors?** Since they’re duplicated in the child process, we need to learn how to manage them properly.

Once the files and commands are parsed, the next step is to set up the input and output streams properly for each child process. this is where dup2() and close() come in.

**Process in the first child:**

The first child process is responsible for reading from the infile, and writing into the pipe.

To be able to read from the infile, we need to redirect the infile’s fd to the standard input (STDIN_FILENO). For that, we can use the `dup2()` function:

```c
#include <unistd.h>

int dup2(int oldfd, int newfd);

dup2(infile_fd, STDIN_FILENO);
```

Now, STDIN will read from the infile instad from the keyboard.

OBS.: how `dup2()` works:

- `dup2()` duplicates a file descriptor: it makes `newfd` refer to the **same underlying resource** (file, pipe, etc.) as `oldfd`.
- If `newfd` is already open, it **closes it** automatically.
- Then it makes `newfd` point to the same file description (i.e., the underlying open file) as `oldfd`.
- Now both `oldfd` and `newfd` refer to the same open file / pipe / socket
- The return value is `newfd` on success, or `-1` on error

Since infile_fd and stdin_fileno are pointing to the same file, we dont need the original file descriptor anymore - so we close it with close() function.

```c
close(infile_fd);
```

This process does not read from the pipe, it writes to it. So we also need to close the read end of the pipe. Closing the ends we are not using is important because another process can see that end open and will wait until there is an input. If we close everything properly, the process will know when they should wait for input/output. 

```c
close(fd[0]);
```

Now child process 1 will read the input from the infile. Now we have to redirect the standard output stream, which is STDOUT_FILENO, to the write end of the pipe.

```c
dupe2(fd[1], STDOUT_FILENO);
close(fd[1]);
```

Now, anything the command writes to stdout will actually go into the pipe. We are also done with the original pipe fd - we’ve duplicated, so it can be closed.

Process in the second child:

This child will read from the pipe and write to the outfile. So we just need to redirect the read end of the pipe to stdin, and the stdout to the outfile, and close everything accordingly, just like in child process 1.

```c
dup2(fd[0], STDIN_FILENO);
close(fd[0]);
dup2(outfile_fd, STDOUT_FILENO);
close(outfile);
close(fd[1]);
```

### Executing the commands

Once the **file descriptors** are set up, and the **input/output** is properly redirected for each child process, we move on to the most important part: executing the command. This is where `execve()` comes in!

The `execve()` function is a system call used to **execute a program** within the current process. When a process calls `execve()`, it **replaces its current image** with the image of the new program. This means the process that called `execve()` is now running the new program instead of the original one.

```c
int execve(const char *pathname, char *const argv[], char *const envp[]);
```

- **`pathname`**: The path of the executable file to run (e.g., `/bin/ls`).
- **`argv[]`**: An array of arguments to pass to the program. The first argument is typically the program name (e.g., `argv[0] = "ls"`), and the last element must always be `NULL`.
- **`envp[]`**: An array of environment variables (e.g., `envp = { "PATH=/usr/bin", "USER=user", NULL }`).

Some other important info about this function:

1. **Program Replacement**: When the child process calls `execve()`, it **replaces** the process image with the new program (i.e., the command). The current process no longer exists in its previous state.
2. **Execution of the New Program**: The operating system loads the new executable into the current process, and the code starts running from its entry point (typically `main()`).
3. **No Return**: After `execve()` successfully runs, the process is completely replaced, so it **never returns** to the original program. If the `execve()` call is successful, the command starts executing immediately, and the original program halts.

You might have an idea right now of what you need to pass as an argument to this function, so I will leave it to you! Don’t forget to error handle in case the function fails :) 

### Using wait() and waitpid()

We are almost done with the project. Let’s just go back to our main function. Remember the pseudo code I showed earlier? There is just two things missing:

```c
//pseudo code:

pipe(fd);
pid_t pid_1 = fork();
if pid_1 == 0
	execute_child_1();
pid_t pid_2 = fork();
if pid_2 == 0
	execute_child_2();
close(fd[0]);
close(fd[1]);
waitpid(pid_1, NULL, 0);
waitpid(pid_2, NULL, 0);
```

After forking the child processes, the **parent process** no longer needs the pipe file descriptors (`fd[0]` and `fd[1]`), so they are closed in the **parent** process. It is important to **close unused file descriptors** in the parent process to ensure proper process synchronization. If they’re left open, other processes might try to read or write from them, which could cause unexpected behavior or deadlocks.

The `waitpid()` function is used to **wait for a specific child process to finish** before continuing the execution in the parent. It’s called twice, once for each child process (`pid_1` and `pid_2`).

```c
pid_t waitpid(pid_t pid, int *status, int options);
```

- **`waitpid()`** waits for the process with the process ID `pid` to terminate.
- In this case, you pass `NULL` for `status` because you don’t need to collect the child’s exit status. You also pass `0` for `options` since you don't need any special behavior.

By calling `waitpid()`, the parent ensures that it **waits for both child processes to finish** before it proceeds, which avoid any premature termination of the parent while the children are still running.

If we do not use waitpid() we cause cause a zombie process. 

**About zombie processes**

A **zombie process** (or **defunct process**) is a process that has **terminated**, but still has an entry in the process table. This happens because the **parent process** has not yet read the child's exit status using `wait()` or `waitpid()`.

Let me explain why this happens:

1. **Process Termination:** When a process finishes executing, it exits and releases most of its resources (like memory and open file descriptors). However, the process's entry in the process table is not immediately removed because the parent process still needs to read the **exit status** of the terminated child.
2. **Parent's Role:** The **parent process** is responsible for calling `wait()` or `waitpid()` to retrieve the exit status of the child. Once the parent collects the exit status, the child is completely removed from the process table.
3. **Zombie State:** Until the parent calls `wait()` or `waitpid()`, the terminated child remains in the process table as a **zombie**. The process is "dead" (it has finished executing), but it still takes up an entry in the system's process table.

### Conclusion

And that’s it for pipex! I tried my best to explain it in as much detail as possible, but if you have any doubts, you can also check the resources list I used to for developing my project and writing this readme. Thank you so much for reading and good luck on your 42 journey!

### Resources:

https://reactive.so/post/42-a-comprehensive-guide-to-pipex/

https://medium.com/@omimouni33/pipex-the-42-project-understanding-pipelines-in-c-71984b3f2103

https://csnotes.medium.com/pipex-tutorial-42-project-4469f5dd5901

https://www.cs.tufts.edu/cs/21/notes/processes/processes_c.html

https://www.youtube.com/playlist?list=PLfqABt5AS4FkW5mOn2Tn9ZZLLDwA3kZUY

http://nob.cs.ucdavis.edu/classes/ecs030-2002-02/handouts/unixproc.html

https://web.fe.up.pt/~jmcruz/etc/unix/faq/faq_2.html#SEC14

https://www.cs.cmu.edu/~guna/15-123S11/Lectures/Lecture25.pdf
