#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>
using namespace std;

// Base class Employee
class Employee {
private:
    int emp_id;
    string name;
    string address;
    float salary;
    int group_id;
    int attendance;
    int performance_rating;

protected:
    void setSalary(float new_salary) {
        salary = new_salary;
    }
public:
    Employee() : emp_id(0), salary(0.0), group_id(0), attendance(0), performance_rating(0) {}

    virtual ~Employee() {}

    virtual void inputEmployeeDetails() {
        cout << "\nEnter Employee ID: ";
        cin >> emp_id;
        cout << "Enter Name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter Address: ";
        cin >> address;
        cout << "Enter Group ID: ";
        cin >> group_id;
        attendance = 0;
        performance_rating = 0;
    }

    virtual void displayEmployeeDetails() const {
        cout << "\nEmployee ID: " << emp_id;
        cout << "\nName: " << name;
        cout << "\nAddress: " << address;
        cout << "\nSalary: Rs." << salary;
        cout << "\nGroup ID: " << group_id;
        cout << "\nAttendance: " << attendance;
        cout << "\nPerformance Rating: " << performance_rating;
    }

    int getEmpID() const {
        return emp_id;
    }

    string getName() const {
        return name;
    }

    float getSalary() const {
        return salary;
    }

    int getGroupID() const {
        return group_id;
    }

    int getAttendance() const {
        return attendance;
    }

    int getPerformanceRating() const {
        return performance_rating;
    }

    void updateSalary(float new_salary) {
        setSalary(new_salary);
    }

    void updateAttendance(int new_attendance) {
        attendance = new_attendance;
    }

    void updatePerformanceRating(int new_rating) {
        if (new_rating >= 1 && new_rating <= 5) {
            performance_rating = new_rating;
        } else {
            cout << "Invalid Rating! Please rate between 1 to 5.\n";
        }
    }

    virtual string getEmployeeType() const = 0;
};

// Derived class FullTimeEmployee
class FullTimeEmployee : public Employee {
public:
    FullTimeEmployee() {}
    virtual ~FullTimeEmployee(){}
    void inputEmployeeDetails() override {
        Employee::inputEmployeeDetails();
        cout << "This is a Full-Time Employee.\n";
    }

    string getEmployeeType() const override {
        return "Full-Time";
    }
};

// Derived class PartTimeEmployee
class PartTimeEmployee : public Employee {
public:
    PartTimeEmployee() {}

    void inputEmployeeDetails() override {
        Employee::inputEmployeeDetails();
        cout << "This is a Part-Time Employee.\n";
    }

    string getEmployeeType() const override {
        return "Part-Time";
    }
};

// Department class
class Department {
public:
    string department_name;
    vector<int> employees_in_dept;
    float base_salary;

    Department() : department_name("Unknown"), base_salary(0.0) {}

    Department(const string& dept_name, float salary) : department_name(dept_name), base_salary(salary) {}

    void addEmployeeToDepartment(int emp_id) {
        employees_in_dept.push_back(emp_id);
    }
};

// EmployeeManagementSystem class
class EmployeeManagementSystem {
    map<string, string> admin_credentials;
    map<string, string> employee_credentials;
    map<string, int> employee_username_to_id; 
    map<int, Employee*> employees;
    map<int, Department> departments;

public:
    EmployeeManagementSystem() {
        admin_credentials["admin"] = "admin123";
    }

    void adminLogin() {
        string username, password;
        cout << "\nAdmin Login\n";
        cout << "Username: ";
        cin >> username;
        cout << "Password: ";
        cin >> password;
        if (admin_credentials.find(username) != admin_credentials.end() && admin_credentials[username] == password) {
            cout << "Login Successful!\n";
            adminMenu();
        } else {
            cout << "Invalid Login!\n";
        }
    }

    void employeeLogin() {
        string username, password;
        cout << "\nEmployee Login\n";
        cout << "Username: ";
        cin >> username;
        cout << "Password: ";
        cin >> password;
        if (employee_credentials.find(username) != employee_credentials.end() && employee_credentials[username] == password) {
            cout << "Login Successful!\n";
            employeeMenu(username);
        } else {
            cout << "Invalid Login!\n";
        }
    }

