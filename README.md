# Project 2: Subdirectories and Moving Files
> Note: I decided to build upon my Project 1 files for this.
## TODO List:
1. [ ] `answers.txt` contains the expected content:
    1. [x] Descriptions of the following standard library routines: `fopen`, `fclose`, `fread`, `fwrite`, `fstat`, `fscanf`, `fprintf`, and `sprintf`.
    2. [ ] List of 5 *other* standard library routines and 5 system calls used by Project 2.
    3. [ ] In `simdisk.cpp`, why do we need to verify `statBuf.st_size == nSectorsPerDisk * nBytesPerSector`?
    4. [ ] Read [Notes on Programming in C](https://avida.cs.wright.edu/courses/CEG4350/Notes/Rob%20Pike%20Notes%20on%20Programming%20in%20C.html) by Rob Pike.  For five identifiers used in the given source code, either:
        1. suggest better alternative names and defend why they are better, or
        2. explain why I am comfortable with the names as they are.
    5. [ ] Write the pre-post conditions for:
        - `uint FileVolume::read33file(byte *fs33leaf, byte *unixFilePath)`
        - `uint FileVolume::write33file(byte *unixFilePath, byte *fs33leaf)`
2. [ ] Learn to use GDB
    1. [ ] Start `script` and `make` P2 as given, running `P2` through `GDB`
    2. [ ] Set a breakpoint immediately after `setArgsGiven(buf, arg, types, nMax);`.  Examine the values of `buf`, `arg`, `types`, and `nMax`.
    3. [ ] Use our shell to make a file volume.  Trace the execution from the above breakpoint by single stepping until after `simDisk` is initialized by `mkSimDisk()`.
    4. [ ] Set a breakpoint at the bottom of the `SimDisk` constructor.  Examine the value of `diskName`.
    5. [ ] Type in a `wrdisk` request, followed by a `rddisk` request.  Verify that the results match.
    6. [ ] End the script, saving it as `gdbSession.txt`.
3. [ ] Additions and Improvements
    - The following commands are already functional:
        - `fs33% mkfs disknm`: creates an empty file volume on the simulated disk named `disknm.dsk` (which must be defined in `diskparams.dat`).  
            - The `maxfnm`, number of inodes, and the inode height are specified in the provided `diskparams.dat` file, which contains multiple possible `disknm` definitions.  
            - The constructed disk becomes the current disk of the shell.  The height includes the `fileSize` field.
            - Files can be at most `maxfnm` characters long.  Valid characters are a-z, A-Z, 0-9, hyphen and period.  All other characters are illegal (including spaces, slashes, etc).
        - `fs33% cp @P0/test0.cpp myfile.txt`: copies `P0/test0.cpp` from the host system's (specified by `@`) current working directory to the current directory inside our shell with the name specified, and prints to `stdout` the inode number of the new file.  If `myfile.txt` already exists, the new content silently replaces it.
        - `fs33% cp myfile.txt @P0/test1.cpp`: copies `myfile.txt` from the current file volume to `P0/test1.cpp` of the host file system, then prints to `stdout` the inode number of `myfile.txt`.  If `P0/test1.cpp` already exists, it is silently replaced.
        - `fs33% cp myfile.txt file2.txt`: copies `myfile.txt` of the current file volume to `file2.txt`, then prints to `stdout` the inode of `file2.txt`.  If `file2.txt` already exists, the new content replaces it.
        - `fs33% ls`: prints a listing of all files in the root directory (as per Linux's `ls -lisa`).
        - `fs33% rm myfile.txt`: remove the file named `myfile.txt` from the root directory and prints to `stdout` the inode number that file had.  If the file does nto exist, be quiet and print `0`.
        - `fs33% inode 4`: print the contents of inode numbered 4, if it exists.
    - Note: there is a second `diskparams.dat` file to test `stdTestScriptP2.txt` with.
    1. [ ] Much of the code provided by this project is functional but not robust.  Improve the code so that it doesn't crash with invalid inputs.  Describe these changes in `improvements.txt`.  Later project phases will replace `TODO` elements of the code with working code.
    2. [ ] Nested Directories: Project 2 involves working with a single volume at a time, no mounting involved.  Implement hierarchical directories, namely the `mkdir`, `rmdir` and `chdir` commands.  Note that this means building from the root directory.
    3. [ ] Linux's `mv` command takes two arguments, which either:
        1. if the last argument is an existing directory, move the specified files or directories in the previous arguments from their current location to this directory, or
        2. renames the first argument or directory into the second argument.
    4. [ ] Write a robust `testscript.txt` to verify the new code works as intended.  This includes (but not limited to):
        - `fs33% mkdir dnm`: Creates a new empty directory in the current directory, and prints its inode number.  If a file or directory named `dnm` already exists in the current directory, create a "nothing new" and return `0`.  The inode needs to have a field that indicates whether or not it's a directory.  Assume that `dnm` does not include slashes.
        - `fs33% rmdir dnm`: If the directory `dnm` is empty, delete it.  If the directory is not empty, make no changes.  In either case, print the number of directory entries in `dnm`, excluding `.` and `..`.
        - `fs33% mv da db`: `da` is either a file or directory.  If `da` does not exist, return `0` and change nothing.  If `db` does not exist in the current directory, `da` is renamed to `db`.  If `db` is an existing directory in the current directory, `da` is moved (along with its contents) to `db` as a subdirectory.  If `db` is an existing file, return `0`.  Carefully consider if `da` and `db` can be pathnames.  Hint: earlier instructions explicitly state to ignore slashes.
        - `fs33% chdir pnm`: Change the current directory to `pnm`.  If it begins with a slash, it's an absolute path name.  If `pnm` does not begin with a slash, it's relative to the current working directory.  In either case, print the absolute path name of the new current directory.  The current directory is initially established as the root directory of the newly created/found file volume.
        - `fs33% pwd`: prints the full path name of the current directory.
        - `fs33% ls pnm`: prints the contents of the directory `pnm` in the "long" format, same as `ls -l`.
        - `fs33% inode myfile.txt `: overload of the above command.  First it discovers the i-number of `myfile.txt` located in the current directory, then invokes the `inode` command above.  NOTE: I believe there should be a `inode number` command listed above, which this refers to (and not `ls`).

# Grading Checklist
- [ ] `ReadMe.txt` exists with the content described in [Project Expectations](https://avida.cs.wright.edu/courses/CEG4350/Projects/4350projects.html) (5 pts)
- [ ] `testscript.txt` is designed so that all functionality is demonstrated, including robustness (5 pts)
- [ ] Program successfully navigates `testscript.txt` (5 pts)
- [ ] `answers.txt` (5 pts)
- [ ] `gdbSession.txt` (10 pts)
- [ ] Improvements are correctly implemented and robust (5 pts)
- [ ] `mkdir dnm` (10 pts)
- [ ] `chdir pnm` (10 pts)
- [ ] `rmdir dnm` (10 pts)
- [ ] `ls dnm` (10 pts)
- [ ] `mv da db` (where `db` may not exist, but if it does, it's a file) (5 pts)
- [ ] `mv da db` (where `db` exists, and is a directory; `da` may or may not exist inside `db`) (5 pts)
- [ ] `mv da db` (where both are path names) (5 pts)
- [ ] `pwd` (5 pts)
- [ ] `inode` works with both inode numbers and file names (5 pts)
- [ ] Bonus: implement `rm -fr dnm` (B25 pts)
- [ ] Bonus: implmeent `ls -lR dnm` (B25 pts)