/************************************************************************
 *  Copyright (c) 2003, Arabeyes, Thamer Mahmoud
 *
 *  A full featured Muslim Prayer Times calculator
 *
 *  NOTE: This is a small example that uses the prayer.h. For more info on
 *  filling the structures and on supported methods read "prayer.h"
 *
 * (www.arabeyes.org - under LGPL license - see COPYING file)
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "prayer.h"
#include <time.h>
#include <getopt.h>


// no bool in C, made our own
typedef int bool;
#define TRUE 1
#define FALSE 0

// logic values for printing info in console
bool PRINT_LOCATION = FALSE;
bool PRINT_TODAY = FALSE;
bool PRINT_TOMORROW = FALSE;
bool PRINT_QIBLA = FALSE;
bool PRINT_TODAY_DATE = FALSE;

// logic for calculation method
int CALC_METHOD = 4;


static void displayTimes(double lat, double lon, char *cityName, int day, int month, int year, int gmtDiff, int dst,
                         int method);

void print_options() {
    printf("Salat times app\n");
    printf("Usage:\n\tprayer [options]\n");

    printf("Options:\n"
                   "\t -l, --location\t\tPrint location for computed prayer times\n"
                   "\t -t, --today\t\tPrint today's date\n"
                   "\t -r, --tomorrow\t\tPrint tomorrows prayer times\n"
                   "\t -q, --qibla\t\tPrint the direction of the Qibla\n"
                   "\t -h, --help\t\tHelp\n"
                   "\t -a, --all\t\tPrint everything\n"
                   "\t -T, --type, \t\tCalculation method\n"

                   "\n\n\nOptions for calculation method:\n"
                   "\n *** NOTE: NEED TO CALL -T FIRST BEFORE -t ****"
                   "\t -T, --type\t\tSet calculation method\n\n"


                   "       \t : none. Set to default or 0\n"
                   "       \t1: Egyptian General Authority of Survey\n"
                   "       \t2: University of Islamic Sciences, Karachi (Shaf'i)\n"
                   "       \t3: University of Islamic Sciences, Karachi (Hanafi)\n"
                   "       \t4: Islamic Society of North America\n"
                   "       \t5: Muslim World League (MWL)\n"
                   "       \t6: Umm Al-Qurra, Saudi Arabia\n"
                   "       \t7: Fixed Ishaa Interval (always 90)\n"
                   "       \t8: Egyptian General Authority of Survey (Egypt)\n"
                   "       \t9: Umm Al-Qurra Ramadan, Saudi Arabia\n"
                   "      \t10: Moonsighting Committee Worldwide\n"
                   "      \t11: Morocco Awqaf, Morocco\n"


    );

}


int main(int argc, char *argv[]) {

    int c;


    // compute time
    time_t rawtime;
    struct tm *timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);


    while (1) {
        static struct option long_options[] = {

                {"location", no_argument,       0, 'l'},
                {"today",    no_argument,       0, 't'},
                {"tomorrow", no_argument,       0, 'r'},
                {"qibla",    no_argument,       0, 'q'},
                {"help",     no_argument,       0, 'h'},
                {"all",      no_argument,       0, 'a'},
                {"type",     required_argument, 0, 'T'},
                {0, 0,                          0, 0}


        };
        /* getopt_long stores the option index here. */
        int option_index = 0;

        c = getopt_long(argc, argv, "ltrqhaT:", long_options, &option_index);

        /* Detect the end of the options. */
        if (c == -1)
            //print_options();
            break;

        switch (c) {

            case 0:
                /* If this option set a flag, do nothing else now. */
                if (long_options[option_index].flag != 0)
                    break;
                printf("option %s", long_options[option_index].name);
                if (optarg)
                    printf(" with arg %s", optarg);
                printf("\n");
                break;


            case 'l':
                PRINT_LOCATION = TRUE;
                goto print;
            case 't':
                PRINT_TODAY_DATE = TRUE;
                goto print;
            case 'r':
                PRINT_TOMORROW = TRUE;
                goto print;
            case 'q':
                PRINT_QIBLA = TRUE;
                goto print;
            case 'h':
                print_options();
                break;

            case 'a':
                PRINT_TODAY_DATE = TRUE;
                PRINT_LOCATION = TRUE;
                PRINT_TOMORROW = TRUE;
                PRINT_QIBLA = TRUE;
                goto print;

            case 'T':
                CALC_METHOD = *optarg - 48;
                //printf("%d:\n",CALC_METHOD);
                goto print;

            print:
                displayTimes(33.755, -84.39, "Atlanta, GA", timeinfo->tm_mday, timeinfo->tm_mon + 1,
                             timeinfo->tm_year + 1900, -4, timeinfo->tm_isdst, CALC_METHOD);
                //displayTimes(33.7981, -84.3877, "Atlanta, GA", 29, 10, 2015, -4, 1, CALC_METHOD);
                break;

            default:

                print_options();
                break;


        }


    }




