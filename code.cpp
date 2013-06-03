#include <iostream> // Нужные классы
#include <fstream>
#include <stdlib.h> // Или stdio.h

using namespace std;

struct my_type // Структура для хранения переменных
{
  char ch[50]; // Имя переменной
	char nm[50]; // Значение переменной
};

   int step = 0; // Шаг выполнения программы
   char *url[1000]; // Массив переменных из адреса
   int url_count = 0; // Их количество
   my_type vars[999]; // Массив структур для хранения 999 переменных
   int vars_count = 0; // Их текущее количество
   
int str_to_int(char * str) // Функция конвертации переменных из *char в int
                           // Примитивно, зато понятно ;) 
    {
    int var = 0; int start = 0;
    if (str[0] == *"-") // Если первый знак "-", то число отрицательное
        {
        start = 1;
        }
    for (int i = start; i < strlen(str); ++i)
        {
                if (str[i] == *"0") {var = var*10 + 0; }
                if (str[i] == *"1") {var = var*10 + 1; }
                if (str[i] == *"2") {var = var*10 + 2; }
                if (str[i] == *"3") {var = var*10 + 3; }
                if (str[i] == *"4") {var = var*10 + 4; }
                if (str[i] == *"5") {var = var*10 + 5; }
                if (str[i] == *"6") {var = var*10 + 6; }
                if (str[i] == *"7") {var = var*10 + 7; }
                if (str[i] == *"8") {var = var*10 + 8; }
                if (str[i] == *"9") {var = var*10 + 9; }
        }
        if (start == 1)
                {
                var = -var;
                }
        return var;
    }

void exit_error(char * error, int line) // Функция вывода ошибок
    {
    cout << "<br><b>Fatal error: </b>" << error << " in line " << line << "<br>";
    }
    
my_type get_vars(char* somevar) /*
Очень юзабительная функция в нашем случае. В качестве параметре мы передаем 
указатель на строку вида: "var_name = value". Она же нам возвращает структуру
типа my_type и значениями my_type.nm и my_type.ch соответственно.
                                */
{
	int check = 0;
 	for (int i = 0; i < strlen(somevar); ++i)
		{ 
			if (somevar[i] == *"=" && check == 0)	
			{
				check = i;
			}
		}

	check += 2;
	
	char var[50], name[50];

	for (int i = 0; i <= check - 4; ++i)
		{
		name[i] = somevar[i];
		}
	name[check-4+1] = '\0';
	
	int len = strlen(somevar) - check;
	for (int i = 0; i <= len; ++i)	
		{
			var[i]   = somevar[check+i];
		}

	my_type vars;
	strcpy(vars.ch, var);
	strcpy(vars.nm, name);
	return vars;
}
    
bool like(char * str1, char * str2) // Сравнения двух строк
    {
    int likes = 0;
    for (int i = 0; i < strlen(str1); ++i)
        {
                if (str1[i] == str2[i]) 
                                {
                                ++likes; /* Если символы совпадают, то увеличиваем счетчик */
                                }
        }
        if (strlen(str1) == likes)
                {
                return TRUE;
                }
                else
                {
                return FALSE;
                }
    }
    
void show_var(char * var) // Вывести значение переменной по ее имени
    {
        if (var[0] == *"'") // Если первый символ "'", то получаем текст между скобками
                {
                for (int i = 1; i < strlen(var) - 1; ++i)
                                {
                                cout << var[i];
                                }
                }
                else
                {
        for (int i = 0; i < vars_count; ++i)
                {
                     if (like(var, vars[i].nm)) 
                                          {
                                          if (vars[i].ch[0] == *"'")
                                          {
                                                          for (int y = 1; y < strlen(vars[i].ch) - 1; ++y)
                                                          {
                                                          cout << vars[i].ch[y];
                                                          }
                                          }
                                          else
                                          {
                                          printf(vars[i].ch);
                                          }
                                          }          
                } 
                }
    }    

