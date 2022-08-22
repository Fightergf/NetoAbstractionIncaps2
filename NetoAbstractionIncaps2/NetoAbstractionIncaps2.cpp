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
};

int out_file(Address* arrADR)
{
    std::ifstream filer("in.txt");
    std::string Country;
    std::string Street;
    int home = 0;
    int room = 0;
    int countAddress = 0;

    if (filer.is_open())
    {
        std::cout << "Файл успешно открыт!!!" << std::endl;
        filer >> countAddress;
        int iter = 0;
        std::cout << countAddress << "\n";

        for (int i = 0; i < countAddress; i++) //Внесение адресов в массив структур
        {
            filer >> Country;
            filer >> Street;
            filer >> home;
            filer >> room;
            arrADR[iter] = Address(Country, Street, home, room);
            iter++;
        }
    }
    else
    {
        std::cout << "Не получилось открыть файл!" << std::endl;
    }
    filer.close();
    return countAddress;
}

void writeFile(Address *arrADR, int countadr)
{
    std::ofstream filew("out.txt");

    std::string s1; //= arrADR[0].get_output_address(); А если будет больше адресов? как возможно сделать?
    std::string s2; //= arrADR[1].get_output_address(); не обьявлять же 100 переменных (строк)
    std::string s3; //= arrADR[2].get_output_address();
    std::string s4; //= arrADR[3].get_output_address();
    std::string s5; //= arrADR[4].get_output_address();

    std::string sM[5] = {s1, s2, s3, s4, s5}; //Массив строк

    for (int i = 0; i < countadr - 1; i++) //Перенос из массива структур в массивы строк
    {
        sM[i+1] = arrADR[i].get_output_address();
    }

    int res = 0;
    int listLength = countadr;

    while (listLength--) //Cортировка по алфавиту и сравнение строк
    {
        bool swapped = false;
        for (int i = 0; i < listLength; i++)
        {
            res = sM[i].compare(0, 2, sM[i+1]); //Сравнение строк
            if (res == 1)
            {
                std::swap(sM[i], sM[i + 1]);
                swapped = true;
            }
        }
        if (swapped == false)
            break;
    }
    filew << countadr;

    for (int i = 0; i < 5; i++) //Запись в файл
    {
        filew << sM[i] + "\n";
    }
    std::cout << "Файл записан успешно, проверьте!!!";
}



int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Address* arrADR = new Address[5];
    int countadr = out_file(arrADR);

    writeFile(arrADR, countadr);
    delete[] arrADR;
    return 1;
}