//    displayTimes(24.4833, 54.35, "Abu Dhabi", 3, 9, 2014, 4, 0, 7);
//    printf("Verified times for Abu Dhabi on 3/ 9/2014\n4:38:32    6:03:14   12:20:52   15:49:22   18:38:09   20:08:09\n");
//
//    displayTimes(51.500152, -0.126236, "London", 1, 1, 2014, 0, 0, 10);
//    printf("Verified times for London on 1/ 1/2014\n6:24:53    8:04:53   12:07:53   13:44:04   16:04:05   17:38:05\n");
//
//    displayTimes(24.671978, 46.675415, "Riyadh", 3, 9, 2014, 3, 0, 6);
//    printf("Verified times for Riyadh on 3/ 9/2014\n4:15:56    5:33:49   11:51:34   15:20:16   18:08:57   19:38:57\n");
//    time_t mytime;
//    mytime = time(NULL);
//    printf(ctime(&mytime));

    //printf("[%d %d %d %d:%d:%d]",timeinfo->tm_mday, timeinfo->tm_mon + 1, timeinfo->tm_year + 1900, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);

//        displayTimes(33.755, -84.39, "Atlanta, GA", timeinfo->tm_mday, timeinfo->tm_mon + 1, timeinfo->tm_year + 1900,
//                     timeinfo->tm_gmtoff - 4, 0, 4);

    return 0;
}

static void displayTimes(double lat, double lon, char *cityName, int day, int month, int year, int gmtDiff, int dst,
                         int method) {
    int i, deg, min;
    double sec;
    const char symb = (char) 0x00B0;
    double qibla;

    Location loc;
    Method conf;
    Date date;

    Prayer ptList[6];
    Prayer imsaak;
    Prayer nextImsaak;
    Prayer nextFajr;

    /* fill the Date structure */
    date.day = day;
    date.month = month;
    date.year = year;
    /* fill the location info. structure */
    loc.degreeLat = lat;
    loc.degreeLong = lon;
    loc.gmtDiff = gmtDiff;
    loc.dst = dst;
    loc.seaLevel = 800;
    loc.pressure = 1010;
    loc.temperature = 10;


    /* auto fill the method structure. Have a look at prayer.h for a
     * list of supported methods */

    getMethod(method, &conf);
    conf.round = 0;

    /* Call the main function to fill the Prayer times array of
     * structures */
    getPrayerTimes(&loc, &conf, &date, ptList);

    /* Call functions for other prayer times and qibla */
    getImsaak(&loc, &conf, &date, &imsaak);
    getNextDayFajr(&loc, &conf, &date, &nextFajr);
    getNextDayImsaak(&loc, &conf, &date, &nextImsaak);
    qibla = getNorthQibla(&loc);

    if (PRINT_TODAY_DATE) {

        PRINT_TODAY_DATE = FALSE;
        printf("Prayer schedule for: %2d/%2d/%4d\n", date.day, date.month, date.year);


        for (i = 0; i < 6; i++)
            if (ptList[i].hour < 12) {
                printf("\n%3d:%02d:%02d%s%c", ptList[i].hour - 1, ptList[i].minute, ptList[i].second, " am",
                       (ptList[i].isExtreme) ? '*' : ' ');

            }
            else {

                if (ptList[i].hour == 13) {
                    printf("\n%3d:%02d:%02d%s%c", 12, ptList[i].minute, ptList[i].second, " pm",
                           (ptList[i].isExtreme) ? '*' : ' ');
                }
                else {


                    printf("\n%3d:%02d:%02d%s%c", ptList[i].hour - 13, ptList[i].minute, ptList[i].second, " pm",
                           (ptList[i].isExtreme) ? '*' : ' ');
                }

            }

    }

    /* Show the results */
    if (PRINT_LOCATION) {
        // reset bool
        PRINT_LOCATION = FALSE;

        printf("\nPrayer schedule for: %s ", cityName);

        decimal2Dms(loc.degreeLat, &deg, &min, &sec);
        printf("\nLatitude\t=  %d%c %2d\' %4.1f\" %c", abs(deg), symb, abs(min),
               fabs(sec), (loc.degreeLat >= 0) ? 'N' : 'S');

        decimal2Dms(loc.degreeLong, &deg, &min, &sec);
        printf("\nLongitude\t=  %d%c %d\' %4.1f\" %c", abs(deg), symb, abs(min),
               fabs(sec), (loc.degreeLong >= 0) ? 'E' : 'W');
    }
    if (PRINT_QIBLA) {
        // reset bool
        PRINT_QIBLA = FALSE;
        decimal2Dms(qibla, &deg, &min, &sec);
        printf("\nQibla\t\t=  %d%c %d\' %4.1f\" %c of true North\n", abs(deg), symb,
               abs(min), fabs(sec), (qibla >= 0) ? 'W' : 'E');

        printf("\n\n");
    }


    printf("\n\n");

    if (PRINT_TOMORROW) {
        // reset bool
        PRINT_TOMORROW = FALSE;

        printf("Tomorrow's Fajr:\t%3d:%02d\n", nextFajr.hour - 1, nextFajr.minute);
        printf("Tomorrow's Imsaak:\t%3d:%02d\n", nextImsaak.hour - 1, nextImsaak.minute);
        printf("Today's Imsaak:\t\t%3d:%02d\n\n", imsaak.hour - 1, imsaak.minute);
    }
}
