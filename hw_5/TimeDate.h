#ifndef TIMEDATE_H
#define TIMEDATE_H

typedef struct TTIME 
{
    short hours;
    short minutes;
} Time;

typedef struct DDate 
{
    short year;
    short month;
    short day;
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
int is_leap_year(short year);

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
Date generate_date(short year, short month, short day);

/*Generates a Date from a given string representation
*
* date - given date string
*
* returns Date corresponding to given string if successful, default Date otherwise*/
Date dateFromString(char* date);

/*Generates a time from given parameters
*
* hours : given hour component of time
* minutes : given minutes component of time
*
* returns time corresponding to parameters if that time is valid, default time otherwise*/
Time generate_time(short hours, short minutes);

/*Generates a Time from a given string representation
*
* time - given time string
*
* returns Time corresponding to given string if successful, default Time otherwise*/
Time timeFromString(char* time);

/*Checks if two Dates are identical
*
* date1, date2 - given Dates
*
* returns 1 if two Dates are identical, 0 otherwise*/
int dateCompare(Date date1,Date date2);

/*Checks if two Times are identical
*
* time1, time2 - given Times
*
* returns 1 if two Times are identical, 0 otherwise*/
int timeCompare(Time time1,Time time2);
#endif