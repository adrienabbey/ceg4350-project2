/*
 * shell.C -- CEG433 File Sys Project shell
 * pmateti@wright.edu
 *
 * Modified for Project 1 of CEG-4350
 * by Adrien Abbey, Sept. 2023
 */

#include "fs33types.hpp"
#include <iostream>
#include <string>
#include <wait.h>

extern MountEntry *mtab;
extern VNIN cwdVNIN;
FileVolume *fv; // Suspicious!
Directory *wd;  // Suspicious!

#define nArgsMax 10
char types[1 + nArgsMax]; // +1 for \0

/* An Arg-ument for one of our commands is either a "word" (a null
 * terminated string), or an unsigned integer.  We store both
 * representations of the argument. */

class Arg
{
public:
  char *s;
  uint u;
} arg[nArgsMax];

uint nArgs = 0;

uint TODO()
{
  printf("to be done!\n");
  return 0;
}

uint TODO(char *p)
{
  printf("%s to be done!\n", p);
  return 0;
}

uint isDigit(char c)
{
  return '0' <= c && c <= '9';
}

uint isAlphaNumDot(char c)
{
  return c == '.' || 'a' <= c && c <= 'z' || 'A' <= c && c <= 'Z' || '0' <= c && c <= '9';
}

int toNum(const char *p)
{
  return (p != 0 && '0' <= *p && *p <= '9' ? atoi(p) : 0);
}

SimDisk *mkSimDisk(byte *name)
{
  SimDisk *simDisk = new SimDisk(name, 0);
  if (simDisk->nSectorsPerDisk == 0)
  {
    printf("Failed to find/create simDisk named %s\n", name);
    delete simDisk;
    simDisk = 0;
  }
  return simDisk;
}

void doMakeDisk(Arg *a)
{
  SimDisk *simDisk = mkSimDisk((byte *)a[0].s);
  if (simDisk == 0)
    return;
  printf("new SimDisk(%s) = %p, nSectorsPerDisk=%d,"
         "nBytesPerSector=%d, simDiskNum=%d)\n",
         simDisk->name, (void *)simDisk, simDisk->nSectorsPerDisk,
         simDisk->nBytesPerSector, simDisk->simDiskNum);
  delete simDisk;
}

void doWriteDisk(Arg *a)
{
  SimDisk *simDisk = mkSimDisk((byte *)a[0].s);
  if (simDisk == 0)
    return;
  char *st = a[2].s; // arbitrary word
  if (st == 0)       // if it is NULL, we use ...
    st = "CEG433/633/Mateti";
  char buf[1024]; // assuming nBytesPerSectorMAX < 1024
  for (uint m = strlen(st), n = 0; n < 1024 - m; n += m)
    memcpy(buf + n, st, m); // fill with several copies of st
  uint r = simDisk->writeSector(a[1].u, (byte *)buf);
  printf("write433disk(%d, %s...) == %d to Disk %s\n", a[1].u, st, r, a[0].s);
  delete simDisk;
}

void doReadDisk(Arg *a)
{
  SimDisk *simDisk = mkSimDisk((byte *)a[0].s);
  if (simDisk == 0)
    return;
  char buf[1024]; // assuming nBytesPerSectorMAX < 1024
  uint r = simDisk->readSector(a[1].u, (byte *)buf);
  buf[10] = 0; // sentinel
  printf("read433disk(%d, %s...) = %d from Disk %s\n", a[1].u, buf, r, a[0].s);
  delete simDisk;
}

void doQuit(Arg *a)
{
  exit(0);
}

void doEcho(Arg *a)
{
  printf("%s#%d, %s#%d, %s#%d, %s#%d\n", a[0].s, a[0].u,
         a[1].s, a[1].u, a[2].s, a[2].u, a[3].s, a[3].u);
}

void doMakeFV(Arg *a)
{
  SimDisk *simDisk = mkSimDisk((byte *)a[0].s);
  if (simDisk == 0)
    return;
  fv = simDisk->make33fv();
  printf("make33fv() = %p, Name == %s, Disk# == %d\n",
         (void *)fv, a[0].s, simDisk->simDiskNum);

  if (fv)
  {
    wd = new Directory(fv, 1, 0);
    cwdVNIN = mkVNIN(simDisk->simDiskNum, 1);
  }
}

void doCopyTo(byte *from, byte *to)
{
  uint r = fv->write33file(to, from);
  printf("write33file(%s, %s) == %d\n", to, from, r);
}

