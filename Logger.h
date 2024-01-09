#include <fstream>
#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>

class Logger {
public:
    static Logger& GetInstance() {
        static Logger instance;
        return instance;
    }

    void log(const std::string& message) {
        logFile_ << message << std::endl;
    }

private:
    std::ofstream logFile_;

    Logger() {
        std::string filename = generateFilename();
        logFile_.open(filename, std::ios::app);
    }

    std::string generateFilename() {
        auto now = std::chrono::system_clock::now();
        auto time = std::chrono::system_clock::to_time_t(now);

        std::tm tm_snapshot;
        localtime_s(&tm_snapshot, &time); // localtime_s를 사용하여 시간을 안전하게 가져옵니다.

        std::stringstream ss;
        ss << std::put_time(&tm_snapshot, "log_%Y%m%d%H%M%S.txt");
        return ss.str();
    }
};
