#include <fstream>  // ���� ��Ʈ���� ���� ����� ����ϱ� ���� ��� ����
#include <string>   // std::string Ŭ������ ����ϱ� ���� ��� ����
#include <chrono>   // ��¥ �� �ð� ���� ����� ����ϱ� ���� ��� ����
#include <iomanip>  // ����� �Ŵ�ǽ������ ����� ����ϱ� ���� ��� ���� (���⼭�� std::put_time �Լ��� ����ϱ� ���� �ʿ�)
#include <sstream>  // ���ڿ� ��Ʈ���� ���� ����� ����ϱ� ���� ��� ����
#include <iostream>

class Logger {
public:
    // GetInstance �Լ��� Logger Ŭ������ �̱��� �ν��Ͻ��� ��ȯ�ϴ� ����(static) �Լ�
    // �̱��� - � Ŭ������ �ν��Ͻ��� ���ø����̼� ��ü�� ���ļ� ���� �ϳ��� �����ϵ��� �����ϴ� ����
    // static(����) ���� Ŭ���� �ν��Ͻ��� �ȸ����, �׳� Logger::GetInstance ���� ��� ����
    // Logger �ڿ� ���� &�� GetInstance �Լ��� Logger �ν��Ͻ��� ������ ��ȯ�Ѵٴ� ���� �ǹ�
    static Logger& GetInstance() {
        // �޼��� ȣ���� ���� �Ŀ��� ��� �����մϴ�. �׷���, ���α׷��� ����Ǵ� ���� �� �ϳ��� Logger �ν��Ͻ����� ����
        // Logger Ÿ���� ��ü�� �����մϴ�. �̴� Logger Ŭ������ �ν��Ͻ�
        static Logger instance; // �ѹ� ����Ǹ� �ι��� ���࿡���� ������� ����
        // GetInstance �޼��尡 ���� �� ȣ��Ǵ��� instance�� �� ���� ����
        return instance;
        //�޼��尡 ó�� ȣ��Ǹ� static Logger instance;�� ����Ǿ� Logger Ŭ������ �ν��Ͻ��� �����մϴ�.
        //�޼��尡 ��ȯ�� �� ������ Logger �ν��Ͻ��� ������ ��ȯ�մϴ�.
        //�޼��尡 �ٽ� ȣ��Ǹ�, �̹� ������ instance�� �ٽ� ��ȯ�մϴ�.���ο� Logger ��ü�� �������� �ʽ��ϴ�.
    }
    //  ���� �޽����� �α� ���Ͽ� �ۼ�
    void log(const std::string& message) {

        std::cout << message << std::endl;
        logFile_ << message << std::endl;
    }

private:
    std::ofstream logFile_; // �α� �޽����� �ۼ��� ���� ��Ʈ�� ��ü

    Logger() {
        //Logger�� �����ڴ� generateFilename �Լ��� ȣ���Ͽ� �α� ������ �̸��� �����ϰ�, ������ �߰� ���(std::ios::app)�� ���ϴ�.
        std::string filename = generateFilename();
        logFile_.open(filename, std::ios::app); // ������ ���� �̸��� ����Ͽ� �α� ������ ���ϴ�.
    }

    std::string generateFilename() {
        auto now = std::chrono::system_clock::now(); // ���� �ý��� �ð��� �����ɴϴ�.
        auto time = std::chrono::system_clock::to_time_t(now); // std::chrono �ð��� time_t �������� ��ȯ�մϴ�. 
        // time_t�� �Ϲ������� �ð��� ��Ÿ���� C++�� ǥ�� Ÿ��

        std::tm tm_snapshot;
        // time_t Ÿ���� �ð��� std::tm ����ü�� �����ϰ� ��ȯ
        localtime_s(&tm_snapshot, &time); // localtime_s�� ����Ͽ� �ð��� �����ϰ� �����ɴϴ�.

        std::stringstream ss; // ���ڿ��� �����ϱ� ���� ��Ʈ���� ����
        ss << std::put_time(&tm_snapshot, "log_%Y%m%d%H%M%S.txt"); // �ð��� Ư�� ����("YYYYMMDDHHMMSS")���� ��Ʈ���� ���
        return ss.str(); // ��Ʈ���� ����� ���ڿ��� std::string���� ��ȯ�Ͽ� ��ȯ
    }
};
