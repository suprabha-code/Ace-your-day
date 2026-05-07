#include<iostream>
#include<conio.h>
#include<fstream>
#include<string>
#include<vector>
#include<ctime>
#include<map>
#include<iomanip>
#include<sstream>
#include<regex>
using namespace std;

void displayBorder(const string &header, const string content[], int contentSize) {
    int width = 80; // Width of the star border
    int height =25; // Height of the star border

    // Print the top border
    cout << string(width, '*') << endl;

    // Print the header
    int headerPadding = (width - header.length()) / 2;
    cout << "*" << string(headerPadding - 1, ' ') << header << string(width - header.length() - headerPadding - 1, ' ') << "*" << endl;

    // Print blank row below the header
    cout << "*" << string(width - 2, ' ') << "*" << endl;

    // Print the content dynamically
    for (int i = 0; i < contentSize; i++) {
        string line = content[i];
        int linePadding = (width - 2 - line.length()) / 2;
        cout << "*" << string(linePadding, ' ') << line << string(width - 2 - line.length() - linePadding, ' ') << "*" << endl;
    }

    // Fill remaining rows with blank space
    for (int i = contentSize + 4; i < height - 2; i++) {
        cout << "*" << string(width - 2, ' ') << "*" << endl;
    }

    // Print the bottom border
    cout << string(width, '*') << endl;
    getch();
}

void menu() {
    string header = "WELCOME TO OUR PROGRAM";
    string content[] = {
        "1. HOSTEL WARDEN",
        "2. STUDENT",
        "3.  EXIT",
        "",
        "CHOOSE YOUR OPTION:"
    };

    displayBorder(header, content, sizeof(content) / sizeof(content[0]));
}

void personalInfo() {
    string header = "Personal Information";
    string content[] = {
        "1. WRITE YOUR INFO",
        "2. READ YOUR INFO",
        "3. UPDATE YOUR INFO",
        "4. BACK TO MAIN MENU"
    };

    displayBorder(header, content, sizeof(content) / sizeof(content[0]));
}
class HostelWarden {
    string email;
    string name;
    string post;
    string hostelName;
    string password;
     bool validateEmail(const string &email) {
    size_t atPos = email.find('@');        // Find position of '@'
    size_t dotPos = email.find('.', atPos); // Find position of '.' after '@'

    // Validate '@' and '.' positions
    if (atPos != string::npos && dotPos != string::npos && atPos > 0 && dotPos > atPos + 1 && dotPos < email.length() - 1) {
        return true;
    }
    return false;
}
public:
    void registerWarden() {
        cout << "\nEnter Name: ";
        cin.ignore();
        getline(cin, name);
         do {
            cout << "Enter Email (e.g., username@domain.com, like john.doe@gmail.)";
            cin >> email;

            if (!validateEmail(email)) {
                cout << "\nInvalid email format! Please enter a valid email.\n";
            }
        } while (!validateEmail(email));

        cout << "Enter Post (e.g., Warden, Assistant): ";
        cin.ignore();
        getline(cin, post);
        cout << "Enter Hostel Name: ";
        getline(cin, hostelName);
        cout << "Set Password: ";

        char ch;
        password.clear();
        while ((ch = getch()) != '\r') { // Mask password input
            if (ch == '\b') { // Handle backspace
                if (!password.empty()) {
                    password.pop_back();
                    cout << "\b \b"; // Erase the last '*' from console
                }
            } else {
                password += ch;
                cout << '*'; // Mask the password
            }
        }

        ofstream file("warden_details.txt");
        file << name << endl << email << endl << post << endl << hostelName << endl << password << endl;
        file.close();
        cout<<"\n____________________________________________________________________________________";
        cout<<"\n|                               Registration successful!                           |";
        cout<<"\n____________________________________________________________________________________";
    }

    bool login() {
        string enteredEmail, enteredPassword;
        cout << "\nEnter Email: ";
        cin >> enteredEmail;
        cout << "Enter Password: ";
        enteredPassword.clear();
        char ch;
        while ((ch = getch()) != '\r') { // Mask password input
            if (ch == '\b') { // Handle backspace
                if (!enteredPassword.empty()) {
                    enteredPassword.pop_back();
                    cout << "\b \b"; // Erase the last '*' from console
                }
            } else {
                enteredPassword += ch;
                cout << '*'; // Mask the password
            }
        }

        ifstream file("warden_details.txt");
        if (file.is_open()) {
            string savedName, savedEmail, savedPost, savedHostelName, savedPassword;
            getline(file, savedName);
            getline(file, savedEmail);
            getline(file, savedPost);
            getline(file, savedHostelName);
            getline(file, savedPassword);
            file.close();

            if (enteredEmail == savedEmail && enteredPassword == savedPassword) {
            cout<<"\n____________________________________________________________________________________";
                cout<<"\n|                                  Login successful!                               |";
                cout<<"\n____________________________________________________________________________________";
                return true;
            } else {
                cout << "\nInvalid Email or Password.\n";
            }
        } else {
            cout << "<<< No registered details found. Please register first. >>>\n";
        }
        return false;
    }
};

// FoodSchedule Class
class FoodSchedule {
    map<string, map<string, vector<string>>> schedule; // Map to store schedule for each day and meal type

public:
    void loadSchedule() {
        schedule.clear();
        ifstream file("food_schedule.txt");
        string day, mealType, foodItem;
        while (getline(file, day)) {
            map<string, vector<string>> dailySchedule;
            while (getline(file, mealType) && mealType != "---") {
                vector<string> foodItems;
                while (getline(file, foodItem) && foodItem != "***") {
                    foodItems.push_back(foodItem);
                }
                dailySchedule[mealType] = foodItems;
            }
            schedule[day] = dailySchedule;
        }
        file.close();
    }

    void saveSchedule() {
        ofstream file("food_schedule.txt");
        for (const auto &daySchedule : schedule) {
            file << daySchedule.first << endl;
            for (const auto &mealSchedule : daySchedule.second) {
                file << mealSchedule.first << endl;
                for (const string &item : mealSchedule.second) {
                    file << item << endl;
                }
                file << "***" << endl; // Separator for each meal
            }
            file << "---" << endl; // Separator for each day
        }
        file.close();
    }

    void displaySchedule() {
    cout<<"\n";
    cout<<"\n+------------------------------------------------------------------------------------+";
    cout<<"\n|                                 WEEKLY FOOD SCHEDULE                               |\n";
    cout<<"\n+-----------------------------------------------------------------------------------+";
    cout<<"\n|          Day           |          Meal Type          |          Food Items         |\n";
    cout<<"\n+-----------------------------------------------------------------------------------+";
    for (const auto &daySchedule : schedule) {
        for (const auto &mealSchedule : daySchedule.second) {
    cout<<"\n|          "<< daySchedule.first<<"     -->     "<<mealSchedule.first<<"    -->    ";
            for (size_t i = 0; i < mealSchedule.second.size(); ++i) {
                cout << mealSchedule.second[i];
                if (i < mealSchedule.second.size() - 1) {
                    cout << ", ";
                }
            }
        }
    }
    cout<<"\n+-----------------------------------------------------------------------------------+";
}

void addFoodItem() {
    string day, foodItem;
    vector<string> mealTypes = {"Breakfast", "Lunch", "Snacks", "Dinner"};
    cout<<"\n|Enter day name (e.g., Monday): ";
    cin.ignore();
    getline(cin, day);

    for (const string &mealType : mealTypes) {
    cout<<"\n____________________________________________________________________________________";
        cout<<"\n|Enter food items for:" << mealType << endl;

        while (true) {
            getline(cin, foodItem);
            if (foodItem.empty()) { // Stop asking for items when input is empty
                break;
            }
            schedule[day][mealType].push_back(foodItem);
        }
    }

    saveSchedule();
    cout<<"\n____________________________________________________________________________________";
    cout<<"\n|           Food items added successfully for !!          " << day << "            !|";
    cout<<"\n____________________________________________________________________________________";
}



