#include <fstream>
#include <string>

class Logger {
public:
    static Logger& GetInstance();
    void log(const std::string& message);

private:
    Logger();  // �����ڸ� private�� ����
    std::ofstream logFile_;
};


/*
// Logger.h �̱��� ����
#include <fstream>
#include <string>

class Logger {
public:
    static Logger& GetInstance() {
        static Logger instance("log.txt");
        return instance;
    }
    // GetInstance �Լ��� Logger Ŭ������ ������ �ν��Ͻ��� ��ȯ�մϴ�.
    // 'static' Ű����� �� �Լ��� Ŭ���� �ν��Ͻ��� ������ �ʰ� Ŭ���� ��ü�� ������ �ǹ��մϴ�.
    // 'instance'�� static ���� ������, �Լ��� ó�� ȣ��� �� �� ���� �ʱ�ȭ�˴ϴ�.
    // �̷��� �ϸ� Logger Ŭ������ ���� �ν��Ͻ��� ����˴ϴ�.

    void log(const std::string& message) {
        logFile_ << message << std::endl;
    }
    // log �Լ��� �־��� �޽����� ���Ͽ� ����մϴ�.
    // logFile_ ��Ʈ���� �޽����� ���� �ٹٲ��� �߰��մϴ�.

private:
    Logger(const std::string& filename) : logFile_(filename, std::ios::app) {}
    // Logger�� �����ڴ� private���� ����Ǿ� �ܺο��� ���� �ν��Ͻ�ȭ�� �� �����ϴ�.
    // �̴� �̱��� ������ �Ϲ����� ���� �������, �ν��Ͻ� ������ �����մϴ�.
    std::ofstream logFile_;
    // logFile_�� std::ofstream ��ü��, ���Ͽ� �α׸� ����ϴ� �� ���˴ϴ�.
};
*/