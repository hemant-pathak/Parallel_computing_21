Input: The number of processes.

Output: The sum of all sub-array and the final sum of the array.

//n is the size of the array
//p is the total number of process
//rank 0 is called master process and other ranks are called worker processes
Algorithm arraySum(){
    if rank is 0 then
        //Initialize the array with size n
        arr[n] ={}
        array_element_per_process = n/p
        for i=1 to p-1 do
            copy sub_arr[array_element_per_process] from arr[n]
            send sub_arr[array_element_per_process] to rank i
            send array_element_per_process to rank i
        //Compute its own local sum
        for i=0 to array_element_per_process do
            local_sum +=arr[i]
        print rank, local_sum
        global_sum += local_sum
        //Collect the local sum from rest of the processes
        for i=1 to p do
            receive local_sum from rank i
            global_sum += local_sum
        //Display the sum of the array
        print global_sum
    else then
        receive sub_arr[array_element_per_process] from rank 0 
        receive array_element_per_process from rank 0
        //Compute the local sum of array
        for i=0 to array_element_per_process do
            local_sum += sub_arr[i]
        //Display the rank and local sum
        print rank, local_sum
        //Send the local sum to the master process
        send local_sum to rank 0
}
