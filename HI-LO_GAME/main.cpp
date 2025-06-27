// A game of Hi-Lo with some input validation.
// There is a bug (feature) when you for example input 123a in any field, nothing happens
// Expected behavior is a mistake from the program, I need to fix it later...

#include <cstdlib> // for std::exit
#include <iostream>
#include <random> // for std::mt19937
#include <limits>

void ignoreLine()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

bool hasUnextractedInput()
{
    return !std::cin.eof() && std::cin.peek() != '\n';
}
bool clearFailedExtraction()
{
    // Check for failed extraction
    if (!std::cin) // If the previous extraction failed
    {
        if (std::cin.eof()) // If the stream was closed
        {
            std::exit(0); // Shut down the program now
        }

        // Let's handle the failure
        std::cin.clear(); // Put us back in 'normal' operation mode
        ignoreLine();     // And remove the bad input

        return true;
    }

    return false;
}
int getInt()
{
    while (true) // Loop until user enters a valid input
    {
        double x{};
        std::cin >> x;
        if (clearFailedExtraction())
        {
            std::cout << "Oops, that input is invalid.  Please try again.\n";
            continue;
        }
        if (!std::cin) // If the previous extraction failed
        {
            // Let's handle the failure
            std::cout << "That seems to be wrong, please try again \n";
            std::cin.clear(); // Put us back in 'normal' operation mode
            ignoreLine();     // And remove the bad input
            continue;
        }
        if (x<0 || x>100) // If the previous extraction failed
        {
            // Let's handle the failure
            std::cout << "Value should be between 0 and 100, try again: \n";
            std::cin.clear(); // Put us back in 'normal' operation mode
            ignoreLine();     // And remove the bad input
            continue;
        }

        if (hasUnextractedInput())
        {
            ignoreLine(); // remove extraneous input
            continue;
        }

        ignoreLine();
        return x;
    }
}
int getGuesses()
{
    while (true) // Loop until user enters a valid input
    {
        double x{};
        std::cin >> x;
        if (clearFailedExtraction())
        {
            std::cout << "Oops, that input is invalid.  Please try again.\n";
            continue;
        }
        if (!std::cin) // If the previous extraction failed
        {
            // Let's handle the failure
            std::cout << "That seems to be wrong, please try again \n";
            std::cin.clear(); // Put us back in 'normal' operation mode
            ignoreLine();     // And remove the bad input
            continue;
        }
        if (x<=0 || x>10) // If the previous extraction failed
        {
            // Let's handle the failure
            std::cout << "You can have between 1 and 10 tries! \n";
            std::cin.clear(); // Put us back in 'normal' operation mode
            ignoreLine();     // And remove the bad input
            continue;
        }

        if (hasUnextractedInput())
        {
            ignoreLine(); // remove extraneous input
            continue;
        }
        return x;

    }
}
void game(int guesses, int min, int max) {

    std::mt19937 mt{
                    std::random_device{}()}; // Instantiate a 32-bit Mersenne Twister

    std::uniform_int_distribution number{min, max};
    int win = {number(mt)};

  std::cout << "Let's play a game. I'm thinking of a number between " << min
            << " and " << max << " You have " << guesses
            << " tries to guess what it is. \n";
  for (int count{1}; count <= guesses; count++) {
    int guess{};
    std::cout << "Guess #" << count << ": ";
    guess = {getInt()};
    if (guess > win)
      std::cout << "Your guess is too high \n";
    else if (guess < win)
      std::cout << "Your guess is too low \n";
    else if (guess == win) {
      std::cout << "Correct! You win! \n";
      return;
    }
    if (count == guesses)
      std::cout << "Sorry, you lose. The correct number was: " << win << '\n';
  }
}

bool again() {
  char again{};
  while (again != 'y') {
    std::cout << "Would you like to play again (type 'y' if you wish to play "
                 "again, 'n' if you wish to finish)? \n";
    std::cin >> again;
    switch (again)
    {
    case 'y': return again;
    case 'n': std::cout << "Thank you for playing \n";
        return 0; // return it to the caller
    default: // otherwise tell the user what went wrong
        std::cout << "Oops, that input is invalid.  Please try again.\n";
        ignoreLine();
    }

    if (hasUnextractedInput())
    {
        ignoreLine(); // remove extraneous input
        continue;
    }


  }
  return 0;
}

int main() {

    std::cout << "Hey! This is a game of HI-LO made by Mitya Zayats. \n"
                 "In the course of it, you need to guess the number in a limited amount of tries. \n"
                 "If the guessed number is too high or low, you will be given a warning. If it is correct - You win! \n"
                 "Let's set up the rules, how many guesses do you wish to have? "
                 "Type the number between 0 and 10: \n";
    int guesses{getGuesses()};
    std::cout << "What do you want the minimum number to be? Type the number "
                 "between 0 and 100: \n";
    int min{getInt()};

    std::cout << "What do you want the maximum number to be? Type the number "
                 "between 0 and 100: \n";
    int max{getInt()};
    game(guesses, min, max);

    while (again())
        game(guesses, min, max);
    return 0;
}
