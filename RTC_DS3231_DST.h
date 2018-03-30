#include <RTClib.h>

class RTC_DS3231_DST : public RTC_DS3231 {
	private:
		DateTime find_last_sunday_of(int y, int m, int h, int minute);
    	bool is_dst_period(DateTime date);

    // Overrides of super methods
	public:
    	DateTime now();
    	void adjust(const DateTime &date);
};

bool operator>(const DateTime &left, const DateTime &right);
void print(DateTime date);