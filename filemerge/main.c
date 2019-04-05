/* Programmer's Name: Surendra Baskey
   Program Name: filemergesort.c
   Program Description: Read a list of numbers from a binary file. Use merge sort to sort the list in ascending order without using arrays and using files. Write the sorted list in a text file
   Date: 6/2/18 */

#include<stdio.h>

/* Global Variables */
char infile[40];
int n;

/* function to sort parts of the list in ascending order and merge the parts */
void merge(int low, int mid, int high)
{
    FILE *f1,*f2,*f3; //file pointers
    int l1,l2,i,a,b;  //integer variables

    f1=fopen("input.bin", "rb");  //opens binary file in reading mode
    f2=fopen("input.bin", "rb"); //opens binary file in reading mode
    f3=fopen("temp.bin", "wb"); //opens binary file in writing mode

    fseek(f1, (low)*sizeof(int), SEEK_SET);
    fread(&a, sizeof(int), 1, f1);
    fseek(f2, (mid+1)*sizeof(int), SEEK_SET);
    fread(&b, sizeof(int), 1, f2);

    /* to numbers from input file and write them to a temporary file in ascending order */
    for(l1=low, l2=mid+1, i=low; l1<=mid && l2<=high; i++)
    {
        if(a<b)
        {
            fwrite(&a, sizeof(int), 1, f3);
            fread(&a, sizeof(int), 1, f1);
            l1++;
        }
        else
        {
            fwrite(&b, sizeof(int), 1, f3);
            fread(&b, sizeof(int), 1, f2);
            l2++;
        }
    }
    while(l1<=mid)
    {
        fwrite(&a, sizeof(int), 1, f3);
        fread(&a, sizeof(int), 1, f1);
        l1++;
    }
    while(l2<=high)
    {
        fwrite(&b, sizeof(int), 1, f3);
        fread(&b, sizeof(int), 1, f2);
        l2++;
    }

    fclose(f1); //closes the file
    fclose(f2); //closes the file
    fclose(f3); //closes the file

    f1=fopen("input.bin", "rb"); //opens binary file in reading mode
    f2=fopen("temp.bin","rb"); //opens binary file in reading mode
    f3=fopen("temp2.bin","wb"); //opens binary file in writing mode

    /* to write the numbers from input file and temporary file to an another temporary file */
    for(i=0; i<n; i++)
    {
        if(i>=low && i<=high)
        {
            fread(&b, sizeof(int), 1, f2);
            fread(&a, sizeof(int), 1, f1);
        }
        else
            fread(&b, sizeof(int), 1, f1);
        fwrite(&b, sizeof(int), 1, f3);
    }

    fclose(f1); //closes the file
    fclose(f2); //closes the file
    fclose(f3); //closes the file

    f1=fopen("temp2.bin", "rb"); //opens binary file in reading mode
    f2=fopen("input.bin", "wb"); //opens binary file in writing mode

    /* to write the numbers from second temporary file(which are part wise sorted) to input file */
    for(i=0; i<n; i++)
    {
        fread(&a, sizeof(int), 1, f1);
        fwrite(&a, sizeof(int), 1, f2);
    }

    fclose(f1); //closes the file
    fclose(f2); //closes the file
}

/* recursive function to divide the list into different parts for sorting */
void mergesort(int low, int high)
{
    int mid; //integer variables

    if(low<high)
    {
        mid=(low+high)/2;
        mergesort(low,mid); //calls the function mergesort
        mergesort(mid+1,high); //calls the function mergesort
        merge(low,mid,high); //calls the function merge
    }
    else
        return;
}

int main()
{
    FILE *f1,*f2; //file pointers
    int a,i; //integer variables

    //printf("Enter input filename\n"); //prompts the user to enter input filename
   // scanf("%s", infile); //scans the input filename

    f1=fopen("input.bin","rb"); //opens binary file in reading mode

    fseek(f1,0,SEEK_END); //moves the file pointer to the end of the file

    n=ftell(f1)/sizeof(int); //to count the no. of numbers present in the input file

    fclose(f1); //closes the file

    mergesort(0,n-1); //calls the function mergesort

    f1=fopen("input.bin","rb"); //opens binary file in reading mode
    f2=fopen("outfile.txt", "w"); //opens text file in writing mode

    /* to write the numbers from input binary file(which are now sorted) to text file */
    for(i=0; i<n; i++)
    {
        fread(&a, sizeof(int), 1, f1);
        printf("%d",a);
        fprintf(f2, "%d\n", a);
    }

    fclose(f1); //closes the file
    fclose(f2); //closes the file

    return 0; //tells the compiler that everything went well
}
