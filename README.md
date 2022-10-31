# Shared-Memory-Producer-Consumer
Implementation of producer and consumer using shared memory and semaphore


C program for Producer, Consumer process illustrating POSIX shared-memory API with Semaphore.

This project contains 4 files: main.c sharedContent.c producer.c consumer.c
Programming Language: C
External Library: semaphore, shm
Compile environment: Linux Ubuntu Terminal
How to compile: 
    gcc main.c -pthread -lrt -o main
    gcc consumer.c -pthread -lrt -o consumer
    gcc producer.c -pthread -lrt -o producer
Order of execution:
    ./main -> ./producer/consumer -> ./consumer/producer

Files details:
  sharedContent.c:
        struct sharedContent:   
            properties: int in, out
                        sem_t mutex, empty, full
                        char** sharedMem
        
        Methods:
            initSharedContent()
              initiate the shared memory to its first state: should only be called one
            getSharedContent()
              return the sharedContent between processes
  main.c
        main():
            init the first values of sharedMemory
  producer.c
        main():
            get the shared content between producer and consumer
            generating as many string as user input 
            orderly puting each string into the shared memory until the shared memory is full
            wait until the shared memory have space and continue puting string into it
  consumer.c
        main():
            get the shared content between producer and consumer
            take out inserted string in the shared memory if there are any and produce space for producer
            wait until there are string to process and until producer finish its crucial part.
            
  Usage example:
            gcc main.c -pthread -lrt -o main
            gcc consumer.c -pthread -lrt -o consumer
            gcc producer.c -pthread -lrt -o producer
            ./main 
            ./producer
            producer terminal: 
                added nwye
                added obzd
            ./consumer
            consumer terminal:
                processed: nwye 
                processed: obzd 
            producer terminal:
                added nwye
                added obzd
                added Bhcq
                added Ae?b
            consumer terminal:
                processed: nwye 
                processed: obzd 
                processed: Bhcq
                processed: Ae?b


            


            

            
    
