## Experimenting with argument parsing

### Terminology
- Argument is anything passed in via the command line
- Option is anything like -O3 or --verbose
- Parameter is any string, path, or numerical value passed in after an option
- There may be zero or more parameters for an option

### IndexableArgParser:
- Load arguments from argc, argv
- use operator[] to check if a given set of options have any parameters

### ChainArgParser:
- regiseter callbacks functions assigned to one or more options
- each callback is called and the given a set of parameters if its associated options were present in argv 
- load arguments from argc, argv, and call the registered callbacks if required