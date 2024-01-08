#include "holidays.h"
#include "sys.h"
#include "rtc.h"
#include "display.h"

	/*
	 э = \xFD
	*/
	
bit holiday = 0; 

code char hd_01_01[] = "Новий рік!!!";
code char hd_01_22[] = "День соборності України";
code char hd_01_27[] = "Нінин день";
code char hd_02_14[] = "День Святого Валентина";
code char hd_02_16[] = "День єдності";
code char hd_02_28[] = "Даня пісос дн";
code char hd_04_01[] = "День сміху";
code char hd_04_02[] = "Світланин день";
code char hd_04_05[] = "Зайка ДН!!";
code char hd_04_26[] = "День памяті ЧАЕС";
code char hd_04_30[] = "День прикордонника";
code char hd_05_05[] = "Юра-гусь-мокриця дн";
code char hd_05_15[] = "День сімї";
code char hd_06_01[] = "День захисту дітей";
code char hd_06_28[] = "Мама дн День конституції";
code char hd_06_30[] = "Теща дн";
code char hd_07_15[] = "День Української Державності";
code char hd_07_23[] = "Софійка ДН";
code char hd_08_12[] = "День молоді";
code char hd_08_23[] = "День прапора";
code char hd_08_24[] = "День незалежності";
code char hd_09_01[] = "День знань";
code char hd_09_21[] = "День миру";
code char hd_09_24[] = "Тесть дн";
code char hd_09_30[] = "Софіїн день";
code char hd_10_01[] = "День захисників України";
code char hd_10_15[] = "Річниця весілля";
code char hd_10_27[] = "День Української мови";
code char hd_10_28[] = "День визволення від фашистів";
code char hd_11_08[] = "Михайлів день";
code char hd_11_17[] = "З днем народження!!!";
code char hd_11_28[] = "Вітаю з річницею!!!";
code char hd_12_02[] = "Льоха картоха дн";
code char hd_12_06[] = "День святого Миколая День ЗСУ";
code char hd_12_12[] = "Міланка дн";
code char hd_12_25[] = "Різдво Христове";
code char hd_12_31[] = "Щедрий вечір";

code char hd_256_day[] = "День программіста 505";
code char hd_05_02_SUN_matherday[] = "День матері";
code char hd_05_03_THU_vishivankaday[] = "День вишиванки";
code char hd_06_03_SUN_fatherday[] = "День батька";
code char hd_07_lastfriday[] = "День системного адміністратора";
code char hd_08_02_SUM_buildersday[] = "День будівельника";
code char hd_08_beerday[] = "Міжнародний день пива, будьмо ;)";
code char hd_10_01_SUN_educatorday[] = "День працівника освіти";
code char hd_11_04_SAT_holodomorsday[] = "День памяті жерт голодомору";

