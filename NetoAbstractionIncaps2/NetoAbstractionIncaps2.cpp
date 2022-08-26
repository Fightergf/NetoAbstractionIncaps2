#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>

class Address
{
private:
    std::string Country;
    std::string Street;
    int home;
    int room;
public:
    Address()
    {
        Country = "";
        Street = "";
        home = 0;
        room = 0;
    }
    Address(std::string Country, std::string Street, int home, int room)
    {
        this->Country = Country;
        this->Street = Street;
        this->home = home;
        this->room = room;
    }
    std::string get_output_address()
    {
        return Country + ", " + Street + ", " + std::to_string(home) + ", " + std::to_string(room);
    }  //Сборка строки
    void sortAdress(Address *arrADR, int countadr)
    {
        std::string* sM = new std::string[countadr];

        for (int i = 0; i < countadr; i++)
        {
            sM[i] = arrADR[i].get_output_address();
        }

        int res = 0;
        int listLength = countadr;

        while (listLength--) //Cортировка по алфавиту и сравнение строк
        {
            bool swapped = false;
            for (int i = 0; i < listLength; i++)
            {
                res = sM[i].compare(0, 2, sM[i + 1]); //Сравнение строк
                if (res == 1)
                {
                    std::swap(sM[i], sM[i + 1]);
                    swapped = true;
                }
            }
            if (swapped == false)
                break;
        }
        delete[] arrADR;
        writeFile(sM, countadr);
    }
    void writeFile(std::string *sM, int countadr) //Запись в файл
    {
        std::ofstream filew("out.txt");

        filew << countadr << "\n";

        for (int i = 0; i < countadr; i++) 
        {
            filew << sM[i] + "\n";
        }
        delete[] sM;  //Очистка массива строк
        std::cout << "Файл записан успешно, проверьте!!!";
    }
};

void out_file()
{
    std::ifstream filer("in.txt");

    std::string Country;
    std::string Street;
    int home = 0;
    int room = 0;
    int countAddress = 0;
    Address ADR;

    if (filer.is_open())
    {
        std::cout << "Файл успешно открыт!!!" << std::endl;
        filer >> countAddress;
        int iter = 0;
        std::cout << countAddress << "Адрессов в наличии!\n";

        Address* arrADR = new Address[countAddress]; //din memory struct

        for (int i = 0; i < countAddress; i++) //Внесение адресов в массив структур
        {
            filer >> Country;
            filer >> Street;
            filer >> home;
            filer >> room;
            arrADR[iter] = Address(Country, Street, home, room);
            iter++;
        }
        ADR.sortAdress(arrADR, countAddress);
    }
    else
    {
        std::cout << "Не получилось открыть файл!" << std::endl;
    }
    filer.close();
}


int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    out_file();

    return 0;
}
