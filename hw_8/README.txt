Submitted by :

Efraim Vishnevetsky 208697656
-----------------------------

Run with compilation line:

gcc hw8.c Interface.c -ansi -Wall -pedantic-errors -o interface
----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Some sample text files are provided for easier inspection.

Some functions are unused by the interface, because they were not requested in the assignment.
The commented out version of compressFile adds a separator after the compressed line, so that it can 
be decompressed afterwards. You may test this functionality, though the function "decompress" will have to be called manually.

Please notice that suffixes are concatenated to the end of a given file name,
For example - a .txt file which has been reversed and then encrypted(bent), will
have the suffix .txt.rpl.bend; e.g haiku.txt.rpl.bend, or train.txt.rpl.rds for a 
file thats been reversed and then compressed.

The function reverseFile, when called from interface (menu), may perform its operation
successfully, but will close the console after running. We do not know why this happens, and will
appreciate feedback, if possible. 