# PS7: Kronos Log Parsing

## Contact
Name:manasvi boineypally
Section:202
Time to Complete:7hrs


## Description
Explain what the project does.
The project is a C++ application that analyzes device boot log files to identify boot initiation and completion events. It uses regular expressions to extract timestamps and calculate the elapsed time for each boot, organizing this information into structured entries. After processing the log, it generates a summary report detailing the number of initiated and completed boots, along with insights on each event. This tool aids system administrators and developers in monitoring performance, troubleshooting issues, and reporting on device behavior.

### Features
Describe what your major decisions were and why you did things that way.

==>Data Structure Design:
Decision: A StartupEntry struct was created to encapsulate all relevant information about each boot event.
Reason: This design promotes better organization and readability of the code, making it easier to manage boot-related data and simplifying the summary report generation.

==>Regular Expressions for Log Parsing:
Decision: Regular expressions were employed to identify boot initiation and completion events within the log lines.
Reason: Regular expressions provide a flexible and powerful way to match patterns in text, allowing for precise extraction of timestamps and event indicators without needing complex string manipulation.

==>Boost Library for Time Calculations:
Decision: The Boost Date_Time library was utilized for handling time calculations.
Reason: Boost offers robust functionality for parsing and manipulating date and time, which simplifies the process of calculating elapsed time between boot initiation and completion.

==>Separation of Concerns:
Decision: The project was structured into distinct functions (processLogFile and createSummary) to handle different aspects of the task.
Reason: This separation enhances code maintainability and readability, allowing future modifications or enhancements to be implemented more easily without affecting the entire codebase.

==>Output Summary Report Format:
Decision: The summary report was designed to be human-readable, with clear sections for total counts and detailed entries for each boot event.
Reason: A well-structured report improves usability for end-users, making it easier to quickly understand device performance metrics and identify issues.

### Approach
Describe your overall approach to solving this problem.


My overall approach to solving the problem involved several key steps. First, I clearly defined the requirements for analyzing device boot log files, which guided the design of a structured data model using a StartupEntry struct to encapsulate relevant information about each boot event. I implemented a line-by-line log file parsing mechanism, utilizing regular expressions to accurately identify boot initiation and completion events, and employed the Boost Date_Time library for precise time calculations of elapsed durations. After collecting the data into structured entries, I developed a function to generate a clear and human-readable summary report detailing the number of initiated and completed boots, along with specific event information. I also incorporated basic error handling to manage potential issues with command-line arguments and file access, enhancing user experience. Finally, I conducted thorough testing with various log files to ensure the application functions correctly across different scenarios, resulting in a reliable tool for analyzing device boot logs.

### Regex
What regular expressions did you use?  Explain what each one does.

Boot Initiation Pattern:

std::regex initiationPattern(R"(\(log\.c\.166\) server started)");

Explanation: This regex matches the specific log message indicating that the server has started. The pattern looks for the exact text "(log.c.166) server started", which signifies the initiation of a boot process. The parentheses are escaped to treat them as literal characters.
Boot Completion Pattern:

std::regex completionPattern(R"(oejs\.AbstractConnector:Started SelectChannelConnector@0\.0\.0\.0:9080)");

Explanation: This regex identifies the log entry that indicates the completion of the boot process. It matches the text oejs.AbstractConnector:Started SelectChannelConnector@0.0.0.0:9080, which is a specific message logged when the server is fully operational and ready to accept connections.
Timestamp Extraction Pattern:

std::regex timePattern(R"((\d{4}-\d{2}-\d{2} \d{2}:\d{2}:\d{2}))");

Explanation: This regex captures timestamps in the format YYYY-MM-DD HH:MM:SS. It looks for four digits (year), followed by a hyphen, two digits (month), another hyphen, two digits (day), a space, and then two digits for hours, minutes, and seconds separated by colons. This pattern is crucial for extracting time information from each log entry to calculate elapsed boot times.
### Issues
What did you have trouble with?  What did you learn?  What doesn't work?  Be honest.  You might be penalized if you claim something works and it doesn't.

had the issues with thw output rpt files regaring the extra credit and am not sure about the output and i partially did the extra credit

### Extra Credit
Anything special you did.  This is required to earn bonus points.
i partially implemented the extra credit by adding the summary header in the output file 

Summary Header Addition:
I modified the createSummary function to include a header section at the beginning of the report. This header provides essential information about the log file being analyzed, such as the file name, total lines scanned, and overall boot counts. The header is formatted for clarity, making it easy for users to understand the context of the report.
Tracking Start and Completion Times:
Within the processLogFile function, I ensured that both initiation and completion timestamps were captured for each boot event. When a boot is initiated, the timestamp is stored in initiationTime, and when it completes, the timestamp is stored in completionTime. This allows for detailed tracking of each service's start and finish times.
Calculating Elapsed Time:
After capturing both timestamps, I calculated the elapsed time for each boot by determining the difference between completionTime and initiationTime. This value is stored in elapsedTime, allowing users to see how long each boot process took.
Formatting Output:
In the summary report, I included sections that detail each boot event's start and completion times alongside the calculated elapsed time. This structured output makes it easy for users to quickly assess performance metrics for each service.

## Acknowledgements
List all sources of help including the instructor or TAs, classmates, and web pages.

materials provided by the professor 
