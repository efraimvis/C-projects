#ifndef TIMEDATE_H
#define TIMEDATE_H

typedef struct TTIME 
{
    unsigned short hours;
    unsigned short minutes;
} Time;

typedef struct DDate 
{
    unsigned short year;
    unsigned short month;
    unsigned short day;
} Date;


/*Checks if given Time is valid
*
* time : given Time
*
* return : returns 1 if time is valid, 0 otherwise*/
int is_valid_time(Time time);

/*Check if given year is a leap year
*
* year : given year
*
* return : 1 if year is a leap year, 0 otherwise*/
int is_leap_year(unsigned short year);

/*Checks if given Date is valid
*
* date : given date
*
* return : returns 1 if date is valid, 0 otherwise*/
int is_valid_date(Date date);

/*Generates string representing given time, in format : hh:mm
*
* time : given Time
*
* return : returns string representing given time if operation succeeded, null otherwise*/
char* time_string(Time time);

/*Generates string representing given date, in format : dd:mm:yyyy
*
* date : given Date
*
* return : returns string representing given date if operation succeeded, null otherwise*/
char* date_string(Date date); 

/*Generates a default date
*
* returns the date 01/01/1886*/
Date default_date();

/*Generates a default time
*
* return the time 00:00*/
Time default_time();

/*Generates a date from given parameters
*
* year : given year
* month : given month
* day : given day
*
* returns date corresponding to parameters if that date is valid, default date otherwise*/
Date generate_date(unsigned short year, unsigned short month, unsigned short day);

/*Generates a time from given parameters
*
* hours : given hour component of time
* minutes : given minutes component of time
*
* returns time corresponding to parameters if that time is valid, default time otherwise*/
Time generate_time(unsigned short hours, unsigned short minutes);
#endif