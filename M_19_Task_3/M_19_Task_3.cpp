/*Задание 3.Реализация программы чтения ведомости

Что нужно сделать
Реализуйте программу чтения информации из ведомости по учёту выплат.
Сама ведомость представляет собой следующую таблицу:
имя и фамилия человека; 
количество денег, которые были выплачены лицу; 
дата выплаты в формате ДД.ММ.ГГГГ.
На основе данных из ведомости следует подсчитать общее количество
выплаченных средств и определить человека с максимальной суммой выплат.*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

//Возвращает вектор строк по кахдому столбце ведомости
std::vector <std::string> pars_string(const std::string& str) {

    std::vector <std::string> tmp;
    std::string last_name;
    std::string first_name;
    std::string salary;
    std::string data;

    std::stringstream buf(str);

    buf >> last_name>> first_name >> salary >> data;
    tmp.push_back(last_name); tmp.push_back(first_name); tmp.push_back(salary); tmp.push_back(data);

    return tmp;
}

//Открвает файл, считывает построчно ведомость, парсит строку, добавляет в вектор векторов
void sal_base(std::vector <std::vector<std::string>>& base, const char* path) {

    std::ifstream ifs(path);
    std::string str;

    if (!ifs.is_open()) {

        std::cout << "File not found";
        return;
    }        
    else {

        while (!ifs.eof())
        {
            std::getline(ifs, str);

            base.push_back(pars_string(str));
        }
    }
}

//Подсчет общей суммы выплат и сотрудника с максимальной ЗП
void result(std::vector <std::vector<std::string>>& base) {

    int s = 0; int s1 = 0;
    int max_s = 0;
    int max_x = std::stoi((base[0])[2]);
    int ind;

    for (int i = 0; i < base.size(); i++) {

        if (i < base.size() - 1 - 1) {
            try
            {
                s = std::stoi((base[i])[2]);
                s1 = std::stoi((base[i + 1])[2]);
                max_s += s;
                if (max_x < std::stoi((base[i + 1])[2])) {

                    max_x = std::stoi((base[i + 1])[2]);
                    ind = i + 1;
                }
            }
            catch (const std::exception& ex)
            {
                std::cout << ex.what() << std::endl;
            }
        }
    }
    std::cout << "Total amount of funds paid = " << max_s << "\n"
        << "The person with the maximum payout amount - " << (base[ind])[0] << " " << (base[ind])[1];
}

int main() {
    const char* path = "D:\\Skillbox\\Module_19\\file_3.txt";
    
    std::vector <std::vector<std::string>> base;

    sal_base(base, path);

    result(base);
}


