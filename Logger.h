#include <fstream>  // 파일 스트림에 대한 기능을 사용하기 위한 헤더 파일
#include <string>   // std::string 클래스를 사용하기 위한 헤더 파일
#include <chrono>   // 날짜 및 시간 관련 기능을 사용하기 위한 헤더 파일
#include <iomanip>  // 입출력 매니퓰레이터 기능을 사용하기 위한 헤더 파일 (여기서는 std::put_time 함수를 사용하기 위해 필요)
#include <sstream>  // 문자열 스트림에 대한 기능을 사용하기 위한 헤더 파일
#include <iostream>

class Logger {
public:
    // GetInstance 함수는 Logger 클래스의 싱글톤 인스턴스를 반환하는 정적(static) 함수
    // 싱글턴 - 어떤 클래스의 인스턴스가 애플리케이션 전체에 걸쳐서 오직 하나만 존재하도록 보장하는 구조
    // static(정적) 사용시 클래스 인스턴스를 안만들고, 그냥 Logger::GetInstance 쓰면 사용 가능
    // Logger 뒤에 붙은 &는 GetInstance 함수가 Logger 인스턴스의 참조를 반환한다는 것을 의미
    static Logger& GetInstance() {
        // 메서드 호출이 끝난 후에도 계속 존재합니다. 그래서, 프로그램이 실행되는 동안 단 하나의 Logger 인스턴스만이 존재
        // Logger 타입의 객체를 선언합니다. 이는 Logger 클래스의 인스턴스
        static Logger instance; // 한번 실행되면 두번쨰 실행에서는 실행되지 않음
        // GetInstance 메서드가 여러 번 호출되더라도 instance는 한 번만 생성
        return instance;
        //메서드가 처음 호출되면 static Logger instance;가 실행되어 Logger 클래스의 인스턴스를 생성합니다.
        //메서드가 반환할 때 생성된 Logger 인스턴스의 참조를 반환합니다.
        //메서드가 다시 호출되면, 이미 생성된 instance를 다시 반환합니다.새로운 Logger 객체가 생성되지 않습니다.
    }
    //  받은 메시지를 로그 파일에 작성
    void log(const std::string& message) {

        std::cout << message << std::endl;
        logFile_ << message << std::endl;
    }

private:
    std::ofstream logFile_; // 로그 메시지를 작성할 파일 스트림 객체

    Logger() {
        //Logger의 생성자는 generateFilename 함수를 호출하여 로그 파일의 이름을 생성하고, 파일을 추가 모드(std::ios::app)로 엽니다.
        std::string filename = generateFilename();
        logFile_.open(filename, std::ios::app); // 생성된 파일 이름을 사용하여 로그 파일을 엽니다.
    }

    std::string generateFilename() {
        auto now = std::chrono::system_clock::now(); // 현재 시스템 시간을 가져옵니다.
        auto time = std::chrono::system_clock::to_time_t(now); // std::chrono 시간을 time_t 형식으로 변환합니다. 
        // time_t는 일반적으로 시간을 나타내는 C++의 표준 타입

        std::tm tm_snapshot;
        // time_t 타입의 시간을 std::tm 구조체로 안전하게 변환
        localtime_s(&tm_snapshot, &time); // localtime_s를 사용하여 시간을 안전하게 가져옵니다.

        std::stringstream ss; // 문자열을 조립하기 위한 스트림을 생성
        ss << std::put_time(&tm_snapshot, "log_%Y%m%d%H%M%S.txt"); // 시간을 특정 형식("YYYYMMDDHHMMSS")으로 스트림에 기록
        return ss.str(); // 스트림에 저장된 문자열을 std::string으로 변환하여 반환
    }
};
