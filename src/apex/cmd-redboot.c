/* cmd-redboot.c

   written by Eddy Petrișor
   31 March 2015

   Copyright (C) 2015 Eddy Petrișor

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public License
   version 2 as published by the Free Software Foundation.
   Please refer to the file debian/copyright for further details.

   -----------
   DESCRIPTION
   -----------

   Call a command from RedBoot as if entered by hand in RedBoot.
   This is a dirty hack to allow automatic booting via tftp w/o
   the need to compile the (now unavailable and) dirty NPE code.

   This is a very hardware dependent (read Linksys NLSU2 version
   dependent) hack and relies on the fact my (lacking) reverse
   engineering skills are good enough to identify the correct
   function in the dissaembled RedBoot code from one of my NSLU2s.

   Note: Since my goal is to boot netbsd, which, apparently only
   needs the binary blob and has its own driver I might consider
   adding a rump kernel for the network driver in apex...

*/

#include <config.h>
#include <linux/string.h>
#include <linux/ctype.h>
#include <linux/kernel.h>
#include <linux/types.h>
#include <error.h>
#include <apex.h>
#include <command.h>

#define TALK 2
#include <talk.h>

/*
 * These values were obtained by reverse engineering the RedBoot code,
 * so, most likely, you need to change them, if you want to use this hack
 */
#define REDBOOT_CMD_BASE 0UL
/* redboot's cmd_proc function */
/* #define REDBOOT_CMD_PROC_FUNC_PTR (REDBOOT_CMD_BASE + 0x21c3cUL) */
#define REDBOOT_CMD_PROC_FUNC_PTR (REDBOOT_CMD_BASE + 0x224ccUL)

/* redboot's interractive command line buffer */
#define REDBOOT_CMD_BUFFER ((char *)0x0006c0b8UL)

#define MAX_CMDS        20
#define MAX_CMD_LEN     50
char const chain_cmds[][MAX_CMD_LEN+1] = {
  "version\0",
  "ip_address -h 192.168.0.2\0",
  "load -r -b 0x220000 netbsd-nfs.bin\0",
  "g\0",
};

//typedef int *redboot_p1(char*);
typedef void redboot_p1(void);

typedef void redboot_p3(char *buff, int len, int always_0a);

void call_redboot_cmd_proc(char *cmd)
{
  int rbresult;
  redboot_p3 *rbfunc;

  char volatile *redboot_cmd_buff = REDBOOT_CMD_BUFFER;

  DBG(2,"%s: peeking into redboot\n", __FUNCTION__);

  DBG(2, "%s: redboot cmd buffer (%x) '%s' cmd '%s' func \n",
      __FUNCTION__, (unsigned int)redboot_cmd_buff, redboot_cmd_buff, cmd);

  //DBG(2, "%s: prepbuffer '%s' rbfunc = %x\n", __FUNCTION__, cmd, (unsigned int)rbfunc);
  strlcpy(redboot_cmd_buff, cmd, MAX_CMD_LEN * sizeof(char));

  rbfunc = (redboot_p3 *)REDBOOT_CMD_PROC_FUNC_PTR;
  DBG(2, "%s: cmd '%s' rbfunc = %x\n", __FUNCTION__, cmd, (unsigned int)rbfunc);

  rbfunc(redboot_cmd_buff, strlen(redboot_cmd_buff)+1, 0x0a);
  //DBG(2, "rbresult %x\n", rbresult);
  DBG(2, "return red\n");
}

int cmd_redboot (int argc, const char** argv)
{
  unsigned int cmdidx;

  DBG(2, "%s: argc %d argv[0] '%s'\n", __FUNCTION__, argc, argv[0]);
  DBG(2, "1\n");
  if (argc>1)
    DBG(2, "%s:         argv[1] '%s'\n", __FUNCTION__, argv[1]);

  DBG(2, "2\n");
  if (argc > 2)
    return ERROR_PARAM;

  cmdidx = 0;

  DBG(2, "3\n");
  if (argc >=2) {
    DBG(2, "redboot parse '%s'\n", argv[1]);
    cmdidx = simple_strtoul(argv[1], NULL, 0);
  }

  DBG(2, "4\n");
  /*DBG(2, "cmdidx %ul redboot_cmd_buff '%s' chain_cmds[cmdidx] '%s'\n",
      cmdidx, redboot_cmd_buff, chain_cmds[cmdidx]);*/
  DBG(2, "cmdidx %u chain_cmds[cmdidx] '%s'\n",
        cmdidx, chain_cmds[cmdidx]);


  DBG(2, "5\n");
  printf("Calling redboot command '%s'\n", chain_cmds[cmdidx]);

  DBG(2, "6\n");
  call_redboot_cmd_proc((char *)chain_cmds[cmdidx]);
  DBG(2, "!!! Returned from RedBoot  !!!\n");

  return ERROR_NONE;
}

static __command struct command_d c_list = {
  .command = "redboot",
  .func = cmd_redboot,
  COMMAND_DESCRIPTION ("call RedBoot commands from Apex")
  COMMAND_HELP(
"redboot"
" [RBCMD]\n"
"  Call RedBoot commmands from Apex. EXPERIMENTAL!\n"
"\nExecute predefined redboot command with index 0\n"
"  e.g. redboot 0   \n"
"\nNOT YET IMPLEMENTED:\n"
"    redboot version\n"
"    redboot ip_address -h 192.168.0.2\n"
  )
};
