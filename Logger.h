#include <fstream>  // 파일 스트림에 대한 기능을 사용하기 위한 헤더 파일
#include <string>   // std::string 클래스를 사용하기 위한 헤더 파일
#include <chrono>   // 날짜 및 시간 관련 기능을 사용하기 위한 헤더 파일
#include <iomanip>  // 입출력 매니퓰레이터 기능을 사용하기 위한 헤더 파일 (여기서는 std::put_time 함수를 사용하기 위해 필요)
#include <sstream>  // 문자열 스트림에 대한 기능을 사용하기 위한 헤더 파일

class Logger {
public:
    // GetInstance 함수는 Logger 클래스의 싱글톤 인스턴스를 반환하는 정적 함수
    static Logger& GetInstance() {
        static Logger instance;
        return instance;
    }
    //  받은 메시지를 로그 파일에 작성
    void log(const std::string& message) {
        logFile_ << message << std::endl;
    }

private:
    std::ofstream logFile_; // 로그 메시지를 작성할 파일 스트림 객체

    Logger() {
        //Logger의 생성자는 generateFilename 함수를 호출하여 로그 파일의 이름을 생성하고, 파일을 추가 모드(std::ios::app)로 엽니다.
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