     void updateFoodItem() {
        string day, mealType;
        cout<<"\n|Enter day name (e.g., Monday):";
        cin.ignore();
        getline(cin, day);
       cout<<"\n____________________________________________________________________________________";
       cout<<"\n|Enter meal type (Breakfast, Lunch, Snacks, Dinner): ";
        getline(cin, mealType);

        if (schedule.find(day) != schedule.end() && schedule[day].find(mealType) != schedule[day].end()) {
            displayMealSchedule(day, mealType);
            int index;
            string foodItem;
            cout<<"\n____________________________________________________________________________________";
            cout<<"\n|Enter the number of the food item to update: ";
            cin >> index;
            cout<<"\n____________________________________________________________________________________";
            cout<<"\n|Enter the new food item: ";
            cin.ignore();
            getline(cin, foodItem);

            if (index > 0 && index <= schedule[day][mealType].size()) {
                schedule[day][mealType][index - 1] = foodItem;
                saveSchedule();
                cout<<"\n____________________________________________________________________________________";
                cout<<"\n|      Food item updated successfully for " << day << " (" << mealType << ")!          |";
                cout<<"\n____________________________________________________________________________________";
            } else {
                cout << "Invalid selection.\n";
            }
        } else {
          cout<<"\n____________________________________________________________________________________";
            cout<<"\n|              No schedule found for " << day << " (" << mealType << ").            |";
            cout<<"\n____________________________________________________________________________________";
        }
    }

    void deleteFoodItem() {
        string day, mealType;
        cout<<"\n|Enter day name (e.g., Monday): ";
        cin.ignore();
        getline(cin, day);
        cout<<"\n____________________________________________________________________________________";
        cout<<"\n|Enter meal type (Breakfast, Lunch, Snacks, Dinner): ";
        getline(cin, mealType);

        if (schedule.find(day) != schedule.end() && schedule[day].find(mealType) != schedule[day].end()) {
            displayMealSchedule(day, mealType);
            int index;
            cout<<"\n____________________________________________________________________________________";
            cout<<"\n|Enter the number of the food item to delete: ";
            cin >> index;

            if (index > 0 && index <= schedule[day][mealType].size()) {
                schedule[day][mealType].erase(schedule[day][mealType].begin() + index - 1);
                saveSchedule();
                cout<<"\n____________________________________________________________________________________";
                cout<<"\n      Food item deleted successfully for " << day << " (" << mealType << ")!\n      ";
                cout<<"\n____________________________________________________________________________________";
            } else {
                cout << "Invalid selection.\n";
            }
        } else {
        cout<<"\n____________________________________________________________________________________";
            cout<<"\n             No schedule found for " << day << " (" << mealType << ").              ";
            cout<<"\n____________________________________________________________________________________";
        }
    }

  void displayMealSchedule(const string &day, const string &mealType) {
        cout << day << " (" << mealType << ") Food Schedule:\n";
        for (size_t i = 0; i < schedule[day][mealType].size(); ++i) {
            cout << "  " << i + 1 << ". " << schedule[day][mealType][i] << endl;
        }
    }
};

class Schedule {
protected:
    string date; // Date in dd-mm-yyyy format
    string day;  // Day of the week (e.g., Monday, Tuesday)

public:
    virtual void addSchedule() = 0; // Pure virtual function
    virtual void viewSchedule() = 0; // View schedule based on date and day
};

// Derived class for Class Schedules
class ClassSchedule : public Schedule {
public:
    // Modified addSchedule to include time slots
void addSchedule() {
    ofstream out("class_schedule.txt", ios::app); // Open file in append mode
    if (!out.is_open()) {
        cout << "\nError: Could not open the class schedule file.\n";
        return;
    }

    cout << "\nEnter the date (dd-mm-yy): ";
    cin.ignore();
    getline(cin, date);

    // Validate the date format
    if (date.size() != 8 || date[2] != '-' || date[5] != '-') {
        cout << "Invalid date format! Please enter the date in dd-mm-yy format.\n";
        return;
    }

    cout << "Enter the day (e.g., Monday, Tuesday): ";
    getline(cin, day);

    char more = 'y';
    while (more == 'y' || more == 'Y') {
        string startTime, endTime, task;
        cout << "Enter the start time (e.g., 09:00): ";
        getline(cin, startTime);

        cout << "Enter the end time (e.g., 10:00): ";
        getline(cin, endTime);

        cout << "Enter the activity for " << startTime << " to " << endTime << ": ";
        getline(cin, task);

        // Write date, day, time block, and activity details to the file
        out << date << " | " << day << " | " << startTime << " to " << endTime << " | " << task << endl;

        cout << "Do you want to add another time slot? (y/n): ";
        cin >> more;
        cin.ignore(); // Clear the input buffer
    }

    cout << "\nClass schedule added successfully for " << day << ", " << date << "!\n";
    out.close();
}


// Modified viewSchedule to display time-based schedules
void viewSchedule() {
    ifstream in("class_schedule.txt");
    if (!in.is_open()) {
        cout << "\nError: Could not open the class schedule file.\n";
        return;
    }

    string inputDate, inputDay;
    cout << "Enter the date (YYYY-MM-DD): ";
    cin >> inputDate;

    cout << "Enter the day (e.g., Monday, Tuesday): ";
    cin >> ws; // Clear the input buffer before getting a line
    getline(cin, inputDay);

    string line;
    bool found = false;

    cout << "\nClass schedule for " << inputDay << ", " << inputDate << ":\n";

    while (getline(in, line)) {
        if (line.find(inputDate + " | " + inputDay + " |") == 0) { // Match date and day
            cout << line.substr(inputDate.length() + inputDay.length() + 5) << endl; // Print the schedule
            found = true;
        }
    }

    if (!found) {
        cout << "No class schedule found for " << inputDay << ", " << inputDate << ".\n";
    }

    in.close();
}
};

// Derived class for Self-Study Schedules
class SelfStudySchedule : public Schedule {
public:
    void addSchedule() {
    ofstream out("self_study_schedule.txt", ios::app); // Open file in append mode
    if (!out.is_open()) {
        cout << "\nError: Could not open the self study schedule file.\n";
        return;
    }

    cout << "\nEnter the date (dd-mm-yy): ";
    cin.ignore();
    getline(cin, date);

    // Validate the date format
    if (date.size() != 8 || date[2] != '-' || date[5] != '-') {
        cout << "Invalid date format! Please enter the date in dd-mm-yy format.\n";
        return;
    }

    cout << "Enter the day (e.g., Monday, Tuesday): ";
    getline(cin, day);

    char more = 'y';
    while (more == 'y' || more == 'Y') {
        string startTime, endTime, task;
        cout << "Enter the start time (e.g., 09:00): ";
        getline(cin, startTime);

        cout << "Enter the end time (e.g., 10:00): ";
        getline(cin, endTime);

        cout << "Enter the activity for " << startTime << " to " << endTime << ": ";
        getline(cin, task);

        // Write date, day, time block, and activity details to the file
        out << date << " | " << day << " | " << startTime << " to " << endTime << " | " << task << endl;

        cout << "Do you want to add another time slot? (y/n): ";
        cin >> more;
        cin.ignore(); // Clear the input buffer
    }

    cout << "\nself study schedule added successfully for " << day << ", " << date << "!\n";
    out.close();
}


