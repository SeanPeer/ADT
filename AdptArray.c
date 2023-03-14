#include "AdptArray.h"
#include "book.h"
#include "Person.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

typedef struct AdptArray_
{
    PElement *arr;
    COPY_FUNC copyFunc;
    DEL_FUNC deleteFunc;
    PRINT_FUNC printFunc;
    int size;
    int max;
};

// Initialize an empty array
PAdptArray CreateAdptArray(COPY_FUNC copyFunc, DEL_FUNC deleteFunc, PRINT_FUNC printFunc)
{
    PAdptArray new_arr = (PAdptArray)malloc(sizeof(struct AdptArray_)); // creating space in memory for new object

    new_arr->arr = (PElement *)malloc(2 * sizeof(PElement)); // creating space in memory for 2 elements inside the array
    new_arr->size = 0;                                       // initialize current size as 0
    new_arr->max = 2;                                        // current max size is set to 2

    new_arr->copyFunc = copyFunc;
    new_arr->deleteFunc = deleteFunc;
    new_arr->printFunc = printFunc;

    return new_arr;
}

// Deleting each element in the array inside the object
void DeleteAdptArray(PAdptArray obj_arr)
{
    // delete each element in the array
    for (int i = 0; i < obj_arr->size; i++)
    {
        obj_arr->deleteFunc(obj_arr->arr[i]);
    }

    free(obj_arr->arr); // Free the space in memory that used to store the array
    free(obj_arr);      // free the space of the whole object
}

Result SetAdptArrayAt(PAdptArray obj_arr, int index, PElement element)
{
    // There is no object to insert to
    if (obj_arr == NULL)
    {
        return FAIL;
    }

    // If the index is out of memory bound in currernt array
    if (index >= obj_arr->max)
    {
        int new_max = obj_arr->max * 2;                                                    // setting new max size twice as big
        PElement *new_arr = (PElement *)realloc(obj_arr->arr, new_max * sizeof(PElement)); // realocating the old arr with new size to other place in memory with the new space

        obj_arr->arr = new_arr; // updating the array with the new space
        obj_arr->max = new_max; // updating the max capacity in obj
    }

    // updating the size of the array in case the index is bigger then current size
    if (index >= obj_arr->size)
    {
        obj_arr->size = index + 1;
    }

    obj_arr->arr[index] = obj_arr->copyFunc(element); // saving a copy of the element as asked
    free(element);                                    // freeing the space used for the element
    return SUCCESS;
}

PElement GetAdptArrayAt(PAdptArray obj_arr, int index)
{
    if (obj_arr == NULL)
    {
        printf("Error - Cannot get an elemnt out of a NULL array! \n");
        return NULL;
    }

    if (index >= obj_arr->size)
    {
        printf("Error - the index is out of the array bound");
        return NULL;
    }

    if (obj_arr->arr[index] == NULL)
    {
        return NULL;
    }
    else 
    {
        PElement copy_element = obj_arr->copyFunc(obj_arr->arr[index]);
        return copy_element;
    }
    
}

int GetAdptArraySize(PAdptArray obj_arr)
{
    if (obj_arr == NULL)
    {
        printf("Error - Cannot get an array size out of a NULL array! \n");
        return -1;
    }
    else
        return obj_arr->size;
}

void PrintDB(PAdptArray obj_arr)
{
    if (obj_arr == NULL)
    {
        printf("Error - Cannot get an element out of a NULL array! \n");
    }
    else
    {

        for (int i = 0; i < obj_arr->size; i++)
        {
            if (obj_arr->arr[i] == NULL)
                continue;
            else obj_arr->printFunc(obj_arr->arr[i]);;
        }
    }
}
