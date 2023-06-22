#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Task {
private:
    string name;
    string startTime;
    string endTime;

public:
    Task(string name, string startTime, string endTime)
        : name(name), startTime(startTime), endTime(endTime) {}

    string getName() const {
        return name;
    }

    string getStartTime() const {
        return startTime;
    }

    string getEndTime() const {
        return endTime;
    }
};

class TodoList {
private:
    string name;
    vector<Task*> tasks;

public:
    TodoList(const string& name) : name(name) {}

    void addTask(Task* task) {
        tasks.push_back(task);
    }

    void displayTasks() const {
        cout << "Tasks for TodoList " << name << ":" << endl;
        for (const auto& task : tasks) {
            cout << "Name: " << task->getName() << ", Start Time: " << task->getStartTime()
                 << ", End Time: " << task->getEndTime() << endl;
        }
    }
};

class User {
private:
    string username;
    string password;

public:
    User(const string& username, const string& password)
        : username(username), password(password) {}

    string getUsername() const {
        return username;
    }

    bool login(const string& username, const string& password) const {
        return (this->username == username && this->password == password);
    }
};

class TodoListManager {
private:
    vector<TodoList*> todoLists;
    vector<User*> users;

public:
    TodoList* createTodoList(const string& name) {
        TodoList* newList = new TodoList(name);
        todoLists.push_back(newList);
        return newList;
    }

    void displayTodoLists() const {
        cout << "Todo Lists:" << endl;
        for (const auto& todoList : todoLists) {
            cout << "Name: " << todoList->getName() << endl;
        }
    }

    User* createUser(const string& username, const string& password) {
        User* newUser = new User(username, password);
        users.push_back(newUser);
        return newUser;
    }

    void displayUsers() const {
        cout << "Users:" << endl;
        for (const auto& user : users) {
            cout << "Username: " << user->getUsername() << endl;
        }
    }

    const vector<TodoList*>& getTodoLists() const {
        return todoLists;
    }

    const vector<User*>& getUsers() const {
        return users;
    }

    ~TodoListManager() {
        for (const auto& todoList : todoLists) {
            for (const auto& task : todoList->tasks) {
                delete task;
            }
            delete todoList;
        }

        for (const auto& user : users) {
            delete user;
        }
    }
};

int main() {
    TodoListManager manager;

    // Create TodoLists
    TodoList* list1 = manager.createTodoList("Work");
    TodoList* list2 = manager.createTodoList("Personal");

    // Create Tasks
    Task* task1 = new Task("Task 1", "10:00 AM", "11:00 AM");
    Task* task2 = new Task("Task 2", "2:00 PM", "3:30 PM");
    Task* task3 = new Task("Task 3", "9:00 AM", "10:30 AM");

    // Add tasks to TodoLists
    list1->addTask(task1);
    list1->addTask(task2);
    list2->addTask(task3);

    // Display TodoLists and tasks
    manager.displayTodoLists();
    list1->displayTasks();
    list2->displayTasks();

    // Create Users
    User* user1 = manager.createUser("Aakriti", "hello321");
    User* user2 = manager.createUser("Kritika", "user123");

    // Display Users
    manager.displayUsers();

    // User Login
    string username, password;
    cout << "Enter your username: ";
    cin >> username;
    cout << "Enter your password: ";
    cin >> password;

    User* loggedInUser = nullptr;
    for (const auto& user : manager.getUsers()) {
        if (user->login(username, password)) {
            loggedInUser = user;
            break;
        }
    }

    if (loggedInUser != nullptr) {
        cout << "Login successful. Welcome, " << username << endl;
    } else {
        cout << "Login failed. Invalid username or password." << endl;
    }

    return 0;
}
