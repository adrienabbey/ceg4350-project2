# Project 2: Subdirectories and Moving Files
> Note: I decided to build upon my Project 1 files for this.
## TODO List:
- [ ] ReadMe.txt contains the expected content
    1. [x] Descriptions of listed standard library routines.
    2. [ ] List of 5 *other* standard library routines and 5 system calls used by Project 2.
    3. [ ] In `simdisk.cpp`, why do we need to verify `statBuf.st_size == nSectorsPerDisk * nBytesPerSector`?
    4. [ ] Read [Notes on Programming in C](https://avida.cs.wright.edu/courses/CEG4350/Notes/Rob%20Pike%20Notes%20on%20Programming%20in%20C.html) by Rob Pike.  For five identifiers used in the given source code, either:
        1. suggest better alternative names and defend why they are better, or
        2. explain why I am comfortable with the names as they are.
    5. [ ] Write the pre-post conditions for:
        - `uint FileVolume::read33file(byte *fs33leaf, byte *unixFilePath)`
        - `uint FileVolume::write33file(byte *unixFilePath, byte *fs33leaf)`