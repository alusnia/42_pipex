🚰 Pipex
Pipex is a system programming project at 42 School that delves into the detailed UNIX mechanisms behind file descriptors, process creation, and inter-process communication.

The goal is to replicate the behavior of the shell pipe operator | in C, handling input/output redirection and command execution.

🚀 Features
This project includes both the mandatory functionality and the Bonus extensions.

Standard Piping: Handles the redirection of input and output between two commands.

Multiple Pipes (Bonus): Supports an arbitrary number of commands chained together (e.g., cmd1 | cmd2 | cmd3 ... | cmdN).

Here_doc Support (Bonus): Implements the << redirection with a custom limiter, appending the output to the file.

Error Handling: Robust management of file permissions, invalid commands, and memory leaks.

Path Parsing: Dynamically locates command binaries using the PATH environment variable.

🛠️ Installation
Clone the repository:

    git clone <repository_url>

Compile the program:

    make
💻 Usage
The program is executed from the command line and takes file names and shell commands as arguments.

1. Standard Mode
Replicates the behavior of: < file1 cmd1 | cmd2 > file2

Syntax:

    ./pipex file1 cmd1 cmd2 file2

Example:

    ./pipex input.txt "grep hello" "wc -l" output.txt
    
Shell equivalent: 

    < input.txt grep hello | wc -l > output.txt

2. Multiple Pipes
Replicates the behavior of: < file1 cmd1 | cmd2 | ... | cmdN > file2

You can chain as many commands as you like.

Syntax:

    ./pipex file1 cmd1 cmd2 cmd3 ... cmdN file2
Example:

    ./pipex infile "ls -la" "grep .c" "wc -l" outfile

    
Shell equivalent: 
    
    < infile ls -la | grep .c | wc -l > outfile

3. Here_doc Support
Replicates the behavior of: cmd1 << LIMITER | cmd2 >> file

When the first argument is "here_doc", the program reads from the standard input until the LIMITER is encountered. Note: The output is appended (>>) to the file, not truncated.

Syntax:

    ./pipex here_doc LIMITER cmd1 cmd2 outfile
Example:

    ./pipex here_doc END "cat" "wc -l" out.txt
Shell equivalent:

    grep a << END | wc -l >> out.txt
    line one
    line two a
    END

Workflow
Parsing: The program parses the environment variables to find the absolute paths of the commands.

Piping: A pipe is created for every connection between two commands.

Forking: A child process is forked for every command.

Redirection: inside each child, dup2 connects the input/output to the appropriate pipes or files.

Execution: execve runs the command. The parent process waits for all children to finish.

⚠️ Error Handling
The program is designed to fail gracefully:

Displays custom error messages (e.g., "Command not found", "Permission denied") to standard error.

Properly closes all file descriptors to avoid FD leaks.

Frees all allocated memory before exiting.
