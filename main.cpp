#include <iostream> // Include the input-output stream library for handling standard input and output.
#include <string>   // Include the string library for handling strings.
#include <vector>   // Include the vector library for handling dynamic arrays (vectors).

// Define the TodoItem class which represents a single to-do item.
class TodoItem {
public:
    // Constructor to initialize the TodoItem with a description and optionally its completed status (default is false).
    TodoItem(const std::string &description, bool completed = false)
        : description(description), completed(completed) {}

    // Getter for the description of the to-do item.
    std::string getDescription() const { return description; }

    // Getter to check if the to-do item is completed.
    bool isCompleted() const { return completed; }

    // Method to mark the to-do item as completed.
    void complete() { completed = true; }

private:
    std::string description; // The description of the to-do item.
    bool completed;          // The status of the to-do item (true if completed, false otherwise).
};

// Define the TodoList class which manages a list of to-do items.
class TodoList {
public:
    // Method to add a new to-do item to the list.
    void addItem(const std::string &description) {
        items.push_back(TodoItem(description));
    }

    // Method to mark a to-do item as completed based on its index in the list.
    void completeItem(size_t index) {
        if (index < items.size()) {
            items[index].complete(); // Complete the item if the index is valid.
        } else {
            std::cerr << "Invalid index\n"; // Print an error message if the index is invalid.
        }
    }

    // Method to list all to-do items.
    void listItems() const {
        for (size_t i = 0; i < items.size(); ++i) {
            // Print each item with its index, description, and completion status.
            std::cout << i + 1 << ". " << items[i].getDescription()
                      << (items[i].isCompleted() ? " [Completed]" : "") << "\n";
        }
    }

private:
    std::vector<TodoItem> items; // A vector to store the list of to-do items.
};

// Function to display the menu options to the user.
void displayMenu() {
    std::cout << "1. Add a to-do item\n"
              << "2. Complete a to-do item\n"
              << "3. List all to-do items\n"
              << "4. Exit\n";
}

// Main function which is the entry point of the program.
int main() {
    TodoList todoList; // Create an instance of TodoList to manage the to-do items.
    int choice;        // Variable to store the user's menu choice.

    // Infinite loop to keep the program running until the user chooses to exit.
    while (true) {
        displayMenu(); // Display the menu options.
        std::cout << "Enter your choice: ";
        std::cin >> choice; // Read the user's choice.

        if (choice == 1) {
            std::cin.ignore(); // Ignore the newline character left in the input buffer.
            std::string description;
            std::cout << "Enter the description: ";
            std::getline(std::cin, description); // Read the description of the new to-do item.
            todoList.addItem(description); // Add the new item to the to-do list.
        } else if (choice == 2) {
            size_t index;
            std::cout << "Enter the index of the item to complete: ";
            std::cin >> index; // Read the index of the item to complete.
            todoList.completeItem(index - 1); // Mark the item as completed (adjusting for zero-based index).
        } else if (choice == 3) {
            todoList.listItems(); // List all to-do items.
        } else if (choice == 4) {
            break; // Exit the loop and terminate the program.
        } else {
            std::cerr << "Invalid choice, please try again\n"; // Print an error message for invalid choices.
        }
    }

    return 0; // Return 0 to indicate successful execution.
}