void doCopyFrom(byte *from, byte *to)
{
  uint r = fv->read33file(to, from);
  printf("read33file(%s, %s) == %d\n", to, from, r);
}

void doCopy33(byte *from, byte *to)
{
  uint r = fv->copy33file(to, from);
  printf("copy33file(%s, %s) == %d\n", to, from, r);
}

void doCopy(Arg *a)
{
  byte *to = (byte *)a[0].s;
  byte *from = (byte *)a[1].s;

  if (a[0].s[0] == '@' && a[1].s[0] != '@')
  {
    doCopyTo(from, (to + 1));
  }
  else if (a[0].s[0] != '@' && a[1].s[0] == '@')
  {
    doCopyFrom((from + 1), to);
  }
  else if (a[0].s[0] != '@' && a[1].s[0] != '@')
  {
    doCopy33(from, to);
  }
  else
  {
    puts("Wrong arguments to cp.");
  }
}

void doLsLong(Arg *a)
{
  printf("\nDirectory listing for disk %s, cwdVNIN == 0x%0lx begins:\n",
         wd->fv->simDisk->name, (ulong)cwdVNIN);
  wd->ls(); // Suspicious!
  printf("Directory listing ends.\n");
}

void doRm(Arg *a)
{
  uint in = wd->fv->deleteFile((byte *)a[0].s);
  printf("rm %s returns %d.\n", a[0].s, in);
}

void doInode(Arg *a)
{
  uint ni = a[0].u;

  wd->fv->inodes.show(ni);
}

void doMkDir(Arg *a)
{
  TODO("doMkDir");
}

void doChDir(Arg *a)
{
  TODO("doChDir");
}

void doPwd(Arg *a)
{
  TODO("doPwd");
}

void doMv(Arg *a)
{
  TODO("doMv");
}

void doMountDF(Arg *a) // arg a ignored
{
  TODO("doMountDF");
}

void doMountUS(Arg *a)
{
  TODO("doMountUS");
}

void doUmount(Arg *a)
{
  TODO("doUmount");
}

/* The following describes one entry in our table of commands.  For
 * each cmmdName (a null terminated string), we specify the arguments
 * it requires by a sequence of letters.  The letter s stands for
 * "that argument should be a string", the letter u stands for "that
 * argument should be an unsigned int."  The data member (func) is a
 * pointer to the function in our code that implements that command.
 * globalsNeeded identifies whether we need a volume ("v"), a simdisk
 * ("d"), or a mount table ("m").  See invokeCmd() below for exact
 * details of how all these flags are interpreted.
 */

class CmdTable
{
public:
  char *cmdName;
  char *argsRequired;
  char *globalsNeeded; // need d==simDisk, v==cfv, m=mtab
  void (*func)(Arg *a);
} cmdTable[] = {
    {"cd", "s", "v", doChDir},
    {"cp", "ss", "v", doCopy},
    {"echo", "ssss", "", doEcho},
    {"inode", "u", "v", doInode},
    {"ls", "", "v", doLsLong},
    {"lslong", "", "v", doLsLong},
    {"mkdir", "s", "v", doMkDir},
    {"mkdisk", "s", "", doMakeDisk},
    {"mkfs", "s", "", doMakeFV},
    {"mount", "us", "", doMountUS},
    {"mount", "", "", doMountDF},
    {"mv", "ss", "v", doMv},
    {"rddisk", "su", "", doReadDisk},
    {"rmdir", "s", "v", doRm},
    {"rm", "s", "v", doRm},
    {"pwd", "", "v", doPwd},
    {"q", "", "", doQuit},
    {"quit", "", "", doQuit},
    {"umount", "u", "m", doUmount},
    {"wrdisk", "sus", "", doWriteDisk}};

uint ncmds = sizeof(cmdTable) / sizeof(CmdTable);

void usage()
{
  printf("The shell has only the following cmds:\n");
  for (uint i = 0; i < ncmds; i++)
    printf("\t%s\t%s\n", cmdTable[i].cmdName, cmdTable[i].argsRequired);
  printf("Start with ! to invoke a Unix shell cmd\n");
}

/* pre:: k >= 0, arg[] are set already;; post:: Check that args are
 * ok, and the needed simDisk or cfv exists before invoking the
 * appropriate action. */

