#include <amtest.h>
#include <inttypes.h>
#include <stdint.h>

void rtc_test() {
  AM_TIMER_RTC_T rtc;
  AM_TIMER_EPOCH_T time_since_epoch;
  int sec = 1;
  while (1) {
    while(io_read(AM_TIMER_UPTIME).us / 1000000 < sec) ;
    rtc = io_read(AM_TIMER_RTC);
    printf("%d-%d-%d %02d:%02d:%02d GMT (", rtc.year, rtc.month, rtc.day, rtc.hour, rtc.minute, rtc.second);
    if (sec == 1) {
      printf("%d second).\n", sec);
    } else {
      printf("%d seconds).\n", sec);
    }
    sec ++;
    time_since_epoch = io_read(AM_TIMER_EPOCH);
    printf("Since epoch: %" PRIu64 " secs and %" PRIu64 " usecs\n", (uint64_t)time_since_epoch.sec, (uint64_t)time_since_epoch.usec);
  }
}