    void viewSchedule() {
    ifstream in("self_study_schedule.txt");
    if (!in.is_open()) {
        cout << "\nError: Could not open the self-study schedule file.\n";
        return;
    }

    string inputDate, inputDay;
    cout << "Enter the date (dd-mm-yy): ";
    cin >> inputDate;

    cout << "Enter the day (e.g., Monday, Tuesday): ";
    cin >> ws; // Clear the input buffer before getting a full line
    getline(cin, inputDay);

    string line;
    bool found = false;

    cout << "\nSelf-study schedule for " << inputDay << ", " << inputDate << ":\n";

    while (getline(in, line)) {
        if (line.find(inputDate + " | " + inputDay + " |") == 0) { // Match date and day
            cout << line.substr(inputDate.length() + inputDay.length() + 5) << endl; // Print the schedule
            found = true;
        }
    }

    if (!found) {
        cout << "No self-study schedule found for " << inputDay << ", " << inputDate << ".\n";
    }

    in.close();
}

};

class ExamTimetable {
private:
    string fileName;

public:
    ExamTimetable(string file = "exam_timetable.txt") {
        fileName = file;
    }

    // Function to add an exam timetable
    void addExamSchedule() {
        ofstream outFile(fileName.c_str(), ios::app); // Open file in append mode
        if (!outFile.is_open()) {
            cout << "\nError: Could not open the exam timetable file for writing.\n";
            return;
        }

        string examName;
        cout << "\nEnter Exam Name: ";
        cin.ignore(); // Clear the input buffer
        getline(cin, examName);

        char addMoreSubjects = 'y';
        outFile << "Exam Name: " << examName << "\n";

        while (addMoreSubjects == 'y' || addMoreSubjects == 'Y') {
            string subject, date, timeDuration;

            cout << "Enter Subject Name: ";
            getline(cin, subject);

            cout << "Enter Date (dd-mm-yy): ";
            getline(cin, date);

            cout << "Enter Time Duration (e.g., 9:00 AM - 12:00 PM): ";
            getline(cin, timeDuration);

            // Save the entry to the file in the required format
            outFile << date << " | " << subject << " | " << timeDuration << "\n";

            cout << "Do you want to add another subject? (Y/N): ";
            cin >> addMoreSubjects;
            cin.ignore(); // Clear the input buffer
        }

        outFile << "--------------------------------------\n"; // Separator for each exam
        cout << "Exam timetable saved successfully.\n";
        outFile.close();
    }

    // Function to view the exam timetable
    void viewExamSchedule() {
        ifstream inFile(fileName.c_str()); // Open file in read mode
        if (!inFile.is_open()) {
            cout << "\nError: Could not open the exam timetable file for reading.\n";
            return;
        }

        string line;
        cout << "\n--- Exam Timetable ---\n";
        while (getline(inFile, line)) {
            // Display exam name as a heading
            if (line.find("Exam Name:") == 0) {
                cout << "\n" << line << "\n";
                cout << "--------------------------------------\n";
                cout << left << setw(15) << "Date"
                     << setw(30) << "Subject"
                     << setw(20) << "Time Duration" << "\n";
                cout << "--------------------------------------\n";
            }
            // Display timetable entries
            else if (line.find("----") == string::npos) {
                // Parse the line manually without using substr
                stringstream ss(line);
                string date, subject, timeDuration;
                getline(ss, date, '|');
                getline(ss, subject, '|');
                getline(ss, timeDuration);

                // Trim leading/trailing spaces (if necessary)
                date = trim(date);
                subject = trim(subject);
                timeDuration = trim(timeDuration);

                cout << left << setw(15) << date
                     << setw(30) << subject
                     << setw(20) << timeDuration << "\n";
            }
        }

        inFile.close();
    }

private:
    // Helper function to trim leading and trailing spaces
    string trim(const string& str) {//declare a func named trim that take a const ref. to a string as input and return string
        size_t first = str.find_first_not_of(" ");//search the str string for the 1st character that is  not a space
        size_t last = str.find_last_not_of(" ");//from the last
        return str.substr(first, (last - first + 1));//extracts a substring from str and length of the substring
    }
};

class Activity {
protected:
    string date;      // Date in dd-mm-yy format
    string details;   // Activity details
    bool isCompleted; // Completion status

public:
    virtual void addActivity() = 0;  // Pure virtual function to add an activity
    virtual void viewActivity(const string& date) = 0; // Pure virtual function to view activities
    virtual void markCompleted(const string& taskDetails) = 0; // Pure virtual function to mark tasks as completed
};
class FiveFoldActivity : public Activity {
public:
    void addActivity() {
        ofstream out("five_fold_activities.txt", ios::app); // Open the file for appending
        if (!out.is_open()) {
            cout << "\nError: Could not open the five-fold activity file.\n";
            return;
        }

        cout << "\nEnter the date for the activity (dd-mm-yy): ";
        cin.ignore();
        getline(cin, date);

        char more = 'y';
        while (more == 'y' || more == 'Y') {
            string startTime, endTime, activityDetails;

            cout << "Enter the start time (e.g., 09:00): ";
            getline(cin, startTime);

            cout << "Enter the end time (e.g., 10:00): ";
            getline(cin, endTime);

            cout << "Enter details of the activity: ";
            getline(cin, activityDetails);

            // Write the full activity schedule to the file
            out << date << " | " << startTime << " to " << endTime << " | " << activityDetails << endl;

            cout << "Do you want to add another activity for this date? (y/n): ";
            cin >> more;
            cin.ignore(); // Clear the input buffer
        }

        cout << "\nAll activities added successfully for " << date << "!\n";
        out.close();
    }

    void viewActivity(const string& date) {
        ifstream in("five_fold_activities.txt");
        if (!in.is_open()) {
            cout << "\nError: Could not open the five-fold activity file.\n";
            return;
        }

        string line;
        bool found = false;

        cout << "\nFive-fold activities for " << date << ":\n";

        while (getline(in, line)) {
            if (line.find(date) == 0) { // Match the date
                cout << line << endl;
                found = true;
            }
        }

        if (!found) {
            cout << "No activities found for " << date << ".\n";
        }

        in.close();
    }

    void markCompleted(const string& taskDetails)  {
        cout << "Completion tracking is not required for five-fold activities.\n";
    }
};
class Assignment : public Activity {
public:
    void addActivity() {
    ofstream out("assignment_list.txt", ios::app); // Append to file
    if (!out.is_open()) {
        cout << "\nError: Could not open the assignment file.\n";
        return;
    }

    cout << "\nEnter the assignment due date (dd-mm-yy): ";
    cin.ignore();
    getline(cin, date);

    char more = 'y';
    while (more == 'y' || more == 'Y') {
        string startTime, endTime, assignmentDetails;

        cout << "Enter the start time (e.g., 09:00): ";
        getline(cin, startTime);

        cout << "Enter the end time (e.g., 10:00): ";
        getline(cin, endTime);

        cout << "Enter assignment details: ";
        getline(cin, assignmentDetails);

        // Write to file
        out << date << " | " << startTime << " to " << endTime << " | " << assignmentDetails << " | Not Completed" << endl;

        cout << "Do you want to add another assignment for this date? (y/n): ";
        cin >> more;
        cin.ignore();
    }

    cout << "\nAll assignments added successfully for " << date << "!\n";
    out.close();
}
    void viewActivity(const string& date)  {
        ifstream in("assignment_list.txt");
        if (!in.is_open()) {
            cout << "\nError: Could not open the assignment file.\n";
            return;
        }

        string line;
        bool found = false;

        cout << "\nAssignments for " << date << ":\n";

        while (getline(in, line)) {
            if (line.find(date) == 0) { // Match date
                cout << line << endl;
                found = true;
            }
        }

        if (!found) {
            cout << "No assignments found for " << date << ".\n";
        }

        in.close();
    }