void invokeCmd(int k, Arg *arg)
{
  uint ok = 1;
  if (cmdTable[k].globalsNeeded[0] == 'v' && cwdVNIN == 0)
  {
    ok = 0;
    printf("Cmd %s needs the cfv to be != 0.\n", cmdTable[k].cmdName);
  }
  else if (cmdTable[k].globalsNeeded[0] == 'm' && mtab == 0)
  {
    ok = 0;
    printf("Cmd %s needs the mtab to be != 0.\n", cmdTable[k].cmdName);
  }

  char *req = cmdTable[k].argsRequired;
  uint na = strlen(req);
  for (uint i = 0; i < na; i++)
  {
    if (req[i] == 's' && (arg[i].s == 0 || arg[i].s[0] == 0))
    {
      ok = 0;
      printf("arg #%d must be a non-empty string.\n", i);
    }
    if ((req[i] == 'u') && (arg[i].s == 0 || !isDigit(arg[i].s[0])))
    {
      ok = 0;
      printf("arg #%d (%s) must be a number.\n", i, arg[i].s);
    }
  }
  if (ok)
    (*cmdTable[k].func)(arg);
}

/* pre:: buf[] is the command line as typed by the user, nMax + 1 ==
 * sizeof(types);; post:: Parse the line, and set types[], arg[].s and
 * arg[].u fields.
 */

void setArgsGiven(char *buf, Arg *arg, char *types, uint nMax)
{
  for (uint i = 0; i < nMax; i++)
  {
    arg[i].s = 0;
    types[i] = 0;
  }
  types[nMax] = 0;

  strtok(buf, " \t\n"); // terminates the cmd name with a \0

  for (uint i = 0; i < nMax;)
  {
    char *q = strtok(0, " \t");
    if (q == 0 || *q == 0)
      break;
    arg[i].s = q;
    arg[i].u = toNum(q);
    types[i] = isDigit(*q) ? 'u' : 's';
    nArgs = ++i;
  }
}

/* pre:: name pts to the command token, argtypes[] is a string of
 * 's'/'u' indicating the types of arguments the user gave;; post::
 * Find the row number of the (possibly overloaded) cmd given in
 * name[].  Return this number if found; return -1 otherwise. */

int findCmd(char *name, char *argtypes)
{
  for (uint i = 0; i < ncmds; i++)
  {
    if (strcmp(name, cmdTable[i].cmdName) == 0 && strcmp(argtypes, cmdTable[i].argsRequired) == 0)
    {
      return i;
    }
  }
  return -1;
}

void ourgets(char *buf)
{
  fgets(buf, 1024, stdin);
  char *p = index(buf, '\n');
  if (p)
    *p = 0;
}

/* The following are all custom functions I wrote for Project 1. */

// Copy/paste of provided code that executes a local command, from main() method to reduce repetition:
void doCommand(char *buf)
{
  setArgsGiven(buf, arg, types, nArgsMax);
  int k = findCmd(buf, types);
  if (k >= 0)
    invokeCmd(k, arg);
  else
    usage();
}

bool checkRedirect(char *str)
{
  // My method to check for a redirect character in the input string.
  // Return true if the `>` character exists in the string.

  // Since we're using character arrays, I need a way to find the size of a
  // given char array: https://stackoverflow.com/a/4180826

  for (long unsigned int i = 0; i < strlen(str); i++)
  {
    if (str[i] == '>')
    {
      return true;
    }
  }
  return false;
}

bool checkPipe(char *str)
{
  // My method to check for a pipe character in the input string.
  // Return true if the `|` character exists in the string.

  for (long unsigned int i = 0; i < strlen(str); i++)
  {
    if (str[i] == '|')
    {
      return true;
    }
  }
  return false;
}

bool checkBackground(char *str)
{
  // Check for a background character in the input string.

  for (long unsigned int i = 0; i < strlen(str); i++)
  {
    if (str[i] == '&')
    {
      return true;
    }
  }
  return false;
}

std::string getRedirectFile(char *str)
{
  // My method to extract the file name from the given string.
  // Search for the `>` character, then return a new string containing every
  // character after that: https://cplusplus.com/reference/cstring/strtok/

  // Tokenize the given string:
  std::string returnString = strtok(str, ">");

  // Do this twice to get the file name:
  returnString = strtok(NULL, ">");

  // If the first character of the string is a space, remove that:
  // https://stackoverflow.com/a/23834717
  if (returnString[0] == ' ')
  {
    returnString.erase(0, 1);
  }

  return returnString;
}

