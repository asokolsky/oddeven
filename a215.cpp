#include <iostream>
#include <vector>
#include <map>

using namespace std;

/**
 * Реализуйте класс TeamTasks, позволяющий хранить статистику по статусам задач команды разработчиков: 
 */

/*enum class TaskStatus {NEW, IN_PROGRESS, TESTING, DONE};

// Объявляем тип-синоним для map<TaskStatus, int>,
// позволяющего хранить количество задач каждого статуса
using TasksInfo = map<TaskStatus, int>;*/

int safeAt(const TasksInfo &ti, TaskStatus s) {
  return (ti.count(s) == 0) ? 0 : ti.at(s);
}
TasksInfo operator+(const TasksInfo &lhs, const TasksInfo& rhs) {
    TasksInfo res;
    res[TaskStatus::NEW] = safeAt(lhs, TaskStatus::NEW) + safeAt(rhs, TaskStatus::NEW);
    res[TaskStatus::IN_PROGRESS] = safeAt(lhs, TaskStatus::IN_PROGRESS) + safeAt(rhs, TaskStatus::IN_PROGRESS);
    res[TaskStatus::TESTING] = safeAt(lhs, TaskStatus::TESTING) + safeAt(rhs, TaskStatus::TESTING);
    res[TaskStatus::DONE] = safeAt(lhs, TaskStatus::DONE) + safeAt(rhs, TaskStatus::DONE);
    return res;
}

void reset(TasksInfo &ti) {
    ti[TaskStatus::NEW] = 0;
    ti[TaskStatus::IN_PROGRESS] = 0;
    ti[TaskStatus::TESTING] = 0;
    ti[TaskStatus::DONE] = 0;
}
void remove0s(TasksInfo &ti) {
    if(ti[TaskStatus::NEW] == 0)
        ti.erase(TaskStatus::NEW);
    if(ti[TaskStatus::IN_PROGRESS] == 0)
        ti.erase(TaskStatus::IN_PROGRESS);
    if(ti[TaskStatus::TESTING] == 0)
        ti.erase(TaskStatus::TESTING);
    if(ti[TaskStatus::DONE] == 0)
        ti.erase(TaskStatus::DONE);
}

class TeamTasks  {
public:
    // Получить статистику по статусам задач конкретного разработчика
    // гарантируется, что метод GetPersonTasksInfo не будет вызван для разработчика, не имеющего задач.
    const TasksInfo& GetPersonTasksInfo(const string& person) const {
        return _tasks.at(person);
    }
    // Добавить новую задачу (в статусе NEW) для конкретного разработчитка
    void AddNewTask(const string& person) {
        addPerson(person);
        _tasks[person][TaskStatus::NEW]++;
    }
    void AddNewTasks(const string& person, int cntr) {
        for(;cntr > 0; cntr--)
            AddNewTask(person);
    }
    // Обновить статусы по данному количеству задач конкретного разработчика,
    // подробности см. ниже
    tuple<TasksInfo, TasksInfo> PerformPersonTasks(const string& person, int task_count);

private:
    void addPerson(const string& person) {
        if(_tasks.count(person) == 0)
            reset(_tasks[person]);
    }
    map<string, TasksInfo> _tasks;
};

