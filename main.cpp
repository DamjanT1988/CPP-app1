#include <iostream> // Input-output stream for std::cin, std::cout, etc.
#include <string>   // String handling with std::string
#include <vector>   // Dynamic array handling with std::vector
#include <fstream>  // File stream handling with std::fstream, std::ifstream, std::ofstream

/// Define a class named TodoItem to represent a single to-do item.
class TodoItem {
public:
    // Constructor to initialize the TodoItem with a description and an optional completed status (default is false).
    TodoItem(const std::string &description, bool completed = false)
        : description(description), completed(completed) {}

    // Getter for the description of the to-do item.
    std::string getDescription() const { return description; }

    // Getter to check if the to-do item is completed.
    bool isCompleted() const { return completed; }

    // Method to mark the to-do item as completed.
    void complete() { completed = true; }

    // Method to return a string representation of the to-do item for saving to a file.
    std::string toString() const {
        return description + (completed ? " [Completed]" : "");
    }

    // Static method to create a TodoItem from a string (used for loading from a file).
    static TodoItem fromString(const std::string &str) {
        size_t pos = str.find(" [Completed]");
        if (pos != std::string::npos) {
            return TodoItem(str.substr(0, pos), true);
        } else {
            return TodoItem(str, false);
        }
    }

private:
    std::string description; // Description of the to-do item.
    bool completed;          // Completion status of the to-do item.
};

/// Define a class named TodoList to manage a list of to-do items.
class TodoList {
public:
    // Constructor to initialize the TodoList and load items from the file.
    TodoList() {
        loadFromFile();
    }

    // Destructor to save items to the file when the program exits.
    ~TodoList() {
        saveToFile();
    }

    // Method to add a new to-do item to the list.
    void addItem(const std::string &description) {
        items.push_back(TodoItem(description)); // Adds a new TodoItem to the vector of items.
        saveToFile(); // Save the updated list to the file.
    }

    // Method to mark a to-do item as completed based on its index in the list.
    void completeItem(size_t index) {
        if (index < items.size()) { // Check if the index is valid (within the range of the vector).
            items[index].complete(); // Mark the item as completed.
            saveToFile(); // Save the updated list to the file.
        } else {
            std::cerr << "Invalid index\n"; // Print an error message if the index is invalid.
        }
    }

    // Method to list all to-do items.
    void listItems() const {
        for (size_t i = 0; i < items.size(); ++i) { // Loop through each item in the vector.
            // Print the item index, description, and completion status.
            std::cout << i + 1 << ". " << items[i].toString() << "\n";
        }
    }

private:
    std::vector<TodoItem> items; // A vector to store the list of to-do items.

    // Method to save the to-do list to a file.
    void saveToFile() const {
        std::ofstream file("todolist.txt"); // Open the file for writing.
        if (file.is_open()) { // Check if the file is successfully opened.
            for (const auto &item : items) {
                file << item.toString() << "\n"; // Write each item to the file.
            }
            file.close(); // Close the file.
        } else {
            std::cerr << "Unable to open file for writing\n"; // Print an error message if the file cannot be opened.
        }
    }

    // Method to load the to-do list from a file.
    void loadFromFile() {
        std::ifstream file("todolist.txt"); // Open the file for reading.
        if (file.is_open()) { // Check if the file is successfully opened.
            std::string line;
            while (getline(file, line)) {
                items.push_back(TodoItem::fromString(line)); // Read each line and create a TodoItem from it.
            }
            file.close(); // Close the file.
        } else {
            std::cerr << "Unable to open file for reading\n"; // Print an error message if the file cannot be opened.
        }
    }
};

// Function to display the menu options to the user.
void displayMenu() {
    std::cout << "1. Add a to-do item\n"
              << "2. Complete a to-do item\n"
              << "3. List all to-do items\n"
              << "4. Exit\n";
}

// Main function: the entry point of the program.
int main() {
    TodoList todoList; // Create an instance of TodoList to manage the to-do items.
    int choice;        // Variable to store the user's menu choice.

    // Infinite loop to keep the program running until the user chooses to exit.
    while (true) {
        displayMenu(); // Display the menu options.
        std::cout << "Enter your choice: ";
        std::cin >> choice; // Read the user's choice.

        if (choice == 1) { // If the user chooses to add a new item:
            std::cin.ignore(); // Ignore the newline character left in the input buffer.
            std::string description;
            std::cout << "Enter the description: ";
            std::getline(std::cin, description); // Read the description of the new to-do item.
            todoList.addItem(description); // Add the new item to the to-do list.
        } else if (choice == 2) { // If the user chooses to complete an item:
            size_t index;
            std::cout << "Enter the index of the item to complete: ";
            std::cin >> index; // Read the index of the item to complete.
            todoList.completeItem(index - 1); // Mark the item as completed (adjusting for zero-based index).
        } else if (choice == 3) { // If the user chooses to list all items:
            todoList.listItems(); // List all to-do items.
        } else if (choice == 4) { // If the user chooses to exit:
            break; // Exit the loop and terminate the program.
        } else { // If the user enters an invalid choice:
            std::cerr << "Invalid choice, please try again\n"; // Print an error message for invalid choices.
        }
    }

    return 0; // Return 0 to indicate successful execution.
}
