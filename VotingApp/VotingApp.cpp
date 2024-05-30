#include <iostream> // The library for Input and Output
#include <fstream> // Read and write from files
#include <string> // Library for using text
#define NOMINMAX // Tells Windows.h not to use min and max macros, needed to avoid conflict
#include <Windows.h> // Includes functions of Windows api, used here to change color
using namespace std; // Using namespace standard

const int voteAge = 18; // The age you can vote is constant and unchangeable
int sop = 0; // Declares variable that will be used for the Switch case when using the main menu options
string first_Name; // Variable to set first name
string second_Name; // Variable to set second name
int myAge; // Variable to set age
bool progLoop; // Variable to be used later when asking user if they wish to retry or exit
bool fin = false; // Sets true or false condition that will eventually end the program when true flag is met

void setcolor(unsigned char color) // Sets a variable called setcolor that will allow for change of colour in Background or text of the console
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

int main() // Main function of the program
{
    setcolor(13); // Sets text colour as light magenta

    fstream myFile; // Declaring fstream variable called myFile that will be called when writing into text file
    myFile.open("Result.txt", ios::out); // Will write into a text file called Result, if it doesn't exist already it will create it

    if (myFile.is_open()) { // If the text file is open

        do { // Will execute one time before it evaluates condition.
            cout << "\nWelcome to the Voting Eligibility Checker, select an option:  1 - Eligibility, 2 - Rules, 3 - Credits, 4 - Close: \n"; // Outputs this text to the console
            cin >> sop; // Takes input from console

            while (cin.fail()) // cin.fail checks if cin input has encountered an error, such as input not meeting expected data type. cin.fail()), means program will loop until user gives valid input in cin.
            {
                cin.clear(); // Clears the error flag that has been triggered by cin.fail
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore all characters in input stream buffer until it reaches either the end of the line or reaches character limit.
                cout << "Invalid input. Please enter a number: ";
                cin >> sop;
            }

            switch (sop) // This Switch statement allows program to decide between multiple code blocks to be executed based on the user input       
            {

            case 1: // Code block will be executed if "1" is input at main menu"
                cout << "\nEnter your first name: "; // \n creates a new line
                cin >> first_Name;
                cout << "Enter your surname: ";
                cin >> second_Name;
                cout << "Enter your age: ";
                cin >> myAge;
                myFile << "Name: " << first_Name << " " << second_Name << "\n";

                while (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    setcolor(12); // Sets text colour as red
                    cout << "\nInvalid age. Please enter a number: ";
                    setcolor(13);
                    cin >> myAge;
                }

                myFile << "Age: " << myAge << "\n";
                cout << endl;

                if (myAge < voteAge) // If age input is less than set voting age (18) do this code block
                {
                    cout << "I'm sorry, " << first_Name << ", you are unable to vote for another " << voteAge - myAge << " years \n";
                    myFile << "I'm sorry, " << first_Name << ", you are unable to vote for another " << voteAge - myAge << " years \n\n";
                    cout << "If you would like to return to the main menu press 0, if you wish to exit enter another number:\n";
                    cin >> progLoop;
                    if (!progLoop == 0) // If progLoop is false 
                    {
                        cout << "\nThank you for using this program, your results are included in the text file in this folder\n";
                        fin = true; // Sets fin to true when progLoop is false, thereby ending program
                    }
                }

                else // Otherwise do this code block              
                {
                    cout << first_Name << ", you have been eligible to vote for " << myAge - voteAge << " years\n";
                    myFile << first_Name << ", you have been eligible to vote for " << myAge - voteAge << " years\n\n";
                    cout << "If you would like to return to the main menu press 0, if you wish to exit enter another number:\n";
                    cin >> progLoop;
                    if (!progLoop == 0)
                    {
                        cout << "\nThank you for using this program, your results are included in the text file in this folder\n";
                        fin = true;
                    }
                }
                break; // Exits out of switch statement, prevents the other case blocks from being executed

            case 2:
                cout << "\nTo be eligible to vote, you must be 18 years of age. Please ensure when voting you are registered and provide identification.\n";
                break;

            case 3:
                cout << "\nAll testing, debugging and moral support performed by Callum Bowie and Morgan Prichard.\n";
                break;

            case 4:
                fin = true;
                cout << "\nThank you for using this program, your results are included in the text file in this folder\n";
                break;

            default:
                setcolor(12);
                cout << "\nInvalid option. Please enter a valid choice.\n";
                setcolor(13);
                break;
            }

        } while (!fin); // Will loop while fin is not true

        myFile.close(); // Closes the text file you are writing to

    }

    return 0; // Used to indicate program has executed sucessfully
}