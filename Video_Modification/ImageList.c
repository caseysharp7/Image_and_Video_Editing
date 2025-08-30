/*********************************************************************/
/* Homework Assignment 5, for EECS 22, Winter 2024                   */
/* ImageList.c: source file for image list manipulations             */
/*********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "ImageList.h"

/* Create a new image list */
ILIST *CreateImageList(void)
{
    /* to be implemented */
    ILIST *list;
    list = malloc(sizeof(ILIST));
    assert(list);
    list->Length = 0;
    list->First = NULL;
    list->Last = NULL;
    return list;
}

/* Delete an image list (and all entries) */
void DeleteImageList(ILIST *list)
{
    /* to be implemented */
    IENTRY *entry, *temp;
    Image *temp_image;

    assert(list);
    entry = list->First;
    while(entry)
    {
        temp = entry->Next;
        temp_image = (Image*) entry->image;
        DeleteImage(temp_image);
        free(entry);
        entry = temp;
    }

    free(list); 
}


/* Insert a RGB image to the image list at the end */
void AppendRGBImage(ILIST *list, Image *RGBimage)
{
    IENTRY *entry = NULL;
    assert(list);
    assert(RGBimage);
    entry = malloc(sizeof(IENTRY));
    entry->List = NULL;
    entry->Next = NULL;
    entry->Prev = NULL;
    entry->image = RGBimage;
    if(list->Last){
        entry->List = list;
        entry->Next = NULL;
        entry->Prev = list->Last;
        list->Last->Next = entry;
        list->Last = entry;
    } else {
        entry->List = list;
        entry->Next = NULL;
        entry->Prev = NULL;
        list->Last = entry;
        list->First = entry;
    }
    list->Length++;
}

/* Insert a YUV image to the image list at the end */
void AppendYUVImage(ILIST *list, YUVImage *YUVimage)
{
    IENTRY *entry = NULL;
    assert(list);
    assert(YUVimage);
    entry = malloc(sizeof(IENTRY));
    entry->List = NULL;
    entry->Next = NULL;
    entry->Prev = NULL;
    entry->image = YUVimage;
    if(list->Last){
        entry->List = list;
        entry->Next = NULL;
        entry->Prev = list->Last;
        list->Last->Next = entry;
        list->Last = entry;
    } else {
        entry->List = list;
        entry->Next = NULL;
        entry->Prev = NULL;
        list->Last = entry;
        list->First = entry;
    }
    list->Length++;
}

void CropImageList(ILIST *list, unsigned int start, unsigned int end)
{
    assert(list);
    if (start >= list->Length || end >= list->Length || start > end) {
        printf("Invalid crop range\n");
        return;
    }

    IENTRY *entry = list->First;
    IENTRY *temp;
    int i = 0;

    while (i < start) {
        temp = entry->Next;
        DeleteYUVImage((YUVImage*)entry->image);
        free(entry);
        entry = temp;
        i++;
        list->Length--;
    }

    list->First = entry;
    assert(entry);
    entry->Prev = NULL;

    while (i < end) {
        entry = entry->Next;
        i++;
    }
    assert(entry);
    temp = entry->Next;
    entry->Next = NULL;
    list->Last = entry;
    entry = temp;

    while (entry) {
        temp = entry->Next;
        DeleteYUVImage((YUVImage*)entry->image);
        free(entry);
        entry = temp;
        list->Length--;
    }
}



void FastImageList(ILIST *list, unsigned int factor) {
    assert(list);
    if (factor <= 1 || list->Length == 0) {
        return;
    }

    IENTRY *entry = list->First;
    IENTRY *temp;
    int i = 0;


    while (entry) {
        temp = entry->Next;

        if (i % factor != 0) {
            if (entry->Prev) {
                entry->Prev->Next = entry->Next;
            } else {
                list->First = entry->Next;
            }

            if (entry->Next) {
                entry->Next->Prev = entry->Prev;
            } else {
                list->Last = entry->Prev;
            }

            DeleteYUVImage((YUVImage *)entry->image);
            free(entry);
            list->Length--;
        }

        i++;
        entry = temp;
    }
}

/* Reverse an image list */
void ReverseImageList(ILIST *list)
{
    assert(list);

    IENTRY *entry = list->First;
    list->First = list->Last;
    IENTRY *temp;

    while (entry) {
        temp = entry->Prev;
        entry->Prev = entry->Next;
        entry->Next = temp;
        entry = entry->Prev;
    }

    list->Last = list->First;
}


/* Insert a RGB image to the image list in the front */
void PrependRGBImage(ILIST *list, Image *RGBimage)
{
    IENTRY *entry = NULL;
    assert(list);
    assert(RGBimage);
    entry = malloc(sizeof(IENTRY));
    entry->List = NULL;
    entry->Next = NULL;
    entry->Prev = NULL;
    entry->image = RGBimage;
    if(list->Last){
        entry->List = list;
        entry->Next = list->First;
        entry->Prev = NULL;
        list->First->Prev = entry;
        list->First = entry;
    } else {
        entry->List = list;
        entry->Next = NULL;
        entry->Prev = NULL;
        list->Last = entry;
        list->First = entry;
    }
    list->Length++;
}


/* EOF */
