/*
 * clock.c:
 ***********************************************************************
 *	Gordon Henderson, January 2013, <projects@drogon.net>
 ***********************************************************************
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <math.h>

#include <wiringPi.h>
#include <lcd128x64.h>

#ifndef	TRUE
#  define	TRUE	(1==1)
#  define	FALSE	(1==2)
#endif


double clockRadius ;
double thickness, barLen ;
int maxX, maxY ;

double rads (double degs)
{
  return degs * M_PI / 180.0 ;
}

void drawClockHands (void)
{
  time_t t ;
  struct tm *now ;
  double angle, p, x0, y0, x1, y1 ;
  int h24, h, m, s ;
  char text [20] ;

  time (&t) ;
  now = localtime (&t) ;

  h24 = now->tm_hour ;
  m   = now->tm_min ;
  s   = now->tm_sec ;

  h = h24 ;
  if (h > 12)
    h -= 12 ;

// Hour hand

  angle = h * 30 + m * 0.5 ;
  x0 = sin (rads (angle)) * (clockRadius * 0.75) ;
  y0 = cos (rads (angle)) * (clockRadius * 0.75) ;
  for (p = -3.0 ; p <= 3.0 ; p += 0.2)
  {
    x1 = sin (rads (angle + p)) * (clockRadius * 0.7) ;
    y1 = cos (rads (angle + p)) * (clockRadius * 0.7) ;
    line (0, 0, x1, y1, 1) ;
    lineTo (x0, y0, 1) ;
  }

// Minute hand

  angle = m * 6 ;
  x0 = sin (rads (angle)) * (clockRadius * 0.9) ;
  y0 = cos (rads (angle)) * (clockRadius * 0.9) ;
  for (p = -1.0 ; p <= 1.0 ; p += 0.2)
  {
    x1 = sin (rads (angle + p)) * (clockRadius * 0.85) ;
    y1 = cos (rads (angle + p)) * (clockRadius * 0.85) ;
    line (0, 0, x1, y1, 1) ;
    lineTo (x0, y0, 1) ;
  }

// Second hand

  angle = s * 6 ;
  x0 = sin (rads (angle)) * (clockRadius * 0.2) ;
  y0 = cos (rads (angle)) * (clockRadius * 0.2) ;
  x1 = sin (rads (angle)) * (clockRadius * 0.95) ;
  y1 = cos (rads (angle)) * (clockRadius * 0.95) ;
  line (0 - x0, 0 - y0, x1, y1, 1) ;
  circle (0, 0, clockRadius * 0.1,  0, 1) ;
  circle (0, 0, clockRadius * 0.05, 1, 1) ;

// Text:

  sprintf (text, "%02d:%02d:%02d", h24, m, s) ;
//  puts22 (-32, 20, text, C_BLACK, C_PURPLE) ;
}

void drawClockFace (void)
{
  int m ;
  double d, px1, py1, px2, py2 ;

  clear (0) ;
  circle (0,0, clockRadius, 1, TRUE) ;
  circle (0,0, clockRadius - thickness, 0, TRUE) ;

// The four big indicators for 12,15,30 and 45

  rectangle (- 3,  clockRadius - barLen, 3,  clockRadius,     1, TRUE) ;	// 12
  rectangle (clockRadius - barLen, 3,  clockRadius, -3, 1, TRUE) ;	// 3
  rectangle (- 3, -clockRadius + barLen, 3, -clockRadius, 1, TRUE) ;	// 6
  rectangle (-clockRadius + barLen, 3, -clockRadius, -3, 1, TRUE) ;	// 9


// Smaller 5 and 1 minute ticks

  for (m = 0 ; m < 60 ; ++m)
  {
    px1 = sin (rads (m * 6)) * clockRadius ;
    py1 = cos (rads (m * 6)) * clockRadius ;
    if ((m % 5) == 0)
      d = barLen ;
    else 
      d = barLen / 2.0 ;

    px2 = sin (rads (m * 6)) * (clockRadius - d) ;
    py2 = cos (rads (m * 6)) * (clockRadius - d) ;
    line (px1, py1, px2, py2, 1) ;
  }
}

void setup (void)
{
  getScreenSize (&maxX, &maxY) ;
  clockRadius = maxY / 2 - 1 ;
  thickness = maxX / 48 ;
  barLen = thickness * 4 ;
  setOrigin (maxX / 2, maxY / 2) ;
}




/*
 ***********************************************************************
 * The main program
 ***********************************************************************
 */

int main (int argc, char *argv [])
{
  time_t now ;

/*
  if (wiringPiSetup () == -1)
    { fprintf (stderr, "%s: Unable to initialise wiringPi: %s\n", argv [0], strerror (errno)) ; return 1 ; }
*/

  lcd128x64Setup () ;

  setup () ;
  for (;;)
  {
    drawClockFace  () ;
    drawClockHands () ;
    lcd128x64Update () ;

    now = time (NULL) ;
    while (time (NULL) == now)
      delay (10) ;
  }
  

  return 0 ;
}