/**
 Обновить статусы по данному количеству задач конкретного разработчика,
Метод PerformPersonTasks должен реализовывать следующий алгоритм:

    Рассмотрим все не выполненные задачи разработчика person.
    Упорядочим их по статусам: сначала все задачи в статусе NEW, затем все задачи в статусе IN_PROGRESS и, 
    наконец, задачи в статусе TESTING.
    Рассмотрим первые task_count задач и переведём каждую из них в следующий статус в соответствии 
    с естественным порядком: NEW → IN_PROGRESS → TESTING → DONE.
    Вернём кортеж из двух элементов: информацию о статусах обновившихся задач (включая те, которые оказались
    в статусе DONE) и информацию о статусах остальных не выполненных задач.

Гарантируется, что task_count является положительным числом. Если task_count превышает текущее количество
невыполненных задач разработчика, достаточно считать, что task_count равен количеству невыполненных задач: 
дважды обновлять статус какой-либо задачи в этом случае не нужно.

Кроме того, гарантируется, что метод GetPersonTasksInfo не будет вызван для разработчика, не имеющего задач.
Пример работы метода PerformPersonTasks

Предположим, что у конкретного разработчика имеется 10 задач со следующими статусами:
    NEW — 3
    IN_PROGRESS — 2
    TESTING — 4
    DONE — 1
Поступает команда PerformPersonTasks с параметром task_count = 4, что означает обновление статуса для 3 задач 
c NEW до IN_PROGRESS и для 1 задачи с IN_PROGRESS до TESTING. Таким образом, новые статусы задач будут следующими:

    IN_PROGRESS — 3 обновлённых, 1 старая
    TESTING — 1 обновлённая, 4 старых
    DONE — 1 старая

В этом случае необходимо вернуть кортеж из 2 словарей:

    Обновлённые задачи: IN_PROGRESS — 3, TESTING — 1.
    Не обновлённые задачи, исключая выполненные: IN_PROGRESS — 1, TESTING — 4.

Словари не должны содержать лишних элементов, то есть статусов, которым соответствует ноль задач.
*/
tuple<TasksInfo, TasksInfo> TeamTasks::PerformPersonTasks(const string& person, int task_count)
{
    addPerson(person);

    TasksInfo tiOld = _tasks[person];
    TasksInfo tiNew;
    reset(tiNew);
    for(;task_count > 0; task_count--) {
        if(tiOld[TaskStatus::NEW] > 0) {
        // first move NEW tasks to IN_PROGRESS
            tiOld[TaskStatus::NEW]--;
            tiNew[TaskStatus::IN_PROGRESS]++;
        } else if (tiOld[TaskStatus::IN_PROGRESS] > 0) {
        // then move IN_PROGRESS tasks to TESTING
            tiOld[TaskStatus::IN_PROGRESS]--;
            tiNew[TaskStatus::TESTING]++;
        } else if (tiOld[TaskStatus::TESTING] > 0) {
        // then move TESTING tasks to DONE
            tiOld[TaskStatus::TESTING]--;
            tiNew[TaskStatus::DONE]++;
        } 
    }
    _tasks[person] = tiOld + tiNew;
    remove0s(tiNew);
    remove0s(tiOld);
    if(tiOld.count(TaskStatus::DONE) > 0) tiOld.erase(TaskStatus::DONE);
    return std::make_tuple(tiNew, tiOld);   
}

/**
Примечание
Обновление словаря одновременно с итерированием по нему может привести к непредсказуемым последствиям. 
При возникновении такой необходимости рекомендуется сначала в отдельном временном словаре собрать информацию
об обновлениях, а затем применить их к основному словарю.
 * 
 */

