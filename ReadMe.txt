Adrien Abbey
abbey.12@wright.edu

total 156
-rw-r--r-- 1 sevriem sevriem   754 Oct 18 14:14 Makefile
-rw-r--r-- 1 sevriem sevriem  7632 Nov  4 15:42 README.md
-rw-r--r-- 1 sevriem sevriem    33 Nov  4 15:44 ReadMe.txt
-rw-r--r-- 1 sevriem sevriem  6237 Oct 20 22:12 answers.txt
-rw-r--r-- 1 sevriem sevriem  2958 Oct 18 14:14 bitvector.cpp
-rw-r--r-- 1 sevriem sevriem  7756 Nov  4 15:27 directory.cpp
-rw-r--r-- 1 sevriem sevriem   174 Oct 18 14:14 diskParams.dat
-rw-r--r-- 1 sevriem sevriem   174 Oct 18 17:49 diskParams2.dat
-rw-r--r-- 1 sevriem sevriem  4237 Oct 18 14:14 file.cpp
-rw-r--r-- 1 sevriem sevriem  8018 Oct 28 18:33 fs33types.hpp
-rw-r--r-- 1 sevriem sevriem  9307 Nov  4 15:41 gdbSession.txt
-rw-r--r-- 1 sevriem sevriem  8980 Oct 25 17:42 inodes.cpp
-rw-r--r-- 1 sevriem sevriem  3644 Oct 18 14:14 mount.cpp
drwxr-xr-x 2 sevriem sevriem  4096 Oct 20 14:59 project_files
-rw-r--r-- 1 sevriem sevriem 31687 Nov  4 15:26 shell.cpp
-rw-r--r-- 1 sevriem sevriem  4138 Oct 25 13:58 simdisk.cpp
-rw-r--r-- 1 sevriem sevriem   362 Oct 18 14:14 stdTestScriptP2.txt
-rw-r--r-- 1 sevriem sevriem   533 Nov  4 15:14 testscript.txt
-rw-r--r-- 1 sevriem sevriem   111 Oct 18 14:14 user.cpp
-rw-r--r-- 1 sevriem sevriem  8220 Nov  4 15:27 volume.cpp

Most of my changes occured in shell.cpp, modifying existing methods, replacing 
"TODO" with appropriate code.  I did write a few additional methods, most of 
which were to reuse useful code and/or for recursive functions.  I'm 
particularly fond of my findFile() and getPwdString() methods, as they are both 
effective and reused by several methods.

I did run into a roadblock with rmdir, which I have not yet completed.
Additionally, I do realize I have a severe bug where moving folders will cause 
a crash when attempting to change to that directory.  My best guess is that I'm 
not properly updating the `.` and `..` directory references, which breaks my 
`pwd` method.