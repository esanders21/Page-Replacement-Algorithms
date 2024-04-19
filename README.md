# Find Optimal 
## int predictPage
Takes in a integer array as the page reference numbers, int vector for frames, int pageNumber as the page number, int page index as the page index. and then returns the predicted page.

## bool searchPage
Takes a int vector for frames, and a int key that has to be searchrd in the frame. It then returns true if the key is found or else it returns false. 

## void findOPT
Takes in integer array as page reference numbers, int pageNumber as the page number, int frameNumber as the current frame number, int step to keep track of the current step, and int fault to keep track of the current number of faults found. Then runs the search page and if found triggers a hit value and incriments the variable hit as an integer starting at 0. it then in either case has found a fault and incrments the value acordingly.

# Find LRU
## void findLRU 
Takes in a int vector as the as page reference numbers, the size or capacity as an int, vector int pages to create a list to store current pages into the memeory, int hits to work as a counter to keep track of the number of its, and faults and steps are treated similarly. Once called it begins by checking if ref_page already exists in pages list, remove it and append it at the end. It then checks the page reference string and incriments for hits and faults based on if the reference page is in the page list or not. after this process is ran for the entire list it then displays the total number of faults at the end.

# Find FIFO
## void FIFO
Takes in a integer array as the page reference numbers, the size or capacity as an int, int n as the size of theh inter array, queue<int> pageQueue and unordered_set<int> pageSet to help create a list to store the the current pages, as well as fault, and step to keep track of the number found. it then checks stating from the front of the array and begins storing and checking for faults. Once fincihsed the final value is displaayed. 