HOLIDAY code holidays[] = {
		hAN( 1, 1, hd_01_01),
		hAN( 1, 22, hd_01_22),
		hAN( 1, 27, hd_01_27),
		hAN( 2, 14, hd_02_14),
		hAN( 2, 16, hd_02_16),
		hAN( 2, 28, hd_02_28),
		hAN( 4, 1, hd_04_01),
		hAN( 4, 2,hd_04_02),
		hAN( 4, 5, hd_04_05),
		hAN( 4, 26, hd_04_26),
		hAN( 4, 30, hd_04_30),
		hAN( 5, 5, hd_05_05),
		hAN( 5, 15, hd_05_15),
		hAN( 6, 1, hd_06_01),
		hAN( 6, 28, hd_06_28),
		hAN( 6, 30, hd_06_30),
		hAN( 7, 15, hd_07_15),
		hAN( 7, 23, hd_07_23),
		hAN( 8, 12, hd_08_12),
		hAN( 8, 23, hd_08_23),
		hAN( 8, 24, hd_08_24),
		hAN( 9, 1, hd_09_01),
		hAN( 9, 21, hd_09_21),
		hAN( 9, 24, hd_09_24),
		hAN( 9, 30, hd_09_30),
		hAN( 10, 1, hd_10_01),
		hAN( 10, 15, hd_10_15),
		hAN( 10, 27, hd_10_27),
		hAN( 10, 28, hd_10_28),
		hAN( 11, 8, hd_11_08),
		hAN( 11, 17, hd_11_17),
		hAN( 11, 28, hd_11_28),
		hAN( 12, 2, hd_12_02),
		hAN( 12, 6, hd_12_06),
		hAN( 12, 12, hd_12_12),
		hAN( 12, 25, hd_12_25),
		hAN( 12, 31, hd_12_31),// місяць, день, подія
		hADN( 256, hd_256_day ), //день від початку року, подія
		hAWN( 5, W2, hd_05_02_SUN_matherday), //номер місяця, порядок тижня, день тижня, подія
		hAWN( 5, W3, hd_05_03_THU_vishivankaday),
		hAWN( 6, W3, hd_06_03_SUN_fatherday),
		hAWL( 7, FRY, hd_07_lastfriday), //остання неділя листопада місяць, день тижня, подія
		hAWN( 8, W2, SUN, hd_08_02_SUM_buildersday),
		hAWN( 8, W1, FRY, hd_08_beerday),
		hAWN( 10, W1, SUN, hd_10_01_SUN_educatorday),
		hAWN( 11, W4, SAT, hd_11_04_SAT_holodomorsday), 
};

uint8_t wdays[5];

void checkWeekDays(void)
{
	uint8_t i, t;
	int8_t w = rtc.wday;

	for( i = 0; i < 5; i++ ) {
		wdays[i] = 0;
	}
	w = rtc.date;
	while( w > 7 ) {
		w -=7;
	}
	t = rtcDaysInMonth();
	for( i = 0; (( i < 5 ) && ( w <= t )); i++, w+=7 ) {
		wdays[i] = w;
	}

	return;
}

bit checkLastWeek(void)
{
	if( wdays[W5] == 0 ) {
		if( wdays[W4] == rtc.date )
			return 1;
	}
	else {
		if( wdays[W5] == rtc.date )
			return 1;
	}

	return 0;
}

bit checkWeekDay(uint8_t weekly)
{
		return wdays[weekly] == rtc.date;
}

void checkHolidays(void)
{
	uint8_t i;

	holiday = 0;
	render_buffer_size = 0;

	checkWeekDays();

	for(i=0; (i < ELEMENTS(holidays)) && (holiday == 0); i++) {
		switch(( holidays[i].month & 0xF0) >> 4) {
			case 0: {
				if((holidays[i].day == rtc.date) && ((holidays[i].month & 0x0F) == rtc.month)) {
					holiday = 1;
					renderHoliday(holidays[i].length, holidays[i].ptr);
					break;
				}
				break;
			}
			case 1:
			case 2:
			case 3:
			case 4:
			case 5: {
				if(((holidays[i].month & 0x0F) == rtc.month)&&(rtc.wday == holidays[i].day)&&checkWeekDay((( holidays[i].month & 0x70) >> 4)-1)) {
					holiday = 1;
					renderHoliday(holidays[i].length, holidays[i].ptr);
				}
				break;
			}
			case 6: {
				if(rtcYearDay()==((((uint16_t)holidays[i].month & 0x01) << 8) | holidays[i].day)) {
					holiday = 1;
					renderHoliday(holidays[i].length, holidays[i].ptr);
				}
				break;
			}
			case 7: {
				if(((holidays[i].month & 0x0F) == rtc.month)&&(rtc.wday == holidays[i].day)&&checkLastWeek()) {
					holiday = 1;
					renderHoliday(holidays[i].length, holidays[i].ptr);
				}
				break;
			}
			default: {
				holiday = 0;
				render_buffer_size = 0;
			}
		}
	}

	return;
}