// My method for executing a redirect:
void doRedirect(char *buf)
{
  // I need to redirect `stdout` to the given file name.
  // To do this, I can use `dup2`:
  // https://www.geeksforgeeks.org/dup-dup2-linux-system-call/

  // First I need to get the filename from the string:
  std::string fileName = getRedirectFile(buf);

  // Remove the redirect from the command:
  char *redirectedCommand = strtok(buf, ">");

  // Open the file: https://www.geeksforgeeks.org/convert-string-char-array-cpp/
  // https://stackoverflow.com/a/35186153
  int fileDescriptor = open(fileName.c_str(), O_WRONLY | O_CREAT, 0644);

  // Save original stdout: https://stackoverflow.com/a/11042581
  int savedStdout = dup(STDOUT_FILENO);

  // Redirect `stdout` to the given file: https://stackoverflow.com/q/26666012
  dup2(fileDescriptor, STDOUT_FILENO);

  // Check for host commands:
  if (redirectedCommand[0] == '!')
  {
    system(redirectedCommand + 1);
  }
  else
  {
    doCommand(redirectedCommand); // Copy of original command handler from main()
  }

  // Restore `stdout`:
  dup2(savedStdout, STDOUT_FILENO);
  close(savedStdout);
}

void splitPipeString(char *buf, char *firstCmd, char *secondCmd)
{
  // Split the given string into multiple commands.
  // This is NOT for bonus points.
  // Assumes only two commands with valid formatting.

  // https://stackoverflow.com/a/49698596
  // I made the mistake of forgetting how pointers and shallow copies work.

  // Pull the first command from the string:
  std::string firstCmdTemp = strtok(buf, "|");

  // Pull the second:
  std::string secondCmdTemp = strtok(NULL, "|");

  // Note: The project instructions state: "Implement piping as discussed
  // in class for commands executed on the host."  I'm interpreting that
  // as meaning that piping will *always* only ever involve host commands
  // starting with '!'

  // Strip ' ' from the beginning of each string:
  while (firstCmdTemp[0] == ' ')
  {
    if (firstCmdTemp[0] == ' ')
    {
      firstCmdTemp.erase(0, 1);
    }
  }

  // Strip ' ' from the beginning of each string:
  while (secondCmdTemp[0] == ' ')
  {
    if (secondCmdTemp[0] == ' ')
    {
      secondCmdTemp.erase(0, 1);
    }
  }

  // Copy the temporary strings to the provided pointers for more permanent results:
  strcpy(firstCmd, firstCmdTemp.c_str());
  strcpy(secondCmd, secondCmdTemp.c_str());
}

void doPipe(char *buf)
{
  // Re-reading the instructions, this is actually a lot easier than I
  // was expecting: I only need to handle host commands!

  // For piped commands, I first need to split the input string into
  // multiple commands:

  // Prep the vars:
  char firstCmd[BUFSIZ];  // Buffersize matters, apparently:
  char secondCmd[BUFSIZ]; // https://stackoverflow.com/a/14428470

  // Split the input:
  splitPipeString(buf, firstCmd, secondCmd);

  // I'm hopelessly lost and overly dependent on others for guidance.
  // https://www.geeksforgeeks.org/c-program-demonstrate-fork-and-pipe/
  // I'm using the above as a reference guide to figure out how to use forks
  // and pipes.

  // That wasn't enough.  I ended up asking for guidance via email.  I was
  // going about this all wrong.  I was so fixated on strings and arguments
  // that I completely missed connecting `stdout` to `stdin`.

  int stdPipe[2]; // I only need to send data to the child process.

  pid_t p; // Tracks the process identifiers used by fork

  // Create the pipe:
  pipe(stdPipe);
  // Data written on stdPipe[1] can be read from stdoutPipe[0]

  // Fork this process:
  p = fork(); // p=-1 for errors, p=0 for the new child, and p>0 for this parent process.

  // If this is the parent process:
  if (p > 0)
  {
    // The parent process handles the second command.
    // This means it wants to read data from the child process,
    // which does the first command.

    // Close the writing end of the pipe:
    close(stdPipe[1]);

    // Redirect the piped data to `stdin`.

    // Make a copy of `stdin` so I can restore it later:
    int stdinCpy = dup(STDIN_FILENO);

    // Redirect piped data to `stdin`:
    dup2(stdPipe[0], STDIN_FILENO);

    // Execute the second command using the piped arguments:
    if (secondCmd[0] == '!') // I need to remove the '!' char before running the command:
    {
      system(secondCmd + 1);
    }
    else
    {
      system(secondCmd);
    }
    // TODO: What if this were another checkCommand call?

    // Restore `stdin`:
    dup2(stdinCpy, STDIN_FILENO);

    // Close both ends of the pipe:
    close(stdPipe[0]);
    close(stdPipe[1]);
  }
  else if (p < 0) // If an error occurred while forking...
  {
    fprintf(stderr, "An error occurred while forking.");
    exit(EXIT_FAILURE);
  }
  // Child process:
  else
  {
    // Close the read pipe:
    close(stdPipe[0]);

    // I need to redirect `stdout` to the write end of the pipe, then run the command.

    // Make a copy of `stdout` so I can restore it later:
    int stdoutCpy = dup(STDOUT_FILENO);

    // Redirect `stdout` to the pipe:
    dup2(stdPipe[1], STDOUT_FILENO);

    // Run the first command:
    // Note: the first command might NOT be a host command:
    if (firstCmd[0] == '!') // If the first command IS a host command:
    {
      system(firstCmd + 1); // Run the first command on the host, excluding the '!' char
    }
    else // Otherwise, the first command is a local command:
    {
      // TODO: Consider checking for redirects, backgrounds, additional pipes, etc.
      doCommand(firstCmd); // Note: this assumes the first command is a regular command.
    }

    // Restore `stdout`:
    dup2(stdoutCpy, STDOUT_FILENO);

    // Close the pipes:
    close(stdPipe[0]);
    close(stdPipe[1]);

    // Close the child process:
    exit(EXIT_SUCCESS);
  }
}

