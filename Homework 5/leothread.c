//Adam Cole

//leothread.c

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>


void *thread(void *vargp);
int leonardo(int n);


//create struct node to hold the process ids
//and their values to be stored in the tree
struct node {
  int tid;
  int level;
};


//first thread automatically run by compiler, must
//take two arguments from caller
int main(int argc, char ** argv){
  //create the root of the fibonacci tree
  pthread_t tid;   //thread id

  //eliminate whitespace and convert string to int
  //of the first character of the second argument in
  //main
  int threads = atoi(argv[1]);

  //creates root with level (order) threads and tid as 0
  struct node root = {0, threads};
  
  //check to make sure inputs are valid before creating
  //any threads
  
  //not enough argumets
  if( argc != 2 ) {
    printf("Must have 2 arguments");
    exit(1);
  }
  //negative number of threads
  if( threads <= 0 ){
    printf("Number of threads has to be positive");
    //exit with error code
    exit(1);
  }
  //root is leaf
  else if ( threads == 1 ){
    //print the leaf
    printf("[%d]\n", 0);
    exit(0);
  }

  //pass the root node as a void pointer to the thread function
  pthread_create(&tid, NULL, thread, (void*)&root);
  //make main() thread wait until thread tid returns
  pthread_join(tid, NULL);

  //exit the main thread
  exit(0);
}



int leonardo(int n){
  //if the input is 0 or 1, have just the root
  if ( n == 0 || n == 1 )
    return 1;
  //if x > 1 then create left and right subtree
  else if ( n > 1 )
    return leonardo( n-1 ) + leonardo( n-2 ) + 1;
  //invalid entry, return 0
  else 
    return 0;
}


//goal of *thread is to create two subtree threads
//with left size ( N-1 ) and right size ( N-2 )
void *thread(void *thr) {
  //recursive function, base case
  int currentlvl = ((struct node*)thr)->level;
  int currentthread = ((struct node*)thr)->tid;
  if ( currentlvl == 0 || currentlvl == 1 ){
    //print the leaf
    printf("[%d]\n", currentthread);
    return NULL;
  }

  //recursive case, recursive case
  //print current tid (first half)
  printf("(%d\n", currentthread);
  //create subtrees
  pthread_t leftid;
  pthread_t rightid;
  
  //create the subtree roots
  struct node left = {currentthread + 1, currentlvl - 1};
  struct node right = {currentthread + 1 + leonardo(currentlvl - 1), currentlvl - 2};

  //check if subtrees have valid levels, then create them
  //preorder, so left first
  if (currentlvl - 1 >= 0){
    pthread_create(&leftid, NULL, thread, (void*)&left);
    pthread_join(leftid, NULL);
  }
  //right second
  if(currentlvl - 2 >= 0){
    pthread_create(&rightid, NULL, thread, (void*)&right);
    pthread_join(rightid, NULL);
  }
  
  //print the level (second half of print)
  printf("%d)\n", currentthread);

  //end of recursive case
  return NULL;
}