int main(int argc, char *argv[])
{
   printf("Content-type: text/html\n\n"); // Отправляем тип содержания страницы
   for (int i = 2; i < argc; ++i) // Получаем переменные из адреса
      {
      url[i-2] = argv[i];
      }
   url_count = argc-1;
   bool in_if = false;
   bool is_if = false;
   ifstream fin; // Обьекст класса ifstream для работы с файлами
   fin.open(argv[1]); // Открываем файл из второго аргумента, переданным apache.
   char buf[80]; // Буфер чтения файла
   int line = 0;
        while (fin.getline(buf, 80)) // Главный цикл 
                {
                 ++line; // Увеличиваем текущий номер линии
                 if (strlen(buf) == 0 || buf[0] == *"#") continue; // Если длина буфера пуста, переходим к след. шагу цикла
                 if (in_if) // Эта секция выполняеться после условия if
                                  {                                           
                                       if (!is_if)
                                          {
                                          is_if = false;
                                          in_if = false; 
                                           continue;
                                          }         
                                          else
                                          {
                                          is_if = false;
                                          in_if = false; 
                                          }            
                                  }
                 if (step == 3 && buf[0] != *"#") // Если мы на шаге чтения комманд, и это не комментарий
                                  {
                                  if (like("stop", buf)) // Если команда stop - выходим из цикла
                                     {
                                     break;
                                     }     
                                     else
                                     {
                                                       if (like("show", buf)) // Если команда show - выводим на экран
                                                       {
                                                       my_type bt = get_vars(buf); // Создаем тип и получем из буфера
                                                       show_var(bt.ch); // Выводим значение на екран
                                                       }    
                                                       else if (like("read", buf)) // Команда read - вывести содержимое файла
                                                          {
                                                             my_type tmp;
                                                             tmp = get_vars(buf);
                                                             int found = 0;
                                                             
                                                             /* Етим циклом ищем полученную переменную в массиве структур */
                                                               for (int i = 0; i < vars_count; ++i)
                                                                {
                                                                 if (like(tmp.ch, vars[i].nm) && (strlen(tmp.ch) == strlen(vars[i].nm)))
                                                                  {
                                                                   found = i;
                                                                  }          
                                                                } 
                                                                
                                                                
                                                       // Если переменная не найдена - сообщение об ошибке         
                                                       if (found == 0)
                                                       {
                                                         char err_text[100];
                                                         sprintf(err_text, "Error. Var <b>%s</b> is unknown", tmp.ch);
                                                         exit_error(err_text, line);     
                                                         break;           
                                                       } 
                                                       else
                                                       {
                                                       // Если все хорошо - читаем и выводим на экран содержимое файла
                                                        ifstream rff;
                                                             rff.open(vars[found].ch);
                                                             char buffer;
                                                             while (rff.get(buffer))
                                                                   {
                                                                     cout << buffer;
                                                                   }          
                                                             rff.close();   
                                                       }
                                                             
                                                             
                                                                 

                                                          }
                                                          
                                                          // Если команда - условие
                                                          else if (like("if", buf))
                                                          {

                                                             char f1[50], f2[50];
                                                             int count = -1;
                                                             bool can = true;
                                                             // Получаем имя переменной
                                                             for (int i = 3; i < strlen(buf); ++i)
                                                                {
                                                                if (buf[i] == *" " && can == true)
                                                                   {
                                                                     can = false;
                                                                   }
                                                                if (can == true)
                                                                   {
                                                                     ++count;
                                                                     f1[count] = buf[i];
                                                                   }
                                                                }
                                                                f1[++count] = '\0';

                                                                can = true;
                                                                int my_count = -1;
                                                                for (int i = count+4; i < strlen(buf); ++i)
                                                                {
                                                                if (buf[i] == *" " && can == true)
                                                                   {
                                                                     can = false;
                                                                   }
                                                                if (can == true)
                                                                   {
                                                                     ++my_count;
                                                                     f2[my_count] = buf[i];
                                                                   }
                                                                }
                                                                f2[++my_count] = '\0';
                                                                // Ищем переменные в массиве структур
                                                                int found = 0, found2 = 0;
                                                                for (int i = 0; i < vars_count; ++i)
                                                                {
                                                                 if (like(f1, vars[i].nm) && (strlen(f1) == strlen(vars[i].nm)))
                                                                  {
                                                                   found = i;
                                                                  }
                                                                }
                                                                // Ищем переменные в массиве структур
                                                                for (int i = 0; i < vars_count; ++i)
                                                                {
                                                                 if (like(f2, vars[i].nm) && (strlen(f2) == strlen(vars[i].nm)))
                                                                  {
                                                                   found2 = i;
                                                                  }
                                                                }
                                                                // Если не найдены
                                                                if (found == 0)
                                                                {
                                                                  char err_text[100];
                                                                  sprintf(err_text, "Error. Var now found", f1);
                                                                  exit_error(err_text, line);
                                                                  break;
                                                                }
                                                                // Если найдены
                                                                if (found2 != 0)
                                                                   {
                                                                     if (like(vars[found].ch, vars[found2].ch) && (strlen(vars[found].ch) == strlen(vars[found2].ch)) && strstr(vars[found].ch, vars[found2].ch))
                                                                        {
                                                                           in_if = true;
                                                                           is_if = true;
                                                                        }
                                                                        else
                                                                        {
                                                                           in_if = true;
                                                                           is_if = false;
                                                                        }
                                                                   }




                                                          }
                                                          // Если в строке имееться знак РАВНО.
                                                          // Это означает что сдесь есть математическое действие
                                                       else if (strstr(buf, "="))
                                                       {
                                                       my_type bt = get_vars(buf);
                                                       int found1 = 0; 
                                                       int found2 = 0;
                                                               // Ищем переменные в массиве структур
                                                               for (int i = 0; i < vars_count; ++i)
                                                                {
                                                                 if (like(bt.nm, vars[i].nm) && (strlen(bt.nm) == strlen(vars[i].nm))) 
                                                                  {
                                                                   found1 = i;
                                                                  }          
                                                                } 
                                                               // Ищем переменные в массиве структур
                                                               for (int i = 0; i < vars_count; ++i)
                                                                {
                                                                 if (like(bt.ch, vars[i].nm) && (strlen(bt.ch) == strlen(vars[i].nm))) 
                                                                  {
                                                                   found2 = i;
                                                                  }          
                                                                } 
                                                                
                                                       // Если не найдены - сообщаем об ошибке         
                                                       if (found1 == 0)
                                                       {
                                                       char err_text[100];
                                                       sprintf(err_text, "Error. Var <b>%s</b> is unknown", bt.nm);
                                                       exit_error(err_text, line);     
                                                       break;           
                                                       }         
                                                       if (found2 == 0)
                                                          {
                                                          // Если часть после РАВНО не переменная, 
                                                          // то просто делаем присваивание
                                                           strcpy(vars[found1].ch, bt.ch);
                                                          }                            
                                                          else
                                                          {
                                                          // Если же она переменная, то записываем
                                                          // ее значение
                                                           strcpy(vars[found1].ch, vars[found2].ch);
                                                          }                                 
                                                       
                                                       } 
                                                       // Операция получения переменных из адреса разделенных проблелами
                                                       // По их порядковому номеру
                                                       else if (like("get", buf))
                                                          {
                                                             char f1[50], f2[50];
                                                             int count = -1;
                                                             bool can = true;
                                                             for (int i = 4; i < strlen(buf); ++i)
                                                                {
                                                                if (buf[i] == *" " && can == true)
                                                                   {
                                                                     can = false;
                                                                   }
                                                                if (can == true)
                                                                   {   
                                                                     ++count;
                                                                     f1[count] = buf[i];                                                                
                                                                   }
                                                                }
                                                                f1[++count] = '\0';
                                                                
                                                                can = true;
                                                                int my_count = -1;
                                                                for (int i = count+5; i < strlen(buf); ++i)
                                                                {
                                                                if (buf[i] == *" " && can == true)
                                                                   {
                                                                     can = false;
                                                                   }
                                                                if (can == true)
                                                                   {   
                                                                     ++my_count;
                                                                     f2[my_count] = buf[i];                                                                
                                                                   }
                                                                }
                                                                f2[++my_count] = '\0';
                                                                
                                                                int found = 0;
                                                                for (int i = 0; i < vars_count; ++i)
                                                                {
                                                                 if (like(f1, vars[i].nm) && (strlen(f1) == strlen(vars[i].nm))) 
                                                                  {
                                                                   found = i;
                                                                  }          
                                                                } 
                                                                
                                                                // Если сама переменная не найдена
                                                                if (found == 0)
                                                                {                                                                
                                                                  char err_text[100];
                                                                  sprintf(err_text, "Error. Var <b>%s</b> is unknown", f1);
                                                                  exit_error(err_text, line);     
                                                                  break;           
                                                                }    
                                                                
                                                                
                                                                // Делаем из строки число
                                                                int num = str_to_int(f2);
                                                                num = num + 1;
                                                                
                                                                // Если число не найдено
                                                                if ((num > argc-1) || (num < 1))
                                                                {
                                                                  // То мы обнуляем переменную
                                                                  strcpy(vars[found].ch, "");     
                                                                }
                                                                else
                                                                {
                                                                 if (strlen(argv[num]) != 0)
                                                                  {
                                                                   // Если найдено, копируем ее значение
                                                                   strcpy(vars[found].ch, argv[num]);
                                                                  }
                                                                } 
                                                                
                                                          }  else if (like("plus", buf)) // Команда plus - сложение
                                                          {
                                                             char f1[50], f2[50];
                                                             int count = -1;
                                                             bool can = true;
                                                             // Блок получения переменных
                                                             for (int i = 5; i < strlen(buf); ++i)
                                                                {
                                                                if (buf[i] == *" " && can == true)
                                                                   {
                                                                     can = false;
                                                                   }
                                                                if (can == true)
                                                                   {
                                                                     ++count;
                                                                     f1[count] = buf[i];
                                                                   }
                                                                }
                                                                f1[++count] = '\0';

                                                                can = true;
                                                                int my_count = -1;
                                                                for (int i = count+6; i < strlen(buf); ++i)
                                                                {
                                                                if (buf[i] == *" " && can == true)
                                                                   {
                                                                     can = false;
                                                                   }
                                                                if (can == true)
                                                                   {
                                                                     ++my_count;
                                                                     f2[my_count] = buf[i];
                                                                   }
                                                                }
                                                                f2[++my_count] = '\0';
                                                                // Ищем переменные в массиве структур
                                                                int found = 0, found2 = 0;
                                                                for (int i = 0; i < vars_count; ++i)
                                                                {
                                                                 if (like(f1, vars[i].nm) && (strlen(f1) == strlen(vars[i].nm)))
                                                                  {
                                                                   found = i;
                                                                  }
                                                                }
                                                                // Ищем переменные в массиве структур
                                                                for (int i = 0; i < vars_count; ++i)
                                                                {
                                                                 if (like(f2, vars[i].nm) && (strlen(f2) == strlen(vars[i].nm)))
                                                                  {
                                                                   found2 = i;
                                                                  }
                                                                }
                                                                // Если не найдены - ошибка
                                                                if (found == 0)
                                                                {
                                                                  char err_text[100];
                                                                  sprintf(err_text, "Error. Var now found", f1);
                                                                  exit_error(err_text, line);
                                                                  break;
                                                                }
                                                                
                                                                // Найдены - производим математическую операцию
                                                                if (found2 != 0)
                                                                   {
                                                                     int v1 = str_to_int(vars[found].ch);
                                                                     int v2 = str_to_int(vars[found2].ch);
                                                                     v2 = v1 + v2;
                                                                     char result[100];
                                                                     sprintf(result, "%d", v2);
                                                                     strcpy(vars[found].ch, result);
                                                                   }



                                                          }   else if (like("minus", buf)) // Соответственно ;)
                                                          {
                                                             char f1[50], f2[50];
                                                             int count = -1;
                                                             bool can = true;
                                                             // Блок получения переменных
                                                             for (int i = 6; i < strlen(buf); ++i)
                                                                {
                                                                if (buf[i] == *" " && can == true)
                                                                   {
                                                                     can = false;
                                                                   }
                                                                if (can == true)
                                                                   {
                                                                     ++count;
                                                                     f1[count] = buf[i];
                                                                   }
                                                                }
                                                                f1[++count] = '\0';

                                                                can = true;
                                                                int my_count = -1;
                                                                for (int i = count+7; i < strlen(buf); ++i)
                                                                {
                                                                if (buf[i] == *" " && can == true)
                                                                   {
                                                                     can = false;
                                                                   }
                                                                if (can == true)
                                                                   {
                                                                     ++my_count;
                                                                     f2[my_count] = buf[i];
                                                                   }
                                                                }
                                                                f2[++my_count] = '\0';
                                                                // Ищем переменные в массиве структур
                                                                int found = 0, found2 = 0;
                                                                for (int i = 0; i < vars_count; ++i)
                                                                {
                                                                 if (like(f1, vars[i].nm) && (strlen(f1) == strlen(vars[i].nm)))
                                                                  {
                                                                   found = i;
                                                                  }
                                                                }
                                                                // Ищем переменные в массиве структур
                                                                for (int i = 0; i < vars_count; ++i)
                                                                {
                                                                 if (like(f2, vars[i].nm) && (strlen(f2) == strlen(vars[i].nm)))
                                                                  {
                                                                   found2 = i;
                                                                  }
                                                                }
                                                                // Если не найдены - ошибка
                                                                if (found == 0 || found2 == 0)
                                                                {
                                                                  char err_text[100];
                                                                  sprintf(err_text, "Error. Var now found", f1);
                                                                  exit_error(err_text, line);
                                                                  break;
                                                                }
                                                                // Найдены - делаем операцию
                                                                if (found2 != 0)
                                                                   {
                                                                     int v1 = str_to_int(vars[found].ch); // Из текста в число
                                                                     int v2 = str_to_int(vars[found2].ch); // Из текста в число
                                                                     v2 = v1 - v2; // Считаем
                                                                     char result[100];
                                                                     sprintf(result, "%d", v2); // Из числа - в текст
                                                                     strcpy(vars[found].ch, result); // Записываем данные в переменную
                                                                   }



                                                          }   else if (like("multi", buf)) // Умножение (полностью аналогично)
                                                          {
                                                             char f1[50], f2[50];
                                                             int count = -1;
                                                             bool can = true;
                                                             for (int i = 6; i < strlen(buf); ++i)
                                                                {
                                                                if (buf[i] == *" " && can == true)
                                                                   {
                                                                     can = false;
                                                                   }
                                                                if (can == true)
                                                                   {
                                                                     ++count;
                                                                     f1[count] = buf[i];
                                                                   }
                                                                }
                                                                f1[++count] = '\0';

                                                                can = true;
                                                                int my_count = -1;
                                                                for (int i = count+7; i < strlen(buf); ++i)
                                                                {
                                                                if (buf[i] == *" " && can == true)
                                                                   {
                                                                     can = false;
                                                                   }
                                                                if (can == true)
                                                                   {
                                                                     ++my_count;
                                                                     f2[my_count] = buf[i];
                                                                   }
                                                                }
                                                                f2[++my_count] = '\0';

                                                                int found = 0, found2 = 0;
                                                                for (int i = 0; i < vars_count; ++i)
                                                                {
                                                                 if (like(f1, vars[i].nm) && (strlen(f1) == strlen(vars[i].nm)))
                                                                  {
                                                                   found = i;
                                                                  }
                                                                }

                                                                for (int i = 0; i < vars_count; ++i)
                                                                {
                                                                 if (like(f2, vars[i].nm) && (strlen(f2) == strlen(vars[i].nm)))
                                                                  {
                                                                   found2 = i;
                                                                  }
                                                                }

                                                                if (found == 0 || found2 == 0)
                                                                {
                                                                  char err_text[100];
                                                                  sprintf(err_text, "Error. Var now found", f1);
                                                                  exit_error(err_text, line);
                                                                  break;
                                                                }

                                                                if (found2 != 0)
                                                                   {
                                                                     int v1 = str_to_int(vars[found].ch);
                                                                     int v2 = str_to_int(vars[found2].ch);
                                                                     double res = v1*v2;
                                                                     char result[100];
                                                                     sprintf(result, "%f", res);
                                                                     strcpy(vars[found].ch, result);
                                                                   }



                                                          }    else if (like("share", buf)) // Деление (полностью аналогично)
                                                          {
                                                             char f1[50], f2[50];
                                                             int count = -1;
                                                             bool can = true;
                                                             for (int i = 6; i < strlen(buf); ++i)
                                                                {
                                                                if (buf[i] == *" " && can == true)
                                                                   {
                                                                     can = false;
                                                                   }
                                                                if (can == true)
                                                                   {
                                                                     ++count;
                                                                     f1[count] = buf[i];
                                                                   }
                                                                }
                                                                f1[++count] = '\0';

                                                                can = true;
                                                                int my_count = -1;
                                                                for (int i = count+7; i < strlen(buf); ++i)
                                                                {
                                                                if (buf[i] == *" " && can == true)
                                                                   {
                                                                     can = false;
                                                                   }
                                                                if (can == true)
                                                                   {
                                                                     ++my_count;
                                                                     f2[my_count] = buf[i];
                                                                   }
                                                                }
                                                                f2[++my_count] = '\0';
                                                                
                                                                int found = 0, found2 = 0;
                                                                for (int i = 0; i < vars_count; ++i)
                                                                {
                                                                 if (like(f1, vars[i].nm) && (strlen(f1) == strlen(vars[i].nm)))
                                                                  {
                                                                   found = i;
                                                                  }
                                                                }

                                                                for (int i = 0; i < vars_count; ++i)
                                                                {
                                                                 if (like(f2, vars[i].nm) && (strlen(f2) == strlen(vars[i].nm)))
                                                                  {
                                                                   found2 = i;
                                                                  }
                                                                }

                                                                if (found == 0 || found2 == 0)
                                                                {
                                                                  char err_text[100];
                                                                  sprintf(err_text, "Error. Var now found", f1);
                                                                  exit_error(err_text, line);
                                                                  break;
                                                                }

                                                                if (found2 != 0)
                                                                   {
                                                                     int v1 = str_to_int(vars[found].ch);
                                                                     int v2 = str_to_int(vars[found2].ch);
                                                                     double res = v1/v2;
                                                                     char result[100];
                                                                     sprintf(result, "%f", res);
                                                                     strcpy(vars[found].ch, result);
                                                                   }



                                                          }
                                                                                                                 
                                     }                             
                                  }
                 if (step == 2 && buf[0] != *"#") // Если шаг поиска переменных
                                  {
                                  if (like("start", buf)) // Если находим start
                                     {
                                     step = 3;
                                     }
                                     else {
                                  if (strstr(buf, "=") == FALSE) // На шаге 2 после поиска команды var мы ищем переменные
                                      {
                                         exit_error("Error. Invalid var.", line);     
                                         break;                              
                                      }
                                      else
                                      {
                                         vars[vars_count] = get_vars(buf);
                                         ++vars_count;                       
                                      }    
                                          }
                                  }
                 if (step == 1 && buf[0] != *"#") // Ищем слово var
                                  {
                                  if (like("var", buf) == FALSE)
                                      {
                                         exit_error("Vars not found", line);     
                                         break;                              
                                      }
                                      else
                                      {
                                         step = 2;                        
                                      }    
                                  }
                 if (step == 0 && buf[0] != *"#") // Ищем название программы
                                  {
                                  if (like("pragma", buf) == FALSE)
                                      {
                                         exit_error("Pragma name not found", line);     
                                         break;                              
                                      }
                                      else
                                      {
                                         vars[vars_count] = get_vars(buf);
                                         ++vars_count;
                                         step = 1;                              
                                      }    
                                  }
                }
   fin.close(); // Закрываем файл
  return 0;
}
