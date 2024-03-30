//Attendance entry system
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max 5000

int queue[max], front = -1, rear = -1;
char names[max][200];

void swap(int *a, int *b, char name_a[], char name_b[]) {
    int temp = *a;
    *a = *b;
    *b = temp;

    char temp_name[200];
    strcpy(temp_name, name_a);
    strcpy(name_a, name_b);
    strcpy(name_b, temp_name);
}
void insertbeg()
{
    int x;
    char y[200];
    if ((front == 0 && rear == max - 1) || (rear == front - 1))
    {
        printf("Overflow");
        return;
    }

    printf("Enter roll number: ");
    scanf("%d", &x);
    printf("\nEnter Name: ");
    scanf(" %[^\n]", y);

    if ((front == -1) && (rear == -1))
    {
        front = 0;
        rear = 0;
        queue[front] = x;
        strcpy(names[front], y);
    }
    else if (front == 0)
    {
        front = max - 1;
        queue[front] = x;
        strcpy(names[front], y);
    }
    else
    {
        front = front - 1;
        queue[front] = x;
        strcpy(names[front], y);
    }
}

void insertend()
{
    int x;
    char y[200];
    if ((front == 0 && rear == max - 1) || (rear == front - 1))
    {
        printf("Overflow");
        return;
    }

    printf("Enter roll number: ");
    scanf("%d", &x);
    printf("\nEnter Name: ");
    scanf(" %[^\n]", y);

    if (front == -1)
    {
        front = 0;
        rear = 0;
    }
    else if (rear == max - 1)
        rear = 0;
    else
        rear++;
    queue[rear] = x;
    strcpy(names[rear], y);
}

void display()
{
    int i;
    if (rear >= front)
    {
        for (i = front; i <= rear; i++)
            printf("Roll Number: %d, Name: %s\n", queue[i], names[i]);
    }
    else
    {
        for (i = front; i < max; i++)
            printf("Roll Number: %d, Name: %s\n", queue[i], names[i]);
        for (i = 0; i <= rear; i++)
            printf("Roll Number: %d, Name: %s\n", queue[i], names[i]);
    }
}

void delete()
{
    int x;
    if (front == -1)
    {
        printf("Underflow");
        return;
    }
    x = queue[front];

    printf("%d is going to delete\n", x);
    if (front == rear)
    {
        front = -1;
        rear = -1;
    }
    else if (front == max - 1)
        front = 0;
    else
        front++;
}

void delfront()
{
    {    
    if((front==-1) && (rear==-1))    
    {    
        printf("Not Found");    
    }    
    else if(front==rear)    
    {    
        printf("\n%d\t is going to delete\n", queue[front]);    
        front=-1;    
        rear=-1;    
            
    }    
     else if(front==(max-1))    
     {    
         printf("\nRoll Number: %d\t is going to delete\n", queue[front]);    
         front=0;    
     }    
     else    
     {    
          printf("\nRoll Number: %d\t is going to delete\n", queue[front]);    
          front=front+1;    
     }    
}  
}  
void delend()
{   
    if((front==-1) && (rear==-1))    
    {    
        printf("Not Found");    
    }    
    else if(front==rear)    
    {    
        printf("\nRoll Number: %d\t is going to delete\n", queue[rear]);    
        front=-1;    
        rear=-1;    
            
    }    
     else if(rear==0)    
     {    
         printf("\n%d\t is going to delete\n", queue[rear]);    
         rear=max-1;    
     }    
     else    
     {    
          printf("\n%d\t is going to delete\n", queue[rear]);    
          rear=rear-1;    
     }    
} 

void bubbleSort() {
    int i, j;
    for (i = front; i <= rear; i++) {
        for (j = front; j < rear; j++) {
            if (queue[j] > queue[j + 1]) {
                swap(&queue[j], &queue[j + 1], names[j], names[j + 1]);
            }
        }
    }
}


void insertmiddle() {
    int x, position, i;
    char y[200];

    if ((front == 0 && rear == max - 1) || (rear == front - 1)) {
        printf("Overflow");
        return;
    }

    printf("Enter roll number: ");
    scanf("%d", &x);
    printf("\nEnter Name: ");
    scanf(" %[^\n]", y);

    if (front == -1) {
        front = 0;
        rear = 0;
        queue[front] = x;
        strcpy(names[front], y);
    } else {
        printf("Enter the position to insert: ");
        scanf("%d", &position);

        if (position < front || position > rear + 1) {
            printf("Invalid position\n");
            return;
        }

        if (front > 0) {
            front--;
        }

        for (i = rear; i >= position; i--) {
            queue[i + 1] = queue[i];
            strcpy(names[i + 1], names[i]);
        }

        rear = (rear + 1) % max;

        queue[position - 1] = x;
        strcpy(names[position - 1], y);
    }
}


void deletemiddle() {
    int position, i;

    if (front == -1) {
        printf("Underflow\n");
        return;
    }

    printf("Enter the position to delete: ");
    scanf("%d", &position);

    if (position < front + 1 || position > rear + 1) {
        printf("Invalid position\n");
        return;
    }

    printf("%d is going to delete\n", queue[position - 1]);

    for (i = position - 1; i < rear; i++) {
        queue[i] = queue[i + 1];
        strcpy(names[i], names[i + 1]);
    }

    rear--;

    if (rear == -1) {
        front = -1;
    }
}

void displayCount() {
    int i;
    int count = 0; 

    if (front == -1) {
        printf("Queue is empty\n");
        return;
    }

    if (rear >= front) {
        for (i = front; i <= rear; i++) {
            count++;
        }
    } else {
        for (i = front; i < max; i++) {
            count++;
        }
        for (i = 0; i <= rear; i++) {
            count++;
        }
    }

    printf("Number of present student: %d\n", count);
}


void saveToFile() {
    FILE *file;
    file = fopen("attendance_data.txt", "w");

    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    int i;
    if (rear >= front) {
        for (i = front; i <= rear; i++) {
            fprintf(file, "Roll Number: %d, Name: %s\n", queue[i], names[i]);
        }
    } else {
        for (i = front; i < max; i++) {
            fprintf(file, "Roll Number: %d, Name: %s\n", queue[i], names[i]);
        }
        for (i = 0; i <= rear; i++) {
            fprintf(file, "Roll Number: %d, Name: %s\n", queue[i], names[i]);
        }
    }

    fclose(file);

    printf("Data saved to attendance_data.txt\n");
}



main()
{
 
  
    int ch,x;
    
do
{
    
    printf("*******************MENU*****************************\n");
    printf("1.Insert\n");
    printf("2.Insert in end\n");
    printf("3.Disply\n");
    printf("4.Delete in begenning\n");
    printf("5.Delete in end\n");
    printf("6.Sort according to roll number\n");
    printf("7.Insert in middle\n");
    printf("8.Delete in middle\n");
    printf("9.Find number of present student\n");
    printf("10.Save as file");
    printf("*****************************************************\n");
    printf("Enter your choice: \n");
    scanf("%d",&x);
    switch(x)
    {
        case 1:
        insertend();
        break;
        case 2:
        insertbeg();
        break;
        case 3:
        display();
        break;
        case 4:
        delfront();
        break;
        case 5:
        delend();
        break;
        case 6:
        bubbleSort();
        break;
        case 7:
        insertmiddle();
        break;
        case 8:
        deletemiddle();
        break;
        case 9:
        displayCount();
        break;
        case 10:
        saveToFile();
        break;
    }
    printf("If you want to continue press 1 else print any other key: ");
    scanf("%d",&ch);
}
    while(ch==1); 
}