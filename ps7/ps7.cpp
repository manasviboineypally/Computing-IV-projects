// copyright 2024 <manasvi boineypally>
#include <iostream>
#include <fstream>
#include <regex>
#include <string>
#include <vector>
#include <boost/date_time/posix_time/posix_time.hpp>

struct StartupEntry {
    int beginRow;
    int finishRow;
    std::string initiationTime;
    std::string completionTime;
    int64_t elapsedTime;
    bool isFinished;

    StartupEntry() : beginRow(0), finishRow(0), elapsedTime(0), isFinished(false) {}
};

std::vector<StartupEntry> processLogFile(const std::string& inputFile, int& lineCount) {
    std::ifstream logStream(inputFile);
    std::string currentLine;
    std::vector<StartupEntry> startupList;
    StartupEntry currentStartup;
    int rowNumber = 0;

    std::regex initiationPattern(R"(\(log\.c\.166\) server started)");
    std::regex completionPattern(R"(oejs\.AbstractConnector:Started SelectChannelConnector@0\.0\.0\.0:9080)");
    std::regex timePattern(R"((\d{4}-\d{2}-\d{2} \d{2}:\d{2}:\d{2}))");

    while (std::getline(logStream, currentLine)) {
        rowNumber++;
        std::smatch timeMatch;

        if (std::regex_search(currentLine, timeMatch, timePattern)) {
            std::string timeStamp = timeMatch[1];
            if (std::regex_search(currentLine, initiationPattern)) {
                if (currentStartup.beginRow != 0) {
                    startupList.push_back(currentStartup);
                }
                currentStartup = StartupEntry();
                currentStartup.beginRow = rowNumber;
                currentStartup.initiationTime = timeStamp;
            } else if (std::regex_search(currentLine, completionPattern)) {
                currentStartup.finishRow = rowNumber;
                currentStartup.completionTime = timeStamp;
                currentStartup.isFinished = true;

boost::posix_time::ptime startTime
= boost::posix_time::time_from_string(currentStartup.initiationTime);
boost::posix_time::ptime endTime =
 boost::posix_time::time_from_string(currentStartup.completionTime);
boost::posix_time::time_duration timeDiff = endTime - startTime;

                currentStartup.elapsedTime = timeDiff.total_milliseconds();
                startupList.push_back(currentStartup);
                currentStartup = StartupEntry();
            }
        }
    }

    if (currentStartup.beginRow != 0) {
        startupList.push_back(currentStartup);
    }

    lineCount = rowNumber;
    return startupList;
}

void createSummary(const std::string& inputFile,
const std::vector<StartupEntry>& startupList, int lineCount) {
    std::ofstream summaryFile(inputFile + ".rpt");

    int totalStartups = startupList.size();
    int finishedStartups = 0;

    for (const auto& startup : startupList) {
        if (startup.isFinished) {
            finishedStartups++;
        }
    }

    summaryFile << "Device Boot Report\n\n";
    summaryFile << "InTouch log file: " << inputFile << "\n";
    summaryFile << "Lines Scanned: " << lineCount << "\n\n";
    summaryFile << "Device boot count: initiated = " << totalStartups
     << ", completed: " << finishedStartups << "\n\n\n";

    for (const auto& startup : startupList) {
        summaryFile << "=== Device boot ===\n";
summaryFile << startup.beginRow << "(" << inputFile << "): "
<< startup.initiationTime << " Boot Start\n";

        if (startup.isFinished) {
            summaryFile << startup.finishRow << "(" << inputFile << "): "
             << startup.completionTime << " Boot Completed\n";
            summaryFile << "\tBoot Time: " << startup.elapsedTime << "ms \n\n";
        } else {
            summaryFile << "**** Incomplete boot **** \n\n";
        }
    }

    summaryFile.close();
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <logfile>\n";
        return 1;
    }

    std::string inputFile = argv[1];
    int lineCount = 0;
    std::vector<StartupEntry> startupList = processLogFile(inputFile, lineCount);
    createSummary(inputFile, startupList, lineCount);

    return 0;
}