    void markCompleted(const string& taskDetails) {
        ifstream in("assignment_list.txt");
        ofstream out("temp.txt");

        if (!in.is_open() || !out.is_open()) {
            cout << "\nError: Could not access the assignment file.\n";
            return;
        }

        string line;
        bool found = false;

        while (getline(in, line)) {
            if (line.find(taskDetails) != string::npos) { // Match task details
                found = true;
                out << line.substr(0, line.find("| Not Completed")) << "| Completed" << endl;
            } else {
                out << line << endl;
            }
        }

        in.close();
        out.close();

        remove("assignment_list.txt");
        rename("temp.txt", "assignment_list.txt");

        if (found) {
            cout << "\nAssignment marked as completed.\n";
        } else {
            cout << "\nAssignment not found.\n";
        }
    }
};
class Hackathon : public Activity {
public:
    void addActivity()  {
    ofstream out("hackathon_list.txt", ios::app); // Append to file
    if (!out.is_open()) {
        cout << "\nError: Could not open the hackathon file.\n";
        return;
    }

    cout << "\nEnter the hackathon due date (dd-mm-yy): ";
    cin.ignore();
    getline(cin, date);

    char more = 'y';
    while (more == 'y' || more == 'Y') {
        string startTime, endTime, hackathonDetails;

        cout << "Enter the start time (e.g., 09:00): ";
        getline(cin, startTime);

        cout << "Enter the end time (e.g., 10:00): ";
        getline(cin, endTime);

        cout << "Enter hackathon details: ";
        getline(cin, hackathonDetails);

        // Write to file
        out << date << " | " << startTime << " to " << endTime << " | " << hackathonDetails << " | Not Completed" << endl;

        cout << "Do you want to add another hackathon for this date? (y/n): ";
        cin >> more;
        cin.ignore();
    }

    cout << "\nAll hackathons added successfully for " << date << "!\n";
    out.close();
}
    void viewActivity(const string& date)  {
        ifstream in("hackathon_list.txt");
        if (!in.is_open()) {
            cout << "\nError: Could not open the hackathon file.\n";
            return;
        }

        string line;
        bool found = false;

        cout << "\nHackathons for " << date << ":\n";

        while (getline(in, line)) {
            if (line.find(date) == 0) { // Match date
                cout << line << endl;
                found = true;
            }
        }

        if (!found) {
            cout << "No hackathons found for " << date << ".\n";
        }

        in.close();
    }

    void markCompleted(const string& taskDetails) {
        ifstream in("hackathon_list.txt");
        ofstream out("temp.txt");

        if (!in.is_open() || !out.is_open()) {
            cout << "\nError: Could not access the hackathon file.\n";
            return;
        }

        string line;
        bool found = false;

        while (getline(in, line)) {
            if (line.find(taskDetails) != string::npos) { // Match task details
                found = true;
                out << line.substr(0, line.find("| Not Completed")) << "| Completed" << endl;
            } else {
                out << line << endl;
            }
        }

        in.close();
        out.close();

        remove("hackathon_list.txt");
        rename("temp.txt", "hackathon_list.txt");

        if (found) {
            cout << "\nHackathon task marked as completed.\n";
        } else {
            cout << "\nHackathon task not found.\n";
        }
    }
};
class Game {
protected:
    string name;
public:
    Game(string n) : name(n) {} //Constructor to initialize
    virtual void play() = 0; // Pure virtual function
    string getName() { return name; }
};

// Physical Game class
class PhysicalGame : public Game {
public:
    PhysicalGame(string n) : Game(n) {} //constructor
    void play() override {
        cout << "Playing a physical game: " << name << endl;
    }
};

// PC Game class
class PCGame : public Game {
public:
    PCGame(string n) : Game(n) {} //constructor
    virtual void play() override {
        cout << "Playing a PC game: " << name << endl;
    }
};

// Rock-Paper-Scissors Class
class RockPaperScissors : public PCGame {
public:
    RockPaperScissors() : PCGame("Rock-Paper-Scissors") {} //constructor

    void play() override {
        int userScore = 0, computerScore = 0;//default
        //for round 1 to 3 do
        for (int round = 1; round <= 3; round++) {
            cout << "\n===== Round-" << round << " =====\n";

            char player = getUserChoice(); //for user choice rock,paper,scissor
            cout << "Your Choice: ";
            showChoice(player);

            char computer = getComputerChoice(); //for computer choice rock,paper,scissor(randomly)
            cout << "Computer's Choice: ";
            showChoice(computer);

            int result = chooseWinner(player, computer);
            if (result == 1) userScore++;
            else if (result == -1) computerScore++;

            cout << "Score: You [" << userScore << "] - Computer [" << computerScore << "]\n";
        }

        // Determine final winner
        cout << "\n===== Final Result =====\n";
        if (userScore > computerScore) cout << "?? You win the game!\n";
        else if (userScore < computerScore) cout << "?? Computer wins the game!\n";
        else cout << "?? It's a tie!\n";
    }

private:
    char getUserChoice() {
        char player;
        do {
            cout << "------------------------------\n";
            cout << "| Rock-Paper-Scissors GAME!  |\n";
            cout << "------------------------------\n";
            cout << "| Choose one of the following: |\n";
            cout << "------------------------------\n";
            cout << "'r' for Rock\n";
            cout << "'p' for Paper\n";
            cout << "'s' for Scissors\n";
            cout<<"\nHere:";
            cin >> player;
        } while (player != 'r' && player != 'p' && player != 's');

        return player;
    }

    char getComputerChoice() {
        int num = rand() % 3; //ctime use for using rand() function
        switch (num) {
            case 0: return 'r';
            case 1: return 'p';
            case 2: return 's';
        }
        return 'r';
    }

    void showChoice(char choice) {
        switch (choice) {
            case 'r': cout << "Rock\n"; break;
            case 'p': cout << "Paper\n"; break;
            case 's': cout << "Scissors\n"; break;
        }
    }

    int chooseWinner(char player, char computer) {
        if (player == computer) {
            cout << "It's a tie!\n";
            return 0;
        }
        else if ((player == 'r' && computer == 's') ||
                 (player == 'p' && computer == 'r') ||
                 (player == 's' && computer == 'p')) {
            cout << "You win this round!\n";
            return 1;
        }
        else {
            cout << "You lose this round!\n";
            return -1;
        }
    }
};

// Tic-Tac-Toe Game Class
class TicTacToe : public PCGame {
public:
    TicTacToe() : PCGame("Tic Tac Toe") {}

    void play() override {
        cout << "Starting Tic Tac Toe game...\n";
        startGame();
    }

private:
    int currentplayer;
    char currentmarker;
    char board[3][3] = {{'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'}};  //dynamic array is used here hence we have used vector library

    void drawboard() {
        cout << "----------------------\n";
        cout << "| Tic-Tac-Toe GAME!  |\n";
        cout << "----------------------\n";
        cout << " " << board[0][0] << " | " << board[0][1] << " | " << board[0][2] << "\n";
        cout << "---|---|---\n";
        cout << " " << board[1][0] << " | " << board[1][1] << " | " << board[1][2] << "\n";
        cout << "---|---|---\n";
        cout << " " << board[2][0] << " | " << board[2][1] << " | " << board[2][2] << "\n";
    }

    bool placemarker(int slot) {
        int row = (slot - 1) / 3;
        int col = (slot - 1) % 3;
        if (board[row][col] != 'X' && board[row][col] != 'O') {
            board[row][col] = currentmarker;
            return true;
        }
        return false;
    }

