#include <fstream>
#include <string>

class Logger {
public:
    static Logger& GetInstance();
    void log(const std::string& message);

private:
    Logger();  // 생성자를 private로 선언
    std::ofstream logFile_;
};


/*
// Logger.h 싱글톤 패턴
#include <fstream>
#include <string>

class Logger {
public:
    static Logger& GetInstance() {
        static Logger instance("log.txt");
        return instance;
    }
    // GetInstance 함수는 Logger 클래스의 유일한 인스턴스를 반환합니다.
    // 'static' 키워드는 이 함수가 클래스 인스턴스에 속하지 않고 클래스 자체에 속함을 의미합니다.
    // 'instance'는 static 로컬 변수로, 함수가 처음 호출될 때 한 번만 초기화됩니다.
    // 이렇게 하면 Logger 클래스의 단일 인스턴스가 보장됩니다.

    void log(const std::string& message) {
        logFile_ << message << std::endl;
    }
    // log 함수는 주어진 메시지를 파일에 기록합니다.
    // logFile_ 스트림에 메시지를 쓰고 줄바꿈을 추가합니다.

private:
    Logger(const std::string& filename) : logFile_(filename, std::ios::app) {}
    // Logger의 생성자는 private으로 선언되어 외부에서 직접 인스턴스화할 수 없습니다.
    // 이는 싱글톤 패턴의 일반적인 구현 방식으로, 인스턴스 생성을 제어합니다.
    std::ofstream logFile_;
    // logFile_은 std::ofstream 객체로, 파일에 로그를 기록하는 데 사용됩니다.
};
*/