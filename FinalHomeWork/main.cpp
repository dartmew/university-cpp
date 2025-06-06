#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <iomanip>
#include <limits>
#include <sstream>
#include <functional>
#include <locale>
#include <codecvt>

using namespace std;

// Структура для представления элемента расписания
struct ScheduleItem {
    int id;                 // Код записи
    string group;           // Группа
    string subject;         // Предмет
    string teacher;         // Преподаватель
    unsigned char day;      // День недели (1-7)
    unsigned char period;   // Номер пары (1-4)

    // Конструктор
    ScheduleItem(int i, const string& g, const string& s, const string& t, unsigned char d, unsigned char p)
        : id(i), group(g), subject(s), teacher(t), day(d), period(p) {}

    // Геттеры для доступа к полям
    int getId() const { return id; }
    string getGroup() const { return group; }
    string getSubject() const { return subject; }
    string getTeacher() const { return teacher; }
    unsigned char getDay() const { return day; }
    unsigned char getPeriod() const { return period; }
};

// Класс для форматированного вывода таблиц
class TableFormatter {
public:
    // Универсальная функция для печати таблиц
    static void printTable(const vector<string>& headers, const vector<vector<string>>& rows) {
        if (headers.empty()) return;
        
        // Рассчитываем ширину столбцов
        vector<size_t> colWidths(headers.size(), 0);
        
        // Учитываем заголовки
        for (size_t i = 0; i < headers.size(); i++) {
            colWidths[i] = calculateUtf8Length(headers[i]);
        }
        
        // Учитываем данные
        for (const auto& row : rows) {
            for (size_t i = 0; i < row.size(); i++) {
                if (i < colWidths.size()) {
                    colWidths[i] = max(colWidths[i], calculateUtf8Length(row[i]));
                }
            }
        }
        
        // Добавляем отступы
        for (size_t i = 0; i < colWidths.size(); i++) {
            colWidths[i] += 2; // По 1 пробелу с каждой стороны
        }
        
        // Верхняя граница таблицы
        printHorizontalLine(colWidths);
        
        // Заголовки столбцов
        printRow(headers, colWidths);
        
        // Разделитель заголовка
        printHorizontalLine(colWidths);
        
        // Данные
        for (const auto& row : rows) {
            printRow(row, colWidths);
        }
        
        // Нижняя граница таблицы
        printHorizontalLine(colWidths);
    }

private:
    // Функция для корректного расчета длины строки UTF-8
    static size_t calculateUtf8Length(const string& str) {
        wstring_convert<codecvt_utf8<wchar_t>> converter;
        wstring wide = converter.from_bytes(str);
        return wide.length();
    }

    // Печать горизонтальной линии
    static void printHorizontalLine(const vector<size_t>& colWidths) {
        cout << "+";
        for (size_t w : colWidths) {
            cout << setfill('-') << setw(static_cast<int>(w) + 1) << "" << "+";
        }
        cout << setfill(' ') << endl;
    }

    // Печать строки данных
    static void printRow(const vector<string>& cells, const vector<size_t>& colWidths) {
        cout << "|";
        for (size_t i = 0; i < cells.size(); i++) {
            if (i < colWidths.size()) {
                size_t actualLength = calculateUtf8Length(cells[i]);
                size_t padding = colWidths[i] - actualLength;
                size_t leftPadding = padding / 2;
                size_t rightPadding = padding - leftPadding;
                
                cout << " " 
                     << setw(static_cast<int>(leftPadding)) << "" 
                     << cells[i]
                     << setw(static_cast<int>(rightPadding)) << ""
                     << " |";
            }
        }
        cout << endl;
    }
};

// Класс для управления базой данных расписания
class ScheduleDatabase {
private:
    vector<ScheduleItem> items;  // Хранение записей

public:
    // Загрузка данных из файла
    void loadFromFile(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cerr << "Ошибка открытия файла: " << filename << endl;
            return;
        }

        items.clear();
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string token;
            vector<string> tokens;

            while (getline(ss, token, ',')) {
                tokens.push_back(token);
            }

            if (tokens.size() != 6) {
                cerr << "Некорректная строка: " << line << endl;
                continue;
            }