    int winner() {
        for (int i = 0; i < 3; i++)
            if (board[i][0] == board[i][1] && board[i][1] == board[i][2])
                return currentplayer;
        for (int i = 0; i < 3; i++)
            if (board[0][i] == board[1][i] && board[1][i] == board[2][i])
                return currentplayer;
        if (board[0][0] == board[1][1] && board[1][1] == board[2][2])
            return currentplayer;
        if (board[0][2] == board[1][1] && board[1][1] == board[2][0])
            return currentplayer;
        return 0;
    }

    void swap() {
        currentmarker = (currentmarker == 'X') ? 'O' : 'X';
        currentplayer = (currentplayer == 1) ? 2 : 1;
    }

    void startGame() {
        cout << "Player 1 choose your marker [X or O]: ";
        char markerP1;
        cin >> markerP1;

        while (markerP1 != 'X' && markerP1 != 'O') {
            cout << "Invalid choice. Choose X or O: ";
            cin >> markerP1;
        }

        currentplayer = 1;
        currentmarker = markerP1;
        char markerP2 = (markerP1 == 'X') ? 'O' : 'X';

        drawboard();
        int playerwon = 0;
        //for 1 to 9 do due to 9 slots
        for (int i = 0; i < 9; i++) {
            cout << "It's Player " << currentplayer << "'s turn. Enter your slot: ";
            int slot;
            cin >> slot;

            if (slot < 1 || slot > 9) {
                cout << "Invalid slot! Try again.\n";
                i--;
                continue;
            }

            if (!placemarker(slot)) {
                cout << "Slot occupied! Try again.\n";
                i--;
                continue;
            }

            drawboard();
            playerwon = winner();

            if (playerwon) {
                cout << "Player " << playerwon << " wins!\n";
                break;
            }

            swap();
        }

        if (playerwon == 0) cout << "It's a tie!\n";
    }
};

// Hangman Class
class Hangman : public PCGame {
public:
    Hangman() : PCGame("Hangman") {}
    void play() override {
/*dynamic*/vector<string> words = {"apple", "banana", "orange", "grape", "mango", "papaya", "kiwi", "watermelon"};
        string word = words[rand() % words.size()];
        vector<bool> guessed(word.length(), false);
        int attempts = 6;
        char guess;
        cout << "\n--------------------------------------\n";
        cout << "\n|Welcome to Hangman! (Fruits Chapter)|\n";
        cout << "\n--------------------------------------\n";
        while (attempts > 0) {
            displayWord(word, guessed);
            cout << "Attempts left: " << attempts << "\nGuess a letter: ";
            cin >> guess;
            bool correct = false;
            for (size_t i = 0; i < word.length(); i++) {
                if (word[i] == guess) { guessed[i] = true; correct = true; }
            }
            if (!correct) { attempts--; cout << "Wrong guess!\n"; }
            if (isWordGuessed(guessed)) {
                cout << "Congratulations! You guessed the word: " << word << "\n";
                return;
            }
        }
        cout << "Game Over! The word was: " << word << "\n";
    }

private:
    void displayWord(const string& word, const vector<bool>& guessed) {
        for (size_t i = 0; i < word.length(); i++) {
            cout << (guessed[i] ? word[i] : '_') << " ";
        }
        cout << endl;
    }

    bool isWordGuessed(const vector<bool>& guessed) {
        for (bool g : guessed) { if (!g) return false; }
        return true;
    }
};
// FoodSchedule Class (for Student)
class FoodScheduleView {
    map<string, map<string, vector<string>>> schedule; // Map to store schedule for each day and meal type

public:
    void loadSchedule() {
        schedule.clear();
        ifstream file("food_schedule.txt");
        string day, mealType, foodItem;
        while (getline(file, day)) {
            map<string, vector<string>> dailySchedule;
            while (getline(file, mealType) && mealType != "---") {
                vector<string> foodItems;
                while (getline(file, foodItem) && foodItem != "***") {
                    foodItems.push_back(foodItem);
                }
                dailySchedule[mealType] = foodItems;
            }
            schedule[day] = dailySchedule;
        }
        file.close();
    }

    void displayFoodView(const string &day) {
        // Check if the day exists in the schedule
        if (schedule.find(day) != schedule.end()) {
            cout << "\n+-----------------------------------------+" << endl;
            cout << "| Food Schedule for Day: " << day;
            for (size_t i = 0; i < 38 - day.length(); ++i)
                cout << " "; // Padding to align the vertical border
            cout << "|" << endl;
            cout << "+-----------------------------------------+" << endl;

            // Display meals for the day
            for (const auto &mealSchedule : schedule[day]) {
                cout << "|  " << mealSchedule.first << ":" << endl;
                for (size_t i = 0; i < mealSchedule.second.size(); ++i) {
                    cout << "|    " << i + 1 << ". " << mealSchedule.second[i];
                    int padding = 40 - (5 + to_string(i + 1).length() + mealSchedule.second[i].length());
                    for (int j = 0; j < padding; ++j)
                        cout << " "; // Padding to align the vertical border
                    cout << "|" << endl;
                }
            }
            cout << "+-----------------------------------------+" << endl;
        } else {
            cout << "No food schedule found for " << day << ".\n";
        }
    }
};
class Attendance {
private:
    static const int MAX_RECORDS = 100; // Maximum number of attendance records
    static const int MAX_SUBJECTS = 10; // Maximum number of subjects

    string dates[MAX_RECORDS];      // Stores dates (YYYY-MM-DD)
    string subjects[MAX_RECORDS][MAX_SUBJECTS]; // Subjects for each date
    bool attendance[MAX_RECORDS][MAX_SUBJECTS]; // Attendance for each subject (1 = Present, 0 = Absent)
    int subjectCounts[MAX_RECORDS]; // Tracks the number of subjects per date
    int recordCount;                // Tracks the number of records (dates)

    string fileName; // File name for storing attendance data

    // Validate date format (yyyy-mm-dd)
    bool isValidDate(const string& date) {
        regex pattern(R"(^\d{4}-(0[1-9]|1[0-2])-(0[1-9]|[1-2][0-9]|3[0-1])$)");
        return regex_match(date, pattern);
    }

public:
    // Constructor
    Attendance(string file = "attendance_data.txt") {
        fileName = file;
        recordCount = 0;
        loadFromFile();
    }

    // Add attendance for a specific date
    void addAttendance() {
        if (recordCount >= MAX_RECORDS) {
            cout << "Error: Maximum attendance records reached.\n";
            return;
        }

        string date;
        do {
            cout << "Enter the date (YYYY-MM-DD): ";
            cin >> date;
            if (!isValidDate(date)) {
                cout << "Invalid date format! Please enter the date in the format yyyy-mm-dd.\n";
            }
        } while (!isValidDate(date)); // Repeat until a valid date is entered

        dates[recordCount] = date;
        subjectCounts[recordCount] = 0;

        char addMoreSubjects = 'y';
        while ((addMoreSubjects == 'y' || addMoreSubjects == 'Y') && subjectCounts[recordCount] < MAX_SUBJECTS) {
            string subject;
            char wasPresent;

            cout << "Enter the subject name: ";
            cin.ignore(); // Clear input buffer
            getline(cin, subject);

            cout << "Were you present in " << subject << "? (P/A): ";
            cin >> wasPresent;

            subjects[recordCount][subjectCounts[recordCount]] = subject;
            attendance[recordCount][subjectCounts[recordCount]] = (wasPresent == 'P' || wasPresent == 'p');
            subjectCounts[recordCount]++;

            cout << "Do you want to add another subject? (Y/N): ";
            cin >> addMoreSubjects;
        }

        recordCount++;
        cout << "Attendance recorded successfully for " << date << ".\n";
        saveToFile();
    }

