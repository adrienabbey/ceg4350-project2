Adrien Abbey
abbey.12@wright.edu

total 160
-rw-r--r-- 1 adrienabbey adrienabbey   754 Nov  4 15:53 Makefile
-rw-r--r-- 1 adrienabbey adrienabbey  7628 Nov  4 18:49 README.md
-rw-r--r-- 1 adrienabbey adrienabbey  2277 Nov  4 19:07 ReadMe.txt
-rw-r--r-- 1 adrienabbey adrienabbey  6237 Oct 20 22:12 answers.txt
-rw-r--r-- 1 adrienabbey adrienabbey  2958 Oct 18 14:14 bitvector.cpp
-rw-r--r-- 1 adrienabbey adrienabbey  7756 Nov  4 15:27 directory.cpp
-rw-r--r-- 1 adrienabbey adrienabbey   174 Oct 18 14:14 diskParams.dat
-rw-r--r-- 1 adrienabbey adrienabbey   174 Oct 18 17:49 diskParams2.dat
-rw-r--r-- 1 adrienabbey adrienabbey  4237 Oct 18 14:14 file.cpp
-rw-r--r-- 1 adrienabbey adrienabbey  8018 Oct 28 18:33 fs33types.hpp
-rw-r--r-- 1 adrienabbey adrienabbey  9307 Nov  4 15:41 gdbSession.txt
-rw-r--r-- 1 adrienabbey adrienabbey   717 Nov  4 19:04 improvements.txt
-rw-r--r-- 1 adrienabbey adrienabbey  8980 Oct 25 17:42 inodes.cpp
-rw-r--r-- 1 adrienabbey adrienabbey     0 Nov  4 19:08 lsout.txt
-rw-r--r-- 1 adrienabbey adrienabbey  3644 Oct 18 14:14 mount.cpp
drwxr-xr-x 2 adrienabbey adrienabbey  4096 Oct 20 14:59 project_files
-rw-r--r-- 1 adrienabbey adrienabbey 31302 Nov  4 18:43 shell.cpp
-rw-r--r-- 1 adrienabbey adrienabbey  4138 Oct 25 13:58 simdisk.cpp
-rw-r--r-- 1 adrienabbey adrienabbey   362 Oct 18 14:14 stdTestScriptP2.txt
-rw-r--r-- 1 adrienabbey adrienabbey   636 Nov  4 18:48 testscript.txt
-rw-r--r-- 1 adrienabbey adrienabbey   111 Oct 18 14:14 user.cpp
-rw-r--r-- 1 adrienabbey adrienabbey  8220 Nov  4 15:27 volume.cpp

Most of my changes occured in shell.cpp, modifying existing methods, replacing 
"TODO" with appropriate code.  I did write a few additional methods, most of 
which were to reuse useful code and/or for recursive functions.  I'm 
particularly fond of my findFile() and getPwdString() methods, as they are both 
effective and reused by several methods.

I wrote many additional comments throughout the project files, leaning heavily 
on VSCode's Doxygen comment feature.  This allowed me to write detailed 
descriptions of methods and the like, which could easily be referenced from 
code anywhere in the project as tooltips.  This was especially useful when 
working with a codebase such as this, which I wasn't familiar with.

I do realize I have a severe bug where moving folders will cause a crash when 
attempting to change to that directory.  My best guess is that I'm not properly 
updating the `.` and `..` directory references, which breaks my `pwd` method.