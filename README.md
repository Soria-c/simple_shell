# Title
Simple Shell Project.

* [Table of Contents](#table-of-contents)
    * [Description](#description)
    * [Objectives](#objectives)
    * [Output](#output)
    * [Allowed Functions](#allowed-functions)
    * [Installation](#installation)
    * [Complilation](#compilation)
    * [Authors](#authors)
    * [License](#license)
### Description
Write a simple UNIX command interpreter.

### Objectives
* Understand the following concepts:
    * Who designed and implemented the original Unix operating system
    * Who wrote the first version of the UNIX shell
    * Who invented the B programming language (the direct predecessor to the C programming language)
    * Who is Ken Thompson
    * How does a shell work
    * What is a pid and a ppid
    * How to manipulate the environment of the current process
    * What is the difference between a function and a system call
    * How to create processes
    * What are the three prototypes of main
    * How does the shell use the PATH to find the programs
    * How to execute another program with the execve system call
    * How to suspend the execution of a process until one of its children terminates
    * What is EOF / “end-of-file”?

### Output
<li>Unless specified otherwise, your program <strong>must have the exact same output</strong> as <code>sh</code> (<code>/bin/sh</code>) as well as the exact same error output.</li>
<li>The only difference is when you print an error, the name of the program must be equivalent to your <code>argv[0]</code> (See below)</li>
</ul>

<p>Example of error with <code>sh</code>:</p>

<pre><code>$ echo &quot;qwerty&quot; | /bin/sh
/bin/sh: 1: qwerty: not found
$ echo &quot;qwerty&quot; | /bin/../bin/sh
/bin/../bin/sh: 1: qwerty: not found
$
</code></pre>

<p>Same error with your program <code>hsh</code>:</p>

<pre><code>$ echo &quot;qwerty&quot; | ./hsh
./hsh: 1: qwerty: not found
$ echo &quot;qwerty&quot; | ./././hsh
./././hsh: 1: qwerty: not found
$

</code></pre>

### Allowed functions ###
* `access (man 2 access)`
* `chdir (man 2 chdir)</li>`
* `close (man 2 close)`
* `closedir (man 3 closedir)`
* `execve (man 2 execve)`
* `exit (man 3 exit)`
* `fork (man 2 fork)`
* `free (man 3 free)`
* `stat (__xstat) that(man 2 stat)`
* `lstat (__lxstat) (man 2 lstat)`
* `fstat (__fxstat) (man 2 fstat)`
* `getcwd (man 3 getcwd)`
* `getline (man 3 getline)`
* `kill (man 2 kill)`
* `malloc (man 3 malloc)`
* `open (man 2 open)`
* `opendir (man 3 opendir)`
* `perror (man 3 perror)`
* `read (man 2 read)`
* `readdir (man 3 readdir)`
* `signal (man 2 signal)`
* `strtok (man 3 strtok)`
* `wait (man 2 wait)`
* `waitpid (man 2 waitpid)`
* `wait3 (man 2 wait3)`
* `wait4 (man 2 wait4)`
* `write (man 2 write)`
* `_exit (man 2 _exit)`
* `isatty (man 3 isatty)`
* `fflush (man 3 fflush)

### Installation
Clone  this repository in your local machine

```bash
https://github.com/Soria-c/simple_shell.git
```
### Compilation

User gcc, with the command

```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
```
### Authors
Carlos Soria [GitHub](https://github.com/Soria-c/simple_shell)

Juan Carlos Garay [GitHub](https://github.com/UNICA-FIME)

### License
Simple_shell is open source.