    void adminMenu() {
        int choice;
        do {
            cout << "\nAdmin Menu:\n";
            cout << "1. Add New Employee\n";
            cout << "2. Search Employee Profile\n";
            cout << "3. View All Employee Profiles\n";
            cout << "4. Update Employee Profile\n";
            cout << "5. Delete Employee Profile\n";
            cout << "6. Calculate Salary Package\n";
            cout << "7. Mark Attendance\n";
            cout << "8. Provide Performance Rating\n";
            cout << "9. Add Department\n";
            cout << "10. Generate Report\n";
            cout << "11. Logout\n";
            cout << "Enter Choice: ";
            cin >> choice;
            switch (choice) {
                case 1: addEmployee(); break;
                case 2: searchEmployee(); break;
                case 3: viewAllEmployees(); break;
                case 4: updateEmployee(); break;
                case 5: deleteEmployee(); break;
                case 6: calculateSalaryPackage(); break;
                case 7: markAttendance(); break;
                case 8: providePerformanceRating(); break;
                case 9: addDepartmentManually(); break;
                case 10: generateReport(); break;
                case 11: cout << "Logging out...\n"; break;
                default: cout << "Invalid choice!\n"; break;
            }
        } while (choice != 11);
    }

    void employeeMenu(const string& username) {
        int choice;
        do {
            cout << "\nEmployee Menu:\n";
            cout << "1. View Profile\n";
            cout << "2. Determine Employee Type\n";
            cout << "3. Logout\n";
            cout << "Enter Choice: ";
            cin >> choice;

            switch (choice) {
                case 1: viewProfile(username); break;
                case 2: determineEmployeeType(username); break;
                case 3: cout << "Logging out...\n"; break;
                default: cout << "Invalid choice!\n"; break;
            }
        } while (choice != 3);
    }

    void addEmployee() {
        int type;
        Employee* emp;
        cout << "Enter Employee Type (1 for Full-Time, 2 for Part-Time): ";
        cin >> type;

        if (type == 1) {
            emp = new FullTimeEmployee();
        } else if (type == 2) {
            emp = new PartTimeEmployee();
        } else {
            cout << "Invalid Employee Type!\n";
            return;
        }

        emp->inputEmployeeDetails();
        int emp_id = emp->getEmpID();
        employees[emp_id] = emp;

        string username, password;
        cout << "Assign Username for Employee: ";
        cin >> username;
        cout << "Assign Password for Employee: ";
        cin >> password;
        employee_credentials[username] = password;
        employee_username_to_id[username] = emp_id;

        addEmployeeToDepartment(emp_id);
        cout << "Employee added successfully.\n";
    }

    void addEmployeeToDepartment(int emp_id) {
        int dept_id;
        string dept_name;

        cout << "Enter Department ID: ";
        cin >> dept_id;

        if (departments.find(dept_id) == departments.end()) {
            cout << "Department not found! Creating new department.\n";
            cout << "Enter Department Name: ";
            cin >> dept_name;
            float base_salary;
            cout << "Enter base salary for department: ";
            cin >> base_salary;
            departments[dept_id] = Department(dept_name, base_salary);
        }

        departments[dept_id].addEmployeeToDepartment(emp_id);
        cout << "Employee assigned to department successfully.\n";
    }

    void addDepartmentManually() {
        int dept_id;
        string dept_name;
        float base_salary;

        cout << "Enter New Department ID: ";
        cin >> dept_id;

        if (departments.find(dept_id) != departments.end()) {
            cout << "Department ID already exists!\n";
            return;
        }

        cout << "Enter Department Name: ";
        cin >> dept_name;
        cout << "Enter Base Salary for Department: ";
        cin >> base_salary;

        departments[dept_id] = Department(dept_name, base_salary);
        cout << "Department added successfully.\n";
    }

    void searchEmployee() {
        int emp_id;
        cout << "Enter Employee ID to search: ";
        cin >> emp_id;

        if (employees.find(emp_id) != employees.end()) {
            employees[emp_id]->displayEmployeeDetails();
        } else {
            cout << "Employee not found!\n";
        }
    }

    void updateEmployee() {
        int emp_id;
        cout << "Enter Employee ID to update: ";
        cin >> emp_id;

        if (employees.find(emp_id) != employees.end()) {
            employees[emp_id]->inputEmployeeDetails();
            cout << "Employee details updated.\n";
        } else {
            cout << "Employee not found!\n";
        }
    }

    void viewAllEmployees() {
        for (const auto& emp_entry : employees) {
            emp_entry.second->displayEmployeeDetails();
            cout << "\n---------------------------------\n";
        }
    }

    void deleteEmployee() {
        int emp_id;
        cout << "Enter Employee ID to delete: ";
        cin >> emp_id;

        if (employees.find(emp_id) != employees.end()) {
            delete employees[emp_id];
            employees.erase(emp_id);
            cout << "Employee deleted.\n";
        } else {
            cout << "Employee not found!\n";
        }
    }

