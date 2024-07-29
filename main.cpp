#include <iostream> // This directive includes the iostream library, which allows us to use input and output streams (like std::cin and std::cout).
#include <string>   // This directive includes the string library, which provides the std::string class for handling text strings.
#include <vector>   // This directive includes the vector library, which provides the std::vector class for dynamic arrays.

/// Define a class named TodoItem to represent a single to-do item.
class TodoItem {
public:
    // Constructor: This special function is called when an object of the class is created.
    // It initializes the TodoItem with a description and an optional completed status (default is false).
    TodoItem(const std::string &description, bool completed = false)
        : description(description), completed(completed) {} // Member initializer list initializes the member variables.

    // Getter method to retrieve the description of the to-do item.
    std::string getDescription() const { return description; }

    // Getter method to check if the to-do item is completed.
    bool isCompleted() const { return completed; }

    // Method to mark the to-do item as completed.
    void complete() { completed = true; }

private:
    std::string description; // A private member variable to hold the description of the to-do item.
    bool completed;          // A private member variable to indicate whether the to-do item is completed.
};

/// Define a class named TodoList to manage a list of to-do items.
class TodoList {
public:
    // Method to add a new to-do item to the list.
    void addItem(const std::string &description) {
        items.push_back(TodoItem(description)); // Adds a new TodoItem to the vector of items.
    }

    // Method to mark a to-do item as completed based on its index in the list.
    void completeItem(size_t index) { // size_t is an unsigned integer type used for array indexing and loop counting.
        if (index < items.size()) { // Check if the index is valid (within the range of the vector).
            items[index].complete(); // Mark the item as completed.
        } else {
            std::cerr << "Invalid index\n"; // Print an error message if the index is invalid.
        }
    }

    // Method to list all to-do items.
    void listItems() const { // const indicates that this method does not modify any member variables.
        for (size_t i = 0; i < items.size(); ++i) { // Loop through each item in the vector.
            // Print the item index, description, and completion status.
            std::cout << i + 1 << ". " << items[i].getDescription()
                      << (items[i].isCompleted() ? " [Completed]" : "") << "\n";
        }
    }

private:
    std::vector<TodoItem> items; // A private member variable to store the list of to-do items in a dynamic array (vector).
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
