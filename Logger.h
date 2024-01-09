#include <fstream>  // ���� ��Ʈ���� ���� ����� ����ϱ� ���� ��� ����
#include <string>   // std::string Ŭ������ ����ϱ� ���� ��� ����
#include <chrono>   // ��¥ �� �ð� ���� ����� ����ϱ� ���� ��� ����
#include <iomanip>  // ����� �Ŵ�ǽ������ ����� ����ϱ� ���� ��� ���� (���⼭�� std::put_time �Լ��� ����ϱ� ���� �ʿ�)
#include <sstream>  // ���ڿ� ��Ʈ���� ���� ����� ����ϱ� ���� ��� ����

class Logger {
public:
    // GetInstance �Լ��� Logger Ŭ������ �̱��� �ν��Ͻ��� ��ȯ�ϴ� ���� �Լ�
    static Logger& GetInstance() {
        static Logger instance;
        return instance;
    }
    //  ���� �޽����� �α� ���Ͽ� �ۼ�
    void log(const std::string& message) {
        logFile_ << message << std::endl;
    }

private:
    std::ofstream logFile_; // �α� �޽����� �ۼ��� ���� ��Ʈ�� ��ü

    Logger() {
        //Logger�� �����ڴ� generateFilename �Լ��� ȣ���Ͽ� �α� ������ �̸��� �����ϰ�, ������ �߰� ���(std::ios::app)�� ���ϴ�.
        std::string filename = generateFilename();
        logFile_.open(filename, std::ios::app);
    }

    std::string generateFilename() {
        auto now = std::chrono::system_clock::now();
        auto time = std::chrono::system_clock::to_time_t(now);

        std::tm tm_snapshot;
        localtime_s(&tm_snapshot, &time); // localtime_s�� ����Ͽ� �ð��� �����ϰ� �����ɴϴ�.

        std::stringstream ss;
        ss << std::put_time(&tm_snapshot, "log_%Y%m%d%H%M%S.txt");
        return ss.str();
    }
};