    // View attendance record for a specific date
    void viewAttendanceRecord() {
        string date;
        cout << "Enter the date (YYYY-MM-DD): ";
        cin >> date;

        int index = findRecord(date);
        if (index == -1) {
            cout << "No attendance record found for " << date << ".\n";
            return;
        }

        cout << "\nAttendance record for " << date << ":\n";
        for (int i = 0; i < subjectCounts[index]; i++) {
            cout << "Subject: " << subjects[index][i] << " - " << (attendance[index][i] ? "Present" : "Absent") << "\n";
        }
    }

    // Calculate attendance percentage for all subjects
    void calculateAttendancePercentage() {
        int totalClasses[MAX_SUBJECTS] = {0};
        int attendedClasses[MAX_SUBJECTS] = {0};
        string uniqueSubjects[MAX_SUBJECTS];
        int uniqueSubjectCount = 0;

        for (int i = 0; i < recordCount; i++) {
            for (int j = 0; j < subjectCounts[i]; j++) {
                // Check if the subject already exists in uniqueSubjects
                int subjectIndex = findSubject(uniqueSubjects, uniqueSubjectCount, subjects[i][j]);

                if (subjectIndex == -1) { // New subject
                    uniqueSubjects[uniqueSubjectCount] = subjects[i][j];
                    subjectIndex = uniqueSubjectCount;
                    uniqueSubjectCount++;
                }

                totalClasses[subjectIndex]++;
                if (attendance[i][j]) {
                    attendedClasses[subjectIndex]++;
                }
            }
        }

        // Display attendance percentages and remarks
        cout << "\n--- Attendance Report ---\n";
        for (int i = 0; i < uniqueSubjectCount; i++) {
            float percentage = (float(attendedClasses[i]) / totalClasses[i]) * 100;
            cout << "Subject: " << uniqueSubjects[i] << "\n";
            cout << "Attendance Percentage: " << fixed << setprecision(2) << percentage << "%\n";

            // Provide remarks
            if (percentage >= 90) {
                cout << "Remark: Good! Your attendance is on mark.\n";
            } else if (percentage >= 70) {
                cout << "Remark: Don't worry, but keep it up!\n";
            } else {
                cout << "Remark: You should attend classes regularly.\n";
            }
            cout << "---------------------------\n";
        }
    }

    // Save attendance data to a file
    void saveToFile() {
        ofstream outFile(fileName.c_str());
        if (!outFile.is_open()) {
            cout << "Error: Could not open file for saving.\n";
            return;
        }

        outFile << recordCount << "\n";
        for (int i = 0; i < recordCount; i++) {
            outFile << dates[i] << "\n";
            outFile << subjectCounts[i] << "\n";

            for (int j = 0; j < subjectCounts[i]; j++) {
                outFile << subjects[i][j] << " " << attendance[i][j] << "\n";
            }
        }

        outFile.close();
        cout << "Attendance data saved successfully to " << fileName << ".\n";
    }

    // Load attendance data from a file
    void loadFromFile() {
        ifstream inFile(fileName.c_str());
        if (!inFile.is_open()) {
            cout << "No previous attendance data found. Starting fresh.\n";
            return;
        }

        inFile >> recordCount;
        inFile.ignore();

        for (int i = 0; i < recordCount; i++) {
            getline(inFile, dates[i]);
            inFile >> subjectCounts[i];
            inFile.ignore();

            for (int j = 0; j < subjectCounts[i]; j++) {
                getline(inFile, subjects[i][j], ' ');
                inFile >> attendance[i][j];
                inFile.ignore();
            }
        }

        inFile.close();
    }

private:
    // Find record by date
    int findRecord(const string& date) {
        for (int i = 0; i < recordCount; i++) {
            if (dates[i] == date) {
                return i;
            }
        }
        return -1; // Not found
    }

    // Find subject in unique subjects array
    int findSubject(const string uniqueSubjects[], int count, const string& subject) {
        for (int i = 0; i < count; i++) {
            if (uniqueSubjects[i] == subject) {
                return i;
            }
        }
        return -1; // Not found
    }
};
class Student {
private:
    string name;
    string email;
    string password;

public:
    // Function to register a new student
    void registerStudent() {
        cout << "\n--- Student Registration ---" << endl;

        // Input Name
        cout << "Enter your Name: ";
        cin.ignore();
        getline(cin, name);

        // Input Email
        cout << "Enter your Email (e.g., user@example.com): ";
        cin >> email;

        // Input Password with masking
        cout << "Set your Password: ";
        char ch;
        password.clear();
        while ((ch = getch()) != '\r') { // Read characters until Enter is pressed
            if (ch == '\b') { // Handle backspace
                if (!password.empty()) {
                    password.pop_back();
                    cout << "\b \b"; // Erase character from screen
                }
            } else {
                password += ch;
                cout << '*'; // Show '*' for password input
            }
        }
        cout << endl;

        // Save registration details to a file
        ofstream outfile("student_data.txt", ios::app);
        if (outfile.is_open()) {
            outfile << name << "," << email << "," << password << endl;
            outfile.close();
            cout << "\nRegistration successful!" << endl;
        } else {
            cerr << "Error: Unable to save data!" << endl;
        }
    }

