# Project 2: Subdirectories and Moving Files
> Note: I decided to build upon my Project 1 files for this.
## TODO List:
1. [ ] ReadMe.txt contains the expected content
    1. [x] Descriptions of listed standard library routines.
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