    void calculateSalaryPackage() {
        int emp_id;
        cout << "Enter Employee ID to calculate salary package: ";
        cin >> emp_id;

        if (employees.find(emp_id) != employees.end()) {
            Employee* emp = employees[emp_id];
            int dept_id = emp->getGroupID();

            if (departments.find(dept_id) != departments.end()) {
                float base_salary = departments[dept_id].base_salary;

                int attendance = emp->getAttendance();
                int rating = emp->getPerformanceRating();

                float attendance_bonus = (attendance / 30.0f) * 0.05f * base_salary;
                float performance_bonus = (rating / 5.0f) * 0.2f * base_salary;

                float final_salary = base_salary + attendance_bonus + performance_bonus;
                emp->updateSalary(final_salary);
                cout << "Final Salary Package: Rs." << final_salary << "\n";
            } else {
                cout << "Department not found for this employee!\n";
            }
        } else {
            cout << "Employee not found!\n";
        }
    }

    void markAttendance() {
        int emp_id, attendance;
        cout << "Enter Employee ID to mark attendance: ";
        cin >> emp_id;

        if (employees.find(emp_id) != employees.end()) {
            cout << "Enter Attendance (out of 30): ";
            cin >> attendance;
            if (attendance >= 0 && attendance <= 30) {
                employees[emp_id]->updateAttendance(attendance);
                cout << "Attendance updated.\n";
            } else {
                cout << "Invalid number of days! Please enter a value between 0 and 30.\n";
            }
        } else {
            cout << "Employee not found!\n";
        }
    }

    void providePerformanceRating() {
        int emp_id, rating;
        cout << "Enter Employee ID to rate performance: ";
        cin >> emp_id;

        if (employees.find(emp_id) != employees.end()) {
            cout << "Enter Performance Rating (1-5): ";
            cin >> rating;
            employees[emp_id]->updatePerformanceRating(rating);
            cout << "Performance Rating updated.\n";
        } else {
            cout << "Employee not found!\n";
        }
    }

    void generateReport() {
    ofstream report("employee_report.txt");
    for (const auto& emp_entry : employees) {
        report << "\nEmployee ID: " << emp_entry.second->getEmpID();
        report << "\nName: " << emp_entry.second->getName();
        report << "\nEmployee Type: " << emp_entry.second->getEmployeeType();  // Add employee type
        report << "\nSalary: Rs." << emp_entry.second->getSalary();
        report << "\nAttendance: " << emp_entry.second->getAttendance();
        report << "\nPerformance Rating: " << emp_entry.second->getPerformanceRating();
        report << "\n---------------------------------\n";
    }
    report.close();
    cout << "Report generated successfully!\n";
}


    void viewProfile(const string& username) {
        if (employee_username_to_id.find(username) != employee_username_to_id.end()) {
            int emp_id = employee_username_to_id[username];
            employees[emp_id]->displayEmployeeDetails();
        } else {
            cout << "Error: Username not found.\n";
        }
    }

    void determineEmployeeType(const string& username) {
        if (employee_username_to_id.find(username) != employee_username_to_id.end()) {
            int emp_id = employee_username_to_id[username];
            Employee* emp = employees[emp_id];

            float salary = emp->getSalary();
            int performance = emp->getPerformanceRating();
            int attendance = emp->getAttendance();

            if(performance==5 && attendance==30){
                cout << "\n--- BEST EMPLOYEE ---\nYou have full performance rating and attendance record.\n";
            }else if (performance >= 4 && attendance>=25) {
                cout << "\n--- EXCELLENT EMPLOYEE ---\nYou have great performance rating and attendance record.\n";
            }else if(performance>=4 && attendance<=25){
                cout << "\n--- AVERAGE EMPLOYEE ---\nYou have a good performance rating but not too well attendance record.\n";
            }else if(performance<4 && attendance>=25){
                cout << "\n--- AVERAGE EMPLOYEE ---\nYou have a good attendance record but weak performance rating.\n";
            }else if (performance >= 3 && attendance >= 20) {
                cout << "\n--- AVERAGE EMPLOYEE ---\nYou have an average performance rating and attendance record.\n";
            }else {
                cout << "\n--- UNDERPERFORMING EMPLOYEE ---\nYou need improvement as your performance rating and attendance record is not acceptable.\n";
            }
        } else {
            cout << "Error: Username not found.\n";
        }
    }
};
int main() {
    EmployeeManagementSystem ems;
    int choice;
    do {
        cout << "\n1. Admin Login\n";
        cout << "2. Employee Login\n";
        cout << "3. Exit\n";
        cout << "Enter Choice: ";
        cin >> choice;
        switch (choice) {
            case 1: ems.adminLogin(); break;
            case 2: ems.employeeLogin(); break;
            case 3: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice!\n"; break;
        }
    } while (choice != 3);
    return 0;
}