    // Function to login the student
    bool loginStudent() {
        cout << "\n--- Student Login ---" << endl;

        string inputEmail, inputPassword;

        // Input Email
        cout << "Enter your Email: ";
        cin >> inputEmail;

        // Input Password with masking
        cout << "Enter your Password: ";
        char ch;
        inputPassword.clear();
        while ((ch = getch()) != '\r') { // Read characters until Enter is pressed
            if (ch == '\b') { // Handle backspace
                if (!inputPassword.empty()) {
                    inputPassword.pop_back();
                    cout << "\b \b"; // Erase character from screen
                }
            } else {
                inputPassword += ch;
                cout << '*'; // Show '*' for password input
            }
        }
        cout << endl;

        // Validate login credentials
        ifstream infile("student_data.txt");
        string line;
        while (getline(infile, line)) {
            size_t pos1 = line.find(',');
            size_t pos2 = line.rfind(',');

            string fileName = line.substr(0, pos1);
            string fileEmail = line.substr(pos1 + 1, pos2 - pos1 - 1);
            string filePassword = line.substr(pos2 + 1);

            if (inputEmail == fileEmail && inputPassword == filePassword) {
                cout << "\nLogin successful! Welcome, " << fileName << "!" << endl;
                infile.close();
                return true;
            }
        }
        infile.close();
        cout << "\nInvalid email or password! Please try again." << endl;
        return false;
    }
    // Function to display the post-login menu
   void postLoginMenu() {
    int choice;
    do {
        cout << "\n--- Student Menu ---" << endl;
        cout << "1. To-Do List" << endl;
        cout << "2. Play Games" << endl;
        cout << "3. Food Menu" << endl;
        cout << "4. Class Attendance" << endl;
        cout << "5. Logout" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
    ClassSchedule classSchedule; // Class Schedule object
    SelfStudySchedule selfStudySchedule; // Self Study Schedule object
    FiveFoldActivity fiveFoldActivity;
    Assignment assignment;
    Hackathon hackathon;
    Attendance attendance;
        switch (choice) {
        case 1: { // To-Do List Menu
            {
    int todoOption;
    do {
        cout << "\n1. CREATE TO-DO LIST AND READ TO-DO LIST\n2. BACK TO MAIN MENU";
        cout << "\nENTER YOUR CHOICE: ";
        cin >> todoOption;

        switch (todoOption) {
        case 1: {
            int taskType;
            do {
                cout << "\n1. STUDY SCHEDULE\n2. OTHER ACTIVITIES\n3. BACK";
                cout << "\nENTER YOUR CHOICE: ";
                cin >> taskType;

                switch (taskType) {
                case 1: { // Study Schedule
                    int studyOption;
                    do {
                        cout << "\n1. CLASS STUDY SCHEDULE\n2. SELF-STUDY SCHEDULE\n3.EXAM SCHEDULE\n4.BACK TO PREVIOUS MENU";
                        cout << "\nENTER YOUR CHOICE: ";
                        cin >> studyOption;

                        switch (studyOption) {
                        case 1: {
                            int classOption;
                            do {
                                cout << "\n1. ADD CLASS SCHEDULE\n2. VIEW TODAY'S CLASS SCHEDULE\n3. BACK";
                                cout << "\nENTER YOUR CHOICE: ";
                                cin >> classOption;

                                switch (classOption) {
                                case 1:
                                    classSchedule.addSchedule();
                                    break;
                                case 2:
                                    classSchedule.viewSchedule();
                                    break;
                                case 3:
                                    cout << "Returning to study schedule menu...\n";
                                    break;
                                default:
                                    cout << "Invalid choice! Try again.\n";
                                }
                            } while (classOption != 3); // Back to "Study Schedule" menu
                            break;
                        }

                        case 2: {
                            int selfStudyOption;
                            do {
                                cout << "\n1. ADD SELF-STUDY SCHEDULE\n2. VIEW TODAY'S SELF-STUDY SCHEDULE\n3. BACK";
                                cout << "\nENTER YOUR CHOICE: ";
                                cin >> selfStudyOption;

                                switch (selfStudyOption) {
                                case 1:
                                    selfStudySchedule.addSchedule();
                                    break;
                                case 2:
                                    selfStudySchedule.viewSchedule();
                                    break;
                                case 3:
                                    cout << "Returning to study schedule menu...\n";
                                    break;
                                default:
                                    cout << "Invalid choice! Try again.\n";
                                }
                            } while (selfStudyOption != 3); // Back to "Study Schedule" menu
                            break;
                        }
                       case 3: { // Exam Timetable Menu
    ExamTimetable examTimetable;
    int examOption;
    do {
        cout << "\n--- EXAM TIMETABLE MENU ---";
        cout << "\n1. ADD EXAM TIMETABLE";
        cout << "\n2. VIEW EXAM TIMETABLE";
        cout << "\n3. BACK TO MAIN MENU";
        cout << "\nENTER YOUR CHOICE: ";
        cin >> examOption;

        switch (examOption) {
        case 1:
            examTimetable.addExamSchedule();
            break;
        case 2:
            examTimetable.viewExamSchedule();
            break;
        case 3:
            cout << "Returning to main menu...\n";
            break;
        default:
            cout << "Invalid choice! Please try again.\n";
        }
    } while (examOption != 3);
    break;
}
                        case 4:
                            cout << "Returning to task type menu...\n";
                            break;

                        default:
                            cout << "Invalid choice! Try again.\n";
                        }
                    } while (studyOption != 4); // Back to "Task Type" menu
                    break;
                }

                case 2: { // Other Activities
                    int mainOption; // Main menu option
                    do {
                        cout << "\n================= MAIN MENU =================";
                        cout << "\n1. MANAGE FIVE-FOLD ACTIVITIES";
                        cout << "\n2. MANAGE ASSIGNMENTS";
                        cout << "\n3. MANAGE HACKATHONS";
                        cout << "\n4. EXIT";
                        cout << "\n============================================";
                        cout << "\nEnter your choice: ";
                        cin >> mainOption;

                        switch (mainOption) {
                        case 1: { // Manage Five-Fold Activities
                            int fiveFoldOption;
                            do {
                                cout << "\n======== FIVE-FOLD ACTIVITIES MENU =========";
                                cout << "\n1. ADD FIVE-FOLD ACTIVITY";
                                cout << "\n2. VIEW FIVE-FOLD ACTIVITIES";
                                cout << "\n3. BACK TO MAIN MENU";
                                cout << "\n============================================";
                                cout << "\nEnter your choice: ";
                                cin >> fiveFoldOption;

                                switch (fiveFoldOption) {
                                case 1:
                                    fiveFoldActivity.addActivity();
                                    break;
                                case 2: {
                                    string date;
                                    cout << "Enter the date to view activities (dd-mm-yy): ";
                                    cin.ignore();
                                    getline(cin, date);
                                    fiveFoldActivity.viewActivity(date);
                                    break;
                                }
                                case 3:
                                    cout << "Returning to Main Menu...\n";
                                    break;
                                default:
                                    cout << "Invalid choice! Please try again.\n";
                                }
                            } while (fiveFoldOption != 3);
                            break;
                        }

                        case 2: { // Manage Assignments
                            int assignmentOption;
                            do {
                                cout << "\n============= ASSIGNMENTS MENU =============";
                                cout << "\n1. ADD ASSIGNMENT";
                                cout << "\n2. VIEW ASSIGNMENTS";
                                cout << "\n3. MARK ASSIGNMENT AS COMPLETED";
                                cout << "\n4. BACK TO MAIN MENU";
                                cout << "\n============================================";
                                cout << "\nEnter your choice: ";
                                cin >> assignmentOption;

                                switch (assignmentOption) {
                                case 1:
                                    assignment.addActivity();
                                    break;
                                case 2: {
                                    string date;
                                    cout << "Enter the date to view assignments (dd-mm-yy): ";
                                    cin.ignore();
                                    getline(cin, date);
                                    assignment.viewActivity(date);
                                    break;
                                }
                                case 3: {
                                    string details;
                                    cout << "Enter the assignment details to mark as completed: ";
                                    cin.ignore();
                                    getline(cin, details);
                                    assignment.markCompleted(details);
                                    break;
                                }
                                case 4:
                                    cout << "Returning to Main Menu...\n";
                                    break;
                                default:
                                    cout << "Invalid choice! Try again.\n";
                                }
                            } while (assignmentOption != 4);
                            break;
                        }

                        case 3: { // Manage Hackathons
                            int hackathonOption;
                            do {
                                cout << "\n=============== HACKATHONS MENU ============";
                                cout << "\n1. ADD HACKATHON";
                                cout << "\n2. VIEW HACKATHONS";
                                cout << "\n3. MARK HACKATHON AS COMPLETED";
                                cout << "\n4. BACK TO MAIN MENU";
                                cout << "\n============================================";
                                cout << "\nEnter your choice: ";
                                cin >> hackathonOption;

                                switch (hackathonOption) {
                                case 1:
                                    hackathon.addActivity();
                                    break;
                                case 2: {
                                    string date;
                                    cout << "Enter the date to view hackathons (dd-mm-yy): ";
                                    cin.ignore();
                                    getline(cin, date);
                                    hackathon.viewActivity(date);
                                    break;
                                }
                                case 3: {
                                    string details;
                                    cout << "Enter the hackathon details to mark as completed: ";
                                    cin.ignore();
                                    getline(cin, details);
                                    hackathon.markCompleted(details);
                                    break;
                                }
                                case 4:
                                    cout << "Returning to Main Menu...\n";
                                    break;
                                default:
                                    cout << "Invalid choice! Try again.\n";
                                }
                            } while (hackathonOption != 4);
                            break;
                        }

                        case 4:
                            cout << "Returning to Main Menu...\n";
                            break;

                        default:
                            cout << "Invalid choice! Please try again.\n";
                        }
                    } while (mainOption != 4);
                    break;
                }

                case 3:
                    cout << "Returning to main menu...\n";
                    break;

                default:
                    cout << "Invalid choice! Try again.\n";
                }
            } while (taskType != 3);
            break;
        }
        case 2: cout << "Returning to main menu...\n";
                    break;
        default:
               cout << "Invalid choice! Try again.\n";    
    }
}while(todoOption!=2);
}
            case 2:
            {
                srand(time(0));
    vector<PhysicalGame> physicalGames = {PhysicalGame("Badminton"), PhysicalGame("Football"), PhysicalGame("Cricket"),
        PhysicalGame("Volleyball"), PhysicalGame("Basketball"), PhysicalGame("Pakdam Pakdai"),
        PhysicalGame("Hide & Seek"), PhysicalGame("Hockey"), PhysicalGame("Gully Danda"),
        PhysicalGame("Hand Ball")};
vector<PCGame*> pcGames = {new TicTacToe(), new RockPaperScissors(), new Hangman()};
            while (true) {
        int choice;
        cout << "\nSelect game type:\n1. Physical Games\n2. PC Games\n3. Exit\nEnter choice: ";
        cin >> choice;
        if (choice == 3) {
            cout << "\nGood to have you on board\nLet's meet next time!\n";
            break;
        }
        if (choice == 1) {
            cout << "Available Physical Games:\n";
            for (size_t i = 0; i < physicalGames.size(); ++i)
                cout << i + 1 << ". " << physicalGames[i].getName() << endl;
            cout << "\nThese are some common games you can choose your own also!!\nPhysical games are good for body,\nthey make you Fit & Healthy.\n";
            break;
        }
        else if (choice == 2) {
            cout << "\nAvailable PC Games:\n";
            for (size_t i = 0; i < pcGames.size(); ++i)
                cout << i + 1 << ". " << pcGames[i]->getName() << endl;
            int gameChoice;
            cout << "Select a game to play: ";
            cin >> gameChoice;
            if (gameChoice > 0 && gameChoice <= pcGames.size())
                pcGames[gameChoice - 1]->play();
            else
                cout << "Invalid choice!\n";
        }
        for (auto game : pcGames) delete game; // Clean up dynamically allocated memory
break;
}
}

       case 3:
                {
    FoodScheduleView foodView;

    int choice;
    foodView.loadSchedule(); // Load the food schedule from file

  do {
        cout << "\n1. View Food Schedule\n2. Exit\nChoose an option: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string day,h;
                cout<<"Hostel name:";
                cin>>h;
                cout << "Enter Day Name (e.g., Monday): ";
                cin.ignore();
                getline(cin, day);
                foodView.displayFoodView(day);
                break;
            }
            case 2:
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid option.\n";
                break;
        }
    }
    while(choice!=2);
break;
}
            case 4:
                {
    char continueChoice;
    do {
        int choice;
        cout << "\n========== ATTENDANCE SYSTEM ==========";
        cout << "\n1. Add Attendance";
        cout << "\n2. View Attendance Record";
        cout << "\n3. Calculate Attendance Percentage";
        cout << "\n4. Exit";
        cout << "\n=======================================";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            attendance.addAttendance();
            break;
        case 2:
            attendance.viewAttendanceRecord();
            break;
        case 3:
            attendance.calculateAttendancePercentage();
            break;
        case 4:
            cout << "Exiting... Goodbye!\n";
            break;
        default:
            cout << "Invalid choice! Please try again.\n";
            break;
        }

        cout << "\nDo you want to continue? (Y/N): ";
        cin >> continueChoice;

    } while (continueChoice == 'Y' || continueChoice == 'y');
    break;
}
            case 5:
                cout << "\nLogging out..." << endl;
                break;
            default:
                cout << "\nInvalid choice! Please try again." << endl;
            }
        }
    }while (choice != 5);
}
};

