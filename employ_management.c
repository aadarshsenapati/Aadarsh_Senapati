/*
    
***********************************************************************************************
    The code is about employee management system which displays:
***********************************************************************************************
    Name of the employee
    Employee ID
    Employee date of birth
    Employee age
    Employee gross pay after calculation
    Employee net pay after calculation
***********************************************************************************************
    With the input:
***********************************************************************************************
    Name
    Employee ID
    Employee Hourly Rate 
    Employee Hour worked in a week
    Employee date of birth
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
struct DateOfBirth {//Nested structure for employee Date of Birth
    int date;
    int month;
    int year;
};
struct Employee { //Nested structure for employee details
    int empNumber;
    char empName[50];
    float salary;
    float   hour;
    struct DateOfBirth dob;  
};

int dobValidation(int date, int month, int year) {//Checking if the input date of birth is correct
    if ((month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) && date < 32 && year < 2023)//For the month having 31 days
        return 1;
    else if ((month == 4 || month == 6 || month == 9 || month == 11) && date < 31 && year < 2023)//For month having 30 days
        return 1;
    else if (month == 2 && year < 2023) {//Checking if the month is February
        if ((year % 4 == 0 && (year % 100 != 0 || year % 400 == 0) && date < 30) || (date < 29))//If the year is a leap year then there must be 29 days else 28 days
            return 1;
        else
            return 0;
    } else
        return 0;
}



int agecal(int year){//Calculating age of employee
    return 2023-year;
}


float GrossPay(float hourlyRate, float TotalHours) {//Calculating gross pay of the week
    float overTime;

    if (TotalHours > 40) {
        overTime = TotalHours - 40;
        float a;
        a = (1.5 * overTime * hourlyRate) + (hourlyRate * 40);
        return a;
    } else {
        return TotalHours * hourlyRate;
    }
}



int employvalidation(int a){//Checking employee id is 7 digit
    if(a>=1000000&&a<=9999999)
    return 1;
    else 
    return 0;
}


float WeeklyNetPay(float WeeklyGrossPay,int age){//Calculating weekly net payment
    float net_pay;
    float taxes_and_benefits= 200.0+1800.0;
    if(WeeklyGrossPay>taxes_and_benefits){
    if(age>50)
    net_pay=(WeeklyGrossPay-(0.15*WeeklyGrossPay)-taxes_and_benefits);
    else
    net_pay=(WeeklyGrossPay-(0.3*WeeklyGrossPay)-taxes_and_benefits);
    return net_pay;
    }else{
        return 0;
    }
}

int checkString(char str1[]) {//Checking if the name is consist of character(including space and '.')
    int i, x = 0, p;
    p = strlen(str1);
    for (i = 0; i < p; i++) {
        if ((str1[i] >= 'a' && str1[i] <= 'z') || (str1[i] >= 'A' && str1[i] <= 'Z') || (str1[i] == ' ') || (str1[i] == '.')) {
            continue;
        } else {
            return 0;
        }
    }
    return 1;
}


//Drivers code
int main() {
    int numEmployees,i;

    printf("Enter the number of employees: ");
    scanf("%d", &numEmployees);//Taking input for number of employee

    struct Employee employees[numEmployees];//Creating structure for each of employee

    for (i = 0; i < numEmployees; ++i) {//Taking the values as input
        printf("\nEnter details for Employee %d:\n", i + 1);

        printf("Name: ");
        scanf(" %[^\n]", employees[i].empName); 

        printf("Employee ID: (7 digit number)");
        scanf("%d", &employees[i].empNumber);

        printf("Employee Hourly Rate: ");
        scanf("%f", &employees[i].salary);

        printf("Employee Hour worked in a week: ");
        scanf("%f", &employees[i].hour);

        printf("Date of Birth (DD MM YYYY): ");
        scanf("%d %d %d", &employees[i].dob.date, &employees[i].dob.month, &employees[i].dob.year );
    }

    int age[numEmployees];
    int a[numEmployees];
    float g[numEmployees],h[numEmployees];
    printf("\nEmployee Details:\n");
    for (int i = 0; i < numEmployees; ++i) {//Loop to store value of next employee
    printf("\nEmployee %d:\n", i + 1);
    int ncheck = checkString(employees[i].empName);//Calling the function checkString
    int eValid = employvalidation(employees[i].empNumber);//Calling the function employvalidation
    int isValid = dobValidation(employees[i].dob.date, employees[i].dob.month, employees[i].dob.year);//Calling the function dobValidation
    age[i]= agecal(employees[i].dob.year);//Calling function age
    if (eValid == 1&&ncheck == 1&& isValid == 1&&employees[i].salary>55&&age[i]>=21){//Checking if the return value of funtion is true
        a[i] = agecal(employees[i].dob.year);//Saving the value of age in a[i]
        g[i] = GrossPay(employees[i].salary, employees[i].hour);//Saving value of gross pay in g[i] 
        h[i] = WeeklyNetPay(g[i],a[i]);//Saving weekly net payment in h[i]
        
        //Printing the values
        printf("Name: %s\n", employees[i].empName);
        printf("Employee ID:(7 digit) %d\n", employees[i].empNumber);
        printf("Date of Birth: %02d-%02d-%d\n", employees[i].dob.date, employees[i].dob.month, employees[i].dob.year);
        printf("Age: %d\n", a[i]);
        printf("Gross Pay: %f\n", g[i]);  
        printf("Net Pay: %f\n", h[i]);  
        }else{
        //If the functions return false then it will return which value is invalid
    if(eValid == 0){//If employee ID is false
        printf("Invalid Employ ID.\n");
    }
    if(ncheck == 0){//If employee name is invalid
        printf("Invalid Name.\n");
    }
    if(isValid == 0){//If employee date of birth is invalid
        printf("Employee has an invalid date of birth.\n");
    }
    if(employees[i].salary<=55){//If employee is underpaid
        printf("Employee is underpaid.\n");
    }
    if(age[i]<21){//If employee is underaged
        printf("Employ is underaged.\n");
    }
        }
    }
}