// Принимаем словарь по значению, чтобы иметь возможность
// обращаться к отсутствующим ключам с помощью [] и получать 0,
// не меняя при этом исходный словарь
void PrintTasksInfo(const char *msg, const TasksInfo &tasks_info) {
    /*
  cout << tasks_info[TaskStatus::NEW] << " new tasks" <<
      ", " << tasks_info[TaskStatus::IN_PROGRESS] << " tasks in progress" <<
      ", " << tasks_info[TaskStatus::TESTING] << " tasks are being tested" <<
      ", " << tasks_info[TaskStatus::DONE] << " tasks are done" << endl;
      */
    cout << msg;
    if(tasks_info.count(TaskStatus::NEW) == 0) cout << "_";
    else cout << tasks_info.at(TaskStatus::NEW);
    cout << ", ";
    if(tasks_info.count(TaskStatus::IN_PROGRESS) == 0) cout << "_";
    else cout << tasks_info.at(TaskStatus::IN_PROGRESS);
    cout << ", ";
    if(tasks_info.count(TaskStatus::TESTING) == 0) cout << "_";
    else cout << tasks_info.at(TaskStatus::TESTING);
    cout << ", ";
    if(tasks_info.count(TaskStatus::DONE) == 0) cout << "_";
    else cout << tasks_info.at(TaskStatus::DONE);
    cout << endl;
}
#if 0
int main() 
{
  TeamTasks tasks;
  TasksInfo updated_tasks, untouched_tasks;  

  /*
  tasks.AddNewTask("Ilia");
  for (int i = 0; i < 3; ++i) tasks.AddNewTask("Ivan");

  PrintTasksInfo("Ilia's tasks: ", tasks.GetPersonTasksInfo("Ilia"));
  PrintTasksInfo("Ivan's tasks: ", tasks.GetPersonTasksInfo("Ivan"));
  
  TasksInfo updated_tasks, untouched_tasks;  
  tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Ivan", 2);
  PrintTasksInfo("Updated Ivan's tasks: ", updated_tasks);
  PrintTasksInfo("Untouched Ivan's tasks: ", untouched_tasks);
  
  tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Ivan", 2);
  PrintTasksInfo("Updated Ivan's tasks: ", updated_tasks);
  PrintTasksInfo("Untouched Ivan's tasks: ", untouched_tasks);
  */

    tasks.AddNewTasks("Alice", 5);//             []                                                                                  []
    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Alice", 5);//      [{"IN_PROGRESS": 5}, {}]                                                            [{"IN_PROGRESS": 5}, {}]
PrintTasksInfo("Updated: ", updated_tasks);
PrintTasksInfo("Untouched: ", untouched_tasks);
    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Alice", 5);//      [{"TESTING": 5}, {}]                                                                [{"TESTING": 5}, {}]
PrintTasksInfo("Updated: ", updated_tasks);
PrintTasksInfo("Untouched: ", untouched_tasks);
    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Alice", 1);//      [{"DONE": 1}, {"TESTING": 4}]                                                       [{"DONE": 1}, {"TESTING": 4}]
PrintTasksInfo("Updated: ", updated_tasks);
PrintTasksInfo("Untouched: ", untouched_tasks);
    tasks.AddNewTasks("Alice", 5);//             []                                                                                  []
    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Alice", 2);//      [{"IN_PROGRESS": 2}, {"NEW": 3, "TESTING": 4, "DONE": 1}]                           [{"IN_PROGRESS": 2}, {"NEW": 3, "TESTING": 4}]
PrintTasksInfo("Updated: ", updated_tasks);
PrintTasksInfo("Untouched: ", untouched_tasks);
    updated_tasks = tasks.GetPersonTasksInfo("Alice");//        {"NEW": 3, "IN_PROGRESS": 2, "TESTING": 4, "DONE": 1}                               {"NEW": 3, "IN_PROGRESS": 2, "TESTING": 4, "DONE": 1}
PrintTasksInfo("Tasks: ", updated_tasks);
    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Alice", 4);//      [{"IN_PROGRESS": 3, "TESTING": 1}, {"IN_PROGRESS": 1, "TESTING": 4, "DONE": 1}]     [{"IN_PROGRESS": 3, "TESTING": 1}, {"IN_PROGRESS": 1, "TESTING": 4}]
PrintTasksInfo("Updated: ", updated_tasks);
PrintTasksInfo("Untouched: ", untouched_tasks);
    updated_tasks = tasks.GetPersonTasksInfo("Alice");//        {"NEW": 0, "IN_PROGRESS": 4, "TESTING": 5, "DONE": 1}                               {"IN_PROGRESS": 4, "TESTING": 5, "DONE": 1}
PrintTasksInfo("Tasks: ", updated_tasks);

    return 0;
}

/*
Ilia's tasks: 1, 0, 0, 0
Ivan's tasks: 3, 0, 0, 0
Updated Ivan's tasks: 0, 2, 0, 0
Untouched Ivan's tasks: 1, 0, 0, 0
Updated Ivan's tasks: 0, 1, 1, 0
Untouched Ivan's tasks: 0, 1, 0, 0
*/

#endif // 0
