#include "TimeDate.h"
#include <stdio.h>


/*Checks if given Time is valid
*
* time : given Time
*
* return : returns 1 if time is valid, 0 otherwise*/
int is_valid_time(Time time)
{
    if(time.hours >= 0 && time.hours <= 23)
    {
        if(time.minutes >= 0 && time.minutes <= 59) return 1;
    }
    return 0;
}

/*Check if given year is a leap year
*
* year : given year
*
* return : 1 if year is a leap year, 0 otherwise*/
int is_leap_year(unsigned short year)
{
    if(year % 4 != 0) return 0;
    else if(year % 100 != 0) return 1;
    else if(year % 400 != 0) return 0;
    else return 1;
}

/*Checks if given Date is valid
*
* date : given date
*
* return : returns 1 if date is valid, 0 otherwise*/
int is_valid_date(Date date)
{
    if(date.year >= 1886)
    {
        if(date.month >= 1 && date.month <= 12)
        {
            if((date.month == 1) || (date.month == 3) || (date.month == 5) || (date.month == 7) || (date.month == 8) || (date.month == 10) || (date.month == 12))
            {
                if(date.day >= 1 && date.day <= 31) return 1;
            }
            else if((date.month == 4) || (date.month == 6) || (date.month == 9) || (date.month == 11))
            {
                if(date.day >= 1 && date.day <= 30) return 1;
            }
            else
            {
                if(is_leap_year(date.year))
                {
                    if(date.month == 2)
                    {
                        if(date.day >= 1 && date.day <= 29) return 1;
                    }
                }
                else
                {
                    if(date.month == 2)
                    {
                        if(date.day >= 1 && date.day <= 28) return 1;
                    }
                }
            }
        }
    }
    return 0;
}

/*Generates string representing given time, in format : hh:mm
*
* time : given Time
*
* return : returns string representing given time if operation succeeded, null otherwise*/
char* time_string(Time time)
{
    if(is_valid_time(time))
    {
        char time_str[6];
        char *s_ptr;
        sprintf(time_str, "%02d:%02d",time.hours,time.minutes);
        s_ptr = time_str;
        return s_ptr;
    }
    return NULL;
}

/*Generates string representing given date, in format : dd:mm:yyyy
*
* date : given Date
*
* return : returns string representing given date if operation succeeded, null otherwise*/
char* date_string(Date date)
{
    if(is_valid_date(date))
    {
        char date_str[12];
        char *s_ptr;
        sprintf(date_str, "%02d:%02d:%04d",date.day,date.month,date.year);
        s_ptr = date_str;
        return s_ptr;
    }
    return NULL;
}

/*Generates a default date
*
* returns the date 01/01/1886*/
Date default_date()
{
    Date date;
    date.year = 1886;
    date.month = 1;
    date.day = 1;
    return date;  
}

/*Generates a default time
*
* return the time 00:00*/
Time default_time()
{
    Time time;
    time.hours = 0;
    time.minutes = 0;
    return time;
}

/*Generates a date from given parameters
*
* year : given year
* month : given month
* day : given day
*
* returns date corresponding to parameters if that date is valid, default date otherwise*/
Date generate_date(unsigned short year, unsigned short month, unsigned short day)
{
    Date date;
    date.year = year;
    date.month = month;
    date.day = day;
    if(is_valid_date(date))
    {
        return date;
    }
    return default_date();
}

/*Generates a time from given parameters
*
* hours : given hour component of time
* minutes : given minutes component of time
*
* returns time corresponding to parameters if that time is valid, default time otherwise*/
Time generate_time(unsigned short hours, unsigned short minutes)
{
    Time time;
    time.hours = hours;
    time.minutes = minutes;
    if(is_valid_time(time))
    {
        return time;
    }
    return default_time();
}