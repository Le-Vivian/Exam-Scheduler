#include <stdio.h>
#include <string.h>
#include "040990185.h"

typedef unsigned long long int uLLInt;//create uLLInt using typedef 
const int rows=sizeof(examBookings)/sizeof(examBookings[0]);//size of the array(rows)
uLLInt binaryReservations[rows][2]={'\0'};//array to store number into 2 weeks 
uLLInt unBookedWeek[2]={'\0'};
int studentNumber=0;
int option=0, loop=0, week=0, startTime=0, endTime=0, duration=0, n=0, dayNum=0;
uLLInt unbookedTimesWeekOne = 0;
uLLInt unbookedTimesWeekTwo = 0;
char day[10];//string of days in week
int columns=sizeof(examBookings[0])/sizeof(examBookings[0][0]);
int availableDay[sizeof(examBookings)][5]={0};//final array used to print out unbooked days
//forward declaration
void displayStudentExamSchedule();
void displayUnbookedTimes();
void convertuLLIntToArray();
void setExamBookingTime();

int main (void){
    printf("\nExam Booking Software System\n");
    printf("\n");
    do{//loop to print menu
        printf("1. display a student's exam schedule\n"
            "2. load a new exam booking\n"  
            "3. find unbooked times\n"
            "4. exit\n");
    scanf("%d", &option);//get user choice
    switch(option){
        case 1:
        printf("Enter student number (0-728)");//get student number
        scanf("%d", &studentNumber);
        n=5;
        displayStudentExamSchedule(examBookings);//call function to print out student exam schedule
        printf("\n");
        break;
        case 2:
        setExamBookingTime();//call function to add on new exam time
        printf("\n");
        break;
        case 3:
        displayUnbookedTimes();//call function to get unbooked times
        printf("\n");
        break;
        case 4:
        printf("Exiting...");//exit
        loop = 1;
        break;
    }
    }while(loop==0);
}//end of main

void displayStudentExamSchedule(int array[][n]){
    for(int i=0; i<rows; i++){//loop through every rows of examBookins[][] array
            if (array[i][0]==studentNumber){
                if(array[i][1]==0){week=1;}//find week
                else{week=2;}
                dayNum=array[i][2];//find day
                if(dayNum==0){strcpy(&day,"Monday");}
                else if(dayNum==1){strcpy(&day,"Tuesday");}
                else if(dayNum==2){strcpy(&day,"Wednesday");}
                else if(dayNum==3){strcpy(&day,"Thursday");}
                else if(dayNum==4){strcpy(&day,"Friday");}
                else if(dayNum==5){strcpy(&day,"Saturday");}
                else if(dayNum==6){strcpy(&day,"Sunday");}
                startTime=array[i][3];//get start time
                duration=array[i][4];//get exam length
                endTime=duration+startTime;//end time of the exam
                if(startTime!=0){
                     printf("Week %d: %s %d:00 - %d:00\n", week, day, startTime, endTime);//print out the date and time
                }
               
            }
        }
}

void displayUnbookedTimes(){
    for (int i = 0; i < rows; i++)//loop through every rows of examBookings[][] array
    {
        uLLInt bitmask = 0xFFFFFFFFFFFFFFFF >> examBookings[i][4];//shift right n times (n=duration)
        bitmask = ~bitmask;//invert
        bitmask = bitmask >> (examBookings[i][2] * 8);//shift right based on the day of week 
        bitmask = bitmask >> (examBookings[i][3] - 9);//shift right based on the start time
        int studentNumber = examBookings[i][0];
        int weekNumber = examBookings[i][1];
        //OR all the bitmasks
        binaryReservations[studentNumber][weekNumber] = binaryReservations[studentNumber][weekNumber] | bitmask;
         
    }
    
    for (int i = 0; i < sizeof(binaryReservations) / sizeof(binaryReservations[0]); i++)
    {
        //seperate into 2 weeks
        unbookedTimesWeekOne = unbookedTimesWeekOne | binaryReservations[i][0];//week 1
        unbookedTimesWeekTwo = unbookedTimesWeekTwo | binaryReservations[i][1];//week 2
    }
   
   convertuLLIntToArray();//convert back
}
void convertuLLIntToArray(){
    int x=0;
    int unBookCount=0;
    int k=0;
    int tempArray[64][2]={'\0'};
   unBookedWeek[0]=unbookedTimesWeekOne;
   unBookedWeek[1]=unbookedTimesWeekTwo;
   int index=0;
   for(int i=0; i<2; i++){//loop twice forr 2 weeks 1,2
    while(unBookedWeek[i]>0){//convert to binary number
        tempArray[64-index][i]= unBookedWeek[i]%2;
        unBookedWeek[i]/=2;
        index++;
    }
    index=0;
    for(int j=0; j<7; j++){//7 days a week
    for(k=0; k<8;k++){//8 hours a day
        for(;k<8;k++){
           if(tempArray[k+(j*8)][i]==0){
            unBookCount++;//get duration of the exam
           }else
           break;
        }
        if(unBookCount>0){//if there's a exam booked
        availableDay[x][0]=0;//studeent number
        availableDay[x][1]=i;//week
        availableDay[x][2]=j;//day of week
        availableDay[x][3]=k-unBookCount+9;//start time
        availableDay[x][4]=unBookCount;//duration
        x++;
        unBookCount=0;//set back to 0
   }
    }
   }
   }
    n=5;
    studentNumber=0;
    displayStudentExamSchedule(availableDay);//print out all unbooked time 
}

void setExamBookingTime(){
  int studNum, weekNum, dayOfWeek, startTime, duration;
    uLLInt newExam = 0xFFFFFFFFFFFFFFFF;
                                                                    // Get Exam Data:
    printf("Enter a Student Number: ");                             // student number
    scanf("%d", &studNum);
    printf("Enter the exam week (0 or 1): ");                       // week of exam
    scanf("%d", &weekNum);
    printf("Enter exam day (0 = Monday, 1 = Tuesday, etc.): ");     // day of exam
    scanf("%d", &dayOfWeek);
    printf("Provide the start time for the exam (9-16): ");         // start time
    scanf("%d", &startTime);
    printf("Enter the duration of the exam: ");                     // duration
    scanf("%d", &duration);

    //shifting bitmask liike in function used for menu opition 3
    newExam >>= duration;
    newExam = ~newExam;
    newExam >>= (startTime - 9);
    newExam >>= (dayOfWeek * 8);

    uLLInt testNum;
    if (weekNum){
        testNum = unbookedTimesWeekTwo;
    }
    else {
        testNum = unbookedTimesWeekOne;
    }
    //find the last place in file to add data
    int i = 0;
    for ( ; i < rows ; i++){
        if (examBookings[i][4] == 0){
            break;
        }
    }

    uLLInt exclusiveCheck = testNum ^ newExam; 
    uLLInt regCheck = testNum | newExam;
    //Check that chosen time is free using test function
    if ( exclusiveCheck != regCheck){
        printf("That timeslot is not available.\n");
    }
    else {//if tiimeslot available
        examBookings[i][0] = studNum;
        examBookings[i][1] = weekNum;
        examBookings[i][2] = dayOfWeek;
        examBookings[i][3] = startTime;
        examBookings[i][4] = duration;
        printf("Timeslot was successfully booked.\n");
    }

    
}