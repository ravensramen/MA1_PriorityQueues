#include "HeapPriorityQueue.h"
#include <iostream>

///Sydnee Boothby CPTS 223 10/18
//This includes all my definitions for the priority queue implemented in main


HeapPriorityQueue::HeapPriorityQueue() {
    this->size = 0; //initialize size to 0
    //Array is allocated with max size, contents and size attribute updated with insertion
}

HeapPriorityQueue::~HeapPriorityQueue() {
    //heap is a fixed array allocated on stack, deleted automatically when out of scope
    //can't use "delete[]" as new items not alloced with "new"
    //don't have to worry about dangling pointers or memory leaks
}

// Copy constructor, creates deep copy based on passed in reference 
HeapPriorityQueue::HeapPriorityQueue(const HeapPriorityQueue& other) {
    //deep copy
    size = other.size; //size attribute of copy should be the same as RHS

    if (other.size == 0){
        return; //return with no new items in array if RHS is empty
    }

    for(int i =0; i<other.size; i++){ //iterate through RHS until all items copied
        heap[i] = other.heap[i];
        //creates deep copy, data at index of RHS stored in LHS
    }
}

//Copy "=" operator, shallow copy logic
//No pointers involved, so shallow copy and deep copy are quite similar
HeapPriorityQueue& HeapPriorityQueue::operator=(const HeapPriorityQueue& other) {

    if (this == &other){ //case one: both items are the same, just return LHS
        return *this; 
    }

    size = other.size; //both copies have the same size
   

    for (int i = 0; i<other.size; i++){ //copy all index items 
        heap[i] = other.heap[i];
    }

    return *this; //return ref to newly copied priority queue array
}

//Enqueue adds new job to the end of the array, increases size, and calls percolate to correct positioning
void HeapPriorityQueue::enqueue(const string& str, int priority) {
    // Insert new PrinterJob(str, priority) while maintaining heap order using percolateUp
    if (size>=MAX_SIZE){
        cout<<"To many items in queue, print a job before adding a new one.";
        return;
    }

    heap[size] = PrinterJob(str, priority); //new item entered at end of array
    percolateUp(size); //percolate up to proper position
    size++; //increment total items in array
    
}

// Print and remove PrinterJobs from the heap in priority order and using percolateDown as necessary
void HeapPriorityQueue::printJobs() {

    if (size == 0){
        cout<<"No jobs in queue to print";
        return;
    }

    while(size>0){
        PrinterJob currentPrint = heap[0];
        cout<<currentPrint.printString;
        cout<<" (Priority: "<<currentPrint.priority<<")"<<endl; //to match screenshot example

        heap[0] = heap[size-1]; //move last element to root position (essentially deleted printed root)
        size--; //decrease total array size (one less item to print)
        percolateDown(0); //percolate the new root to it's proper position

    }

}


//PercolateUp function
//Checks if the item at a given index has a higher priority than it's parent and swaps accordingly
//Swaps until root is reached or correct position
void HeapPriorityQueue::percolateUp(int index) {

    while (index>0){
        int parent = (index - 1)/2;
        if(heap[index].priority<heap[parent].priority){
        
        PrinterJob temp = heap[index];
        heap[index] = heap[parent];
        heap[parent] = temp;
        
        index = parent; //set new index after percolated up, continue until correct position 
        }
        else //break out of loop is proper position found
        {
            break;
        }
    }
}

//PercolateDown function
//Checks if node at given index has a lower priority than it's children, swaps if so
//Rearranges array index values to uphold priority queue logic
void HeapPriorityQueue::percolateDown(int index) { //index coresponds to the root of what we're percolating down

    while(true){ //keeps percolating until break (the item at index is the highest priority)

        int left = (2 * index) +1;
        int right = (2 * index )+2;
        int smallest = index;

        //check if left child exists and is smaller than input node (at index)

        if(left< size && heap[left].priority< heap[smallest].priority) {
            smallest = left; //new smallest is left child
        }
        if (right < size && heap[right].priority < heap[smallest].priority){
            smallest = right; //new smallest is right child
        }

        if (smallest == index) break; //return if root is highest priority (smallest not changed)

        //swap logic if a child is higher priority 
        PrinterJob temp = heap[index];
        heap[index] = heap[smallest];
        heap[smallest] = temp;

        index = smallest; //continue swapping with updated position

    }


}
