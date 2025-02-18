# PS6: RandWriter

## Contact
Name:
Section:
Time to Complete:


## Description
Explain what the project does.

The primary goal of the project is to generate random text based on a given input text. It does this by analyzing the input text to understand the relationships between sequences of characters (called k-grams) and then using this information to produce new text that mimics the style and structure of the original input.
### Features
Describe what your major decisions were and why you did things that way.

A primary choice was to use nested std::map structures for storing frequencies of characters following 
k-grams, allowing efficient lookups and updates. To ensure deterministic output, a fixed seed was used for the random number generator, which facilitates consistent results during testing and debugging. Comprehensive input validation was implemented to check the length of the input text against k and to ensure logical integrity in text generation, providing immediate feedback for incorrect inputs. The modular design of the RandWriter class promotes separation of concerns, making the code easier to maintain and extend, while leveraging the Standard Template Library (STL) enhances performance and readability. Finally, the Boost Test Library was chosen for unit testing due to its robust features, increasing confidence in the correctness of the code. Overall, these decisions focused on creating a reliable, user-friendly tool for generating random text based on Markov chain principles.

### Testing
What tests did you write?  What exceptions did you use?  Does your code pass the tests?

Constructor Tests:
Verify that the constructor does not throw exceptions for valid inputs and throws an std::invalid_argument exception when the input text length is less than k.

Order k Tests:
Confirm that the orderK method returns the correct value of k.

Frequency Tests:
Check the frequency of various k-grams and specific characters following those k-grams, ensuring correct counts are returned.
Validate that appropriate exceptions are thrown for invalid k-gram lengths.

Random Character Selection Tests (kRand):
Ensure that kRand correctly selects a character based on frequencies and throws exceptions for invalid or non-existent k-grams.

Text Generation Tests:
Test the generate method to confirm it produces text of the expected length and starts with the correct k-gram.
Validate that exceptions are thrown for invalid arguments, such as incorrect initial k-grams or lengths.

Zero Order Tests:
Specifically test behavior when k=0, including frequency calculations and text generation.

### Lambda
What does your lambda expression do?  What function did you pass it to?

The lambda expression is designed to decrement a random value (randVal) by the frequency of each character in a given 
k-gram's frequency map. The goal is to determine which character corresponds to the randomly generated value based on the cumulative frequencies.

Here is the relevant portion of the code that defines the lambda expression:

auto findChar = [&randVal](const auto& pair) {
    randVal -= pair.second;
    return randVal <= 0;
};

Parameters: The lambda takes a single parameter pair, which represents an element from the inner map of the frequency map. Each pair consists of a character and its corresponding frequency.
Functionality:
It subtracts the frequency (pair.second) from randVal.
It checks if randVal has dropped to zero or below, indicating that this character should be selected.
Function Passed To
The lambda expression is passed to the std::find_if function, which is used as follows:

auto selectedPair = std::find_if(it->second.begin(), it->second.end(), findChar);

Function: std::find_if iterates over the range defined by the inner map (the frequencies of characters following a specifick-gram).
Behavior: It applies the findChar lambda to each element in that range until it finds one for which the lambda returns true. This effectively selects a character based on its weighted probability (frequency), allowing for random selection in accordance with the defined frequencies.

### Issues
What did you have trouble with?  What did you learn?  What doesn't work?  Be honest.  You might be penalized if you claim something works and it doesn't.
output 
### Extra Credit
Anything special you did.  This is required to earn bonus points.

## Acknowledgements
List all sources of help including the instructor or TAs, classmates, and web pages.

PROFESSORS MATERIAL
