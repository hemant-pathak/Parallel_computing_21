/*
 ROOT MPI Process Controls All Communications
● most straightforward paradigm;
● maps one MPI process to one SMP node;
● each MPI process spawns a fixed number of shared memory threads;
● communication among MPI processes is handled by the main MPI process
only, at fixed predetermined intervals;
● allows for tight control of all communications;

*/
