#include "Logger.h"

Logger& Logger::GetInstance() {
    static Logger instance;
    return instance;
}

Logger::Logger() : logFile_("log.txt", std::ios::app) {
    // ������ �߰� ���� ����
}

void Logger::log(const std::string& message) {
    logFile_ << message << std::endl;
    // �޽����� ���Ͽ� ���
}


/* ���� �ð� ��Ÿ���� �ΰ�
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
// ���� �Լ� (�׽�Ʈ ����)
int main() {
    Logger logger("log.txt"); // Logger �ν��Ͻ� ����
    logger.log("This is a log message."); // �޽��� �α�
}




/*
#include <fstream> // ���� ����� ���� ǥ�� ���̺귯�� ���
#include <string>  // ���ڿ� ���� ǥ�� ���̺귯�� ���

class Logger { // 'Logger' Ŭ���� ����
public:
    Logger(const std::string& filename) : logFile_(filename, std::ios::app) {
        // Ŭ������ �������Դϴ�. ���ڿ� Ÿ���� 'filename'�� ���ڷ� �޽��ϴ�.
        // 'logFile_' ��Ʈ�� ��ü�� �ʱ�ȭ�ϰ�, ������ �߰� ���(app)�� ���ٴ� �ǹ��Դϴ�.
        // �̴� ������ ������ ����� �ʰ� ���� �߰����� �ǹ��մϴ�.
    }

    void log(const std::string& message) {
        // 'log'��� �̸��� ��� �Լ��� �����մϴ�. �α� �޽����� ����ϴ� ����� �����մϴ�.
        logFile_ << message << std::endl; // 'logFile_' ��Ʈ���� �޽����� ����, �ٹٲ��� �߰��մϴ�.
    }

private:
    std::ofstream logFile_; // ���� ��� ��Ʈ�� ��ü. ���Ͽ� �����͸� ���� �� ����մϴ�.
};

int main() {
    Logger logger("log.txt"); // 'Logger' Ŭ������ ��ü�� �����ϰ�, "log.txt" ���Ϸ� �α׸� ����մϴ�.
    logger.log("This is a log message."); // 'log' �Լ��� ȣ���Ͽ� �޽����� �α� ���Ͽ� ����մϴ�.
}

*/