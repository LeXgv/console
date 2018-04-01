#include "console.h"
#include <pthread.h>
Console::Console()
{


}

void Console::run()
{

/*Создать pipe, и два процесса. 
Родительский процесс перенаправит дескрипторы ввода и вывода в этот pipe. А дочерний процеесс будет принимать данный и управлять ими*/



}

void static Console::create()
{
	
	//Заблокируем для других нитей проход
	int err = pthread_mutex_trylock(&m);
	if(err == 0)
	{
		if(instance == nullptr)
		{
			instance = new Console;
			inctance.run();
		}
	}
	else
	{
		//Неканоничный режим консоли запущен или запускается
		return;
	}
	pthread_mutex_unlock(&m);

}
