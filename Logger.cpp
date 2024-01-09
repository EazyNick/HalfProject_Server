#include "Logger.h"

Logger& Logger::GetInstance() {
    static Logger instance;
    return instance;
}

Logger::Logger() : logFile_("log.txt", std::ios::app) {
    // 파일을 추가 모드로 열기
}

void Logger::log(const std::string& message) {
    logFile_ << message << std::endl;
    // 메시지를 파일에 기록
}


/* 현재 시간 나타내는 로거
#include <fstream>
#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>

class Logger {
public:
    Logger() {
        std::string filename = generateFilename();
        logFile_.open(filename, std::ios::app);
    }

    void log(const std::string& message) {
        logFile_ << message << std::endl;
    }

private:
    std::ofstream logFile_;

    std::string generateFilename() {
        auto now = std::chrono::system_clock::now();
        auto time = std::chrono::system_clock::to_time_t(now);

        std::stringstream ss;
        ss << std::put_time(std::localtime(&time), "log_%Y%m%d%H%M%S.txt");
        return ss.str();
    }
};
*/

/*
// 메인 함수 (테스트 목적)
int main() {
    Logger logger("log.txt"); // Logger 인스턴스 생성
    logger.log("This is a log message."); // 메시지 로깅
}




/*
#include <fstream> // 파일 입출력 관련 표준 라이브러리 헤더
#include <string>  // 문자열 관련 표준 라이브러리 헤더

class Logger { // 'Logger' 클래스 정의
public:
    Logger(const std::string& filename) : logFile_(filename, std::ios::app) {
        // 클래스의 생성자입니다. 문자열 타입의 'filename'을 인자로 받습니다.
        // 'logFile_' 스트림 객체를 초기화하고, 파일을 추가 모드(app)로 연다는 의미입니다.
        // 이는 파일의 내용을 덮어쓰지 않고 끝에 추가함을 의미합니다.
    }

    void log(const std::string& message) {
        // 'log'라는 이름의 멤버 함수를 정의합니다. 로그 메시지를 기록하는 기능을 수행합니다.
        logFile_ << message << std::endl; // 'logFile_' 스트림에 메시지를 쓰고, 줄바꿈을 추가합니다.
    }

private:
    std::ofstream logFile_; // 파일 출력 스트림 객체. 파일에 데이터를 쓰는 데 사용합니다.
};

int main() {
    Logger logger("log.txt"); // 'Logger' 클래스의 객체를 생성하고, "log.txt" 파일로 로그를 기록합니다.
    logger.log("This is a log message."); // 'log' 함수를 호출하여 메시지를 로그 파일에 기록합니다.
}

*/