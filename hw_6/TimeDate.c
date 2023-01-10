#include "TimeDate.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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
* return : 1 if year is a leap year, 0 if not, -1 on error (if year is invalid)*/
int is_leap_year(short year)
{
    if(year >= 1886 && year <= 9999)
    {
        if(year % 4 != 0) return 0;
        else if(year % 100 != 0) return 1;
        else if(year % 400 != 0) return 0;
        else return 1;
    }
    else return -1;
}

/*Checks if given Date is valid
*
* date : given date
*
* return : returns 1 if date is valid, 0 otherwise*/
int is_valid_date(Date date)
{
    if(date.year >= 1886 && date.year <=9999)
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
        char* timeString;
        timeString = (char*)malloc(6);
        if(timeString == NULL) return NULL;
        sprintf(timeString, "%02d:%02d",time.hours,time.minutes);
        return timeString;
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
        char* dateString;
        dateString = (char*)malloc(11);
        if(dateString == NULL) return NULL;
        sprintf(dateString, "%02d/%02d/%04d",date.day,date.month,date.year);
        return dateString;
    }
    return NULL;
}

/*Generates a default date
*
* returns the date 00/00/1885*/
Date default_date()
{
    Date date;
    date.year = 1885;
    date.month = 0;
    date.day = 0;
    return date;  
}

/*Generates a default time
*
* return the time -1:-1*/
Time default_time()
{
    Time time;
    time.hours = -1;
    time.minutes = -1;
    return time;
}

/*Generates a date from given parameters
*
* year : given year
* month : given month
* day : given day
*
* returns date corresponding to parameters if that date is valid, default date otherwise*/
Date generate_date(short year, short month, short day)
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
Time generate_time(short hours, short minutes)
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

/*Checks if two Dates are identical
*
* date1, date2 - given Dates
*
* returns 0 if dates are identical, negative value if date1 is earlier, positive value if date1 is later*/
int dateCompare(Date date1,Date date2)
{
    if(date1.year == date2.year)
    {
        if(date1.month == date2.month)
        {
            if(date1.day == date2.day) return 0;
            else return (date1.day-date2.day);
        }
        else return (date1.month-date2.month);
    }
    else return (date1.year-date2.year);
}

/*Checks if two Times are identical
*
* time1, time2 - given Times
*
* returns 0 if times are identical, negative value if time1 is earlier, positive value if time1 is later*/
int timeCompare(Time time1,Time time2)
{
    if(time1.hours == time2.hours)
    {
        if(time1.minutes == time2.minutes) return 0;
        else return (time1.minutes-time2.minutes);
    }
    else return (time1.hours-time2.hours);
}

/*Generates a Date from a given string representation
*
* date - given date string
*
* returns Date corresponding to given string if successful, default Date otherwise*/
Date dateFromString(char* date)
{
    if(date != NULL)
    {
        if(strlen(date) == 10)
        {
            if(date[2] == '/' && date[5] == '/')
            {
                Date newDate;
                char* day;
                char* month;
                char* year;
                int i;
                day = (char*)malloc(3);
                month = (char*)malloc(3);
                year = (char*)malloc(5);
                if(!day || !month || !year) return default_date();
                for(i=0;i<2;i++)
                {
                    day[i] = date[i];
                }
                day[2] = '\0';
                for(i=3;i<5;i++)
                {
                    month[i-3] = date[i];
                }
                month[2] = '\0';
                for(i=6;i<10;i++)
                {
                    year[i-6] = date[i];
                }
                year[5] = '\0';
                newDate = generate_date(atoi(year),atoi(month),atoi(day));
                free(day);
                free(month);
                free(year);
                day = month = year = NULL;
                return newDate;
            }
        }
    }
    return default_date();
}

/*Generates a Time from a given string representation
*
* time - given time string
*
* returns Time corresponding to given string if successful, default Time otherwise*/
Time timeFromString(char* time)
{
    if(time != NULL)
    {
        if(strlen(time) == 5)
        {
            if(time[2] == ':')
            {
                Time newTime;
                char* hours;
                char* minutes;
                int i;
                hours = (char*)malloc(3);
                minutes = (char*)malloc(3);
                if(!hours || !minutes) return default_time();
                for(i=0;i<2;i++)
                {
                    hours[i] = time[i];
                }
                hours[2] = '\0';
                for(i=3;i<5;i++)
                {
                    minutes[i-3] = time[i];
                }
                minutes[2] = '\0';
                newTime = generate_time(atoi(hours),atoi(minutes));
                free(hours);
                free(minutes);
                hours = NULL;
                minutes = NULL;
                return newTime;
            }
        }
    }
    return default_time();
}