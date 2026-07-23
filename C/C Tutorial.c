#include <ctype.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

// float division(int a ,int b){
//     if (a/b == 0)
//     {
//         printf("Error");
//         return 0;
//     }
//     return (float) a / (float) b;
// }

// float multiplication(int a ,int b)
// {
//     return (float) a * (float) b;
// }

// void parking_function()
// {
//     printf("\nParking Y/N:");
//     scanf("%c ", &parking);
//     if (parking == 'y' && parking == 'Y'&&parking == 'N'&&parking == 'n')
//     {
//         if (parking == 'y'||parking == 'Y')
//         {
//             parking_slot++;
//         }
//         return;
//     }
//     else
//     {
//         printf("\nError");
//         return ;
//     }
// }

int main()
{
    //Q1
    //printf("Faculty     :   Computer Science\n");
    //printf("Programme   :   Introducing to Programming\n");
    //printf("___________________________________________\n");
    //printf("Subject Code        Subject Name        Credit Value\n");
    //printf("___________________________________________\n");
    //printf("BCS1014             ITP                 3\n");
    //printf("BCS1053             C&LA                3\n");
    //printf("BCS1033             DM                  3");

    //Q2
    //int a,b,add,minus,multiply,divide,power,avg;

    //printf("Declare A Variable:");
    //scanf("%d",&a);
    //printf("Declare B Variable:");
    //scanf("%d",&b);

    //add = a + b;
    //minus = a - b;
    //multiply = a * b;
    //divide = a / b;
    //power = pow(a,b);
    //avg = (a + b)/2;

    //printf("\n\nAdd:%d\n",add);
    //printf("Minus:%d\n",minus);
    //printf("Multiply:%d\n",multiply);
    //printf("Divide:%d\n",divide);
    //printf("Power:%d\n",power);
    //printf("Avg:%d",avg);

    //Q3
    //float items[5],discount,price[5];
    //for (int i = 0; i < 5; i++)
    // {
    //     printf("Enter items %d: ",i+1);
    //     scanf("%f",&items[i]);
    //}

    //printf("\nEnter discount: ");
    //scanf("%f",&discount);
    //printf("\n");
    //float discounted = (1 - discount/100);
    //for (int j = 0; j < 5; j++)
    //{
    //  price[j] =items[j] * discounted;
    //printf("Price %d:%.2f\n",j + 1,price[j]);
    //}

    // int value;
    // printf("Enter Value:");
    // scanf("%d",&value);
    // if (value %2 == 0)
    // {
    //     printf("You entered an even number\n");
    // }
    // else
    // {
    //     printf("You entered an odd number\n");
    // }

    // char colour,colour2;
    //
    // printf("Enter a Colour(Y,R,B):");
    // colour = getchar();
    // colour = toupper(colour);
    // getchar();
    //
    // if (colour == 'Y'||colour == 'R'||colour == 'B')
    // {
    //     printf("Enter a second colour:");
    //     colour2 = getchar();
    //     colour2 = toupper(colour2);
    //     getchar();
    //
    //     if (colour == 'Y'||colour == 'R'||colour == 'B')
    //     {
    //         if (colour == colour2)
    //         {
    //             printf("You enter same colour.\n");
    //         }
    //         else if(colour == 'Y'&& colour2 == 'R')
    //         {
    //             printf("Colour: Orange Colour\n");
    //         }
    //         else if(colour == 'Y'&& colour2 == 'B')
    //         {
    //             printf("Colour: Green Colour\n");
    //         }
    //         else if(colour == 'R'&& colour2 == 'B')
    //         {
    //             printf("Colour: Purple Colour\n");
    //         }
    //     }
    //     else
    //     {
    //         printf("Invalid:\n");
    //     }
    // }
    // else
    // {
    //     printf("Invalid.\n");
    // }

    // int num1,num2,num3,temp;
    //
    // printf("Enter number1: ");
    // scanf("%d", &num1);
    //
    // printf("Enter number2: ");
    // scanf("%d", &num2);
    //
    // printf("Enter number3: ");
    // scanf("%d", &num3);
    //
    // if (num1 > num2 && num2 >num3)//321
    // {
    //     num1 = num1;
    //     num2 = num2;
    //     num3 = num3;
    // }
    // else if (num3 > num2 && num3 >num1 && num2 >num1)//123
    // {
    //     temp = num1;
    //     num1 = num3;
    //     num2 = num2;
    //     num3 = temp;
    // }
    // else if (num3 > num1 && num2 < num1)//213
    // {
    //     temp = num1;
    //     num1 =num3;
    //     num3 = num2;
    //     num2 = temp;
    // }
    // else if (num1 > num2 && num2 < num3)//312
    // {
    //     num1 = num1;
    //     temp = num2;
    //     num2 = num3;
    //     num3 = temp;
    // }
    //
    // printf("Largest:%d\nMiddle:%d\nSmallest:%d\n",num1,num2,num3);

    // int m1,m2,m3,total_marks,final_exam;
    //
    // printf("Assigment mark (20%%):");
    // scanf("%d",&m1);
    // printf("Quizzes (10%%/2):");
    // scanf("%d",&m2);
    // printf("mid-Test (30%%):");
    // scanf("%d",&m3);
    //
    // total_marks = m1 + m2 + m3;
    //
    // if (total_marks >= 30 && total_marks <= 60)
    // {
    // printf("Total Coursework marks: %d%%\n",total_marks);
    //     printf("Enter Your Final Exam Mark (0-100%%):");
    //     scanf("%d",&final_exam);
    //
    //     int test_pass;
    //     test_pass = total_marks + final_exam;
    //
    //     if (test_pass < 0 && test_pass > 100)
    //     {
    //     printf("error");
    //     }
    //     else if ( test_pass>= 56)
    //     {
    //         printf("Your Final Exam result is %d%%\n",test_pass);
    //         if (test_pass >= 56 && test_pass <= 59)
    //         {
    //             printf("C+");
    //         }
    //         else if (test_pass >= 60 && test_pass <= 64)
    //         {
    //             printf("B-");
    //         }
    //         else if (test_pass >= 65 && test_pass <= 69)
    //         {
    //             printf("B");
    //         }
    //         else if (test_pass >= 70 && test_pass <= 74)
    //         {
    //             printf("B+");
    //         }
    //         else if (test_pass >= 75 && test_pass <= 79)
    //         {
    //             printf("A-");
    //         }
    //         else if (test_pass >= 80 && test_pass <= 89)
    //         {
    //             printf("A");
    //         }
    //         else
    //         {
    //             printf("A+");
    //         }
    //     }
    //     else
    //     {
    //         printf("You need to retake.");
    //     }
    // }
    // else if (total_marks < 30 && total_marks >= 0)
    // {
    // printf("You Can't Go to Exam.");
    // }
    // else
    // {
    //     printf("Error.");
    // }

    // for (int i = 5; 0 <= i; i--)
    // {
    //     for (int k = 0;k <= 5 - i;k++)
    //     {
    //         printf(" ");
    //     }
    //     for (int j = 0; j < i; j++)
    //     {
    //         printf("*");
    //     }
    //     printf("\n");
    // }

    // int input,total = 0,loop = 0;
    // float average = 0;
    // while (input > -1)
    // {
    //  printf("Pls Enter your input:");
    //     scanf("%d", &input);
    //     if (input >= 0)
    //     {
    //         total += input;
    //         loop++;
    //     }
    // }
    //
    // average = total;
    // average = average / loop;
    // printf("Your total is: %d\n", total);
    // printf("Your average is: %.2f\n",average);

    // int n,output = 1;
    //
    // printf("Enter the number:");
    // scanf("%d", &n);
    //
    // if (n < -1)
    // {
    //     printf("error\n");
    //     return 0;
    // }
    //
    // for (int i = 1; i <= n; i++)
    // {
    //     output *= i;
    // }
    //
    // printf("Factorial: %d\n", output);

    // int Fac_Rec (int n)
    // {
    //     if (n == 1)
    //     {
    //         return n;
    //     }
    //     else
    //     {
    //         return n*Fac_Rec(n-1);
    //     }
    // }

    // int a,b;
    //
    // printf("Enter number:");
    // scanf("%d %d",&a,&b);
    //
    // printf("You entered: %d, %d\n",a,b);
    // printf("Multiplication: %.2f\n",multiplication(a,b));
    // printf("Division:%.2f\n",division(a,b));

    // int lists[10],repeat,count = 0,total = 0,even = 0,odd = 0,positive = 0,negative = 0;
    //
    // for (int i = 0; i < 10; i++)
    // {
    //     printf("Enter a Number %d:",i+1);
    //     scanf("%d",&lists[i]);
    //     total += lists[i];
    // }
    // printf("\n");
    // for (int i = 0; i < 10; i++)
    // {
    //     printf("%d,%d\n",i+1,lists[i]);
    // }
    //
    // printf("\nEnter the value check repeatiton:");
    // scanf("%d",&repeat);
    //
    // for (int i = 0; i < 10; i++)
    // {
    //     if (lists[i] %2 ==0){even++;}else{odd++;}
    //     if (lists[i] >= 0){positive++;}else{negative++;}
    //     if (repeat == lists[i]){count++;}
    //     else if (count == 0){printf("\nNo Repeat\n");break;}
    // }
    // printf("Repeat:%d\n",count);
    // printf("Average:%.2f\n",(float)total/10);
    // printf("Even:%d Odd:%d\n",even, odd);
    // printf("Positive:%d Negative:%d\n",positive, negative);
    // for (int i = 0; i < 10; i++)
    // {
    //     if (lists[i] % 2 == 0 && lists[i] % 3 != 0){printf("%d ",lists[i]);}
    // }

    // int num[5],max = 0;
    // for (int i = 0; i < 5; i++)
    // {
    //     printf("Enter number %d: ", i+1);
    //     scanf("%d", &num[i]);
    //     if (num[i] >= max)
    //     {
    //         max = num[i];
    //     }
    // }
    // printf("\nMax number is %d", max);

    // int num,odd=0,turn = 0;
    //
    // while (turn != 6)
    // {
    //     printf("Please enter a number:");
    //     scanf("%d",&num);
    //     if (num % 2 != 0)
    //     {
    //         odd += num;
    //     }
    //     turn++;
    // }
    // printf("\nTotal Odd Number: %d",odd);

    // int num,total=0;
    // while (num > -1)
    // {
    //     printf("Enter number: ");
    //     scanf("%d", &num);
    //     if (num >= 0)
    //     {
    //         total += num;
    //     }
    // }
    // printf("Total = %d\n", total);

    // printf("Parking lot Management System\n");
    // printf("1.Enter Parking.\n2.Exit Parking.\n3.Check Available.\n");
    // printf("\nEnter your choice: ");
    // scanf("%d", &choice);
    // switch (choice)
    // {
    // case 1:parking_function();break;
    // }

// for (int i = 1;i <= 5;i++)
// {
//     for (int j = 5;j >= i;j--)
//     {
//         printf(" ");
//     }
//     for (int k = 1 ;k <= i;k++)
//     {
//         printf("* ");
//     }
//     printf("\n");
// }

    return 0;
}