            try {
                int id = stoi(tokens[0]);
                string group = tokens[1];
                string subject = tokens[2];
                string teacher = tokens[3];
                unsigned char day = static_cast<unsigned char>(stoi(tokens[4]));
                unsigned char period = static_cast<unsigned char>(stoi(tokens[5]));

                if (day < 1 || day > 7 || period < 1 || period > 4) {
                    cerr << "Некорректные данные: " << line << endl;
                    continue;
                }

                items.emplace_back(id, group, subject, teacher, day, period);
            } catch (...) {
                cerr << "Ошибка обработки строки: " << line << endl;
            }
        }
        file.close();
        cout << "Данные загружены (" << items.size() << " записей)" << endl;
    }

    // Сохранение данных в файл
    void saveToFile(const string& filename) {
        ofstream file(filename);
        if (!file.is_open()) {
            cerr << "Ошибка создания файла: " << filename << endl;
            return;
        }

        for (const auto& item : items) {
            file << item.id << ','
                 << item.group << ','
                 << item.subject << ','
                 << item.teacher << ','
                 << static_cast<int>(item.day) << ','
                 << static_cast<int>(item.period) << '\n';
        }
        file.close();
        cout << "Данные сохранены (" << items.size() << " записей)" << endl;
    }

    // Просмотр всех записей в виде таблицы
    void displayAll() const {
        if (items.empty()) {
            cout << "База данных пуста" << endl;
            return;
        }
        
        vector<string> headers = {"ID", "Группа", "Предмет", "Преподаватель", "День", "Пара"};
        vector<vector<string>> rows;
        
        for (const auto& item : items) {
            rows.push_back({
                to_string(item.id),
                item.group,
                item.subject,
                item.teacher,
                to_string(static_cast<int>(item.day)),
                to_string(static_cast<int>(item.period))
            });
        }
        
        TableFormatter::printTable(headers, rows);
    }

    // Добавление новой записи
    void addItem(int id, const string& group, const string& subject, const string& teacher, unsigned char day, unsigned char period) {
        if (day < 1 || day > 7 || period < 1 || period > 4) {
            cerr << "Некорректные данные (день: 1-7, пара: 1-4)" << endl;
            return;
        }

        for (const auto& item : items) {
            if (item.id == id) {
                cerr << "Ошибка: ID должен быть уникальным" << endl;
                return;
            }
        }

        items.emplace_back(id, group, subject, teacher, day, period);
        cout << "Запись добавлена (ID: " << id << ")" << endl;
    }

    // Удаление записи по ID
    void deleteItem(int id) {
        auto it = remove_if(items.begin(), items.end(),
            [id](const ScheduleItem& item) { return item.id == id; });
        
        if (it != items.end()) {
            items.erase(it, items.end());
            cout << "Запись удалена (ID: " << id << ")" << endl;
        } else {
            cerr << "Запись с ID " << id << " не найдена" << endl;
        }
    }

    // Сортировка по ID
    void sortById() {
        sort(items.begin(), items.end(),
            [](const ScheduleItem& a, const ScheduleItem& b) { return a.id < b.id; });
        cout << "Данные отсортированы по ID" << endl;
    }

    // Поиск записи по ID
    vector<ScheduleItem> searchById(int id) const {
        vector<ScheduleItem> results;
        for (const auto& item : items) {
            if (item.id == id) {
                results.push_back(item);
            }
        }
        return results;
    }

    // Фильтрация по диапазону дней
    vector<ScheduleItem> filterByDayRange(unsigned char start, unsigned char end) const {
        vector<ScheduleItem> results;
        for (const auto& item : items) {
            if (item.day >= start && item.day <= end) {
                results.push_back(item);
            }
        }
        return results;
    }

    // Проверка на конфликты в расписании
    void checkConflicts() const {
        // Для групп: (группа, день, пара) -> предметы
        map<tuple<string, int, int>, set<string>> groupConflicts;
        // Для преподавателей: (преподаватель, день, пара) -> группы
        map<tuple<string, int, int>, set<string>> teacherConflicts;

        for (const auto& item : items) {
            auto groupKey = make_tuple(item.group, item.day, item.period);
            groupConflicts[groupKey].insert(item.subject);

            auto teacherKey = make_tuple(item.teacher, item.day, item.period);
            teacherConflicts[teacherKey].insert(item.group);
        }

        // Формирование данных о конфликтах
        vector<tuple<string, int, int, string>> groupConflictData;
        for (const auto& [key, subjects] : groupConflicts) {
            if (subjects.size() > 1) {
                auto [group, day, period] = key;
                string subjectsList;
                for (const auto& subject : subjects) {
                    if (!subjectsList.empty()) subjectsList += ", ";
                    subjectsList += subject;
                }
                groupConflictData.emplace_back(group, day, period, subjectsList);
            }
        }

        vector<tuple<string, int, int, string>> teacherConflictData;
        for (const auto& [key, groups] : teacherConflicts) {
            if (groups.size() > 1) {
                auto [teacher, day, period] = key;
                string groupsList;
                for (const auto& group : groups) {
                    if (!groupsList.empty()) groupsList += ", ";
                    groupsList += group;
                }
                teacherConflictData.emplace_back(teacher, day, period, groupsList);
            }
        }

        // Вывод конфликтов
        if (!groupConflictData.empty()) {
            cout << "\nКонфликты в группах:" << endl;
            printConflictTable(groupConflictData, {"Группа", "День", "Пара", "Предметы"});
        } else {
            cout << "Конфликтов в группах не обнаружено" << endl;
        }

        if (!teacherConflictData.empty()) {
            cout << "\nКонфликты у преподавателей:" << endl;
            printConflictTable(teacherConflictData, {"Преподаватель", "День", "Пара", "Группы"});
        } else {
            cout << "Конфликтов у преподавателей не обнаружено" << endl;
        }
    }

    // Печать таблицы конфликтов
    void printConflictTable(const vector<tuple<string, int, int, string>>& conflicts, 
                           const vector<string>& headers) const {
        vector<vector<string>> rows;
        
        for (const auto& conflict : conflicts) {
            auto [col1, col2, col3, col4] = conflict;
            rows.push_back({
                col1,
                to_string(col2),
                to_string(col3),
                col4
            });
        }
        
        TableFormatter::printTable(headers, rows);
    }

    // Печать расписания для группы
    void printGroupSchedule(const string& group) const {
        // Фильтрация записей по группе
        vector<ScheduleItem> groupItems;
        for (const auto& item : items) {
            if (item.group == group) {
                groupItems.push_back(item);
            }
        }

        if (groupItems.empty()) {
            cout << "Расписание для группы " << group << " не найдено" << endl;
            return;
        }

        // Сортировка по дню и паре
        sort(groupItems.begin(), groupItems.end(),
            [](const ScheduleItem& a, const ScheduleItem& b) {
                if (a.day != b.day) return a.day < b.day;
                return a.period < b.period;
            });

        // Преобразование номера дня в текст
        auto dayToString = [](unsigned char day) -> string {
            switch (day) {
                case 1: return "Понедельник";
                case 2: return "Вторник";
                case 3: return "Среда";
                case 4: return "Четверг";
                case 5: return "Пятница";
                case 6: return "Суббота";
                case 7: return "Воскресенье";
                default: return "Неизвестный день";
            }
        };

        // Вывод расписания
        cout << "\nРасписание для группы " << group << ":" << endl;
        
        unsigned char currentDay = 0;
        vector<ScheduleItem> dayItems;
        
        for (const auto& item : groupItems) {
            if (item.day != currentDay) {
                // Выводим предыдущий день
                if (!dayItems.empty()) {
                    cout << "\n" << dayToString(currentDay) << ":\n";
                    printDaySchedule(dayItems);
                    dayItems.clear();
                }
                currentDay = item.day;
            }
            dayItems.push_back(item);
        }
        
        // Выводим последний день
        if (!dayItems.empty()) {
            cout << "\n" << dayToString(currentDay) << ":\n";
            printDaySchedule(dayItems);
        }
    }

    // Печать расписания на день
    void printDaySchedule(const vector<ScheduleItem>& items) const {
        vector<string> headers = {"Пара", "Предмет", "Преподаватель"};
        vector<vector<string>> rows;
        
        for (const auto& item : items) {
            rows.push_back({
                to_string(static_cast<int>(item.period)),
                item.subject,
                item.teacher
            });
        }
        
        TableFormatter::printTable(headers, rows);
    }
};

