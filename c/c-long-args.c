/* Argparse All-Over
 * An example C argument parser (long)
 * Copyright (C) 2012 Robert M. Sherbert <bob@retrospectivelyobvious.org>
 * Tutorial At: http://retrospectivelyobvious.org/c-argument-parse
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * 
 * If by some strange twist you believe that this software would have value for a
 * commercial project but are unwilling to be bound by the strictures of the GPL,
 * you may contact the author with inquiries for alternative licence terms.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>  //Long options are not part of POSIX, so we need an extra
                     //header to process them.
 
int main (int argc, char **argv){
    int a = 0, b = 0, e = 0;
    char *cstr = NULL, *dstr = NULL;
    int arg;
    int index = 0;

    opterr = 0;

    /* We need a way of configuring the options that getopt_long() will accept.
     * This is done through an array of 'struct option'. The elements of the
     * struct are as follows:
     * name -    The option that needs to be handled. If you want to accept
     *           --alpha, include an entry with name="alpha"
     *
     * has_arg - Indicates if that option will take an argument or not
     *              * no_argument - indicates that it will not
     *              * required_argument - indicates that it will
     * flag -    Ignoring this for now, it's safe to always set to 'NULL'
     * val -     The value that getopt_long will return if it finds this flag
     *
     * The structure must terminate with a NULL entry.
     */
    struct option opts[] = /* const char*   int                int*    int 
                              name          has_arg            flag    val    */
                         {  { "alpha",      no_argument,       NULL,   'a' },
                            { "bravo",      no_argument,       NULL,   'b' },
                            { "charlie",    required_argument, NULL,   'c' },
                            { "delta",      required_argument, NULL,   'd' },
                            { "echo",       no_argument,       NULL,   'e' },
                            { NULL,         0,                 NULL,    0  }
                         };
 
    /* Calling getopt_long is similar to the original, with a few extra
     * caveats. argc, argv, and the options string, are the same as before. The
     * options string is used to specify what short options will be accepted
     * (if any). Two additional arguments are included - the array of long
     * options specifiers and a variable that can carry the index of a long
     * option, should one be found (see case 'd' below).
     */
    while ((arg = getopt_long(argc, argv, "abc:d", opts, &index)) != -1){
        switch (arg){
            case 'a':
                a = 1;
                break;
            case 'b':
                b = 1;
                break;
            case 'c':
                cstr = optarg;
                break;
            case 'd':
                /* When a long argument is received, getopt_long populates the
                 * value at &index to hold the index into the opts array of the
                 * argument that it found in argv. This index can be used to
                 * look up information from the opts array about the option.
                 * Note that if a short option is processed, the value of
                 * &index is not altered and retains its previous value.
                 */
                fprintf(stdout, "Got long argument: %s.\n", opts[index].name);
                dstr = optarg;
                break;
            case 'e':
                fprintf(stdout, "Got long argument: %s.\n", opts[index].name);
                e = 1;
                break;
            case '?':
                // Handle improperly formatted arguments.
                if (optopt == 'c'){
                    fprintf(stderr, "-c requires an argument.\n");
                }else if (optopt == 'd'){
                    fprintf(stderr, "--delta requires an argument.\n");
                }else{
                    fprintf(stderr, "Unknown flag '%c'.\n", optopt);
                }
                //Fall-through here is intentional 
            default:
                //Hit some unexpected case - quit.
                exit(EXIT_FAILURE);
        }
    }

    /* Display the values of the found arguments */
    fprintf(stdout, "a = %d\nb = %d\ncstr = %s\ndstr = %s\ne = %d\n",
            a, b, cstr, dstr, e);
 
    // Print out any remaining arguments unhandled by getopt() 
    for (int i = optind; i < argc; i++){
        printf("Additional argument %s\n", argv[i]);
    }

    exit(EXIT_SUCCESS);
    return 0;
}
