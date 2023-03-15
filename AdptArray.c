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
} AdptArray;

// Initialize an empty array
PAdptArray CreateAdptArray(COPY_FUNC copyFunc, DEL_FUNC deleteFunc, PRINT_FUNC printFunc)
{
    PAdptArray new_arr = (PAdptArray)malloc(sizeof(struct AdptArray_)); // creating space in memory for new object

    new_arr->arr = (PElement *)malloc(2 * sizeof(PElement)); // creating space in memory for 2 elements inside the array
    new_arr->size = 2;                                       // initialize current size as 0
    // new_arr->max = 2;                                        // current max size is set to 2

   for (int i = obj_arr->size; i < new_size; i++)
    {
        new_arr[i] = NULL;
    }
    new_arr->copyFunc = copyFunc;
    new_arr->deleteFunc = deleteFunc;
    new_arr->printFunc = printFunc;

    return new_arr;
}

// Deleting each element in the array inside the object
void DeleteAdptArray(PAdptArray obj_arr)
{
    // delete each element in the array
    for (int i = 0; i < obj_arr->max; i++)
    {
        obj_arr->deleteFunc(obj_arr->arr[i]);
    }

    free(obj_arr->arr); // Free the space in memory that used to store the array
    free(obj_arr);      // free the space of the whole object
}

Result SetAdptArrayAt(PAdptArray obj_arr, int index, PElement element)
{
    if (index < obj_arr->size && index >= 0) // check if the index is within the current size of the array
    {
        obj_arr->deleteFunc(obj_arr->arr[index]);         // delete the element at the given index
        obj_arr->arr[index] = obj_arr->copyFunc(element); // set the element to the given element
    }
    else if (index >= obj_arr->size) // if the index is greater than the current size of the array, resize the array
    {
        int new_size = index + 1;
        PElement *new_arr = (PElement *)malloc(new_size * sizeof(PElement));
        if (!new_arr)
        {
            printf("Error: Out of memory.\n");
            return FAIL;
        }
        // Copy the existing elements to the new array
        for (int i = 0; i < obj_arr->size; i++)
        {
            new_arr[i] = obj_arr->arr[i];
        }
        // Initialize the new elements to NULL
        for (int i = obj_arr->size; i < new_size; i++)
        {
            new_arr[i] = NULL;
        }
        // Delete the old array and update the object's fields
        free(obj_arr->arr);
        obj_arr->arr = new_arr;
        obj_arr->size = new_size;
        obj_arr->arr[index] = obj_arr->copyFunc(element);
    }
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
    if (obj_arr == NULL || obj_arr->size == 0)
    {
        printf("Error - Cannot get an element out of a NULL array! \n");
        return;
    }
    else
    {

        for (int i = 0; i < obj_arr->size; i++)
        {

            if (obj_arr->arr[i])
            {

                obj_arr->printFunc(obj_arr->arr[i]);
            }
            else
                continue;
        }
    }
}
