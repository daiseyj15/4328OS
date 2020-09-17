#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_LINE 1024

int page_faults = 0;

int main()
{
    int length=20;
    int frames, referenceString[length];
    int lower =1;
    int upper =5;
    int lruPAGEFAULTS,optimalPAGEFAULTS;

    srand(time(0));

    /*Write a program to compare the performance of the LRU and the Optimal page replacement
    algorithms. The program will take a reference string and the number of frames as inputs.
    Assume the maximum length of a reference string is 20 and there are 5 different pages from
    page 1 to page 5. The reference string can be randomly generated and the number of frames
    is entered through the keyboard. For example, the system generates a reference string
    2 1 3 4 5 2 3 ...5 and you enter the number of frames 3. Compare the number of page
    faults generated by the Optimal and LRU algorithms. Print out the page replacement process
    and you can see how LRU differs from the optimal.*/

    for(int i=0;i<20;i++)
    {
        referenceString[i]=(rand()%(upper-lower+1))+lower;
        printf("%d ",referenceString[i]);
    }

    printf("\nEnter the number of frames you would like to use: ");
    scanf("%d",&frames);

    int framearray[frames];

    /*Least recently used */
    printf("\n\nLRU\n");
    lruPAGEFAULTS=Lru(referenceString, frames, length, framearray);
    printf("\n\n");



    /*optimal*/
    printf("\n\nOptimal\n");
    optimalPAGEFAULTS=Optimal(referenceString, frames, length, framearray);
    printf("\n\n");


    printf("\n\n\nNumber of Page Faults\n");
    printf("LRU: %d\n",lruPAGEFAULTS);
    printf("Optimal: %d\n",optimalPAGEFAULTS);

    return 0;
}

int checkIFpresent(int check, int frames,int framearray[])
{
  int present = 0;
  int k = 0;
  while (k < frames)
  {
    if (framearray[k] != check)
    {
    }
    else
    {
      present = 1;
      break;
    }
    k++;
  }
  return present;
}

void initialize(int frames,int framearray[])
{
  page_faults = 0;
  int j = 0;
  for (j = 0; j < frames; j++)
  {
    framearray[j] = 0;
  }
}

int Optimal(int referenceString[], int frames, int length,int framearray[])
{
  int i, j, k = 0;
  int close[MAX_LINE / 2];
  initialize(frames,framearray);
  for(int d=0;d<frames;d++)
    {
        printf("\n_____\n");
        printf("| %d |\n",framearray[d]);
        printf("_____");
    }
  while (k < length)
  {
    /*Finds and executes only if there is a page fault*/
    if (checkIFpresent(referenceString[k], frames,framearray) == 0)
    {
      for (i = 0; i < frames; i++)
      {
        int find = 0;
        int page = framearray[i];
        j = k;
        while (j < length)
        {
          if (page == referenceString[j])
          {
            find = 1;
            close[i] = j;
            break;
          }
          else
          {
            find = 0;
          }
          j++;
        }
        if (!find)
        {
          close[i] = 9999;
        }
      }
      int maximum = -9999;
      int repeated;
      i = 0;
      while (i < frames)
      {
        if (maximum < close[i])
        {
          repeated = i;
          maximum = close[i];
        }
        i++;
      }
      framearray[repeated] = referenceString[k];
      page_faults = page_faults + 1;
    }
    printf("\n\n\n");
    for(int d=0;d<frames;d++)
    {
        printf("\n_____\n");
        printf("| %d |\n",framearray[d]);
        printf("_____");
    }
    k++;
  }
  return page_faults;
}

int Lru(int referenceString[], int frames, int length,int framearray[])
{
  int i, j, k = 0;
  int close[MAX_LINE / 2];
  initialize(frames,framearray);
  for(int d=0;d<frames;d++)
    {
        printf("\n_____\n");
        printf("| %d |\n",framearray[d]);
        printf("_____");
    }
  while (k < length)
  {
    /*Finds and executes only if there is a page fault*/
    if (checkIFpresent(referenceString[k], frames,framearray) == 0)
    {
      for (i = 0; i < frames; i++)
      {
        int find = 0;
        int page = framearray[i];
        j = k - 1;
        while (j >= 0)
        {
          if (page == referenceString[j])
          {
            find = 1;
            close[i] = j;
            break;
          }
          else
          {
            find = 0;
          }
          j--;
        }
        if (!find)
        {
          close[i] = -9999;
        }
      }
      int least = 9999;
      int repeated;
      i = 0;
      while (i < frames)
      {
        if (close[i] < least)
        {
          repeated = i;
          least = close[i];
        }
        i++;
      }
      framearray[repeated] = referenceString[k];
      page_faults = page_faults + 1;
    }


    printf("\n\n\n");
   for(int d=0;d<frames;d++)
    {
        printf("\n_____\n");
        printf("| %d |\n",framearray[d]);
        printf("_____");
    }

    k++;
  }
  return page_faults;
}