// Функция для очистки буфера ввода
void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Основное меню программы
int main() {
    ScheduleDatabase db;
    int choice;

    while (true) {
        cout << "\n=== Управление базой данных расписания ===" << endl;
        cout << "1. Загрузить БД из файла" << endl;
        cout << "2. Просмотреть БД" << endl;
        cout << "3. Добавить запись" << endl;
        cout << "4. Удалить запись" << endl;
        cout << "5. Сохранить БД в файл" << endl;
        cout << "6. Сортировать по ID" << endl;
        cout << "7. Поиск по ID" << endl;
        cout << "8. Фильтр по диапазону дней" << endl;
        cout << "9. Проверить накладки" << endl;
        cout << "10. Расписание группы" << endl;
        cout << "0. Выход" << endl;
        cout << "Выбор: ";
        
        cin >> choice;
        if (cin.fail()) {
            clearInputBuffer();
            cout << "Ошибка ввода. Пожалуйста, введите число." << endl;
            continue;
        }

        switch (choice) {
            case 1: {
                string filename;
                cout << "Имя файла: ";
                cin >> filename;
                db.loadFromFile(filename);
                break;
            }
            case 2:
                db.displayAll();
                break;
            case 3: {
                int id;
                string group, subject, teacher;
                unsigned char day, period;
                int temp;
                
                cout << "ID: "; 
                if (!(cin >> id)) {
                    clearInputBuffer();
                    cout << "Некорректный ID" << endl;
                    break;
                }
                clearInputBuffer();
                
                cout << "Группа: "; getline(cin, group);
                cout << "Предмет: "; getline(cin, subject);
                cout << "Преподаватель: "; getline(cin, teacher);
                
                cout << "День (1-7): "; 
                if (!(cin >> temp) || temp < 1 || temp > 7) {
                    clearInputBuffer();
                    cout << "Некорректный день" << endl;
                    break;
                }
                day = static_cast<unsigned char>(temp);
                
                cout << "Пара (1-4): "; 
                if (!(cin >> temp) || temp < 1 || temp > 4) {
                    clearInputBuffer();
                    cout << "Некорректный номер пары" << endl;
                    break;
                }
                period = static_cast<unsigned char>(temp);
                
                db.addItem(id, group, subject, teacher, day, period);
                break;
            }
            case 4: {
                int id;
                cout << "ID для удаления: "; 
                if (!(cin >> id)) {
                    clearInputBuffer();
                    cout << "Некорректный ID" << endl;
                    break;
                }
                db.deleteItem(id);
                break;
            }
            case 5: {
                string filename;
                cout << "Имя файла: "; cin >> filename;
                db.saveToFile(filename);
                break;
            }
            case 6:
                db.sortById();
                break;
            case 7: {
                int id;
                cout << "ID для поиска: "; 
                if (!(cin >> id)) {
                    clearInputBuffer();
                    cout << "Некорректный ID" << endl;
                    break;
                }
                auto results = db.searchById(id);
                if (results.empty()) {
                    cout << "Записи не найдены" << endl;
                } else {
                    vector<string> headers = {"ID", "Группа", "Предмет", "Преподаватель", "День", "Пара"};
                    vector<vector<string>> rows;
                    for (const auto& item : results) {
                        rows.push_back({
                            to_string(item.getId()),
                            item.getGroup(),
                            item.getSubject(),
                            item.getTeacher(),
                            to_string(static_cast<int>(item.getDay())),
                            to_string(static_cast<int>(item.getPeriod()))
                        });
                    }
                    TableFormatter::printTable(headers, rows);
                }
                break;
            }
            case 8: {
                int start, end;
                cout << "Начальный день (1-7): "; 
                if (!(cin >> start) || start < 1 || start > 7) {
                    clearInputBuffer();
                    cout << "Некорректный день" << endl;
                    break;
                }
                
                cout << "Конечный день (1-7): "; 
                if (!(cin >> end) || end < 1 || end > 7 || end < start) {
                    clearInputBuffer();
                    cout << "Некорректный день" << endl;
                    break;
                }
                
                auto filtered = db.filterByDayRange(start, end);
                if (filtered.empty()) {
                    cout << "Записи не найдены" << endl;
                } else {
                    vector<string> headers = {"ID", "Группа", "Предмет", "Преподаватель", "День", "Пара"};
                    vector<vector<string>> rows;
                    for (const auto& item : filtered) {
                        rows.push_back({
                            to_string(item.getId()),
                            item.getGroup(),
                            item.getSubject(),
                            item.getTeacher(),
                            to_string(static_cast<int>(item.getDay())),
                            to_string(static_cast<int>(item.getPeriod()))
                        });
                    }
                    TableFormatter::printTable(headers, rows);
                }
                break;
            }
            case 9:
                db.checkConflicts();
                break;
            case 10: {
                string group;
                clearInputBuffer();
                cout << "Название группы: "; getline(cin, group);
                db.printGroupSchedule(group);
                break;
            }
            case 0:
                cout << "Завершение программы" << endl;
                return 0;
            default:
                cout << "Неверный выбор!" << endl;
        }
    }
}