void doBackground(char *buf)
{
  // Run the given command in the background.
  // This could be a local or a host command.

  // Remove the '&' character from the command string:
  std::string sanitizedCmd = buf;
  for (long unsigned int i = 0; i < sanitizedCmd.length(); i++)
  {
    if (sanitizedCmd[i] == '&')
    {
      sanitizedCmd.erase(i, i + 1);
      i--; // We just deleted a character, go back one index.
    }
  }

  // Create a pid object ot track the process identifiers:
  pid_t pid;

  // Fork the process:
  pid = fork();

  // I only need to have the child process do anything:
  if (pid == 0)
  {
    // Run the given command.  Assume it's properly formatted.
    // If it's a system command:
    if (sanitizedCmd[0] == '!')
    {
      system(sanitizedCmd.c_str() + 1);
      exit(EXIT_SUCCESS);
    }
    else
    {
      // FIXME: Assume it's a local, non-piped, non-redirect command:
      // https://www.geeksforgeeks.org/convert-string-char-array-cpp/
      char *commandChar = new char[sanitizedCmd.length() + 1]; // doCommand ain't happy with str.c_str()
      doCommand(commandChar);
      exit(EXIT_SUCCESS);
    }
  }
  else if (pid > 0)
  {
    // Parent process, do nothing.
  }
  else // Otherwise something went wrong...
  {
    fprintf(stderr, "An error occurred while executing a background process.");
    exit(EXIT_FAILURE);
  }
}

// My method to parse commands, applying redirects, pipes, and background as appropriate:
void parseCommands(char *buf)
{
  // Start by checking for blank commands and comments.
  //   Note: much of this is a copy of code provided in main(), moved to here:
  if (buf[0] == 0)
  {
    return; // no command, so do nothing
  }
  else if (buf[0] == '#')
  {
    return; // this is a comment line, do nothing
  }
  else // If not blank or commented code, do stuff:
  {
    // If the command has a pipe:
    if (checkPipe(buf))
    {
      doPipe(buf); // TODO: does doPipe need to handle redirects, background, and additional commands?
    }
    else if (checkRedirect(buf)) // If the command has a redirect but no pipe:
    {
      doRedirect(buf); // TODO: Likewise as above.
    }
    else // If not a pipe or redirect:
    {
      if (buf[0] == '!') // If a host command:
      {
        if (checkBackground(buf)) // Check for any background:
        {
          doBackground(buf); // TODO: Consider having this method check for local/host execution!
        }
        else // not a background, pipe, or redirect, but it IS a host command:
        {
          system(buf + 1); // Execute the shell command on host, excluding the '!' character
        }
      }
      else // Not a pipe, redirect, or host command:
      {
        // Execute a local command.
        doCommand(buf); // Todo: Should this check for background, etc?
      }
    }
  }
}

/* End of my custom functions. */

int main()
{
  char buf[1024]; // better not type longer than 1023 chars

  usage();
  for (;;)
  {
    *buf = 0;               // clear old input
    printf("%s", "sh33% "); // prompt
    ourgets(buf);
    printf("cmd [%s]\n", buf); // just print out what we got as-is
    // I moved conditional checking of the given command to another method, allowing me to reuse the code elsewhere.
    parseCommands(buf); // Parse the command for comments, host, redirects, pipes, background, etc, then apply those as appropriate.
  }
}

// -eof-