// Function to display the main menu
void displayMainMenu() {
    cout << "\n--- Main Menu ---" << endl;
    cout << "1. Warden" << endl;
    cout << "2. Student" << endl;
    cout << "3. Exit" << endl;
    cout << "Enter your choice: ";
}

// Main Function
int main() {
    // Declare objects and variables needed
    HostelWarden warden;
    SelfStudySchedule selfStudySchedule;
    FiveFoldActivity fiveFoldActivity;
    Assignment assignment;
    Hackathon hackathon;
    FoodSchedule schedule;
    Student student;
    
    int choice;

    do {
        menu(); // Display the main menu
        cout << "\nEnter any key to continue:\n";
        getch(); // Wait for input
        cout << "Enter your choice: ";
        cin >> choice;
        system("cls"); // Clear the screen

        switch (choice) {
            case 1: { // Food Schedule Manager
                int manageChoice;
                do {
                    cout << "\n+-----------------------------------------------------------------------------------+\n";
                    cout << "|======================= FOOD SCHEDULE MANAGER =========================|\n";
                    cout << "+-----------------------------------------------------------------------------------+\n";
                    cout << "| 1. Register Warden                                                                |\n";
                    cout << "| 2. Login                                                                          |\n";
                    cout << "| 3. Exit                                                                           |\n";
                    cout << "+-----------------------------------------------------------------------------------+\n";
                    cout << "\n-> Choose an option: ";
                    cin >> manageChoice;

                    switch (manageChoice) {
                        case 1: // Register Warden
                            cout << "\n+-----------------------------------------------------------------------------------+\n";
                            cout << "|============================= REGISTER YOURSELF ===================================|\n";
                            cout << "+-----------------------------------------------------------------------------------+\n";
                            warden.registerWarden();
                            system("cls");
                            break;

                        case 2: // Login
                            cout << "\n+-----------------------------------------------------------------------------------+\n";
                            cout << "|============================ LOGIN TO YOUR DASHBOARD ==============================|\n";
                            cout << "+-----------------------------------------------------------------------------------+\n";
                            if (warden.login()) {
                                system("cls");
                                schedule.loadSchedule();
                                int scheduleChoice;
                                do {
                                    cout << "\n+-----------------------------------------------------------------------------------+\n";
                                    cout << "| 1. Add Food Item                                                                  |\n";
                                    cout << "| 2. Display Schedule                                                               |\n";
                                    cout << "| 3. Update Food Item                                                               |\n";
                                    cout << "| 4. Delete Food Item                                                               |\n";
                                    cout << "| 5. Logout                                                                         |\n";
                                    cout << "+-----------------------------------------------------------------------------------+\n";
                                    cout << "\n-> Choose an option: ";
                                    cin >> scheduleChoice;

                                    switch (scheduleChoice) {
                                        case 1: schedule.addFoodItem(); break;
                                        case 2: schedule.displaySchedule(); break;
                                        case 3: schedule.updateFoodItem(); break;
                                        case 4: schedule.deleteFoodItem(); break;
                                        case 5: cout << "\n|============================ LOGGED OUT SUCCESSFULLY ===============================|\n"; break;
                                        default: cout << "Invalid option.\n"; break;
                                    }
                                } while (scheduleChoice != 5);
                            }
                            break;

                        case 3:
                            cout << "\n|======================== EXIT....PORTAL CLOSED....SEE YOU UNTIL NEXT TIME ===========================|\n";
                            break;

                        default:
                            cout << "Invalid option.\n";
                            break;
                    }
                } while (manageChoice != 3);
                break;
            }

            case 2: { // Student Menu
                student.registerStudent();
                if (student.loginStudent()) {
                    student.postLoginMenu();
                } else {
                    cout << "\nIncorrect password.\n";
                }
                break;
            }

            case 3:
                cout << "\nExiting the program.\n";
                break;

            default:
                cout << "Invalid or unhandled input.\n";
                break;
        }
    } while (choice != 3);

    return 0;
}
