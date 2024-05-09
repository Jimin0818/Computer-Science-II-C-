/*
Program Name: Stack Queue
Date: 11/4/2022
Author: Ji Min Yoon
Module Purpose:Designed to develop implementations of a stack and a queue using templates.

*/

template <class DATATYPE>
class QueueListClass {  
  DATATYPE *dynamicAry = nullptr;        // dynamic array
  int      queueElementCount;            // number of items in the queue

public:
  // default constructor
  QueueListClass() { queueElementCount = 0; }

/*
Name: CopyToQueueFrom
Function Purpose : Copy to a newly formed queue 
Function Design:   allocates new memory for a new array to contain a copy of the queue
Inputs:            DATATYPE* newAry 
                   const QueueListClass sourceQueueObj - source object queue to be copied
Outputs:           QueueListClass& *this the newly formed queue
*/
  QueueListClass& CopyToQueueFrom(DATATYPE* newAry, const QueueListClass &obj) 
  {

      try 
      {
          newAry = new DATATYPE[obj.queueElementCount];
          if(queueElementCount > 0)
            delete[] dynamicAry;
          dynamicAry = newAry;
          queueElementCount = obj.queueElementCount;

          for(int i = 0; i < obj.queueElementCount; i++)
          {
            dynamicAry[i] = obj.dynamicAry[i];
          }
      }
      catch (bad_alloc e) 
      {
          cout << e.what() << endl;
          exit(EXIT_FAILURE);
      }
      return *this;
  }

  // copy constructor
  QueueListClass(const QueueListClass& QueueListClassObj) {
    CopyToQueueFrom(dynamicAry, QueueListClassObj);
  }

/*
Name: Enqueue
Function Purpose : add item to the queue
Function Design:   allocates new memory for in a dynamic  new array to contain a copy of the queue
                   if not sucessful memory allocation entry, states the reason and exits
                   creates a new dynamic array that holds the added to queue
                   deletes the old array
Inputs:            DATATYPE data- the item to add to back of the queue 
Outputs:           void
*/

  void Enqueue(DATATYPE data) 
  {

    DATATYPE* oldAry;
    oldAry = dynamicAry;
    try 
    {
        dynamicAry = new DATATYPE[queueElementCount + 1];
        for(int i = 0; i < queueElementCount; i++)
        {
            dynamicAry[i] = oldAry[i];
        }
        dynamicAry[queueElementCount] = data;

        queueElementCount++;

        if(queueElementCount > 1)
        {
            delete[] oldAry;
        }
    }
    catch (bad_alloc e) 
    {
      cout << e.what() << endl;
      exit(EXIT_FAILURE);
    }
  }
  

/*
Name: Denqueue
Function Purpose : take item out of queue front
Function Design:   allocates new memory for in a dynamic  new array to contain a copy of the queue
                   if not sucessful memory allocation entry, states the reason and exits
                   creates a new dynamic array that holds new queue with front removed
                   deletes the old array
Inputs:            none
Outputs:           DTATATYPE - the removed item from the front of the queue
*/

  DATATYPE Dequeue() 
  {

    if (queueElementCount == 0)
      return 0;
    DATATYPE item;
    item = dynamicAry[0];
    try
    {
        DATATYPE* newAry;
        newAry = new DATATYPE[queueElementCount - 1];
        queueElementCount--;

        for(int i = 0; i < queueElementCount; i++)
        {
            newAry[i] = dynamicAry[i+1];
        }
        if(queueElementCount > 0)
            delete[] dynamicAry;
        dynamicAry = newAry;
        return item;
    }
    catch (bad_alloc e)
    {
      cout << e.what() << endl;
      exit(EXIT_FAILURE);
    }

      return 0;
  
  }

  // operator function operator=(), implements assignment of objects of type QueueListClass
  QueueListClass &operator=(QueueListClass& obj) {
   DATATYPE* newAry = nullptr;
   CopyToQueueFrom(newAry, obj);
    return *this;
  }

  // destructor
  ~QueueListClass() {

    if (queueElementCount > 0)
      delete[] dynamicAry;
  }

  /*
Name: Peek
Function Purpose : look at item at queue front
Function Design:   checks if queue is empty
                   returns0
                   gets the front item in the queue
Inputs:            none
Outputs:           DTATATYPE - the item athe front of the queue
*/

  DATATYPE Peek() {
  if(queueElementCount > 0)
    return dynamicAry[0];
  else
    return 0;   
  }

/*
Name: Clear
Function Purpose : Clears the queue
Function Design:   if the queue is not empty, it deallocates the queue
Inputs:            called by the object that invokes it
Outputs:           void
                   clears the queue that invokes it
*/
  void Clear() {
    if(queueElementCount > 0)
    {
        delete[] dynamicAry;
        queueElementCount = 0;
    }
  }

/*
Name: IsEmpty()
Function Purpose : Checks if the queue is empty
Function Design:   Checks the existence of elements in the QueueListClass
Inputs:            called by object that invokes it
Outputs:           bool - true if empty, 0 is not empty
                   clears the queue that invokes it
*/
  bool IsEmpty()
  { 
  return queueElementCount == 0; 
  }

  // number items in the QueueListClass
  int getQueueElementCount() {
	return queueElementCount; 

  }

  // method that displays QueueListClass Objects
  void Display(const char* objName) {

    cout << "Object: " << objName << endl;
    for (int i = 0; i < queueElementCount; i++)
      cout << dynamicAry[i] << "\t";
    cout << endl;
    cout << "Element Count: " << getQueueElementCount() << endl;
    cout << "---------------------" << endl  << endl;

  }
};