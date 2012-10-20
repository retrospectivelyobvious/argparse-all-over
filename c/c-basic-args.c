/* Argparse All-Over
 * An example C argument parser (basic)
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
 
int main (int argc, char **argv){
    /* Variables for storing information returned from getopt() */
    int a = 0, b = 0;
    char *cstr = NULL;
    int arg;

    /* Indicate to getopt() how we want it to handle unrecognized options.
     *     * If this value is non-zero (default), getopt() will print an error
     *         message when it encounters an unrecognized option.
     *     * If this value is 0, getopt() will not print an error message when
     *         it encounters an unrecognized option.
     */
    opterr = 0;
 
    /* Main getopt() processing loop
     * Each time we call getopt(), it processes a single argument from the argv
     * list. That list is compared against the
     */
    while ((arg = getopt (argc, argv, "abc:")) != -1){
        switch (arg){
            case 'a':
                // Detected the 'a' option, mark a flag to indicate
                a = 1;
                break;
            case 'b':
                // Detected the 'b' option, mark a flag to indicate
                b = 1;
                break;
            case 'c':
                // Detected the 'c' option, save the location of its
                // argument (which getopt populates in the 'optarg' global).
                cstr = optarg;
                break;
            case '?':
                // Encountered an unknown or improperly formatted flag,
                // deal with these appropriately.
                //
                // getopt() populates the flag character into the 'optopt' 
                // global.
                if (optopt == 'c'){
                    fprintf(stderr, "-c requires an argument.\n");
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
    fprintf(stdout, "a = %d\nb = %d\ncstr = %s\n", a, b, cstr);
 
    /* Print out any remaining arguments unhandled by getopt() 
     *
     * optind is populated by getopt() to contain the (argc)index of the
     * next argument to be parsed. Since getopt() is finished parsing, at
     * this point it contains the first non-option argument.
     */
    for (int i = optind; i < argc; i++){
        printf("Additional argument %s\n", argv[i]);
    }

    exit(EXIT_SUCCESS);
    return 0;
}
