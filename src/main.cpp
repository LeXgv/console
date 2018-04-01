#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <termios.h>// Функции работы с настройками терминала

static struct termios stored_settings;

void set_keypress(void)
{
	struct termios new_settings;// структура настроек терминала

	tcgetattr(0,&stored_settings);//получение текущих настроик териминала
	//текущие настройки терминала мы немного видо изменим
	new_settings = stored_settings;
	/*ICANON - канонический режим работы <- Отключим его
	Отключение данного режима приводит к тому, что набираемые символы сразу же отправлются в программу
	Нет ожидания нажатия кнопки Enter;
	ECHO - печать набираемых символов <- отключим*/
	new_settings.c_lflag &= (~ICANON & ~ECHO);
	new_settings.c_cc[VTIME] = 0; //Время ожидания ввода для неканонического ввода (Ввода без потверждения)
	new_settings.c_cc[VMIN] = 1;//Минимальное количесвто символов для не кананического ввода

	tcsetattr(0,TCSANOW,&new_settings);//Установка атрибутов
	return;
}

void reset_keypress(void)
{
	tcsetattr(0,TCSANOW,&stored_settings);//восстановление исходиных настроек консоли
	return;
}

int main(void) 
{
	fd_set rfds;
	struct timeval tv;
	int retval;
	
	set_keypress();

	while(1)
	{
		FD_ZERO(&rfds);
		FD_SET(0, &rfds);
		
		tv.tv_sec = 0;
		tv.tv_usec = 0;	
		retval = select(2, &rfds, NULL, NULL, &tv);
		if (retval)
		{
			printf("Data is available now.\n");
			int sym_code = getc(stdin);
			printf("symbole code: %d \n\n", sym_code);
		} 
		usleep(100000);
	}
	reset_keypress();
	exit(0);
}
